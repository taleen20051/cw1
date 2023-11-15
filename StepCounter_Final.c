#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

#define MAX_RECORDS 12000

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

int importFile(const char *filename, FITNESS_DATA records[], int *totalRecords) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }

    char line[100], date[30], time[15], steps[10];
    const char *delimiter = ",";
    int recordsRead = 0;

    while (fgets(line, sizeof(line), file) != NULL && recordsRead < MAX_RECORDS) {
        tokeniseRecord(line, delimiter, date, time, steps);
        strcpy(records[recordsRead].date, date);
        strcpy(records[recordsRead].time, time);
        records[recordsRead].steps = atoi(steps);
        recordsRead++;
    }

    *totalRecords = recordsRead;
    fclose(file);
    return 1;
}

int main() {
    FITNESS_DATA records[MAX_RECORDS];
    int totalRecords = 0;
    char choice;
    int dataImported = 0;


while (1) {
    printf("\nA: Specify the filename to be imported\n"
            "B: Display the total number of records in the file\n"
            "C: Find the date and time of the time slot with the fewest steps\n"
            "D: Find the date and time of the time slot with the largest number of steps\n"
            "E: Find the mean step count of all the records in the file\n"
            "F: Find the longest continuous period where the step count is above 500 steps\n"
            "Q: Exit\n");
    printf("Enter your choice: ");
    scanf(" %c", &choice);

    switch (choice) {
        case 'A':
            {
                char filename[100];
                printf("Input filename: ");
                scanf("%s", filename);
                if (importFile(filename, records, &totalRecords)) {
                    printf("Data imported successfully!\n");
                    dataImported = 1;
                } else {
                    printf("Error: Data not imported successfully\n");
                    dataImported = 0;
                }
            break;
            }
        case 'B':
            if (dataImported) {
                printf("Total records: %d\n", totalRecords);
            } else {
                printf("Data not imported. Please import data first (Option A).\n");
            }
            break;
        case 'C':
            if (dataImported) {
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
                printf("Data not imported. Please import data first (Option A).\n");
            }
            break;
        case 'D': 
            if (dataImported) {
            int maxSteps = records[0].steps;
            int index = 0;

            for (int i = 1; i < totalRecords; ++i) {
                if (records[i].steps > maxSteps) {
                    maxSteps = records[i].steps;
                    index = i;
                }
            }
            printf("Largest steps: %s %s\n", records[index].date, records[index].time);
            }       else {
                printf("Data not imported. Please import data first (Option A).\n");
            }
            break;
        case 'E':
            if (dataImported) {
                int totalSteps = 0;
            for (int i = 0; i < totalRecords; ++i) {
                totalSteps += records[i].steps;
            }
            float meanSteps = (float)totalSteps / totalRecords;
            printf("Mean step count: %d\n", (int)(meanSteps + 0.5));
            } else {
                printf("Data not imported. Please import data first (Option A).\n");
            }
            break;
        case 'F':
            if (dataImported) {
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
                printf("Longest period start: %s %s\n", records[start].date, records[start].time);
                printf("Longest period end: %s %s\n", records[end].date, records[end].time);
            } else {
                printf("No continuous period where the step count is above 500 steps.\n");
            }
            } else {
                printf("Data not imported. Please import data first (Option A).\n");
            }
            break;
        case 'Q':
            printf("Program returns 0 & exits.\n");
            exit(0);
            break;
        default:
            printf("Invalid choice. Please select a valid option.\n");
    }
} while (choice != 'Q');

return 0;
}