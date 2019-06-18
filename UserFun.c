#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "main.h"
#include "utility.h"
#include "UserFun.h"
extern Graph G;
extern lineinfo L[MAXLINESUM];
extern int  MaxLine;
extern int MaxStation;
ArrayNode shortestN[MaxVertexNum];
/*���&��������*/
char* TransferConversion(int num){
	int lineSum;
	char lineInfoPath[100]="data\\lineinfo.ini";
	lineSum=GetIniKeyInt(lineInfoPath,"config","linesum");
	for(int i=0;i<lineSum && i<MAXLINESUM;i++){
		if(L[i].number==num){
			return L[i].linecn;
		}
	}
	return "";
}


void PrintLine(){
	int lineSum,tempNo=-1;
	char temp[500]; 
	int i;
	char lineInfoPath[100]="data\\lineinfo.ini";
	lineSum=GetIniKeyInt(lineInfoPath,"config","linesum");
	for(i=0;i<lineSum;i++){
		sprintf(temp,"%d.%s",i+1,L[i].linecn);
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


void PrintStation(int lNum){
	int lineSum;
	char temp[500]; 
	int i;
	char lineInfoPath[100]="data\\lineinfo.ini";
	lineSum=GetIniKeyInt(lineInfoPath,"config","linesum");

	for(i=0;i<L[lNum].stationsum;i++){
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

void UserStationHead(void){
	system("cls");
	printf("\t\t\t| �������������������������������������������������������������������������� |\n");
	printf("\t\t\t|                               ");
	color(2);
	printf("�� �û�ģʽ ��");
	color(7);
	printf("                               |\n");
	printf("\t\t\t|                              ��վ����Ϣ��ѯ��                              |\n");
	printf("\t\t\t|                                                                            |\n");
	printf("\t\t\t|\t"); 
} 


void UserStationTail(void){
	printf("\t\t\t|                                                                            |\n");
	printf("\t\t\t|        m.���˵�                                              q.����        |\n");
	printf("\t\t\t|  ��������������������������������������������������������������������������|\n");
}

void UserStationTailNoQ(void){
	printf("\t\t\t|                                                                            |\n");
	printf("\t\t\t|                                                              m.���˵�      |\n");
	printf("\t\t\t|  ��������������������������������������������������������������������������|\n");
}

	
	
void PrintStationInfo(int lNum,int sNum){
	int lineSum;
	char temp[500],temp1[500],temp2[500],ch1; 
	int i,flag;
	char lineInfoPath[100]="data\\lineinfo.ini";
	lineSum=GetIniKeyInt(lineInfoPath,"config","linesum");
	system("cls");
	printf("\t\t\t| ������������������������������������������������������������������|\n");
	printf("\t\t\t|                           ");
	color(2);
	printf("�� �û�ģʽ ��");
	color(7);
	printf("                          |\n");
	printf("\t\t\t|                          ��վ����Ϣ��ѯ��                         |\n");
	printf("\t\t\t|                                                                   |\n");
	sprintf(temp,"վ����%s(%s)",L[lNum].station[sNum].namecn,L[lNum].station[sNum].nameen);
	printf("\t\t\t|\t\t\t%-44s|\n",temp);
	sprintf(temp,"�ߺţ�%s(%s))",L[lNum].linecn,L[lNum].lineen);
	printf("\t\t\t|\t\t\t%-44s|\n",temp);
	sprintf(temp,"�������ʱ�䣺%d����",L[lNum].averageintervaltime/60);
	printf("\t\t\t|\t\t\t%-44s|\n",temp);
	i=0;
	flag=0;
	while(L[lNum].station[sNum].transfer[i]!=0 && L[lNum].station[sNum].transfer[i]<=MaxLine){
		if(i==0){
			sprintf(temp,"�ɻ��ˣ�%s",TransferConversion(L[lNum].station[sNum].transfer[i]));
			flag=1;
		}else{
			sprintf(temp1,"%s��%s",temp,TransferConversion(L[lNum].station[sNum].transfer[i]));
			flag=2;
		}
		
		i++;
	}
	if(flag==1){
		printf("\t\t\t|\t\t\t%-44s|\n",temp);
	}else if(flag==2){
		printf("\t\t\t|\t\t\t%-44s|\n",temp1);
	}
	printf("\t\t\t|                                                                   |\n");
	sprintf(temp1,"%s����:",L[lNum].end);
	sprintf(temp2,"%s����:",L[lNum].start);
	sprintf(temp,"%-26s\t%-26s",temp1,temp2);
	printf("\t\t\t|\t%-55s|\n",temp);
	sprintf(temp1,"�װ೵ʱ�䣺%s",L[lNum].station[sNum].startonetime);
	sprintf(temp2,"�װ೵ʱ�䣺%s",L[lNum].station[sNum].starttwotime);
	sprintf(temp,"%-26s\t%-26s",temp1,temp2);
	printf("\t\t\t|\t%-55s|\n",temp);
	sprintf(temp1,"ĩ�೵ʱ�䣺%s",L[lNum].station[sNum].endonetime);
	sprintf(temp2,"ĩ�೵ʱ�䣺%s",L[lNum].station[sNum].endtwotime);
	sprintf(temp,"%-26s\t%-26s",temp1,temp2);
	printf("\t\t\t|\t%-55s|\n",temp);
	printf("\t\t\t|                                                                   |\n");
	/*���������Ϣ*/ 
	if(L[lNum].station[sNum].exitsum!=0){
		printf("\t\t\t|                           ");
		color(2);
		printf("�� ������Ϣ ��");
		color(7);
		printf("                          |\n");
	}
	for(i=0;i<L[lNum].station[sNum].exitsum;i++){
		if(L[lNum].station[sNum].exitdata[i].exitname!=""){
			sprintf(temp,"��%s��",L[lNum].station[sNum].exitdata[i].exitname);
			printf("\t\t\t|\t%-60s|\n",temp);
			flag=0;
			temp[0]='\0';
			for(int j=0;j<=L[lNum].station[sNum].exitdata[i].adnum;j++){
				if(j==0){
					printf("\t\t\t|\t");
				}
				strcpy(temp2,L[lNum].station[sNum].exitdata[i].exitad[j]);
				if(strlen(temp)+strlen(temp2)>=55){//��һ��
					if(strlen(temp2)>55){
						if(temp!=""){
							printf("%-60s|\n\t\t\t|\t",temp);
						}
						strncpy(temp,temp2,55);
						printf("%-60s|\n\t\t\t|\t",temp);
						strcpy(temp,temp2+55);
						if(j==L[lNum].station[sNum].exitdata[i].adnum-1){
							printf("%-60s|\n",temp);
						}else{
								strcat(temp,"��");
						}
					}else{
						printf("%-60s|\n\t\t\t|\t",temp);
						strcpy(temp,temp2);
						if(j==L[lNum].station[sNum].exitdata[i].adnum-1){
							printf("%-60s|\n",temp);
						}else{
								strcat(temp,"��");
						}
					}
				}else{
					strcat(temp,temp2);
					if(j==L[lNum].station[sNum].exitdata[i].adnum-1){
						printf("%-60s|\n",temp);
					}else{
						strcat(temp,"��");
					}
					
				}				
			}
		}
		
		
	}
	printf("\t\t\t|                                                                   |\n");
	printf("\t\t\t|      m.���˵�                                         q.����      |\n");
	printf("\t\t\t| ������������������������������������������������������������������|\n");
	printf("\t\t\t��������ĸ����  ��\b\b\b\b");

	
}

void PrintTicketPice(int from,int to){
	char temp[100];
	system("cls");
	printf("\t\t\t\t| ����������������������������������������������|\n");
	printf("\t\t\t\t|                ");
	color(2);
	printf("�� �û�ģʽ ��");
	color(7);
	printf("                 |\n");
	printf("\t\t\t\t|                ��վ����Ϣ��ѯ��               |\n");
	printf("\t\t\t\t|                                               |\n");
	printf("\t\t\t\t|\t\t"); 
	sprintf(temp,"ʼ��վ��%s",G.data[from].namecn);
	printf("%-23s",temp);
	printf("\t\t|\n");
	printf("\t\t\t\t|\t\t"); 
	sprintf(temp,"�յ�վ��%s",G.data[to].namecn);
	printf("%-23s",temp);
	printf("\t\t|\n");
	printf("\t\t\t\t|\t\t"); 
	if(CalculateFares(shortestN[to].distance)>=30){
		printf("%-23s","��·���޷�����Ʊ��");
	} else{
		
		sprintf(temp,"Ʊ�ۣ�%dԪ",CalculateFares(shortestN[to].distance));
		printf("%-23s",temp);
		
	}
	printf("\t\t|\n");
	printf("\t\t\t\t|                                               |\n");
	printf("\t\t\t\t|   m.���˵�                           q.����   |\n");
	printf("\t\t\t\t| ����������������������������������������������|\n");
}

int CalculateFares(double distance){
	int dis,price=2;
	dis=(int)(distance+0.5);//��������
	dis=dis-4;
	if(dis-4>=0){
		dis=dis-4;
		price++;
	}
	if(dis-4>=0){
		dis=dis-4;
		price++;
	}
	if(dis-6>=0){
		dis=dis-6;
		price++;
	}
	if(dis-6>=0){
		dis=dis-6;
		price++;
	}
	while(dis-8>=0){
		dis=dis-8;
		price++;
	}
	if(dis>=0){
		price++;
	}
	return price;
}


void Dijkstra(int from,int to){
	int i,j,index=-1; 
    int n=1;//��¼�Ѿ������������֮�����̾���ĸ��� 
    char re[400];
    int flag[MaxVertexNum]={0};//��ǣ�Ϊ1��ʾ������������̾�������� 
    /*��ʼ��*/
	for(i=0;i<=MaxStation;i++){
		if(i==from){
			shortestN[i].distance=0;
			shortestN[i].path[0]=from;
			flag[from]=1;
		}else if(G.arcs[from][i].weight>0){
			shortestN[i].distance=G.arcs[from][i].weight;
			shortestN[i].path[1]=i;
		}else{
			shortestN[i].distance=INFINITE;
		}
	}
	//����ÿ���ҳ�һ����������·��
	while(n<=MaxStation){
		index=-1;
		for(i=0;i<=MaxStation;i++){
			if(i==from){
				continue;
			}
			if(flag[i]==0  && shortestN[i].distance!=INFINITE){
				index=i;
			}
			if(flag[i]==0  && shortestN[i].distance<shortestN[index].distance){
				index=i;
			}
		}
		flag[index]=1;
		//���±� 
		for(i=0;i<=MaxStation;i++){
			if(i==from){
				continue;
			}
			if(G.arcs[index][i].weight>0 && G.arcs[index][i].weight+shortestN[index].distance<shortestN[i].distance){
				shortestN[i].distance=G.arcs[index][i].weight+shortestN[index].distance;
				j=0;
				while(1){
					shortestN[i].path[j]=shortestN[index].path[j];
					if(shortestN[index].path[j]==index){
						break;
					}
					j++;
				}
				shortestN[i].path[0]=from;
				shortestN[i].path[j+1]=i;
			}
		}
		n++;
	}
//	if(shortestN[to].distance==INFINITE){
//		printf("%s��%sû��·��\n",G.data[from].namecn,G.data[to].namecn);
//	}
//	printf("%s��%s�����·�������ǣ�%f\n",G.data[from].namecn,G.data[to].namecn,shortestN[to].distance); 
//    printf("�����Ķ��㣺  "); 
//    i=0; 
//    while(1){ 
//        strcat_s(re,sizeof(re),G.data[shortestN[to].path[i]].namecn);
//        if(shortestN[to].path[i]==to){
//        	break; 
//		}else{
//			strcat_s(re,sizeof(re),"---��"); 
//		}
//        i++; 
//    } 
//    printf("\n"); 
}


void RouteQuery(void){
	int lineSum,lNum=0,sNum=0;
	int from=0,to=0,flag=1,i=0;
	char lineInfoPath[100]="data\\lineinfo.ini";
	char name[10]="ʼ��վ",re[500];
	lineSum=GetIniKeyInt(lineInfoPath,"config","linesum");
	while(1){
		if(flag==1 || flag==3){
			char ch[5];
			UserStationHead();
			PrintLine();
			UserStationTailNoQ();
			printf("\t\t\t������ѡ��");
			color(2);
			printf("%s",name);
			color(7);
			printf("����·��š�  ��\b\b\b\b");
			ch[0]='\0';
			scanf("%s",&ch);
			if(ch[0]=='m'){
				menu(1);break;
			}else if(atoi(ch)<=0 || atoi(ch)>lineSum){
				color(4);
				printf("\n\t\t\t�������1�������...");
				color(7);
				Sleep(1000); 
			}else{
				lNum=atoi(ch)-1;
				flag++;
			}
			
			
		}else if(flag==2 || flag==4){
			char ch[5];
			UserStationHead();
			PrintStation(lNum);
			UserStationTail();
			printf("\t\t\t������ѡ��");
			color(2);
			printf("%s",name);
			color(7);
			printf("��վ����š�  ��\b\b\b\b");
			ch[0]='\0';
			scanf("%s",&ch);
			if(ch[0]=='m'){
				menu(1);break;
			}else if(ch[0]=='q'){
				flag--;
				lNum=0;
			}else if(atoi(ch)>0 && atoi(ch)<=L[lNum].stationsum){//�������� 
				sNum=atoi(ch)-1; 
				if(flag==2){
					from=L[lNum].station[sNum].stationid;
					strcpy(name,"�յ�վ");
				}else if(flag==4){
					to=L[lNum].station[sNum].stationid;
				}
				flag++;
			}else{
				color(4);
				printf("\n\t\t\t�������1�������...");
				color(7);
				Sleep(1000);
//				flag=2;
			}
				
			
		}else if(flag==5){
			char ch;
			if(flag==5 && from>0 && from<=MaxStation && to>0 &&to<=MaxStation){
				Dijkstra(from,to);
				
				if(shortestN[to].distance==INFINITE){
					printf("%s��%sû��·��\n",G.data[from].namecn,G.data[to].namecn);
				}else{
				
					printf("%s��%s�����·�������ǣ�%f\nƱ��Ϊ��%d",G.data[from].namecn,G.data[to].namecn,shortestN[to].distance,CalculateFares(shortestN[to].distance)); 
				    printf("�����Ķ��㣺  "); 
				    shortestN[to].path[0]=from;
					while(1){ 
				        strcat_s(re,sizeof(re),G.data[shortestN[to].path[i]].namecn);
				        if(shortestN[to].path[i]==to){
				        	break; 
						}else{
							strcat_s(re,sizeof(re),"---��"); 
						}
				        i++; 
				    }
					printf("%s",re);
			    }
				printf("\n"); 
				printf("\t\t\t��q�����ء�  ��\b\b\b\b");
				ch=getch();
				if(ch=='m'){
					menu(1);break;
				}else if(ch=='q'){
					break;
				}
				
				
				
				
			}
			ch=getch();
			printf("%c",ch);
			switch(ch){
				case 'q':sNum=0;flag--;break;
				case 'm':menu(1);break;
				default:
					color(4);
					printf("\n\t\t\t�������1�������\b\b\b");
					color(7);
					Sleep(1000);
//					flag=3;
			}
	
		}
	
		
	}
	RouteQuery(); 
}


void QuerySiteInformation(int flag){
	int lineSum,lNum=0,sNum=0;
	char lineInfoPath[100]="data\\lineinfo.ini";
	lineSum=GetIniKeyInt(lineInfoPath,"config","linesum");
	while(1){
		if(flag==1){
			char ch[5];
			UserStationHead();
			PrintLine();
			UserStationTailNoQ();
			printf("\t\t\t������Ҫ��ѯ����·��š�  ��\b\b\b\b");
			ch[0]='\0';
			scanf("%s",&ch);
			if(ch[0]=='m'){
				menu(1);break;
			}else if(atoi(ch)<=0 || atoi(ch)>lineSum){
				color(4);
				printf("\n\t\t\t�������1�������...");
				color(7);
				Sleep(1000); 
				PrintLine();
			}else{
				lNum=atoi(ch)-1;
				flag=2;
			}
			
			
		}else if(flag==2){
			char ch[5];
			UserStationHead();
			PrintStation(lNum);
			UserStationTail();
			printf("\t\t\t������Ҫ��ѯ��վ����š�  ��\b\b\b\b");
			ch[0]='\0';
			scanf("%s",&ch);
			if(ch[0]=='m'){
				menu(1);break;
			}else if(ch[0]=='q'){
				flag=1;
				lNum=0;
			}else if(atoi(ch)>0 && atoi(ch)<=L[lNum].stationsum){//�������� 
				flag=3;
				sNum=atoi(ch)-1; 
			}else{
				color(4);
				printf("\n\t\t\t�������1�������...");
				color(7);
				Sleep(1000);
				flag=2;
			}
				
			
		}else if(flag==3){
			char ch;
			PrintStationInfo(lNum,sNum);
			ch=getch();
			printf("%c",ch);
			switch(ch){
				case 'q':sNum=0;flag=2;break;
				case 'm':menu(1);break;
				default:
					color(4);
					printf("\n\t\t\t�������1�������\b\b\b");
					color(7);
					Sleep(1000);
					flag=3;
			}
	
		}
	
		
	}
		
	
}


void ViewMap(void){
	
}

void QueryTicketPrice(void){
	int lineSum,lNum=0,sNum=0;
	int from=0,to=0,flag=1,i=0;
	char lineInfoPath[100]="data\\lineinfo.ini";
	char name[10]="ʼ��վ",re[500];
	lineSum=GetIniKeyInt(lineInfoPath,"config","linesum");
	while(1){
		if(flag==1 || flag==3){
			char ch[5];
			UserStationHead();
			PrintLine();
			UserStationTailNoQ();
			printf("\t\t\t������ѡ��");
			color(2);
			printf("%s",name);
			color(7);
			printf("����·��š�  ��\b\b\b\b");
			ch[0]='\0';
			scanf("%s",&ch);
			if(ch[0]=='m'){
				menu(1);break;
			}else if(atoi(ch)<=0 || atoi(ch)>lineSum){
				color(4);
				printf("\n\t\t\t�������1�������...");
				color(7);
				Sleep(1000); 
			}else{
				lNum=atoi(ch)-1;
				flag++;
			}
			
			
		}else if(flag==2 || flag==4){
			char ch[5];
			UserStationHead();
			PrintStation(lNum);
			UserStationTail();
			printf("\t\t\t������ѡ��");
			color(2);
			printf("%s",name);
			color(7);
			printf("��վ����š�  ��\b\b\b\b");
			ch[0]='\0';
			scanf("%s",&ch);
			if(ch[0]=='m'){
				menu(1);break;
			}else if(ch[0]=='q'){
				flag--;
				lNum=0;
			}else if(atoi(ch)>0 && atoi(ch)<=L[lNum].stationsum){//�������� 
				sNum=atoi(ch)-1; 
				if(flag==2){
					from=L[lNum].station[sNum].stationid;
					strcpy(name,"�յ�վ");
				}else if(flag==4){
					to=L[lNum].station[sNum].stationid;
				}
				flag++;
			}else{
				color(4);
				printf("\n\t\t\t�������1�������...");
				color(7);
				Sleep(1000);
//				flag=2;
			}
				
			
		}else if(flag==5){
			char ch;
			if(flag==5 && from>0 && from<=MaxStation && to>0 &&to<=MaxStation){
				Dijkstra(from,to);
				PrintTicketPice(from,to);
				 
			    printf("\n"); 
				printf("\t\t\t��q�����ء�  ��\b\b\b\b");
				ch=getch();
				if(ch=='m'){
					menu(1);break;
				}else if(ch=='q'){
					break;
				}
				
				
				
				
			}
			ch=getch();
			printf("%c",ch);
			switch(ch){
				case 'q':sNum=0;flag--;break;
				case 'm':menu(1);break;
				default:
					color(4);
					printf("\n\t\t\t�������1�������\b\b\b");
					color(7);
					Sleep(1000);
//					flag=3;
			}
	
		}
	
		
	}
	QueryTicketPrice(); 
}




