#include<iostream>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
using namespace std;

#define high 20  // 游戏画面尺寸
#define wide 40
#define EnemyNum 5 // 敌机个数

int x1,y1;//我方飞机
int x2[5],y2[5];//敌方飞机
int a[high][wide]={0};//游戏元素 0-空格 1-我方飞机 2-敌方飞机 3-子弹
int score;//得分 
int enemyspeed=5;//敌机速度 
int speed=0;//敌机飞行速度 
int life;//生命值 

void gotoxy(int x,int y)  //光标移动到(x,y)位置//？？？？？ 
{
  HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD pos;
  pos.X = x;
  pos.Y = y;
  SetConsoleCursorPosition(handle,pos);
}

void HideCursor() // 用于隐藏光标//？？？？？ 
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};  // 第二个值为0表示隐藏光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);//函数和结构体都在windows.h中定义。
}

void startup()
{
	x1=high-1;//飞机初始位置 
	y1=wide/2;
	a[x1][y1]=1;//生成我方飞机 
	int n;
	for(n=0;n<5;n++)//随机生成敌方飞机 
	{
		x2[n]=rand()%2;
		y2[n]=rand()%40;
		a[x2[n]][y2[n]]=3;
	} 
	score=0;
	enemyspeed = 5;
}
	
void show()//游戏画面 
{
	for(int i=0;i<00;i++)
	{
		for(int j=0;j<40;j++)
		{
			if(a[i][j]==0)
			{
				gotoxy(i,j);
				cout<<' ';//0-空格 
			}
			else if(a[i][j]==1)
			{
				gotoxy(i,j);
				cout<<"@";//1-我方飞机 
			}
			else if(a[i][j]==2)
			{
				gotoxy(i,j);
				cout<<"#";//2-敌方飞机 
			}
			else if(a[i][j]==3)
			{
				gotoxy(i,j);
				cout<<"！";//3-子弹 
			}
			cout<<endl;
		}
	}
	cout<<"分数："<<score<<endl;
	cout<<"生命值："<<life<<endl; 
}

void  bullet()//子弹 
{
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<40;j++)
		{
					if(a[i][j]==3)//中弹 
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
								a[i-1][j]=3;//子弹 
					}
		}
	}
}

void enemymovespeed()//移动速度 
{
	if(speed%5==0&&enemyspeed>3)
	speed--;
} 

void enemymove()
{
	int n;
		if(speed<enemyspeed)
		speed++;
	if(speed==enemyspeed)//敌机下落 
	{
		for( n=0;n<5;n++)
		{
				a[x2[n]][y2[n]]=0;
				y2[n]++;
				y2[n]=-1+rand()%3;
				speed=0;
				a[x2[n]][y2[n]]=2;
			
		}
		if(x1==x2[n]&&y1==y2[n])//敌机命中我方飞机 
		{
			cout<<"game over";
			Sleep(3000);
			system("pause");
			exit(0); 
		}
		if(x2[n]>40)//拦截失败，扣分 
		{
			score--;	
			a[x2[n]][y2[n]]=0;
			x2[n]=rand()%20;
		    y2[n]=rand()%2;
			a[x2[n]][y2[n]]=2;	
		}	
	}
}
		

void updateWithoutInput()//与用户输入无关的更新
{
	bullet();
	enemymovespeed();
	enemymove();
}

void updateWithInput()//与用户输入有关的更新
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
  startup();  // 数据初始化
  while (1) //  游戏循环执行
  {
	show();  // 显示画面
	updateWithoutInput();  // 与用户输入无关的更新
	updateWithInput();  // 与用户输入有关的更新
  }
  return 0;
}




















