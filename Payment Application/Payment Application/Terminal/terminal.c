#include "terminal.h"


extern uint8_t g_day;
extern uint8_t g_month;
extern uint8_t g_year;


/* Enabling test functions by defining TEST_CASE */
//#define TEST_CASE
#define APP_START
#define MAIN_APP

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
	uint8_t StringLength;
	uint8_t month = 0;
	uint8_t year = 0;
	uint8_t day = 0;

#ifndef TEST_CASE
	printf("Date format DD/MM/YYYY ex: 19/02/2022\n");
	printf("Please enter transaction date : ");
	gets(termData->transactionDate);
#endif
	StringLength = strlen(termData->transactionDate);

	if (StringLength == NULL) {
#ifndef MAIN_APP
		printf("No date entered\n");
#endif
		return WRONG_DATE;
	}
	/*check the size of the entered date*/
	if (StringLength != 10) {
#ifndef MAIN_APP
		printf("Wrong date format\n\n");
		puts(termData->transactionDate);
#endif
		return WRONG_DATE;
	}
	else if (StringLength == 10) {
		/* check if the date format is valid*/
		if ((termData->transactionDate[2] != '/') || (termData->transactionDate[5] != '/')) {
#ifndef MAIN_APP
			printf("Wrong date format\n\n");
			puts(termData->transactionDate);
#endif
			return WRONG_DATE;
		}
		/*get the month and year to be compared with the global month and year*/
		for (int i = 0; i < StringLength; i++) {
			if (i < 2) {
				if ((termData->transactionDate[i] >= '0') && (termData->transactionDate[i] <= '9')) {
					uint8_t digit;
					digit = termData->transactionDate[i] - '0';
					day = day * 10 + digit;
				}
			}
			else if (i > 2 && i < 5) {
				if ((termData->transactionDate[i] > '0') && (termData->transactionDate[i] < '9')) {
					uint8_t digit;
					digit = termData->transactionDate[i] - '0';
					month = month * 10 + digit;
				}
			}
			else if (i > 7 && i < 10) {
				if ((termData->transactionDate[i] > '0') && (termData->transactionDate[i] < '9')) {
					uint8_t digit;
					digit = termData->transactionDate[i] - '0';
					year = year * 10 + digit;
				}
			}
		}
		if (day == g_day && month == g_month && year == g_year) {
#ifndef MAIN_APP
			printf("Terminal Date is OK\n\n");
#endif
			return TERMINAL_OK;
		}
		else {
#ifndef MAIN_APP
			printf("Wrong Date \n");
#endif
			return WRONG_DATE;
		}
	}
}


EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData) {
	EN_terminalError_t TerminalDate = cmpTransactionDate(termData);
	EN_cardError_t CardDate = cmpCardExpiryDate(cardData);
#ifdef TEST_CASE
	EN_terminalError_t TerminalDate = getTransactionDate(termData);
	EN_cardError_t CardDate = getCardExpiryDate(cardData);
#endif
	if (TerminalDate == TERMINAL_OK) {
		if (CardDate == CARD_OK) {
#ifndef MAIN_APP
			printf("Card Status is : OK\n\n");
#endif
			return TERMINAL_OK;
		}
		else {
#ifndef MAIN_APP
			printf("Card Status is : EXPIRED\n\n");
#endif
			return EXPIRED_CARD;
		}
	}
	else if (TerminalDate == WRONG_DATE) {
		
	}
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
#ifndef TEST_CASE
	printf("Enter transaction ammount : ");
	scanf_s(" %f", &termData->transAmount);
#endif
	if (termData->transAmount <= 0) {
#ifndef MAIN_APP
		printf("Amount is %f\n\n", termData->transAmount);
#endif
		return INVALID_AMOUNT;
	}
	else {
#ifndef MAIN_APP
		printf("Amount is %0.2f\n", termData->transAmount);
#endif
		return TERMINAL_OK;
	}
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
	if (termData->transAmount <= termData->maxTransAmount) {
#ifndef MAIN_APP
		printf("Amount APPROVED\n");
#endif
		return TERMINAL_OK;
	}
	else {
#ifndef MAIN_APP
		printf("NO ACCEPTED\n");
#endif
		return EXCEED_MAX_AMOUNT;
	}
}


EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount) {
	if ( maxAmount >= 0) {
		termData->maxTransAmount = maxAmount;
#ifndef MAIN_APP
		printf("Max amount is set successfully\n");
#endif
		return TERMINAL_OK;
	}
	else {
#ifndef MAIN_APP
		printf("Max amount is invalid\n");
#endif
		return INVALID_MAX_AMOUNT;
	}
}




static EN_terminalError_t cmpTransactionDate(ST_terminalData_t* termData) {
	uint8_t StringLength;
	uint8_t month = 0;
	uint8_t year = 0;
	uint8_t day = 0;

	StringLength = strlen(termData->transactionDate);

	if (StringLength == NULL) {
#ifndef MAIN_APP
		printf("No date entered\n");
#endif
		return WRONG_DATE;
	}
	/*check the size of the entered date*/
	if (StringLength != 10) {
#ifndef MAIN_APP
		printf("Wrong date format\n\n");
		puts(termData->transactionDate);
#endif
		return WRONG_DATE;
	}
	else if (StringLength == 10) {
		/* check if the date format is valid*/
		if ((termData->transactionDate[2] != '/') || (termData->transactionDate[5] != '/')) {
#ifndef MAIN_APP
			printf("Wrong date format\n\n");
			puts(termData->transactionDate);
#endif
			return WRONG_DATE;
		}
		/*get the month and year to be compared with the global month and year*/
		for (int i = 0; i < StringLength; i++) {
			if (i < 2) {
				if ((termData->transactionDate[i] >= '0') && (termData->transactionDate[i] <= '9')) {
					uint8_t digit;
					digit = termData->transactionDate[i] - '0';
					day = day * 10 + digit;
				}
			}
			else if (i > 2 && i < 5) {
				if ((termData->transactionDate[i] > '0') && (termData->transactionDate[i] < '9')) {
					uint8_t digit;
					digit = termData->transactionDate[i] - '0';
					month = month * 10 + digit;
				}
			}
			else if (i > 7 && i < 10) {
				if ((termData->transactionDate[i] > '0') && (termData->transactionDate[i] < '9')) {
					uint8_t digit;
					digit = termData->transactionDate[i] - '0';
					year = year * 10 + digit;
				}
			}
		}
		if (day == g_day && month == g_month && year == g_year) {
#ifndef MAIN_APP
			printf("Terminal Date is OK\n\n");
#endif
			return TERMINAL_OK;
		}
		else {
#ifndef MAIN_APP
			printf("Wrong Date \n");
#endif
			return WRONG_DATE;
		}
	}
}

/**************************************************************/
/*********************** Test Functions ***********************/
/**************************************************************/

void getTransactionDateTest(void) {

	/* ASSUME TODAYS DATE IS 19/11/2022 */
	ST_terminalData_t terminalTest;
	uint8_t counter = 1;
	printf("Tester name : Andrew Ashraf Waheed\n");
	printf("Function Name : getTransactionDate\n\n");
	while (counter <= 3) {
		switch (counter) {
		case 1:
			strcpy_s(terminalTest.transactionDate, sizeof(terminalTest.transactionDate), "18/11/2022");
			printf("Test Case %d: \n", counter);
			printf("Input data: 18/11/2022 -> Wrong Date\n");
			printf("Expected Value : Wrong Date\n");
			printf("Atual Value : ");
			getTransactionDate(&terminalTest);
			printf("\n");
			break;
		case 2:
			strcpy_s(terminalTest.transactionDate, sizeof(terminalTest.transactionDate), "");
			printf("Test Case %d: \n", counter);
			printf("Input data: NULL\n");
			printf("Expected Value : NULL\n");
			printf("Atual Value : ");
			getTransactionDate(&terminalTest);
			printf("\n");
			break;
		case 3:
			strcpy_s(terminalTest.transactionDate, sizeof(terminalTest.transactionDate), "21/11/2022");
			printf("Test Case %d: \n", counter);
			printf("Input data: 21/11/2022 -> Today's Date\n");
			printf("Expected Value : Terminal Date is OK\n");
			printf("Atual Value : ");
			getTransactionDate(&terminalTest);
			printf("\n");
			break;
		}
		counter++;
	}
}


void isCardExpiredTest(void) {
	/* ASSUME TODAYS DATE IS 19/11/2022 */
	ST_terminalData_t terminalTest;
	ST_cardData_t cardTest;
	uint8_t counter = 1;
	printf("Tester name : Andrew Ashraf Waheed\n");
	printf("Function Name : isCardExpired\n\n");
	while (counter <= 2) {
		switch (counter) {
		case 1:
			strcpy_s(terminalTest.transactionDate, sizeof(terminalTest.transactionDate), "21/11/2022");
			strcpy_s(cardTest.cardExpirationDate, sizeof(cardTest.cardExpirationDate), "11/22");
			printf("Test Case %d: \n", counter);
			printf("Input Terminal data: 21/11/2022 -> Today's Date\n");
			printf("Input Card data :    11/22 \n");
			printf("Expected Value : Terminal is OK \n");
			printf("Atual Value : ");
			isCardExpired(&cardTest, &terminalTest);
			printf("\n");
			break;
		case 2:
			strcpy_s(terminalTest.transactionDate, sizeof(terminalTest.transactionDate), "21/11/2022");
			strcpy_s(cardTest.cardExpirationDate, sizeof(cardTest.cardExpirationDate), "10/21");
			printf("Test Case %d: \n", counter);
			printf("Input Terminal data: 21/11/2022 -> Today's Date\n");
			printf("Input Card data :    10/21 \n");
			printf("Expected Value : Expired Card  \n");
			printf("Atual Value : ");
			isCardExpired(&cardTest, &terminalTest);
			printf("\n");
			break;
		}
		counter++;
	}
}

void getTransactionAmountTest(void) {
	ST_terminalData_t terminalTest;
	uint8_t counter = 1;
	printf("Tester name : Andrew Ashraf Waheed\n");
	printf("Function Name : getTransactionAmount\n\n"); 
	while (counter <= 2) {
		switch (counter) {
		case 1 :
			terminalTest.transAmount = 1452.5;
			printf("Test Case %d: \n", counter);
			printf("Input : 1452.5\n");
			printf("Expected Value : Value is accepted \n");
			printf("Atual Value : ");
			getTransactionAmount(&terminalTest);
			printf("\n");
			break;
		case 2:
			terminalTest.transAmount = -1000.2;
			printf("Test Case %d: \n", counter);
			printf("Input : -1000.2\n");
			printf("Expected Value : Value is not accepted \n");
			printf("Atual Value : ");
			getTransactionAmount(&terminalTest);
			printf("\n");
			break;
		}
		counter++;
	}
}

void isBelowMaxAmountTest(void) {
	ST_terminalData_t terminalTest;
	uint8_t counter = 1;
	printf("Tester name : Andrew Ashraf Waheed\n");
	printf("Function Name : isBelowMaxAmount\n\n");
	while (counter <= 2) {
		switch (counter) {
		case 1:
			terminalTest.maxTransAmount = 1000;
			terminalTest.transAmount = 900;
			printf("Test Case %d: \n", counter);
			printf("Input max amount : 1000\n");
			printf("Input Transaction amount : 900\n");
			printf("Expected Value : APPROVED\n");
			printf("Atual Value : ");
			getTransactionAmount(&terminalTest);
			printf("\n");
			break;
		case 2:
			terminalTest.maxTransAmount = 900;
			terminalTest.transAmount = 1000;
			printf("Test Case %d: \n", counter);
			printf("Input max amount : 900\n");
			printf("Input Transaction amount : 1000\n");
			printf("Expected Value : NOT ACCEPTED\n");
			printf("Atual Value : NO ACCEPTED\n");
			getTransactionAmount(&terminalTest);
			printf("\n");
			break;
		}
		counter++;
	}
}

void setMaxAmountTest(void) {
	ST_terminalData_t terminalTest;
	int maxAmount = 1000;
	uint8_t counter = 1;
	printf("Tester name : Andrew Ashraf Waheed\n");
	printf("Function Name : setMaxAmount\n\n");
	while (counter <= 2) {
		switch (counter) {
		case 1:
			printf("Test Case %d: \n", counter);
			printf("Input max amount : 1000\n");
			printf("Expected Value : Max amount is set successfully\n");
			printf("Atual Value : ");
			setMaxAmount(&terminalTest, maxAmount);
			printf("\n");
			break;
		case 2:
			maxAmount = -1000;
			printf("Test Case %d: \n", counter);
			printf("Input max amount : -1000\n");
			printf("Expected Value : Amount not valid\n");
			printf("Atual Value : ");
			setMaxAmount(&terminalTest, maxAmount);
			printf("\n");
			break;
		}
		counter++;
	}
}