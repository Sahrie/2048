#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <graphics.h>      // 引用图形库头文件
#include <conio.h>


#define SIZE 4 //设置尺寸长宽
void printBoard(int board[SIZE][SIZE]);//打印界面
void insertNewNumber(int board[SIZE][SIZE]);//生成随机2，4，8
void upmove(int board[SIZE][SIZE]);//向上移动
void downmove(int board[SIZE][SIZE]);//向下移动
void leftmove(int board[SIZE][SIZE]);//向左移动
void rightmove(int board[SIZE][SIZE]);//向右移动
int gameoverjudge(const int  board[SIZE][SIZE]);
int winjudge(const int board[SIZE][SIZE]);
IMAGE imgboard, img0, img2, img4, img8, img16, img32, img64, img128, img256, img512, img1024, img2048;


static int sum = 0;
char move;

int main(void)
{
	
	srand(time(0));  //随机数种子
	
	IMAGE winimg, loseimg;
	loadimage(&winimg, _T("img\\win.jpg"));
	loadimage(&loseimg, _T("img\\lose.jpg"));
	int board[SIZE][SIZE];     //数组初始化
	for (int i = 0; i <= SIZE-1; i++)
	{
		for (int j = 0; j <= SIZE-1; j++)
		{
			board[i][j] = 0;
		}
	}

	insertNewNumber(board);
	insertNewNumber(board);//生成两个初始数值
	
	initgraph(494, 768);
	printBoard(board);//生成初始棋盘
	
	 
	 int win = 0;
	 int lose = 0;
	while (true)
	{
		move = getch();
		
	
		switch (move)//用字符WASD对应的ASCLL码
		{
		case 115:
			downmove(board);
			downmove(board);
			downmove(board);
			insertNewNumber(board);
		
			printBoard(board);
		
		
			break;
		case 97:
			leftmove(board);
			leftmove(board);
			leftmove(board);
			insertNewNumber(board);

			printBoard(board);
			break;
		case 100:
			rightmove(board);
			rightmove(board);
			rightmove(board);
			insertNewNumber(board);

			printBoard(board);
			break;
		case 119:
			upmove(board);
			upmove(board);
			upmove(board);
			insertNewNumber(board);

			printBoard(board);
			break;
		}

		lose = gameoverjudge(board);
		win = winjudge(board);
		if (win == 1)
		{
			cleardevice();
			putimage(0, 0, &winimg);
			while (true)
			getch();
		}
		if (lose == 1)
		{
			cleardevice();
			putimage(0, 0, &loseimg);
			while (true)
			getch();
		}
	}
	
	
}










void printBoard(int board[SIZE][SIZE])   //打印界面
{
	
	loadimage(&img0, TEXT("img\\0.png"));
	loadimage(&imgboard, TEXT("img\\1.jpg"));
	loadimage(&img2, TEXT("img\\2.png"));
	loadimage(&img4, TEXT("img\\4.png"));
	loadimage(&img8, TEXT("img\\8.png"));
	loadimage(&img16, TEXT("img\\16.png"));
	loadimage(&img32, TEXT("img\\32.png"));
	loadimage(&img64, TEXT("img\\64.png"));
	loadimage(&img128, TEXT("img\\128.png"));
	loadimage(&img256, TEXT("img\\256.png"));
	loadimage(&img512, TEXT("img\\512.png"));
	loadimage(&img1024, TEXT("img\\1024.png"));
	loadimage(&img2048, TEXT("img\\2048.jpg"));
	cleardevice();
	putimage(0, 0, &imgboard);// 绘图环境初始化
	

	BeginBatchDraw();//开始批量绘图
	
	settextstyle(32, 0, _T("宋体"));
	TCHAR s1[11];
	_stprintf(s1, _T("%d"), sum);// 在屏幕中央输出总分
	outtextxy(80,45,s1);


	int x = 46, y = 322;//基础坐标

	for (int i = 0; i <= SIZE-1; i++)
	{
		for (int j = 0; j <= SIZE-1; j++)
		{
			switch (board[i][j])
			{
				case 0:
					putimage(x, y, &img0);
					break;
				case 2:
					putimage(x, y, &img2);
					break;
				case 4:
					putimage(x, y, &img4);
					break;
				case 8:
					putimage(x, y, &img8);
					break;
				case 16:
					putimage(x, y, &img16);
					break;
				case 32:
					putimage(x, y, &img32);
					break;
			
				case 64:
					putimage(x, y, &img64);
					break;
				case 128:
					putimage(x, y, &img128);
					break;
				case 256:
					putimage(x, y, &img256);
					break;
				case 512:
					putimage(x, y, &img512);
					break;
				case 1024:
					putimage(x, y, &img1024);
					break;
			
				case 2048:
					putimage(x, y, &img2048);
					break;
			}
					x = x + 105;
			
		}
		x = 46;
		y = y + 105;
	}
	
	EndBatchDraw();
	
}                   

void insertNewNumber(int board[SIZE][SIZE])
{
	int isblank = 0;
	for (int i = 0; i <= SIZE - 1; i++)		//判断数组是否有空位
	{
		for (int j = 0; j <= SIZE - 1; j++)
		{
			if (board[i][j] == 0)
				isblank = 1;
		}
	}
	if (isblank == 0) //如果数组没有空位，则无需加入随机值
		return  ;
	
	
	int insertNumber, checkNumber, locationNumber1, locationNumber2;
	checkNumber = rand() % 4;   // 如果没有空位，就生成随机值
	switch (checkNumber)
	{
	
	case 0:
		insertNumber = 2;
	case 1:
		insertNumber = 2;
		break;
	case 2:
		insertNumber = 4;
		break;
	case 3:
		insertNumber = 8;
		break;
     }

	
	
	
	do                                  //在随机位置赋予上述随机值
	{
		locationNumber1 = rand() % SIZE;
		locationNumber2 = rand() % SIZE;
	} while (board[locationNumber1][locationNumber2] != 0);
	
	board[locationNumber1][locationNumber2]  = insertNumber;
	sum = sum + insertNumber;//自动积分
}

void upmove(int board[SIZE][SIZE])
{
	for (int i = 0; i <= SIZE - 2; i++)  //最底一行不需要做加法，故SIZE - 2
	{
		for (int j = 0; j <= SIZE -1 ; j++)
		{
			if (board[i][j] == board[i + 1][j])
			{
				board[i][j] = board[i][j] * 2;
				board[i + 1][j] = 0;
				sum = sum + board[i][j];//自动积分
			}
			else if (board[i][j] == 0)
			{
				board[i][j] = board[i + 1][j];
				board[i + 1][j] = 0;
			}
		}
	}

}

void downmove(int board[SIZE][SIZE])
{
	for (int i = 3; i >= 1; i--)  //最顶一行不需要做加法，故SIZE - 2
	{
		for (int j = 0; j <= SIZE-1; j++)
		{
			if (board[i][j] == board[i - 1][j])
			{
				board[i][j] = board[i][j] * 2;
				board[i - 1][j] = 0;
				sum = sum + board[i][j];//自动积分
			}
			else if (board[i][j] == 0)
			{
				board[i][j] = board[i - 1][j];
				board[i - 1][j] = 0;
			}
		}
	}

}

void leftmove(int board[SIZE][SIZE])
{
	for (int i = 0; i <= SIZE-1 ; i++)  
	{
		for (int j = 0; j <= SIZE-2; j++)  //最右一行不需要做加法，故SIZE - 2
		{
			if (board[i][j] == board[i][j+1])
			{
				board[i][j] = board[i][j] * 2;
				board[i][j+1] = 0;
				sum = sum + board[i][j];//自动积分
			}
			else if (board[i][j] == 0)
			{
				board[i][j] = board[i][j+1];
				board[i][j+1] = 0;
			}
		}
	}
	
}

void rightmove(int board[SIZE][SIZE])
{
	for (int i = 0; i <= SIZE-1; i++)
	{
		for (int j = 3; j >= 1; j--)  //最左一行不需要做加法
		{
			if (board[i][j] == board[i][j - 1])
			{
				board[i][j] = board[i][j] * 2;
				board[i][j - 1] = 0;
				sum = sum + board[i][j];//自动积分
			}
			else if (board[i][j] == 0)
			{
				board[i][j] = board[i][j - 1];
				board[i][j - 1] = 0;
			}
		}
	}
	
}

int gameoverjudge(const int board[SIZE][SIZE])
{
	int lose = 0, isblank = 0, judgesumrl = 0, judgesumdu = 0; //判断数组是否有空位，上下左右是否有相同数字，若无则失败
	for (int i = 0; i <= SIZE - 1; i++)		//判断数组是否有空位
	{
		for (int j = 0; j <= SIZE - 1; j++)
		{
			if (board[i][j] == 0)
				isblank = 1;
		}
	}

	for (int i = 0; i <= SIZE - 2; i++)  //最底一行不需要做加法，故SIZE - 2,判断上下方是否有相同数字
	{
		for (int j = 0; j <= SIZE - 1; j++)
		{
			if (board[i][j] == board[i+1][j])
				judgesumdu = 1;
		}
	}

	for (int i = 0; i <= SIZE - 1; i++)
	{
		for (int j = 0; j <= SIZE - 2; j++)  //最右一行不需要做加法，故SIZE - 2,判断左右方是否有相同数字
		{
			if (board[i][j] == board[i][j + 1])
				judgesumrl = 1;
		}
	}
	
	if (judgesumrl == 0 && judgesumdu == 0 && isblank == 0)
	{
		lose = 1;
		return lose;
	}
	else return lose;



}

int winjudge(const int board[SIZE][SIZE])
{
	int win = 0;
	int is2048 = 0;
	for (int i = 0; i <= SIZE - 1; i++)
	{
		for (int j = 0; j <= SIZE - 1; j++)
		{
			if (board[i][j] == 2048)
			{
				is2048 = 1;
			}
		}

	}
	if (is2048)
	{
		win = 1;
		return win;
			
	}
	else
		return win;
}