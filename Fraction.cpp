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

//default constructor
Fraction::Fraction()
{

	this->num = 0;
	this->denom = 1;
}

//constructor given int numerator and unsigned denominator
Fraction::Fraction(int inNum, unsigned int inDenom)
 {

    this->num = inNum;
    this->denom = inDenom;
    this->reduce();
 }

//constructor given int numerator and denominator
 Fraction::Fraction(int inNum, int inDenom)
 {

    this->num = inNum;
    this->denom = unsigned(inDenom);
    this->reduce();
 }

 //constructor given whole number, numerator, and denominator, sets numerator and denominator
Fraction::Fraction(int inWhole, unsigned inNum, unsigned int inDenom)
 {
    //numerator becomes numerator times whole number if whole != 0
    if(inWhole != 0)
    {
        this->num = inNum*inWhole;
    }
    else
    {
        this->num = inNum;
    }
    this->denom = inDenom;

    this->reduce();
 }


 //constructor given whole number, numerator, and denominator, sets numerator and denominator
Fraction::Fraction(int inWhole, int inNum, int inDenom)
 {
    //numerator becomes numerator times whole number if whole != 0
    if(inWhole != 0)
    {
        this->num = inNum*inWhole;
    }
    else
    {
        this->num = inNum;
    }
    this->denom = unsigned(inDenom);

    this->reduce();
 }


//float convert constructor
Fraction::Fraction(float number)
 {
	this->floatToFraction(number);
 }


 //string constructor
 Fraction::Fraction(string fractionString)
 {
    this->stringToFraction(fractionString);
 }

 void Fraction::stringToFraction(string fractionString)
 {
      int bug = 0;
      int wholePart = 0;
      istringstream inString(fractionString);
      int c = inString.peek();
      size_t undPos =fractionString.find("_");
      size_t slashPos =fractionString.find("/");
      int wholeFlag = 0;
      this->num = 0;
      this->denom = 1;

      //if first char isn't digit, set Fraction to 0 due to incorrect input
      if(!isdigit(c) && c != '-')
      {
          if(bug ==1)
          {
              cout << "Determined to not be valid due to first digit being nondigit or non -" << endl;
          }
          Fraction(0);
      }
      //this would probably be better as a switch, do if you have time
      else
      {
        //if no _ / or . is found set numerator to entire number
        if(fractionString.find("_") == std::string::npos && fractionString.find("/") == std::string::npos && fractionString.find(".") == std::string::npos)
        {
            if(bug ==1)
            {
                cout << "No _ / or . found, setting this-> num to be: " << stoi(fractionString) << endl;
            }
            this->num = stoi(fractionString);
        }
        //if string has a decimal, call float constructor
        else if(fractionString.find(".") != std::string::npos)
        {
            if(bug ==1)
            {
                cout << ". found, sending to float the following: " << stof(fractionString) << endl;
            }
            float stringAsFloat = stof(fractionString);
            this->floatToFraction(stringAsFloat);
        }
        else{

            //if fraction string has whole number, set it
            if(fractionString.find("_") != std::string::npos)
            {
                if(bug ==1)
                {
                    cout << "_ found, setting wholePart to: " << stoi(fractionString.substr(0, undPos).c_str()) << endl;
                }
                wholePart = stoi(fractionString.substr(0, undPos).c_str());
            }

            //get numerator and denom from string of format "X/Y" or "A_B/C" where above if statement has already handled A portion
            if(fractionString.find("/") != std::string::npos)
            {

                    //if there was no whole number part, set num using substring from index 0 to /
                    if (fractionString.find("_") == std::string::npos)
                    {
                        if(bug ==1)
                        {
                            cout << "Only / found, setting this->num to: " << stoi(fractionString.substr(0, slashPos).c_str()) << endl;
                        }
                        this->num = stoi(fractionString.substr(0, slashPos).c_str());

                    }
                    else
                    {
                        if(bug ==1)
                        {
                            cout << "_ found as well as /, setting this->num to: " << (stoi(fractionString.substr(undPos+1, slashPos).c_str())) << endl;
                        }
                        //mult by whole part to get correct improper fraction
                        this->num = (stoi(fractionString.substr(undPos+1, slashPos).c_str()));
                        wholeFlag = 1;

                    }
                    if(bug ==1)
                    {
                        cout << "Setting this->denom to: " << stoi(fractionString.substr(slashPos + 1).c_str()) << endl;
                    }

                    this->denom = stoi(fractionString.substr(slashPos + 1).c_str());
            }
            if(wholeFlag == 1)
            {

                if(wholePart >= 0)
                {
                    if(bug ==1)
                    {
                        cout << "Whole flag =1, whole is positive, setting num to: " <<  this->num << " + " << (wholePart*this->denom) << endl;
                    }
                    this->num += (wholePart*this->denom);
                }
                else
                {
                    if(bug ==1)
                    {
                        cout << "Whole flag =1, whole is negative, setting num to: -1*(" <<  this->num << " - " << (wholePart*this->denom) << ")" << endl;
                    }
                    this->num -= (wholePart*this->denom);
                    this->num = num*-1;
                }

            }
            if(bug ==1)
            {
                    cout << "Reducing: " <<  *this;
            }
            this->reduce();
            if(bug ==1)
            {
                    cout << " resulted in: " <<  *this << endl;
            }

        }
      }
 }

 bool Fraction::Valid() const
 {
     long long whole = this->num / this->denom;
     if(whole == 0 && this->num == 0)
     {
        return false;
     }
     else
     {
        return true;
     }

 }

 //takes a given float and constructs fraction class object
 void Fraction::floatToFraction(float number)
 {
	float fracPart = number - int(number);
	int wholePart = int(number);

    

    //get precision length on decimal portion (-2 to account for 0 and . of 0.xxx)
    stringstream ss;
    ss << fracPart;
    string size = ss.str();
    int length = size.length() -2;

    if(fracPart != 0)
    {
        //set denom to 10^length * 1 (adding 0.2 to fix pow rounding errors)
        this->denom= int((pow(10, length)+ 0.2));

        //numerator becomes numerator times whole number if whole != 0
        if(int(wholePart) != 0)
        {
            //set numerator to (10^length * decimal portion of number) times whole number
            this->num = int(wholePart)*this->denom + int(fracPart * (pow(10, length)+ 0.2));
        }
        else
        {
            this->num = int(fracPart * (pow(10, length)+ 0.2));
        }

        this->reduce();
    }
    else
    {
        this->num = wholePart;
        this->denom = 1;
    }

    


 }

bool Fraction::operator==(const Fraction &fraction) const
{
	return (this->num * (this->denom * fraction.Denominator())) == (fraction.Numerator() * (this->denom * fraction.Denominator()));
}

bool Fraction::operator!=(const Fraction &fraction) const
{
	return (this->num * (this->denom * fraction.Denominator())) != (fraction.Numerator() * (this->denom * fraction.Denominator()));
}

bool Fraction::operator<(const Fraction &fraction) const
{  
    long long num1 = this->num * fraction.Denominator();
    long long num2 = fraction.Numerator() * this->denom;
    return num1 < num2;
}

bool Fraction::operator<=(const Fraction &fraction) const
{
    long long num1 = this->num * fraction.Denominator();
    long long num2 = fraction.Numerator() * this->denom;

    return num1 <= num2;
}

bool Fraction::operator>(const Fraction &fraction) const
{
	long long num1 = this->num * fraction.Denominator();
    long long num2 = fraction.Numerator() * this->denom;

    return num1 > num2;
}

bool Fraction::operator>=(const Fraction &fraction) const
{
	long long num1 = this->num * fraction.Denominator();
    long long num2 = fraction.Numerator() * this->denom;

    return num1 >= num2;
}

//+ operator overload
Fraction Fraction::operator + (const Fraction &fraction) const
{
    Fraction result;
    //add numerators the correct way based on whether or not they have the same denominator
    if(this->denom == fraction.Denominator())
    {
        result.setNumerator(this->num + fraction.Numerator());
        result.setDenominator(this->denom);
    } else
    {
        result.setNumerator((this->num * fraction.Denominator()) + (fraction.Numerator() * this->denom));
        result.setDenominator(this->denom * fraction.Denominator());
    }
    result.reduce();

    return result;
}

//- operator overload
Fraction Fraction::operator - (const Fraction &fraction) const
{
    Fraction result;

    if (this->denom == fraction.Denominator()) {
		result.setNumerator(this->num - fraction.Numerator());
		result.setDenominator(this->denom);
	} else {
		result.setNumerator((this->num * fraction.Denominator()) - (fraction.Numerator() * this->denom));
		result.setDenominator(this->denom * fraction.Denominator());
	}
    result.reduce();

    return result;
}
//* operator overload
Fraction Fraction::operator * (const Fraction &fraction) const
{
    Fraction result;

    result.setNumerator(this->num * fraction.Numerator());
	result.setDenominator(this->denom * fraction.Denominator());
    result.reduce();

    return result;
}
// / operator overload
Fraction Fraction::operator / (const Fraction &fraction) const
{
    Fraction result;

    result.setDenominator(this->denom * fraction.Numerator());
	result.setNumerator(this->num * fraction.Denominator());
    result.reduce();

    return result;
}

//+= operator overload
Fraction Fraction::operator += (const Fraction &fraction)
{
    if (this->denom == fraction.Denominator()) {
		this->num += fraction.Numerator();
	} else {
		this->num = (this->num * fraction.Denominator()) + (fraction.Numerator() * this->denom);
		this->denom *= fraction.Denominator();
	}
    this->reduce();

	return *this;
}

//-= operator overload
Fraction Fraction::operator -= (const Fraction &fraction)
{
    if (this->denom == fraction.Denominator()) {
		this->num -= fraction.Numerator();
	} else {
		this->num = (this->num* fraction.Denominator()) - (fraction.Numerator() * this->denom);
		this->denom *= fraction.Denominator();
	}
    this->reduce();

	return *this;
}

//*= operator overload
Fraction Fraction::operator *= (const Fraction &fraction)
{
    this->denom *= fraction.Denominator();
	this->num *= fraction.Numerator();
    this->reduce();

	return *this;
}

// /= operator overload
Fraction Fraction::operator /= (const Fraction &fraction)
{

    this->denom *= fraction.Numerator();
	this->num *= fraction.Denominator();
    this->reduce();

	return *this;
}

ostream& operator << (ostream& out, const Fraction& fraction)
{
        long long whole = fraction.num / fraction.denom;
        int wholeFlag;
        if(whole != 0)
        {
            wholeFlag = 1;
        }
        if(wholeFlag ==1)
        {
            if(whole > 0)
            {
                out << whole << "_" << (fraction.Numerator()%fraction.Denominator()) << "/" << fraction.Denominator();
            }
            else
            {
                out << whole << "_" << ((-1*fraction.Numerator())%fraction.Denominator()) << "/" << fraction.Denominator();
            }
        }
        else
        {
            out << fraction.Numerator() << "/" << fraction.Denominator();
        }

        return out;
}


istream& operator>>(istream &in, Fraction &Fraction)
{

    string input;
    in >> input;
    return in;

}

void Fraction::reduce()
{
    long long gcd = __gcd(this->num, this->denom);

    if(gcd < 0)
    {
        gcd *= -1;
    }
    if(gcd > 1)
    {
        this->num /= gcd;
        this->denom /= gcd;
    }
}



int Fraction::Whole() const
{
    return int(this->num / this->denom);
}

long long Fraction::Numerator() const
{
    return this->num;
}

unsigned Fraction::Denominator() const
{
    return this->denom;
}

void Fraction::setNumerator(long long numerator)
{
    this->num = numerator;
}

void Fraction::setDenominator(long long denominator)
{
    this->denom = denominator;
}





