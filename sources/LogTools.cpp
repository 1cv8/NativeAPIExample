
#include "LogTools.h"

void SetLog(char* logstr)
{
        FILE*f;
        f=fopen("c:\\dat.txt","a");
        fprintf(f,"   ");
        fprintf(f,logstr);
        fprintf(f,"\n\r");
        fclose(f);
}

void SetLog(int zna4)
{
        FILE*f;
        f=fopen("c:\\dat.txt","a");
        fprintf(f,"   ");
        fprintf(f," %d",zna4);
        fprintf(f,"\n\r");
        fclose(f);
}
