#ifndef SERVER_H_
#define SERVER_H_
#include "..\Terminal\terminal.h"

#define server_debug  0

/* unsigned 32 integer typedef */
typedef unsigned long long uint32_t;
/* trasaction states enum */
typedef enum EN_transState_t
{
    APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD, INTERNAL_SERVER_ERROR
}EN_transState_t;
/* transaction data struct */
typedef struct ST_transaction_t
{
    ST_cardData_t cardHolderData;
    ST_terminalData_t terminalData;
    EN_transState_t transState;
    uint32_t transactionSequenceNumber;
}ST_transaction_t;
/* server error enum */
typedef enum EN_serverError_t
{
    SERVER_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE, BLOCKED_ACCOUNT
}EN_serverError_t;
/* account state enum*/
typedef enum EN_accountState_t
{
    RUNNING,
    BLOCKED
}EN_accountState_t;

/* accounts data struct */
typedef struct ST_accountsDB_t
{
    float balance;
    EN_accountState_t state;
    uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;

/**
 * @brief  recieve Transaction Data from the server 
 * 
 * @param transData 
 * @return EN_transState_t 
 */
EN_transState_t recieveTransactionData(ST_transaction_t* transData);

/**
 * @brief check if an account is in the database  
 * 
 * @param cardData 
 * @param accountRefrence 
 * @return EN_serverError_t 
 */
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence);
/**
 * @brief check if an account is blocked or not 
 * 
 * @param accountRefrence 
 * @return EN_serverError_t 
 */
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence);
/**
 * @brief check if the transaction amount is not exceeding the amount in account 
 * 
 * @param termData 
 * @param accountRefrence 
 * @return EN_serverError_t 
 */
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence);
/**
 * @brief save transaction data into the database 
 * 
 * @param transData 
 * @return EN_serverError_t 
 */
EN_serverError_t saveTransaction(ST_transaction_t* transData);
/**
 * @brief show all saved transactions
 * 
 */
void listSavedTransactions(void);

/* test functions */
#if server_debug > 0
void recieveTransactionDataTest(void);

void isValidAccountTest(void);

void isBlockedAccountTest(void);

void isAmountAvailableTest(void);

void saveTransactionTest(void);

void listSavedTransactionsTest(void);
#endif 


#endif // !SERVER_H_
