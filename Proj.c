#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc, char** argv)
{
    char p[10000][1000];
    int i = 2;
    while(i < argc)
    {
        const char * filename = (const char*)argv[1];
        FILE* src; 
        int num[1000] = {0};                     
        src = fopen(filename, "r"); 
        if(src == NULL)
            printf("NOT found");
        while(fgetc(src) != EOF)
        {
            char line[10000];
            const char * name = (const char*)argv[i];
            fgets(line, 1000, src);
            char* q = strstr(line, name);
            if(q != NULL)
            {
                num[i]++;
            }  
        }
        printf("%s has interacted %d in this group\n", argv[i], num[i]);
        i++;
        fclose(src);
        free(src);
    }
}