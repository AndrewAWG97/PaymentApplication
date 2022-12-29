#include "card.h"


extern uint8_t g_month;
extern uint8_t g_year;


/* Enabling test functions by defining TEST_CASE */
//#define TEST_CASE
//#define TEST_CARD_TERMINAL
#define MAIN_APP

EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
	uint8_t StringLength;
#ifndef TEST_CASE
	printf("Please enter card's holder name : ");
	//strcpy_s(cardData->cardHolderName, sizeof(cardData->cardHolderName),"");
	fgets( cardData->cardHolderName, sizeof(cardData->cardHolderName), stdin);
#endif
	StringLength = strlen(cardData->cardHolderName);

	/*check if name is enetred correctly*/
	if (StringLength < 20 || (StringLength+1) >24){
#ifndef MAIN_APP
		printf("Wrong Name Format \n");
#endif
		return WRONG_NAME;
	}
	else if (StringLength == NULL) {
#ifndef MAIN_APP
		printf("Wrong Name \n");
#endif
		return WRONG_NAME;
	}
	else {
#ifndef MAIN_APP
		printf("Card is OK \n");
#endif
		return CARD_OK;
	}
}




EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
	uint8_t StringLength;
	uint8_t month = 0;
	uint8_t year = 0;
#ifndef TEST_CASE
	printf("Date format MM/YY ex: 02/22\n");
	printf("Please enter card expiration date : ");
	gets(cardData->cardExpirationDate);
#endif
	StringLength = strlen(cardData->cardExpirationDate);

	/*check the size of the entered date*/
	if (StringLength != 5) {
#ifndef MAIN_APP
		printf("Wrong date format\n");
#endif
		puts(cardData->cardExpirationDate);
		return WRONG_EXP_DATE;
	}
	else if(StringLength == 5) {
		/* check if the date format is valid*/
		if (cardData->cardExpirationDate[2] != '/') {
#ifndef MAIN_APP
			printf("Wrong date format\n");
#endif
			puts(cardData->cardExpirationDate);
			return WRONG_EXP_DATE;
		}
		/*get the month and year to be compared with the global month and year*/
		for (int i = 0; i < StringLength; i++) {
			if (i < 2) {
				if ((cardData->cardExpirationDate[i] > '0') && (cardData->cardExpirationDate[i] < '9')) {
					uint8_t digit;
					digit = cardData->cardExpirationDate[i] - '0';
					month = month * 10 + digit;
				}
			}
			else {
				if ((cardData->cardExpirationDate[i] > '0') && (cardData->cardExpirationDate[i] < '9')) {
					uint8_t digit;
					digit = cardData->cardExpirationDate[i] - '0';
					year = year * 10 + digit;
				}
			}
		}
		/*check if the date is bigger than 12*/
		if (month > 12) {
#ifndef MAIN_APP
			printf("Month is entered incorrectly\n");
#endif
			puts(cardData->cardExpirationDate);
			return WRONG_EXP_DATE;
		}
		/*check if the year is bigger than today's year*/
		if (year > g_year) {
#ifndef MAIN_APP
			printf("Card EXP DATE is OK\n");
			puts(cardData->cardExpirationDate);
#endif
			return CARD_OK;
		}else if(year == g_year && month > g_month) { /*checks if today's year but it's the next month*/
#ifndef MAIN_APP
			printf("Card EXP DATE is OK\n");
			puts(cardData->cardExpirationDate);
#endif
			return CARD_OK;
		}
		else if (year == g_year && month == g_month) { /*check if it's today's exact month and year*/
#ifndef MAIN_APP
			printf("Card EXP DATE is OK\n");
			puts(cardData->cardExpirationDate);
#endif
			return CARD_OK;
		}
		else {
#ifndef MAIN_APP
			printf("Card Expiration date is out of date\n");
			puts(cardData->cardExpirationDate);
#endif
			return WRONG_EXP_DATE;
		}
	}
	else if (StringLength == NULL) {
#ifndef MAIN_APP
		printf("Date is NULL\n\n");
#endif
		return WRONG_EXP_DATE;
	}
}

EN_cardError_t cmpCardExpiryDate(ST_cardData_t* cardData) {
	uint8_t StringLength;
	uint8_t month = 0;
	uint8_t year = 0;

	StringLength = strlen(cardData->cardExpirationDate);

	/*check the size of the entered date*/
	if (StringLength != 5) {
#ifndef MAIN_APP
		printf("Wrong date format\n");
#endif
		puts(cardData->cardExpirationDate);
		return WRONG_EXP_DATE;
	}
	else if (StringLength == 5) {
		/* check if the date format is valid*/
		if (cardData->cardExpirationDate[2] != '/') {
#ifndef MAIN_APP
			printf("Wrong date format\n");
#endif
			puts(cardData->cardExpirationDate);
			return WRONG_EXP_DATE;
		}
		/*get the month and year to be compared with the global month and year*/
		for (int i = 0; i < StringLength; i++) {
			if (i < 2) {
				if ((cardData->cardExpirationDate[i] > '0') && (cardData->cardExpirationDate[i] < '9')) {
					uint8_t digit;
					digit = cardData->cardExpirationDate[i] - '0';
					month = month * 10 + digit;
				}
			}
			else {
				if ((cardData->cardExpirationDate[i] > '0') && (cardData->cardExpirationDate[i] < '9')) {
					uint8_t digit;
					digit = cardData->cardExpirationDate[i] - '0';
					year = year * 10 + digit;
				}
			}
		}
		/*check if the date is bigger than 12*/
		if (month > 12) {
#ifndef MAIN_APP
			printf("Month is entered incorrectly\n");
#endif
			puts(cardData->cardExpirationDate);
			return WRONG_EXP_DATE;
		}
		/*check if the year is bigger than today's year*/
		if (year > g_year) {
#ifndef MAIN_APP
			printf("Card EXP DATE is OK\n");
			puts(cardData->cardExpirationDate);
#endif
			return CARD_OK;
		}
		else if (year == g_year && month > g_month) { /*checks if today's year but it's the next month*/
#ifndef MAIN_APP
			printf("Card EXP DATE is OK\n");
			puts(cardData->cardExpirationDate);
#endif
			return CARD_OK;
		}
		else if (year == g_year && month == g_month) { /*check if it's today's exact month and year*/
#ifndef MAIN_APP
			printf("Card EXP DATE is OK\n");
			puts(cardData->cardExpirationDate);
#endif
			return CARD_OK;
		}
		else {
#ifndef MAIN_APP
			printf("Card Expiration date is out of date\n");
			puts(cardData->cardExpirationDate);
#endif
			return WRONG_EXP_DATE;
		}
	}
	else if (StringLength == NULL) {
#ifndef MAIN_APP
		printf("Date is NULL\n\n");
#endif
		return WRONG_EXP_DATE;
	}
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
	uint8_t StringLength;
#ifndef TEST_CASE
	printf("Please enter card PAN : ");
	fgets(cardData->primaryAccountNumber, sizeof(cardData->primaryAccountNumber), stdin);
	//gets(cardData->primaryAccountNumber);
#endif
	StringLength = strlen(cardData->primaryAccountNumber);
	/*check if the PAN is entered correctly*/
	if (StringLength < 16 || StringLength > 19) {
#ifndef MAIN_APP
		printf("Wrong PAN format\n");
#endif
		return WRONG_PAN;
	}
	else if ((StringLength >= 16) && (StringLength <= 19)) {
		/* check if the PAN is valid*/
		for (int i = 0; i < StringLength; i++) {
			if ( (cardData->primaryAccountNumber[i] < '0') || (cardData->primaryAccountNumber[i] > '9') ) {
#ifndef MAIN_APP
				printf("PAN number is entered incorrectly\n");
#endif
				return WRONG_PAN;
			}
		}
#ifndef MAIN_APP
		printf("PAN number is correct\n\n");
#endif
		return CARD_OK;
	}
}



 /***************************************
 ************** Test Functions **********
 ***************************************/

void getCardHolderNameTest(void) {
	ST_cardData_t cardTest;
	uint8_t counter = 1;
	printf("Tester name : Andrew Ashraf Waheed\n");
	printf("Function Name : getCardHolderName\n\n");
	while (counter <= 4) {
		switch (counter) {
		case 1:
			strcpy_s(cardTest.cardHolderName, sizeof(cardTest.cardHolderName), "Andrew Ashraf");
			printf("Test Case %d: \n", counter);
			printf("Input data: Andrew Ashraf -> Name less than 20 characters\n");
			printf("Expected Value : Wrong Name\n");
			printf("Atual Value : ");
			getCardHolderName(&cardTest);
			printf("\n");
			break;
		case 2:
			strcpy_s(cardTest.cardHolderName, sizeof(cardTest.cardHolderName), "");
			printf("Test Case %d: \n", counter);
			printf("Input data: NULL-> No Name\n");
			printf("Expected Value : Wrong Name\n");
			printf("Atual Value : ");
			getCardHolderName(&cardTest);
			printf("\n");
			break;
		case 3:
			strcpy_s(cardTest.cardHolderName, sizeof(cardTest.cardHolderName), "Andrew Ashraf Waheed");
			printf("Test Case %d: \n", counter);
			printf("Input data: Andrew Ashraf Waheed -> Name is Correct\n");
			printf("Expected Value : Card is OK\n");
			printf("Atual Value : ");
			getCardHolderName(&cardTest);
			printf("\n");
			break;
		case 4:
			strcpy_s(cardTest.cardHolderName, sizeof(cardTest.cardHolderName), "Andrew Ashraf Waheed Jac");
			printf("Test Case %d: \n", counter);
			printf("Input data: Andrew Ashraf Waheed Jac-> Name is not correct exceeding 24 characters\n");
			printf("Expected Value : Wrong Name\n");
			printf("Atual Value : ");
			getCardHolderName(&cardTest);
			printf("\n");
			break;
		}
		counter++;
	}
}

void getCardExpiryDateTest(void) {
	ST_cardData_t cardTest;
	uint8_t counter = 1;
	printf("Tester name : Andrew Ashraf Waheed\n");
	printf("Function Name : getCardExpiryDate\n\n");
	while (counter <= 8) {
		switch (counter) {
		case 1:
			strcpy_s(cardTest.cardExpirationDate, sizeof(cardTest.cardExpirationDate), "03-23");
			printf("Test Case %d: \n", counter);
			printf("Input data: 03-23 -> Wrong Date Format\n");
			printf("Expected Value : Wrong Date\n");
			printf("Atual Value : ");
			getCardExpiryDate(&cardTest);
			printf("\n");
			break;
		case 2:
			strcpy_s(cardTest.cardExpirationDate, sizeof(cardTest.cardExpirationDate), "1234");
			printf("Test Case %d: \n", counter);
			printf("Input data: 1234 -> Wrong Date\n");
			printf("Expected Value : Wrong Date\n");
			printf("Atual Value : ");
			getCardExpiryDate(&cardTest);
			printf("\n");
			break;
		case 3:
			strcpy_s(cardTest.cardExpirationDate, sizeof(cardTest.cardExpirationDate), "02/22");
			printf("Test Case %d: \n", counter);
			printf("Input data: 02/22 -> Old date\n");
			printf("Expected Value : Card expired\n");
			printf("Atual Value : ");
			getCardExpiryDate(&cardTest);
			printf("\n");
			break;
		case 4:
			strcpy_s(cardTest.cardExpirationDate, sizeof(cardTest.cardExpirationDate), "");
			printf("Test Case %d: \n", counter);
			printf("Input data: NULL -> no date\n");
			printf("Expected Value : Wrong Date Format\n");
			printf("Atual Value : ");
			getCardExpiryDate(&cardTest);
			printf("\n");
			break;
		case 5:
			strcpy_s(cardTest.cardExpirationDate, sizeof(cardTest.cardExpirationDate), "11/22");
			printf("Test Case %d: \n", counter);
			printf("Input data: 11/22-> Today's date\n");
			printf("Expected Value : Card OK\n");
			printf("Atual Value : ");
			getCardExpiryDate(&cardTest);
			printf("\n");
			break;
		case 6:
			strcpy_s(cardTest.cardExpirationDate, sizeof(cardTest.cardExpirationDate), "12/22");
			printf("Test Case %d: \n", counter);
			printf("Input data: 12/22 -> Same year Next month\n");
			printf("Expected Value : Card OK\n");
			printf("Atual Value : ");
			getCardExpiryDate(&cardTest);
			printf("\n");
			break;
		case 7:
			strcpy_s(cardTest.cardExpirationDate, sizeof(cardTest.cardExpirationDate), "02/23");
			printf("Test Case %d: \n", counter);
			printf("Input data: 02/23 -> Next Year\n");
			printf("Expected Value : Card OK\n");
			printf("Atual Value : ");
			getCardExpiryDate(&cardTest);
			printf("\n");
			break;
		case 8:
			strcpy_s(cardTest.cardExpirationDate, sizeof(cardTest.cardExpirationDate), "13/23");
			printf("Test Case %d: \n", counter);
			printf("Input data: 13/23 -> Month > 12\n");
			printf("Expected Value : Month is entered incorrectly\n");
			printf("Atual Value : ");
			getCardExpiryDate(&cardTest);
			printf("\n");
			break;

		}
		counter++;
	}
}

void getCardPANTest(void) {
	ST_cardData_t cardTest;
	uint8_t counter = 1;
	printf("Tester name : Andrew Ashraf Waheed\n");
	printf("Function Name : getCardPAN\n\n");
	while (counter <= 5) {
		switch (counter) {
		case 1:
			strcpy_s(cardTest.primaryAccountNumber, sizeof(cardTest.primaryAccountNumber), "100020003000");
			printf("Test Case %d: \n", counter);
			printf("Input data: 100020003000 -> Wrong Number less than 16 char\n");
			printf("Expected Value : Wrong Number\n");
			printf("Atual Value : ");
			getCardPAN(&cardTest);
			printf("\n");
			break;
		case 2:
			strcpy_s(cardTest.primaryAccountNumber, sizeof(cardTest.primaryAccountNumber), "100020003000400a");
			printf("Test Case %d: \n", counter);
			printf("Input data: 100020003000400a -> Number entered incorrecly\n");
			printf("Expected Value :  Number entered incorrecly\n");
			printf("Atual Value : ");
			getCardPAN(&cardTest);
			printf("\n");
			break;
		case 3:
			strcpy_s(cardTest.primaryAccountNumber, sizeof(cardTest.primaryAccountNumber), "1000200030004000100");
			printf("Test Case %d: \n", counter);
			printf("Input data: 1000200030004000100 -> Max Number of char\n");
			printf("Expected Value : Correct Number\n");
			printf("Atual Value : ");
			getCardPAN(&cardTest);
			printf("\n");
			break;
		case 4:
			strcpy_s(cardTest.primaryAccountNumber, sizeof(cardTest.primaryAccountNumber), "1000200030004000");
			printf("Test Case %d: \n", counter);
			printf("Input data: 1000200030004000 -> 16 Number entered\n");
			printf("Expected Value : Correct Number\n");
			printf("Atual Value : ");
			getCardPAN(&cardTest);
			printf("\n");
			break;
		case 5:
			strcpy_s(cardTest.primaryAccountNumber, sizeof(cardTest.primaryAccountNumber), "");
			printf("Test Case %d: \n", counter);
			printf("Input data: NULL\n");
			printf("Expected Value : NULL\n");
			printf("Atual Value : ");
			getCardPAN(&cardTest);
			printf("\n");
			break;
		}
		counter++;
	}
}
