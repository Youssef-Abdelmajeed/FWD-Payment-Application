#include "server.h"

/* server-side accounts' database */
ST_accountsDB_t accountsDB[255] = 
{
	{.balance = 1000.0,.state = BLOCKED,.primaryAccountNumber = "2769148304059987" },
	{.balance = 4040, .state = RUNNING,.primaryAccountNumber = "26789819223902201" },
	{.balance = 96204, .state = BLOCKED,.primaryAccountNumber = "25558569495666551" },
	{.balance = 222,   .state = RUNNING,.primaryAccountNumber = "35854584549948483" },
	{.balance = 6666,  .state = BLOCKED,.primaryAccountNumber = "52565959245959593" }
};

/* server-side transactions' database*/
ST_transaction_t transactionData[255] = { {0} }; /* intitializing the array with zeros */

static uint32_t sequance_no = 0;
EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	ST_accountsDB_t accountref;
	EN_transState_t state = INTERNAL_SERVER_ERROR;
	
	/* if account is found */
	if (isValidAccount(&transData->cardHolderData, &accountref) == SERVER_OK)
	{
		/* if the amount is available */
		if (isAmountAvailable(&transData->terminalData,&accountref)!=LOW_BALANCE) 
		{
			/* the account is not blocked */ 
			if (isBlockedAccount(&accountref) == SERVER_OK)
			{
					/* update the balance */
					accountref.balance -= transData->terminalData.transAmount;
					state = APPROVED;
			}
			else
			{
				state = DECLINED_STOLEN_CARD;
			}
		}
		else
		{
			state =  DECLINED_INSUFFECIENT_FUND;
		}

	}
	else
	{
		state = FRAUD_CARD;
	}
	/* update trasdate */
	transData->transState = state;
	/* if trasaction is saved */
	if(saveTransaction(transData)==SERVER_OK)
	{
		return state;
	}
	else
	{
		return INTERNAL_SERVER_ERROR;
	}
}
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
	/* linear search for the account PAN in accounts database */
	for (uint8_t i = 0; i < 255; i++)
	{
		/* if the account PAN is found */
		if (isTheSame(accountsDB[i].primaryAccountNumber,cardData->primaryAccountNumber))
		{
			/* get the account address in the database */
			*accountRefrence= accountsDB[i]; 
			return SERVER_OK;
		}
	}
	/* in case if the search fails set account Refrence to NULL */
	accountRefrence = NULL; 
	return ACCOUNT_NOT_FOUND;
}
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
	/* check account state */
	if (accountRefrence->state == BLOCKED)
	{
		return BLOCKED_ACCOUNT;
	}
	/* in case if not blocked */
	return SERVER_OK;
}
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence)
{
	if (accountRefrence == NULL || termData == NULL) return ACCOUNT_NOT_FOUND;
	else
	{
		/* if the transtion amount is bigger than the balance in the account */
		if (termData->transAmount > accountRefrence->balance)
		{
			return LOW_BALANCE;
		}
	}
	return SERVER_OK;
}
EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	/* database limit 255 so after the seq exceed that will start from zero and overwrite the data */
	uint8_t Transaction_no = (sequance_no & 255); 
	ST_transaction_t* ptr = &transactionData[Transaction_no]; 

	/* copy all data to the database */
	ptr->cardHolderData = transData->cardHolderData;
	ptr->terminalData = transData->terminalData;
	ptr->transState = transData->transState; 
	ptr->transactionSequenceNumber = sequance_no;

	/*increment sequance number */
	sequance_no++;

	listSavedTransactions(); // this function isn't in the right place  
	
	/* Assuming that the connection between the terminal and server is always connected */
	return SERVER_OK;
}

void listSavedTransactions(void)
{
	uint8_t no = sequance_no & 255; 
	char state[5][27] = { "APPROVED", "DECLINED_INSUFFECIENT_FUND", "DECLINED_STOLEN_CARD", "FRAUD_CARD", "INTERNAL_SERVER_ERROR" };
	for (uint8_t i = 0; i<no ; i++)
	{
		ST_transaction_t* ptr = &transactionData[i];
		printf("#########################\n");
		printf("Transaction Sequence Number : %lld \n", ptr->transactionSequenceNumber); 
		printf("Transaction Date : %s \n", ptr->terminalData.transactionDate); 
		printf("Transaction Amount : %.4f\n", ptr->terminalData.transAmount);
		uint8_t stindex = ptr->transState; 
		printf("Transaction State : %s \n" ,state[stindex]); 
		printf("Terminal Max Amount : %.4f\n", ptr->terminalData.maxTransAmount); 
		printf("Cardholder Name : %s\n", ptr->cardHolderData.cardHolderName); 
		printf("PAN: %s\n", ptr->cardHolderData.primaryAccountNumber); 
		printf("Card Expiration Date : %s \n", ptr->cardHolderData.cardExpirationDate); 
		printf("#########################\n");
	}
}

/* test functions implementaion */
#if server_debug > 0 

void recieveTransactionDataTest(void)
{
	/* crate dummy cards */
	ST_cardData_t card[2] =
	{
		{.cardExpirationDate = "05/22",.cardHolderName = "youssef abdelmajeed a",.primaryAccountNumber = "26789819223902201"},
		{.cardExpirationDate = "06/22",.cardHolderName = "Mohamed Ahmed Moh",.primaryAccountNumber = "52565959245959593"}
	};
	/* create dummy terminal */
	ST_terminalData_t terminal[2] =
	{
		{.maxTransAmount = 1000,.transactionDate = "05/02/2022",.transAmount = 50},
		{.maxTransAmount = 1000,.transactionDate = "05/03/2022",.transAmount = 30},

	};
	/* dummy states */
	EN_transState_t state[2] = { APPROVED,DECLINED_STOLEN_CARD };

	printf("Tester Name: Youssef Abdelmajeed\n");
	printf("Functions Name:  recieveTransactionData \n");

	ST_transaction_t trans1 = { .cardHolderData = card[0],.terminalData = terminal[0],.transactionSequenceNumber = 1,.transState = state[0] };
	printf("Test Case 1: \n");
	recieveTransactionData(&trans1);

	ST_transaction_t trans2 = { .cardHolderData = card[1],.terminalData = terminal[1],.transactionSequenceNumber = 2,.transState = state[1] };
	printf("Test Case 2: \n");
	recieveTransactionData(&trans2);
}

void isValidAccountTest(void)
{
	const uint8_t lenght = 5;

	ST_cardData_t DummyCards[5] =
	{
		{.primaryAccountNumber = "2559591304059987"}, /* not in the data base */
		{.primaryAccountNumber = "2769148304059987"},
		{.primaryAccountNumber = "62504584549948483" }, /* not in the data base */
		{.primaryAccountNumber = "35854584549948483" },
		{.primaryAccountNumber = "52565959245959593" }
	};

	ST_accountsDB_t* Dummyacount_ptr = NULL;
	
	/* list of expected output */
	uint8_t expextedOutputs[5][18] = { "ACCOUNT_NOT_FOUND","SERVER_OK","ACCOUNT_NOT_FOUND","SERVER_OK","SERVER_OK" };

	printf("Tester Name: Youssef Abdelmajeed\n");
	printf("Function Name: isValidAccount\n");
	for (uint8_t i = 0; i < lenght; i++)
	{

		printf("Test Case %d: %s \n", i + 1, DummyCards[i].primaryAccountNumber);
		printf("Expected Result: %s \n", expextedOutputs[i]);
		printf("Actual Result: %s \n", isValidAccount(&DummyCards[i], Dummyacount_ptr) == SERVER_OK ? "SERVER_OK" : "ACCOUNT_NOT_FOUND");
	}
}

void isBlockedAccountTest(void)
{
	const uint8_t lenght = 5;

	ST_accountsDB_t Dummyaccounts[5] = { {0} };
	
	/* get the first 5 elements in the accounts database */
	for (uint8_t i = 0; i < 5; i++)
	{
		Dummyaccounts[i] = accountsDB[i];
	}

	/* list of expected output */
	uint8_t expextedOutputs[5][10] = { "BLOCKED","SERVER_OK","BLOCKED","SERVER_OK","BLOCKED" };

	printf("Tester Name: Youssef Abdelmajeed\n");
	printf("Function Name: isBlockedAccount\n");
	for (uint8_t i = 0; i < lenght; i++)
	{

		printf("Test Case %d: \n", i + 1);
		printf("Expected Result: %s \n", expextedOutputs[i]);
		printf("Actual Result: %s \n", isBlockedAccount(&Dummyaccounts[i]) == SERVER_OK ? "SERVER_OK" : "BLOCKED");
	}
}

void isAmountAvailableTest(void)
{
	const uint8_t lenght = 4;
	ST_accountsDB_t DummyAccount = { .balance = 5000 };
	ST_terminalData_t Dummyterminals[5] = { {.transAmount=500},{.transAmount=5000},{.transAmount=10000},{.transAmount=0} };

	/* list of expected output */
	uint8_t expextedOutputs[4][12] = { "SERVER_OK","SERVER_OK","LOW_BALANCE","SERVER_OK"};
	printf("Tester Name: Youssef Abdelmajeed\n");
	printf("Function Name: isAmountAvailable\n");
	printf("the amount in the dummy account is 5000 \n"); 
	for (uint8_t i = 0; i < lenght; i++)
	{

		printf("Test Case %d: %.2f \n", i + 1,Dummyterminals[i].transAmount);
		printf("Expected Result: %s \n", expextedOutputs[i]);
		printf("Actual Result: %s \n", isAmountAvailable(&Dummyterminals[i],&DummyAccount) == SERVER_OK? "SERVER_OK" : "LOW_BALANCE");
	}
}

void saveTransactionTest(void)
{
	/* crate dummy cards */
	ST_cardData_t card[2] =
	{
		{.cardExpirationDate = "05/22",.cardHolderName = "youssef abdelmajeed a",.primaryAccountNumber = "26789819223902201"},
		{.cardExpirationDate = "06/22",.cardHolderName = "Mohamed Ahmed Moh",.primaryAccountNumber = "52565959245959593"}
	};
	/* create dummy terminal */
	ST_terminalData_t terminal[2] =
	{
		{.maxTransAmount = 1000,.transactionDate = "05/02/2022",.transAmount = 50},
		{.maxTransAmount = 1000,.transactionDate = "05/03/2022",.transAmount = 30},

	};
	/* dummy states */
	EN_transState_t state[2] = { APPROVED,DECLINED_STOLEN_CARD };

	printf("Tester Name: Youssef Abdelmajeed\n");
	printf("Functions Name: saveTransactionTest & listSavedTransactions\n");

	ST_transaction_t trans1 = { .cardHolderData = card[0],.terminalData = terminal[0],.transactionSequenceNumber = 1,.transState = state[0] };
	printf("Test Case 1: \n");
	saveTransaction(&trans1);

	ST_transaction_t trans2 = { .cardHolderData = card[1],.terminalData = terminal[1],.transactionSequenceNumber = 2,.transState = state[1] };
	printf("Test Case 2: \n");
	saveTransaction(&trans2);
}

void listSavedTransactionsTest(void)
{
	/* save trasaction & listSavedTransactions is validated using the same function */
	saveTransactionTest(); 
}
#endif /* server debug */