//Pmedian problem (clasical formulation). Problem with m=4, n=2.
#include <fstream>
#include <iostream>
#include <algorithm>
#include <ilcplex/ilocplex.h>
#include "Aux_Functions.h"
#include "Subrutines.h"
#include "global.h"
#include "models.h"


using namespace std;

ILOSTLBEGIN

typedef IloArray<IloNumArray>    NumMatrix;
typedef IloArray<IloNumVarArray> NumVarMatrix;
typedef vector <vector <int> > matrixInt;
typedef IloArray<IloBoolVarArray> NumBoolMatrix;

int main(int argc, char ** argv)
{
	//Start time BB.
	clock_t clock_initial = clock();
	double total_time = 0;

	//solution
	double Optimal_value;
	if (Read_Parameters(argc, argv) == false)
	{
		printf("ERROR: wrong command line.\n");
		printf("The structure is: lineal.exe <data_file> -p p\n");
		printf("\n");
		return 0;
	}

	
	for (size_t i = 0; i < instances; i++) // numero de instancias a hacer el experimento
	{
		//readData(argc, argv,i);
		readData2(argc, argv, i);

		cout << "Solve RF" << endl;
		model = "RF";
		RF();
		output_BB();

		//cout << "Solve pattern" << endl;
		//model = "Patterns";
		//Patterns();
		//output_BB();
	}


	return 0;

	}
