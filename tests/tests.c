#include "tests.h"


int tests_run = 0;
int tests_failed = 0;
int tests_result = 0;


static void
ALL_TESTS()
{
    MU_RUN_TEST(test_hashmap_fnv1a_32);
    MU_RUN_TEST(test_hashmap_fnv1a_64);

    MU_RUN_TEST(test_hashmap_full);
    MU_RUN_TEST(test_hashmap_empty);
    MU_RUN_TEST(test_hashmap_clear);
    MU_RUN_TEST(test_hashmap_size);

    MU_RUN_TEST(test_hashmap_store);
    MU_RUN_TEST(test_hashmap_delete);
    MU_RUN_TEST(test_hashmap_update);

    #ifdef __GNUC__
    MU_RUN_TEST(test_hashmap_storei);
    MU_RUN_TEST(test_hashmap_deletei);
    MU_RUN_TEST(test_hashmap_updatei);
    MU_RUN_TEST(test_hashmap_key_values);
    #endif
}

int
main(void)
{
    ALL_TESTS();

    MU_STATS();

    return tests_failed != 0;
}
