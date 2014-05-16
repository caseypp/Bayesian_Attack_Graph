#include <stdio.h>
#include <stdlib.h>
#include <math.h>//gcc -lm to build
#include <string.h>
#include "cJSON.h"
#include "cJSON.c"

/**
**     USING THE LCPD_PRE_NUMBER TO CREATING THE 0-1 ARRAY
**     LCPD_COUNT IS THE CURRENT NUMBER
**     RETURN THE ARRAY
**/

int * ONE_ZERO_CREATE(int LCPD_PRE_NUMBER,int LCPD_COUNT_CURRENT,int * ONE_ZERO_ARRAY)

    //CREATE THE ONE-ZERO ARRAY
    int i;
    for (int i = 0; LCPD_PRE_NUMBER >0; i++,LCPD_PRE_NUMBER--)
    {
        ONE_ZERO_ARRAY[i]=(LCPD_COUNT_CURRENT >> (LCPD_PRE_NUMBER - 1)) & 1;
	}
	return ONE_ZERO_ARRAY;
	free(ONE_ZERO_ARRAY);
}


/**
***        the function is to read json
***        return cjson * type data
**/
cJSON *Read_Json(char* filename)
{
    FILE *fp;//file point
    char * data;//save the data from the file
	if(fp = fopen(filename,"r"))
	{
		//get the data of the json file
        printf("Open the %s successfully\n",filename);
		fseek(fp,0,SEEK_END);//move the file point to the file tail
        long len=ftell(fp);//get the current location in the json file
        fseek(fp,0,SEEK_SET);//move the file point to the file head
        data=(char*)malloc(len+1);
        fread(data,1,len,fp);
        fclose(fp);
	}
	else
		printf("Open %s Error!\n\n",filename);

    //transfer the data to json
    cJSON * json;
    //char *out;
    json=cJSON_Parse(data);
    if (!json) {printf("Error before: [%s]\n",cJSON_GetErrorPtr());}
	else
	{
        return json;
        cJSON_Delete(json);//delete
	}

}

/**
**     THE FUNCTION IS TO REVERSE THE INT ARRAY
**     RETURN INT * TYPE DATA
**/

int * REVERSE_INT(int *DATA,int LCPD_PRE_NUMBER)
{
    int DATA_LENGTH;//THE LENGTH OF THE INT DATA
    DATA_LENGTH = LCPD_PRE_NUMBER;
    //printf("%d\n",DATA_LENGTH);
    //int DATA_TEMP;
    int i;
    for(i=0;i<DATA_LENGTH/2;i++)
    {

        int DATA_HEAD,DATA_END,DATA_TMP;
        DATA_HEAD=i;
        DATA_END=DATA_LENGTH-1-i;
        //printf("HEAD:%d\t",DATA[DATA_HEAD]);
        //printf("END:%d\t",DATA[DATA_END]);
        DATA_TMP=DATA[DATA_HEAD];
        DATA[DATA_HEAD]=DATA[DATA_END];
        DATA[DATA_END]=DATA_TMP;
    }
    return DATA;

}


/**
**     THE MAIN FUNCTION
**/

int main(int arg,char* argv[])
{
	int LCPD_PRE_NUMBER;//the number of the pre node
	int LCPD_COUNT;//THE NUMBER EQUALS POW(2,LCPD_PRE_NUMBER)
    int *ONE_ZERO_ARRAY;

    cJSON *json;
    json=Read_Json("edge.json");

    //get the part of a
    cJSON *name = cJSON_GetObjectItem(json,"a");
    cJSON *pre=cJSON_GetObjectItem(name,"pre");

    LCPD_PRE_NUMBER=(int)pre->valuedouble;

    LCPD_COUNT=pow(2,LCPD_PRE_NUMBER);//THE NUMBER OF THE 0-1 MATRATIX IN TOTAL

    ONE_ZERO_ARRAY=(int*)malloc(LCPD_PRE_NUMBER);

    int i;
    for(i=0;i<LCPD_COUNT;i++)
    {
        printf("%d: ",i);
        ONE_ZERO_ARRAY=ONE_ZERO_CREATE(LCPD_PRE_NUMBER,i,ONE_ZERO_ARRAY);

        //REVERSE THE INT DATA
        ONE_ZERO_ARRAY=REVERSE_INT(ONE_ZERO_ARRAY,LCPD_PRE_NUMBER);
        int k;//JUST FOR LOOP
        for(k=0;k<LCPD_PRE_NUMBER;k++)
        {
            printf("%d\t",ONE_ZERO_ARRAY[k]);
        }
        printf("\n");

    }

}
