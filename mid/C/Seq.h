#ifndef _Seq_H__
#define _Seq_H__
#include <iostream>
#include <string>
class Seq
{
private:
    int *data;
    int size;
public:
    // Q-1
    Seq(int);
    Seq(std::string);
    Seq(int *data, int size);
    ~Seq();
    void display();
    //Q-2
    void operator >> (int); // right circular shift
    void operator << (int); // left circular shift
    Seq operator - (); // circular time reversal
    Seq(const Seq&);
    //Q-3
    friend Seq operator * (const Seq&, const Seq&); // convolution sum
    Seq mid_filter(int); // median filter
};
#endif
