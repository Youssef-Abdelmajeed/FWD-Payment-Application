#ifndef TERMINAL_H_
#define TERMINAL_H_

#include "..\Card\card.h"
/* Terminal data struct */
typedef struct ST_terminalData_t
{
    float transAmount;
    float maxTransAmount;
    uint8_t transactionDate[11];
}ST_terminalData_t;
/* terminal error struct */
typedef enum EN_terminalError_t
{
    TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t;

/**
 * @brief Get the Transaction Date object
 * 
 * @param termData 
 * @return EN_terminalError_t 
 */
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData);

/**
 * @brief check if the given card is expired or not 
 * 
 * @param cardData 
 * @param termData 
 * @return EN_terminalError_t 
 */
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData);

/**
 * @brief Get the Transaction Amount object
 * 
 * @param termData 
 * @return EN_terminalError_t 
 */
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData);

/**
 * @brief check if the Transaction is below the max amount 
 * 
 * @param termData 
 * @return EN_terminalError_t 
 */
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData);

/**
 * @brief Set the Max Amount object
 * 
 * @param termData 
 * @param maxAmount 
 * @return EN_terminalError_t 
 */
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount);

/**
 * @brief check if luhn number is valid 
 * 
 * @param cardData 
 * @return EN_terminalError_t 
 */
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData); // Optional



#endif // !TERMINAL_H_
