#include "tests.h"


MU_TEST(test_hashmap_empty)
{
    HHASHMAP hMap = hashmap_create(2, 8, sizeof(int));

    int value = 2;
    MU_CHECK(true == hashmap_store(hMap, "two", sizeof("two"), &value, sizeof(value)));
    MU_CHECK(false == hashmap_is_empty(hMap));
    MU_CHECK(2 == *(int *)hashmap_get(hMap, "two", sizeof("two")));

    MU_CHECK(NULL == hashmap_get(hMap, "one", sizeof("one")));

    MU_CHECK(true == hashmap_delete(hMap, "two", sizeof("two")));
    MU_CHECK(true == hashmap_is_empty(hMap));
    
    hashmap_free(hMap);
}
