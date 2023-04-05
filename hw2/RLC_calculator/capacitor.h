#ifndef __CAPACITOR_H__
#define __CAPACITOR_H__

#include "component.h"
#include <iostream>
using std::ostream;

class capacitor : public component
{
private:
public:
    void setFreq(double);
    double get_impedance() const;
    capacitor();
    // Add some functions or data members by yourself
    capacitor(double impedance, double frequency);
    capacitor operator+(const capacitor &);
    capacitor operator||(const capacitor &);

    friend ostream &operator<<(ostream &, const capacitor &);
};


// capacitor.cpp
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <cmath> // include M_PI

// #include "capacitor.h"

#include <iomanip>
using std::ios;
using std::setiosflags;
using std::setprecision;

void capacitor::setFreq(double f)
{
    frequency = f;
}

double capacitor::get_impedance() const
{
    static const double unit = 0.000001; // (uF)
    return (1.0 / unit) /
           (2 * M_PI * frequency * impedance); // Z = 1 / wC
}

capacitor::capacitor()
{
}

capacitor::capacitor(double _impedance, double _frequency)
{
    impedance = _impedance;
    frequency = _frequency;
}

capacitor capacitor::operator+(const capacitor &c)
{
    return capacitor((impedance * c.impedance) / (impedance + c.impedance), frequency);
}

capacitor capacitor::operator||(const capacitor &c)
{
    return capacitor(impedance + c.impedance, frequency);
}

ostream &operator<<(ostream &out, const capacitor &c)
{
    ios init(nullptr);
    init.copyfmt(out);

    out << setiosflags(ios::fixed) << setprecision(5) << c.impedance << " μF "
        << " (Xc " << c.get_impedance() << " Ω)"; // Ω = \u03A9

    out.copyfmt(init);
    return out;
}

#endif // __CAPACITOR_H__
