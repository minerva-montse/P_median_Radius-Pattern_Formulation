#pragma once
#include "global.h"

void readData(int argc, char ** argv, int ins)
{	
	//string trash_char;
	if (argc == 4)
	{
		strcat_s(file_name, "data/");
		strcat_s(file_name, argv[1]);
		printf("The file is:%s\n", file_name);
	}

	if (argc == 2)
	{
		file_name[0] = '\0';

		char file_trash[50];
		strcpy(file_trash, file[ins].c_str());

		//cout << "file_name: " << file_name << endl;
		//cout << "file_trash: " << file_trash << endl;

		strcat_s(file_name, "data/");
		strcat_s(file_name, file_trash);
		printf("The file is:%s\n", file_name);

		//cout << "file_name: " << file_name << endl;

	}

	//We need to indicate the file to start.
	//Define the name/location of the file acording to the input parameter.
	//strcat_s(file_name, "data/");
	//strcat(file_name, argv[1]);
	//printf("The file is:%s\n", file_name);
	//strcat(instance, argv[1]);

	//Create an input file stream
	ifstream in(file_name, ios::in);
	int number;  //Variable to hold each number as it is read
	in >> number;
	n = number;// size of the problem, number of costumers
	in >> number;
	p = number; // facilite to locate using the value in the file
	//const int p = atoi(argv[3]);// facilite to locate using the value in the input parameters


	printf("The value of n: %d\n", n);
	printf("The value of p: %d\n", p);
	
	d.empty();
	D.empty();
	Gi.empty();
	d.clear();
	D.clear();
	Gi.clear();

	//Read number using the extraction (>>) operator, using the triangular form of the data.
	d.resize(n, vector <double>(n));
	for (int i = 0; i < n; i++)
	{
		if (i != n- 1)
		{
			for (int j = i + 1; j <= (n - 1); j++)
			{
				in >> number;
				d[i][j] = number;
				d[j][i] = number;
			}
			d[i][i] = 0;
		}
		else
		{
			d[i][i] = 0;
		}
	}
	
	//Close the file stream
	in.close();
	
	cout << "n= " << n << endl;
	/*Loop to sort and eliminate repetead distances.*/
	Gi.resize(n);
	
	for (int i = 0; i < n; i++)
	{
		vector<double> dist_temp;
		vector<double> temp(d[i]);

		sort(temp.begin(), temp.end()); //Sort the distances in ascending order.
		temp.erase(unique(temp.begin(), temp.end()), temp.end()); // Eliminates repetead distances
		Gi[i] = temp.size();
		D.push_back(temp);
	}
	
}

void readData2(int argc, char ** argv, int ins)
{
	//We need to indicate the file to start.
	//Define the name/location of the file acording to the input parameter.
	//strcat_s(file_name, "data/fl1400.txt");

	string trash_char;
	if (argc == 4)
	{
		strcat_s(file_name, "data/");
		strcat_s(file_name, argv[1]);
		printf("The file is:%s\n", file_name);
	}

	cout << "file= " << file_name << endl;
	//Create an input file stream
	ifstream in(file_name, ios::in);
	double number;  //Variable to hold each number as it is read
	
	in >> number;
	n = (int) number;// size of the problem, number of costumers
	in >> number;
	p = (int) number; // facilite to locate using the value in the file
	//const int p = atoi(argv[3]);// facilite to locate using the value in the input parameters

	printf("The value of n: %d\n", n);
	printf("The value of p: %d\n", p);

	datatsp.resize(n, vector <double>(2));
	
	for (int i = 0; i < n; i++)
	{
			in >> number;
			in >> number;
			datatsp[i][0] = number;			
			in >> number;
			datatsp[i][1] = number;
	}

	d.empty();
	D.empty();
	Gi.empty();
	d.clear();
	D.clear();
	Gi.clear();

	//Read number using the extraction (>>) operator, using the triangular form of the data.
	d.resize(n, vector <double>(n));

	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			double a = datatsp[i][0] - datatsp[j][0];
			double b = datatsp[i][1] - datatsp[j][1];
			a *= a;
			b *= b;
			int c = (int)sqrt(a + b);
			d[i][j] = c;
		}
	}

	//Close the file stream
	in.close();
		
	/*Loop to sort and eliminate repetead distances.*/
	Gi.resize(n);

	for (int i = 0; i < n; i++)
	{
		vector<double> dist_temp;
		vector<double> temp(d[i]);

		sort(temp.begin(), temp.end()); //Sort the distances in ascending order.
		temp.erase(unique(temp.begin(), temp.end()), temp.end()); // Eliminates repetead distances
		Gi[i] = temp.size();
		D.push_back(temp);
	}
}

