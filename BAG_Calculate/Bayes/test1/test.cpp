/*
*����json���ݶ�ȡ���ԣ������в��Ի�ȡjson����Ԫ�ػ�ȡ
*
*/


#include<iostream>
#include<string.h>
#include "cJSON.h"
#include "cJSON.c"
using namespace std;

/*
//����json���ݽṹ��
typedef struct cJSON {
    struct cJSON *next,*prev;   // ���� �����������õ�
    struct cJSON *child;        // ���� �Ͷ�����ָ������������ֵ

    int type;           // Ԫ�ص����ͣ����Ƕ���������

    char *valuestring;          // ������ַ���
    int valueint;               // �������ֵ
    double valuedouble;         // ���������cJSON_Number

    char *string;               // The item's name string, if this item is the child of, or is in the list of subitems of an object.
} cJSON;
*/

//json���ݽ���
void doit(char *text)
{
	char *out;cJSON *json;

	json=cJSON_Parse(text);
	if (!json) {printf("Error before: [%s]\n",cJSON_GetErrorPtr());}
	else
	{
		out=cJSON_Print(json);

		//��ȡjson�����е�Ԫ��
		cJSON *name = cJSON_GetObjectItem(json,"name");
        //string na = cJSON_GetObjectItem(name,"name");
        //cout<<na<<endl;
        string str=name->valuestring;
		cout<<str<<endl;
        cJSON *format = cJSON_GetObjectItem(json,"format");
        int framerate = cJSON_GetObjectItem(format,"frame rate")->valueint;
   		//int width = cJSON_GetObjectItem(format,"width")->valueint;

        cout<<framerate<<endl;
        cout<<name->next->valuestring<<endl;

		cJSON_Delete(json);//delete
		//int width = cJSON_GetObjectItem(format,"width")->valueint;
        //cout<<width<<endl;
		printf("%s\n",out);
		free(out);
	}
}


//��ȡjson�ļ�
void dofile(char *filename)
{
	FILE *f=fopen(filename,"rb");
	fseek(f,0,SEEK_END);//ָ���ƶ����ļ�β
	long len=ftell(f);//��ȡ��ǰ�ļ���дλ��,�õ��ļ�����
	fseek(f,0,SEEK_SET);//�ļ�ָ���ƶ����ļ�ͷ
	char *data=(char*)malloc(len+1);
	fread(data,1,len,f);
	fclose(f);
    //printf("%s\n",data);

	//data����json����
	doit(data);
	free(data);
}


int main()
{
    dofile("test");
}
