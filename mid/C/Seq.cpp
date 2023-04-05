#include "Seq.h"
#include <iostream>
#include <fstream>
using namespace std;

// Q-1
Seq::Seq(int)
{

}
Seq::Seq(string inf)
{
    ifstream ifs(inf, ios::in | ios::binary);
    ifs.read((char *)&size, sizeof(size));
    // cout << size << " "; // for debug
    data = new int[size];
    for(int i = 0; i < size; i++)
    {
        ifs.read((char *)&data[i], sizeof(data[i]));
        // cout << data[i] << " "; // for debug
    }
    // cout << endl; // for debug
    ifs.close();
}
Seq::Seq(int *_data, int _size)
{
    size = _size;
    data = _data;
}
Seq::~Seq()
{
    delete []data;
}
void Seq::display()
{
    for(int i = 0; i < size; i++)
        cout << data[i] << " ";
    cout << endl;
}

//Q-2
void Seq::operator >> (int rshNum) // right circular shift
{
    rshNum %= size;
    int tmp[size];
    for(int i = 0; i < size; i++)
        tmp[i] = data[(i - rshNum) < 0 ? (i - rshNum + size) : (i - rshNum)];
    for(int i = 0; i < size; i++)
        data[i] = tmp[i];
}
void Seq::operator << (int lshNum) // left circular shift
{
    lshNum %= size;
    int tmp[size];
    for(int i = 0; i < size; i++)
        tmp[i] = data[(i + lshNum) >= size ? (i + lshNum - size) : (i + lshNum)]; 
    for(int i = 0; i < size; i++)
        data[i] = tmp[i];
}
Seq Seq::operator - () // circular time reversal
{
    int *_data = new int[size];
    _data[0] = data[0];
    for(int i = 1; i < size; i++)
        _data[i] = data[size - i];
    return Seq(_data, size);
}
Seq::Seq(const Seq &S)
{
    size = S.size;
    data = new int[S.size];
    for(int i = 0; i < size; i++)
        data[i] = S.data[i];
}
