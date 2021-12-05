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
int a[high][wide]={0};//��ϷԪ��
int score=0;//�÷� 
int life=10;//����ֵ 
int speed=0;
int enemyspeed=10;//�л��ٶ� 
unsigned long long t;
void gotoxy(int x,int y)  //����ƶ���(x,y)λ�� 
{
  HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD pos;
  pos.X = x;
  pos.Y = y;
  SetConsoleCursorPosition(handle,pos);
}

void HideCursor() // �������ع��
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};  // �ڶ���ֵΪ0��ʾ���ع��
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);//�����ͽṹ�嶼��windows.h�ж��塣
}

void startup()//��ʼ�� 
{
	x1=high-1;//�ҷ��ɻ���ʼλ�� 
	y1=wide/2;
	a[x1][y1]=1;
	for(int n=0;n<5;n++)
	{
		x2[n]=rand()%2;//�з��ɻ����λ�� 
		y2[n]=rand()%40;
		a[x2[n]][y2[n]]=2;
	}
	score=0;
	enemyspeed=10;
}

void show()//����
{
	gotoxy(0,0);
	for(int i=0;i<high;i++)
	{
		for(int j=0;j<wide;j++)
		{
			if(a[i][j]==0)
			cout<<' ';//0-�ո� 
			if(a[i][j]==1)
			cout<<'@';//�ҷ��ɻ�
			if(a[i][j]==2)
			cout<<'#'; //�з��ɻ�
			if(a[i][j]==3)
			cout<<'1';//�ӵ� 
		}
		cout<<endl;
	}
	cout<<"�÷֣�"<<score<<endl;
	cout<<"����ֵ��"<<life<<endl; 
} 

void bullet()//�ӵ� 
{
	HideCursor();
	for(int i=0;i<high;i++)
	{
		for(int j=0;j<wide;j++)
		{
			if(a[i][j]==3)
			{
				a[i][j]=0;//�ӵ������ƶ� 
				if(i>0)
				a[i-1][j]=3;
				for(int n=0;n<5;n++)
				{
					if((i==x2[n]) && (j==y2[n]))//���ез��ɻ� 
					{
						score++;
						a[x2[n]][y2[n]]=0;//�����µĵз��ɻ� 
						x2[n]=rand()%2;
						y2[n]=rand()%wide;
						a[x2[n]][y2[n]]=2;
						a[i][j]=0;//�ӵ���ʧ 
					}
				}
			}
		}
	}
} 

void enemyplane()//�л����䣬�л����磬�л�ײ�� 
{
	for(int n=0;n<5;n++)
	{
		
		if(x1==x2[n]&&y1==y2[n] || life<=0)//�ɻ���ײ
		{
			cout<<"�ٽ�������";
			Sleep(1000);
			system("pause");
			 exit(0);
		}
		else if(x2[n]==high)//�ɻ����� 
		{
			a[x2[n]][y2[n]]=0;
			x2[n]=0;
			y2[n]=rand()%wide;
			a[x2[n]][y2[n]]=2;
			score--;//�۷� 
			life--;//����ֵ���� 
		}
		else //�л����� 
		{
			a[x2[n]][y2[n]]=0;
			x2[n]++;
			y2[n]=rand()%40;
			speed=0;
			a[x2[n]][y2[n]]=2;
		}
	}  
} 

void enemymovespeed()//�л��ƶ��ٶ�
{
	if(score%5==0&&score>0&&enemyspeed>2)
	speed--;
} 

void updateWithoutInput()//���û������޹صĸ���
{
	bullet();
	enemymovespeed();
	if(!(t%enemyspeed))enemyplane();
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
		else if(input=='d'&&y1<39)
		{
		a[x1][y1]=0;
		y1++;
		a[x1][y1]=1;
		}
		else if(input=='w')
		{
		a[x1][y1]=0;
		x1--;
		a[x1][y1]=1;
		}
		else if(input=='s')
		{
		a[x1][y1]=0;
		x1++;
		a[x1][y1]=1;
		}
		else if(input==' ')//�ӵ� 
		a[x1-1][y1]=3;
	}
}

int main()
{
  startup();  // ���ݳ�ʼ��
  while (1) //  ��Ϸѭ��ִ��
  {
  	t++;
  	updateWithInput();// ���û������йصĸ���
	updateWithoutInput();  // ���û������޹صĸ���
	
	show(); 	  // ��ʾ���� 
  }
  return 0;
}
