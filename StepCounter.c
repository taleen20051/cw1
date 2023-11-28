#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

#define MAX_RECORDS 12000
#define MAX_LINE_LENGTH 100

void tokeniseRecord(const char *input, const char *delimiter, char *date, char *time, char *steps) {
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

void printRecord(FITNESS_DATA record) {
    printf("Date: %s, Time: %s, Steps: %d\n", record.date, record.time, record.steps);
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
    FITNESS_DATA records[MAX_RECORDS];
    int totalRecords = 0;
    char filename[100];
    char choice;
    int dataImported = 0;

    while (1) {
        displayMenu();
        scanf(" %c", &choice);

        switch (choice) {
            case 'A':
            case 'a': {
                printf("Input filename: ");
                scanf("%s", filename);
                
                FILE *file = fopen(filename, "r");
                if (file == NULL) {
                    printf("Error: Could not find or open the file.\n");
                    return 1;
                }

                char line[MAX_LINE_LENGTH], date[11], time[6], steps[10];
                const char *delimiter = ",";
                
                totalRecords = 0;
                while (fgets(line, sizeof(line), file) != NULL && totalRecords < MAX_RECORDS) {
                    tokeniseRecord(line, delimiter, date, time, steps);
                    strcpy(records[totalRecords].date, date);
                    strcpy(records[totalRecords].time, time);
                    records[totalRecords].steps = atoi(steps);
                    totalRecords++;
                }
                
                fclose(file);
                printf("File successfully loaded.\n");
                dataImported = 1;
                break;
            }
            case 'B':
            case 'b': {
                if (dataImported) {
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
                        printf("Fewest steps: %s %s\n", records[index].date, records[index].time);
                    
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
                        printf("Largest steps: %s %s\n", records[index].date, records[index].time);

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
                            printf("Longest period start: %s %s\n", records[start].date, records[start].time);

                            printf("Longest period end: %s %s\n", records[end].date, records[end].time);

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
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}