#pragma once
#include <vector>
#include <cstdio>
#include <chrono>
#include "global.h"

using namespace std;

bool Read_Parameters(int argc, char *argv[])
{
	int data_format = 0;
	int p = 0;
	if (argc < 2) return false;
	

	char *file_name;
	file_name = argv[1];

	char *str2 = "all";
	if (strcmp(file_name, str2) == 0)
	{
		cout << "Doing all instances." << endl;
		AllInstances = true;
	}
	else
	{
		cout << "Instance " << file_name << endl;
		AllInstances = false;
	}

	//Check file extension
	if (strlen(file_name) >= 4)
	{
		printf("The file is:%s\n", file_name);
		if (strcmp(&file_name[strlen(file_name) - 4], ".dat") == 0)
		{
			data_format = 3;
		}
		else
		{
			printf("ERROR: data extension not recognized.\n");
			printf("Valid extensions: .dat\n");
			return false;
		}
	}

	int arg = 2;
	//bool no_p = true;
	while (arg < argc)
	{
		if (strcmp(arg[argv], "-p") == 0)
		{
			++arg;
			if (arg == argc) return false;
			p = atoi(argv[arg]);
			if (p <= 0)
			{
				printf("ERROR: p must be strictly positive.\n");
				return false;
			}
			//no_p = false;
			++arg;
			continue;
		}
	cout << "p= " << p << endl;
		return false;
	}

	return true;
}

char *Get_y_Name(int i)
{
	static  char aux[10];
	sprintf_s(aux, "y(%d)", i);
	return aux;
}

char *Get_z_Name(int i, int k)
{
	static char aux[20];
	sprintf_s(aux, "z(%d,%d)", i, k);
	return aux;
}

char *Get_s_Name(int i, int k)
{
	static char aux[20];
	sprintf_s(aux, "s(%d,%d)", i, k);
	return aux;
}


void output_BB()
{
	char file_check_name[50] = "Results/RF.csv";
	ifstream check_file(file_check_name);
	bool file_exist = false;

	if (check_file.is_open())
	{
		cout << "File exists: " << file_check_name << endl;

		check_file.close();
		file_exist = true;
	}
	else file_exist = false;


	auto end = std::chrono::system_clock::now();
	time_t end_time = std::chrono::system_clock::to_time_t(end);

	ofstream outfile;
	outfile.open("Results/RF.csv", std::fstream::app);

	//header of file
	if (!file_exist)
	{
		outfile << "Model," << char(9);
		outfile << "Instance," << char(9);
		outfile << "n," << char(9);
		outfile << "p," << char(9);
		outfile << "Objective," << char(9);
		outfile << "Time," << char(9);
		outfile << "Nodes," << char(9);
		outfile << "Status," << char(9);
		outfile << "Current time," << endl;
	}

	//Results;
	outfile << model << char(9);
	outfile << "," << file_name << char(9);
	outfile << "," << n << char(9);
	outfile << "," << p << char(9);
	outfile << "," << optimal_value << char(9);
	outfile << "," << sol_time << char(9);
	outfile << "," << BBnodes << char(9);
	outfile << "," << status << char(9);
	outfile << "," << ctime(&end_time);

	//Close the file.
	outfile.close();
}