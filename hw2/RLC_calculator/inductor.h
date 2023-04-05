#ifndef __INDUCTOR_H__
#define __INDUCTOR_H__

#include "component.h"
#include <iostream>
using std::ostream;

class inductor : public component
{
private:
public:
    void setFreq(double);
    double get_impedance() const;
    inductor();
    // Add some functions or data members by yourself
    inductor(double impedance, double frequency);
    inductor operator+(const inductor &);
    inductor operator||(const inductor &);

    friend ostream &operator<<(ostream &, const inductor &);
};


// inductor.cpp
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include <cmath> // include M_PI

// #include "inductor.h"

#include <iomanip>
using std::ios;
using std::setiosflags;
using std::setprecision;

void inductor::setFreq(double f)
{
    frequency = f;
}

double inductor::get_impedance() const
{
    static const double unit = 0.001; // (mH)
    return unit *
           2 * M_PI * frequency * impedance; // Z = wL
}

inductor::inductor()
{
}

inductor::inductor(double _impedance, double _frequency)
{
    impedance = _impedance;
    frequency = _frequency;
}

inductor inductor::operator+(const inductor &l)
{
    return inductor(impedance + l.impedance, frequency);
}

inductor inductor::operator||(const inductor &l)
{
    return inductor((impedance * l.impedance) / (impedance + l.impedance), frequency);
}

ostream &operator<<(ostream &out, const inductor &l)
{
    ios init(nullptr);
    init.copyfmt(out);

    out << setiosflags(ios::fixed) << setprecision(5) << l.impedance << " mH "
        << " (Xl " << l.get_impedance() << " \u03A9) "; // Ω = \u03A9

    out.copyfmt(init);
    return out;
}

#endif // __INDUCTOR_H__
