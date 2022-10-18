#include "Card\card.h"
#include "Terminal\terminal.h"
#include "Server\server.h"
//#include "Application\app.h"

int main(int argc ,char * argv[])
{
	ST_cardData_t card1; 
	
	if (getCardHolderName(&card1) != WRONG_NAME)
	{
		printf("%s \n", card1.cardHolderName);
	}
	else
	{
		printf("Wrong Name\n");
	}

	if (getCardExpiryDate(&card1) != WRONG_EXP_DATE)
	{
		printf("%s \n", card1.cardExpirationDate);
	}
	else
	{
		printf("Wrong Date\n");
	}

	if (getCardPAN(&card1) != WRONG_PAN)
	{
		printf("%s \n", card1.primaryAccountNumber);
	}
	else
	{
		printf("Wrong Pan\n");
	}
	
	
	return 0;
} 