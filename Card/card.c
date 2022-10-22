#include "card.h"


EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	/* card name buffer */
	uint8_t * namebuff =(uint8_t*) malloc(25);

	uint8_t lenght = 0; 

	/* if malloc sucssed */
	if (namebuff != NULL)
	{
		/* if in debug mode */
		#if debug>0
		/* get buffer from fixed array */
			uint8_t namesTest[4][28] = { "Youssef abdelmajeed A","shortname","name1234567mixed1234","123456789101112125847" };
			static uint8_t test_no = 0;
			strcopy(namesTest[test_no++], namebuff);
			test_no &= 0x3;
		#else
		/* get buffer from stdin */
			/* prompt the user */
			printf("please enter cardholder name: ");
			/* get name from stdin */
			gets(namebuff);
		#endif // debug==1
	
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
	strcopy(namebuff, cardData->cardHolderName);
	
	/* set the null char */
	cardData->cardHolderName[lenght] = '\0';

	/*free name buffer */
	free(namebuff);
	
	return CARD_OK;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	/* card expiry date buffer */
	uint8_t* datebuff = (uint8_t*)malloc(7);
	
	uint8_t lenght = 0;

	/* if malloc sucssed */
	if (datebuff != NULL)
	{	
		/* if in debug mode */
		#if debug>0
			/* get buffer from fixed array */
			uint8_t datesTest[4][7] = { "05/22","0522","05/y6","05/223" };
			static uint8_t test_no = 0;
			strcopy(datesTest[test_no++], datebuff);
			test_no &= 0x3;
		#else
			/* get buffer from stdin */
			/* prompt the user */
			printf("please enter card expiry date in the following format \"MM/YY\" : ");
			/* get date from stdin */
			gets(datebuff);
		#endif 

		/* get date lenght */
		lenght = len(datebuff);
	}

	/* check if the date is invalid */
	if (datebuff == NULL || lenght != 5 || (datebuff[2] != '/')|| !isdate(datebuff))
	{
		free(datebuff);
		return WRONG_EXP_DATE;
	}

	/* copy string from buffer to card */
	strcopy(datebuff, cardData->cardExpirationDate);

	/*free date buffer */
	free(datebuff);

	return CARD_OK;
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	/* card pan buffer */
	uint8_t* panbuff = (uint8_t*)malloc(21);

	uint8_t lenght = 0;

	/* if malloc sucssed */
	if (panbuff != NULL)
	{
	
		/* if in debug mode */
		#if debug>0
			/* get buffer from fixed array */
			uint8_t pansTest[4][20] = { "2769148304059987","666","2769148304059987a","2769148304059987125" };
			static uint8_t test_no = 0;
			strcopy(pansTest[test_no++], panbuff);
			test_no &= 0x3;
		#else
			/* get buffer from stdin */
			/* prompt the user */
			printf("please enter card pan number: ");
			/* get pan from stdin */
			gets(panbuff);
		#endif 


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
	strcopy(panbuff, cardData->primaryAccountNumber);
	
	/*free pan buffer */
	free(panbuff);

	return CARD_OK;

}
#if debug>0
void getCardHolderNameTest(void)
{
	ST_cardData_t testCard;
	const uint8_t lenght = 4;

	/* list of tests */
	uint8_t namesTest[4][28] = { "Youssef abdelmajeed A","shortname","name1234567mixed1234","123456789101112125847" };

	/* list of expected output */
	uint8_t expextedOutputs[4][11] = { "CARD_OK","WRONG_NAME","WRONG_NAME","WRONG_NAME" };

	printf("Tester Name: Youssef Abdelmajeed\n");
	printf("Function Name: getCardHolderName\n");
	for (uint8_t i = 0; i < lenght; i++)
	{
		printf("Test Case %d: %s \n", i + 1, namesTest[i]);
		printf("Expected Result: %s \n", expextedOutputs[i]);
		printf("Actual Result: %s \n", getCardHolderName(&testCard) == CARD_OK ? "CARD_OK" : "WRONG_NAME");
	}
}

void getCardExpiryDateTest(void)
{
	ST_cardData_t testCard;
	const uint8_t lenght = 4;

	/* list of tests */
	uint8_t datesTest[4][7] = { "05/22","0522","05/y6","05/223" };

	/* list of expected output */
	uint8_t expextedOutputs[4][15] = { "CARD_OK","WRONG_EXP_DATE","WRONG_EXP_DATE","WRONG_EXP_DATE" };

	printf("Tester Name: Youssef Abdelmajeed\n");
	printf("Function Name: getCardExpiryDate\n");
	for (uint8_t i = 0; i < lenght; i++)
	{
		printf("Test Case %d: %s \n", i + 1, datesTest[i]);
		printf("Expected Result: %s \n", expextedOutputs[i]);
		printf("Actual Result: %s \n", getCardExpiryDate(&testCard) == CARD_OK ? "CARD_OK" : "WRONG_EXP_DATE");
	}
}

void getCardPANTest(void)
{
	ST_cardData_t testCard;
	const uint8_t lenght = 4;

	/* list of tests */
	uint8_t pansTest[4][20] = { "2769148304059987","666","2769148304059987a","2769148304059987125" };

	/* list of expected output */
	uint8_t expextedOutputs[4][10] = { "CARD_OK","WRONG_PAN","WRONG_PAN","WRONG_PAN" };

	printf("Tester Name: Youssef Abdelmajeed\n");
	printf("Function Name: getCardPAN\n");
	for (uint8_t i = 0; i < lenght; i++)
	{
		printf("Test Case %d: %s \n", i + 1, pansTest[i]);
		printf("Expected Result: %s \n", expextedOutputs[i]);
		printf("Actual Result: %s \n", getCardPAN(&testCard) == CARD_OK ? "CARD_OK" : "WRONG_PAN");
	}
}
#endif