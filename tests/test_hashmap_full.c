#include "tests.h"


MU_TEST(test_hashmap_full)
{
    HHASHMAP hMap = hashmap_create(2, 8, sizeof(int));

    int value;

    value = 1;
    MU_CHECK(true == hashmap_store(hMap, "one", sizeof("one"), &value, sizeof(value)));

    value = 2;
    MU_CHECK(true == hashmap_store(hMap, "two", sizeof("two"), &value, sizeof(value)));

    MU_CHECK(true == hashmap_is_full(hMap));

    value = 3;
    MU_CHECK(false == hashmap_store(hMap, "three", sizeof("three"), &value, sizeof(value)));

    hashmap_free(hMap);
}
