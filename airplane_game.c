#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<stdbool.h>
#include<unistd.h>
#include<pthread.h>
#include"setplay.h"
//#include "mmsystem.h" 

int plantType=0;                                  //���������A 
int i,j,score=0,canchange=0;                       //�y�Ц�m
int keyboard;                                      //keyboard���O
HANDLE hIn, hOut;                                  //I/O ���
bool out;                                          
time_t initaltime,bullettime,Gametime,type1_time;   
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;   //������
int number_enemy=3,enemy_speed=4,bullet_number=20; //��l���A

struct head
{
	int (*compare)(int,int);
	struct linklist* rear;
	struct linklist* firstptr;
	int count;
};
struct linklist
{
	struct linklist* nextptr;
	int bulletx;
	int bullety;
	int times;
	bool flag;
	bool reward;
    time_t now;
};
struct data
{
	char *a;
	int score;
};

typedef struct data* DATA;
typedef struct head* HEAD;
typedef struct linklist* LIST;

void* playMusicThread(void* arg2);                   //���� 
void enemyAction(HEAD ,HEAD ,HEAD );      //�ĤH�ʧ@��P�_ 
void drawboss(int x,int y);               //�eboss�� 
void cleanboss(int x,int y);              //�M��boss 
void gotoxy (int x, int y);               //���ʴ�� 
HEAD createhead(int(*compare)(int n1,int n2)); //�ͦ�meta data 
bool insert(HEAD list,LIST pre,int x,int y);    // �[�ilist
bool search(HEAD head,LIST *pre,LIST* loc,int x); //��[�J�I 
bool enemyedge(LIST first,HEAD list);          //�P�_�ĤH��� 
int addlist(HEAD head,int x,int y);           // �P�_�[�J���A
bool deletelist(HEAD list,int x);             //�qlist�R�� 
bool _delete(HEAD head,LIST pre,LIST loc);    //�P�_�R�����A 
bool edge(int i,int j);                 //��� 
bool bulletedge(LIST ,HEAD);           //�P�_�l�u�O�_��� 
void drawframe();                      //�e��� 
HEAD enemy_create(int number_of_enemy,HEAD enemyhead);//�ͦ��ĤH 
void clean(int ,int );               //�M�Ť@�� 
void initial();                      //��l 
void* shotThread(void* listt);             //�g�X�l�u���h�����
void* moveThread(void* arg1);              //���� 
void plant(int );                    //���� 
void cleanplant(int );               //�M���� 
HEAD star1(int );                    //�P�P�ͦ� 
void starmove(HEAD);                 //�P�P���� 
void* backgroundThread(void* arg);               //�]�P�P 
int compare(int n1,int n2);          //��� 
HEAD enemyhead;                       
int main()
{
	DATA rank;
    rank=(DATA)malloc(10*sizeof(struct data));
	int k,count22;
	for(k=0;k<10;k++)
	{
		(rank+k)->score=-1;
	}
    while(1)
	{
		number_enemy=3,enemy_speed=4;
    	pthread_t thread1,thread2,thread3,thread4;     //�h������
		bool cont=true;
		HEAD listt;
		listt=createhead(compare);
    	enemyhead=createhead(compare);
    	hOut = GetStdHandle (STD_OUTPUT_HANDLE);
    	hIn  = GetStdHandle (STD_INPUT_HANDLE);
    	HANDLE err = INVALID_HANDLE_VALUE;
    	textcolor(YELLOW);
    	set(&number_enemy,&enemy_speed,&bullet_number);        //�C�������b���n�@�I
		system("cls");
    	initaltime=time(NULL);
    	FILE * fptr;
		fptr=fopen("rank1.txt","r");
		for(k=0;k<10;k++)
		{
			(rank+k)->a=(char*)calloc(50,sizeof(char));
		}
    	k=0;
    	while(	fscanf(fptr,"%s%d",(rank+k)->a,&((rank+k)->score))!=EOF)
    	{

    		k++;
		}
    	fclose(fptr);
    	system("CLS");
    	initial();
    	system("PAUSE");
    	system("CLS");
    	srand(time(NULL));             //�ζü��H�����Ͱ_�l�I
    	drawframe();
    	i=rand()%18+2;
    	j=rand()%20+2;
    	gotoxy(2,62);
    	printf("����:%d",score);
    	Gametime=time(NULL);    //���l���ɶ� 
    	pthread_create(&thread2,NULL,backgroundThread,NULL);
    	pthread_create(&thread1,NULL,shotThread,(void*)listt);
    	pthread_create(&thread3,NULL,moveThread,NULL);
    	pthread_create(&thread4,NULL,playMusicThread,NULL);
    	pthread_join(thread2,NULL);
    	pthread_join(thread1,NULL);
    	pthread_join(thread4,NULL);
    	pthread_join(thread3,NULL);
    	system("CLS");
    	gotoxy(10,25);
    	printf("GAME OVER!!");
    	drawframe();
    	MessageBox(NULL ,"GAME OVER!!", "GG",MB_OK|MB_ICONASTERISK);
    	gotoxy(22,0);
    	system("PAUSE");
    	system("CLS");
    	out=false;
    	keyboard++;

    	if(score>(rank+9)->score)   //�n�W�Ʀ�]�{�� 
    	{
    		fptr=fopen("rank1.txt","w");
    		int g,h,name;
    		(rank+9)->score=score;
    		gotoxy(4,25);
    		printf("PLEASE ENTER YOUR STUDENT ID");
    		gotoxy(5,35);
    		scanf("%s",(rank+9)->a);
    		system("cls");
			for(g=0;g<9;g++)
    		{
    			for(h=0;h<9-g;h++)
    			{
    				if((rank+h+1)->score>(rank+h)->score)
    				{

    					int temp22,nary;
    					char temp33[1];
    	
    				temp22=(rank+h+1)->score;
    				(rank+h+1)->score=(rank+h)->score;
    				(rank+h)->score=temp22;
    				for(nary=0;nary<20;nary++)
    				{
						temp33[0]=*((rank+h+1)->a+nary);
    					*((rank+h+1)->a+nary)=*((rank+h)->a+nary);
    					*((rank+h)->a+nary)=temp33[0];
					}
					}
				}
			}
			for(g=0;g<10;g++)  //��X���ɮ׸� 
			{
					fprintf(fptr,"%s %d\n",(rank+g)->a,(rank+g)->score);
			}

	 		fclose(fptr);
		}
     	plantType=0;
     	score=0;
	}
    return 0;
}
bool edge(int i,int j)
{
	if(i<1||i>19||j<2||j>58)
	{
	return false;

	}
	return true;
}
void drawframe()
{
	int x1,y1;
	textcolor(2);
	for(x1=0;x1<30;x1++)
	{
		gotoxy(0,2*x1);
		printf("��");
	}
	gotoxy(0,60);
	printf("��");
	for(y1=1;y1<20;y1++)
	{
		gotoxy(y1,0);
		printf("��");
	}
	for(x1=0;x1<30;x1++)
	{
		gotoxy(20,2*x1);
		printf("��");
	}
	gotoxy(20,60);
	printf("��");
	for(y1=1;y1<20;y1++)
	{
		gotoxy(y1,60);
		printf("��");
	}
	textcolor(6);
}
HEAD createhead(int(*compare)(int n1,int n2))
{
	HEAD list;
	list=(HEAD)malloc(sizeof(struct head));
	if(!list)
	{
		printf("error!\n");
	}
	else
	{
		list->rear=NULL;
		list->compare=compare;
		list->count=0;
		list->firstptr=NULL;
	}
	return list;
}
bool insert(HEAD head,LIST pre,int x,int y)
{
	LIST newptr;
	newptr=(LIST)malloc(sizeof(struct linklist));
	if(!newptr)
	{
		printf("OUT OF MEMORY");
		return false;
	}
	else
	{
		newptr->bulletx=x;
		newptr->bullety=y;
		newptr->nextptr=NULL;
		newptr->times=0;
		newptr->flag=true;
		newptr->now=time(NULL);
		srand(time(NULL)*i*j*x*y);
        if(rand()%6==1)
        {
        	newptr->reward=true;
		}
		else
			newptr->reward=false;
	}
	if(pre==NULL)
	{
	 	newptr->nextptr=head->firstptr;
	 	head->firstptr=newptr;
	 	if(head->count==0)
	 	{
		 	head->rear=newptr;
		}
	}
	else
	{
	 	newptr->nextptr=pre->nextptr;
	 	pre->nextptr=newptr;

	 	if(newptr->nextptr==NULL)
	 	{
	 		head->rear=newptr;
		}
	}
	head->count++;
	return true;
}
bool search(HEAD head,LIST * pre,LIST * loc,int x)
{
	#define COMPARE\
	(((*head->compare)(x,(*loc)->bulletx)))
	#define COMPARE_LAST\
	((*head->compare)(x,head->rear->bulletx))
	int result;
	*pre=NULL;
	*loc=head->firstptr;
	if(head->count==0)
	{
		return false;
	}
	if(COMPARE_LAST>0)
	{
		*pre=head->rear;
		*loc=NULL;
		return false;
	}
	while((result=COMPARE)>0)
	{
		*pre=*loc;
		*loc=(*loc)->nextptr;
	}
	if(result==0)
	{
		return true;
	}
	else
	{
		return false;
	}

}
int addlist(HEAD head,int x,int y)
{
	bool found;
	bool success;
	LIST pre;
	LIST loc;

	found=search(head,&pre,&loc,x);

	if(found)
	{
		return 1;
	}
	else
	{
		success=insert(head,pre,x,y);
		if(success)
		{
			return 0;
		}
		else
		return -1;
	}
}
bool deletelist(HEAD head,int x)
{
	bool found;
	LIST pre=NULL;
	LIST loc=NULL;
	found=search(head,&pre,&loc,x);
	if(found)
	{
		_delete(head,pre,loc);
		return true;
	}
	else
	{
		return false;
	}

}
bool _delete(HEAD head,LIST pre,LIST loc)
{
	if(head->count==0)
	{
		printf("error!\n");
		return false;
	}
	if(pre==NULL)
	{
		head->firstptr=loc->nextptr;
	}
	else
	{
		pre->nextptr=loc->nextptr;
	}
	if(loc->nextptr==NULL)
	{
		head->rear=pre;
	}
	head->count--;
	free(loc);
	return true;
}
void clean(int x,int y)
{
	gotoxy(x,y);
	printf("  ");
}
HEAD enemy_create(int number_of_enemy,HEAD enemyhead)
{
	int i,coor=1;
    int in;
    int space;
    switch(number_of_enemy)
    {
    	case 3:
    		space=4;
    		coor=3;
    		break;
    			case 6:
    				coor=2;
    		space= 3;
    		break;
    			case 9:
    		space= 2;
    		break;
    			case 13:
    		space=1;
    		break;
	}
	for(i=0;i<19/space;i++)
	{
		srand(time(NULL)+i*i*time(NULL)*i*i+6*time(NULL));
		in=57-rand()%8;
		addlist(enemyhead,in,coor);
		coor=coor+space;
	}
	return enemyhead;
}
void initial()
{
	gotoxy(1,35);
	printf("�����C��");
	gotoxy(2,20);
	printf("�W�h:");
	gotoxy(3,20);
	printf("w,a,s,d�ӱ����,enter�ӵo�g�l�u,");
	gotoxy(5,20);
	printf("�]�����j�@�q�ɶ��|�X�{,�����ľ��i�Τl�u����,");
	gotoxy(7,20);
	printf("�����ᦳ���v���_,�Y���_����t�i�ܨ�,�_�������|�۰ʮ���");
	gotoxy(9,20);
	printf("�Q���IĲ�줤�߶�y�ΥX��");
	gotoxy(11,20);
	printf("�W,�U�W�X���,�|��t�@�Y,�i�O��,�k���|");
	gotoxy(13,20);
	textbackground(RED);
	printf("�бN��J�Ҧ��ը�^��");
	textbackground(BLACK);
	gotoxy(15,20);
	printf("�l�u�g���n������˼u,�J�ӧ�X�]�����z�I������");
	gotoxy(17,20);
	printf("���ư����i�H�n�W�Ʀ�]");
	gotoxy(19,26);
}
void* shotThread(void* listt)                          //�g�X�l�u���h�����
{
	int t,randvar=0;
	int totalbullet=0;
	HEAD enemy_head;
	HEAD list=(HEAD)listt;
	HEAD boss_head;
	boss_head=createhead(compare);
	HEAD bossbullet;
	bossbullet=createhead(compare);
	HEAD reward1;
	reward1=createhead(compare);
	bool shoot=true;
	bool boss_exist=false;
	time_t starttime=time(NULL);
	time_t bosstime;
	bosstime=time(NULL); 
    while(1)                              //�}�lŪ���ϥΪ̪��ʧ@      main loop
    {
    	LIST cleanlist;
    	pthread_mutex_lock(&mutex) ;                            //�L�X����� 
        plant(plantType);                      
        gotoxy(21,0);
        printf("�l�u��:");                       
        if(shoot==true)              //�ϥܤl�u  
        {
			for(t=0;t<bullet_number-totalbullet;t++)
	    	{
	    		gotoxy(21,8+2*t);
	    		textcolor(BLUE);
	    		printf("�o");
	    		textcolor(YELLOW);
			}
			for(t=0;t<totalbullet;t++)
			{
				gotoxy(21,8+2*(bullet_number-1)-2*t);
				printf("  ");
			}
	    }                   //�ϥܤl�u���� 
	    else
	    {
			gotoxy(21,8);
			printf("  ");
	    }
		gotoxy(22,0);
        printf("��q:");          //�ĤH��q 
        gotoxy(5,62);
	    printf("       ");
	    gotoxy(5,62);
	    printf("�l�u%d",list->count); //�l�u�� 
	    gotoxy(6,62);
	    pthread_mutex_unlock(&mutex) ;
	    
	    if(120-(time(NULL)-Gametime)>=0)//�P�_�ٳѤU���ɶ� 
	    {
	    	pthread_mutex_lock(&mutex) ;
	    	gotoxy(1,70);
	    	printf("     ");
	    	gotoxy(1,62);
    	    printf("�ѤU�ɶ�%d",120-(time(NULL)-Gametime));
    	    pthread_mutex_unlock(&mutex) ;
		}
	    else         //�ɶ��S�F�N���X 
	    {
	    	out=true;
	    	gotoxy(10,20);
			printf("PLEASE PRESS ANY WORD!!");
	    	pthread_exit(NULL);
		}
		if(plantType==1 )
		{
			if(time(NULL)-type1_time>10)  //�p�G�ܦ�type_1���ɶ��j��10��N�ܦ^��� 
			{
				plantType=0;
				cleanplant(1);
			}
	   	}
        if(-bullettime+time(NULL)>5) //�������ɥR�l�u 
		{
	        shoot=true;
	    }
        if (keyboard ==13)//�g�l�u
	    {
	        keyboard=keyboard+1;               //��keyboard���A�O��X�l�u�Ҧ�
	        if(shoot)            //�W�[�l�u��l�u�� 
	       	{
	            if(plantType==0)
				{
					addlist(list,-(j+2),i);
				}
				else
				{
					addlist(list,-(j+2),i);
					if(i==1)
					{
						addlist(list,-(j+3),i+1);
				
					}
					else if(i==19)
					{
						addlist(list,-(j+4),i-1);
					}
					else
					{
						addlist(list,-(j+3),i+1);
						addlist(list,-(j+4),i-1);
					}
				}
				totalbullet++;
	            pthread_mutex_lock(&mutex) ;
	            gotoxy(i,j+2);
	            textcolor(3);
	            printf("��");
	            textcolor(YELLOW);
	            pthread_mutex_unlock(&mutex) ;
	        }
	        if(totalbullet==bullet_number) //�p�G�l�u�Ƶ���l�u�W��=>�S�l�u  
			{
			 	shoot=false;
			 	totalbullet=0;
			 	bullettime=time(NULL);
					 	
			}
		}
	       

		if(list->count>0) //�p�G���l�u  �l�u������  �P�I���P�_  
		{
			LIST temp1;
			temp1=list->firstptr;
			while(temp1)                    //�l�u������  �P�I���P�_ 
			{
				pthread_mutex_lock(&mutex) ;
				gotoxy(temp1->bullety,-temp1->bulletx);
				printf("  ");
				temp1->bulletx--;
				if(edge(temp1->bullety,-(temp1->bulletx)))
				{
					if(temp1->flag)
					{
						gotoxy(temp1->bullety,-temp1->bulletx);
				        textcolor(3);
						printf("��");
						textcolor(YELLOW);
					}
				}
				else
				{
					deletelist(list,temp1->bulletx);
					gotoxy(temp1->bullety,58);
					printf(" ");
				}
				    pthread_mutex_unlock(&mutex) ;
					temp1=temp1->nextptr;   //�~��traverse�U�@�� 

			}
		}
		if(time(NULL)-starttime>=15)   //�C�j15��ϥͤ@�x�]���� 
		{
		    boss_exist=true;
		    if(boss_head->count==0)     //�i���W�S���p�ľ��~�ϥ� 
		    addlist(boss_head,57,10);
		}
		
		if((boss_head->count>0&&enemyhead->count==0)||bossbullet->count>0)  //�]���������ʻP�P�_ 
		{ 
		    int judge_xy;
		    LIST bullet1;
		    srand(time(NULL)*time(NULL)+randvar*time(NULL)+i+j);
		    judge_xy=rand()%10;
		    
		    
		    if(boss_head->count>0)
		    {
		    	pthread_mutex_lock(&mutex) ;
		    	gotoxy(22,0);
        	   	printf("��q:");
           		for(t=0;t<boss_head->firstptr->times;t++)
				{
					gotoxy(22,5+2*2-2*t);
					printf("  ");
				}
           		for(t=0;t<3-boss_head->firstptr->times;t++)
	   		 	{
	    			gotoxy(22,5+2*t);
	    			textcolor(RED);
	    			printf("�o");
	    			textcolor(YELLOW);
				}
				pthread_mutex_unlock(&mutex) ;
		    	cleanboss(boss_head->firstptr->bulletx,boss_head->firstptr->bullety);
		    	if(boss_head->count>0)   //�۰ʲ��� ,���v���o���n�i�A�� 
		    	{
		    	
		    		if(judge_xy==0 ||judge_xy==7 ||judge_xy==5)
		    		{
                      	srand(time(NULL)*time(NULL)+20*time(NULL)+i+j*2) ;
                    	randvar=rand()%30;
		        		if(boss_head->firstptr->bullety==17||boss_head->firstptr->bullety==4)
		        		{

		     			   if(boss_head->firstptr->bullety==17)
		        			{
		            			boss_head->firstptr->bullety--;
		        			    drawboss(boss_head->firstptr->bulletx,boss_head->firstptr->bullety);
		        			}
		       				if(boss_head->firstptr->bullety==4)
		        			{
		            			boss_head->firstptr->bullety++;
		            			drawboss(boss_head->firstptr->bulletx,boss_head->firstptr->bullety);
		        			}
		    			}
		        		else
		        		{
		          		  	int judge_y;
		           			srand(time(NULL)*time(NULL)*time(NULL)+6*time(NULL)+9+i+j*4);
		           			judge_y=rand()%2;
		        			if(judge_y==0)
		        			{
		         		   		boss_head->firstptr->bullety++;
		        	    		drawboss(boss_head->firstptr->bulletx,boss_head->firstptr->bullety);
		       		 		}
		       		 		else
		       		 		{
		     	        		boss_head->firstptr->bullety--;
		       		      		drawboss(boss_head->firstptr->bulletx,boss_head->firstptr->bullety);
		        			}
		        		}

		    		}
		    		else if(judge_xy==2)
		        	{
		    			srand(time(NULL)*time(NULL)*time(NULL)+4*i+j) ;
                	    randvar=rand()%50;
		       			if(boss_head->firstptr->bulletx>=30)
		        		{
		            		boss_head->firstptr->bulletx--;
		            		drawboss(boss_head->firstptr->bulletx,boss_head->firstptr->bullety);
		        		}
		        		else
		        		{
		            		drawboss(boss_head->firstptr->bulletx,boss_head->firstptr->bullety);
		        		}
                	}
                	else
                	{
            			drawboss(boss_head->firstptr->bulletx,boss_head->firstptr->bullety);
			    	}	
		   		}
		    	if(time(NULL)-bosstime)//�i�ծg�W,�]���o�g�l�u 
            	{
         
        		 	addlist(bossbullet,boss_head->firstptr->bulletx-1,boss_head->firstptr->bullety+1);
         			addlist(bossbullet,boss_head->firstptr->bulletx,boss_head->firstptr->bullety-3);
         			addlist(bossbullet,boss_head->firstptr->bulletx-3,boss_head->firstptr->bullety);
            		addlist(bossbullet,boss_head->firstptr->bulletx-5,boss_head->firstptr->bullety);
         			bosstime=time(NULL);
		    	}
			}
         
			if(bossbullet->count>0)
		 	{ 
           		enemyAction(bossbullet,list,reward1);
         	}	 
      
		   if(boss_head->count>0)
		  	{
            	bullet1=list->firstptr;
		    	while(bullet1)
				{		
					if(boss_head->count>0)
					{
	
						if(boss_head->firstptr->bullety==bullet1->bullety&&-bullet1->bulletx>=boss_head->firstptr->bulletx&&bullet1->flag) //�P�_�O�_�Q�l�u���� 
						{
		   					if(boss_head->count>0)
           					{
           						if(j<=boss_head->firstptr->bulletx)
           						{
           							boss_head->firstptr->times++;
           							if(boss_head->firstptr->times>=3)
           							{
			     						score=score+20;
			 							cleanboss(boss_head->firstptr->bulletx,boss_head->firstptr->bullety);
           								boss_head->firstptr->flag=false;
            							boss_exist=false;
            							deletelist(boss_head,boss_head->firstptr->bulletx);
          
    								}
        
	        						bullet1->flag=false;
            						starttime=time(NULL);
        						}
        					}
        				}		
					}
					bullet1=bullet1->nextptr;
				}		
			}
            if(boss_head->count<=0)
           	{
         		pthread_mutex_lock(&mutex) ;
         		gotoxy(22,5);
         		printf("         ");
         		pthread_mutex_unlock(&mutex) ;
		  	}
		}
		  
    	if((-initaltime+time(NULL))>=1&&boss_head->count==0)        //�C�j�@�q�ɶ��ϥͤp�ľ�,�i�վ�����
		{
        	initaltime=time(NULL);
        	pthread_mutex_lock(&mutex);
        	enemy_create(number_enemy,enemyhead);
        	pthread_mutex_unlock(&mutex) ;
    	}

		if(enemyhead->count>0)
		{
      		enemyAction( enemyhead,list,reward1);
    	}// end if enemy
    	if(reward1->count>0)
    	{
    		LIST reward_temp;
    		reward_temp=reward1->firstptr;
    		while(reward_temp)
    		{
    			pthread_mutex_lock(&mutex);
    			gotoxy(reward_temp->bullety,reward_temp->bulletx);
    			printf(" ");
    			gotoxy(reward_temp->bullety,reward_temp->bulletx);
    			printf("��");
    			pthread_mutex_unlock(&mutex) ;
    			if(i==reward_temp->bullety && j<=reward_temp->bulletx&&reward_temp->bulletx<=j+4+plantType)
    			{
    				deletelist(reward1,reward_temp->bulletx);
    				canchange++;
				}
				if(time(NULL)-reward_temp->now>=5)
				{
					deletelist(reward1,reward_temp->bulletx);
				}
    			reward_temp=reward_temp->nextptr;
			}
		}
    	if(keyboard ==27) //�p�G�Vesc�N���� 
        {
            pthread_exit(NULL);
		}
		Sleep(enemy_speed*5);//�i�վ�����
	}//while end
	pthread_exit(NULL);
}
void* moveThread(void* arg1)
{
	bool cont;
	cont=true;
	HANDLE handle;
	DWORD cnt;//�x�s�X�J
    DWORD mode;//Console Mode
    INPUT_RECORD input;
	handle = GetStdHandle(STD_INPUT_HANDLE);//�����o�򥻿�JHandle
	GetConsoleMode(handle, &mode);//�o��򥻿�J��Mode
    SetConsoleMode(handle, mode & ~ENABLE_LINE_INPUT);//�]�w�򥻿�J�Ҧ��A�䤤~ENABLE_LINE_INPUT�N���Ϋ��UEnter�]�i�ʧ@
     while(ReadConsoleInput(handle, &input, 1, &cnt))//�}�lŪ���ϥΪ̪��ʧ@      main loop
    {

		if(out)
		{
			pthread_exit(NULL);
		}
        if(input.EventType == KEY_EVENT)
        {
            if(input.Event.KeyEvent.bKeyDown == TRUE)
            {
               keyboard=input.Event.KeyEvent.wVirtualKeyCode;
               
               if (input.Event.KeyEvent.wVirtualKeyCode ==84)
               {
               		if(plantType==0 && canchange>0)
               		{
				   		plantType=1;
               			type1_time=time(NULL);
               			canchange--;
               		}
			   }
                if (input.Event.KeyEvent.wVirtualKeyCode ==87)//w
                {
                	pthread_mutex_lock(&mutex) ;
                	cleanplant(plantType);
					i--;
    				cont=edge( i, j);
    				if(!cont)
    				{
						i=19;
					}
 					plant(plantType);
        			pthread_mutex_unlock(&mutex) ;
   				}

                 else if (input.Event.KeyEvent.wVirtualKeyCode == 65)//a
                {
                  	pthread_mutex_lock(&mutex) ;
    				cleanplant(plantType);
    				j--;
    				cont=edge( i, j);
					if(!cont)
    				{
						j++;
					}
 					plant(plantType);
   					pthread_mutex_unlock(&mutex) ;
  				}
                else if (input.Event.KeyEvent.wVirtualKeyCode ==83)//s
                {
                   	pthread_mutex_lock(&mutex) ;
   					cleanplant(plantType);
    				i++;
    				cont=edge( i, j);
					if(!cont)
  					{
						i=1;
					}
 					plant(plantType);
        			pthread_mutex_unlock(&mutex) ;
				}
                else if (input.Event.KeyEvent.wVirtualKeyCode ==68)//d
                {
                	pthread_mutex_lock(&mutex) ;
    				cleanplant(plantType);
    				j++;
				    cont=edge( i, j+5);
					if(!cont)
    				{
						j--;
					}
 					plant(plantType);
        			pthread_mutex_unlock(&mutex) ;
				}		
				else if(input.Event.KeyEvent.wVirtualKeyCode ==27)
                {

                pthread_exit(NULL);
				}
         	}
      	}
 		Sleep(10);
	}
}
void plant(int type)
{
	textcolor(5);
	gotoxy(i,j);
	printf("��");
	gotoxy(i,j+2);
	textcolor(BLUE);
	if(type==0)
		printf("��");
	else
		printf("��");
	gotoxy(i,j+4);
	if(type==0)
		printf(">");
	else
		printf("��");
	if(edge(i+1,j)==true)
	{
		if(type==0)
		{
		gotoxy(i+1,j);
		printf("��");
		}
		else
		{
			gotoxy(i+1,j);
			printf("��");
			gotoxy(i+1,j+4);
		printf("��");
		}
	}
	if(edge(i-1,j)==true)
	{
		if(type==0)
		{
			gotoxy(i-1,j);
			printf("��");
    	}
    	else
    	{
    		gotoxy(i-1,j);
	   		printf("��"); 
	   		gotoxy(i-1,j+4);
			printf("��");
		}
	}	
	textcolor(YELLOW);
}
void cleanplant(int type)
{
	gotoxy(i,j);
	printf("  ");
	gotoxy(i,j+2);
	printf("  ");
	gotoxy(i,j+4);
	printf(" ");
	if(edge(i+1,j)==true)
	{
	gotoxy(i+1,j);
	printf("  ");
		if(type==1)
		{
			gotoxy(i+1,j+4);
			printf(" ");
		}
	}
	if(edge(i-1,j)==true)
	{
		gotoxy(i-1,j);
		printf("  ");
		if(type==1)
		{
			gotoxy(i-1,j+4);
			printf(" ");
		}
	}
}
HEAD star1(int n)
{
	HEAD star;
	LIST starfirst;
	int a;
	star=createhead(compare);
	for(a=0;a<n;a++)
	{
		srand(time(NULL)+a*a*a*a*a+1);
		addlist(star,rand()%56+2,rand()%18+1);
	}
	return star;
}
void starmove(HEAD star)
{
	LIST stt;
	stt=star->firstptr;

	while(stt)
	{
		gotoxy(stt->bullety,stt->bulletx);
		printf(" ");
		stt->bulletx--;
		if(!edge(stt->bullety,stt->bulletx))
		{
			stt->bulletx=58;
		}

		gotoxy(stt->bullety,stt->bulletx);
		textcolor(WHITE);
		printf("�D");
		textcolor(YELLOW);
		stt=stt->nextptr;
	}
}
void* backgroundThread(void* arg)
{
	HEAD star;
	star=star1(30);
	while(1)
	{
		pthread_mutex_lock(&mutex) ;
		starmove(star);
		pthread_mutex_unlock(&mutex) ;
		if(out || keyboard ==27)
		{
			pthread_exit(NULL);
		}
		Sleep(200);
	}
}
int compare(int n1,int n2)
{
	return n1-n2;
}
void gotoxy (int x, int y)
{
    static COORD c; c.X = y; c.Y = x;
    SetConsoleCursorPosition (hOut, c);
}
void cleanboss(int x,int y)
{
	pthread_mutex_lock(&mutex) ;
   	int i,yy;
   	yy=y;
   	for(i=0;i<5;i++)
   	{
   		gotoxy1(x,yy-2);

		printf("  ");
   		yy++;
   }
   yy=y;
   for(i=0;i<3;i++)
   {
   		gotoxy1(x-2,yy-1);
   		printf("  ");
   		yy++;
   }
   	gotoxy1(x-4,y);
   	printf("  ");
  	pthread_mutex_unlock(&mutex);
}
void drawboss(int x,int y)
{
  	pthread_mutex_lock(&mutex) ;
 	int i,yy;
   	yy=y;
   	for(i=0;i<5;i++)
   	{
   		gotoxy1(x,yy-2);
		if(i==3)
		{
			printf(" *");
		}
		else
			printf(" ��");
   		yy++;
   }
   yy=y;
   for(i=0;i<3;i++)
   {
   		gotoxy1(x-2,yy-1);
   		printf(" ��");
   		yy++;
   }
   	gotoxy1(x-4,y);
	printf(" ��");
   	pthread_mutex_unlock(&mutex);
 }
void enemyAction(HEAD enemyhead,HEAD list,HEAD reward1)
{
        LIST temp;
		LIST bullet;
		temp=enemyhead->firstptr;
    	while(temp)//traverse
		{
			LIST bullet;
		    pthread_mutex_lock(&mutex) ;
		    gotoxy(temp->bullety,temp->bulletx);
			printf(" ");
			pthread_mutex_unlock(&mutex);
			bullet=list->firstptr;
			while(bullet)
			{	
				if(temp->bullety==bullet->bullety&&-bullet->bulletx>=temp->bulletx-1&&bullet->flag) //�I���P�_
				{
					if(j<=temp->bulletx-1) 
              		{
              			if(temp->reward&&temp->bulletx<=45)
              			{
              				addlist(reward1,temp->bulletx,temp->bullety);
				  		}
             			deletelist(enemyhead,temp->bulletx);
			  			temp->flag=false;
						bullet->flag=false;
	            		score++;
	         			pthread_mutex_lock(&mutex) ;
	        			gotoxy(2,63);
           				printf("����:%d",score);
    	   				pthread_mutex_unlock(&mutex);
	        		}
				}

				bullet=bullet->nextptr;
			}
			if(temp->flag)
			{	
				temp->bulletx--;           //�ĤH������
      			if(i==temp->bullety && j==temp->bulletx ) //�p�G�Q�ĤH����ΥX��
				{
					out=true;
					gotoxy(10,20);
					printf("PLEASE PRESS ANY WORD!!");
					pthread_exit(NULL);
				}
        		if(!edge(temp->bullety,temp->bulletx))
				{
					deletelist(enemyhead,temp->bulletx);   
		    	}
		    	else
		    	{
		    		pthread_mutex_lock(&mutex);
		        	gotoxy(temp->bullety,temp->bulletx);
					printf("��");
					 pthread_mutex_unlock(&mutex);
		  	   }
			    pthread_mutex_lock(&mutex) ;
			    gotoxy(8,62);
	  		      printf("  ");
				gotoxy(8,62);
				printf("%d",enemyhead->count);
    	        pthread_mutex_unlock(&mutex);
			}
			temp=temp->nextptr;
		}
}// end if enemy
void* playMusicThread(void* arg2) //dont play music 
{
   // PlaySound( "Im Yours.wav" , NULL, SND_FILENAME | SND_ASYNC ); //�񭵼� 
	if(out || keyboard ==27)
	{
		pthread_exit(NULL);
	}

}

