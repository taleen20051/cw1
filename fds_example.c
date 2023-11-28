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