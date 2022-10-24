#include "app.h"
void appStart(void)
{
	ST_cardData_t card; 
	ST_terminalData_t terminal; 
	/* get card name */
	while (getCardHolderName(&card) != CARD_OK)
	{
		printf("Wrong Name try again\n"); 
	}
	/*get card expiry date */
	while (getCardExpiryDate(&card) != CARD_OK)
	{
		printf("Wrong Expiry Date try again\n");
	}
	
	/* check on card number and format and see if it Luhn number or not  */
	while (1)
	{
		if (getCardPAN(&card) != CARD_OK)
		{
			printf("Wrong card Pan try again\n");
		}
		else
		{
			if (isValidCardPAN(&card) == TERMINAL_OK)
			{
				break;
			}
			else
			{
				printf("Wrong card Pan (Not Luhn Number) try again\n");
			}
		}

	}
	printf("\n------- all card data collected -------\n");
						/* Card Ends Here */

	/*get trasaction date number */
	while (getTransactionDate(&terminal) != TERMINAL_OK) 
	{
		printf("Wrong trasaction date number \n");
	}
	/*if the card isn't expiered*/
	if (isCardExpired(&card,&terminal) == TERMINAL_OK)
	{
		/* get trasaction amount */
		while (getTransactionAmount(&terminal) != TERMINAL_OK)
		{
			printf("Wrong trasaction amount enter number > 0 \n");
		}
		setMaxAmount(&terminal, 20000.5); /* hard coded max amount to be 20000.5 */
		
		/* check if the trasaction amount is biger than max amount */
		if (isBelowMaxAmount(&terminal) != TERMINAL_OK)
		{
			printf("Declined Amount Exceeding Limit 20000.5\n"); 
		}
		else
		{
			printf("\n------- terminal data collected  -------\n");
								/* Terminal Ends Here */
			
			ST_transaction_t trasData = { .cardHolderData = card , .terminalData = terminal };
			
			/* all state msgs */
			char statemsg[5][27] = { "TANSACTION_APPROVED", "DECLINED_INSUFFECIENT_FUND", "DECLINED_STOLEN_CARD", "FRAUD_CARD", "INTERNAL_SERVER_ERROR" };
			
			/* recieve Transaction Data from the server data base */
			EN_transState_t state = recieveTransactionData(&trasData);
			
			/* print server state msg */
			printf("\nTransaction shortened state: %s \n",statemsg[(int)state]);
		}

	}
	else 
	{
		printf("Declined Expired card  \n"); 
	}

}
