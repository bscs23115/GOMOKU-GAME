#include<iostream>
#include<iomanip>
#include<conio.h>
#define MR 100
#define MC 100
using namespace std;




bool boardfilled(char board[][MC], int dim)
{
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			if (board[r][c] == '-')
				return false;
		}
	}
	return true;
}
bool isvalidentry(char Board[][MC], int pr, int pc, int d)
{
	if (pc < 0 || pc >= d || pr < 0 || pr >= d)
		return false;
	return Board[pr][pc] == '-';
}
void init(char Board[][MC], int& d, int& nop, char sym[], int& turn, string nameofp[], int& wc,int & winners)
{
	winners = 0;
	cout << "ENTER DIMENSION : ";
	cin >> d;
	cout << "ON HOW MANY CONTIGUOS SYMBOLS PLAYER WINS : ";
	cin >> wc;
	for (int r = 0; r < d; r++)
	{
		for (int c = 0; c < d; c++)
		{
			Board[r][c] = '-';
		}
	}
	nop = 2;
	cout << "ENTER NAME OF PLAYER : ";
	cin >> nameofp[0];
	cout << "ENTER SYMBOL FOR PLAYER : ";
	cin >> sym[0];
	nameofp[1] = "COMPUTER";
	sym[1]='|';
	turn =0;
}
void displayboard(char Board[][MC], int d)
{
	system("cls");
	for (int r = 0; r < d; r++)
	{
		for (int c = 0; c < d; c++)
		{
			cout << setw(5) << Board[r][c] << " ";
		}
		cout << endl;
	}
}
void turnname(string name, char s)
{
	cout << name << "'s TURN(" << s << ") : ";
}
void selectlocation(int& pr, int& pc)
{
	cin >> pr >> pc;
	pr--, pc--;
}
void updateboard(char Board[][MC], int pc, int pr, char sym)
{
	Board[pc][pr] = sym;
}
void turnchange(int& turn, int nop)
{
	turn = (turn + 1) % nop;
}
bool iswinvertically(char board[][MC], int d, char sym, int wc, int R, int C)
{
	if (R > (d - wc))
		return false;
	for (int t = 0; t < wc; t++)
	{
		if (board[R + t][C] != sym)
			return false;
	}
	return true;
}
bool iswinhorizontally(char board[][MC], int d, char sym, int wc, int R, int C)
{
	if (C > (d - wc))
		return false;
	for (int t = 0; t < wc; t++)
	{
		if (board[R][C + t] != sym)
			return false;
	}
	return true;
}
bool iswindiagdownr(char board[][MC], int d, char sym, int wc, int R, int C)
{
	if (R > (d - wc) || C > (d - wc))
		return false;
	for (int t = 0; t < wc; t++)
	{
		if (board[R + t][C + t] != sym)
			return false;
	}
	return true;
}
bool iswindiagdownl(char board[][MC], int d, char sym, int wc, int R, int C)
{
	if (R > (d - wc) || C < (wc - 1))
		return false;
	for (int t = 0; t < wc; t++)
	{
		if (board[R + t][C - t] != sym)
			return false;
	}
	return true;
}
bool iswin(char Board[][MC], int d, char sym, int wc)
{
	for (int r = 0; r < d; r++)
	{
		for (int c = 0; c < d; c++)
		{
			if (iswinvertically(Board, d, sym, wc, r, c) || iswinhorizontally(Board, d, sym, wc, r, c) || iswindiagdownr(Board, d, sym, wc, r, c) || iswindiagdownl(Board, d, sym, wc, r, c))
				return true;
		}
	}
	return false;
}
bool iswin2(char Board[][MC], int d, char sym, int wc)///win finction with nested loop
{
	bool won = false;
	for (int r = 0; r < d; r++)
	{
		for (int c = 0; c < d; c++)
		{
			bool wv = true, wh = true, wdl = true, wdr = true;
			for (int t = 0; t < wc; t++)
			{
				if (r > (d - wc))
				{
					wv = false;
					break;
				}
				if (Board[r + t][c] != sym)
				{
					wv = false;
					break;
				}
			}
			if (wv)
			{
				won = true;
				break;
			}

			for (int t = 0; t < wc; t++)
			{
				if (c > d - wc)
				{
					wh = false;
					break;
				}
				if (Board[r][c + t] != sym)
				{
					wh = false;
					break;
				}
			}

			if (wh)
			{
				won = true;
				break;
			}

			for (int t = 0; t < wc; t++)
			{
				if (r > (d - wc) || c > (d - wc))
				{
					wdr = false;
					break;
				}

				if (Board[r + t][c + t] != sym)
				{
					wdr = false;
					break;
				}
			}

			if (wdr)
			{
				won = true;
				break;
			}


			for (int t = 0; t < wc; t++)
			{
				if (r > (d - wc) || c < (wc - 1))
				{
					wdl = false;
					break;
				}
				if (Board[r + t][c - t] != sym)
				{
					wdl = false;
					break;
				}
			}

			if (wdl)
			{
				won = true;
				break;
			}
		}
		if (won)
			break;
	}

	return won;
}
bool continued(char board[][MC], int d, int nop, int winners)
{
	if (winners >= nop - 1)
		return false;
	if (boardfilled(board, d))
		return false;


	return true;

}
void displayresult(int winnerplayer, string names[], int turn)
{

	cout << endl << "-------------------------------------------"<<endl;
	cout << "WINNER : " << names[winnerplayer] << endl;
	cout << "LOSER : " << names[turn]<<endl;
	cout << "-------------------------------------------";
}
void assignrandom(int pr, int pc, char board[][MC], int d)
{
	do
	{
		pr = rand()%d;
		pc = rand()%d;
	} while (!isvalidentry(board, pr, pc, d));
}
void makeacopy(char a[][MC], int d,char board[][MC])
{
	for (int r = 0; r < d; r++)
	{
		for (int c = 0; c < d; c++)
		{
			a[r][c] = board[r][c];
		}
	}


}
bool checkplace(char b[][MC], int d, int& pr, int& pc,int wc,char s)
{
		for (int r = 0; r < d; r++)
		{
			for (int c = 0; c < d; c++)
			{
				if (isvalidentry(b, r, c, d))
				{
					b[r][c] = s;
					if (iswin(b, d, s, wc))
					{
						pr = r;
						pc = c;
						return true;
					}
					else
						b[r][c] = '-';
				}
			}
		}
	return false;
}
bool block(char b[][MC], int d, int& pr, int& pc, int wc, char s)
{
		for (int r = 0; r < d; r++)
		{
			for (int c = 0; c < d; c++)
			{
				if (isvalidentry(b, r, c, d))
				{
					b[r][c] = s;
					if (iswin(b, d, s, wc))
					{
						pr = r;
						pc = c;
						return true;
					}
					else
						b[r][c] = '-';
				}
			}
		}
	return false;
}
void computerturn(char board[][MC], int d, char sym[],int &pr,int &pc,int wc)
{
	char copy[MC][MR] = {};
	makeacopy(copy, d, board);
	for (int n = wc; n > 1; n--)
	{
		if (checkplace(copy, d, pr, pc, n, sym[1]))
			return;
		if (block(copy, d, pr, pc, n, sym[0]))
			return;
	}
	assignrandom(pr, pc, board, d);
}



int main()
{
	char Board[MR][MC];
	int nop, d, turn, pr, pc, wc,winners,winnerplayer;
	char sym[MR];
	string nameofp[MR];
	init(Board, d, nop, sym, turn, nameofp, wc,winners);
	displayboard(Board, d);
	do
	{
		if (turn==1)
			computerturn( Board, d,sym,pr,pc,wc);
		else 
		{
			do
			{
				turnname(nameofp[turn], sym[turn]);
				selectlocation(pr, pc);
			} while (!isvalidentry(Board, pr, pc, d));
		}
		updateboard(Board, pr, pc, sym[turn]);
		displayboard(Board, d);
		if (iswin(Board, d, sym[turn], wc))
		{
			cout << nameofp[turn] << " WON!!!" << endl;
			winnerplayer = turn;
			winners++;
		}
		turnchange(turn, nop);
	} while (continued(Board, d, nop, winners));
	displayresult(winnerplayer,nameofp,turn);
	return 0;
}






