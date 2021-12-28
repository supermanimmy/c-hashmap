[![test](https://github.com/seird/c-hashmap/actions/workflows/test.yml/badge.svg)](https://github.com/seird/c-hashmap/actions) [![codecov](https://codecov.io/gh/seird/c-hashmap/branch/master/graph/badge.svg)](https://codecov.io/gh/seird/c-hashmap)


# C Hashmap

### Functions


- HHASHMAP hashmap_create(size_t size, size_t key_max_size, size_t value_max_size);
- void hashmap_free(HHASHMAP hHashMap);
- void hashmap_clear(HHASHMAP hHashMap);
- size_t hashmap_size(HHASHMAP hHashMap);
- size_t hashmap_capacity(HHASHMAP hHashMap);
- bool hashmap_is_full(HHASHMAP hHashMap);
- bool hashmap_is_empty(HHASHMAP hHashMap);
- bool hashmap_store(HHASHMAP hHashMap, void * key, size_t key_size, void * value, size_t value_size);
- bool hashmap_delete(HHASHMAP hHashMap, void * key, size_t key_size);
- bool hashmap_update(HHASHMAP hHashMap, void * key, size_t key_size, void * value, size_t value_size);
- void * hashmap_get(HHASHMAP hHashMap, void * key, size_t key_size);
