#include<iostream>
#include<algorithm>

using namespace std;

double* gaussmethod(double** arra, double* arrb, int n);
double* vectornevyazki(double** arra, double* arrb, double* X, int n);
double* vectorb(double** arra, double* x, int n);
double* raznost(double* x1, double* x2, int n);
double norma_vektora(double* F, int n);


double* gaussmethod(double** arra, double* arrb, int n)
{
	double* X = new double[n];  
	for (int k = 0; k < n; k++) 
	{
		for (int i = k + 1; i < n; i++)
		{
			if (abs(arra[i][k]) > abs(arra[k][k]))
			{
				swap(arra[i], arra[k]);  
				swap(arrb[i], arrb[k]);   
			}
		}
		double amain = arra[k][k];
		if (amain == 0)
		{
			cout << "error\n";
			system("pause");
			exit(0);
		}
		for (int i = k; i < n; i++)
		{
			arra[k][i] /= amain;
		}
		arrb[k] /= amain;
		for (int i = k + 1; i < n; i++)
		{
			double s = arra[i][k];
			for (int j = k; j < n; j++)
			{
				arra[i][j] -= s * arra[k][j];
			}
			arrb[i] -= s * arrb[k];
		}
	}
	for (int k = n - 1; k >= 0; k--)  
	{
		X[k] = arrb[k];
		for (int i = n - 1; i > k; i--)
		{
			X[k] -= arra[k][i] * X[i];
		}
	}
	return X;
}

double* vectornevyazki(double** arra, double* arrb, double* X, int n)
{
	double* result = new double[n];
	for (int i = 0; i < n; i++)
	{
		result[i] = -arrb[i];
		for (int j = 0; j < n; j++)
		{
			result[i] += arra[i][j] * X[j];
		}
	}
	return result;
}

double norma_vektora(double* F, int n)
{
	double normaVektora = abs(F[0]);
	for (int i = 0; i < n; i++)
	{
		normaVektora = max(F[i], normaVektora);
	}
	return normaVektora;
}

double* vectorb(double** arra, double* X, int n)
{
	double* b = new double[n];
	for (int i = 0; i < n; i++)
	{
		b[i] = 0;
		for (int j = 0; j < n; j++)
		{
			b[i] += arra[i][j] * X[j];
		}
	}
	return b;
}

double* raznost(double* X1, double* X2, int n)
{
	double* x = new double[n];
	for (int i = 0; i < n; i++)
	{
		x[i] = X2[i] - X1[i];
	}
	return x;
}

int main()
{
	setlocale(LC_ALL, "RUS");
	int n;
	cout << "vvedite poryadok matrici: ";
	do
	{
		cin >> n;
	} while (n < 0);
	double** arra = new double* [n];
	double* arrb = new double[n];
	double** copya = new double* [n];
	double* copyb = new double[n];
	cout << "\nVvedide matricu: \n";
	for (int i = 0; i < n; i++)
	{
		arra[i] = new double[n];
		copya[i] = new double[n];
		for (int j = 0; j < n; j++)
		{
			cout << "a[" << i + 1 << "][" << j + 1 << "]: ";
			cin >> arra[i][j];
			copya[i][j] = arra[i][j];
		}
	}
	cout << "\nvvedite svobodnie chleni: \n";
	for (int i = 0; i < n; i++)
	{
		cin >> arrb[i];
		copyb[i] = arrb[i];
	}
	double* X = gaussmethod(arra, arrb, n);
	cout << "\nReshenie SLAU: " <<endl;
	for (int i = 0; i < n; i++)
	{
		cout << X[i] << " ";
	}
	cout << endl;
	double* F = vectornevyazki(copya, copyb, X, n);
	cout << "\nVektor nevyazki F: " <<endl;
	for (int i = 0; i < n; i++)
	{
		cout << F[i] << " ";
	}
	cout << endl;
	cout << "Norma vectora nevyazki F: " <<endl;
	double normaVektora = norma_vektora(F, n);
	cout << normaVektora;
	double* b = vectorb(copya, X, n);
	double* X2 = gaussmethod(copya, b, n);
	cout << "\nReshenie vspomagatelnoi sistemi : " <<endl;
	for (int i = 0; i < n; i++)
	{
		cout << X2[i] << " ";
	}
	cout << endl;
	cout << "Otnositelnaya pogreshnost: " << norma_vektora(raznost(X, X2, n), n) / norma_vektora(X, n) <<endl;
	cout << endl;
	system("pause");
	return 0;
}

