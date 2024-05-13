#define _CRT_SECURE_NO_WARNINGS
  
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
