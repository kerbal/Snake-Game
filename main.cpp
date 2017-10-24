#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

using namespace std;

short a[31][31], n = 30, dir = 1, u, v,length=2;
int score;
struct node
{
	int x, y;
	node *pNext;
	node *pBack;
};

node *head = new node();
node *tail = new node();

void init()
{

	srand(time(NULL));
	do
	{
		head->x = rand() % 29 + 2;
		head->y = rand() % 29 + 2;
	} while (head->x>=n||head->y>=n||head->x<=1||head->y<=1);
	head->pBack = NULL;
	tail->x = head->x;
	tail->y = head->y;
	tail->pNext = NULL;
	tail->pBack = head;
	head->pNext = tail;

	for (int i(1); i <= n; i++) a[i][1] = a[i][n] = 1;
	for (int i(1); i <= n; i++) a[1][i] = a[n][i] = 2;
	a[1][1] = a[1][n] = a[n][1] = a[n][n] = 3;
	a[head->x][head->y] = 5;
}

char pixel(int n)
{
	switch (n)
	{
	case 0: return ' ';
	case 1: return '|';
	case 2: return '-';
	case 3: return '+';
	case 5: return '0';
	case 10: return 'x';
	}
}


void drawSnake(node *p)
{
	while (p != NULL)
	{
		a[p->x][p->y] = 5;
		p = p->pNext;
	}
}

void eraseSnake(node *p)
{
	while (p != NULL)
	{
		a[p->x][p->y] = 0;
		p = p->pNext;
	}
}

void display()
{
	system("cls");
	drawSnake(head);
	cout << score << endl;
	for (int i(1); i <= n; i++)
	{
		for (int j(1); j <= n; j++) cout << pixel(a[i][j]);
		cout << endl;
	}
	eraseSnake(head);
}

void newNode()
{
	node *p = new node();
	tail->pNext = p;
	p->pBack = tail;
	p->pNext = NULL;
	p->x = tail->x;
	p->y = tail->y;
	tail = p;
}

void newFood()
{
	if (a[u][v] == 10) return;
	newNode();
	score++;
	do
	{
		srand(time(NULL));
		u = rand() % 28 + 3;
		v = rand() % 28 + 3;
	} while (u >= n || u <= 2 || v >= n || v <= 2);//||abs(x-u)<=5||abs(y-v)<=5);
	a[u][v] = 10;
}

void input()
{
	if (_kbhit())
	{
		int c = _getch();
		switch (c)
		{
		case 13: 
		{
			cout << "QUITTING...";
			Sleep(1000);
			exit(EXIT_SUCCESS);
		}
		case 80: if (dir != 1) dir = 3; break;
		case 77: if (dir != 4) dir = 2; break;
		case 72: if (dir != 3) dir = 1; break;
		case 75: if (dir != 2) dir = 4; break;
		}
	}
}

void change()
{
	int x = head->x;
	int y = head->y;
	if (dir == 1) head->x--;
	if (dir == 2) head->y++;
	if (dir == 3) head->x++;
	if (dir == 4) head->y--;
	node *p = tail;
	//if (length == 2) return;
	(head->pNext)->pBack = p;
	tail = tail->pBack;
	tail->pNext = NULL;
	p->pBack = head;
	p->pNext = head->pNext;
	head->pNext = p;
	p->x = x;
	p->y = y;
}

int state()
{
	if (head->x >= n || head->y >= n || head->x <= 1 || head->y <= 1) return -1;
	return 1;
}

void sleep(int time)
{
	for (int i(1); i <= time; i++)
	{
		Sleep(1);
		input();
	}
}

void hello()
{
	cout << "Using up/down/left/right arrow to play" << endl << "Press Enter to Quit"<<endl;
	system("pause");
	Sleep(1000);
}

int main()
{
	hello();
	init();
	display();
	system("pause");
	while (1)
	{
		newFood();
		display();
		input();
		change();
		if (state() == -1)
		{
			cout << "GAME OVER"<<endl;
			Sleep(1000);
			break;
		}
		sleep(80);
	}
	system("Pause");
	return 0;
}
