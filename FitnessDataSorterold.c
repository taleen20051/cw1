#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 12000

// Define the struct for the fitness data
typedef struct {
    char date[11];
    char time[6];
    int steps;
} FitnessData;

// Function to tokenize a record
void tokeniseRecord(char *record, char delimiter, char *date, char *time, int *steps) {
    char *ptr = strtok(record, &delimiter);
    if (ptr != NULL) {
        strcpy(date, ptr);
        ptr = strtok(NULL, &delimiter);
        if (ptr != NULL) {
            strcpy(time, ptr);
            ptr = strtok(NULL, &delimiter);
            if (ptr != NULL) {
                *steps = atoi(ptr);
            } else {
                *steps = 0; // Assigning default value if steps data is missing
            }
        }
    }
}

int importFile(const char *filename, FitnessData records[], int *totalRecords) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }

    char line[100], date[30], time[15], steps[10];
    const char delimiter = ',';
    int recordsRead = 0;

    while (fgets(line, sizeof(line), file) != NULL && recordsRead < MAX_RECORDS) {
        tokeniseRecord(line, delimiter, date, time, &records[recordsRead].steps);
        strcpy(records[recordsRead].date, date);
        strcpy(records[recordsRead].time, time);
        recordsRead++;
    }

    *totalRecords = recordsRead;
    fclose(file);
    return 1;
}

void writeTSVFile(const char *filename, FitnessData records[], int totalRecords) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error creating output file");
        exit(1);
    }

    // Write the data to the output file in tab-separated values
    for (int i = 0; i < totalRecords; i++) {
        char output[150];
        strcpy(output, records[i].date);
        strcat(output, "\t");
        strcat(output, records[i].time);
        strcat(output, "\t");
        char steps[20];
        sprintf(steps, "%d\n", records[i].steps);
        strcat(output, steps);

        fprintf(file, "%s", output);
    }

    fclose(file);
}

int main() {
    char filename[100];

    printf("Enter filename: ");
    scanf("%s", filename);

    FitnessData records[MAX_RECORDS];
    int totalRecords = 0;

    if (!importFile(filename, records, &totalRecords)) {
        printf("Error: invalid file\n");
        return 1;
    }

    char outputFilename[150];
    strcpy(outputFilename, filename);
    strcat(outputFilename, ".tsv");
    writeTSVFile(outputFilename, records, totalRecords);
    printf("Output file created successfully: %s\n", outputFilename);

    return 0;
}