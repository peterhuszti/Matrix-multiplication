#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>

#include "sparse_matrix.h"
#include "linalg.h"

#define fileName "saylr3.mtx"

using namespace std;

int main()
{
	int N;
	cout << "****Reading dense matrix from file!****\n";

	ifstream inD(fileName);
	inD >> N;
	
	vector<vector<double> > dense;
	dense.resize(N);
	for(int i=0;i<N;i++)
		dense[i].resize(N);
	
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			dense[i][j]=0;

	while(!inD.eof())
	{
		int i,j;
		inD >> i >> j;
		double temp;
		inD >> temp;
		if(temp) dense[i-1][j-1]=temp;
	}
	inD.close();
	
	cout << "\nFinished reading!\n";
	
	cout << "\n****Calculating matrix multiplication with dense matrix****\n          ****Normal algorithm****\n\n";

	clock_t tD;
	double secD;
	tD=clock();
	
	vector<vector<double> > denseResult=dense*dense;
	
	tD=clock()-tD;
    secD=((float)tD)/CLOCKS_PER_SEC;
	cout << "\a" << "Finished the calculation!\nTime spent: " << secD << " seconds\n\n\n" ;
	
	cout << "\n****Calculating matrix multiplication with dense matrix****\n          ****Block algorithm****\n\n";

	clock_t tDB;
	double secDB;
	tDB=clock();
	
	vector<vector<double> > denseResultBlock=blockMatMul(dense,dense);
	
	tDB=clock()-tDB;
    secDB=((float)tDB)/CLOCKS_PER_SEC;
	cout << "\a" << "Finished the calculation!\nTime spent: " << secDB << " seconds\n\n\n" ;
//
	cout << "****Reading sparse matrix from file!****\n";
	
	ifstream inS(fileName);
	inS >> N;
	
	sparse_matrix sparse(N);

	while(!inS.eof())
	{
		int i,j;
		inS >> i >> j;
		double temp;
		inS >> temp;
		if(temp) sparse.befuz(new node(i,j,temp));
	}
	inS.close();

	cout << "\nFinished reading!\n";

	cout << "\n****Calculating matrix multiplication with sparse matrix****\n\n";

	clock_t tS;
	double secS;
	tS=clock();
	
	sparse_matrix sparseResult=sparse*sparse;
	
	tS=clock()-tS;
    secS=((float)tS)/CLOCKS_PER_SEC;
	cout << "\a" << "Finished the calculation!\nTime spent: " << secS << " seconds\n\n\n" ;
	
	cout << "\n****Checking the results****\n";
	if(equals(sparseResult,toSpare(denseResult)) && equals(denseResult,denseResultBlock)) cout << "The multiplication was CORRECT!\n";
	else cout << "The multiplication was INCORRECT\n";	
	return 0;
}









