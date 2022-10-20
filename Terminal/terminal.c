#include "terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	/* allocate memory for the Transaction Date Buffer */
	uint8_t* TransactionDatebuff = (uint8_t*)malloc(11);

	uint8_t lenght = 0;

	/* if malloc sucssed */
	if (TransactionDatebuff != NULL)
	{
		/* prompt the user */
		printf("please enter Transaction Date in the following format \"DD/MM/YYYY\" : ");

		/* get date from stdin */
		gets(TransactionDatebuff);

		/* get date lenght */
		lenght = len(TransactionDatebuff);
	}

	/* check if the date is invalid */
	if (TransactionDatebuff == NULL || lenght != 10 || (TransactionDatebuff[2] != '/') || (TransactionDatebuff[5] != '/') || !isnum(TransactionDatebuff))
	{
		free(TransactionDatebuff);
		return WRONG_DATE;
	}
	
	/* copy string from buffer to card */
	for (uint8_t i = 0; i < lenght; i++)
	{
		termData->transactionDate[i] = TransactionDatebuff[i];
	}

	/* set the null char */
	termData->transactionDate[lenght] = '\0';

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
		else if  (termData->transactionDate[9] == cardData->cardExpirationDate[4] && termData->transactionDate[8] == cardData->cardExpirationDate[3])
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
	/* prompt the user */
	printf("please enter Transaction Amount : ");
	scanf_s("%f", &amount);
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
			tmp = (i % 2 == 0) ? digitbuff[i] * 2 : digitbuff[i] * 1;

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