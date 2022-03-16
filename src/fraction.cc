#include "fraction.hpp"

int maxvalue_int = std::numeric_limits<int>::max();

Fraction::Fraction(){
    numerator = 0;
    denominator = 1000;
}

//Precision of three decimals
Fraction::Fraction(double v){
    numerator = v * 1000;
    denominator = 1000;
    Valid();
    reduction();
}

Fraction::Fraction(int n, int d){
    numerator = n;
    denominator = d;
    Valid();
    reduction();
}

void Fraction::Fraction::Valid(){
    //A fraction with a denominator and numerator of 0 is not valid 
    if(denominator == 0 && numerator == 0){
        throw std::runtime_error("invalid fraction");
    }
    if(denominator == 0){
        std::cout << "Detect zero denominator" <<std::endl;
        numerator = maxvalue_int;
        denominator = 1;
    }
}

int FindGCD(int a, int b){
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
    new_fraction.Valid();
    new_fraction.reduction();
    return new_fraction;
}

std::string Fraction::toString() const{
    if(denominator == 1){
        return std::to_string(numerator);
    }else{
        return std::to_string(numerator) + "/" + std::to_string(denominator);
    }
}

std::ostream& operator << (std::ostream& os,Fraction f){
    os << f.toString();
    return os;
}

bool operator== (const Fraction& f1, const Fraction& f2){
    return (f1.numerator / f1.denominator == f2.numerator / f2.denominator);
}

Fraction operator+ (const Fraction& f1, const Fraction& f2){
    int new_numerator = f1.numerator * f2.denominator + f2.numerator * f1.denominator;
    int new_denominator = f1.denominator * f2.denominator;
    Fraction new_fraction(new_numerator,new_denominator);
    new_fraction.Valid();
    new_fraction.reduction();
    return new_fraction;
}

Fraction operator- (const Fraction& f1, const Fraction& f2){
    int new_numerator = f1.numerator * f2.denominator - f2.numerator * f1.denominator;
    int new_denominator = f1.denominator * f2.denominator;
    Fraction new_fraction(new_numerator,new_denominator);
    new_fraction.Valid();
    new_fraction.reduction();
    return new_fraction;
}

Fraction operator* (const Fraction& f1, const Fraction& f2){
    int new_numerator = f1.numerator * f2.numerator;
    int new_denominator = f1.denominator * f2.denominator;
    Fraction new_fraction(new_numerator,new_denominator);
    new_fraction.Valid();
    new_fraction.reduction();
    return new_fraction;
}

Fraction operator/ (const Fraction& f1, const Fraction& f2){
     int new_numerator = f1.numerator * f2.denominator;
    int new_denominator = f1.denominator * f2.numerator;
    Fraction new_fraction(new_numerator,new_denominator);
    new_fraction.Valid();
    new_fraction.reduction();
    return new_fraction;
}