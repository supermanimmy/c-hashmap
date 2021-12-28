#ifndef __HASHMAP_H__
#define __HASHMAP_H__


#include <stdint.h>
#include <stdbool.h>


// A handle to a hashmap object
typedef void * HHASHMAP;


#if defined(_WIN32)
    // Microsoft attibutes to tell compiler that symbols are imported/exported from a .dll
    #if defined(BUILD_LIBTYPE_SHARED)
        #define CUAPI __declspec(dllexport)     // building as a Win32 shared library (.dll)
    #else
        #define CUAPI   // building or using as a static library
    #endif
#else
    #define CUAPI       // building as a static library (or Linux shared library)
#endif


/**
 * @brief Create a hashmap of size entries.
 * 
 * @param size 
 * @param key_max_size 
 * @param value_max_size 
 * @return HHASHMAP 
 */
CUAPI HHASHMAP hashmap_create(size_t size, size_t key_max_size, size_t value_max_size);

/** 
 * @brief Free a hashmap object.
 * 
 * @param hHashMap  
 */
CUAPI void hashmap_free(HHASHMAP hHashMap);

/**
 * @brief Remove all entries from a hashmap object.
 * 
 * @param hHashMap  
 */
CUAPI void hashmap_clear(HHASHMAP hHashMap);

/**
 * @brief Get the number of entries in a hashmap object.
 * 
 * @param hHashMap 
 * @return size_t 
 */
CUAPI size_t hashmap_size(HHASHMAP hHashMap);

/**
 * @brief Get the maximum capacity of a hashmap object.
 * 
 * @param hHashMap 
 * @return size_t 
 */
CUAPI size_t hashmap_capacity(HHASHMAP hHashMap);

/**
 * @brief Test if a hashmap is full.
 * 
 * @param hHashMap 
 * @return bool 
 */
CUAPI bool hashmap_is_full(HHASHMAP hHashMap);

/**
 * @brief Test if a hashmap is empty.
 * 
 * @param hHashMap 
 * @return bool 
 */
CUAPI bool hashmap_is_empty(HHASHMAP hHashMap);

/**
 * @brief Store a key-value pair in a hashmap object.
 * 
 * @param hHashMap 
 * @param key 
 * @param key_size 
 * @param value 
 * @param value_size 
 * @return bool 
 */
CUAPI bool hashmap_store(HHASHMAP hHashMap, void * key, size_t key_size, void * value, size_t value_size);

/**
 * @brief Delete a key-value pair from a hashmap object.
 * 
 * @param hHashMap 
 * @param key 
 * @param key_size 
 * @return bool 
 */
CUAPI bool hashmap_delete(HHASHMAP hHashMap, void * key, size_t key_size);

/**
 * @brief Update an existing key-value pair in a hashmap object.
 * 
 * @param hHashMap 
 * @param key 
 * @param key_size 
 * @param value 
 * @param value_size 
 * @return bool 
 */
CUAPI bool hashmap_update(HHASHMAP hHashMap, void * key, size_t key_size, void * value, size_t value_size);

/**
 * @brief Retreive a key-value pair in a hashmap object.
 * 
 * @param hHashMap 
 * @param key 
 * @param key_size 
 * @return void * 
 */
CUAPI void * hashmap_get(HHASHMAP hHashMap, void * key, size_t key_size);

/**
 * @brief 
 * 
 * @param in 
 * @param size 
 * @return uint32_t 
 */
CUAPI uint32_t _hashmap_hash32(char * in, size_t size);

/**
 * @brief 
 * 
 * @param in 
 * @param size 
 * @return uint64_t 
 */
CUAPI uint64_t _hashmap_hash64(char * in, size_t size);

/**
 * @brief 
 * 
 * @param hHashMap 
 * @return uint32_t 
 */
CUAPI uint32_t _hashmap_hash32_values(HHASHMAP hHashMap);

/**
 * @brief 
 * 
 * @param hHashMap 
 * @return uint32_t 
 */
CUAPI uint32_t _hashmap_hash32_keys(HHASHMAP hHashMap);


#ifdef __GNUC__
// https://gcc.gnu.org/onlinedocs/gcc/Statement-Exprs.html // __extension__

#define hashmap_storei(hHashMap, key, value) __extension__ ({\
    __typeof__(key) _key = key;\
    __typeof__(value) _value = value;\
    hashmap_store(hHashMap, &_key, sizeof(_key), &_value, sizeof(_value));\
})

#define hashmap_updatei(hHashMap, key, value) __extension__ ({\
    __typeof__(key) _key = key;\
    __typeof__(value) _value = value;\
    hashmap_update(hHashMap, &_key, sizeof(_key), &_value, sizeof(_value));\
})

#define hashmap_deletei(hHashMap, key) __extension__ ({\
    __typeof__(key) _key = key;\
    hashmap_delete(hHashMap, &_key, sizeof(_key));\
})

#define hashmap_geti(hHashMap, key) __extension__ ({\
    __typeof__(key) _key = key;\
    hashmap_get(hHashMap, &_key, sizeof(_key));\
})
#endif


#endif // __HASHMAP_H__
