#define _CRT_SECURE_NO_WARNINGS
  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

int main() {
    const char path[] = "2024_4_6_TestSub20_ARM_L_106.csv";
    
    FILE *file = fopen(path, "r+");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    FILE *save = fopen("Save", "w");
    if (save == NULL) {
        perror("Error opening file");
        return 1;
    }
    printf("Start\n");

    char line[MAX_LINE_LENGTH];
    char new_label[MAX_LINE_LENGTH];
    char newline[MAX_LINE_LENGTH];
    int sec,lable,lableFrequency = 0,i = 0,fs = 4000;
    char startLines[MAX_LINE_LENGTH];
    char *direction;

    // skip 5 first lines and save sec and direction
    for (int skip = 0; skip < 5; skip++) {
        fgets(line, sizeof(line), file);
        if(skip == 1)
        {
            sscanf(&line[18], "%c", &direction);
            //printf("Direction is:%c\n",direction);
        }
        if(skip == 3)
        {
            sscanf(&line[15], "%d", &sec);
            //printf("Sec is:%d\n",sec);
            lableFrequency = sec*fs;
        }
        strcat(startLines,line);
        //printf("%s",line);
    }
    //printf("LableFreq is:%d\n", lableFrequency);
    //printf(startLines);

    //Save the first lines to the doccument
    fprintf(save,startLines);

    //Chose starting lable based on diraction
    if(*direction == 'u' || *direction == 'U')
    {
        lable = 0;
    }
    else if(*direction == 'd' || *direction == 'D')
    {
        lable = 2;
    }
    //printf("lable = %d", lable);


    // Read file line by line
    while (fgets(line, sizeof(line), file)) {
           // Find the length of the string

            int length = 0;
            while (line[length] != '\n') {
                if(length != 0)
                    newline[length-1] = line[length-1];
             length++;
            }
            newline[length - 1] = '\0';
            
            /*
            if(length > 0)
            {
                printf("prev char:%s", line);
                printf("test char:%s\n",newline);
            }
            */

            sprintf(new_label, "%d", lable);
            strcat(newline,new_label);
            strcat(newline,"\n");
           // strcat(newline,"\0"); 
           // printf("%s\n",new_label);

             // print the last character
            if (length > 0) {
                fprintf(save,"%s",newline);
                //printf("last char:%s\n\n",newline);
                //printf("last char:%c\n",newline[length]);
                if(i%500 == 0)
                {
                    //printf("last char:%s\n",newline);
                }
            }


            i++;
            /*if(i > 100)
            {
                break;
            }*/
            
            // labeling
            if(i%(lableFrequency) == 0)
            {
                lable = (1+lable)%4;
                //printf("Lable is now %d\n", lable);
            }


    }
    printf("End");

    fclose(file);
    
    fclose(save);

    return 0;
}

