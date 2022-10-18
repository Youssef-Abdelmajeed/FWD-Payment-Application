#include "card.h"

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	/* card name buffer */
	unsigned char* namebuff =(unsigned char *) malloc(25);
	
	uint8_t lenght = 0; 
	_Bool isalpha = 1;
	/* if malloc sucssed */
	if (namebuff != NULL)
	{
		/* prompt the user */
		printf("please enter cardholder name: ");
		
		/* get name from stdin */
		gets(namebuff);
		

		/* get name lenght */
		while (namebuff[lenght] != '\0')
		{
			lenght++;
			/* alphabetic charaters in ascii table is between DEC(65) - DEC(90) (uppercase) or DEC(97) - DEC(122) (lowercase) */
			isalpha = ((namebuff[lenght] >= 65 && namebuff[lenght] <= 90) || (namebuff[lenght] >= 97 && namebuff[lenght] <= 122)||(namebuff[lenght]==' ')) ? 1 : 0;
		
			/* if the char is not alphabetic break of the loop */
			if (!isalpha)
			{
				break;
			}
		}
	
	}

	/*check if the name is invalid*/
	if (namebuff == NULL || lenght < 20 || lenght >24 || !isalpha)
	{
		free(namebuff);
		return WRONG_NAME;
	}
	for (uint8_t i = 0; i < lenght; i++)
	{
		
		cardData->cardHolderName[i] = namebuff[i];
	}

	/* set the null char */
	cardData->cardHolderName[lenght] = '\0';

	/*free name buffer */
	free(namebuff);
	
	return   CARD_OK;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	/* card expiry date buffer */
	unsigned char* datebuff = (unsigned char*)malloc(6);
	
	uint8_t lenght = 0;
	_Bool isalpha = 1;

	/* if malloc sucssed */
	if (datebuff != NULL)
	{
		/* prompt the user */
		printf("please enter card expiry date in the following format \"MM/YY\" : ");
		
		/* get date from stdin */
		gets(datebuff);
		
		/* get date lenght */
		while (datebuff[lenght] != '\0')
		{
			/* index 2 stores '/' */
			if (lenght != 2)
			{
				/* numbers in ascii table is between DEC(48) and DEC(57) */
				isalpha = (datebuff[lenght] >= 48 && datebuff[lenght] <= 57) ? 1 : 0;

				/* if the char is not alphanum break of the loop */
				if (!isalpha)
				{
					break;
				}
			}
			lenght++;
		}
	}
	
	/* check if the date is invalid */
	if (datebuff == NULL || lenght != 5 || (datebuff[2] != '/')|| !isalpha)
	{
		free(datebuff);
		return WRONG_EXP_DATE;
	}
	for (uint8_t i = 0 ;i < 5; i++)
	{
		cardData->cardExpirationDate[i] = datebuff[i];
	}

	/* set the null char */
	cardData->cardExpirationDate[lenght] = '\0';

	/*free date buffer */
	free(datebuff);

	return CARD_OK;
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	/* card pan buffer */
	unsigned char* panbuff = (unsigned char*)malloc(20);

	uint8_t lenght = 0;

	_Bool isalpha = 1;
	/* if malloc sucssed */
	if (panbuff != NULL)
	{
		/* prompt the user */
		printf("please enter card pan number: ");

		/* get pan from stdin */
		gets(panbuff);

		
		/* get pan lenght */
		while(panbuff[lenght] != '\0')
		{
			/* numbers in ascii table is between DEC(48) and DEC(57) */
			isalpha = (panbuff[lenght] >= 48 && panbuff[lenght] <= 57) ? 1 : 0;
			
			/* if the char is not alphanum break of the loop */
			if (!isalpha)
			{
				break;
			}

			lenght++;
		}
	}
	/* check if the pan is invalid */
	if (panbuff == NULL || lenght < 16 || lenght >19 || !isalpha)
	{
		free(panbuff);
		return WRONG_PAN;
	}
	for (uint8_t i = 0; i < lenght; i++)
	{

		cardData->primaryAccountNumber[i] = panbuff[i];
	}
	/* set the null char */
	cardData->primaryAccountNumber[lenght] = '\0';

	/*free pan buffer */
	free(panbuff);

	return CARD_OK;

}

