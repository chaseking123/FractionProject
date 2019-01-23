/*
    A program to sort a list of fractions (or integers) in ascending order, as well as calculate the sum, difference, product, and quotient of the entire list.

    To run: 
    1. run makefile "make" while in the same folder as FractionProgram.cpp, Fraction.cpp, and Fraction.h to create FractionProgram.out if it isn't already in folder or needs to be re-compiled
    2. then run "./FractionProgram.out nameOfFile.txt" where nameOfFile.txt is the name of the file within the folder of fractions to be used (I have provided a few small test.txt inputs)

    Program takes a file of numbers/fractions in the following forms separated by spaces or newline:
    1, 1.1, 1_1/2, 1/2

    The console output is in the following form:
    The sum of the sorted fractions is: 32_5791/10710
    The difference of the fractions is: -52_5791/10710
    The product of the fractions is: -7228_51812/83521
    The quotient of the fractions is: -83521/6037416
    -10_0/1
    7/17
    9/17
    9/17
    1_3/17
    1_2/9
    2_4/7
    10_0/1
    12_1/10
    14_0/1
*/

#include <string>       
#include <sstream>      
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <math.h>
#include <vector>
#include <time.h>
#include <algorithm>

using namespace std;

#include "Fraction.h"

Fraction getSum(const vector<Fraction>&);
Fraction getDifference(const vector<Fraction>&);
Fraction getProduct(const vector<Fraction>&);
Fraction getQuotient(const vector<Fraction>&);
void printList(const vector<Fraction>&);



int main(int argc, char** argv)
{
    string inLine;
    ifstream inFile;
    vector <Fraction> fractionList; //initialize fraction list vector

    inFile.open(argv[1]);
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); //terminate with error
    }

    //read in file, create Fraction objects and place in vector fractionList
    while(getline(inFile, inLine))
    {
        istringstream ss(inLine);
        string inFraction;

        while(ss >> inFraction)
        {
            Fraction newFraction(inFraction);
            if(newFraction.Valid())
            {
                fractionList.push_back(newFraction);
            }

        }
    }

    //sort Vector
    sort(fractionList.begin(),	fractionList.end());

    cout << "The sum of the sorted fractions is: " << getSum(fractionList) << endl;
    cout << "The difference of the fractions is: " << getDifference(fractionList) << endl;
    cout << "The product of the fractions is: " << getProduct(fractionList) << endl;
    cout << "The quotient of the fractions is: " << getQuotient(fractionList) << endl;

    printList(fractionList);
}

Fraction getSum(const vector<Fraction> &fractionList)
{
    Fraction sumFraction;

    unsigned long long size = fractionList.size();

	for(unsigned int i = 0; i < size; i++)
	{
		sumFraction += fractionList[i];
	}

	return sumFraction;
}

Fraction getDifference(const vector<Fraction> &fractionList)
{
    Fraction difFraction;
    unsigned long long size = fractionList.size();

    difFraction = fractionList[0];
	for(unsigned int i = 1; i < size; i++)
	{
		difFraction -= fractionList[i];
	}

	return difFraction;
}

Fraction getProduct(const vector<Fraction> &fractionList)
{
    Fraction prodFraction;

    unsigned long long size = fractionList.size();

    prodFraction = fractionList[0];
	for(unsigned int i = 1; i < size; i++)
	{

		prodFraction *= fractionList[i];

	}

	return prodFraction;
}

Fraction getQuotient(const vector<Fraction> &fractionList)
{
    Fraction quotFraction;

    unsigned long long size = fractionList.size();

    quotFraction = fractionList[0];
	for(unsigned int i = 1; i < size; i++)
	{
	    if(fractionList[i].Valid())
        {
            quotFraction /= fractionList[i];
        }
	}

	return quotFraction;
}

void printList(const vector<Fraction> &fractionList)
{
    for (auto i: fractionList)
    {
        std::cout << i << endl;
    }
    
}
