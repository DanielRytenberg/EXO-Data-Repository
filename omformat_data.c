#define _CRT_SECURE_NO_WARNINGS
  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

void insertIntToStr(char* str, int adressStart, int adressStop, int insert)
{
    //printf("Start insert\n");
    char strToUse[MAX_LINE_LENGTH];
    strcpy(strToUse, str);

    char leftOverStr[MAX_LINE_LENGTH];
    strcpy(leftOverStr, &(strToUse[adressStop]));
    char insertStr[MAX_LINE_LENGTH];

    strToUse[adressStart] = '\0';
    sprintf(insertStr,"%d",insert);
    strcat(strToUse,insertStr);
    strcat(strToUse,leftOverStr);

    
    strcpy(str, strToUse);
    //printf(strToUse);
    //printf("\n");
}

FILE* pathFinder(int* months,int*  days, int currentPoint,char* location, char* openingType, char* saveLocation)
{
    //printf("Start Pathfinder\n");
    FILE *file;
    char path[MAX_LINE_LENGTH];
    char temp[MAX_LINE_LENGTH];
    strcpy(path,"2024_x_x_TestSubxx_ARM_x_xxx.csv");

    
    insertIntToStr(path,strlen(path)-7,strlen(path)-4,currentPoint);

    for(int month = months[0]; month <= months[1]; month++)
    {
        insertIntToStr(path,5,6,month);
        

        
        for(int day = days[0]; day <= days[1]; day++)
        {
            insertIntToStr(path,7,strlen(path)-24,day);
            
            
                
            for(char arm = 0; arm <= 1; arm++)
            {
                if(arm)
                {
                    path[strlen(path)-9] = 'L';
                }
                else
                {
                    path[strlen(path)-9] = 'R';
                }
                
                for(int group = 1; group <= 2; group++)
                {
                    for(int subject = 0; subject < 4; subject++)
                    {
                        insertIntToStr(path,strlen(path)-16,strlen(path)-14,(group*10)+subject);

                        strcpy(temp,location);
                        strcat(temp,path);
                        file = fopen(temp, openingType);
                        if (file != NULL)
                        {
                            strcpy(temp,"Fixed_Data\\");
                            strcat(temp,path);
                            strcpy(saveLocation, temp);
                            return file;
                        }                      
                    }

                }
            }
        }
    }

    printf("End Pathfinder\n");
    return NULL;
}

int main() {
    printf("Start\n");


    char saveLocation[MAX_LINE_LENGTH];
    int days[2];
    days[0] = 0;
    days[1] = 30;
    int months[2];
    months[0] = 4;
    months[1] = 4;
    char line[MAX_LINE_LENGTH];
    char new_label[MAX_LINE_LENGTH];
    char newline[MAX_LINE_LENGTH];
    char startLines[MAX_LINE_LENGTH];
    int sec,lable,lableFrequency,i = 0,fs = 4000;
    char *direction;
    for(int currentPoint = 243; currentPoint <= 260; currentPoint++)
    {

        strcpy(line,"");
        strcpy(new_label,"");
        strcpy(newline,"");
        strcpy(startLines,"");
        i = 0;
        sec = 0;
        lable = 0;
        lableFrequency = 0;

        FILE *file = pathFinder(months,days,currentPoint, "", "r+", saveLocation);
        if (file == NULL) {
            perror("Error opening file");
            return 1;
        }
        else
        {
            printf("Found file of %d\n", currentPoint);
        }

        //printf(saveLocation);
        printf("\n");
        FILE *save = fopen(saveLocation, "w");
        if (save == NULL) {
            perror("Error opening file");
            return 1;
        }
        else
        {
            //printf("Found save location\n");
        }
        //printf("Start\n");

        


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
            //printf(line);
            //printf(startLines);
            //printf("\n");
        }
        printf("LableFreq is:%d\n", lableFrequency);
        printf(startLines);
        printf("\n");

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
        //printf("lable = %d\n", lable);


        // Read file line by line
        while (fgets(line, sizeof(line), file)) {
            // Find the length of the string

                int length = 0;
                while (line[length] != '\n') {
                    if(length != 0)
                        newline[length-1] = line[length-1];
                    length++;
                }
                newline[length-1] = '\0';
                
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
        //printf("End\n");

        fclose(file);
        
        fclose(save);
    }
    return 0;
}

