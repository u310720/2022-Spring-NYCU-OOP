#include <cmath>   //for M_PI, sqrt
#include <iomanip> // for setprecision(6)
#include "component.h"
#include "capacitor.h"
#include "resistor.h"
#include "inductor.h"
using namespace std;
double impedance_RLC(resistor r, inductor l, capacitor c,
                     double f);
int main(int argc, char *argv[])
{
    double f = 10;
    resistor r1(10), r2(32.5);
    cout << "r1: " << r1 << " r2: " << r2 << endl;
    r1 = r1 + r2;
    cout << "r1: " << r1 << " r2: " << r2 << endl;
    r1 = r1 || r2;
    cout << "r1: " << r1 << " r2: " << r2 << endl;
    capacitor c1(10, f), c2(30.5, f);
    cout << "c1: " << c1 << " c2: " << c2 << endl;
    c1 = c1 + c2;
    cout << "c1: " << c1 << " c2: " << c2 << endl;
    c1 = c1 || c2;
    cout << "c1: " << c1 << " c2: " << c2 << endl;
    inductor l1(10.5, f), l2(20.5, f);
    cout << "l1: " << l1 << " l2: " << l2 << endl;
    l1 = l1 + l2;
    cout << "l1: " << l1 << " l2: " << l2 << endl;
    l1 = l1 || l2;
    cout << "l1: " << l1 << " l2: " << l2 << endl;
    double result = impedance_RLC(r1, l1, c1, f);
    cout << fixed << setprecision(5);
    cout << "Series RLC Circuit Impedance is " << result
         << " \u03A9" << endl;
    return 0;
}

double impedance_RLC(resistor r, inductor l, capacitor c, double f)
{
    l.setFreq(f);
    c.setFreq(f);
    cout << "Series RLC Circuit Impedance Calculator ....." << endl;
    cout << r << " " << l << " " << c << endl;

    double re_2 = pow(r.get_impedance(), 2),
           im_2 = pow(l.get_impedance() - c.get_impedance(), 2);
    return sqrt(re_2 + im_2);
}
