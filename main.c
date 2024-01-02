#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>


// Structure to store temporary data
struct temporarydata {
	char village[20];
	int snowThatDay;
};


// Function to read the day input
void readDay(int *day) {
	char input[10];
	printf("> Enter a day (1-8): \n");
	scanf("%9s", input);

	// Validate the input
	if (strlen(input) != 1 || (int)input[0] < '1' || (int)input[0] > '8') {
		fprintf(stderr, "Enter a whole digit from 1-8!");
		exit(EXIT_FAILURE);
	}

	*day = atoi(input);
}


// Function to read the village input
void readVillage(char *village) {
	printf("> Enter village:\n");
	scanf("%s", village);
}


// Function to extract data from a file based on village
void extractData(FILE **snowdata, char *line, size_t line_size, struct temporarydata *td, char* village) {
	while (fgets(line, line_size, *snowdata) != NULL) {
		// Parse data from the line using sscanf
		sscanf(line, "%19[^;];%d", td->village, &td->snowThatDay);

		// Check if the village matches the target village
		if (strcmp(td->village, village) == 0) {
			return; // Found the village, return from the function
		}
	}

	// Village not found, exit with an error message
	fprintf(stderr, "Village couldn't be found!");
	exit(EXIT_FAILURE);
}


int main() {
	int day = 0;
	int count = 1;
	char village[15] = "";
	char dataFile[50];
	char varFilename[50];
	int snowTotal = 0;

	// Read input values
	readVillage(village);
	readDay(&day);

	// Open the data storage file for writing
	FILE *totaldata;
	snprintf(dataFile, sizeof(dataFile), "snow_data\\%s_%d.txt", village, day);
	totaldata = fopen(dataFile, "w");

	// Check if the file is successfully opened
	if (totaldata == NULL) {
		fprintf(stderr, "Data storage file couldn't be created or opened!\n");
		exit(EXIT_FAILURE);
	}

	// Loop through each day
	while (count <= day) {
		char line[30];

		// Open the input data file for reading
		FILE *snowdata;
		snprintf(varFilename, sizeof(varFilename), "snow_data\\%d.txt", count);
		snowdata = fopen(varFilename, "r");

		// Check if the input data file is successfully opened
		if(snowdata == NULL) {
			fprintf(stderr, "Input data file couldn't be opened!");
			exit(EXIT_FAILURE);
		}

		// Structure to store temporary data
		struct temporarydata td;

		// Extract data based on the village from the input data file
		extractData(&snowdata, line, sizeof(line), &td, village);

		// Write results to the data storage file
		fprintf(totaldata, "Day %d: %dcm\n", count, td.snowThatDay);

		// Accumulate total snow
		snowTotal += td.snowThatDay;

		// Close the input data file
		fclose(snowdata);

		// Move to the next day
		count++;
	}

	// Print success message and write the total snow to the data storage file
	printf("> The results of your request were successfully written to the %s directory.\n", dataFile);
	fprintf(totaldata, "Sum: %dcm", snowTotal);

	// Close the data storage file
	fclose(totaldata);

	return 0;
}