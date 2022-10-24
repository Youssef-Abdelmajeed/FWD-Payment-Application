#include "string.h"

uint8_t len(uint8_t* str)
{
	uint8_t lenght = 0;
	/*Transverse throght the arr of string to get it's lenght*/
	while (str[lenght] != '\0')
	{
		lenght++;
	}
	return lenght;
}

_Bool isnum(uint8_t* str)
{
	_Bool isnum = 1;
	while ((* str ) != '\0' && isnum)
	{
		/* numbers in ascii table is between DEC(48) and DEC(57) */
		isnum = ((* str) >= 48 && (* str) <= 57)? 1 : 0;
		str++;
	}
	return isnum;
}
_Bool isdate(uint8_t* str)
{
	_Bool isnum = 1;
	while ((*str) != '\0' && isnum)
	{
		/* numbers in ascii table is between DEC(48) and DEC(57) */
		isnum = ((*str) >= 48 && (*str) <= 57 || (*str) == '/') ? 1 : 0;
		str++;
	}
	return isnum;
}
_Bool isalphabetic(uint8_t* str)
{
	_Bool isalpha = 1;
	while ((* str) != '\0' && isalpha)
	{
		/* alphabetic charaters in ascii table is between DEC(65) - DEC(90) (uppercase) or DEC(97) - DEC(122) (lowercase) */
		isalpha = (((* str) >= 65 && (* str) <= 90) || ((* str) >= 97 && (* str) <= 122) || ((* str) == ' '))? 1 : 0;
		str++;
	}
	return isalpha;
}
void strcopy(uint8_t* src, uint8_t* des)
{
	uint8_t lenght = len(src);
	if (lenght > 0)
	{
		/*copy each char form src to des*/
		for (uint8_t i = 0; i < lenght; i++)
		{
			des[i] = src[i];
		}
		/* set the null char */
		des[lenght] = '\0';
	}
}
_Bool isTheSame(uint8_t* src, uint8_t* des)
{
	/* if the two strings are not equal */
	if (len(src) != len(des)) return 0; 

	uint8_t lenght = len(des);

	
	/* check each character */
	for (uint8_t i = 0; i < lenght; i++)
	{
		/* if there a diffrent character */
		if (src[i] != des[i])
		{
			return 0; 
			
		}
	}
	return 1;
}