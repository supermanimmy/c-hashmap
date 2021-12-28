#include "tests.h"


MU_TEST(test_hashmap_size)
{
    HHASHMAP hMap = hashmap_create(3, sizeof(int), sizeof(int));

    MU_CHECK(4 == hashmap_capacity(hMap)); // power of 2
    MU_CHECK(0 == hashmap_size(hMap));

    int key, value;
    for (key = value = 0; key < 4; ++key) {
        MU_CHECK(true == hashmap_store(hMap, &key, sizeof(key), &value, sizeof(value)));
        MU_CHECK((key + 1) == (int)hashmap_size(hMap));
    }
    
    hashmap_free(hMap);
}
