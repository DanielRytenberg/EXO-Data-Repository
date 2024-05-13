#define _CRT_SECURE_NO_WARNINGS
/*#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SEGMENT_SIZE 1000
#define FS 4000
#define DATA_FILE "/home/elliot/Dokument/GitHub/EXO-Data-Repository/2024_4_6_TestSub20_ARM_L_"
#define OUTPUT_FILE "/home/elliot/Dokument/GitHub/EXO2/Data/features.txt"

int main() {
    FILE* fp, * output_fp;
    float data[SEGMENT_SIZE];
    int Fs = FS,sec;
    char* path = (char*)malloc(1000*sizeof(char));
    int file_id;

    for(file_id = 105; file_id < 106; file_id++)
    {
    memset(path,'\0',sizeof(path));
  
    int counter = 0;
    char test[3];

    snprintf(test, 10, "%d", file_id);


    strcpy(path, DATA_FILE);
    strcat(path, test);
    strcat(path,".csv");

    printf("%s\n",path);

    fp = fopen(path, "r+");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }
    printf("File opened \n");

    float temp; //temporärt spara datan 
    char buffer[100];
    
    //skippa första cykeln rader 
    

    char line[SEGMENT_SIZE];
    char label[SEGMENT_SIZE];
    char new_label[SEGMENT_SIZE];
    char *newline;

    // Read file line by line
    while (fgets(line, sizeof(line), fp)) {
        // Find the label
        strcpy(label, strtok(line, ";"));

        // If the line is empty, skip
        if (label[0] == '\n') {
            continue;
        }

        strcpy(new_label,"0\n");

        // Remove newline character from new label
       // newline = strchr(new_label, '\n');
        if (newline) {
            *newline = '\0';
        }

      //  printf("new line: %s\n",new_label);
        // Move file pointer to beginning of line
        fseek(fp, -strlen(line), SEEK_CUR);

        // Write the new label
      char *token = strtok(line, ";");
        if (token != NULL) {
            strcpy(label, token);
        } else {
            // Handle the case where no semicolon is found in the line
        }
    }   
    printf("done!\n");
    fclose(fp);
    }
   return 0;
}
*/


   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000

int main() {
    FILE *file = fopen("/home/elliot/Dokument/GitHub/EXO-Data-Repository/2024_4_6_TestSub20_ARM_L_105.csv", "r+");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    char new_label[MAX_LINE_LENGTH];
    char *space_position;
    char *newline;
    int sec;

    // skip 5 first lines and save sec
    for (int skip = 0; skip < 4000; skip++) {
        fgets(line, sizeof(line), file);
        if(skip == 3)
        {
         sscanf(&line[15], "%d", &sec);
       //  printf("%d\n",sec);
        }
     //   printf("%s\n",line);
    }

    // Read file line by line
    while (fgets(line, sizeof(line), file)) {
           // Find the length of the string
             int length = 0;
            while (line[length] != '\n') {
             length++;
            }
    
             // Access the last character
            char last_char = '\0'; // Initialize with null character
            if (length > 0) {
                fprintf(file,"%c",line[length - 1]);
                printf("last char:%c\n",line[length - 1]);
            }
     }

    fclose(file);
    return 0;
}
