#include "Point_Set.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

// A01
Point_Set::Point_Set()
{
}
Point_Set::~Point_Set()
{
}
void Point_Set::Parser(string inf)
{
    ifstream ifs(inf);
    ifs >> name;
    name.pop_back(); // remove ':'
    ifs >> num;
    points = new Point[num];
    for(int i = 0; i < num; i++)
    {
        ifs >> points[i].name;
        
        string tmp;        
        ifs >> tmp;
        for(auto &c : tmp)
            if(c == '(' || c == ')' || c == ',')
                c = ' ';
        istringstream iss(tmp);
        iss >> points[i].x >> points[i].y;
    }
}
/*void sort(Point *arr, size)
{
    double min_dist = 10000000;
    double dist = new double[size];
    for(int i = 0; i < size; i++)
        dist = arr[i].x * arr[i].x + arr[i].y * arr[i].y;
    for(int i = 0; i < size; i++)
    {
        for(int j = i + 1; j < size; j++)
        {
            
        }
    }
}*/
void DisplayPointSet(const Point_Set &ps)
{
    /*sort(ps.points, ps.num);
    cout << ps.name << ":" << endl;
    for(int i = 0; i < ps.num; i++)
    {
        cout << ps.points[i].name << ": ";
        cout << "(" << ps.points[i].x << "," << ps.points[i].y << ")" << endl;
    }
    cout << endl;*/
    vector<Point> v;
    for(int i = 0; i < ps.num; i++)
        v.push_back(ps.points[i]);
    sort(v.begin(), v.end(), [](Point &p1, Point &p2)
        {
            return p1.x * p1.x + p1.y * p1.y
                    < p2.x * p2.x + p2.y * p2.y;
        });
    cout << ps.name << ":" << endl;
    for(const auto p : v)
    {
        cout << p.name << ": ";
        cout << "(" << p.x << "," << p.y << ")" << endl;
    }
    cout << endl;
}

// Q2
void Point_Set::operator+=(const double &d)
{
    for(int i = 0; i < num; i++)
    {
        points[i].x += d;
        points[i].y += d;
    }
}
void Point_Set::operator*=(const double &d)
{
    for(int i = 0; i < num; i++)
    {
        points[i].x *= d;
        points[i].y *= d;
    }
}

// A03
void Point_Set::fit(double &b0, double &b1)
{
    double avgX = 0, avgY = 0;
    for(int i = 0; i < num; i++)
    {
        avgX += points[i].x;
        avgY += points[i].y;
    }
    avgX /= num;
    avgY /= num;

    double SSxx = 0, SSxy = 0;
    for(int i = 0; i < num; i++)
    {
        SSxx += (points[i].x - avgX) * (points[i].x - avgX);
        SSxy += (points[i].x - avgX) * (points[i].y - avgY);
    }
    b1 = SSxy / SSxx;
    b0 = avgY - b1 * avgX;
}
void Point_Set::predict(const double &b0, const double &b1)
{
    cout << "b_0 = " << b0 << endl;
    cout << "b_1 = " << b1 << endl;

    cout << endl;
    cout << "Predicted Data:" << endl;
    for(int i = 0; i < num; i++)
        cout << "(" << points[i].x << "," << (b0 + b1 *  points[i].x) << ")" << endl;
}
