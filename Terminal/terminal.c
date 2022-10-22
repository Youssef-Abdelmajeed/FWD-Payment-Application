#include "terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	/* allocate memory for the Transaction Date Buffer */
	uint8_t* TransactionDatebuff = (uint8_t*)malloc(12);

	uint8_t lenght = 0;

	/* if malloc sucssed */
	if (TransactionDatebuff != NULL)
	{
		/* if in debug mode */
		#if card_debug>0
			/* get buffer from fixed array */
				uint8_t TransactionDatesTest[4][12] = { "10/22/2022","10/b2/2022","055","10/22/20222" };
				static uint8_t test_no = 0;
				strcopy(TransactionDatesTest[test_no++], TransactionDatebuff);
				test_no &= 0x03;
		#else
			/* get buffer from stdin */
			/* prompt the user */
			printf("please enter Transaction Date in the following format \"DD/MM/YYYY\" : ");
			/* get date from stdin */
			gets(TransactionDatebuff);
		#endif 

		/* get date lenght */
		lenght = len(TransactionDatebuff);
	}

	/* check if the date is invalid */
	if (TransactionDatebuff == NULL || lenght != 10 || (TransactionDatebuff[2] != '/') || (TransactionDatebuff[5] != '/') || !isdate(TransactionDatebuff))
	{
		free(TransactionDatebuff);
		return WRONG_DATE;
	}
	
	/* copy string from buffer to card */
	strcopy(TransactionDatebuff, termData->transactionDate);

	/*free date buffer */
	free(TransactionDatebuff);

	return TERMINAL_OK;
	
}

EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
	/* check if the user enter the current millennium 20xx */
	if (termData->transactionDate[6] == '2' && termData->transactionDate[7] == '0')
	{
		
		/* in case if transaction year was lower than expiry year then the card is still valid */
		
		/* if transaction date decade was less than the card 's  */
		if (termData->transactionDate[8] < cardData->cardExpirationDate[3])
		{
			
			return TERMINAL_OK;	
		}
		/* if transaction date decade was bigger or equal than the card 's  */
		else if (termData->transactionDate[8] >= cardData->cardExpirationDate[3])
		{
			/* check year */
			if (termData->transactionDate[9] < cardData->cardExpirationDate[3])
			{
				return TERMINAL_OK;
			}
		}
		/* in case if transaction year was equal to the expiry year  */
		if  (termData->transactionDate[9] == cardData->cardExpirationDate[4] && termData->transactionDate[8] == cardData->cardExpirationDate[3])
		{
			/* check the expiration month */
			if (termData->transactionDate[4] <= cardData->cardExpirationDate[1] && termData->transactionDate[3] <= cardData->cardExpirationDate[0])
			{
				/* card is still vaild */
				return TERMINAL_OK;
			}
		}
	}
	/* if any case fail then the card would be expired */
	return EXPIRED_CARD;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	float amount = 0; 
	#if terminal_debug>0
	/* get amount from fixed array */
	static uint8_t test_no = 0;
	float amountsTest[] = { 550,4000.5,-10,0};
	amount = amountsTest[test_no++]; 
	test_no &= 0x03;
	#else
	/* prompt the user */
	printf("please enter Transaction Amount : ");
	scanf_s("%f", &amount);
	#endif
	if (amount <= 0) return INVALID_AMOUNT;
	termData->transAmount = amount;
	return TERMINAL_OK;
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	if (termData->transAmount > termData->maxTransAmount)
	{
		return EXCEED_MAX_AMOUNT;
	}
	return TERMINAL_OK;
}
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount)
{
	if (maxAmount <= 0) return INVALID_MAX_AMOUNT;
	termData->maxTransAmount = maxAmount;
	return TERMINAL_OK;
}
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData)
{
	uint8_t lenght = 0, tmp = 0, sum = 0;

	/* get number lenght */
	lenght = len(cardData->primaryAccountNumber);

	uint8_t* digitbuff = (uint8_t*)malloc(sizeof(uint8_t) * lenght);

	if (digitbuff != NULL)
	{
		/* convert from string to integer */
		for (uint8_t i = 0; i < lenght; i++)
		{

			digitbuff[i] = cardData->primaryAccountNumber[i] - 48;
		}
		for (uint8_t i = 0; i < lenght; i++)
		{
			/* even index mul by 2 and odd index mul by 1 */
			tmp = (i % 2 == 0) ? (digitbuff[i] * 2) : (digitbuff[i] * 1);

			/* if the number was two digit number multiply add the two digits*/
			tmp = (tmp > 9) ? (tmp / 10) + (tmp % 10) : tmp;
			/* sum the number mul by the wight */
			sum += tmp;
		}
	}

	free(digitbuff);

	/* if the first digit of the sum is zero then the number is valid  Luhn number */
	return (sum % 10 == 0)?TERMINAL_OK :INVALID_CARD;
}
#if terminal_debug>0

void getTransactionDateTest(void)
{
	ST_terminalData_t testTerminal ;
	const uint8_t lenght = 4;

	/* list of tests */
	uint8_t TransactionDatesTest[4][12] = { "10/22/2022","10/b2/2022","055","10/22/20222" };
	
	/* list of expected output */
	uint8_t expextedOutputs[4][12] = { "TERMINAL_OK","WRONG_DATE","WRONG_DATE","WRONG_DATE" };

	printf("Tester Name: Youssef Abdelmajeed\n");
	printf("Function Name: getTransactionDate\n");
	for (uint8_t i = 0; i < lenght; i++)
	{

		printf("Test Case %d: %s \n", i + 1, TransactionDatesTest[i]);
		printf("Expected Result: %s \n", expextedOutputs[i]);
		printf("Actual Result: %s \n", getCardExpiryDate(&testTerminal) == TERMINAL_OK ? "TERMINAL_OK" : "WRONG_DATE");
	}
}
void isCardExpiredTest(void)
{
	const uint8_t lenght = 5;

	ST_cardData_t DummyCard = { .cardExpirationDate = "05/22" };

	ST_terminalData_t Dummyterminals[5] = {
		{ .transactionDate = "31/04/2021" }, 
		{ .transactionDate = "31/06/2019" }, 
		{ .transactionDate = "31/05/2022" }, 
		{ .transactionDate = "31/05/2023" },
		{.transactionDate =	 "31/05/3023" }
		};
	
	/* list of expected output */
	uint8_t expextedOutputs[5][13] = { "TERMINAL_OK","TERMINAL_OK","TERMINAL_OK","EXPIRED_CARD","EXPIRED_CARD" };
	
	printf("Tester Name: Youssef Abdelmajeed\n");
	printf("Function Name: isCardExpired\n");
	for (uint8_t i = 0; i < lenght; i++)
	{

		printf("Test Case %d: %s \n", i + 1, Dummyterminals[i].transactionDate);
		printf("Expected Result: %s \n", expextedOutputs[i]);

		printf("Actual Result: %s \n", isCardExpired(&DummyCard,&Dummyterminals[i]) == TERMINAL_OK ? "TERMINAL_OK" : "EXPIRED_CARD");
	}
}
void getTransactionAmountTest(void)
{
	
	ST_terminalData_t testTerminal;
	const uint8_t lenght = 4;

	/* list of tests */
	float amountsTest[] = { 550,4000.5,-10,0};
	
	/* list of expected output */
	uint8_t expextedOutputs[4][15] = {"TERMINAL_OK","TERMINAL_OK","INVALID_AMOUNT","INVALID_AMOUNT" };

	printf("Tester Name: Youssef Abdelmajeed\n");
	printf("Function Name: getTransactionAmount\n");
	for (uint8_t i = 0; i < lenght; i++)
	{

		printf("Test Case %d: %f \n", i + 1, amountsTest[i]);
		printf("Expected Result: %s \n", expextedOutputs[i]);
		printf("Actual Result: %s \n", getTransactionAmount(&testTerminal) == TERMINAL_OK ? "TERMINAL_OK" : "INVALID_AMOUNT");
	}
}
void isBelowMaxAmountTest(void)
{
	const uint8_t lenght = 4;
	ST_terminalData_t DummyTerminals[] =
	{ 
		{.transAmount= 400   ,.maxTransAmount = 5050.5},
		{.transAmount= 5050.5,.maxTransAmount = 5050.5},
		{.transAmount= 5050.0,.maxTransAmount = 5050.5},
		{.transAmount= 6000  ,.maxTransAmount = 5050.5}
	};
	/* list of expected output */
	uint8_t expextedOutputs[4][18] = { "TERMINAL_OK","TERMINAL_OK","TERMINAL_OK","EXCEED_MAX_AMOUNT"};
	printf("Tester Name: Youssef Abdelmajeed\n");
	printf("Function Name: isBelowMaxAmountTest\n");
	for (uint8_t i = 0; i < lenght; i++)
	{
		printf("Test Case %d: %f \n", i + 1, DummyTerminals[i].transAmount);
		printf("Expected Result: %s \n", expextedOutputs[i]);
		printf("Actual Result: %s \n", isBelowMaxAmount(&DummyTerminals[i]) == TERMINAL_OK ? "TERMINAL_OK" : "EXCEED_MAX_AMOUNT");
	}
}
void setMaxAmountTest(void)
{
	const uint8_t lenght = 4;

	ST_terminalData_t testTerminal; 
	float maxamounts[] = { 5000,-5,5.5,0 };
	uint8_t expextedOutputs[4][19] = { "TERMINAL_OK","INVALID_MAX_AMOUNT","TERMINAL_OK","INVALID_MAX_AMOUNT" };
	printf("Tester Name: Youssef Abdelmajeed\n");
	printf("Function Name: setMaxAmount\n");
	for (uint8_t i = 0; i < lenght; i++)
	{
		printf("Test Case %d: %f \n", i + 1, maxamounts[i]);
		printf("Expected Result: %s \n", expextedOutputs[i]);
		printf("Actual Result: %s \n", setMaxAmount(&testTerminal,maxamounts[i]) == TERMINAL_OK ? "TERMINAL_OK" : "INVALID_MAX_AMOUNT");
	}
}
void isValidCardPANTest(void)
{
	const uint8_t lenght = 2;
	ST_cardData_t Dummycards[2] = 
	{ 
		{.primaryAccountNumber="2769148304059987"},
		{.primaryAccountNumber = "2769148304059983"} 
	};

	uint8_t expextedOutputs[2][13] = { "TERMINAL_OK","INVALID_CARD" };
	printf("Tester Name: Youssef Abdelmajeed\n");
	printf("Function Name: isValidCardPAN\n");
	for (uint8_t i = 0; i < lenght; i++)
	{
		printf("Test Case %d: %s \n", i + 1, Dummycards[i].primaryAccountNumber);
		printf("Expected Result: %s \n", expextedOutputs[i]);
		printf("Actual Result: %s \n", isValidCardPAN(&Dummycards[i]) == TERMINAL_OK ? "TERMINAL_OK" : "INVALID_CARD");
	}
}
#endif