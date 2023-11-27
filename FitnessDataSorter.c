#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 12000

typedef struct {
    char date[11];
    char time[6];
    int steps;
} FitnessData;

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
                printf("Error: Steps data missing in the file\n");
                exit(1);
            }
        }
    }
}

int importFile(const char *filename, FitnessData records[], int *totalRecords) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
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
        printf("Error creating output file\n");
        exit(1);
    }

    for (int i = 0; i < totalRecords - 1; i++) {
        for (int j = i + 1; j < totalRecords; j++) {
            if (records[i].steps < records[j].steps) {
                FitnessData temp = records[i];
                records[i] = records[j];
                records[j] = temp;
            }
        }
    }

    for (int i = 0; i < totalRecords; i++) {
        fprintf(file, "%s\t%s\t%d\n", records[i].date, records[i].time, records[i].steps);
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
    int len = strlen(filename);
    strcpy(outputFilename, filename);
    outputFilename[len] = '.';
    outputFilename[len + 1] = 't';
    outputFilename[len + 2] = 's';
    outputFilename[len + 3] = 'v';
    outputFilename[len + 4] = '\0';
    
    writeTSVFile(outputFilename, records, totalRecords);
    printf("Output file created successfully: %s\n", outputFilename);

    return 0;
}