/* This file contains the global variables */

#pragma once
#define epsilon 1E-6

using namespace std;

typedef vector <vector <double> > matrixDoubles;

//Problem parameters & data
int n;
int p;
int k_radious = 3;
char file_name[50] = "";
char instance[50] = "";

//Data
matrixDoubles dist; // bi-vector of distances, all values are initialized to 0.
matrixDoubles d;
matrixDoubles D;
matrixDoubles datatsp;
vector <int> Gi;

//Cplex definition
typedef IloArray<IloNumVarArray> IloNumVarArray2;
typedef IloArray<IloBoolVarArray> IloBoolVarArray2;

IloNum optimal_value;
IloNum sol_time;
int BBnodes;
int status;
string model;
bool AllInstances;
const int instances = 2;

string file[instances] = {
	"pmed01.dat",
	"pmed02.dat",
	//"pmed03.dat",
	//"pmed04.dat",
	//"pmed05.dat",
	//"pmed06.dat",
	//"pmed07.dat",
	//"pmed08.dat",
	//"pmed09.dat",
	//"pmed10.dat",
	//"pmed11.dat",
	//"pmed12.dat",
	//"pmed13.dat",
	//"pmed14.dat",
	//"pmed15.dat",
	//"pmed16.dat",
	//"pmed17.dat",
	//"pmed18.dat",
	//"pmed19.dat",
	//"pmed20.dat",
	//"pmed21.dat",
	//"pmed22.dat",
	//"pmed23.dat",
	//"pmed24.dat",
	//"pmed25.dat",
	//"pmed26.dat",
	//"pmed27.dat",
	//"pmed28.dat",
	//"pmed29.dat",
	//"pmed30.dat",
	//"pmed31.dat",
	//"pmed32.dat",
	//"pmed33.dat",
	//"pmed34.dat",
	//"pmed35.dat",
	//"pmed36.dat",
	//"pmed37.dat",
	//"pmed38.dat",
	//"pmed39.dat",
	//"pmed40.dat"
};
