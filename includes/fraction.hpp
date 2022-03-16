#pragma once
#include <iostream>
#include <limits>

class Fraction{
    public:
        Fraction(int n, int d);
        Fraction FindInverse();
        bool isValid();
        void reduction();

        int numerator;
        int denominator;
    private:

};

int FindGCD(int a, int b);
Fraction operator+ (const Fraction& f1, const Fraction& f2);
Fraction operator- (const Fraction& f1, const Fraction& f2);
Fraction operator* (const Fraction& f1, const Fraction& f2);
Fraction operator/ (const Fraction& f1, const Fraction& f2);
bool operator== (const Fraction& f1, const Fraction& f2);