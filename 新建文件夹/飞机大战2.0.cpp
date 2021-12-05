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
int a[high][wide]={0};//游戏元素
int score=0;//得分 
int life=10;//生命值 
int speed=0;
int enemyspeed=10;//敌机速度 
unsigned long long t;
void gotoxy(int x,int y)  //光标移动到(x,y)位置 
{
  HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD pos;
  pos.X = x;
  pos.Y = y;
  SetConsoleCursorPosition(handle,pos);
}

void HideCursor() // 用于隐藏光标
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};  // 第二个值为0表示隐藏光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);//函数和结构体都在windows.h中定义。
}

void startup()//初始化 
{
	x1=high-1;//我方飞机初始位置 
	y1=wide/2;
	a[x1][y1]=1;
	for(int n=0;n<5;n++)
	{
		x2[n]=rand()%2;//敌方飞机随机位置 
		y2[n]=rand()%40;
		a[x2[n]][y2[n]]=2;
	}
	score=0;
	enemyspeed=10;
}

void show()//画面
{
	gotoxy(0,0);
	for(int i=0;i<high;i++)
	{
		for(int j=0;j<wide;j++)
		{
			if(a[i][j]==0)
			cout<<' ';//0-空格 
			if(a[i][j]==1)
			cout<<'@';//我方飞机
			if(a[i][j]==2)
			cout<<'#'; //敌方飞机
			if(a[i][j]==3)
			cout<<'1';//子弹 
		}
		cout<<endl;
	}
	cout<<"得分："<<score<<endl;
	cout<<"生命值："<<life<<endl; 
} 

void bullet()//子弹 
{
	HideCursor();
	for(int i=0;i<high;i++)
	{
		for(int j=0;j<wide;j++)
		{
			if(a[i][j]==3)
			{
				a[i][j]=0;//子弹向上移动 
				if(i>0)
				a[i-1][j]=3;
				for(int n=0;n<5;n++)
				{
					if((i==x2[n]) && (j==y2[n]))//打中敌方飞机 
					{
						score++;
						a[x2[n]][y2[n]]=0;//生成新的敌方飞机 
						x2[n]=rand()%2;
						y2[n]=rand()%wide;
						a[x2[n]][y2[n]]=2;
						a[i][j]=0;//子弹消失 
					}
				}
			}
		}
	}
} 

void enemyplane()//敌机下落，敌机出界，敌机撞机 
{
	for(int n=0;n<5;n++)
	{
		
		if(x1==x2[n]&&y1==y2[n] || life<=0)//飞机相撞
		{
			cout<<"再接再厉！";
			Sleep(1000);
			system("pause");
			 exit(0);
		}
		else if(x2[n]==high)//飞机出界 
		{
			a[x2[n]][y2[n]]=0;
			x2[n]=0;
			y2[n]=rand()%wide;
			a[x2[n]][y2[n]]=2;
			score--;//扣分 
			life--;//生命值减少 
		}
		else //敌机下落 
		{
			a[x2[n]][y2[n]]=0;
			x2[n]++;
			y2[n]=rand()%40;
			speed=0;
			a[x2[n]][y2[n]]=2;
		}
	}  
} 

void enemymovespeed()//敌机移动速度
{
	if(score%5==0&&score>0&&enemyspeed>2)
	speed--;
} 

void updateWithoutInput()//与用户输入无关的更新
{
	bullet();
	enemymovespeed();
	if(!(t%enemyspeed))enemyplane();
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
		else if(input==' ')//子弹 
		a[x1-1][y1]=3;
	}
}

int main()
{
  startup();  // 数据初始化
  while (1) //  游戏循环执行
  {
  	t++;
  	updateWithInput();// 与用户输入有关的更新
	updateWithoutInput();  // 与用户输入无关的更新
	
	show(); 	  // 显示画面 
  }
  return 0;
}
