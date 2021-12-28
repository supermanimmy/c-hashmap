#include "tests.h"


#ifdef __GNUC__

MU_TEST(test_hashmap_deletei)
{
    HHASHMAP hMap = hashmap_create(2, 8, sizeof(int));

    MU_CHECK(true == hashmap_storei(hMap, "one", 1));
    MU_CHECK(NULL != hashmap_geti(hMap, "one"));
    MU_CHECK(true == hashmap_deletei(hMap, "one"));
    MU_CHECK(false == hashmap_deletei(hMap, "one")); // already deleted
    // hMap is now empty
    MU_CHECK(NULL == hashmap_geti(hMap, "one"));
    MU_CHECK(true == hashmap_is_empty(hMap));

    MU_CHECK(true == hashmap_storei(hMap, "two", 2));
    MU_CHECK(true == hashmap_storei(hMap, "three", 3));
    // hMap is now full
    MU_CHECK(false == hashmap_storei(hMap, "four", 4));

    MU_CHECK(true == hashmap_deletei(hMap, "three"));
    MU_CHECK(true == hashmap_storei(hMap, "four", 4));
    
    hashmap_free(hMap);
}

#endif


MU_TEST(test_hashmap_delete)
{
    HHASHMAP hMap = hashmap_create(2, 8, sizeof(int));

    int value;

    value = 1;
    MU_CHECK(true == hashmap_store(hMap, "one", sizeof("one"), &value, sizeof(value)));
    MU_CHECK(NULL != hashmap_get(hMap, "one", sizeof("one")));
    MU_CHECK(true == hashmap_delete(hMap, "one", sizeof("one")));
    MU_CHECK(false == hashmap_delete(hMap, "one", sizeof("one"))); // already deleted
    // hMap is now empty
    MU_CHECK(NULL == hashmap_get(hMap, "one", sizeof("one")));
    MU_CHECK(true == hashmap_is_empty(hMap));

    value = 2;
    MU_CHECK(true == hashmap_store(hMap, "two", sizeof("two"), &value, sizeof(value)));
    value = 3;
    MU_CHECK(true == hashmap_store(hMap, "three", sizeof("three"), &value, sizeof(value)));
    // hMap is now full
    value = 4;
    MU_CHECK(false == hashmap_store(hMap, "four", sizeof("four"), &value, sizeof(value)));

    MU_CHECK(true == hashmap_delete(hMap, "three", sizeof("three")));
    value = 4;
    MU_CHECK(true == hashmap_store(hMap, "four", sizeof("four"), &value, sizeof(value)));
    
    hashmap_free(hMap);
}
