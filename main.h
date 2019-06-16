#define MAXKEYERR 3
#define MaxVertexNum 500
#define MAXEXITNUM 20 
#define MAXTRANNUM 5
#define MAXSTATIONSUM 40
#define MAXLINESUM 30
#define ADMINPWD "123456" 
#define MAXSTANUM 20
#ifndef MAIN_H
#define MAIN_H
 
#ifdef __cplusplus
extern "C" {
#endif
typedef struct{
	int adnum;
	char exitname[100];//xx���� 
	char exitad[MAXSTANUM][100];//�������� 
}exitinfo;

typedef struct{
	int lineno;//��·��� 
	int stationid;//վ���� 
	int stageseq;//վ��˳�� 
	int exitsum;//������ 
	int x;//��ͼʱʹ�õ����� 
	int y;
	double longitude;//���� 
	double latitude;//γ��
	int transfer[MAXTRANNUM];//����վ  
	char namecn[50];//վ��������
	char nameen[50];//վ��Ӣ���� 
	char startonetime[8];//�����װ೵ʱ�� 
	char starttwotime[8];//�����װ೵ʱ�� 
	char endonetime[8];//����ĩ�೵ʱ�� 
	char endtwotime[8];//����ĩ�೵ʱ�� 
//	lineinfo line;
	exitinfo exitdata[MAXEXITNUM];//�������� 	
}stationinfo;


typedef struct{
	int number;//��·��ţ���·�ļ��� 
	int lineno;//��·�� 
	int averageintervaltime;//ƽ����μ��ʱ�� 
	int lastmodifytime;//��·��ͨʱ�� 
	int stationsum;//վ���� 
	char linecn[30];//��·������ 
	char lineen[30];//��·Ӣ���� 
	char start[50];//ʼ��վ
	char end[50]; //�յ�վ 
	char color[10];//8λ��·��ɫ���� 
	char color1[10];//��ɫ���� 
	stationinfo station[MAXSTATIONSUM];
}lineinfo;




typedef struct EdgeNode{
	double weight;//����Ȩֵ 	
}Edge,Edgearc[MaxVertexNum][MaxVertexNum];


typedef struct{
	int vexnum,arcnum;
	stationinfo data[MaxVertexNum];
	Edgearc arcs;
}Graph;


void mylogin(void); 
void ModifyInfoMenu(int opt); 
void menu(int opt);
void quit(void); 
#ifdef  __cplusplus
}
#endif
 
#endif
