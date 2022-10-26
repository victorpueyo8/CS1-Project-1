// Victor Pueyo 
// This is my Lab 1
// I have neither given nor received unauthorized aid in completing this work, nor have I presented someone else's work as my own.

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int Process_Employee(int&, float&, int&, ifstream&);
void process_payroll(ifstream&, ofstream&);
void print_summary(float, float, float, float, float, ofstream& Output);

int main()
{

	ifstream Input;
	ofstream Output;
	
	Input.open("Lab1.txt");
	Output.open("out.txt");
	
	if (Input.fail())
	{
		cout << "Input file failed to open" << endl;
		system("pause");
		exit(1);
	}
	if (Output)
		;
	else
	{
		cout << "Output file failed to opem" << endl;
		system("pause");
		exit(1);
	}
	
	process_payroll(Input, Output);

	system("pause");
	return 0;
}

//This function reads the id, wage and the hours of each indivual from the text file.

int Process_Employee(int& id, float& wage, int& hours, ifstream& in)
{
	if (in >> id >> wage >> hours)
		return 1;
	return 0;
}

//This function calculates the gross pay, net pay, and all the taxes. Also, it prints out the heading of the table. 

void process_payroll(ifstream& Input, ofstream& Output)
{
	int hours, Id;
	float rate, grosspay, state, soc_sec, fed, net_pay;
	double tot_gross_pay = 0, tot_net_pay = 0, tot_state_tax = 0, tot_fed_tax = 0, tot_soc_sec_tax = 0;
	const float STATE_TAX = 0.0542;
	const float SOCIAL_SECURITY_TAX = 0.07;
	const float FEDERAL_TAX = 0.16;

	cout << "Employee Payroll" << endl << endl;
	cout << "Employee" << setw(10) << "Hours" << setw(10) << "Rate" << setw(10) << "Gross" << setw(11) << "Net" << setw(11)
		<< "Fed" << setw(11) << "State" << setw(12) << "Soc Sec" << endl << endl;
	Output << "Employee Payroll" << endl << endl;
	Output << "Employee" << setw(10) << "Hours" << setw(10) << "Rate" << setw(10) << "Gross" << setw(11) << "Net" << setw(11)
		<< "Fed" << setw(11) << "State" << setw(12) << "Soc Sec" << endl << endl;

	cout << setprecision(2) << fixed;
	Output << setprecision(2) << fixed;
	
	while (Process_Employee(Id, rate, hours, Input))
	{
		cout << setw(8) << Id;
		Output << setw(8) << Id;

		if (hours <= 35)
		{
			grosspay = hours * (0.15 + rate);

			cout << setw(10) << hours << "*" << setw(9) << rate;
			Output << setw(10) << hours << "*" << setw(9) << rate;
			
		}
		else if (hours > 40)
		{
			grosspay = (40 * rate) + (hours - 40) * (1.5 * rate);

			cout << setw(10) << hours << "$" << setw(9) << rate;
			Output << setw(10) << hours << "$" << setw(9) << rate;
			
		}
		else
		{
			grosspay = hours * rate;

			cout << setw(10) << hours << setw(10) << rate;
			Output << setw(10) << hours << setw(10) << rate;
		}

			// calculate all taxes
		state = grosspay * STATE_TAX;
		soc_sec = grosspay * SOCIAL_SECURITY_TAX;
		fed = grosspay * FEDERAL_TAX;

			// calculate net pay
		net_pay = grosspay - state - fed - soc_sec;

			// update totals for gros, net, and all taxes.
		tot_gross_pay += grosspay;
		tot_net_pay += net_pay;
		tot_state_tax += state;
		tot_fed_tax += fed;
		tot_soc_sec_tax += soc_sec;

		cout << setw(10) << grosspay << setw(12) << net_pay << setw(10) << fed << setw(11) << state << setw(12) << soc_sec << endl << endl;
		Output << setw(10) << grosspay << setw(12) << net_pay << setw(10) << fed << setw(11) << state << setw(12) << soc_sec << endl << endl;
	}

	print_summary(tot_gross_pay, tot_net_pay, tot_fed_tax, tot_state_tax, tot_soc_sec_tax, Output);
}

//This function prints out the totals of all the company, with the data of each employee calculated in the function above (process payrole)

void print_summary(float tot_gross_pay, float tot_net_pay, float tot_fed_tax, float tot_state_tax, float tot_soc_sec_tax, ofstream& Output)
{
	cout << "Summary - Totals for all employees " << endl << endl;
	cout << setw(14) << "Gross Pay" << setw(14) << "Net Pay" << setw(16) << "Federal Tax" << setw(15) << "State Tax" << setw(16) << "Soc Security" << endl << endl;
	Output << "Summary - Totals for all employees " << endl << endl;
	Output << setw(14) << "Gross Pay" << setw(14) << "Net Pay" << setw(16) << "Federal Tax" << setw(15) << "State Tax" << setw(16) << "Soc Security" << endl << endl;
	cout << setw(14) << tot_gross_pay << setw(14) << tot_net_pay << setw(16) << tot_fed_tax << setw(15) << tot_state_tax << setw(16) << tot_soc_sec_tax << endl << endl;
	Output << setw(14) << tot_gross_pay << setw(14) << tot_net_pay << setw(16) << tot_fed_tax << setw(15) << tot_state_tax << setw(16) << tot_soc_sec_tax << endl << endl;
}
