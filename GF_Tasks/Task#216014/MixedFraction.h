
#include<iostream>

void lowestTerm(int& numerator, int& denominator);
class MixedFraction
{
	private:
		int whole;
		int numerator;
		int denominator;
	public:
		MixedFraction(int whole, int numerator, int denominator)
		{
			this->whole = whole;
			this->numerator = numerator;
			if (denominator == 0)
			{
				std::cout << "Error: denominator = 0. Value will be changed to 1\n";
				denominator = 1; 	
			}
			this->denominator = denominator;
			while ((this->numerator -= this->denominator) >= 0) this->whole++;
			this->numerator += this->denominator;
			lowestTerm(this->numerator, this->denominator);
		}
		int GetWhole() { return whole; }
		int GetNumerator() { return numerator; }
		int GetDenominator() { return denominator; }
		void SetWhole(int value) { whole = value; }
		void SetNumerator(int value) { numerator = value; }
	 	void SetDenominator(int value) { denominator = value; }
};
std::ostream& operator <<(std::ostream& cout, MixedFraction& value);
MixedFraction operator +(MixedFraction& value1, MixedFraction& value2);
MixedFraction operator *(MixedFraction& value1, MixedFraction& value2);

