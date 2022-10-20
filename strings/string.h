#ifndef _STRING_H_
#define  _STRING_H_
/* 8 bit unsigned integer */
typedef unsigned char uint8_t;
/**
 * @brief get the lenght of a given string
 * 
 * @param str String
 * @return uint8_t lenght of the string (null char not included)
 */
uint8_t len(uint8_t* str);
/**
 * @brief function to check if the whole string conssist of numbers 
 * 
 * @param str String
 * @return _Bool  
 */
_Bool isnum(uint8_t* str);
/**
 * @brief function to check if the whole string conssist of alphabetic characters  '/' is allowed (special case )
 * 
 * @param str String
 * @return _Bool 
 */
_Bool isalphabetic(uint8_t* str);

#endif // !_STRING_H_
