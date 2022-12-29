#include "server.h"

/* Enabling test functions by defining TEST_CASE */
//#define TEST_CASE
#define MAIN_APP

static int transactionCounter = 0;

extern int accReferenceNumber;
extern ST_accountsDB_t accountsDB[255];
extern ST_transaction_t transactionDB[255];

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountReference) {
	uint8_t AccountValidity = 1;
	
	for (int i = 0; i < 255; i++) {
		AccountValidity = strcmp(cardData->primaryAccountNumber, (accountReference+i)->primaryAccountNumber);
		if(AccountValidity == 0) {
			accReferenceNumber = i;
#ifndef MAIN_APP
			printf("Account is found \n");
			puts((accountReference + i)->primaryAccountNumber);
#endif
			return SERVER_OK;
		}
	}
#ifndef MAIN_APP
	printf("Account not Found\n");
#endif
#ifndef TEST_CASE
	accReferenceNumber = NULL;
#endif
	return ACCOUNT_NOT_FOUND;
}


EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountReference) {
	EN_accountState_t State = BLOCKED;
	State = (accountReference + accReferenceNumber)->state;
	if (BLOCKED == State) {
#ifndef MAIN_APP
		printf("This account %s is Blocked\n", (accountReference + accReferenceNumber)->primaryAccountNumber);
#endif
		return BLOCKED_ACCOUNT;
	}
	else {
#ifndef MAIN_APP
		printf("This account  %s is Running\n", (accountReference + accReferenceNumber)->primaryAccountNumber);
#endif
		return SERVER_OK;
	}
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountReference) {
	if (termData->transAmount > (accountReference + accReferenceNumber)->balance) {
#ifndef MAIN_APP
		printf("The Account balance is insufficient :%f\n\n", (accountReference + accReferenceNumber)->balance);
#endif
		return LOW_BALANCE;
	}
	else {
#ifndef MAIN_APP
		printf("The Account balance is sufficient :%f\n\n", (accountReference + accReferenceNumber)->balance);
#endif
		return SERVER_OK;
	}
}

EN_serverError_t saveTransaction(ST_transaction_t* transData) {
	transData->transactionSequenceNumber = (transactionCounter + 1);
	*(transactionDB + transactionCounter) = *transData;
	listSavedTransactions();
	++transactionCounter;
	accReferenceNumber++;
	return SERVER_OK;
}

void listSavedTransactions(void) {
	static uint8_t breakCounter = 0;
	for(int i = 0 ; i<transactionCounter+1; i++){
		if (breakCounter > transactionCounter) {
			break;
		}
		printf("\n#######################\n");
		printf("Transaction Sequence Number: %u\n", transactionDB[transactionCounter].transactionSequenceNumber);
		printf("Transaction Date: %s\n", transactionDB[transactionCounter].terminalData.transactionDate);
		printf("Transaction Amount : %f\n", transactionDB[transactionCounter].terminalData.transAmount);
		switch (transactionDB[transactionCounter].transState) {
		case APPROVED:
			printf("Transaction State: APPROVED\n");
			printf("New balance : %f\n", accountsDB[accReferenceNumber].balance);
			break;
		case DECLINED_INSUFFECIENT_FUND:
			printf("Transaction State: DECLINED - Insufficient balance amount\n");
			break;
		case DECLINED_STOLEN_CARD:
			printf("Transaction State: DECLINED stolen card\n");
			break;
		case FRAUD_CARD:
			printf("Transaction State: DECLINED Account not available\n");
			break;
		case INTERNAL_SERVER_ERROR:
			printf("Transaction State: DECLINED server error\n");
			break;
		case DECLINED:
			printf("Transaction State: DECLINED Card Expired\n");
			break;
		case EXCEED_MAX:
			printf("Transaction State: DECLINED Exceed Max Amount\n");
			break;
		default:
			printf("NO ENTERED VALUE\n");
		}
		printf("Terminal Max Amount: %f\n", transactionDB[transactionCounter].terminalData.maxTransAmount);
		printf("Cardholder Name : %s", transactionDB[transactionCounter].cardHolderData.cardHolderName);
		printf("PAN : %s", transactionDB[transactionCounter].cardHolderData.primaryAccountNumber);
		printf("Card Expiration Date: %s\n", transactionDB[transactionCounter].cardHolderData.cardExpirationDate);
		printf("#######################\n");
		breakCounter++;
	}
	getchar();
}

EN_transState_t receiveTransactionData(ST_transaction_t* transData) {
	ST_cardData_t cardDataHolder = transData->cardHolderData;
	ST_terminalData_t terminalDataHolder = transData->terminalData;

	EN_terminalError_t isBelowMax;
	EN_serverError_t isBlocked;
	EN_serverError_t isValid;
	EN_terminalError_t isEXP;
	isEXP = isCardExpired(&cardDataHolder, &terminalDataHolder);

	
	isValid = isValidAccount(&cardDataHolder, accountsDB);
	
	if (SERVER_OK == isValid) {

		isBlocked = isBlockedAccount(accountsDB);
		isBelowMax = isBelowMaxAmount(&terminalDataHolder);
		if (isEXP == EXPIRED_CARD) {
			return DECLINED;
		}

		if (SERVER_OK == isBlocked) {
			EN_serverError_t isAmountAv;
			isAmountAv = isAmountAvailable(&terminalDataHolder, accountsDB);
			
			if (SERVER_OK == isAmountAv) {
				if (isBelowMax == TERMINAL_OK) {
					(accountsDB + accReferenceNumber)->balance = ((accountsDB + accReferenceNumber)->balance) - terminalDataHolder.transAmount;
#ifndef MAIN_APP
					printf("The new balance is %f\n", (accountsDB + accReferenceNumber)->balance);
#endif
					return APPROVED;
				}
				else {
					return EXCEED_MAX;
				}
			}
			else {
#ifndef MAIN_APP
				printf("Declined insufficient amount\n");
#endif
				return DECLINED_INSUFFECIENT_FUND;
			}
		}
		else if(isBlocked == BLOCKED_ACCOUNT) {
#ifndef MAIN_APP
			printf("Declined Stolen Card\n");
#endif
			return DECLINED_STOLEN_CARD;
		}
//		else if (isEXP == EXPIRED_CARD)
//		{
//#ifndef MAIN_APP
//			printf("EXPIRED CARD\n");
//#endif
//			return DECLINED;
//		}
	}
	else {
#ifndef MAIN_APP
		printf("Account is not available\n");
#endif
		return FRAUD_CARD;
	}
}

/******************* Test Functions ***********************/


void receiveTransactionDataTest(void) {
	ST_transaction_t transTest;
	ST_cardData_t cardtest;
	ST_terminalData_t terminalTest;

	printf("Tester name : Andrew Ashraf Waheed\n");
	printf("Function Name : receiveTransaction\n\n");

	printf("Test no 1\n");
	printf("This account has 1000.0 in Balance\n ");
	printf("            Will withdraw 7000\n ");
	printf("            is running\n ");
	printf("            Max withdrawal is 5000.0\n ");
	printf("            Card Exp date is 12/22\n");
	printf("Expected to be DECLINED\n");

	strcpy_s(transTest.cardHolderData.cardHolderName, sizeof(transTest.cardHolderData.cardHolderName), "Andrew Ashraf Waheed");
	strcpy_s(transTest.cardHolderData.cardExpirationDate, sizeof(transTest.cardHolderData.cardExpirationDate), "12/22");
	strcpy_s(transTest.cardHolderData.primaryAccountNumber, sizeof(transTest.cardHolderData.primaryAccountNumber), "8989374615436851");

	transTest.terminalData.transAmount = 7000.0;
	transTest.terminalData.maxTransAmount = 5000.0;
	strcpy_s(transTest.terminalData.transactionDate, sizeof(transTest.terminalData.transactionDate), "21/11/2022");
	transTest.transState = receiveTransactionData(&transTest);
	saveTransaction(&transTest);	
	/**************************************************************************************/
	printf("\nTest no 2\n");
	printf("This account has 1000.0 in Balance\n ");
	printf("            Will withdraw 1000\n ");
	printf("            is blocked\n ");
	printf("            Max withdrawal is 5000.0\n ");
	printf("            Card Exp date is 12/23\n");
	printf("Expected to be DECLINED\n");
	ST_transaction_t transTest_1;

	strcpy_s(transTest_1.cardHolderData.cardHolderName, sizeof(transTest_1.cardHolderData.cardHolderName), "Mina Maher Seif");
	strcpy_s(transTest_1.cardHolderData.cardExpirationDate, sizeof(transTest_1.cardHolderData.cardExpirationDate), "12/23");
	strcpy_s(transTest_1.cardHolderData.primaryAccountNumber, sizeof(transTest_1.cardHolderData.primaryAccountNumber), "5807007076043875");

	transTest_1.terminalData.transAmount = 1000.0;
	transTest_1.terminalData.maxTransAmount = 5000.0;
	strcpy_s(transTest_1.terminalData.transactionDate, sizeof(transTest_1.terminalData.transactionDate), "21/11/2022");

	transTest_1.transState = receiveTransactionData(&transTest_1);
	saveTransaction(&transTest_1);


	/**************************************************************************************/
	printf("\nTest no 3\n");
	printf("This account has 10000.0 in Balance\n ");
	printf("            Will withdraw 1000\n ");
	printf("            is running\n ");
	printf("            Max withdrawal is 5000.0\n ");
	printf("            Card Exp date is 12/21\n");
	printf("Expected to be DECLINED EXPIRED CARD\n");
	ST_transaction_t transTest_2;

	strcpy_s(transTest_2.cardHolderData.cardHolderName, sizeof(transTest_2.cardHolderData.cardHolderName), "Ahmed Mohamed Hossam");
	strcpy_s(transTest_2.cardHolderData.cardExpirationDate, sizeof(transTest_2.cardHolderData.cardExpirationDate), "12/21");
	strcpy_s(transTest_2.cardHolderData.primaryAccountNumber, sizeof(transTest_2.cardHolderData.primaryAccountNumber), "5286149814901616");

	transTest_2.terminalData.transAmount = 1000.0;
	transTest_2.terminalData.maxTransAmount = 5000.0;
	strcpy_s(transTest_2.terminalData.transactionDate, sizeof(transTest_2.terminalData.transactionDate), "21/11/2022");

	transTest_2.transState = receiveTransactionData(&transTest_2);
	saveTransaction(&transTest_2);
}



void isValidAccountTest(void) {
	ST_cardData_t cardTest;

	printf("Tester name : Andrew Ashraf Waheed\n");
	printf("Function Name : isValidAccount\n\n");

	/* Test account no 1 */
	printf("Test no 1\n");
	printf("Input Data : 8989374615436851\n");
	printf("Expected Value : Account is found\n");
	printf("Actual Value : ");
	strcpy_s(cardTest.primaryAccountNumber, sizeof(cardTest.primaryAccountNumber), "8989374615436851");
	isValidAccount(&cardTest, accountsDB);

	/* Test account no 2 */
	printf("\nTest no 2\n");
	printf("Input Data : 5807007076043875\n");
	printf("Expected Value : Account is found\n");
	printf("Actual Value : ");
	strcpy_s(cardTest.primaryAccountNumber, sizeof(cardTest.primaryAccountNumber), "5807007076043875");
	isValidAccount(&cardTest, accountsDB);

	/* Test account no 3 */
	printf("\nTest no 3\n");
	printf("Input Data : 5286149814901616\n");
	printf("Expected Value : Account is found\n");
	printf("Actual Value : ");
	strcpy_s(cardTest.primaryAccountNumber, sizeof(cardTest.primaryAccountNumber), "5286149814901616");
	isValidAccount(&cardTest, accountsDB);

	/* Test account no 4 */
	printf("\nTest no 4\n");
	printf("Input Data : 5553150909172242\n");
	printf("Expected Value : Account is found\n");
	printf("Actual Value : ");
	strcpy_s(cardTest.primaryAccountNumber, sizeof(cardTest.primaryAccountNumber), "5553150909172242");
	isValidAccount(&cardTest, accountsDB);

	/* Test account no 5 */
	printf("\nTest no 5\n");
	printf("Input Data : 5594436517409675\n");
	printf("Expected Value : Account is found\n");
	printf("Actual Value : ");
	strcpy_s(cardTest.primaryAccountNumber, sizeof(cardTest.primaryAccountNumber), "5594436517409675");
	isValidAccount(&cardTest, accountsDB);

	/* Test account no 6 */
	printf("\nTest no 6\n");
	printf("Input Data : 5103673122656977\n");
	printf("Expected Value : Account is found\n");
	printf("Actual Value : ");
	strcpy_s(cardTest.primaryAccountNumber, sizeof(cardTest.primaryAccountNumber), "5103673122656977");
	isValidAccount(&cardTest, accountsDB);

	/* Test account no 7 */
	printf("\nTest no 7\n");
	printf("Input Data : 4024007188082142\n");
	printf("Expected Value : Account is found\n");
	printf("Actual Value : ");
	strcpy_s(cardTest.primaryAccountNumber, sizeof(cardTest.primaryAccountNumber), "4024007188082142");
	isValidAccount(&cardTest, accountsDB);

	/* Test account no 8 */
	printf("\nTest no 8\n");
	printf("Input Data : 4556224496299666\n");
	printf("Expected Value : Account is found\n");
	printf("Actual Value : ");
	strcpy_s(cardTest.primaryAccountNumber, sizeof(cardTest.primaryAccountNumber), "4556224496299666");
	isValidAccount(&cardTest, accountsDB);

	/* Test account no 9 */
	printf("\nTest no 9\n");
	printf("Input Data : 6011882618265321\n");
	printf("Expected Value : Account is found\n");
	printf("Actual Value : ");
	strcpy_s(cardTest.primaryAccountNumber, sizeof(cardTest.primaryAccountNumber), "6011882618265321");
	isValidAccount(&cardTest, accountsDB);

	/* Test account no 10 */
	printf("\nTest no 10\n");
	printf("Input Data : 6011940773789228\n");
	printf("Expected Value : Account is found\n");
	printf("Actual Value : ");
	strcpy_s(cardTest.primaryAccountNumber, sizeof(cardTest.primaryAccountNumber), "6011940773789228");
	isValidAccount(&cardTest, accountsDB);

	/* Test account INVALID ACCOUNT */
	printf("\nTest no 11\n");
	printf("Input Data : 1000200030004000\n");
	printf("Expected Value : Account not found\n");
	printf("Actual Value : ");
	strcpy_s(cardTest.primaryAccountNumber, sizeof(cardTest.primaryAccountNumber), "1000200030004000");
	isValidAccount(&cardTest, accountsDB);
}

void isBlockedAccountTest(void) {
	ST_cardData_t cardTest;

	printf("Tester name : Andrew Ashraf Waheed\n");
	printf("Function Name : isBlockedAccount\n\n");

	/* Test account no 1 */
	printf("Test no 1\n");
	printf("Input Data : 8989374615436851\n");
	printf("Expected Value : RUNNING\n");
	printf("Actual Value : ");
	strcpy_s(cardTest.primaryAccountNumber, sizeof(cardTest.primaryAccountNumber), "8989374615436851");
	if (isValidAccount(&cardTest, accountsDB) == SERVER_OK) {
		isBlockedAccount(accountsDB);
	}
	/* Test account no 2 */
	printf("\nTest no 2\n");
	printf("Input Data : 5807007076043875\n");
	printf("Expected Value : BLOCKED\n");
	printf("Actual Value : ");
	strcpy_s(cardTest.primaryAccountNumber, sizeof(cardTest.primaryAccountNumber), "5807007076043875");
	if (isValidAccount(&cardTest, accountsDB) == SERVER_OK) {
		isBlockedAccount(accountsDB);
	}

	/* Test account no 3 */
	printf("\nTest no 3\n");
	printf("Input Data : 5286149814901616\n");
	printf("Expected Value : RUNNING\n");
	printf("Actual Value : ");
	strcpy_s(cardTest.primaryAccountNumber, sizeof(cardTest.primaryAccountNumber), "5286149814901616");
	if (isValidAccount(&cardTest, accountsDB) == SERVER_OK) {
		isBlockedAccount(accountsDB);
	}
	/* Test account no 4 */
	printf("\nTest no 4\n");
	printf("Input Data : 5553150909172242\n");
	printf("Expected Value : BLOCKED\n");
	printf("Actual Value : ");
	strcpy_s(cardTest.primaryAccountNumber, sizeof(cardTest.primaryAccountNumber), "5553150909172242");
	if (isValidAccount(&cardTest, accountsDB) == SERVER_OK) {
		isBlockedAccount(accountsDB);
	}

	/* Test account no 5 */
	printf("\nTest no 5\n");
	printf("Input Data : 5594436517409675\n");
	printf("Expected Value : RUNNING\n");
	printf("Actual Value : ");
	strcpy_s(cardTest.primaryAccountNumber, sizeof(cardTest.primaryAccountNumber), "5594436517409675");
	if (isValidAccount(&cardTest, accountsDB) == SERVER_OK) {
		isBlockedAccount(accountsDB);
	}

	/* Test account no 6 */
	printf("\nTest no 6\n");
	printf("Input Data : 5103673122656977\n");
	printf("Expected Value : BLOCKED\n");
	printf("Actual Value : ");
	strcpy_s(cardTest.primaryAccountNumber, sizeof(cardTest.primaryAccountNumber), "5103673122656977");
	if (isValidAccount(&cardTest, accountsDB) == SERVER_OK) {
		isBlockedAccount(accountsDB);
	}

	/* Test account no 7 */
	printf("\nTest no 7\n");
	printf("Input Data : 4024007188082142\n");
	printf("Expected Value : RUNNING\n");
	printf("Actual Value : ");
	strcpy_s(cardTest.primaryAccountNumber, sizeof(cardTest.primaryAccountNumber), "4024007188082142");
	if (isValidAccount(&cardTest, accountsDB) == SERVER_OK) {
		isBlockedAccount(accountsDB);
	}

	/* Test account no 8 */
	printf("\nTest no 8\n");
	printf("Input Data : 4556224496299666\n");
	printf("Expected Value : RUNNING\n");
	printf("Actual Value : ");
	strcpy_s(cardTest.primaryAccountNumber, sizeof(cardTest.primaryAccountNumber), "4556224496299666");
	if (isValidAccount(&cardTest, accountsDB) == SERVER_OK) {
		isBlockedAccount(accountsDB);
	}

	/* Test account no 9 */
	printf("\nTest no 9\n");
	printf("Input Data : 6011882618265321\n");
	printf("Expected Value : BLOCKED\n");
	printf("Actual Value : ");
	strcpy_s(cardTest.primaryAccountNumber, sizeof(cardTest.primaryAccountNumber), "6011882618265321");
	if (isValidAccount(&cardTest, accountsDB) == SERVER_OK) {
		isBlockedAccount(accountsDB);
	}

	/* Test account no 10 */
	printf("\nTest no 10\n");
	printf("Input Data : 6011940773789228\n");
	printf("Expected Value : BLOCKED\n");
	printf("Actual Value : ");
	strcpy_s(cardTest.primaryAccountNumber, sizeof(cardTest.primaryAccountNumber), "6011940773789228");
	if (isValidAccount(&cardTest, accountsDB) == SERVER_OK) {
		isBlockedAccount(accountsDB);
	}

	/* Test account INVALID ACCOUNT */
	printf("\nTest no 11\n");
	printf("Input Data : 5286149814901616\n");
	printf("Expected Value : ACCOUNT NOT FOUND\n");
	printf("Actual Value : ");
	strcpy_s(cardTest.primaryAccountNumber, sizeof(cardTest.primaryAccountNumber), "1000200030004000");
	if (isValidAccount(&cardTest, accountsDB) == SERVER_OK) {
		isBlockedAccount(accountsDB);
	}
}
/**********************************************************************************************************/



void isAmountAvailableTest(void) {
	ST_terminalData_t termTest;
	ST_cardData_t cardTest;

	printf("Tester name : Andrew Ashraf Waheed\n");
	printf("Function Name : isAmountAvailable\n\n");

	printf("Test Case 1: 1\n");
	printf("Input data: Withdraw 200.0\n");

	termTest.transAmount = 200.0;
	strcpy_s(cardTest.primaryAccountNumber, sizeof(cardTest.primaryAccountNumber), "8989374615436851");
	if (isValidAccount(&cardTest, accountsDB) == SERVER_OK) {
		if (isBlockedAccount(accountsDB) == RUNNING) {
			printf("Expected Value : The Account balance is sufficient\n");
			printf("Atual Value : ");
			isAmountAvailable(&termTest, accountsDB);
		}
	}

	printf("\nTest Case 2\n");
	printf("Input data: Withdraw 800.0\n");


	termTest.transAmount = 800.0;
	strcpy_s(cardTest.primaryAccountNumber, sizeof(cardTest.primaryAccountNumber), "5807007076043875");
	if (isValidAccount(&cardTest, accountsDB) == SERVER_OK) {
		printf("Expected Value : The Account is blocked & has sufficient balance\n");
		printf("Atual Value : ");
		if (isBlockedAccount(accountsDB) == RUNNING) {
			isAmountAvailable(&termTest, accountsDB);
		}
	}

	printf("\nTest Case 3\n");
	printf("Input data: Withdraw 1000.0\n");

	termTest.transAmount = 1000.0;
	strcpy_s(cardTest.primaryAccountNumber, sizeof(cardTest.primaryAccountNumber), "5594436517409675");
	if (isValidAccount(&cardTest, accountsDB) == SERVER_OK) {
		if (isBlockedAccount(accountsDB) == RUNNING) {
			printf("Expected Value : The Account balance is running and has insufficient balance\n");
			printf("Atual Value : ");
			isAmountAvailable(&termTest, accountsDB);
		}
	}

	printf("\nTest Case 4\n");
	printf("Input data: 900.0\n");

	termTest.transAmount = 1000.0;
	strcpy_s(cardTest.primaryAccountNumber, sizeof(cardTest.primaryAccountNumber), "6011882618265321");
	if (isValidAccount(&cardTest, accountsDB) == SERVER_OK) {
		printf("Expected Value : The Account is blocked but has insufficient balance\n");
		printf("Atual Value : ");
		if (isBlockedAccount(accountsDB) == RUNNING) {
			isAmountAvailable(&termTest, accountsDB);
		}
	}

	printf("\nTest Case 5\n");
	printf("Input data: 1000.0\n");

	termTest.transAmount = 1000.0;
	strcpy_s(cardTest.primaryAccountNumber, sizeof(cardTest.primaryAccountNumber), "1002003215616");
	printf("Expected Value : The Account is not found\n");
	printf("Atual Value : ");
	if (isValidAccount(&cardTest, accountsDB) == SERVER_OK) {
		if (isBlockedAccount(accountsDB) == RUNNING) {
			isAmountAvailable(&termTest, accountsDB);
		}
	}
}
