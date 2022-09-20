#include "functions.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

unsigned long long _mystrlen(const char *str);
int _mystrcmp(const char *lhs, const char *rhs);
char *_mystrstr(const char *str, const char *substr);
unsigned int _count_ones(const int num);
void _int_to_arr(unsigned int num, int arr[], unsigned int sz);

unsigned int randint;
int *arr8 = NULL;
int *arr32 = NULL;
int *exparr8 = NULL;
int *exparr32 = NULL;

/* The suite initialization function.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite1(void) {
  // Initialize random integer for tests
  srand(time(NULL));
  randint = (unsigned int)rand();

  // Initialize arrays on heap
  arr8 = (int *)malloc(sizeof(int) * 8);
  arr8 = memset((void *)arr8, 0, sizeof(int) * 8);
  arr32 = (int *)malloc(sizeof(int) * 32);
  arr32 = memset((void *)arr32, 0, sizeof(int) * 32);
  exparr8 = (int *)malloc(sizeof(int) * 8);
  exparr8 = memset((void *)exparr8, 0, sizeof(int) * 8);
  exparr32 = (int *)malloc(sizeof(int) * 32);
  exparr32 = memset((void *)exparr32, 0, sizeof(int) * 32);

  if (arr8 && arr32 && exparr8 && exparr32)
    return 0;
  else
    return 1;
}

/* The suite cleanup function.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite1(void) {
  free(arr8);
  free(arr32);
  return 0;
}

void testMYSTRLEN(void) {
  CU_ASSERT_EQUAL(mystrlen(""), _mystrlen(""));
  CU_ASSERT_EQUAL(mystrlen("strawberry"), _mystrlen("strawberry"));
  CU_ASSERT_EQUAL(mystrlen("caramel\0coconut"), _mystrlen("caramel\0coconut"));
}

void testMYSTRCMP(void) {
  CU_ASSERT_EQUAL(mystrcmp("binghamton", "albany"),
                  _mystrcmp("binghamton", "albany"));
  CU_ASSERT_EQUAL(mystrcmp("Albany", "Binghamton"),
                  _mystrcmp("Albany", "Binghamton"));
  CU_ASSERT_EQUAL(mystrcmp("binghamton", "binghamton"),
                  _mystrcmp("binghamton", "binghamton"));
  CU_ASSERT_EQUAL(mystrcmp("binghamton", "Binghamton"),
                  _mystrcmp("binghamton", "Binghamton"));
}

void testMYSTRSTR(void) {
  CU_ASSERT_PTR_EQUAL(mystrstr("binghamton", "bing"),
                      _mystrstr("binghamton", "bing"));
  CU_ASSERT_PTR_EQUAL(mystrstr("binghamton", "ham"),
                      _mystrstr("binghamton", "ham"));
  CU_ASSERT_PTR_EQUAL(mystrstr("bingbingbing", "ing"),
                      _mystrstr("bingbingbing", "ing"));
  CU_ASSERT_PTR_EQUAL(mystrstr("Binghamton", "bing"),
                      _mystrstr("Binghamton", "bing"));
}

void testCOUNTONES(void) {
  CU_ASSERT_EQUAL(count_ones(0), _count_ones(0));
  CU_ASSERT_EQUAL(count_ones(INT_MAX), _count_ones(INT_MAX));
  CU_ASSERT_EQUAL(count_ones(INT_MIN), _count_ones(INT_MIN));
  CU_ASSERT_EQUAL(count_ones(randint), _count_ones(randint));
}

void testINTOTARR(void) {
  int_to_arr(1, arr8, 8);
  _int_to_arr(1, exparr8, 8);
  CU_ASSERT(memcmp(arr8, exparr8, sizeof(int) * 8) == 0);
  int_to_arr(1, arr32, 32);
  _int_to_arr(1, exparr32, 32);
  CU_ASSERT(memcmp(arr8, exparr8, sizeof(int) * 32) == 0);
  int_to_arr(randint, arr32, 32);
  _int_to_arr(randint, exparr32, 32);
  CU_ASSERT(memcmp(arr32, exparr32, sizeof(int) * 32) == 0);
}

int main(int argc, char *argv[]) {
  CU_pSuite pSuite = NULL;

  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* add a suite to the registry */
  pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
  if (NULL == pSuite) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* add the tests to the suite */
  if ((NULL == CU_add_test(pSuite, "test of mystrlen", testMYSTRLEN)) ||
      (NULL == CU_add_test(pSuite, "test of mystrcmp", testMYSTRCMP)) ||
      (NULL == CU_add_test(pSuite, "test of mystrstr", testMYSTRCMP)) ||
      (NULL == CU_add_test(pSuite, "test of count_ones", testCOUNTONES)) ||
      (NULL == CU_add_test(pSuite, "test of int_to_arr", testINTOTARR))) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Run all tests using the CUnit Basic interface */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}