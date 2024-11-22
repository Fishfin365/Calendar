// if you use this after year 10000 it will break
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>


// ***** directions ********
// if you run it with no input, it with output the current month calendar
// if you run it with 2 inputs (the file, and the year), it will output the whole calendar year of the year inputted
//options
//1. if you have 3 inputs (the file, the year, and the month) it will give that months calendar in the inputted year (like july of 2007)
//2. if you input file, -m (this means it is leaving the year open), then month, it will output the month of this year 
//3. if you input cal, -m, and the first 3 letters of the month (jul, may, dec) it will output the month of this year
//1. if you run it with 4 inputs, file, -m, month, year (cal, -m, FEb, 2020)
//2. file, -m, 5, 2024,  this will output the month of that year
//with the shortened month the casing will not matter, it also can be longer it should still work
// if the month is outside 1-12 it will error


//constants to check the months, days in each month and the 3 letter shortened month
char *months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
char *firstThreeMonth[12] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
int dateList[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


/*
 * findCurrentMonth uses the time library to find the current month
 *
 * int: returns the current month of the year that is it
 */
int findCurrentMonth(){
    //returns current month in integer form
    time_t timenow;

    struct tm *current;

    //check the time function documentation
    time (&timenow);

    //returns address to struct tim, so tm needs to be address
    current = localtime (&timenow);

    int currentMonth = current->tm_mon+1;
    return currentMonth;
}


/*
 * findCurrentYear checks to see what year it is using the time library
 * 
 * int: it returns the current year 
 */
int findCurrentYear(){
    //returns current year in integer form
    time_t timenow;

    struct tm *current;

    //check the time function documentation
    time (&timenow);

    //returns address to struct tim, so tm needs to be address
    current = localtime (&timenow);

    int currentYear = current->tm_year+1900;
    return currentYear;
}


/*
 * yearLength will check the inputted year and see how many digits are in it and return if it is a valid year
 *
 * int year: the year that checked to see if it is a valid year
 * int: if year is 1 digit it will return 1, if it is 2 digits it will return 2, if it is 3 digits it will return 3 
 * and if it is 4 digits it will return 4. if it is not within any of these it will return 0
 */
int yearLength(int year){
	int yearL = 0;
	if (year < 10){// if its 1 digit long
		yearL = 1;
	}
	else if (year < 100) { // if it is 2 digits long
		yearL = 2;
	}
	if (year < 1000){
		yearL = 3;
	}
	else if (year < 10000) {
		yearL = 4;
	}
	else {
		yearL = 0;
	}
	return yearL;
}

/*
 * isLeapyear checks the inputted year to see if it is a leapyear. it returns a 1 if it is and 0 if it isnt
 *
 * int year: the integer value between 1753 - 9999 that represents the year of which you want the month printed
 * int : returns 1 if it is a leapyear and 0 if it is not a leapyear
 */
int isLeapyear(int year){
	// this will return 1 if it is a leap year
	// and 0 if it is not a leap year
	if (year % 4 == 0 && (year % 100 != 0) || year % 400 == 0){return 1;}
	else {return 0;}
}

/*
 * this function and return what day of the week it is based on the month day year inputted. it also checks to 
 * see if the day/month/year is a valid date
 *
 * int month: the integer between 1 - 12 that is representing the month you want printed
 * int year: the integer value between 1753 - 9999 that represents the year of which you want the month printed
 */
int date(int month, int day, int year){
	if (isLeapyear(year) == 1){
		dateList[1] = 29;
	}
	if (year<1753 || month<1 || month >12 || day< 1 || day >dateList[month-1]){
		printf("Not a valid date\n");
	}
	// add up all the days since the invention of the gregorian calendar, till now, then do it mod 7
	int acc_days = 0;
	for (int i = 1753; i < year; i++){
		//acc_days = acc_days + 365;
		if (isLeapyear(i) == 1) {
			acc_days += 366;
		}
		else {
			acc_days += 365;
		}
	}
	//int total_days = 0;
	// add up all the months
	for (int j = 0; j < month-1; j++) {
		acc_days += dateList[j];
	}
	//printf(" %d\n", acc_days%7);
	return acc_days%7;
}

/*
 * printMonth will print out the month of the inputted month and year
 *
 * int month: the integer between 1 - 12 that is representing the month you want printed
 * int year: the integer value between 1753 - 9999 that represents the year of which you want the month printed
 */
int printMonth(int month, int year){

int firstDay = date(month, 1, year);
char *mon = months[month-1];

int length2 = yearLength(year);
int length = strlen(mon); // this will give the lenght of the month
int totalLen = 20;
int spaces = (totalLen - (length+length2+1))/2; // this is the total spaces before you start printing the month
for (int k = 0; k < spaces; k++){
	printf(" ");
}
printf("%s", mon);
printf(" ");
printf("%d", year);
printf("\n");

printf("Su Mo Tu We Th Fr Sa\n");

	//int firstDay = date(month, 1, year);
	//printf("%d\n", firstDay);     testing which day is the first day of the month
	if (firstDay != 6){
		for (int z = 0; z <= firstDay;z++){
			printf("   ");
		}
	}

for (int l = 1; l <= 31; l++) {
	printf ("%2d",l);
	printf(" ");
	if ((firstDay+1+l)%7 == 0){
		printf("\n");
	}
}
return 0;
}



/*
 * printYear function will print out the full calendar year of the inputted year in the correct formatting
 *
 * int year: this will be a valid year from 1753 - 9999 technically
 */
//DONE
int printYear(int year){
	int fullLength = 64;
	int year_Length = 4;
	int halfwayLen = 30;
	int currentPrintingMonth = 0;
	int currentPrintingMonth1 = 0;
	
	for(int i = 0; i < 30;i++){ // printing out the year centered on the top
		printf(" ");
	}
	printf("%d", year);
	for(int j = 0; j < 30; j++){
		printf(" ");
	}
	printf("\n");
	for(int i = 1; i < 5; i++){ //print each row for the year with 3 months in each
			
			int spaceCount[3];
			int monthNum[3];
			int firstDay[3];
			monthNum[0] = 0;
			spaceCount[0] = 0;	// variables that are stored to make calculating the printing part easier
			monthNum[1] = 0;
			spaceCount[1] = 0;
			monthNum[2] = 0;
			spaceCount[2] = 0;
			int numCount = 0;
			int rowCounter = 0; // this is the counter to make sure that we dont print the same row 
						 // a bunch and mess uo the whole calendar
			bool flag = true;


			while(flag == true){
			if (rowCounter == 0) { // this will print the top of each month with the written month
				for (int l = 0; l < 3; l++){ // this is to make sure it can change the month as it moves to each month
					int oneTotal = 20;
					int monthLength = strlen(months[currentPrintingMonth]);
					int FRspaces = ((oneTotal-monthLength)/2);
					int RRspaces = ((FRspaces+monthLength)/2);
					for (int n = 0; n < FRspaces;n++){//printing spaces in front of the month
						printf(" ");
					}
					printf("%s", months[currentPrintingMonth+l]);
					for (int m = 0; m < RRspaces+2; m++){ //printing the spaces after the month
						printf(" ");
					}
				}
				printf("\n");
				rowCounter += 1;
			}

			//printf("\n");
			else if (rowCounter == 1){ // this will print the days of the week
				for (int tr = 0; tr < 3; tr++){
					printf("Su Mo Tu We Th Fr Sa  ");
				}
				printf("\n");
				rowCounter += 1;
			}

			else if (rowCounter == 2){ // this will print out each number in the month at the correct spot
					if (numCount == 0) { // if its the first row where we have to deal with spaces
						for (int k = 0; k < 3; k++){ // needs to go through with numbers for each month
							firstDay[k] = date(currentPrintingMonth+1, 1, year); //figures out which day each month starts on
							spaceCount[k] = firstDay[k] + 1; 
							int days = 0;
							
							if (firstDay[k] != 6){
								for (int z = 0; z <= firstDay[k];z++){ // this prints the spaces on the first line
									printf("   ");
								}
							}
							if(spaceCount[k]==7){
									spaceCount[k] = 0;
									monthNum[k] = 7;
							}
							for (int u = 1; u <= 7; u++){ // this prints the numbers on the first line
								if ((spaceCount[k]+u) <= 7){
									printf("%2d", u);
									printf(" ");
									days += 1;
								}
								else{
									monthNum[k] = days;
								}
							}
							printf(" ");
							currentPrintingMonth += 1;
						}
						printf("\n");
						numCount +=1;
					}

					else if(numCount == 1){ // this will print the normal lines that are full in the calendar
						for (int o = 0; o < 5;o++){
							int weekDays = 0;
							for (int y = 0; y < 3; y++){
								int loopCount = 0;
								for (int t = 1; t < 8; t++){
									if (dateList[currentPrintingMonth1+y] == monthNum[weekDays]){
										for (int finish = loopCount; finish < 7; finish++){
											printf("  ");
											printf(" ");
										}
										break;
									}
									loopCount += 1;
									printf("%2d", monthNum[weekDays]+1);
									printf(" ");
									monthNum[weekDays] += 1;
								}
								weekDays += 1;
								printf(" ");
							}
							printf("\n");
						}
						numCount +=1;
						currentPrintingMonth1 += 3;
					}

					else{
						rowCounter +=1;
					}
			}
			else{
				printf("\n");
				//printf("\n");
				flag = false;
			}
		}
	}
	return 0;
}

/*
 * 
 * this function will check the inputted string, and see if the first three characters 
 * match the first 3 characters of any month. it doesnt matter the case for the inputted value
 *
 *char input[]: this is the string that can be any length or case, that the function will check against 
 * 				months of the year
 *int: this output will be the corresponding number that the month is ( like 1 for january, 2 for febuary, etc...)
 *
 */

int checkFirstThree(char input[]){

	char upperInput[4];
	for (int new = 0; new < 3; new++){
		upperInput[new] = input[new];
	}
	for (int up = 0; up < 3; up++){
		upperInput[up] = toupper(input[up]);
		//printf("%s", upperInput[up]);
	}

	if (strcmp(upperInput, firstThreeMonth[0]) == 0){ // checking the inputted string against the first 3 of eahc month
		return 1; // returns the number that the month is for printMonth or printYear to use
	}
	else if (strcmp(upperInput, firstThreeMonth[1]) == 0){
		return 2;
	}
	else if (strcmp(upperInput, firstThreeMonth[2]) == 0){
		return 3;
	}
	else if (strcmp(upperInput, firstThreeMonth[3]) == 0){
		return 4;
	}
	else if (strcmp(upperInput, firstThreeMonth[4]) == 0){
		return 5;
	}
	else if (strcmp(upperInput, firstThreeMonth[5]) == 0){
		return 6;
	}
	else if (strcmp(upperInput, firstThreeMonth[6]) == 0){
		return 7;
	}
	else if (strcmp(upperInput, firstThreeMonth[7]) == 0){
		return 8;
	}
	else if (strcmp(upperInput, firstThreeMonth[8]) == 0){
		return 9;
	}
	else if (strcmp(upperInput, firstThreeMonth[9]) == 0){
		return 10;
	}
	else if (strcmp(upperInput, firstThreeMonth[10]) == 0){
		return 11;
	}
	else if (strcmp(upperInput, firstThreeMonth[11]) == 0){
		return 12;
	}
	else {
		return 30;
	}
	return 0;
}



int main(int argc, char *argv[]){ // parsing for
	int x = findCurrentMonth();
	int y = findCurrentYear();
	if (argc == 1) {
		//prints out current month and year (only inputted the file name)
		printMonth(x,y);
	}
	else if (argc == 2) {
		if (0 < atoi(argv[1]) && atoi(argv[1]) <= 9999){
			//prints out the entire year that was inputted
			printYear(atoi(argv[1]));
		}
		else {
			printf("Enter a proper year\n");
		}
	}
	else if (argc == 3) {
		if ((strcmp(argv[1],"-m") == 0) && (atoi(argv[2]) < 13) && (atoi(argv[2]) > 0)) {
			//get the current year (louis shall provide)
			//print out the inputted month with the  current year);
			printMonth(atoi(argv[2]),y);
		}
		else if (strcmp(argv[1],"-m") == 0 && argv[2]){
			// first 3 letters, if they match the first 3 of a month)
			// write a function to check and see if the first 3 letters match the first 3 of any month
			// if it does print out month with current year
			if (checkFirstThree(argv[2]) != 30) {
				// if the first 3 does match, print out that month in the current year
				printMonth(checkFirstThree(argv[2]), y);
			}
			else {
				//error if input doesnt match any month
				printf("Please enter a valid month");
			}
		}
		else if(atoi(argv[1]) > 0 && atoi(argv[1]) < 13 && atoi(argv[2]) > 0 && atoi(argv[2]) <= 9999){
			// inputted file, month, year
			printMonth(atoi(argv[1]), atoi(argv[2]));
		}
		else {
			//error
			printf("Error");
		}
	}
	else if (argc == 4) {
			if (strcmp(argv[1], "-m") == 0 && (checkFirstThree(argv[2])<13 && checkFirstThree(argv[2])>0) && (0<atoi(argv[3]) && atoi(argv[3]) <9999)){
				printMonth(checkFirstThree(argv[2]),atoi(argv[3]));
			}
			else if ((strcmp(argv[1], "-m")==0) && ((0<atoi(argv[2])) && (atoi(argv[2])<13)) && ((0<atoi(argv[3])) && (atoi(argv[3])<9999))){
				printMonth(atoi(argv[2]), atoi(argv[3]));
			}
			else {
				printf("Error");
			}
		}
	else {
		printf("invalid input\n");
	}
return 0;
}