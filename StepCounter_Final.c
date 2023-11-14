#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

#define BUFFER_SIZE 1000
FITNESS_DATA records[12000];

// Struct moved to header file
// Define any additional variables here
// Global variables for filename and FITNESS_DATA array
// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {        strcpy(date, token);
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
FILE *open_file(const char *filename, const char *mode) {
    FILE *file = fopen(filename, mode);
    if (file == NULL) {
        perror("There is an error in the file");
        exit(1);
    }
    return file;
}

void importFile(const char *filename, FITNESS_DATA records[], int *totalRecords) {
    FILE *file = open_file(filename, "r");
    char line[100], date[11], time[6], steps[10];
    const char *delimiter = ",";
    int recordsRead = 0;

    while (fgets(line, sizeof(line), file) != NULL && recordsRead < 12000) {
        tokeniseRecord(line, delimiter, date, time, steps);
        strcpy(records[recordsRead].date, date);
        strcpy(records[recordsRead].time, time);
        records[recordsRead].steps = atoi(steps);
        recordsRead++;
    }

    *totalRecords = recordsRead;
    fclose(file);
}

// Complete the main function
int main() {
    char choice;
    char filename[BUFFER_SIZE];
    int totalRecords = 0;

    do {
        printf("\nA: Specify the filename to be imported\n"
               "B: Display the total number of records in the file\n"
               "C: Find the date and time of the time slot with the fewest steps\n"
               "D: Find the data and time of the time slot with the largest number of steps\n"
               "E: Find the mean step count of all the records in the file\n"
               "F: Find the longest continuous period where the step count is above 500 steps\n"
               "Q: Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case 'A': {
                printf("Input filename: ");
                scanf("%s", filename);
                file = fopen(filename, "r");
                if (file == NULL) {
                    printf("Error: could not open file\n");
                    break;
                }
                importFile(filename, records, &totalRecords);
                printf("Data imported successfully!\n");
                fclose(file);
                break;
            }
            case 'B':
                printf("Total records: %d\n", totalRecords);
                break;
            case 'C': {
                int minSteps = records[0].steps;
                int index = 0;

                for (int i = 1; i < totalRecords; ++i) {
                    if (records[i].steps < minSteps) {
                        minSteps = records[i].steps;
                        index = i;
                    }
                }
                printf("Date and time of the timeslot with the fewest steps: %s %s\n", records[index].date, records[index].time);
                break;
            }
            case 'D': {
                int maxSteps = records[0].steps;
                int index = 0;

                for (int i = 1; i < totalRecords; ++i) {
                    if (records[i].steps > maxSteps) {
                        maxSteps = records[i].steps;
                        index = i;
                    }
                }
                printf("Date and time of the timeslot with the largest number of steps: %s %s\n", records[index].date, records[index].time);
                break;
            }
            case 'E': {
                int totalSteps = 0;
                for (int i = 0; i < totalRecords; ++i) {
                    totalSteps += records[i].steps;
                }
                int meanSteps = totalSteps / totalRecords;
                printf("Mean step count of all the records in the file: %d\n", meanSteps);
                break;
            }
            case 'F': {
                int start = -1, end = -1;
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
                        currentPeriod = 0;
                    }
                }

                if (start != -1 && end != -1) {
                    printf("Longest continuous period where the step count is above 500 steps:\n");
                    printf("Start time: %s %s\n", records[start].date, records[start].time);
                    printf("End time: %s %s\n", records[end].date, records[end].time);
                } else {
                    printf("No continuous period where the step count is above 500 steps.\n");
                }
                break;
            }
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