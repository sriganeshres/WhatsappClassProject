#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int findpos(char* src, const char name)
{
    for(int i = 0; src[i] != '\0'; i++)
    {
        if(src[i] == name)
            return i+1;
    }
    return -1;
}
void copySubstring(const char* original, char* destination) 
{
    // Find the position of the hyphen
    const char* start = strchr(original, '-'); 
    // Find the position of the colon
    const char* end = strchr(original, ':');   

    if (start == NULL || end == NULL || start >= end) 
    {
        //fprintf(stderr, "Invalid string format.\n");
        return;
    }
    // Calculate the length of the desired substring
    size_t length = end - start - 1; 
    // Copy the substring to the destination
    strncpy(destination, start + 1, length); 
    // Ensure the destination string is properly terminated
    destination[length] = '\0';
}
typedef struct Stringer
{
    char name[100];
    int count;
} NameArr;
int compareNames(const void* a, const void* b) 
{
    //function for sorting usernames alphabetically
    const NameArr* entryA = (const NameArr*)a;
    const NameArr* entryB = (const NameArr*)b;
    return strcmp(entryA->name, entryB->name);
}
int main(int argc, char** argv)
{
    //command line input for filename to search so that it can be used for multiple programs without change in src code
    const char* filename = (const char*)argv[1];
    FILE* fp, *os;
    fp = fopen(filename, "r");
    //open chat file
    os = fopen("Report.txt", "w");
    //target file for user out put
    char line[1000] ,temp[1000], temp1[1000];
    while(fgets(line, 1000, fp) != NULL)
    {
        strncpy(temp, line+15, 1000);
        copySubstring(temp, temp1);
        if(strlen(temp1))
            fprintf(os, "%s\n", temp1);
    }
    fclose(fp);
    fclose(os);
    os = fopen("Report.txt", "r");
    char name[100];
    int index = 0, flag = 0;
    NameArr array[1000];
    while(fgets(name, 100, os) != NULL)
    {
        if(index == 0)
        {
            //first input
            strcpy(array[index].name, name);
            array[index].count++; 
            index++;
        }
        else
        {
            int ver = 0;
            for(int i = 0; i < index; i++)
            {
                if(strcmp(array[i].name, name) == 0)
                {
                    ver = i;
                    flag = 0;
                    break;
                }
                else
                    flag = 1; 
            }
            if(flag == 1)
            {
                strcpy(array[index].name, name);
                array[index].count++; 
                index++;
            }
            else
            {
                array[ver].count++;
            }
        }
    }
    qsort(array, index, sizeof(NameArr), compareNames);
    for(int i = 0; i < index; i++)
    {
        printf("%s %d\n",array[i].name, array[i].count);
    }
}
