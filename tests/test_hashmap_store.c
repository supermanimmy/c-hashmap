#include "tests.h"


#ifdef __GNUC__
MU_TEST(test_hashmap_storei)
{
    HHASHMAP hMap = hashmap_create(2, 8, sizeof(int));

    MU_CHECK(true == hashmap_storei(hMap, "one", 1));
    MU_CHECK(false == hashmap_storei(hMap, "one", 1)); // key already exists
    MU_CHECK(true == hashmap_storei(hMap, "two", 2));
    
    MU_CHECK(1 == *(int *)hashmap_geti(hMap, "one"));
    MU_CHECK(2 == *(int *)hashmap_geti(hMap, "two"));

    hashmap_free(hMap);
}


MU_TEST(test_hashmap_key_values)
{
    HHASHMAP hMap = hashmap_create(5, 8, 20);

    MU_CHECK(true == hashmap_storei(hMap, "1", "str_1"));
    MU_CHECK(true == hashmap_storei(hMap, 1, "int_1"));
    MU_CHECK(true == hashmap_storei(hMap, 1.0f, "float_1"));
    MU_CHECK(true == hashmap_storei(hMap, 1.0, "double_1"));
    MU_CHECK(true == hashmap_storei(hMap, "Hello", 22.22f));

    char * value_str = hashmap_geti(hMap, "1");
    MU_CHECK(0 == strncmp(value_str, "str_1", sizeof("str_1")));

    value_str = hashmap_geti(hMap, 1);
    MU_CHECK(0 == strncmp(value_str, "int_1", sizeof("int_1")));

    value_str = hashmap_geti(hMap, 1.0f);
    MU_CHECK(0 == strncmp(value_str, "float_1", sizeof("float_1")));

    value_str = hashmap_geti(hMap, 1.0);
    MU_CHECK(0 == strncmp(value_str, "double_1", sizeof("double_1")));

    float * value_float = hashmap_geti(hMap, "Hello");
    MU_CHECK(*value_float == 22.22f);

    hashmap_free(hMap);
}
#endif


MU_TEST(test_hashmap_store)
{
    HHASHMAP hMap = hashmap_create(2, 8, sizeof(int));

    int value;

    value = 1;
    MU_CHECK(true == hashmap_store(hMap, "one", sizeof("one"), &value, sizeof(value)));
    MU_CHECK(false == hashmap_store(hMap, "one", sizeof("one"), &value, sizeof(value))); // key already exists

    value = 2;
    MU_CHECK(true == hashmap_store(hMap, "two", sizeof("two"), &value, sizeof(value)));
    
    MU_CHECK(1 == *(int *)hashmap_get(hMap, "one", sizeof("one")));
    MU_CHECK(2 == *(int *)hashmap_get(hMap, "two", sizeof("two")));

    hashmap_free(hMap);
}
