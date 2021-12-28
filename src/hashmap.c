#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../include/hashmap.h"


struct HashMapEntry {
    size_t key_size;
    size_t value_size;
    bool occupied;
    bool deleted;
};

struct HashMap {
    struct HashMapEntry * entries;
    size_t size;
    size_t num_entries;
    uint8_t * keys;
    size_t key_max_size;
    uint8_t * values;
    size_t value_max_size;
};


uint64_t
_hashmap_hash64(char * in, size_t size)
{
    // FNV-1a
    uint64_t hash = 0xcbf29ce484222325;
    for (size_t i=0; i<size; ++i) {
        hash ^= in[i];
        hash *= 0x00000100000001b3;
    }
    return hash;
}


uint32_t
_hashmap_hash32(char * in, size_t size)
{
    // FNV-1a
    uint32_t hash = 0x811c9dc5;
    for (size_t i=0; i<size; ++i) {
        hash ^= in[i];
        hash *= 0x01000193;
    }
    return hash;
}


uint32_t
_hashmap_hash32_values(HHASHMAP hHashMap)
{
    struct HashMap * hmap = (struct HashMap *) hHashMap;
    return _hashmap_hash32((char *)hmap->values, hmap->value_max_size*hmap->size);
}


uint32_t
_hashmap_hash32_keys(HHASHMAP hHashMap)
{
    struct HashMap * hmap = (struct HashMap *) hHashMap;
    return _hashmap_hash32((char *)hmap->keys, hmap->key_max_size*hmap->size);
}


HHASHMAP
hashmap_create(size_t size, size_t key_max_size, size_t value_max_size)
{
    struct HashMap * hmap = malloc(sizeof(struct HashMap));
    
    size_t size_power_of_two = (size_t) pow(2.0, ceil(log2(size))); // hash & (hmap->size-1) == hash % hmap->size for hmap->size a power of 2;
    size_t value_size_power_of_two = (size_t) pow(2.0, ceil(log2(value_max_size))); // id*hmap->key_max_size --> becomes shift by power of 2
    size_t key_size_power_of_two = (size_t) pow(2.0, ceil(log2(key_max_size)));
    
    hmap->entries = calloc(size_power_of_two, sizeof(struct HashMapEntry));
    hmap->size = size_power_of_two;
    hmap->num_entries = 0;
    
    hmap->keys = calloc(size_power_of_two, key_size_power_of_two);
    hmap->key_max_size = key_size_power_of_two;
    
    hmap->values = calloc(size_power_of_two, value_size_power_of_two);
    hmap->value_max_size = value_size_power_of_two;

    return (HHASHMAP) hmap;
}


void
hashmap_clear(HHASHMAP hHashMap)
{
    struct HashMap * hmap = (struct HashMap *) hHashMap;
    memset(hmap->values, 0, hmap->value_max_size*hmap->size);
    memset(hmap->keys, 0, hmap->key_max_size*hmap->size);
    hmap->num_entries = 0;
    memset(hmap->entries, 0, hmap->size*sizeof(struct HashMapEntry));
}


void
hashmap_free(HHASHMAP hHashMap)
{
    struct HashMap * hmap = (struct HashMap *) hHashMap;

    free(hmap->keys);
    hmap->keys = NULL;

    free(hmap->values);
    hmap->values = NULL;

    free(hmap->entries);
    hmap->entries = NULL;

    free(hmap);
}


size_t
hashmap_size(HHASHMAP hHashMap)
{
    return ((struct HashMap *) hHashMap)->num_entries;
}


size_t
hashmap_capacity(HHASHMAP hHashMap)
{
    return ((struct HashMap *) hHashMap)->size;
}


bool
hashmap_is_full(HHASHMAP hHashMap)
{
    struct HashMap * hmap = (struct HashMap *) hHashMap;
    return hmap->num_entries == hmap->size;
}


bool
hashmap_is_empty(HHASHMAP hHashMap)
{
    return ((struct HashMap *) hHashMap)->num_entries == 0;
}


bool
hashmap_store(HHASHMAP hHashMap, void * key, size_t key_size, void * value, size_t value_size)
{
    struct HashMap * hmap = (struct HashMap *) hHashMap;

    uint32_t hash = _hashmap_hash32(key, key_size);
    uint32_t id = hash & (hmap->size-1);

    size_t i = 0;
    for (; i<hmap->size; ++i) {
        if (hmap->entries[id].occupied && (memcmp(key, &hmap->keys[id*hmap->key_max_size], key_size) == 0))
            // key is already used
            return false;
        if (!hmap->entries[id].occupied)
            // current id is available
            break;
        id = (id+1) & (hmap->size-1);
    }

    if (i == hmap->size)
        // TODO: hashmap is full -> realloc
        return false;

    // Create the hashmap entry
    memcpy(&hmap->keys[id*hmap->key_max_size], key, key_size);
    hmap->entries[id].key_size = key_size;

    memcpy(&hmap->values[id*hmap->value_max_size], value, value_size);
    hmap->entries[id].value_size = value_size;
    
    hmap->entries[id].occupied = true;
    hmap->entries[id].deleted = false;

    hmap->num_entries++;
    
   return true;
}


bool
hashmap_update(HHASHMAP hHashMap, void * key, size_t key_size, void * value, size_t value_size)
{
    struct HashMap * hmap = (struct HashMap *) hHashMap;

    uint32_t hash = _hashmap_hash32(key, key_size);
    uint32_t id = hash & (hmap->size-1);

    size_t i = 0;
    for (; i<hmap->size; ++i) {
        if (hmap->entries[id].occupied && (memcmp(key, &hmap->keys[id*hmap->key_max_size], key_size) == 0))
            // key is already used
            break;
        if (!hmap->entries[id].occupied)
            // current id is available
            return false;
        id = (id+1) & (hmap->size-1);
    }

    if (i == hmap->size)
        // TODO: hashmap is full -> realloc + rehash
        return false;

    memcpy(&hmap->values[id*hmap->value_max_size], value, value_size);
    hmap->entries[id].value_size = value_size;
    
   return true;
}


void *
hashmap_get(HHASHMAP hHashMap, void * key, size_t key_size)
{
    struct HashMap * hmap = (struct HashMap *) hHashMap;

    uint32_t hash = _hashmap_hash32(key, key_size);
    uint32_t id = hash & (hmap->size-1);

    for (size_t i=0; i<hmap->size; ++i) {
        if (hmap->entries[id].occupied && (key_size == hmap->entries[id].key_size) && (memcmp(&hmap->keys[id*hmap->key_max_size], key, key_size) == 0)) {
            return &hmap->values[id*hmap->value_max_size];
        } else if (hmap->entries[id].deleted) {
            id = (id+1) & (hmap->size-1);
            continue;
        } else if (!hmap->entries[id].occupied) {
            // entry not deleted and not occupied
            break;
        }
        // entry is occupied but didn't match
        id = (id+1) & (hmap->size-1);
    }

    return NULL;
}


bool
hashmap_delete(HHASHMAP hHashMap, void * key, size_t key_size)
{
    struct HashMap * hmap = (struct HashMap *) hHashMap;

    uint32_t hash = _hashmap_hash32(key, key_size);
    uint32_t id = hash & (hmap->size-1);

    for (size_t i=0; i<hmap->size; ++i) {
        if (hmap->entries[id].occupied && (key_size == hmap->entries[id].key_size) && (memcmp(&hmap->keys[id*hmap->key_max_size], key, key_size) == 0)) {
            hmap->entries[id].occupied = false;
            hmap->entries[id].deleted = true;
            memset(&hmap->values[id*hmap->value_max_size], 0, hmap->value_max_size);
            hmap->num_entries--;
            return true;
        } else if (hmap->entries[id].deleted) {
            id = (id+1) & (hmap->size-1);
            continue;
        } else if (!hmap->entries[id].occupied) {
            // entry not deleted and not occupied
            break;
        }
        // entry is occupied but didn't match
        id = (id+1) & (hmap->size-1);
    }

    return false;
}
