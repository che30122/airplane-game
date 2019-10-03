#include<stdio.h>
#include<stdlib.h>
#include"conio2.h"
#include"conio0.h"
#include<windows.h>
struct data_1
{
	char *a;
	int score;
};
typedef struct data_1* DATA1;
void inital();   //初始化 
int set(int *number,int *speed,int * bullet)
{
	int keyboard,out=1,back=0;
	DATA1 rank2;
				 	
    rank2=(DATA1)malloc(10*sizeof(struct data_1));
	int l;
	for(l=0;l<10;l++)
	{
		(rank2+l)->score=-1;
	}
	gotoxy1(30,1);
    printf("打飛機遊戲");
    gotoxy1(10,4);
	while(out)
	{

		int y,y1;
		y=wherey();
		inital();
      	if(y==4)    
      	{
      	  	gotoxy1(30,1);
    		printf("打飛機遊戲");
      		inital();
      		textbackground(CYAN);  //設定字背景 
			gotoxy1(25,4);
			printf("EASY");
			textbackground(BLACK);
	  	}
	  	else if(y==6)
	  	{
	  	 	gotoxy1(30,1);
    		printf("打飛機遊戲");
	  		inital();
	  		textbackground(CYAN);//設定字背景 
	  		gotoxy1(25,6);
			printf("MEDIUM");
			textbackground(BLACK);
	  	}
	  	else if(y==8)
	  	{
	  		gotoxy1(30,1);
    		printf("打飛機遊戲");
	  		inital();
	  		textbackground(CYAN);//設定字背景 
	  		gotoxy1(25,8);
			printf("HARD");
			textbackground(BLACK);
	  	}
	  	else if(y==10)
	  	{
	  		gotoxy1(30,1);
    		printf("打飛機遊戲");
	  		inital();
	  		textbackground(CYAN);//設定字背景 
	  		gotoxy1(25,10);
			printf("VERY HARD");
			textbackground(BLACK);
	  	}
	  	else if(y==12)
	  	{
	  		gotoxy1(30,1);
    		printf("打飛機遊戲");
	 	 	inital();
	  		textbackground(CYAN);//設定字背景 
	  		gotoxy1(25,12);
	  		printf("SEE RANK");
			textbackground(BLACK);
	  	}

		keyboard=getch();
	 	if(keyboard==224)
	 	{
	 		keyboard=getch();
	 		switch(keyboard)   // 讓游標能上下移動 
	 		{
	 			case 72:
	 				if(wherey()==4)
	 				{
	 					gotoxy1(10,12);
					}
					else
					{
						gotoxy1(10,wherey()-2);
					}
	 				break;
	 		
	 			case 80:
	 	
	 				if(wherey()==12)
	 				{
	 					gotoxy1(10,4);
				 	}	
				 	else
				 	{
				 		gotoxy1(10,wherey()+2);
				 	}
	 				break;
		 	}
	 	}
	 	else if(keyboard==13)//按下enter後的設定 
	 	{
	 		y1=wherey();
	 		switch(y1)
	 		{
	 			case 4:
		 
		 			*number=3;
		 			*speed=4;
		 			back=0;	
		 			out=0;
		 			* bullet=20;
		 			break;
	 			case 6:
	 				* bullet=15;
			 		*number=6;
	 				*speed=3;
	 				back=1;
	 				out=0;
	 				break;
	 			case 8:
				 	* bullet=10;
	 				*number=9;
	 				*speed=2;
	 				back=2;
	 				out=0;
	 				break;
	 			case 10:
	 				* bullet=5;
	 				*number=13;
	 				*speed=1;
	 				out=0;
	 				back=3;
	 				break;
	 		
	 			case 12:
					system("cls");
					FILE * fptr1;
					fptr1=fopen("rank1.txt","r");
					for(l=0;l<10;l++)
					{
						(rank2+l)->a=(char*)malloc(50*sizeof(char));
					}
    				l=0;
   					 while(	fscanf(fptr1,"%s%d",(rank2+l)->a,&((rank2+l)->score))!=EOF)
    				{
						l++;
					}
					gotoxy1(34,2);
					printf("RANK");
					gotoxy1(21,4);
					printf("NAME                 SCORE");
					for(l=0;l<10;l++)
					{
						if((rank2+l)->score>=0)
						{
							gotoxy1(21,5+l);
							printf("%d.%s",l+1,(rank2+l)->a);
							gotoxy1(42,5+l);
							printf("%d",(rank2+l)->score);
						}
						else
						{
							gotoxy1(21,5+l);
							printf("%d.-------",l+1);
							gotoxy1(42,5+l);
							printf("-------");
						}
					}
				fclose(fptr1);
				gotoxy1(27,21);
				system("pause");
	 			system("cls");
	 			gotoxy1(10,12);
	 			break;
		 	}
	 	}

	}

}
void inital()
{
	gotoxy1(25,4);
 	printf("EASY");
 	gotoxy1(25,6);
	printf("MEDIUM");
	gotoxy1(25,8);
	printf("HARD");
	gotoxy1(25,10);
	printf("VERY HARD");
	gotoxy1(25,12);
	printf("SEE RANK");
}
