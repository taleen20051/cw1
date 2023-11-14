#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

// Struct moved to header file
#define MAX_FILENAME_LENGTH 50
#define MAX_RECORDS 1000
// Define any additional variables here
// Global variables for filename and FITNESS_DATA array
char filename[MAX_FILENAME_LENGTH];
FITNESS_DATA records[MAX_RECORDS];
int totalRecords = 0;

// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {        
        strcpy(date, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(steps, token);
    }
    
    // Free the duplicated string
    free(inputCopy);

}

FITNESS_DATA fitness_data[12000];
FILE *open_file(char filename[], char mode[]) {
    FILE *file = fopen("FitnessData_2023.csv", "r");
    
    if (file == NULL) {
        perror("There is an error in the file");
        exit(1);
    }
    return file;
}


// Complete the main function
int main() {
   char choice;

    do {
        printf("\nA: Specify the filename to be imported\n"
               "B: Display the total number of records in the file\n"
               "C: Find the date and time of the timeslot with the fewest steps\n"
               "D: Find the date and time of the timeslot with the largest number of steps\n"
               "E: Find the mean step count of all the records in the file\n"
               "F: Find the longest continuous period where the step count is above 500 steps\n"
               "Q: Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case 'A':
                importFile();
                totalRecords = 0;
            while (fgets(date, time, steps))
            {
                // split up the line and store it in the right place
                // using the & operator to pass in a pointer to the bloodIron so it stores it
                tokeniseRecord(choice, ",", fitness_data[totalRecords].date, &fitness_data[totalRecords].time, fitness_data[totalRecords].steps);
                totalRecords++;
            }
            for (int i = 0; i < totalRecords; i++)
            {
                printf("%s - Blood iron: %.1f\n", fitness_data[i].date, fitness_data[i].time, fitness_data[i].steps)
            fclose(input);
            break;

            case 'B':
                displayTotalRecords();
                break;
            case 'C':
                findFewestSteps();
                break;
            case 'D':
                findLargestSteps();
                break;
            case 'E':
                findMeanStepCount();
                break;
            case 'F':
                findLongestPeriod();
                break;
            case 'Q':
                printf("Program returns 0 & exits.\n");
                exit(0);
                break;
            default:
                printf("Invalid choice. Please select a valid option.\n");
        }
    } while (1);

    return 0;
}

void importFile() {
    FILE *file;
    char line[100], date[11], time[6], steps[10];
    const char *delimiter = ",";
    int recordsRead = 0;

    printf("Input filename: ");
    scanf("%s", filename);

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: could not open file\n");
        return;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        if (recordsRead < MAX_RECORDS) {
            tokeniseRecord(line, delimiter, date, time, steps);
            strcpy(records[recordsRead].date, date);
            strcpy(records[recordsRead].time, time);
            records[recordsRead].steps = atoi(steps);
            recordsRead++;
        } else {
            printf("Maximum records exceeded. Ignoring additional entries.\n");
            break;
        }
    }

    totalRecords = recordsRead;
    fclose(file);
}

void displayTotalRecords() {
    printf("Total records: %d\n", totalRecords);
}

void findFewestSteps() {
    int minSteps = records[0].steps;
    int index = 0;

    for (int i = 1; i < totalRecords; ++i) {
        if (records[i].steps < minSteps) {
            minSteps = records[i].steps;
            index = i;
        }
    }

    printf("Fewest steps: %s %s\n", records[index].date, records[index].time);
}

void findLargestSteps() {
    int maxSteps = records[0].steps;
    int index = 0;

    for (int i = 1; i < totalRecords; ++i) {
        if (records[i].steps > maxSteps) {
            maxSteps = records[i].steps;
            index = i;
        }
    }

    printf("Largest steps: %s %s\n", records[index].date, records[index].time);
}

void findMeanStepCount() {
    int totalSteps = 0;

    for (int i = 0; i < totalRecords; ++i) {
        totalSteps += records[i].steps;
    }

    int meanSteps = totalSteps / totalRecords;
    printf("Mean step count: %d\n", meanSteps);
}

void findLongestPeriod() {
    int start = 0, end = 0;
    int longestPeriod = 0;
    int currentPeriod = 0;

    for (int i = 0; i < totalRecords; ++i) {
        if (records[i].steps > 500) {
            if (currentPeriod == 0) {
                start = i;
            }
            currentPeriod++;
        } else {
            if (currentPeriod > longestPeriod) {
                longestPeriod = currentPeriod;
                end = i - 1;
            }
}
    }
}