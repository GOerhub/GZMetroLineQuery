#define MAXSIZE 1024
#define PI                      3.1415926
#define EARTH_RADIUS            6371.393        //������ư뾶6378.137
#define MAXPATH 100
#ifndef ITILITY_H
#define ITILITY_H
 
#ifdef __cplusplus
extern "C" {
#endif
typedef struct times
{
        int Year;
        int Mon;
        int Day;
        int Hour;
        int Min;
        int Second;
}Times;



//�ļ��������� 
void trim_string(char *str);
void trim_all_string(char *str);
//�ļ����ò��� 
char* GetIniKeyString(char* filename, char* title, char* key);
int GetIniKeyInt(char* filename, char* title, char* key);
int PutIniKeyString(char* filename,char* title,char* key, char* val);
int PutIniKeyInt(char* filename, char* title, char* key, int val);
int DeleteIniSection(char* filename,char* title);
int ChangeIniTitle(char* filename,char* title,char* Newtitle); 
//��γ�ȼ������ 
double radian(double d);
double get_distance(double lat1, double lng1, double lat2, double lng2);
//���� 
Times stamp_to_standard(int stampTime); 
void color(short x);
void BuildPath(int num,char *path);
char *GetWorkPath(void);
#ifdef  __cplusplus
}
#endif
 
#endif
