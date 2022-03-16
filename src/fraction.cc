#include "fraction.hpp"

int maxvalue_int = std::numeric_limits<int>::max();
Fraction::Fraction(int n, int d){
    if(d == 0){
        d = 1;
        n = maxvalue_int;
    }
    numerator = n;
    denominator = d;
    reduction();
}

bool Fraction::Fraction::isValid(){
    //A fraction with a denominator of 0 is not valid 
    if(denominator == 0){
        return false;
    }
    return true;
}

int FindGCD(int a, int b){
    if(a == 0 && b == 0){
        throw std::runtime_error("a and b are both 0");
    }

    if(a == 0){
       return b;
    }
    if(b == 0){
        return a;
    }

    int r = a % b;
    return FindGCD(b,r);
}

void Fraction::reduction(){
    int gcd = FindGCD(numerator, denominator);
    numerator = numerator / gcd;
    denominator = denominator / gcd;
}

Fraction Fraction::FindInverse(){
    int new_numerator = denominator;
    int new_denominator = numerator;
    Fraction new_fraction(new_numerator,new_denominator);
    new_fraction.reduction();
    return new_fraction;
}

bool operator== (const Fraction& f1, const Fraction& f2){
    return (f1.numerator / f1.denominator == f2.numerator / f2.denominator);
}

Fraction operator+ (const Fraction& f1, const Fraction& f2){
    int new_numerator = f1.numerator * f2.denominator + f2.numerator * f1.denominator;
    int new_denominator = f1.denominator * f2.denominator;
    Fraction new_fraction(new_numerator,new_denominator);
    new_fraction.reduction();
    return new_fraction;
}

Fraction operator- (const Fraction& f1, const Fraction& f2){
    int new_numerator = f1.numerator * f2.denominator - f2.numerator * f1.denominator;
    int new_denominator = f1.denominator * f2.denominator;
    Fraction new_fraction(new_numerator,new_denominator);
    new_fraction.reduction();
    return new_fraction;
}

Fraction operator* (const Fraction& f1, const Fraction& f2){
    int new_numerator = f1.numerator * f2.numerator;
    int new_denominator = f1.denominator * f2.denominator;
    Fraction new_fraction(new_numerator,new_denominator);
    new_fraction.reduction();
    return new_fraction;
}

Fraction operator/ (const Fraction& f1, const Fraction& f2){
     int new_numerator = f1.numerator * f2.denominator;
    int new_denominator = f1.denominator * f2.numerator;
    Fraction new_fraction(new_numerator,new_denominator);
    new_fraction.reduction();
    return new_fraction;
}