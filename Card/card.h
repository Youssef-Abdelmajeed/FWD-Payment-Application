#ifndef CARD_H_

#define CARD_H_

#include <stdio.h>
#include <stdlib.h>

typedef unsigned char uint8_t;

/* card structure */
typedef struct ST_cardData_t
{
    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
}ST_cardData_t;

/*card error struct */
typedef enum EN_cardError_t
{
    CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

/**
 * @brief Get the Card Holder Name object
 * 
 * @param cardData 
 * @return EN_cardError_t 
 */
EN_cardError_t getCardHolderName(ST_cardData_t* cardData);

/**
 * @brief Get the Card Expiry Date object
 * 
 * @param cardData 
 * @return EN_cardError_t 
 */
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);

/**
 * @brief Get the Card P A N object
 * 
 * @param cardData 
 * @return EN_cardError_t 
 */
EN_cardError_t getCardPAN(ST_cardData_t* cardData);


#endif // !CARD_H_
