#ifndef FUNCTIONS_H
#define FUNCTIONS_H

///
/// @brief      { return the length of the given null-terminated string }
///
/// @param[in]  str   pointer to the null-terminated byte string to be examined
///
/// @return     { return the number of characters in str 
///               up to and not including the first null character }
///
unsigned long long mystrlen(const char* str);

///
/// @brief      { compares two null-terminated strings lexicographically }
///
/// @param[in]  lhs   pointer to the left null-terminated byte string to compare
/// @param[in]  rhs   pointer to the right null-terminated byte strings to compare
///
/// @return     { -1 if lhs appears before rhs in lexicographic order
/// 			   0 if lhs and rhs are the same string
/// 			   1 if lhs appears after rhs in lexicographic order }
///
int mystrcmp(const char *lhs, const char *rhs);

///
/// @brief      { function_description }
///
/// @param[in]  str     pointer to the null-terminated byte string to examine
/// @param[in]  substr  pointer to the null-terminated byte string to search for
///
/// @return     { description_of_the_return_value }
///
char *mystrstr(const char* str, const char* substr);

///
/// @brief      { Counts the number of ones in the binary representation of a 
///               number. }
///
/// @param[in]  num   The number
///
/// @return     Number of ones.
///
unsigned int count_ones(int num);

///
/// @brief      { Convert a number to an array of bits. }
///
/// @param[in]  num   The number to be converted
/// @param      arr   The destination array
/// @param[in]  sz    The size of arr
///
/// @return     { Function does not return a value, instead, it constructs the array
///             in arr, }
///
void int_to_arr(unsigned int num, int arr[], unsigned int sz);

#endif //FUNCTIONS_H