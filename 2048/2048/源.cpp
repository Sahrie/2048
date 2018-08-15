#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <graphics.h>      // ����ͼ�ο�ͷ�ļ�
#include <conio.h>


#define SIZE 4 //���óߴ糤��
void printBoard(int board[SIZE][SIZE]);//��ӡ����
void insertNewNumber(int board[SIZE][SIZE]);//�������2��4��8
void upmove(int board[SIZE][SIZE]);//�����ƶ�
void downmove(int board[SIZE][SIZE]);//�����ƶ�
void leftmove(int board[SIZE][SIZE]);//�����ƶ�
void rightmove(int board[SIZE][SIZE]);//�����ƶ�
int gameoverjudge(const int  board[SIZE][SIZE]);
int winjudge(const int board[SIZE][SIZE]);
IMAGE imgboard, img0, img2, img4, img8, img16, img32, img64, img128, img256, img512, img1024, img2048;


static int sum = 0;
char move;

int main(void)
{
	
	srand(time(0));  //���������
	
	IMAGE winimg, loseimg;
	loadimage(&winimg, _T("img\\win.jpg"));
	loadimage(&loseimg, _T("img\\lose.jpg"));
	int board[SIZE][SIZE];     //�����ʼ��
	for (int i = 0; i <= SIZE-1; i++)
	{
		for (int j = 0; j <= SIZE-1; j++)
		{
			board[i][j] = 0;
		}
	}

	insertNewNumber(board);
	insertNewNumber(board);//����������ʼ��ֵ
	
	initgraph(494, 768);
	printBoard(board);//���ɳ�ʼ����
	
	 
	 int win = 0;
	 int lose = 0;
	while (true)
	{
		move = getch();
		
	
		switch (move)//���ַ�WASD��Ӧ��ASCLL��
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










void printBoard(int board[SIZE][SIZE])   //��ӡ����
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
	putimage(0, 0, &imgboard);// ��ͼ������ʼ��
	

	BeginBatchDraw();//��ʼ������ͼ
	
	settextstyle(32, 0, _T("����"));
	TCHAR s1[11];
	_stprintf(s1, _T("%d"), sum);// ����Ļ��������ܷ�
	outtextxy(80,45,s1);


	int x = 46, y = 322;//��������

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
	for (int i = 0; i <= SIZE - 1; i++)		//�ж������Ƿ��п�λ
	{
		for (int j = 0; j <= SIZE - 1; j++)
		{
			if (board[i][j] == 0)
				isblank = 1;
		}
	}
	if (isblank == 0) //�������û�п�λ��������������ֵ
		return  ;
	
	
	int insertNumber, checkNumber, locationNumber1, locationNumber2;
	checkNumber = rand() % 4;   // ���û�п�λ�����������ֵ
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

	
	
	
	do                                  //�����λ�ø����������ֵ
	{
		locationNumber1 = rand() % SIZE;
		locationNumber2 = rand() % SIZE;
	} while (board[locationNumber1][locationNumber2] != 0);
	
	board[locationNumber1][locationNumber2]  = insertNumber;
	sum = sum + insertNumber;//�Զ�����
}

void upmove(int board[SIZE][SIZE])
{
	for (int i = 0; i <= SIZE - 2; i++)  //���һ�в���Ҫ���ӷ�����SIZE - 2
	{
		for (int j = 0; j <= SIZE -1 ; j++)
		{
			if (board[i][j] == board[i + 1][j])
			{
				board[i][j] = board[i][j] * 2;
				board[i + 1][j] = 0;
				sum = sum + board[i][j];//�Զ�����
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
	for (int i = 3; i >= 1; i--)  //�һ�в���Ҫ���ӷ�����SIZE - 2
	{
		for (int j = 0; j <= SIZE-1; j++)
		{
			if (board[i][j] == board[i - 1][j])
			{
				board[i][j] = board[i][j] * 2;
				board[i - 1][j] = 0;
				sum = sum + board[i][j];//�Զ�����
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
		for (int j = 0; j <= SIZE-2; j++)  //����һ�в���Ҫ���ӷ�����SIZE - 2
		{
			if (board[i][j] == board[i][j+1])
			{
				board[i][j] = board[i][j] * 2;
				board[i][j+1] = 0;
				sum = sum + board[i][j];//�Զ�����
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
		for (int j = 3; j >= 1; j--)  //����һ�в���Ҫ���ӷ�
		{
			if (board[i][j] == board[i][j - 1])
			{
				board[i][j] = board[i][j] * 2;
				board[i][j - 1] = 0;
				sum = sum + board[i][j];//�Զ�����
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
	int lose = 0, isblank = 0, judgesumrl = 0, judgesumdu = 0; //�ж������Ƿ��п�λ�����������Ƿ�����ͬ���֣�������ʧ��
	for (int i = 0; i <= SIZE - 1; i++)		//�ж������Ƿ��п�λ
	{
		for (int j = 0; j <= SIZE - 1; j++)
		{
			if (board[i][j] == 0)
				isblank = 1;
		}
	}

	for (int i = 0; i <= SIZE - 2; i++)  //���һ�в���Ҫ���ӷ�����SIZE - 2,�ж����·��Ƿ�����ͬ����
	{
		for (int j = 0; j <= SIZE - 1; j++)
		{
			if (board[i][j] == board[i+1][j])
				judgesumdu = 1;
		}
	}

	for (int i = 0; i <= SIZE - 1; i++)
	{
		for (int j = 0; j <= SIZE - 2; j++)  //����һ�в���Ҫ���ӷ�����SIZE - 2,�ж����ҷ��Ƿ�����ͬ����
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