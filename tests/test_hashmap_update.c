#include "tests.h"


#ifdef __GNUC__

MU_TEST(test_hashmap_updatei)
{
    HHASHMAP hMap = hashmap_create(2, 8, sizeof(int));

    MU_CHECK(true == hashmap_storei(hMap, "one", 1));
    MU_CHECK(1 == *(int *)hashmap_geti(hMap, "one"));

    MU_CHECK(true == hashmap_updatei(hMap, "one", 2));
    MU_CHECK(2 == *(int *)hashmap_geti(hMap, "one"));

    MU_CHECK(false == hashmap_updatei(hMap, "three", 3)); // key doesn't exist

    MU_CHECK(true == hashmap_storei(hMap, "four", 4));
    MU_CHECK(false == hashmap_storei(hMap, "five", 5));
    MU_CHECK(false == hashmap_updatei(hMap, "five", 3));
    
    hashmap_free(hMap);
}

#endif


MU_TEST(test_hashmap_update)
{
    HHASHMAP hMap = hashmap_create(2, 8, sizeof(int));

    int value;

    value = 1;
    MU_CHECK(true == hashmap_store(hMap, "one", sizeof("one"), &value, sizeof(value)));
    MU_CHECK(1 == *(int *)hashmap_get(hMap, "one", sizeof("one")));

    value = 2;
    MU_CHECK(true == hashmap_update(hMap, "one", sizeof("one"), &value, sizeof(value)));
    MU_CHECK(2 == *(int *)hashmap_get(hMap, "one", sizeof("one")));

    value = 3;
    MU_CHECK(false == hashmap_update(hMap, "three", sizeof("three"), &value, sizeof(value)));

    value = 4;
    MU_CHECK(true == hashmap_store(hMap, "four", sizeof("four"), &value, sizeof(value)));

    value = 5;
    MU_CHECK(false == hashmap_update(hMap, "five", sizeof("five"), &value, sizeof(value)));

    value = 3;
    MU_CHECK(false == hashmap_update(hMap, "five", sizeof("five"), &value, sizeof(value)));
    
    hashmap_free(hMap);
}
