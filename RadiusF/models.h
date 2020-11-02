#pragma once

void RF()
{
	cout << "RF model" << endl;
	//Solve the problem using the Radius Formulation. Formulation on Sergio's Paper

	IloEnv env;
	IloModel model(env);
	IloCplex cplex(model);


	try
	{
		cout << "initial" << endl;
		//(1) Variables
		//Location Variable.
		IloBoolVarArray y(env, n); // 1-dimension array
		IloNumVarArray2 z(env, n); // 1-dimension array 
		//IloNumVarArray y(env, n); // 1-dimension array

		//Give the names to the variables.
		for (int i = 0; i < n; i++)
		{
			y[i] = IloBoolVar(env, Get_y_Name(i));
			//y[i] = IloNumVar(env, 0, 1, ILOFLOAT, Get_y_Name(i));

			z[i] = IloNumVarArray(env, Gi[i] - 1); //Becuse index k on z[i][k] stats at 2.

			for (int k = 0; k < (Gi[i] - 1); k++)
				z[i][k] = IloNumVar(env, 0, IloInfinity, ILOFLOAT, Get_z_Name(i, k));
		}
		
		//(2) Objective Function
		IloExpr obj(env);
		
		for (size_t i = 0; i < n; i++)
		{
			for (size_t k = 1; k < Gi[i]; k++) //the sum starts at t=2, but we have index 0.
			{
				obj += (D[i][k] - D[i][k - 1])*z[i][k - 1];
			}
		}

		model.add(IloMinimize(env, obj));
		cout << "OF added" << endl;
		//(3) Constraints
		//(3.1) Locate P clusters
		IloExpr cons1(env);
		for (size_t i = 0; i < n; i++)
			cons1 += y[i];

		model.add(cons1 == p);
		cons1.clear();
		cout << "sum y=p added" << endl;
		//(3.2) Radius Constraint
		IloExpr cons2(env);
		for (size_t i = 0; i < n; i++)
		{
			for (size_t k = 1; k < Gi[i]; k++)
			{
				for (size_t j = 0; j < n; j++)
					if (d[i][j] < (D[i][k] - epsilon))
						cons2 += y[j];

				model.add(z[i][k - 1] + cons2 >= 1);
				cons2.clear();
			}
		}
		cout << "Radius constraint added" << endl;

		//(4) Solve model.
		cplex.setParam(IloCplex::ClockType, 1); // CPU time
		cplex.setParam(IloCplex::TiLim, 7200); // Time limit
		cplex.setParam(IloCplex::Threads, 1); // Number of threads

		//cplex.exportModel("model_RF.lp");
		if (!cplex.solve()) {
			env.error() << "Failed to optimize LP." << endl;
			throw(-1);
		}

		//(5) Solution.
		optimal_value = cplex.getObjValue();
		cout << "Optimal= " << optimal_value << endl;

		sol_time = cplex.getTime();
		cout << "Time= " << sol_time << endl;

		BBnodes = cplex.getNnodes();
		status = cplex.getCplexStatus();

		env.end();
	}
	catch (IloException& ex) {
		cerr << "Concert exception caught: " << ex << endl;
		ex.~IloException();

		env.end();
	}
	catch (...) {
		cerr << "Unknown exception caught" << endl;
		env.end();
	}
}

void Patterns()
{
	cout << "Patterns model" << endl;
	//Solve the problem using the Radius Formulation with patterns variables.

	IloEnv env;
	IloModel model(env);
	IloCplex cplex(model);

	try
	{

		//(1) Variables
		//Location Variable.
		IloBoolVarArray y(env, n); // 1-dimension array
		//IloNumVarArray y(env, n); // 1-dimension array 
		//IloBoolVarArray2 s(env, n); // 2-dimension array
		IloNumVarArray2 s(env, n); // 2-dimension array 


		//Give the names to the variables.
		for (int i = 0; i < n; i++)
		{
			y[i] = IloBoolVar(env, Get_y_Name(i));
			//y[i] = IloNumVar(env, 0, 1, ILOFLOAT, Get_y_Name(i));

			s[i] = IloNumVarArray(env, Gi[i]); //Becuse index k on z[i][k] stats at 2.
			//s[i] = IloBoolVarArray(env, Gi[i]); //Becuse index k on z[i][k] stats at 2.

			for (int k = 0; k < Gi[i]; k++)
			{
				s[i][k] = IloNumVar(env, 0, IloInfinity, ILOFLOAT, Get_s_Name(i, k));
				//s[i][k] = IloBoolVar(env, Get_s_Name(i, k));
			}
				
		}

		//(2) Objective Function
		IloExpr obj(env);
		
		for (size_t i = 0; i < n; i++)
		{
			for (size_t k = 0; k < Gi[i]; k++) //the sum starts at t=2, but we have index 0.
			{
				obj += D[i][k]*s[i][k];
			}
		}

		model.add(IloMinimize(env, obj));

		//(3) Constraints
		//(3.1) Locate P clusters
		IloExpr cons1(env);
		for (size_t i = 0; i < n; i++)
			cons1 += y[i];

		model.add(cons1 == p);
		cons1.clear();

		//(3.2) Choose one pattern.
		IloExpr cons3(env);
		for (size_t i = 0; i < n; i++)
		{
			for (size_t k = 0; k < Gi[i]; k++)
				cons3 += s[i][k];

				model.add(cons3 == 1);
				cons3.clear();
		}


		//(3.5) Radius Constraint
		IloExpr cons2(env);
		for (size_t i = 0; i < n; i++)
		{
			for (size_t k = 0; k < Gi[i]-1; k++)
			{
				for (size_t j = 0; j < n; j++)
					if (abs(d[i][j] - D[i][k]) < epsilon)
						cons2 += y[j];

				model.add(s[i][k] <= cons2);
				cons2.clear();
			}
		}

		//(4) Solve model.
		cplex.setParam(IloCplex::ClockType, 1); // CPU time
		cplex.setParam(IloCplex::TiLim, 7200); // Time limit
		cplex.setParam(IloCplex::Threads, 1); // Number of threads

		//cplex.exportModel("model_patterns.lp");
		if (!cplex.solve()) {
			env.error() << "Failed to optimize LP." << endl;
			throw(-1);
		}

		//(5) Solution.
		optimal_value = cplex.getObjValue();
		cout << "Optimal= " << optimal_value << endl;

		sol_time = cplex.getTime();
		cout << "Time= " << sol_time << endl;

		BBnodes = cplex.getNnodes();
		status = cplex.getCplexStatus();

		//Values variable y.
		IloNumArray yval(env, n);
		cplex.getValues(y, yval);

		//Values variable x.
		IloNumArray2 sval(env, n);
		for (size_t i = 0; i < n; i++)
		{
			sval[i] = IloNumArray(env, n);
			cplex.getValues(s[i], sval[i]);
		}

		env.end();
	}
	catch (IloException& ex) {
		cerr << "Concert exception caught: " << ex << endl;
		ex.~IloException();

		env.end();
	}
	catch (...) {
		cerr << "Unknown exception caught" << endl;
		env.end();
	}
}