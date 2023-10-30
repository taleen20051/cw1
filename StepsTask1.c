#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Define an appropriate struct
typedef struct {
	char date[11];
	char time[6];
	int steps;
} FITNESS_DATA;

// Define any additional variables here



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

FITNESS_DATA fitness_data[12000];
FILE *open_file(char filename[], char mode[]) {
    FILE *file = fopen("FitnessData_2023.csv", "r");
    
    if (file == NULL) {
        perror("There is an error in reading the file");
        exit(1);
    }
    return file;
}

// Complete the main function
int main() {

    char filename [] = "FitnessData_2023.csv";
    FILE *file = fopen(filename, "r");


    int buffer_size = 60;
    char line_buffer[60];
    int line_count = 0;
   
    while (fgets(line_buffer, buffer_size, file) != NULL) {
        char date[11];
        char time[6];
        char steps[20];

        tokeniseRecord(line_buffer, ",", date, time, steps);
        // Using strcpy to copy source to destination
        strcpy(fitness_data[line_count].date, date);
        strcpy(fitness_data[line_count].time, time);
        fitness_data[line_count].steps = atoi(steps);
        line_count++;
    }

    fclose(file);

    // Printing the copied string
    printf("Number of records in file: %d\n", line_count);

    for (int x = 0; x < 3; x++) {
        printf("%s/", fitness_data[x].date);
        printf("%s/", fitness_data[x].time);
        printf("%d\n", fitness_data[x].steps);
    }
    
    return 0;
}
