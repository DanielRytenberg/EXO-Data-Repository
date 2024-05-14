#define _CRT_SECURE_NO_WARNINGS
  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

int main() {
    FILE *file = fopen("/home/elliot/Dokument/GitHub/EXO-Data-Repository/2024_4_6_TestSub20_ARM_L_106.csv", "r+");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    char new_label[MAX_LINE_LENGTH];
    char *space_position;
    char newline[MAX_LINE_LENGTH];
    int sec,lable = 0,i = 0,fs = 4000;

    // skip 5 first lines and save sec
    for (int skip = 0; skip < 5; skip++) {
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
           // Find the length of the string7


             int length = 0;
            while (line[length] != '\n') {
                if(length != 0)
                    newline[length-1] = line[length-1];
             length++;
            }
            newline[length] = '\0';
           
            // labeling
            if(i%(sec*fs) == 0 && i != 0)
            {
                lable = (1+lable)%4;
                 printf("%d\n",lable);
            }

            i++;

            sprintf(new_label, "%d", lable);

            //strcat(newline,new_label);
            strcat(newline,"\0"); 
           // printf("%s\n",new_label);

             // print the last character
            if (length > 0) {
                //fprintf(file,"%s",newline);
                printf("last char:%s\n",newline);
            }
     }

    fclose(file);
    return 0;
}

