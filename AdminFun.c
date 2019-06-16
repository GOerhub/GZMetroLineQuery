#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <io.h>
#include <time.h>
#include "main.h"
#include "utility.h"
#include "AdminFun.h"
#include "UserFun.h"
extern Graph G;
extern lineinfo L[MAXLINESUM];
extern int  MaxLine;
extern int MaxStation;

/*�����·��Ϣ*///flag=0�������·վ�㣬flag=1�����
int AdminPrintLine(int flag){ 
	int lineSum,tempNo=-1;
	char temp[500]; 
	int i,re,num=1;
	char lineInfoPath[100]="data\\lineinfo.ini";
	lineSum=GetIniKeyInt(lineInfoPath,"config","linesum");
	for(i=0;i<lineSum;i++){
		if(L[i].number==9999 && flag==1){
			re=i; 
			continue; 
		}
		sprintf(temp,"%d.%s",num,L[i].linecn);
			printf("%-23s",temp);
		if((num)%3==0){
			printf("|\n\t\t\t|\t");	
		}
		num++;
	}	
	for(int j=0;j<3-(num-1)%3;j++){
		printf("%-23s"," ");
	}
	printf("|\n");
	return re;
}

/*���վ����Ϣ*/ 
void AdminPrintStation(int lNum){
	int lineSum;
	char temp[500]; 
	int i;
	char lineInfoPath[100]="data\\lineinfo.ini";
	lineSum=GetIniKeyInt(lineInfoPath,"config","linesum");

	for(i=0;i<L[lNum].stationsum;i++){
//		sprintf(temp,"(%d)",i+1);
//		printf("%-4s",temp);
//		sprintf(temp,"%s",L[lNum].station[i].namecn);
//		printf("%-19s",temp);
//		if((i+1)%3==0){
//			printf("|\n\t\t\t|\t");	
//		}
		sprintf(temp,"%d.%s",i+1,L[lNum].station[i].namecn);
		printf("%-23s",temp);
		if((i+1)%3==0){
			printf("|\n\t\t\t|\t");	
		}
	}
	for(int j=0;j<3-(i%3);j++){
		printf("%-23s"," ");
	}
	printf("|\n");
}

/*�������Ա��·ͷ*/ 
void AdminLineHead(void){
	color(7);
	//system("cls");
	printf("\t\t\t| �������������������������������������������������������������������������� |\n");
	printf("\t\t\t|                               ");
	color(2);
	printf("�� ����Աģʽ ��");
	color(7);
	printf("                             |\n");
	printf("\t\t\t|                                 ����·��Ϣ��                               |\n");
	printf("\t\t\t|                                                                            |\n");
	printf("\t\t\t|\t"); 
} 

/*�������Ավ��ͷ*/ 
void AdminStationHead(void){
	color(7);
	//system("cls");
	printf("\t\t\t| �������������������������������������������������������������������������� |\n");
	printf("\t\t\t|                               ");
	color(2);
	printf("�� ����Աģʽ ��");
	color(7);
	printf("                             |\n");
	printf("\t\t\t|                                 ��վ����Ϣ��                               |\n");
	printf("\t\t\t|                                                                            |\n");
	printf("\t\t\t|\t"); 
} 

/*�������Ավ��ͷ2*/ 
void AdminStationHead2(void){
	printf("\t\t\t| ������������������������������������������������������������������|\n");
	printf("\t\t\t|                          ");
	color(2);
	printf("�� ����Աģʽ ��");
	color(7);
	printf("                         |\n");
	printf("\t\t\t|                          �����վ����Ϣ��                         |\n");
	printf("\t\t\t|                                                                   |\n");
} 

/*�������Ավ��β2*/ 
void AdminStationTail2(void){
	printf("\t\t\t|                                                                   |\n");
	printf("\t\t\t| ������������������������������������������������������������������|\n");
}

/*�������Ավ��β��ѡ��*/ 
void AdminStationTailAllNo(void){
	color(7);
	printf("\t\t\t|                                                                            |\n");
	printf("\t\t\t|                                                                            |\n");
	printf("\t\t\t|  ��������������������������������������������������������������������������|\n");
}

/*�������Ավ��β��ѡ��*/ 
void AdminStationTailNoM(void){
	color(7);
	printf("\t\t\t|                                                                            |\n");
	printf("\t\t\t|                                                              q.����        |\n");
	printf("\t\t\t|  ��������������������������������������������������������������������������|\n");
}

/*�������Ավ��β*/ 
void AdminStationTail(void){
	color(7);
	printf("\t\t\t|                                                                            |\n");
	printf("\t\t\t|        m.���˵�                                              q.����        |\n");
	printf("\t\t\t|  ��������������������������������������������������������������������������|\n");
}

/*������վ����Ϣ*/ 
void PrintAddStaInfo(int lNum,int sNum){
	int lindex=-1,sindex=-1;
	AdminStationHead2();
	if(lNum==9999){
		for(int i=MAXLINESUM-1;i>=0;i--){
			if(L[i].number==9999){
				lindex=i;
			}
		}
		for(int i=L[lindex].stationsum-1;i>=0;i--){
			if(L[lindex].station[i].stationid==sNum){
				sindex=i;
			}
			
		}
		if(lindex!=-1 && sindex!=-1){
			PrintStationInfo(lindex,sindex);
		}
		
	}else{
		PrintStationInfo(lNum,sNum);
	}
	
	AdminStationTail2(); 
}

/*������·վ����*/ 
int ReturnLineStaSum(int lineNo){
	for(int i=0;i<=MaxLine;i++){
		if(L[i].number==lineNo){
			return L[i].stationsum;
		}
	}
	return -1;
}

/*վ�����*/ 
void SiteAddition(void){
	stationinfo station;
	int lineNum,stationNum,tempNo,lineSum,LineNum,flag=0,trueInput=0,lindex=0,lnum=0,snum=0;
	char lineInfoPath[100]="data\\lineinfo.ini";
	lineSum=GetIniKeyInt(lineInfoPath,"config","linesum");
	/*վ���ʼ��start*/ 
	station.endonetime[0]='\0';
	station.endtwotime[0]='\0';
	station.namecn[0]='\0';
	station.nameen[0]='\0';
	station.startonetime[0]='\0';
	station.starttwotime[0]='\0';
	station.exitsum=0;
	station.latitude=0;
	station.longitude=0;
	station.stageseq=0;
	station.stationid=0;
	station.lineno=0;
	station.x=0;
	station.y=0;
	for(int k=0;k<MAXTRANNUM;k++){
		station.transfer[k]=0;
	}
	for(int i=0;i<MAXEXITNUM;i++){
		for(int k=0;k<MAXEXITNUM;k++){
			station.exitdata[i].exitad[k][0]='\0';
			
		}
		station.exitdata[i].exitname[0]='\0';
	}
	/*վ���ʼ��end*/
		
	char ch; 
	system("cls");
	printf("\t\t\t\t| ����������������������������������������������|\n");
	printf("\t\t\t\t|                ");
	color(4);
	printf("�� ����Աģʽ ��");
	color(7);
	printf("               |\n");
	printf("\t\t\t\t|                  ��վ����ӡ�                 |\n");
	printf("\t\t\t\t|                                               |\n");
	printf("\t\t\t\t| ����������������������������������������������|\n");
	printf("\t\t\t\t��������Ҫ��ӵ�վ�����ƣ�"); 
	color(9);
	scanf("%s",&station.namecn);
	MaxStation=MaxStation+1;
	while(!trueInput){
		color(7);
		printf("\t\t\t\t�����Ƿ����վ��Ӣ����[Y/N]:");
		color(9);
		ch=getch();
		printf("%c\n",ch);
		color(7);
		switch(ch){
			case 'Y':
			case 'y':
				printf("\t\t\t\t������վ��Ӣ������");
				color(9);
				scanf("%s",&station.nameen); 
				color(7);trueInput=1;break;
			case 'N':
			case 'n':trueInput=1;break;
			default:
				trueInput=0;
				color(4);
				printf("\t\t\t\t���������\n");
				color(7);
		}
		
	}
	
	printf("\t\t\t\t�����������װ೵ʱ��(����6:30)��");
	color(9);
	scanf("%s",&station.startonetime); 
	color(7);
	printf("\t\t\t\t����������ĩ�೵ʱ��(����23:30)��");
	color(9);
	scanf("%s",&station.endonetime); 
	color(7);
	printf("\t\t\t\t�����������װ೵ʱ��(����6:30)��");
	color(9);
	scanf("%s",&station.starttwotime); 
	color(7);
	printf("\t\t\t\t����������ĩ�೵ʱ��(����23:30)��");
	color(9);
	scanf("%s",&station.endtwotime); 
	trueInput=0;
	while(!trueInput){
		color(7);
		printf("\t\t\t\t�����Ƿ����վ�����[Y/N]:");
		color(9);
		ch=getch();
		printf("%c\n",ch);
		color(7);
		switch(ch){
			case 'Y':
			case 'y':
				printf("\t\t\t\t������վ�����������");
				color(9);
				scanf("%d",&station.exitsum); 
				color(7);
				for(int i=0;i<station.exitsum;i++){
					printf("\t\t\t\t�������%d����������(����A����)��",i+1);
					color(9);
					scanf("%s",&station.exitdata[i]);
					color(7);
					printf("\t\t\t\t������ó��ڵص�������");
					color(9);
					scanf("%d",&station.exitdata[i].adnum); 
					color(7);
					for(int j=0;j<station.exitdata[i].adnum;j++){
						printf("\t\t\t\t�������%d���ص�(����������ѧԺ)��",j+1);
						color(9);
						scanf("%s",&station.exitdata[i].exitad[j]);
						color(7);
					}
					
				}
				trueInput=1;break;
			case 'N':
			case 'n':trueInput=1;break;
			default:
				trueInput=0;
				color(4);
				printf("\t\t\t\t���������\n");
				color(7);
		}
		
	}
	
	trueInput=0;
	while(!trueInput){
		printf("\t\t\t\t�����Ƿ����վ��ľ�γ������(���������Զ����������ľ�γ��)[Y/N]:");
		color(9);
		ch=getch();
		printf("%c\n",ch);
		color(7);
		switch(ch){
			case 'Y':
			case 'y':
				printf("\t\t\t\t�����뾭��(�磺113.321206)��");
				color(9);
				scanf("%lf",&station.longitude); 
				color(7);
				printf("\t\t\t\t������γ��(�磺23.119293)��");
				color(9);
				scanf("%lf",&station.latitude); 
				color(7);trueInput=1;break; 
			case 'N':
			case 'n':trueInput=1;break;
			default:
				trueInput=0;
				color(4);
				printf("\t\t\t\t���������\n");
				color(7);
		}
	}
	trueInput=0;
	while(!trueInput){
		printf("\t\t\t\t�����Ƿ�����վ������·�����ܴ�������·ѡ��,��������Ϊ����վ��)[Y/N]:");
		color(9);
		ch=getch();
		printf("%c\n",ch);
		color(7);
		switch(ch){
			case 'Y':
			case 'y':
				lindex=SelectAddres(&station,1,&lnum,&snum);
			case 'N':
			case 'n':trueInput=1;break;
			default:
				trueInput=0;
				color(4);
				printf("\t\t\t\t���������\n");
				color(7);
		}
	}
	if(station.lineno==0){
		station.lineno=9999;
		for(int i=0;i<=MaxLine;i++){
			if(L[i].number==9999){
				station.stageseq=L[i].station[L[i].stationsum].stageseq+1;
				L[i].station[L[i].stationsum]=station;
				L[i].stationsum++;
				lindex=i; 
				
			}
		}
		
	}
	
//	station.stationid=MaxStation;
	G.data[station.stationid]=station;
	G.vexnum++;
	printf("\t\t\t\t����������Ժ�....\n");
	if(AdditionWrite(station.stationid,lindex)!=-1){
		color(2);
		printf("\t\t\t\t��ӳɹ�\n");
		color(7);
		printf("\n\t\t\t����ӵ���Ϣ���£�\n");
		if(station.lineno==9999){
			PrintAddStaInfo(9999,0);
		}else{
			PrintAddStaInfo(lnum,snum);
		}
		printf("\n\t\t\t���������ַ��������˵�����  ��\b\b\b\b");
		ch=getch();
		menu(2);

	}else{
		color(4);
		printf("\t\t\t���ʧ��\n");
		color(7);
		printf("\n\t\t\t���������ַ��������˵�����  ��\b\b\b\b");
		ch=getch();
		menu(2);
	}
	
}

/*վ��ѡ��*/ 
int SelectAddres(stationinfo *station,int code,int *lnum,int *snum){
	int LineNum,lineSum,stationNum,flag,nrindex;
	char sch[5];
	char lineInfoPath[100]="data\\lineinfo.ini";
	lineSum=GetIniKeyInt(lineInfoPath,"config","linesum");
	while(1){
		if(code=1){
			system("cls");
			AdminLineHead();
			nrindex=AdminPrintLine(1);
			AdminStationTailAllNo();
			printf("\t\t\t��������·��ţ���  ��\b\b\b\b");
			color(9);
			scanf("%d",&LineNum); 
			if(nrindex<LineNum){
				LineNum++;
			}
			color(7);
			while(LineNum<=0 && LineNum-1>=lineSum && L[LineNum-1].stationsum>=MAXSTATIONSUM && nrindex!=LineNum){
				color(4);
				printf("\t\t\t�������\n");
				if(L[LineNum-1].stationsum>=MAXSTATIONSUM){
					printf("\t\t\t����·վ��������\n"); 
				}
				color(7);
				printf("\t\t\t������������·��ţ���  ��\b\b\b\b");
				color(9);
				scanf("%d",&LineNum); 
				if(nrindex<LineNum){
					LineNum++;
				}
			}
			color(7);
			station->lineno=L[LineNum-1].lineno;
			code=2;
		}
		
		
		if(code==2){
			if(L[LineNum-1].stationsum!=0){
				AdminStationHead(); 
				AdminPrintStation(LineNum-1);
				AdminStationTailNoM();
				printf("\t\t\t���������λ����ţ���  ��\b\b\b\b");
				color(9);
				scanf("%s",&sch); 
				if(strcmp(sch,"q")==0){
					code=1;
					continue;
				}else{
					stationNum=atoi(sch);
				}
				color(7);
				while(stationNum<=0 && stationNum>=L[LineNum-1].stationsum){
					color(4);
					printf("\t\t\t�������\n");
					color(7);
					printf("\t\t\t�����²���λ����ţ���  ��\b\b\b\b");
					color(9);
					scanf("%s",sch); 
					if(strcmp(sch,"q")==0){
						code=1;
						continue;
					}else{
						stationNum=atoi(sch);
					}
					
				}
				L[LineNum-1].stationsum++;
			}else{
				stationNum=1;
			}
			
			for(int i=L[LineNum-1].stationsum-1;i>=0;i--){
				if(stationNum<=i){//����վ�� 
					L[LineNum-1].station[i]=L[LineNum-1].station[i-1];
					L[LineNum-1].station[i].stageseq=L[LineNum-1].station[i].stageseq+1;
				}else{
					if(i!=0){
						station->stageseq=L[LineNum-1].station[i-1].stageseq+1;
					}else{
						station->stageseq=L[LineNum-1].station[i+1].stageseq-1;
					}
					
					if(station->latitude==0 || station->longitude==0){//����γ�� 
						if(L[LineNum-1].station[i+1].latitude==0){
							station->latitude=L[LineNum-1].station[i-1].latitude+0.000010;
						}else{
							station->latitude=(L[LineNum-1].station[i-1].latitude+L[LineNum-1].station[i+1].latitude)*0.5;
						}
						if(L[LineNum-1].station[i+1].longitude==0){
							station->longitude=L[LineNum-1].station[i-1].longitude+0.000010;
						}else{
							station->longitude=(L[LineNum-1].station[i-1].longitude+L[LineNum-1].station[i+1].longitude)*0.5;
						}
					}
					if(L[LineNum-1].station[i+1].stationid!=0){//�����ڽӾ��� 
						if(station->latitude!=0 && station->longitude!=0 && L[LineNum-1].station[i+1].latitude!=0 && L[LineNum-1].station[i+1].longitude!=0){
							G.arcs[station->stationid][L[LineNum-1].station[i+1].stationid].weight=get_distance(station->latitude,station->longitude,L[LineNum-1].station[i+1].latitude,L[LineNum-1].station[i+1].longitude);
							G.arcs[L[LineNum-1].station[i+1].stationid][station->stationid].weight=get_distance(station->latitude,station->longitude,L[LineNum-1].station[i+1].latitude,L[LineNum-1].station[i+1].longitude);
							flag=1;
							G.arcnum=G.arcnum+2;
						}
						
					}
					
					if(L[LineNum-1].station[i-1].stationid!=0){
						if(station->latitude!=0 && station->longitude!=0 && L[LineNum-1].station[i-1].latitude!=0 && L[LineNum-1].station[i-1].longitude!=0){
							G.arcs[station->stationid][L[LineNum-1].station[i-1].stationid].weight=get_distance(station->latitude,station->longitude,L[LineNum-1].station[i-1].latitude,L[LineNum-1].station[i-1].longitude);
							G.arcs[L[LineNum-1].station[i-1].stationid][station->stationid].weight=get_distance(station->latitude,station->longitude,L[LineNum-1].station[i-1].latitude,L[LineNum-1].station[i-1].longitude);
							G.arcnum=G.arcnum+2;
							if(flag==1){
								G.arcs[L[LineNum-1].station[i+1].stationid][L[LineNum-1].station[i-1].stationid].weight=0;
								G.arcs[L[LineNum-1].station[i-1].stationid][L[LineNum-1].station[i+1].stationid].weight=0;
								G.arcnum=G.arcnum-2;
							}
						}
					}
					//L[LineNum-1].station[i]=L[LineNum-1].station[i-1];
					//L[LineNum-1].station[i].stageseq=L[LineNum-1].station[i].stageseq+1;
					
					station->stationid=MaxStation;
					for(int i=0;i<MAXTRANNUM;i++){//���»������� 
						if(station->transfer[i]==0){
							station->transfer[i]=L[LineNum-1].number;
						}
					}
					
					L[LineNum-1].station[i]=*station;
					code=3;
					break; 

					
					
					
				}
			}
		}
		
		if(code==3){
			break;
		}
	}
	*lnum=LineNum-1;
	*snum=stationNum-1;
	return LineNum-1;
} 

/*���վ��д��*/ 
int AdditionWrite(int sid,int lindex){
	char title[5],key[30],temp[200],temp1[200];
	char lineInfoPath[100]="data\\lineinfo.ini",linePath[100];
//	itoa(L[lindex].number,key,10);
	BuildPath(L[lindex].number,linePath);
	for(int i=L[lindex].stationsum;i>=0;i--){
		if(L[lindex].station[i].stationid==G.data[sid].stationid){
			itoa(i,title,10);
			itoa(i+1,key,10);
			ChangeIniTitle(linePath,title,key);
			break;
		}
		itoa(i,title,10);
		itoa(i+1,key,10);
		ChangeIniTitle(linePath,title,key);
	}
	for(int i=0;i<L[lindex].stationsum;i++){
		itoa(i,title,10);
		PutIniKeyInt(linePath,title,"stageseq", L[lindex].station[i].stageseq);
		if(i==0){	
			PutIniKeyInt(linePath,"config","stationsum", L[lindex].stationsum);
			sprintf(temp,"��%s",L[lindex].station[i].namecn); 
			PutIniKeyString(linePath,"config","startone", temp);
			sprintf(temp,"��%s",L[lindex].station[L[lindex].stationsum-1].namecn); 
			PutIniKeyString(linePath,"config","starttow", temp);
			sprintf(temp,"��%s",L[lindex].station[i].namecn); 
			PutIniKeyString(linePath,"config","endone", temp);
			sprintf(temp,"��%s",L[lindex].station[L[lindex].stationsum-1].namecn); 
			PutIniKeyString(linePath,"config","endtow", temp);
		}

		if(L[lindex].station[i].stationid==G.data[sid].stationid){
			PutIniKeyInt(linePath,title,"lineno", L[lindex].station[i].lineno);
			PutIniKeyInt(linePath,title,"stationid", L[lindex].station[i].stationid);
			PutIniKeyString(linePath,title,"namecn", L[lindex].station[i].namecn);
			PutIniKeyString(linePath,title,"nameen", L[lindex].station[i].nameen);
			PutIniKeyString(linePath,title,"startone", L[lindex].station[i].startonetime);
			PutIniKeyString(linePath,title,"starttow", L[lindex].station[i].starttwotime);
			PutIniKeyString(linePath,title,"endone", L[lindex].station[i].endonetime);
			PutIniKeyString(linePath,title,"endtow", L[lindex].station[i].endtwotime);
			sprintf(temp,"%lf",L[lindex].station[i].longitude);
			PutIniKeyString(linePath,title,"longitude", temp);
			sprintf(temp,"%lf",L[lindex].station[i].latitude);
			PutIniKeyString(linePath,title,"latitude", temp);
			int j=0;
			temp[0]='\0';
			temp1[0]='\0';
			while(L[lindex].station[i].transfer[j]!=0){
				sprintf(temp1,"|%d",L[lindex].station[i].transfer[j]);
				strcpy(temp,temp1);
				j++;
			}
			PutIniKeyString(linePath,title,"transfer", temp);
			j=0;

			char exitsta1[500],exitsta[500],ich[10];
			exitsta[0]='\0';
			exitsta1[0]='\0';
			temp[0]='\0';
			temp1[0]='\0';
			while(L[lindex].station[i].exitdata[j].exitname[0]!='\0'){
				sprintf(temp1,"|%s",L[lindex].station[i].exitdata[j].exitname);
				strcat_s(temp,sizeof(temp),temp1);
				exitsta[0]='\0';
				exitsta1[0]='\0';
				for(int k=0;k<L[lindex].station[i].exitdata[j].adnum;k++){
					sprintf(exitsta1,"|%s",L[lindex].station[i].exitdata[j].exitad[k]);
					strcat_s(exitsta,sizeof(temp),exitsta1);
				}
				itoa(j+1,ich,10);
				PutIniKeyString(linePath,title,ich, exitsta);
				j++;
			}
			PutIniKeyInt(linePath,title,"exitsum", L[lindex].station[i].exitsum);
			PutIniKeyString(linePath,title,"exitname", temp);

		}
	}
	
	return 1;
}

/*վ��ɾ��*/ 
void SiteDeletion(){
	stationinfo station;
	int LineNum,lineSum,stationNum,flag,code=1,fin=1,trueInput=0;
	char sch[5],lch[5];
	char lineInfoPath[100]="data\\lineinfo.ini";
	lineSum=GetIniKeyInt(lineInfoPath,"config","linesum");
	/*��ʼ��station*/
	station.endonetime[0]='\0';
	station.endtwotime[0]='\0';
	station.namecn[0]='\0';
	station.nameen[0]='\0';
	station.startonetime[0]='\0';
	station.starttwotime[0]='\0';
	station.exitsum=0;
	station.latitude=0;
	station.longitude=0;
	station.stageseq=0;
	station.stationid=0;
	station.lineno=0;
	station.x=0;
	station.y=0;
	/*��ʼ������*/ 
	while(1){
		if(code==1){
			system("cls");
			AdminLineHead();
			AdminPrintLine(0);
			AdminStationTailNoM();
			printf("\t\t\t��������·��ţ���  ��\b\b\b\b");
			color(9);
			scanf("%s",&lch); 
			color(7);
			if(strcmp(lch,"q")==0){
				menu(2);break;
			}else{
				LineNum=atoi(lch);
				color(7);
				code=2;
			}
			while(LineNum<=0 && LineNum-1>=lineSum){
				color(4);
				printf("\t\t\t�������\n");
				color(7);
				printf("\t\t\t������������·��ţ���  ��\b\b\b\b");
				color(9);
				scanf("%s",&lch); 
				color(7);
				if(strcmp(sch,"q")==0){
					menu(2);break;
				}else{
					LineNum=atoi(lch);
					color(7);
					code=2;break;
				} 
				
			}
			
		}
		
		
		if(code==2){
			system("cls");
			AdminStationHead(); 
			AdminPrintStation(LineNum-1);
			AdminStationTail();
			printf("\t\t\t������ɾ��վ����ţ���  ��\b\b\b\b");
			color(9);
			scanf("%s",&sch); 
			if(strcmp(sch,"q")==0){
				code=1;
				continue;
			}else if(strcmp(sch,"m")==0){
				menu(2);break;
			}else{
				stationNum=atoi(sch);break;
			}
			color(7);
			while(stationNum<=0 && stationNum>=L[LineNum-1].stationsum){
				color(4);
				printf("\t\t\t�������\n");
				color(7);
				printf("\t\t\t������ɾ��վ����ţ���  ��\b\b\b\b");
				color(9);
				scanf("%s",sch); 
				if(strcmp(sch,"q")==0){
					code=1;
					continue;
				}else if(strcmp(sch,"m")==0){
					menu(2);break;
				}else{
					stationNum=atoi(sch);break;
				}
				
			}
			code=3;
			break;	
		}
		
		
		
	}
	char ch;
	while(!trueInput){
		color(4);
		printf("\t\t\t��ȷ��Ҫɾ����վ�㣿�˲���������[Y/N]��  ��\b\b\b\b"); 
		color(9);
		char ch=getch();
		color(7);
		switch(ch){
			case 'Y':
			case 'y':
				printf("\n\t\t\t����ɾ�����Ժ�.....\n"); 
				DeleteStaMem(station,code,LineNum,stationNum);//���ú���ɾ��������վ����Ϣ 
				trueInput=1;break;
			case 'N':
			case 'n':menu(2);trueInput=1;break;
			default:
				trueInput=0;
				color(4);
				printf("\t\t\t���������\n");
				color(7);
		}
		
	}

}

/*վ�����ɾ��*/ 
void DeleteStaMem(stationinfo station,int code,int LineNum,int stationNum){
	int fin=1;
	/*���G�ڵ�վ������*/
	if(code=3){
		G.data[L[LineNum-1].station[stationNum-1].stationid]=station;
		G.vexnum--;
		for(int i=0;i<=MaxStation;i++){
			if(G.arcs[L[LineNum-1].station[stationNum-1].stationid][i].weight!=0){
				G.arcs[L[LineNum-1].station[stationNum-1].stationid][i].weight=0;
				G.arcnum--;
			}
			
		}
		if(MaxStation==L[LineNum-1].station[stationNum-1].stationid){
			MaxStation--;
		}
		
		/*���L�ڵ�վ������*/
		
		L[LineNum-1].stationsum--;
		fin=DeleteStaWrite(stationNum-1,LineNum-1); //���ú���ɾ���ļ���վ����Ϣ 
		for(int i=0;i<=L[LineNum-1].stationsum-1;i++){
			if(i>=stationNum-1){
				L[LineNum-1].station[i]=L[LineNum-1].station[i+1];
				L[LineNum-1].station[i].stageseq=L[LineNum-1].station[i].stageseq-1;
			}
		}
		L[LineNum-1].station[L[LineNum-1].stationsum]=station;
		
	}
	char ch;
	if(fin!=EOF){
		color(2);
		printf("\t\t\tɾ���ɹ�");
		color(7);
		printf("\n\t\t\t���������ַ��������˵�����  ��\b\b\b\b");
		ch=getch();
		menu(2);

	}else{
		color(4);
		printf("\t\t\tɾ��ʧ��");
		color(7);
		printf("\n\t\t\t���������ַ��������˵�����  ��\b\b\b\b");
		ch=getch();
		menu(2);
	}
	
}

/*վ��ɾ�������ļ�*/ 
int DeleteStaWrite(int sNum,int lindex){
	char title[5],key[5],temp[200];
	char lineInfoPath[100]="data\\lineinfo.ini",linePath[100];
	int code=0,flag=0;
//	itoa(L[lindex].number,key,10);
	BuildPath(L[lindex].number,linePath);

	for(int i=0;i<L[lindex].stationsum+1;i++){
		itoa(i,title,10);
		if(i==0){	
			PutIniKeyInt(linePath,"config","stationsum", L[lindex].stationsum);
			sprintf(temp,"��%s",L[lindex].station[i].namecn); 
			PutIniKeyString(linePath,"config","startone", temp);
			sprintf(temp,"��%s",L[lindex].station[L[lindex].stationsum-1].namecn); 
			PutIniKeyString(linePath,"config","starttow", temp);
			sprintf(temp,"��%s",L[lindex].station[i].namecn); 
			PutIniKeyString(linePath,"config","endone", temp);
			sprintf(temp,"��%s",L[lindex].station[L[lindex].stationsum-1].namecn); 
			PutIniKeyString(linePath,"config","endtow", temp);
		}
		if(L[lindex].station[i].stationid==L[lindex].station[sNum].stationid){
			itoa(i,title,10);
			code=DeleteIniSection(linePath,title);
		}
		
		if(L[lindex].station[i].stationid==L[lindex].station[sNum].stationid){
			flag=1;
			continue;
		}
		if(flag==1){
			PutIniKeyInt(linePath,title,"stageseq", L[lindex].station[i-1].stageseq);
		}
		
		
	}
	flag=0;
	for(int i=0;i<=L[lindex].stationsum+1;i++){
		if(L[lindex].station[i].stationid==L[lindex].station[sNum].stationid){
			flag=1;
			continue;
		}
		if(flag!=0){
			itoa(i,title,10);
			itoa(i-1,key,10);
			code=ChangeIniTitle(linePath,title,key);
		}
		
	}
	
	return code;
}

/*ѡ��վ��*/ 
int SelectSta(int i){
	int LineNum,lineSum,stationNum,code,nrindex;
	char sch[5];
	char lineInfoPath[100]="data\\lineinfo.ini";
	lineSum=GetIniKeyInt(lineInfoPath,"config","linesum");
	while(code!=3){
		if(code=1){
			system("cls");
			AdminLineHead();
			nrindex=AdminPrintLine(1);
			AdminStationTailAllNo();
			printf("\t\t\t�������%d������·��ţ���  ��\b\b\b\b",i);
			color(9);
			scanf("%d",&LineNum); 
			if(nrindex<LineNum){
				LineNum++;
			}
			color(7);
			while(LineNum<=0 && LineNum-1>=lineSum && nrindex!=LineNum){
				color(4);
				printf("\t\t\t�������\n");
				color(7);
				printf("\t\t\t�����������%d������·��ţ���  ��\b\b\b\b",i);
				color(9);
				scanf("%d",&LineNum); 
				if(nrindex<LineNum){
					LineNum++;
				}
			}
			color(7);
			code=2;
		}
		
		
		if(code==2){
			system("cls");
			AdminStationHead(); 
			AdminPrintStation(LineNum-1);
			AdminStationTailNoM();
			printf("\t\t\t�������%d����վ����ţ���  ��\b\b\b\b",i);
			color(9);
			scanf("%s",&sch); 
			if(strcmp(sch,"q")==0){
				code=1;
				continue;
			}else{
				stationNum=atoi(sch);
				code=3;
			}
			color(7);
			while(stationNum<=0 && stationNum>=L[LineNum-1].stationsum){
				color(4);
				printf("\t\t\t�������\n");
				color(7);
				printf("\t\t\t�����µ�%d����վ����ţ���  ��\b\b\b\b",i);
				color(9);
				scanf("%s",sch); 
				if(strcmp(sch,"q")==0){
					code=1;
					continue;
				}else{
					stationNum=atoi(sch);
					code=3;
				}
				
			}
		}
	}
	return L[LineNum-1].station[stationNum-1].stationid;
} 

/*��·վ������*/ 
int LineStaLink(lineinfo *line){
	int trueInput=0,stationid=0;
	char ch;
	while(!trueInput){
		color(7);
		printf("\t\t\t\t�����Ƿ�Ϊ���߱���վ��[Y/N]:");
		color(9);
		ch=getch();
		printf("%c\n",ch);
		color(7);
		switch(ch){
			case 'Y':
			case 'y':
				printf("\t\t\t\t������վ��������");
				color(9);
				scanf("%d",&(line->stationsum)); 
				color(7);
				for(int i=0;i<line->stationsum;i++){
					stationid=SelectSta(i+1);
					if(i==0){
						sprintf(line->start,"��%s",G.data[stationid].namecn);
					} 
					if(i==line->stationsum-1){
						sprintf(line->end,"��%s",G.data[stationid].namecn);
					}
					for(int j=0;j<MAXTRANNUM;j++){
						if(G.data[stationid].transfer[j]==0){
							G.data[stationid].transfer[j]=line->number;
							break;
						}
						
					}
					memcpy(&(line->station[i]),&(G.data[stationid]),sizeof(G.data[stationid]));
					//line->station[i]=G.data[stationid];
					line->station[i].stageseq=i+1;
					line->station[i].lineno=line->lineno;
					
					
				}
				trueInput=1;break;
			case 'N':
			case 'n':trueInput=1;break;
			default:
				trueInput=0;
				color(4);
				printf("\t\t\t\t���������\n");
				color(7);
		}
		
	}
} 

/*��·���*/ 
void LineAddition(void){
	static lineinfo line;
	char lineInfoPath[100]="data\\lineinfo.ini";
	int lineSum=GetIniKeyInt(lineInfoPath,"config","linesum"),trueInput=0;
	/*��·��ʼ��start*/ 
	line.averageintervaltime=0;
	line.lastmodifytime=0;
	line.lineno=0;
	line.number=0;
	line.stationsum=0;
	line.color[0]='\0';
	line.color1[0]='\0';
	line.end[0]='\0';
	line.linecn[0]='\0';
	line.lineen[0]='\0';
	line.start[0]='\0';
	/*��·��ʼ��end*/ 
	char ch; 
	system("cls");
	printf("\t\t\t\t| ����������������������������������������������|\n");
	printf("\t\t\t\t|                ");
	color(4);
	printf("�� ����Աģʽ ��");
	color(7);
	printf("               |\n");
	printf("\t\t\t\t|                  ����·��ӡ�                 |\n");
	printf("\t\t\t\t|                                               |\n");
	printf("\t\t\t\t| ����������������������������������������������|\n");
	printf("\t\t\t\t��������Ҫ��ӵ���·���ƣ�"); 
	color(9);
	scanf("%s",&line.linecn);
	MaxLine=MaxLine+1;
	while(!trueInput){
		color(7);
		printf("\t\t\t\t�����Ƿ������·Ӣ����[Y/N]:");
		color(9);
		ch=getch();
		printf("%c\n",ch);
		color(7);
		switch(ch){
			case 'Y':
			case 'y':
				printf("\t\t\t\t��������·Ӣ������");
				color(9);
				scanf("%s",&line.lineen); 
				color(7);trueInput=1;break;
			case 'N':
			case 'n':trueInput=1;break;
			default:
				trueInput=0;
				color(4);
				printf("\t\t\t\t���������\n");
				color(7);
		}
		
	}
	
	color(7);
	printf("\t\t\t\t��������·ƽ���ȴ�ʱ�䣺  ����\b\b\b\b\b\b");
	color(9);
	scanf("%d",&line.averageintervaltime); 
	line.averageintervaltime=line.averageintervaltime*60;
	color(7);
	printf("\t\t\t\t�������ߺţ�");
	color(9);
	scanf("%d",&line.lineno); 
	line.number=MaxLine;
	trueInput=0;
	time_t t;
	t = time(NULL);
	line.lastmodifytime=time(&t);//���뵱ǰʱ���
	LineStaLink(&line); //������·վ�� 
	MaxLine++;
	//end 
	if(lineSum>MAXLINESUM){
		printf("\t\t\t\t������·ʧ�ܣ����������·��"); 
	}else{
		L[lineSum]=line;
		for(int i=0;i<line.stationsum;i++){
			for(int j=0;j<MaxLine-1;j++){
				for(int k=0;k<L[j].stationsum;k++){
					if(L[j].station[k].stationid==line.station[i].stationid){
						for(int r=0;r<MAXTRANNUM;r++){
							if(L[j].station[k].transfer[r]==line.number){
								break;
							}
							if(L[j].station[k].transfer[r]==0 && r>=0 && r<MAXTRANNUM){
								L[j].station[k].transfer[r]=line.number;
								break;
							}
						}
					}
				}
			}
		}

		
		
		for(int i=1;i<L[lineSum].stationsum;i++){//������� 
			G.arcs[L[lineSum].station[i].stationid][L[lineSum].station[i-1].stationid].weight=get_distance(L[lineSum].station[i].latitude,L[lineSum].station[i].longitude,L[lineSum].station[i-1].latitude,L[lineSum].station[i-1].longitude);
			G.arcs[L[lineSum].station[i-1].stationid][L[lineSum].station[i].stationid].weight=get_distance(L[lineSum].station[i].latitude,L[lineSum].station[i].longitude,L[lineSum].station[i-1].latitude,L[lineSum].station[i-1].longitude);
			G.arcnum++;
		}
		
		 
	}
	
	printf("\t\t\t�����,���Ժ�...");
	L[lineSum]=line;
	if(LineAdditionWrite(&line)!=-1){
		color(2);
		printf("\t\t\t��ӳɹ�");
		color(7);
		printf("\n\t\t\t����ӵ���Ϣ���£�\n");
		PrintLineInfo(lineSum);
		printf("\n\t\t\t���������ַ��������˵�����  ��\b\b\b\b");
		ch=getch();
		menu(2);

	}else{
		color(4);
		printf("\t\t\t���ʧ��");
		color(7);
		printf("\n\t\t\t���������ַ��������˵�����  ��\b\b\b\b");
		ch=getch();
		menu(2);
	}
	
} 

/*��·���д��*/ 
int LineAdditionWrite(lineinfo *line){
	char title[5],title1[5],key[30],temp[200],temp1[200],ich[5];
	char lineInfoPath[100]="data\\lineinfo.ini",linePath[100],linePath1[100];
	int lineSum=GetIniKeyInt(lineInfoPath,"config","linesum");
	int code=0,indexl=-1,indexs=-1;
	itoa(lineSum,title,10);
	PutIniKeyInt(lineInfoPath,"config","linesum", lineSum+1);
	PutIniKeyInt(lineInfoPath,title,"number", line->number);
	PutIniKeyInt(lineInfoPath,title,"lineno", line->lineno);
	PutIniKeyString(lineInfoPath,title,"linecn", line->linecn);
	PutIniKeyString(lineInfoPath,title,"lineen", line->lineen);
	PutIniKeyInt(lineInfoPath,title,"averageintervaltime", line->averageintervaltime);
	PutIniKeyInt(lineInfoPath,title,"lastmodifytime", line->lastmodifytime);
	PutIniKeyInt(lineInfoPath,title,"numcolor", 0);//����վ�㸽0
	BuildPath(line->number,linePath);
	
	if(access(linePath, 0)==-1){
		FILE *fp=fopen(linePath,"w");
		fclose(fp);
	}
	PutIniKeyInt(linePath,"config","line", line->lineno);
	PutIniKeyInt(linePath,"config","stationsum", line->stationsum);
	PutIniKeyString(linePath,"config","startone", line->start);
	PutIniKeyString(linePath,"config","starttow", line->end);
	PutIniKeyString(linePath,"config","endone", line->start);
	PutIniKeyString(linePath,"config","endtow", line->end);
	for(int i=0;i<line->stationsum;i++){
		itoa(i,title,10);
		PutIniKeyInt(linePath,title,"lineno", line->lineno);
		PutIniKeyInt(linePath,title,"stationid", line->station[i].stationid);
		PutIniKeyInt(linePath,title,"stageseq", line->station[i].stageseq);
		PutIniKeyString(linePath,title,"namecn", line->station[i].namecn);
		PutIniKeyString(linePath,title,"nameen", line->station[i].nameen);
		PutIniKeyString(linePath,title,"startone", line->station[i].startonetime);
		PutIniKeyString(linePath,title,"starttow", line->station[i].starttwotime);
		PutIniKeyString(linePath,title,"endone", line->station[i].endonetime);
		PutIniKeyString(linePath,title,"endtow", line->station[i].endtwotime);
		sprintf(temp,"%lf",line->station[i].longitude);
		PutIniKeyString(linePath,title,"longitude", temp);
		sprintf(temp,"%lf",line->station[i].latitude);
		PutIniKeyString(linePath,title,"latitude", temp);
		int j=0;
		temp[0]='\0';
		temp1[0]='\0';
		while(line->station[i].transfer[j]!=0 && j>=0 && j<MAXTRANNUM){
			sprintf(temp1,"|%d",line->station[i].transfer[j]);
			strcat_s(temp,sizeof(temp),temp1);
			j++;
		}
		PutIniKeyString(linePath,title,"transfer", temp);

		for(int i=0;i<line->stationsum;i++){//ʱ�临�Ӷȹ��ߣ����޷������ 
			for(j=0;j<MaxLine-1;j++){
				for(int k=0;k<L[j].stationsum;k++){
					if(L[j].station[k].stationid==line->station[i].stationid){
						int r=0;
						temp[0]='\0';
						temp1[0]='\0';
						indexl=-1;
						indexs=-1;
						while(L[j].station[k].transfer[r]!=0 && r>=0 && r<MAXTRANNUM){
							sprintf(temp1,"|%d",L[j].station[k].transfer[r]);
							strcat_s(temp,sizeof(temp),temp1);//�ڶ����ļ�δд�� 
							r++;
						}
						indexl=L[j].number;
						indexs=k;
						//break;
					}
				}
				if(indexl!=-1){
					itoa(indexs,title1,10);
					BuildPath(indexl,linePath1);
					PutIniKeyString(linePath1,title1,"transfer", temp);
				}	
			}		
		}
		
		
		j=0;
		char exitsta1[500],exitsta[500],ich[10];
		exitsta[0]='\0';
		exitsta1[0]='\0';
		temp[0]='\0';
		temp1[0]='\0';
		while(line->station[i].exitdata[j].exitname[0]!='\0'){
			sprintf(temp1,"|%s",line->station[i].exitdata[j].exitname);
			strcat_s(temp,sizeof(temp),temp1);
			exitsta[0]='\0';
			exitsta1[0]='\0';
			for(int k=0;k<line->station[i].exitdata[j].adnum;k++){
				sprintf(exitsta1,"|%s",line->station[i].exitdata[j].exitad[k]);
				strcat_s(exitsta,sizeof(exitsta),exitsta1);
			}
			itoa(j,ich,10);
			PutIniKeyString(linePath,title,ich, exitsta);
			j++;
		}
		PutIniKeyInt(linePath,title,"exitsum", line->station[i].exitsum);
		code=PutIniKeyString(linePath,title,"exitname", temp);
		
	} 
	return code;
}

/*��·ɾ��*/ 
void LineDeletion(void){
	int LineNum,trueInput=0,nrindex,code=0;
	char lch[5],sch[5];
	char lineInfoPath[100]="data\\lineinfo.ini";
	int lineSum=GetIniKeyInt(lineInfoPath,"config","linesum");
	system("cls");
	AdminLineHead();
	nrindex=AdminPrintLine(1);
	AdminStationTailNoM();
	printf("\t\t\t��������·��ţ���  ��\b\b\b\b");
	color(9);
	scanf("%s",&lch); 
	color(7);
	if(strcmp(lch,"q")==0){
		menu(2);code=0;
	}else{
		LineNum=atoi(lch);
		if(nrindex<LineNum){
			LineNum++;
		}
		code=1;
		color(7);
	}
	while(LineNum<=0 && LineNum-1>=lineSum && nrindex!=LineNum){
		color(4);
		printf("\t\t\t�������\n");
		color(7);
		printf("\t\t\t������������·��ţ���  ��\b\b\b\b");
		color(9);
		scanf("%s",&lch); 
		color(7);
		if(strcmp(sch,"q")==0){
			menu(2);code=0;break;
		}else{
			LineNum=atoi(lch);
			if(nrindex<LineNum){
				LineNum++;
			}
			code=1;
			color(7);
		} 
		
	}
	if(code==1){
		char ch;
		while(!trueInput){
			color(4);
			printf("\t\t\t��ȷ��Ҫɾ������·���˲���������[Y/N]��  ��\b\b\b\b"); 
			color(9);
			char ch=getch();
			printf("%c",ch);
			color(7);
			switch(ch){
				case 'Y':
				case 'y':
					printf("\n\t\t\tɾ���У����Ժ�....."); 
					DeleteLineMem(LineNum-1);
					trueInput=1;break;
				case 'N':
				case 'n':menu(2);trueInput=1;break;
				default:
					trueInput=0;
					color(4);
					printf("\n\t\t\t���������\n");
					color(7);
			}	
		}

	}
	
	
	
}

/*��·����ɾ��*/ 
void DeleteLineMem(int lnum){
	char lineInfoPath[100]="data\\lineinfo.ini";
	int lineSum=GetIniKeyInt(lineInfoPath,"config","linesum");
	int lindex=-1;
	for(int i;i<lineSum;i++){
		if(L[lnum].number==9999){
			lindex=i;
			break;
		}
	}
	/*�޸�G������*/
	for(int i=0;i<L[lnum].stationsum;i++){
		if(i+1<L[lnum].stationsum){
			G.arcs[L[lnum].station[i].stationid][L[lnum].station[i+1].stationid].weight=0;
			G.arcs[L[lnum].station[i+1].stationid][L[lnum].station[i].stationid].weight=0;
			G.arcnum=G.arcnum-2;
			
		}
		if(i-1>=0){
			G.arcs[L[lnum].station[i].stationid][L[lnum].station[i-1].stationid].weight=0;
			G.arcs[L[lnum].station[i-1].stationid][L[lnum].station[i].stationid].weight=0;
			G.arcnum=G.arcnum-2;
		}
		G.data[L[lnum].station[i].stationid].lineno=9999;
		G.data[L[lnum].station[i].stationid].stageseq=L[lindex].stationsum+i;
		//�޸Ļ������� 
		for(int j=0;j<MAXTRANNUM;j++){
			if(G.data[L[lnum].station[i].stationid].transfer[j]==L[lnum].number){
				if(j+1<MAXTRANNUM){
					G.data[L[lnum].station[i].stationid].transfer[j]=G.data[L[lnum].station[i].stationid].transfer[j+1];
					G.data[L[lnum].station[i].stationid].transfer[j+1]=0;
				}else{
					G.data[L[lnum].station[i].stationid].transfer[j]=0;
				}	
			}
		}
	
	}
	int fin=1;
	char ch;
	fin=DeleteLineWrite(lnum);
	/*�޸�L������*/
	for(int i=lnum;i<lineSum;i++){
		if(i+1<MAXLINESUM){
			L[i]=L[i+1];
		}	
	}
	if(fin==-1){
		color(2);
		printf("\t\t\tɾ���ɹ�");
		color(7);
		printf("\n\t\t\t���������ַ��������˵�����  ��\b\b\b\b");
		ch=getch();
		menu(2);

	}else{
		color(4);
		printf("\t\t\tɾ��ʧ��");
		color(7);
		printf("\n\t\t\t���������ַ��������˵�����  ��\b\b\b\b");
		ch=getch();
		menu(2);
	}
	
	
}

/*��·ɾ���ļ�д��*/ 
int DeleteLineWrite(int lnum){
	/*�޸�Դ�ļ�����*/
	char linePath[100],trlinePath[100],title[5],ntitle[5],title1[5],temp[200],temp1[200];
	char lineInfoPath[100]="data\\lineinfo.ini";
	int lineSum=GetIniKeyInt(lineInfoPath,"config","linesum");
	int lindex=-1,indexl=-1,indexs=-1;
	for(int i=0;i<lineSum;i++){
		if(L[lnum].number==9999 && L[i].number==9999){
			lindex=i;
			break;
		}
	}
	


	BuildPath(L[lnum].number,linePath);
	for(int i=0;i<L[lnum].stationsum;i++){
		//itoa(i,title,10);
		//itoa(L[lindex].stationsum+1,ntitle,10);
		//ChangeIniTitle(linePath,title,ntitle);
		//�޸Ļ������� 
		for(int j=0;j<lineSum;j++){
			for(int k=0;k<L[j].stationsum;k++){
				if(L[j].station[k].stationid==L[lnum].station[i].stationid){
					int r=0;
					temp[0]='\0';
					temp1[0]='\0';
					indexl=-1;
					indexs=-1;
					while(L[j].station[k].transfer[r]!=0 && r>=0 && r<MAXTRANNUM){
						sprintf(temp1,"|%d",G.data[L[j].station[k].stationid].transfer[r]);
						strcat_s(temp,sizeof(temp),temp1);
						r++;
					}
					indexl=L[j].number;
					indexs=k;
					break;
				}
			}
			if(indexl!=-1){
				itoa(indexs,title1,10);
				BuildPath(indexl,trlinePath);
				PutIniKeyString(trlinePath,title1,"transfer", temp);
			}	
		}
				
	}
	int flag=0;
	
	for(int i;i<lineSum;i++){
		if(L[lnum].number==L[i].number || flag==1){
			itoa(i,title,10);
			if(flag==0){
				DeleteIniSection(lineInfoPath,title);
			}
			itoa(i-1,ntitle,10);
			ChangeIniTitle(lineInfoPath,title,ntitle);
			flag=1;
		}
		
	}
	PutIniKeyInt(lineInfoPath,"config","linesum", lineSum-1);
	remove(linePath);
	return access(linePath, 0);
	
}

/*��·վ�����*/ 
void LineStaAddition(void){
	int trueInput=0,code=1,lindex,LineNum,stationNum,lnum,snum;
	char sch[5],lch[5];
	char lineInfoPath[100]="data\\lineinfo.ini";
	int lineSum=GetIniKeyInt(lineInfoPath,"config","linesum");
	while(1){
		if(code==1){
			system("cls");
			AdminLineHead();
			AdminPrintLine(0);
			AdminStationTail();
			printf("\t\t\t��������·��ţ���  ��\b\b\b\b");
			color(9);
			scanf("%s",&lch); 
			color(7);
			if(strcmp(lch,"q")==0){
				menu(2);break;
			}else{
				LineNum=atoi(lch);
				color(7);
				code=2;
			}
			while(LineNum<=0 && LineNum-1>=lineSum){
				color(4);
				printf("\t\t\t�������\n");
				color(7);
				printf("\t\t\t������������·��ţ���  ��\b\b\b\b");
				color(9);
				scanf("%s",&lch); 
				color(7);
				if(strcmp(lch,"q")==0){
					menu(2);break;
				}else{
					LineNum=atoi(lch);
					color(7);
					code=2;
				} 
				
			}
			
		}
		
		
		if(code==2){
			system("cls");
			AdminStationHead(); 
			AdminPrintStation(LineNum-1);
			AdminStationTail();
			printf("\t\t\t������������վ����ţ���  ��\b\b\b\b");
			color(9);
			scanf("%s",&sch); 
			if(strcmp(sch,"q")==0){
				code=1;
				continue;
			}else if(strcmp(sch,"m")==0){
				menu(2);break;
			}else{
				stationNum=atoi(sch);
			}
			color(7);
			while(stationNum<=0 && stationNum>=L[LineNum-1].stationsum){
				color(4);
				printf("\t\t\t�������\n");
				color(7);
				printf("\t\t\t����������������վ����ţ���  ��\b\b\b\b");
				color(9);
				scanf("%s",sch); 
				if(strcmp(sch,"q")==0){
					code=1;
					continue;
				}else if(strcmp(sch,"m")==0){
					menu(2);break;
				}else{
					stationNum=atoi(sch);
				}
			}
		}
		code=3;
		break;	
	}
	static stationinfo station;
	station=L[LineNum-1].station[stationNum-1];
	char ch;
	if(code==3){
		lindex=SelectAddres(&station,1,&lnum,&snum);
		if(AdditionWrite(station.stationid,lindex)!=-1){
			color(2);
			printf("\t\t\t����ɹ�");
			color(7);
//			printf("\n\t\t\t\t����ӵ���Ϣ���£�");
//			PrintAddStaInfo(lnum,snum);
			printf("\n\t\t\t���������ַ��������˵�����  ��\b\b\b\b");
			ch=getch();
			menu(2);
	
		}else{
			color(4);
			printf("\t\t\t\t���ʧ��");
			color(7);
			printf("\n\t\t\t\t���������ַ��������˵�����  ��\b\b\b\b");
			ch=getch();
			menu(2);
		}	
			
	}
	
} 
