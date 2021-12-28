#ifndef __TESTS_H__
#define __TESTS_H__


#include "minunit.h"
#include "../include/hashmap.h"


MU_TEST(test_hashmap_fnv1a_32);
MU_TEST(test_hashmap_fnv1a_64);

MU_TEST(test_hashmap_full);
MU_TEST(test_hashmap_empty);
MU_TEST(test_hashmap_clear);
MU_TEST(test_hashmap_size);

MU_TEST(test_hashmap_store);
MU_TEST(test_hashmap_delete);
MU_TEST(test_hashmap_update);

#ifdef __GNUC__
MU_TEST(test_hashmap_storei);
MU_TEST(test_hashmap_deletei);
MU_TEST(test_hashmap_updatei);
MU_TEST(test_hashmap_key_values);
#endif


#endif