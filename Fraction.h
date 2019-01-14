
#ifndef FRACTION_H
#define FRACTION_H
#include <iostream>
using namespace std;
class Fraction
{
	public:
		class Exception
		{
			public:
				Exception ();
				Exception (int C);
				int GetCode () const;
				string GetMessage () const;
			private:
				int code;
		};
		Fraction ();
		Fraction (int, int);
		Fraction (int, unsigned);
		Fraction (int, unsigned, unsigned);
		Fraction (int, int, int);
		Fraction (float);
		Fraction (string);
		bool Valid () const;
		int Whole () const;
		long long Numerator () const;
		unsigned Denominator () const;
		bool operator == (const Fraction &) const;
		bool operator != (const Fraction &) const;
		bool operator < (const Fraction &) const;
		bool operator <= (const Fraction &) const;
		bool operator > (const Fraction &) const;
		bool operator >= (const Fraction &) const;
		Fraction operator + (const Fraction &) const;
		Fraction operator - (const Fraction &) const;
		Fraction operator * (const Fraction &) const;
		Fraction operator / (const Fraction &) const;
		Fraction operator += (const Fraction &);
		Fraction operator -= (const Fraction &);
		Fraction operator *= (const Fraction &);
		Fraction operator /= (const Fraction &);
		friend ostream & operator << (ostream &, const Fraction &);
		friend istream & operator >> (istream &, Fraction &);
		void floatToFraction(float);
		void stringToFraction(string);
		void reduce();
		void setNumerator(long long);
		void setDenominator(long long);
	private:
		long long num;
		long long denom;



};

#endif
