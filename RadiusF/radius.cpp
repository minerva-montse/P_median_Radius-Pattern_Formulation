//Pmedian problem radius formulation & pattern formulation
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

	//Read input parameters.
	if (Read_Parameters(argc, argv) == false)
	{
		printf("ERROR: wrong command line.\n");
		printf("The structure could be: \n");
		printf("For an instance with a given p: RadiusF.exe <data_file> -p p\n");
		printf("For an instance using p on file: RadiusF.exe <data_file>\n");
		printf("all instances: RadiusF.exe all\n");
		printf("\n");
		return 0;
	}


	// Solve for each instance the Radius formulation and Pattern Formulation
	//Size of instances and names are deffined on global.h
	if (AllInstances) //solve instances in global.h
	{
		for (size_t i = 0; i < instances; i++)
		{
			readData(argc, argv, i);

			//Solve the radius formulation with cumulative variables.
			cout << "Solve RF" << endl;
			model = "RF";
			RF();
			output_BB();

			//Solve the patter formulation.
			cout << "Solve pattern" << endl;
			model = "Patterns";
			Patterns();
			output_BB();
		}
	}
	else //solve instances given in command line
	{
		readData(argc, argv, 1);

		//Solve the radius formulation with cumulative variables.
		cout << "Solve RF" << endl;
		model = "RF";
		RF();
		output_BB();

		//Solve the patter formulation.
		cout << "Solve pattern" << endl;
		model = "Patterns";
		Patterns();
		output_BB();
	}



	return 0;

	}
