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
 * @brief function to check if the whole string conssist of numbers & '/' is allowed (special case )
 *
 * @param str String
 * @return _Bool
 */
_Bool isdate(uint8_t* str);
/**
 * @brief function to check if the whole string conssist of alphabetic characters  
 * 
 * @param str String
 * @return _Bool 
 */
_Bool isalphabetic(uint8_t* str);

/**
 * @brief simple implementaion on string copy function 
 * 
 * @param src  Source string 
 * @param des  Destination string (note there is no size check on destination make sure destination >= Source)
 */
void strcopy(uint8_t* src, uint8_t* des);
/**
 * @brief check if Destination string is the same with the source 
 * 
 * @param src 
 * @param des 
 * @return _Bool 
 */
_Bool isTheSame(uint8_t* src, uint8_t* des);

#endif // !_STRING_H_
