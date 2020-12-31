#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

/*
struct tm {
		int tm_sec;          seconds,  range 0 to 59          
		int tm_min;          minutes, range 0 to 59          
		int tm_hour;         hours, range 0 to 23           
		int tm_mday;         day of the month, range 1 to 31
		int tm_mon;          month, range 0 to 11          
		int tm_year;         The number of years since 1900
		int tm_wday;         day of the week, range 0 to 6
		int tm_yday;         day in the year, range 0 to 365
		int tm_isdst;        daylight saving time     
};
*/
int main (int argc, char **argv) {
	FILE *fp;
	char fName[] = "log.txt";

	fp = fopen(fName, "a");

	if (fp == NULL) {
		fprintf(stderr, "Error opening file %s for appending\n", fName);
		perror("Error");
		exit(EXIT_FAILURE);
	}

	time_t start, finish;

	start = time(NULL);

	struct tm* date;
	date = localtime(&start);
	
	char buffer[80];
	int bufferSize = 80;

	while (1) {
		fgets(buffer, bufferSize, stdin);
		buffer[strlen(buffer) - 1] = '\0';
		if (strcmp(buffer, "stop") == 0)
			break;
	}

	finish = time(NULL);
	
	double tdiff = difftime(finish, start);

	fprintf(fp, "%02i/%02i/%i\t%02i:%02i\t%i\n", date->tm_mday, date->tm_mon, date->tm_year + 1900, date->tm_hour, date->tm_min, (int)(tdiff / 60));

	fclose(fp);

	return 0;
}

