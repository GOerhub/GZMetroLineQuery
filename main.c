#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "utility.h"
#include "main.h"
#include "UserFun.h"
#include "AdminFun.h"
#include "AdminFunModi.h"
#define __STDC_WANT_LIB_EXT1__ 1
Graph G;
lineinfo L[MAXLINESUM];
int MaxLine;
int MaxStation;

/*��ʼ��*/
void init(){
	
	int i=0,j=0,k=0,r=0,lineNum,stationNum,lineSum,temp,prior,next;
	double templa=0,templng=0;
	char linePath[100],str1[200],str2[200],chNumLine[5],chNumStation[5],chNumExit[5],*pname,*pad,tempch[5],*temp_p,*temp_e;
	char lineInfoPath[100]="data\\lineinfo.ini",buffer[MAXPATH];
//	strcpy(lineInfoPath,GetInfoPath());
//	getcwd(buffer,MAXPATH);
//    sprintf(buffer,"\\lineinfo.ini");
	lineSum=GetIniKeyInt(lineInfoPath,"config","linesum");
	for(i=0;i<lineSum;i++){
		itoa(i,chNumLine,10);
		lineinfo *lInfo;
		lInfo=(lineinfo*)malloc(sizeof(lineinfo));
		/*��ʼ��lInfo��ʼ*/
		lInfo->averageintervaltime=0; 
		lInfo->lastmodifytime=0;
		lInfo->lineno=0;
		lInfo->number=0;
		lInfo->stationsum=0;
		lInfo->color[0]='\0';
		lInfo->color1[0]='\0';
		lInfo->end[0]='\0';
		lInfo->linecn[0]='\0';
		lInfo->lineen[0]='\0';
		lInfo->start[0]='\0';
		/*��ʼ��lInfo����*/ 
		
		BuildPath(GetIniKeyInt(lineInfoPath,chNumLine,"number"),linePath);//��Ӧ��·���ļ�·����ȡ 
		stationNum=GetIniKeyInt(linePath,"config","stationsum");//��Ӧ��·վ������ 
		 
//		printf("%d  ",GetIniKeyInt(lineInfoPath,chNumLine,"number"));
		/*��·��Ϣ��ȡ*/
		lInfo->averageintervaltime=GetIniKeyInt(lineInfoPath,chNumLine,"averageintervaltime");
		lInfo->lastmodifytime=GetIniKeyInt(lineInfoPath,chNumLine,"lastmodifytime");
		lInfo->lineno=GetIniKeyInt(lineInfoPath,chNumLine,"lineno");
		lInfo->number=GetIniKeyInt(lineInfoPath,chNumLine,"number");
		if(lInfo->number>MaxLine && lInfo->number!=9999){//ʵʱ���������id��������ӵص� 
			MaxLine=lInfo->number;
		}
		lInfo->stationsum=GetIniKeyInt(linePath,"config","stationsum");
		strcpy(lInfo->color,GetIniKeyString(lineInfoPath,chNumLine,"color"));
		strcpy(lInfo->color1,GetIniKeyString(lineInfoPath,chNumLine,"numcolor"));
		strcpy(lInfo->linecn,GetIniKeyString(lineInfoPath,chNumLine,"linecn"));
		strcpy(lInfo->lineen,GetIniKeyString(lineInfoPath,chNumLine,"lineen"));
		strcpy(lInfo->start,GetIniKeyString(linePath,"config","startone"));
		strcpy(lInfo->end,GetIniKeyString(linePath,"config","starttow"));
		/*վ����Ϣ��ȡ*/
		for(j=0;j<stationNum;j++){//վ����Ϣ 
			stationinfo *sInfo;
			exitinfo *eInfo;
			sInfo=(stationinfo*)malloc(sizeof(stationinfo));
			eInfo=(exitinfo*)malloc(sizeof(exitinfo));
			/*��ʼ��sInfo��ʼ*/
			sInfo->exitsum=0;
			sInfo->lineno=0;
			sInfo->latitude=0; 
			sInfo->longitude=0;
			sInfo->stageseq=0;
			sInfo->stationid=0;
			for(k=0;k<MAXTRANNUM;k++){
				sInfo->transfer[k]=0;
			}
			
			sInfo->x=0;
			sInfo->y=0;
			sInfo->endonetime[0]='\0';
			sInfo->endtwotime[0]='\0';
			sInfo->namecn[0]='\0';
			sInfo->nameen[0]='\0';
			sInfo->startonetime[0]='\0';
			sInfo->starttwotime[0]='\0';
			for(k=0;k<MAXEXITNUM;k++){//�趨�����������Ϊ20��������Ҫ�޸����� 
				sInfo->exitdata[k].exitname[0]='\0';
				for(int r=0;r<MAXEXITNUM;r++){
					sInfo->exitdata[k].exitad[r][0]='\0';
				}	
			}
			/*��ʼ��sInfo����*/

			itoa(j,chNumStation,10);			
			strcpy(sInfo->endonetime,GetIniKeyString(linePath,chNumStation,"endone"));
			strcpy(sInfo->endtwotime,GetIniKeyString(linePath,chNumStation,"endtow"));
			strcpy(sInfo->nameen,GetIniKeyString(linePath,chNumStation,"nameen"));
			strcpy(sInfo->namecn,GetIniKeyString(linePath,chNumStation,"namecn"));
			strcpy(sInfo->startonetime,GetIniKeyString(linePath,chNumStation,"startone"));
			strcpy(sInfo->starttwotime,GetIniKeyString(linePath,chNumStation,"starttow"));
			
			sInfo->stationid=GetIniKeyInt(linePath,chNumStation,"stationid");
			sInfo->exitsum=GetIniKeyInt(linePath,chNumStation,"exitsum");
			sInfo->lineno=GetIniKeyInt(linePath,chNumStation,"lineno");
			sInfo->longitude=atof(GetIniKeyString(linePath,chNumStation,"longitude"));
			sInfo->latitude=atof(GetIniKeyString(linePath,chNumStation,"latitude"));
			sInfo->stageseq=GetIniKeyInt(linePath,chNumStation,"stageseq");			
			sInfo->x=GetIniKeyInt(linePath,chNumStation,"x");
			sInfo->y=GetIniKeyInt(linePath,chNumStation,"y");
			if(sInfo->stationid>MaxStation){//ʵʱ�������վid��������ӵص� 
				MaxStation=sInfo->stationid;
			}
//			printf("%d.%s   ",sInfo->stationid,sInfo->namecn);
//			if(j%8==0){
//				printf("\n");
//			}
			
			/*վ�������Ϣ��ȡ*/ 
			strcpy(str1,GetIniKeyString(linePath,chNumStation,"exitname"));
			strcat(str1,"|");
			pname=strtok_s(str1, "|",&temp_p);
			k=0;
			while(pname){//�˴�δ��վ��������жϣ�������ʱ������ 
				k++;
				itoa(k,chNumExit,10);
				strcpy(sInfo->exitdata[k-1].exitname,pname);
				pname=strtok_s(NULL, "|",&temp_p);
				strcpy(str2,GetIniKeyString(linePath,chNumStation,chNumExit));
				strcat(str2,"|");
				pad=strtok_s(str2, "|",&temp_e);
				r=0;
				sInfo->exitdata[k-1].adnum=0;
				while(pad){
					strcpy(sInfo->exitdata[k-1].exitad[r++],pad);
					sInfo->exitdata[k-1].adnum++;
					pad=strtok_s(NULL, "|",&temp_e);
				}
			}
			/*վ�������Ϣ��ȡend*/ 
			
			/*վ�㻻����Ϣ��ȡ*/ 
			
			strcpy(str1,GetIniKeyString(linePath,chNumStation,"transfer"));
			pname=strtok(str1, "|");
			k=0;
			while(pname){//�˴�δ��վ��������жϣ�������ʱ������ 	
				if(atoi(pname)!=0 && atoi(pname)!=lInfo->number && k<MAXTRANNUM){
					sInfo->transfer[k]=atoi(pname);
					k++;
				}
				pname=strtok(NULL, "|");
			}
			
			/*վ�㻻����Ϣ��ȡend*/ 
			
			lInfo->station[j]=*sInfo;//��վ����Ϣ��ֵ����· 
			
			if(sInfo->stationid<MaxVertexNum && G.data[sInfo->stationid].stationid==0){//��վ�㸳ֵ��ͼ��Ϣͷ 
				G.vexnum++; 
				G.data[sInfo->stationid]=*sInfo;
				
			}
			/*����վ���ڽӾ���*/
			
			if(GetIniKeyInt(linePath,tempch,"prior")==0 || GetIniKeyInt(linePath,tempch,"next")==0){//�ж��Ƿ����ǰ�����̣�����վ���� 
				if(j+1<=stationNum){
					itoa(j+1,tempch,10);
					temp=GetIniKeyInt(linePath,tempch,"stationid");
					templa=atof(GetIniKeyString(linePath,tempch,"latitude"));
					templng=atof(GetIniKeyString(linePath,tempch,"longitude"));
					if(templa==0){//���Ƿ��޾�γ�ȵ��жϣ����������վ��ͬ��γ�� 
						templa=sInfo->latitude;
					} 
					if(templng==0){
						templng=sInfo->longitude;
					}
					if(G.arcs[sInfo->stationid][temp].weight==0){//����ԳƸ�ֵ 
						G.arcs[sInfo->stationid][temp].weight=get_distance(sInfo->latitude,sInfo->longitude,templa,templng);
						G.arcnum++;
					}
					if(G.arcs[temp][sInfo->stationid].weight==0){
						G.arcs[temp][sInfo->stationid].weight=get_distance(sInfo->latitude,sInfo->longitude,templa,templng);
						G.arcnum++;
					}
					
					
					
				}
				if(j-1>=0){
					itoa(j-1,tempch,10);
					temp=GetIniKeyInt(linePath,tempch,"stationid");
					templa=atof(GetIniKeyString(linePath,tempch,"latitude"));
					templng=atof(GetIniKeyString(linePath,tempch,"longitude"));
					if(templa==0){//���Ƿ��޾�γ�ȵ��жϣ����������վ��ͬ��γ�� 
						templa=sInfo->latitude;
					} 
					if(templng==0){
						templng=sInfo->longitude;
					}
					if(G.arcs[sInfo->stationid][temp].weight==0){//����ԳƸ�ֵ
						G.arcs[sInfo->stationid][temp].weight=get_distance(sInfo->latitude,sInfo->longitude,templa,templng);
						G.arcnum++;
					}
					if(G.arcs[temp][sInfo->stationid].weight==0){
						G.arcs[temp][sInfo->stationid].weight=get_distance(sInfo->latitude,sInfo->longitude,templa,templng);
						G.arcnum++;
					}
				}	
				
			}else{//������ִ������ 
				itoa(j,tempch,10);
				prior=GetIniKeyInt(linePath,tempch,"priorstation");
				next=GetIniKeyInt(linePath,tempch,"nextstation");
				templa=atof(GetIniKeyString(linePath,tempch,"latitude"));
				templng=atof(GetIniKeyString(linePath,tempch,"longitude"));
				if(prior!=0 && prior<MaxVertexNum){
					if(templa==0){//���Ƿ��޾�γ�ȵ��жϣ��������ֵ����CBD�齭�³Ǿ�γ�� 
						templa=23.119293;
					} 
					if(templng==0){
						templng=113.321206;
					}
					if(G.arcs[sInfo->stationid][prior].weight==0){//����ԳƸ�ֵ
						G.arcs[sInfo->stationid][prior].weight=get_distance(sInfo->latitude,sInfo->longitude,templa,templng);
						G.arcnum++;
					}
					if(G.arcs[prior][sInfo->stationid].weight==0){
						G.arcs[prior][sInfo->stationid].weight=get_distance(sInfo->latitude,sInfo->longitude,templa,templng);
						G.arcnum++;
					}
				}
				
				
				if(next!=0 && next<MaxVertexNum){
					if(templa==0){//���Ƿ��޾�γ�ȵ��жϣ��������ֵ����CBD�齭�³Ǿ�γ�� 
						templa=23.119293;
					} 
					if(templng==0){
						templng=113.321206;
					}
					if(G.arcs[sInfo->stationid][next].weight==0){//����ԳƸ�ֵ
						G.arcs[sInfo->stationid][next].weight=get_distance(sInfo->latitude,sInfo->longitude,templa,templng);
						G.arcnum++;
					}
					if(G.arcs[next][sInfo->stationid].weight==0){
						G.arcs[next][sInfo->stationid].weight=get_distance(sInfo->latitude,sInfo->longitude,templa,templng);
						G.arcnum++;
					}
				}
				
			}
	
		}
		L[i]=*lInfo;
	}
	
	printf("��������%d,������%d",G.vexnum,G.arcnum);
	
}

/*���˵�*/ 
void menu(int opt){
	char ch;
	system("cls");
	if(opt==1){//�û�ģʽ 
		printf("\t\t\t\t|����������������������������������������|\n");
		printf("\t\t\t\t|     �� ��ӭʹ�õ�����Ϣ��ѯϵͳ ��     |\n");
		printf("\t\t\t\t|               ");
		color(2);
		printf("���û�ģʽ��");
		color(7);
		printf("             |\n");
		printf("\t\t\t\t|   1.·�߲�ѯ                           |\n");
		printf("\t\t\t\t|   2.վ����Ϣ��ѯ                       |\n");
//		printf("\t\t\t\t|   3.��ͼ�鿴                           |\n");
//		printf("\t\t\t\t|   4.Ʊ�۲�ѯ                           |\n");
		printf("\t\t\t\t|   3.Ʊ�۲�ѯ                           |\n");
		printf("\t\t\t\t|   4.��·�鿴                           |\n");
		printf("\t\t\t\t|                                 q.���� |\n");
		printf("\t\t\t\t|����������������������������������������|\n");
		printf("\t\t\t\t��������š�  ��\b\b\b\b");
		ch=getch();
		printf("%c",ch);
		switch(ch){
			case '1':RouteQuery();break;
			case '2':QuerySiteInformation(1);break;
//			case '3':ViewMap();break;
//			case '4':QueryTicketPrice();break;
			case '3':QueryTicketPrice();break;
			case '4':QueryLine();break;
			case 'q':mylogin();break;
			default:
				color(4);
				printf("\n\t\t\t\t�������1�������\b\b\b");
				color(7);
				Sleep(1000); 
				menu(1);break;
		}
	}else if(opt==2){//����Աģʽ 
		printf("\t\t\t\t|����������������������������������������|\n");
		printf("\t\t\t\t|     �� ��ӭʹ�õ�����Ϣ��ѯϵͳ ��     |\n");
		printf("\t\t\t\t|              ");
		color(4);
		printf("������Աģʽ��");
		color(7);
		printf("            |\n");
		printf("\t\t\t\t|   1.վ�����                           |\n");
		printf("\t\t\t\t|   2.վ��ɾ��                           |\n");
		printf("\t\t\t\t|   3.��·���                           |\n");
		printf("\t\t\t\t|   4.��·ɾ��                           |\n");
		printf("\t\t\t\t|   5.��·վ�����                       |\n");
		printf("\t\t\t\t|   6.��·��Ϣ�޸�                       |\n");
		printf("\t\t\t\t|   7.վ����Ϣ�޸�                       |\n");
		printf("\t\t\t\t|                                 q.���� |\n");
		printf("\t\t\t\t|����������������������������������������|\n");
		printf("\t\t\t\t��������š�  ��\b\b\b\b");
		ch=getch();
		printf("%c",ch);
		switch(ch){
			case '1':SiteAddition();break;
			case '2':SiteDeletion();break;
			case '3':LineAddition();break;
			case '4':LineDeletion();break;
			case '5':LineStaAddition();break;
			case '6':ModifyInfoMenu(1);break;
			case '7':ModifyInfoMenu(2);break;
			case 'q':mylogin();break;
			default:
				color(4);
				printf("\n\t\t\t\t�������1�������...");
				color(7);
				Sleep(1000); 
				menu(2);break;
		}
	}
	
}

/*����Ա�޸Ĳ˵�*/ 
void ModifyInfoMenu(int opt){//1�޸���·��Ϣ��2�޸�վ����Ϣ 
	char ch; 
	system("cls");
	if(opt==1){
		printf("\t\t\t\t|����������������������������������������|\n");
		printf("\t\t\t\t|            �� ����Աģʽ ��            |\n");
		printf("\t\t\t\t|            ����·��Ϣ�޸ġ�            |\n");
		printf("\t\t\t\t|   1.��·�����޸�                       |\n");
		printf("\t\t\t\t|   2.ƽ���ȴ�ʱ���޸�                   |\n");
//		printf("\t\t\t\t|   3.��·��ɫ�޸�                       |\n");
		printf("\t\t\t\t|                                 q.���� |\n");
		printf("\t\t\t\t|����������������������������������������|\n");
		printf("\t\t\t\t��������š�  ��\b\b\b\b");
		ch=getch();
		printf("%c",ch);
		switch(ch){
			case '1':LineNameModi();break;
			case '2':AverageTimeModi();break;
//			case '3':break;
			case 'q':menu(2);break;
			default:
				color(4);
				printf("\n\t\t\t\t�������1�������...");
				color(7);
				Sleep(1000); 
				ModifyInfoMenu(1);break;
		}
	}else if(opt==2){
		printf("\t\t\t\t|����������������������������������������|\n");
		printf("\t\t\t\t|            �� ����Աģʽ ��            |\n");
		printf("\t\t\t\t|            ��վ����Ϣ�޸ġ�            |\n");
		printf("\t\t\t\t|   1.վ�������޸�                       |\n");
		printf("\t\t\t\t|   2.ͣʼʱ���޸�                       |\n");
		printf("\t\t\t\t|   3.��γ���޸�                         |\n");
		printf("\t\t\t\t|   4.վ������޸�                       |\n");
		printf("\t\t\t\t|                                 q.���� |\n");
		printf("\t\t\t\t|����������������������������������������|\n");
		printf("\t\t\t\t��������š�  ��\b\b\b\b");
		ch=getch();
		printf("%c",ch);
		switch(ch){
			case '1':SiteNameModi();break;
			case '2':StoStaTimeModi();break;
			case '3':LaLoModi();break;
			case '4':SiteExitModi();break;
//			case '5':break;
			case 'q':menu(2);break;
			default:
				color(4);
				printf("\n\t\t\t\t�������1�������...");
				color(7);
				Sleep(1000); 
				ModifyInfoMenu(2);break;
		}
	}
	
	
}

/*��½*/ 
void mylogin(void){
	int input,i,time=1;
	char pr[20],word,ch;
	system("cls");
	printf("\n\n");
	printf("\t\t\t\t|����������������������������������������|\n");
	printf("\t\t\t\t|                                        |\n");
	printf("\t\t\t\t|     �� ��ӭʹ�õ�����Ϣ��ѯϵͳ ��     |\n");
	printf("\t\t\t\t|                                        |\n");
	printf("\t\t\t\t|             �����ˣ�̷����             |\n");
	printf("\t\t\t\t|                                        |\n");
	printf("\t\t\t\t|   ");
	color(2);
	printf("1.�û�ģʽ");
	color(7);
	printf("            ");
	color(4);
	printf("2.����Աģʽ");
	color(7);
	printf("   |\n");
	printf("\t\t\t\t|                 0.�˳�                 |\n");
	printf("\t\t\t\t|����������������������������������������|\n");
	printf("\t\t\t\t ��ѡ��ģʽ����  ��\b\b\b\b");
//	scanf("%1d",&input);
	ch=getch(); 
	printf("%c",ch);
	if(ch=='0'){
		printf("\n\t\t\t\t���Ժ�..."); 
		Sleep(300); 
		quit();
	}else if(ch=='1'){
		printf("\n\t\t\t\t���Ժ�..."); 
		Sleep(300); 
		menu(1);
	}else if(ch=='2'){
		printf("\n\t\t\t\t���Ժ�..."); 
		Sleep(300); 
		while(1){
			system("CLS");
			printf("\n\n");
			printf("\t\t\t\t|����������������������������������������|\n");
			printf("\t\t\t\t|                                        |\n");
			printf("\t\t\t\t|       �� ��ǰģʽ������Աģʽ ��       |\n");
			printf("\t\t\t\t|                                        |\n");
			printf("\t\t\t\t|����������������������������������������|\n");
			printf("\t\t\t\t ���������룺");
			i=0;
			while((word=getch())!='\r') 
			{
	            if(word=='\b' && i>0) 
				{
	                printf("\b \b");                 /*'\b'�������һ���ո�' '���滻�����һ���ַ�*/
	                --i;
	            }
	            else if(word!='\b') 
				{
	                pr[i++]=word;
	                printf("*");
	            }
			}
	        pr[i]='\0';
			if(strcmp(pr,ADMINPWD)==0)
			{
				color(2);
				printf("\n\t\t\t\t ��������ȷ!��\n");
				color(7);
				Sleep(500);
				system("CLS");
				break;
			}
			else
			{
				if(time>=MAXKEYERR){
//					system("CLS");
					color(4);
					printf("\n\t\t\t��������󡿴������� %d ��",MAXKEYERR);
					printf("\n\t\t\t2��󷵻�������...");
					Sleep(1000);
					printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b1��󷵻�������...");
					color(7);
					Sleep(1000);
					system("CLS");
					time=0;
					mylogin();
					break;
				}
				time++;
				color(4);
				printf("\n\t\t\t\t ����������!��\n");
				printf("\n\t\t\t\t ����2�����������������...");
				Sleep(1000);
				printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b1�����������������...");
				color(7);
				Sleep(1000);
				system("CLS");
				
			}
		}
		menu(2);
	}else{
		color(4);
		printf("\n\t\t\t\t���������1�������\b\b");
		color(7);
		Sleep(1000);
		mylogin();
	}
	
}

void quit(void){
	system("cls");
	printf("\t\t\t\t|����������������������������������������|\n");
	printf("\t\t\t\t|                                        |\n");
	printf("\t\t\t\t|                ��лʹ��                |\n");
	printf("\t\t\t\t|         �� ������Ϣ��ѯϵͳ ��         |\n");
	printf("\t\t\t\t|   ��Metro Information Query System��   |\n");
	printf("\t\t\t\t|                                        |\n");
	printf("\t\t\t\t|                                        |\n");
	printf("\t\t\t\t|            Made By ̷����              |\n");
	printf("\t\t\t\t|����������������������������������������|\n");
}

int main(void) {
	
	MaxLine=0;
	MaxStation=0;
	G.arcnum=0;
	G.vexnum=0;
	for(int i=0;i<MaxVertexNum;i++){
		for(int j=0;j<MaxVertexNum;j++){
			G.arcs[i][j].weight=0;
			for(int k=0;k<MAXEXITNUM;k++){
				G.data[i].exitdata[j].exitad[k][0]='\0';	
			}
			G.data[i].exitdata[j].exitname[0]='\0';
		}
		G.data[i].endonetime[0]='\0';
		G.data[i].endtwotime[0]='\0';
		G.data[i].namecn[0]='\0';
		G.data[i].nameen[0]='\0';
		G.data[i].startonetime[0]='\0';
		G.data[i].starttwotime[0]='\0';
		G.data[i].exitsum=0;
		G.data[i].latitude=0;
		G.data[i].lineno=0;
		G.data[i].longitude=0;
		G.data[i].stageseq=0;
		G.data[i].stationid=0;
		for(int k=0;k<MAXTRANNUM;k++){
			G.data[i].transfer[k]=0;
		}	
		G.data[i].x=0;
		G.data[i].y=0;
//		G.data[i].line.color[0]='\0';
//		G.data[i].line.color1[0]='\0';
//		G.data[i].line.end[0]='\0';
//		G.data[i].line.linecn[0]='\0';
//		G.data[i].line.lineen[0]='\0';
//		G.data[i].line.start[0]='\0';
//		G.data[i].line.averageintervaltime=0;
//		G.data[i].line.lastmodifytime=0;
//		G.data[i].line.lineno=0;
//		G.data[i].line.number=0;
//		G.data[i].line.stationsum=0;
		
	}


	init();
	
	mylogin();
	return 0;
}
