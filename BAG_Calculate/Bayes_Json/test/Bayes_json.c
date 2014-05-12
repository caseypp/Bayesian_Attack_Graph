/*
*test for json c_code reading linux
*
*/

#include<stdio.h>
#include<string.h>
#include "cJSON.h"
#include "cJSON.c"

//json reading
void doit(char *text)
{
	char *out;
	cJSON *json;

	json=cJSON_Parse(text);
	//cout<<"haha"<<endl;
	if (!json) {printf("Error before: [%s]\n",cJSON_GetErrorPtr());}
	else
	{
		//cout<<"haha"<<endl;
		out=cJSON_Print(json);

		//get the paramater from the json

		cJSON *name = cJSON_GetObjectItem(json,"name");
		int name_count = cJSON_GetArraySize(name);
        int i=0;
		for (i =0 ; i < name_count ; i++)
        {
            cJSON *node = cJSON_GetArrayItem(name,i);//
            //int node_count = cJSON_GetArraySize(node);

            //pre node
            cJSON *attr = cJSON_GetObjectItem(node,"pre");
            int pre_count = cJSON_GetArraySize(attr);//get the pre node
            int j;
            for ( j = 0; j < pre_count ; j++)
            {
                cJSON *pre = cJSON_GetArrayItem(attr,j);
                //cout<<pre->valuestring<<endl;
                printf("%s\n",pre->valuestring);
                //cout<<11111111111111111<<endl;
            }

            //get LCPD

            //True
            cJSON *probability_T = cJSON_GetObjectItem(node,"T");
            int pro_count_T = cJSON_GetArraySize(probability_T);

            int k;
            for (k =0 ; k < pro_count_T ; k++)
            {
                cJSON *pro = cJSON_GetArrayItem(probability_T,k);
                //cout<<pro->valuedouble<<endl;
                printf("%f\n",pro->valuedouble);
            }

            //False
            cJSON *probability_F = cJSON_GetObjectItem(node,"F");
            int pro_count_F= cJSON_GetArraySize(probability_F);

            for ( k =0 ; k < pro_count_F ; k++)
            {
                cJSON *pro = cJSON_GetArrayItem(probability_F,k);
                //cout<<pro->valuedouble<<endl;
                printf("%f\n",pro->valuedouble);
            }
        }

		cJSON_Delete(json);//delete
		//int width = cJSON_GetObjectItem(format,"width")->valueint;
        //cout<<width<<endl;
        //cout<<endl;
	printf("\n");
		//printf("%s\n",out);
		free(out);
	}
}


//read json file
void dofile(char *filename)
{
	FILE *f=fopen(filename,"rb");
	fseek(f,0,SEEK_END);//move the file point to the file tail
	long len=ftell(f);//get the current location in the json file
	fseek(f,0,SEEK_SET);//move the file point to the file head
	char *data=(char*)malloc(len+1);
	fread(data,1,len,f);
	fclose(f);
    //printf("%s\n",data);

	//data inlucde the json datas
	doit(data);
	free(data);
}


int main()
{
    dofile("test");//test is the json file name
}