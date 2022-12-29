#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE

/***** User libraries *****/
//#include "/Andrew Gam3a/egfwd/New folder/Payment Application/Payment Application/App/app.h"
#include "card.h"
#include "server.h" 
#include "terminal.h"
#include "app.h"

/* Accounts Data Base*/
ST_accountsDB_t accountsDB[255] = {
	{  1000.0, RUNNING, "8989374615436851\n"},
	{  1000.0, BLOCKED, "5807007076043875\n"},
	{ 10000.0, RUNNING, "5286149814901616\n"},
	{120000.0, BLOCKED, "5553150909172242\n"},
	{   322.0, RUNNING, "5594436517409675\n"},
	{965000.0, BLOCKED, "5103673122656977\n"},
	{ 32100.0, RUNNING, "4024007188082142\n"},
	{123000.0, RUNNING, "4556224496299666\n"},
	{   900.0, BLOCKED, "6011882618265321\n"},
	{  7890.0, BLOCKED, "6011940773789228\n"},
	{  1000.0, RUNNING, "9000800070006000\n"},
	{  1000.0, BLOCKED, "1000200030004000\n"},

};

int accReferenceNumber = 0;

ST_transaction_t transactionDB[255] = { 0 };


/*Date used for testing purposes*/
uint8_t g_day = 21;
uint8_t g_month = 11;
uint8_t g_year = 22;


int main() {
	//int counter = 0;
	//while (1) {
	//	counter++;
	//	printf("Counter %d\n", counter);
	//}
	appStart();

	


	/* Testing Terminal.h */

	//ST_terminalData_t termtest;
	//getTransactionDateTest();
	//printf("************************************\n");
	//printf("************************************\n");
	//isCardExpiredTest();
	//printf("************************************\n");
	//printf("************************************\n");
	////getTransactionAmount(&termtest);
	//getTransactionAmountTest();
	//printf("************************************\n");
	//printf("************************************\n");
	//isBelowMaxAmountTest();
	//printf("************************************\n");
	//printf("************************************\n");
	//setMaxAmountTest();
	//printf("************************************\n");
	//printf("************************************\n");

	/* Testing Card.h */

	/*getCardHolderNameTest();
	printf("************************************\n");
	printf("************************************\n");
	getCardExpiryDateTest();
	printf("************************************\n");
	printf("************************************\n");
	getCardPANTest();
	printf("************************************\n");
	printf("************************************\n");*/


	/* Testing Server.h*/
	/*ST_transaction_t transTest;
	ST_terminalData_t terminalTest;
	ST_cardData_t cardTest;

	strcpy_s(transTest.cardHolderData.cardHolderName, sizeof(transTest.cardHolderData.cardHolderName), "Andrew Ashraf Waheed");
	strcpy_s(transTest.cardHolderData.cardExpirationDate, sizeof(transTest.cardHolderData.cardExpirationDate), "12/22");
	strcpy_s(transTest.cardHolderData.primaryAccountNumber, sizeof(transTest.cardHolderData.primaryAccountNumber), "8989374615436851");


	transTest.terminalData.transAmount = 7000.0;
	transTest.terminalData.maxTransAmount = 5000.0;
	strcpy_s(transTest.terminalData.transactionDate, sizeof(transTest.terminalData.transactionDate), "21/11/2022");

	transTest.transState = receiveTransactionData(&transTest);
	saveTransaction(&transTest);*/

	/**************************************************************************/
	/******************************** Second Account **************************/
	/**************************************************************************/
	/*ST_transaction_t transTest_1;

	strcpy_s(transTest_1.cardHolderData.cardHolderName, sizeof(transTest_1.cardHolderData.cardHolderName), "Mina Maher Seif");
	strcpy_s(transTest_1.cardHolderData.cardExpirationDate, sizeof(transTest_1.cardHolderData.cardExpirationDate), "12/23");
	strcpy_s(transTest_1.cardHolderData.primaryAccountNumber, sizeof(transTest_1.cardHolderData.primaryAccountNumber), "5807007076043875");


	transTest_1.terminalData.transAmount = 1000.0;
	transTest_1.terminalData.maxTransAmount = 5000.0;
	strcpy_s(transTest_1.terminalData.transactionDate, sizeof(transTest_1.terminalData.transactionDate), "21/11/2022");

	transTest_1.transState = receiveTransactionData(&transTest_1);
	saveTransaction(&transTest_1);*/


	//isValidAccountTest();
	//printf("************************************\n");
	//printf("************************************\n");
	//isBlockedAccountTest();
	//printf("************************************\n");
	//printf("************************************\n");
	//isAmountAvailableTest();
	//printf("************************************\n");
	//printf("************************************\n");
	//receiveTransactionDataTest();
	//printf("************************************\n");
	//printf("************************************\n");

	
	/**************************************************/

}

