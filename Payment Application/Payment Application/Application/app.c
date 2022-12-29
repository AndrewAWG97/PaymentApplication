#include "app.h"

ST_cardData_t AppCard;
ST_terminalData_t AppTerminal;
ST_transaction_t AppTransaction;


extern ST_accountsDB_t accountsDB[255];
extern ST_transaction_t transactionDB[255];

//EN_cardError_t isEXP_APP;



void appStart(void) {
	ST_cardData_t AppCard = { 0 };
	ST_terminalData_t AppTerminal = { 0 };
	ST_transaction_t AppTransaction = { 0 };

	setMaxAmount(&AppTerminal, 5000.0);
	
	getCardHolderName(&AppCard);
	getCardPAN(&AppCard);
	getCardExpiryDate(&AppCard);

	getTransactionDate(&AppTerminal);
	getTransactionAmount(&AppTerminal);

	AppTransaction.cardHolderData = AppCard;
	AppTransaction.terminalData = AppTerminal;

	AppTransaction.transState = receiveTransactionData(&AppTransaction);
	saveTransaction(&AppTransaction);
}


