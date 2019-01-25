#include"MixedFraction.h"
using namespace std;
void lowestTerm(int& numerator, int& denominator)
{
	int i = denominator;
	while (i > 1)
	{
		if ((numerator % i == 0) && (denominator % i == 0))
		{
			denominator /= i;
			numerator /= i;
			i = denominator;	
		} else i--;	
	}	
}
ostream& operator <<(ostream& cout, MixedFraction& value)
{
	cout << value.GetWhole() << ' ' << value.GetNumerator() << '/' << value.GetDenominator();
	return cout;	
}
MixedFraction operator +(MixedFraction& value1, MixedFraction& value2)
{	
	int numerator1 = value1.GetNumerator(),
		numerator2 = value2.GetNumerator();
	numerator1 += (value1.GetWhole() * value1.GetDenominator());
	numerator2 += (value2.GetWhole() * value2.GetDenominator());
	numerator1 *= value2.GetDenominator();
	numerator2 *= value1.GetDenominator();
	MixedFraction result = MixedFraction(0, numerator1 + numerator2, value1.GetDenominator() * value2.GetDenominator());
	return result;
}
MixedFraction operator *(MixedFraction& value1, MixedFraction& value2)
{
	int whole = value1.GetWhole(),
		numerator = value1.GetNumerator(),
		denominator = value1.GetDenominator();
	numerator += (whole * denominator);
	whole = value2.GetWhole();
	numerator *= (value2.GetNumerator() + (whole * value2.GetDenominator()));
	denominator *= value2.GetDenominator();
	whole = 0;
	lowestTerm(numerator, denominator);
	while ((numerator -= denominator) >= 0) whole++;
	numerator += denominator;
	MixedFraction result = MixedFraction(whole, numerator, denominator);
	return result;
}


