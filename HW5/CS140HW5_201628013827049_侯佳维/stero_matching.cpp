#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

#define INT_MAX 0x7fffffff
#define INT_MIN 0x80000000
#define MAXD 25

int m, n;

int min(int a, int b, int c, int &f)
{
	int m;
	if (a <= b) { m = a; f = 1; }
	else { m = b; f = -1; }
	if (c<m) { m = c; f = 0; }
	return m;
}
int *L, *R;
int *dist;
void unary_cost(int *L,int *R, int max, int *dist)
{
	/**********************************	PROBLEM 1 : dist = unary_cost(L,R,MAXD)	******************************/
	cout  << endl << "test for Problem 1 : dist = unary_cost(L,R,MAXD) " << endl;
	cout << " output the dist  of L pixel (1,25) and corresponding R pixels:" << endl << " L[1,25]=119 R[1,1:25]=117 117 116 119 122 121 117 113 113 113 115 116 116 116 115 109 114 120 105 119 98 105 106 116 124" << endl;
	cout << "output the dist[1,1:25,:] :" << endl;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int d = 0; d < max; d++)
			{
				//dist(i,j,d) = (L(i,j) ¨C R(i,j-d))^2.
				if (j - d < 0)
				{
					dist[i*n*max + j*max + d] = INT_MAX;
				}
				else
				{
					dist[i*n*max + j*max + d] = pow(L[i*n + j] - R[i*n + j - d], 2);
				}
				//test: output the dist[d] of L pixel (1,25) and corresponding R pixels:
				//	L=119 R=117 117 116 119 122 121 117 113 113 113 115 116 116 116 115 109 114 120 105 119 98 105 106 116 124,
				//output the dist[1,1:25,:] :25 9 169 196 441 0 196 1 25 100 16 9 9 9 16 36 36 36 4 4 9 0 9 4 4	correct!
				if (i == 0 && j == 24)	cout << dist[i*n*max + j*max + d] << " ";
			}
		}
	}

}
void potts_cost(int *L, int K, int *P)
{
	/**********************************	PROBLEM 2 : P = potts_cost(L,K)	******************************/
	cout <<endl<< endl << "test for Problem 2 : P = potts_cost(L,K)" << endl;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{

			if (i == 1 && j == 2) 
			{
				cout << "L[1,2] and its neighbors  " << L[i*n + j] << " " << L[(i + 1)*n + j] << " " << L[(i - 1)*n + j] << " " << L[i*n + j - 1] << " " << L[i*n + j + 1] << endl;
				cout << "output L[1,2] 's pott_cost to its neighbors: " << endl;
			}
			for (int c = 0; c < 4; c++)
			{
				switch (c)
				{
				case 0://compare with its bottom neighbor
					if (i < m - 1)
					{
						P[i*n * 4 + j * 4 + c] = abs(L[i*n + j] - L[(i + 1)*n + j]);
						if (P[i*n * 4 + j * 4 + c] <= 5)	P[i*n * 4 + j * 4 + c] = 2 * K;
						else P[i*n * 4 + j * 4 + c] = K;
					}
					else
						P[i*n * 4 + j * 4 + c] = INT_MAX;
					break;
				case 1://compare with its top neighbor
					if (i >0)
					{
						P[i*n * 4 + j * 4 + c] = abs(L[i*n + j] - L[(i - 1)*n + j]);
						if (P[i*n * 4 + j * 4 + c] <= 5)	P[i*n * 4 + j * 4 + c] = 2 * K;
						else P[i*n * 4 + j * 4 + c] = K;
					}
					else
						P[i*n * 4 + j * 4 + c] = INT_MAX;
					break;
				case 2://compare with its left neighbor
					if (j >0)
					{
						P[i*n * 4 + j * 4 + c] = abs(L[i*n + j] - L[i*n + j - 1]);
						if (P[i*n * 4 + j * 4 + c] <= 5)	P[i*n * 4 + j * 4 + c] = 2 * K;
						else P[i*n * 4 + j * 4 + c] = K;
					}
					else
						P[i*n * 4 + j * 4 + c] = INT_MAX;
					break;
				case 3://compare with its bottom neighbor
					if (j <n - 1)
					{
						P[i*n * 4 + j * 4 + c] = abs(L[i*n + j] - L[i*n + j + 1]);
						if (P[i*n * 4 + j * 4 + c] <= 5)	P[i*n * 4 + j * 4 + c] = 2 * K;
						else P[i*n * 4 + j * 4 + c] = K;
					}
					else
						P[i*n * 4 + j * 4 + c] = INT_MAX;
					break;
				default:
					P[i*n * 4 + j * 4 + c] = INT_MAX;
					break;
				}
				if (i == 1 && j == 2)
				{
					//test: output L[1,2] 's pott_cost to its neighbors: 6 6 4 7; L[1,2] and its neighbors: 67 61 61 63 60
					cout << P[i*n * 4 + j * 4 + c] << " ";
				}
			}
		}
	}
}
void initialize(int *dist, int*D)
{
	/**********************************	PROBLEM 3 : D = initialize(dist)	******************************/
	cout<<endl <<endl<< "test for Problem 3  D = initialize(dist): output to D.txt" << endl;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int min_d = INT_MAX;
			for (int d = 0; d < MAXD; d++)
			{
				if (dist[i*n*MAXD + j*MAXD + d] < min_d)
				{
					min_d = dist[i*n*MAXD + j*MAXD + d];
				}
			}
			D[i*n + j] = min_d;
		}
	}

}
int main()
{
	fstream f1, f2, fout,fD;
	f1.open("L.txt", ios::in);
	f2.open("R.txt", ios::in);
	fD.open("D.txt", ios::app | ios::out);
	fout.open("out.txt", ios::app | ios::out);
	if (!f1.is_open()) { cout << "no left file open!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl; return -1; }
	if (!f2.is_open()) { cout << "no Right file open!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl; return -1; }
	if (!fD.is_open()) { cout << "no D file open!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl; return -1; }
	if (!fout.is_open()) { cout << "no out file open!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl; return -1; }

	f1 >> m;
	f1 >> n;
	f2 >> m;
	f2 >> n;
	cout << "m=" << m << " n=" << n << endl;

	L = new int[m*n];//mÐÐnÁÐ
	R = new int[m*n];
	int *visited = new int[m*n];
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			f1 >> L[i*n + j];
			f2 >> R[i*n + j];
			visited[i*n + j] = 0;
		}
	}
	f1.close();
	f2.close();

	//P1
	dist = new int[m*n*MAXD];
	unary_cost(L, R, MAXD, dist);

	//P2
	int *P = new int[m*n*4];
	int K = 20;
	potts_cost(L, K, P);

	//P3
	int *D;
	D = new int[m*n];
	initialize(dist, D);
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			fD << D[i*n + j] << " ";
		}
		fD << endl;
	}

	//P4


	delete[]L;
	delete[]R;
	delete[]visited;
	delete[]dist;
	delete[]P;
	delete[]D;
	fout.close();
	fD.close();
	system("pause");
	return 0;
}