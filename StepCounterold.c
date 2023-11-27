#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "FitnessDataStruct.h"

#define MAX_RECORDS 12000
FITNESS_DATA records[MAX_RECORDS];

void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    char *inputCopy = strdup(input);
    
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
    
    free(inputCopy);
}

void displayMenu() {
    printf("\nA: Specify the filename to be imported\n"
           "B: Display the total number of records in the file\n"
           "C: Find the date and time of the timeslot with the fewest steps\n"
           "D: Find the date and time of the timeslot with the largest number of steps\n"
           "E: Find the mean step count of all the records in the file\n"
           "F: Find the longest continuous period where the step count is above 500 steps\n"
           "Q: Quit\n");
    printf("Enter choice: ");
}

int main() {
    char line[MAX_RECORDS];
    char filename[MAX_RECORDS];
    int totalRecords = 0;
    char choice;
    float mean = 0;

    while (1) {
        displayMenu();
        scanf(" %c", &choice);
        while (getchar() != '\n')

        switch (choice)
        {
            case 'A':
            case 'a':  {
                printf("Input filename: ");
                scanf("%s", filename);
                FILE *input = fopen(filename, "r");
                if (!input)
                {
                    printf("Error: The file does not exist or cannot be opened.\n");
                    return 1;
                }
                totalRecords = 0;
                while (fgets(line, MAX_RECORDS, input)){
                    char charSteps[100];
                    tokenoiseRecord(line, ",", records[totalRecords].date, records[totalRecords].time, charSteps);
                    records[totalRecords].steps = atoi(charSteps);
                    totalRecords++;
            }
            fclose(input);
            printf("File loaded successfully.\n");
            break;
            case 'B':
            case 'b': {
            {
                printf("Total records: %d\n", totalRecords);
                } else {
                    printf("Data not imported. Please import data first (Option A).\n");
            }
                break;
            }
            case 'C':
            case 'c':  {
                if (dataImported) {
                    if (totalRecords > 0) {
                        int minSteps = records[0].steps;
                        int index = 0;

                        for (int i = 1; i < totalRecords; i++) {
                            if (records[i].steps < minSteps) {
                                minSteps = records[i].steps;
                                index = i;
                            }
                        }
                        printf("Fewest steps: ");
                        printRecord(records[index]);
                    } else {
                        printf("No records available.\n");
                    }
                } else {
                    printf("Data not imported. Please import data first (Option A).\n");
                }
                break;
            }
            case 'D':
            case 'd':  {
                if (dataImported) {
                    if (totalRecords > 0) {
                        int maxSteps = records[0].steps;
                        int index = 0;

                        for (int i = 1; i < totalRecords; ++i) {
                            if (records[i].steps > maxSteps) {
                                maxSteps = records[i].steps;
                                index = i;
                            }
                        }
                        printf("Largest steps: ");
                        printRecord(records[index]);
                    } else {
                        printf("No records available.\n");
                    }
                } else {
                    printf("Data not imported. Please import data first (Option A).\n");
                }
                break;
            }
            case 'E':
            case 'e':  {
                if (dataImported) {
                    if (totalRecords > 0) {
                        int totalSteps = 0;
                        for (int i = 0; i < totalRecords; ++i) {
                            totalSteps += records[i].steps;
                        }
                        float meanSteps = (float)totalSteps / totalRecords;
                        printf("Mean step count: %d\n", (int)(meanSteps + 0.5));
                    } else {
                        printf("No records available.\n");
                    }
                } else {
                    printf("Data not imported. Please import data first (Option A).\n");
                }
                break;
            }
            case 'F':
            case 'f':  {
                if (dataImported) {
                    if (totalRecords > 0) {
                        int start = -1, end = -1;
                        int longestPeriod = 0;
                        int currentPeriod = 0;
                        int startTemp = -1;

                        for (int i = 0; i < totalRecords; ++i) {
                            if (records[i].steps > 500) {
                                if (currentPeriod == 0) {
                                    startTemp = i;
                                }
                                currentPeriod++;
                            } else {
                                if (currentPeriod > longestPeriod) {
                                    longestPeriod = currentPeriod;
                                    start = startTemp;
                                    end = i - 1;
                                }
                                currentPeriod = 0;
                            }
                        }

                        if (currentPeriod > longestPeriod) {
                            longestPeriod = currentPeriod;
                            start = startTemp;
                            end = totalRecords - 1;
                        }

                        if (start != -1 && end != -1) {
                            printf("Longest period start: ");
                            printRecord(records[start]);
                            printf("Longest period end: ");
                            printRecord(records[end]);
                        } else {
                            printf("No continuous period where the step count is above 500 steps.\n");
                        }
                    } else {
                        printf("No records available.\n");
                    }
                } else {
                    printf("Data not imported. Please import data first (Option A).\n");
                }
                break;
            }
            case 'Q':
            case 'q':  {
                printf("Program exits.\n");
                exit(0);
            }
            default:
                printf("Invalid choice. Please select a valid option.\n");
        }
    }

    return 0;
}