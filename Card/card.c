#include "card.h"

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	/* card name buffer */
	uint8_t * namebuff =(uint8_t*) malloc(25);

	uint8_t lenght = 0; 

	/* if malloc sucssed */
	if (namebuff != NULL)
	{
		/* prompt the user */
		printf("please enter cardholder name: ");

		/* get name from stdin */
		gets(namebuff);

		/* get name lenght */
		lenght = len(namebuff);
	}
	/*check if the name is valid */
	if (namebuff == NULL || (lenght < 20) || (lenght > 24) || !isalphabetic(namebuff))
	{
		free(namebuff); 
		return WRONG_NAME;
 	}

	/* copy string from buffer to card */
	for (uint8_t i = 0; i < lenght; i++)
	{
		cardData->cardHolderName[i] = namebuff[i];
	}

	/* set the null char */
	cardData->cardHolderName[lenght] = '\0';

	/*free name buffer */
	free(namebuff);
	
	return CARD_OK;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	/* card expiry date buffer */
	uint8_t* datebuff = (uint8_t*)malloc(6);
	
	uint8_t lenght = 0;

	/* if malloc sucssed */
	if (datebuff != NULL)
	{
		/* prompt the user */
		printf("please enter card expiry date in the following format \"MM/YY\" : ");
		
		/* get date from stdin */
		gets(datebuff);
		
		/* get date lenght */
		lenght = len(datebuff);
	}

	/* check if the date is invalid */
	if (datebuff == NULL || lenght != 5 || (datebuff[2] != '/')|| !isnum(datebuff))
	{
		free(datebuff);
		return WRONG_EXP_DATE;
	}

	/* copy string from buffer to card */
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
	uint8_t* panbuff = (uint8_t*)malloc(20);

	uint8_t lenght = 0;

	/* if malloc sucssed */
	if (panbuff != NULL)
	{
		/* prompt the user */
		printf("please enter card pan number: ");

		/* get pan from stdin */
		gets(panbuff);

		/* get pan lenght */
		lenght = len(panbuff);
	}
	/* check if the pan is invalid */
	if (panbuff == NULL || (lenght < 16) || (lenght > 19) || !isnum(panbuff))
	{
		free(panbuff);
		return WRONG_NAME;
	}

	/* copy string from buffer to card */
	for (uint8_t i = 0; i < lenght; i++)
	{
		/* in pan number we can't accept '/' that isnum() is accepting */
		if (panbuff[i] == '/')
		{
			free(panbuff);
			return WRONG_PAN;
		}
		cardData->primaryAccountNumber[i] = panbuff[i];
	}
	/* set the null char */
	cardData->primaryAccountNumber[lenght] = '\0';

	/*free pan buffer */
	free(panbuff);

	return CARD_OK;

}

