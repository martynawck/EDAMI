
// Created on 25-05-2016 by Michael nickson

#include<iostream>
#include<conio.h>
using namespace std;
int main()
{
	double Xmax= 0.0;
	double Xmin= 0.0;
	double Xi= 8;
	double answer;
	cout << "Enter the max value:!" << endl;
	cin >> Xmax;
	cout << "Enter the min value:" << endl;
	cin >> Xmin;
	cout << "Enter the value of the point i normalized between 0 and 1:" << endl;
	
	cin >> Xi;
	answer=(Xi-Xmin)/(Xmax-Xmin);
	
	cout << "Normalized value is" << answer << endl;
	system("PAUSE");
	return 0;
}
