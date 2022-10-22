#include "Card\card.h"
#include "Terminal\terminal.h"
#include "Server\server.h"
#include "Application\app.h"

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

