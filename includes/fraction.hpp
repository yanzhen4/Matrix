#pragma once
#include <iostream>
#include <limits>
#include <iomanip>

class Fraction{
    public:
        Fraction();
        Fraction(int n , int d );
        Fraction(double v);
        Fraction FindInverse();
        bool isValid();
        void reduction();
        std::string toString() const;

        int numerator;
        int denominator;
    private:

};

int FindGCD(int a, int b);
std::ostream& operator << (std::ostream& os,Fraction f);
Fraction operator+ (const Fraction& f1, const Fraction& f2);
Fraction operator- (const Fraction& f1, const Fraction& f2);
Fraction operator* (const Fraction& f1, const Fraction& f2);
Fraction operator/ (const Fraction& f1, const Fraction& f2);
bool operator== (const Fraction& f1, const Fraction& f2);