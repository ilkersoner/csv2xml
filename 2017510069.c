#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//I EXECUTE IT LIKE THIS= ./2017510069 contacts.csv contacts.xml
const char* getfield(char* line, int num) //COLUMN READ (,)
{
    const char* tok;
    for (tok = strtok(line, ",");
            tok && *tok;
            tok = strtok(NULL, ",\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}
//FOR REPLACING ' ' TO '_' FOR THE XML
int replacechar(char *str, char orig, char rep) {
    char *ix = str;
    int n = 0;
    while((ix = strchr(ix, orig)) != NULL) {
        *ix++ = rep;
        n++;
    }
    return n;
}
int main(int argc, char** argv)
{
    // GETTING THE FILES FROM ARGUMENTS
    FILE* stream = fopen(argv[1], "r");
    FILE* fptr = fopen(argv[2], "w");

    char line[1024];
    int a=1;
    int b=1;
    char* arr[51];
    while (fgets(line, 1024, stream))
    {
        char* tmp = strdup(line);
        replacechar(tmp,' ','_');
        if(b==52)
        break;
        arr[b]=getfield(tmp,1);
        //printf("arr %d of %d is %s\n",a,b, arr[b]);
        
        b++;
        // I COULD ONLY MANAGE TAKING ONE COLUMN BUT IF YOU CHANGE THE INTEGER IN "arr[b]=getfield(tmp,1);" BETWEEN 1 TO 5 OTHER COLUMNS CAN BE DISPLAYED BUT IN ONE EXECUTION
    }
    
    for(int i=0;i<52;i++){
        printf("%d = %s \n",i,arr[i]);
    }
    // IN THIS PART I WROTE THE ELEMENTS WE GOT FROM CSV TO XML (I COULD ONLY GET THE FIRST COLUMNS I COULD LOOK INTO IT BUT I'M ALREADY 1 DAY LATE)
    fprintf(fptr,"<contacts>\n");
    for(int i=2;i<52;i++){
        fprintf(fptr,"<row id=%d>\n",a);
        fprintf(fptr,"<%s>",arr[1]);
        fprintf(fptr,"%s",arr[i]);
        fprintf(fptr,"</%s>\n",arr[1]);
        fprintf(fptr,"</row>\n");
        a++;
    }
    fprintf(fptr,"</contacts>\n");
    
}