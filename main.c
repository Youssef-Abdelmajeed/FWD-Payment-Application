#include "Card\card.h"
#include "Terminal\terminal.h"
#include "Server\server.h"
#include "Application\app.h"

int main(int argc ,char * argv[])
{
	ST_cardData_t card1; 
	
	getCardHolderName(&card1); 
	getCardExpiryDate(&card1);
	getCardPAN(&card1);

	printf("%s \n", card1.cardHolderName);
	printf("%s \n", card1.cardExpirationDate);
	printf("%s \n", card1.primaryAccountNumber);
	return 0;
} 