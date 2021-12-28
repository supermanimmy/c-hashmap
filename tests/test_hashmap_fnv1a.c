#include "tests.h"


/* https://tools.ietf.org/html/draft-eastlake-fnv-03#page-15

Appendix C: A Few Test Vectors

   Below are a few test vectors in the form of ASCII strings and their
   FNV32 and FNV64 hashes using the FNV-1a algorithm.

   Strings without null (zero byte) termination:

   String       FNV32       FNV64
    ""        0x811c9dc5  0xcbf29ce484222325
    "a"       0xe40c292c  0xaf63dc4c8601ec8c
    "foobar"  0xbf9cf968  0x85944171f73967e8

   Strings including null (zero byte) termination:

   String       FNV32       FNV64
    ""        0x050c5d1f  0xaf63bd4c8601b7df
    "a"       0x2b24d044  0x089be207b544f1e4
    "foobar"  0x0c1c9eb8  0x34531ca7168b8f38

*/

MU_TEST(test_hashmap_fnv1a_32)
{
    /* without null byte */
    MU_CHECK(0x811c9dc5 == _hashmap_hash32("", strlen("")));
    MU_CHECK(0xe40c292c == _hashmap_hash32("a", strlen("a")));
    MU_CHECK(0xbf9cf968 == _hashmap_hash32("foobar", strlen("foobar")));

    /* including null byte */
    MU_CHECK(0x050c5d1f == _hashmap_hash32("", sizeof("")));
    MU_CHECK(0x2b24d044 == _hashmap_hash32("a", sizeof("a")));
    MU_CHECK(0x0c1c9eb8 == _hashmap_hash32("foobar", sizeof("foobar")));
}


MU_TEST(test_hashmap_fnv1a_64)
{
    /* without null byte */
    MU_CHECK(0xcbf29ce484222325 == _hashmap_hash64("", strlen("")));
    MU_CHECK(0xaf63dc4c8601ec8c == _hashmap_hash64("a", strlen("a")));
    MU_CHECK(0x85944171f73967e8 == _hashmap_hash64("foobar", strlen("foobar")));

    /* including null byte */
    MU_CHECK(0xaf63bd4c8601b7df == _hashmap_hash64("", sizeof("")));
    MU_CHECK(0x089be207b544f1e4 == _hashmap_hash64("a", sizeof("a")));
    MU_CHECK(0x34531ca7168b8f38 == _hashmap_hash64("foobar", sizeof("foobar")));
}
