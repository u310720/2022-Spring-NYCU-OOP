#ifndef COMP_H_
#define COMP_H_
class component
{
protected:
    double impedance;
    double value;
    double frequency;

public:
    virtual double get_impedance() const = 0;
    virtual void setFreq(double) = 0;
};

#endif
