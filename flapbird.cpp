#include <iostream>
#include <math.h>  
#include <windows.h>
#include <conio.h>
#include <string>
#include <vector>
#include <time.h>
#include <stack>
#include <fstream>
using namespace std;
//fstream Data("C:\\HighScore.txt");
int aftert=0,bt=13;
int score=0, highscore=0;
bool die=0;
string Merge[21];
void got(int x, int y)
{
    COORD coordinate;
    coordinate.X=x;
    coordinate.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coordinate);
}
void Color(short a)
{
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,a);
}
struct bird
{
    char p='@';
    int x=8,y=9;
    short j;
    pair<int, int> bpos;
    string clear="  ";
    void Reset()
    {
		Color(15);
		for(int k=0; k<21; k++)
		Merge[k]="                                                                               ";
		for(int i=2; i<=22; i++)
		{
			got(3,i);
			cout<<"                                                                               ";
		}
    	x=8;y=9;
		j=score=0;
		//Data>>highscore;
		die=false;
		got(8,25); cout<<"0      ";
	}
} chim;
struct Waterpipe
{
	int t;
	bool in, used;
	int cnt;
	void create()
	{ 
		srand(time(NULL));
		aftert=rand()%3;
		used=false;
		bt=t;
		cnt=0;
		if(rand()%2==0) aftert=-aftert;
	}
};
stack<Waterpipe> LastPipe;
void Background()
{
    for(int k=1; k<=2; k++)
    {
        got(0,k-1);
        cout<<"000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
        got(0,k+22);
        cout<<"000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    }
	for(int i=2; i<=22; i++)
	{
		got(0,i);
		cout<<"000";
		got(81,i); 
		cout<<"000";
	}
	got(0,25);
	cout<<"Score: ";
	got(0,26);
	cout<<"Highscore: ";
}
void GameOver()
{
	Color(4);
	got(36,12);
	cout<<"GAME OVER";
	//Data<<highscore;
}
void Print()
{
	for(int i=0; i<=20; i++)
		for(int j=0; j<=76; j++)
			Merge[i][j]=Merge[i][j+1];
	if(Merge[chim.y][chim.x]==' ')
	Merge[chim.bpos.second][chim.bpos.first-1]=' ';
	else
	{
		die=1;
		return;
	}
	if(!LastPipe.empty()) 
	{
		if(!LastPipe.top().used)
		{
			LastPipe.top().used=true;
			int t= LastPipe.top().t; cout<<t;
			Merge[21-t][76]=Merge[21-t-6][76]='0';
		}
		else 
			if( LastPipe.top().cnt<=3)
				for(int i=0; i<=20; i++)
					{
						if(i==21-LastPipe.top().t-5) i+=5;
						Merge[i][76]='0';
					}
			else
			{
				int t= LastPipe.top().t;
				LastPipe.pop();
				Merge[21-t][76]='0';
				Merge[21-t-6][76]='0';
			}	
		if(!LastPipe.empty()) LastPipe.top().cnt++;
	}
	else 
		for(int i=0; i<=20; i++)
		Merge[i][76]=' ';
	Merge[chim.y][chim.x]=chim.p;
	for (int i=chim.y; i>=0; i--)
		if(Merge[i][chim.x]=='0')
		if(Merge[i][chim.x+1]=='0') break;
		else 
			{
				score++;
				if(score>highscore) highscore=score;
				got(8,25); cout<<score;
				got(11,26); cout<<highscore;
				break;
			}
	for(int i=0; i<21; i++)
	{
		got(3,i+2);
		cout<<Merge[i];
	}
}
void Play()
{
	int cnt=0;
	while(1)
    {
        Sleep(70);
        cnt++;
        if(cnt>=15)
        {
        	cnt=0;
			Waterpipe tmp;
			tmp.t=bt+aftert;
			tmp.create();
			LastPipe.push(tmp);
		}
        if(kbhit())
        {
            char a=getch();
            if(a==char(32) )     chim.j=4-(4-chim.y)*(chim.y<4);
        }
        chim.bpos={chim.x, chim.y};
        if(chim.j) 
        {
            chim.j--;
            if(chim.y>=0) chim.y--;
        }
        else chim.y++;
        if(chim.y>=20) die=true;
		else Print();
		if(die==true)
        {
        	GameOver();
        	got(30,13);
        	break;
		}
    }
	return;
}
int main()
{
    Background();
	got(8,25); cout<<score;
//	Data>>highscore;
	got(11,26); cout<<highscore;
    while(1)
    {
    	chim.Reset();
    	Play();
    	system("pause");
	}
}
