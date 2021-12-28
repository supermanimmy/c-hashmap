#include "tests.h"


MU_TEST(test_hashmap_clear)
{
    HHASHMAP hMap = hashmap_create(2, 8, sizeof(int));

    hashmap_clear(hMap);
    MU_CHECK(true == hashmap_is_empty(hMap));

    int value = 1;
    MU_CHECK(true == hashmap_store(hMap, "one", sizeof("one"), &value, sizeof(value)));

    MU_CHECK(false == hashmap_is_empty(hMap));
    hashmap_clear(hMap);
    MU_CHECK(true == hashmap_is_empty(hMap));
    
    hashmap_free(hMap);
}
