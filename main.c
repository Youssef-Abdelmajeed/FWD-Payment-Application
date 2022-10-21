#include "Card\card.h"
#include "Terminal\terminal.h"
#include "Server\server.h"
#include "Application\app.h"

void getCardHolderNameTest(void);
void getCardExpiryDateTest(void);
void getCardPANTest(void);


int main(int argc ,char * argv[])
{
	
	//ST_cardData_t card1 = { .cardExpirationDate = "05/22",.cardHolderName = "Youssef Abdelmajeeda",.primaryAccountNumber = "2769148304059987" };

	//ST_terminalData_t terminal1={.transactionDate="31/06/2021"};
	getCardHolderNameTest(); 
	printf("__________________\n");
	getCardExpiryDateTest();
	printf("__________________\n");
	getCardPANTest();
	return 0;
} 

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
		printf("Test Case %d: %s \n", i + 1,namesTest[i]);
		printf("Expected Result: %s \n", expextedOutputs[i]);
		printf("Actual Result: %s \n",getCardHolderName(&testCard) == CARD_OK ? "CARD_OK" : "WRONG_NAME");
	}
}

void getCardExpiryDateTest(void)
{
	ST_cardData_t testCard;
	const uint8_t lenght = 4;

	/* list of tests */
	uint8_t datesTest[4][7] = {"05/22","0522","05/y6","05/223" };

	/* list of expected output */
	uint8_t expextedOutputs[4][15] = { "CARD_OK","WRONG_EXP_DATE","WRONG_EXP_DATE","WRONG_EXP_DATE" };

	printf("Tester Name: Youssef Abdelmajeed\n");
	printf("Function Name: getCardExpiryDate\n");
	for (uint8_t i = 0; i < lenght; i++)
	{
		printf("Test Case %d: %s \n", i + 1,datesTest[i]);
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
		printf("Actual Result: %s \n", getCardPAN(& testCard) == CARD_OK ? "CARD_OK" : "WRONG_PAN");
	}
}