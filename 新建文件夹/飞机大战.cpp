#include<iostream>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
using namespace std;

#define high 20  // ��Ϸ����ߴ�
#define wide 40
#define EnemyNum 5 // �л�����

int x1,y1;//�ҷ��ɻ�
int x2[5],y2[5];//�з��ɻ�
int a[high][wide]={0};//��ϷԪ�� 0-�ո� 1-�ҷ��ɻ� 2-�з��ɻ� 3-�ӵ�
int score;//�÷� 
int enemyspeed=5;//�л��ٶ� 
int speed=0;//�л������ٶ� 
int life;//����ֵ 

void gotoxy(int x,int y)  //����ƶ���(x,y)λ��//���������� 
{
  HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD pos;
  pos.X = x;
  pos.Y = y;
  SetConsoleCursorPosition(handle,pos);
}

void HideCursor() // �������ع��//���������� 
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};  // �ڶ���ֵΪ0��ʾ���ع��
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);//�����ͽṹ�嶼��windows.h�ж��塣
}

void startup()
{
	x1=high-1;//�ɻ���ʼλ�� 
	y1=wide/2;
	a[x1][y1]=1;//�����ҷ��ɻ� 
	int n;
	for(n=0;n<5;n++)//������ɵз��ɻ� 
	{
		x2[n]=rand()%2;
		y2[n]=rand()%40;
		a[x2[n]][y2[n]]=3;
	} 
	score=0;
	enemyspeed = 5;
}
	
void show()//��Ϸ���� 
{
	for(int i=0;i<00;i++)
	{
		for(int j=0;j<40;j++)
		{
			if(a[i][j]==0)
			{
				gotoxy(i,j);
				cout<<' ';//0-�ո� 
			}
			else if(a[i][j]==1)
			{
				gotoxy(i,j);
				cout<<"@";//1-�ҷ��ɻ� 
			}
			else if(a[i][j]==2)
			{
				gotoxy(i,j);
				cout<<"#";//2-�з��ɻ� 
			}
			else if(a[i][j]==3)
			{
				gotoxy(i,j);
				cout<<"��";//3-�ӵ� 
			}
			cout<<endl;
		}
	}
	cout<<"������"<<score<<endl;
	cout<<"����ֵ��"<<life<<endl; 
}

void  bullet()//�ӵ� 
{
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<40;j++)
		{
					if(a[i][j]==3)//�е� 
					{
						for(int n=0;n<5;n++)
							{
								if(i==x2[n]&&j==y2[n])
								{	
									score++;
									a[x2[n]][y2[n]]=0;
									x2[n]=rand()%2;
									y2[n]=rand()%40;
									a[x2[n]][y2[n]]=2;
									a[i][j]=0;
								}
							}
								a[i][j]=0;
								if(i>0)
								a[i-1][j]=3;//�ӵ� 
					}
		}
	}
}

void enemymovespeed()//�ƶ��ٶ� 
{
	if(speed%5==0&&enemyspeed>3)
	speed--;
} 

void enemymove()
{
	int n;
		if(speed<enemyspeed)
		speed++;
	if(speed==enemyspeed)//�л����� 
	{
		for( n=0;n<5;n++)
		{
				a[x2[n]][y2[n]]=0;
				y2[n]++;
				y2[n]=-1+rand()%3;
				speed=0;
				a[x2[n]][y2[n]]=2;
			
		}
		if(x1==x2[n]&&y1==y2[n])//�л������ҷ��ɻ� 
		{
			cout<<"game over";
			Sleep(3000);
			system("pause");
			exit(0); 
		}
		if(x2[n]>40)//����ʧ�ܣ��۷� 
		{
			score--;	
			a[x2[n]][y2[n]]=0;
			x2[n]=rand()%20;
		    y2[n]=rand()%2;
			a[x2[n]][y2[n]]=2;	
		}	
	}
}
		

void updateWithoutInput()//���û������޹صĸ���
{
	bullet();
	enemymovespeed();
	enemymove();
}

void updateWithInput()//���û������йصĸ���
{
	if(kbhit())
	{
		char input;
		input=getch();
		if(input=='a'&&y1>0)
		{
			a[x1][y1]=0;
			y1--;
			a[x1][y1]=1;
		}
		else if(input=='d'&&y1<20)
		{
			a[x1][y1]=0;
			y1++;
			a[x1][y1]=1;
		}
		else if(input=='w'&&x1>0)
		{
			a[x1][y1]=0;
			x1--;
			a[x1][y1]=1;
		}
		else if(input=='s'&&x1<40)
		{
			a[x1][y1]=0;
			x1++;
			a[x1][y1]=1;
		}
		else if(input==' ')
		{
			a[x1-1][y1]=3;
		}
	}
}


int main()
{
  startup();  // ���ݳ�ʼ��
  while (1) //  ��Ϸѭ��ִ��
  {
	show();  // ��ʾ����
	updateWithoutInput();  // ���û������޹صĸ���
	updateWithInput();  // ���û������йصĸ���
  }
  return 0;
}




















