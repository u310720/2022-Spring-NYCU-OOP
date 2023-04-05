#ifndef RESISTOR_H_
#define RESISTOR_H_
#include "component.h"

#include <iostream>
using std::ostream;

class resistor : public component
{
private:
public:
    void setFreq(double);
    double get_impedance() const;
    resistor();
    // Add some functions or data members by yourself
    resistor(double);
    resistor operator+(const resistor &);
    resistor operator||(const resistor &);

    friend ostream &operator<<(ostream &, const resistor &);
};

// resistor.cpp
// #include "resistor.h"
#include <iomanip>
using std::ios;
using std::setiosflags;
using std::setprecision;

void resistor::setFreq(double f)
{
    frequency = f;
}

double resistor::get_impedance() const
{
    static const double unit = 1; // (Ω)
    return unit *
           impedance; // Z = R
}

resistor::resistor()
{
}

resistor::resistor(double _impedance)
{
    impedance = _impedance;
}

resistor resistor::operator+(const resistor &r)
{
    return resistor(impedance + r.impedance);
}
resistor resistor::operator||(const resistor &r)
{
    return resistor((impedance * r.impedance) / (impedance + r.impedance));
}

ostream &operator<<(ostream &out, const resistor &r)
{
    ios init(nullptr);
    init.copyfmt(out);

    out << setiosflags(ios::fixed) << setprecision(5) << r.impedance << " Ω "; // Ω = \u03A9

    out.copyfmt(init);
    return out;
}

#endif
