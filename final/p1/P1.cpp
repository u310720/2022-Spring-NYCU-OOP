#define _USE_MATH_DEFINES
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// P1.cpp PART1-Template
template <class T>
T *new_pvec(int n)
{
    /*
    FUNCTION:
    New the number of n spaces in type T.
    */
    // NEED SOME CODES
    T *arr = new T[n];
    return arr;
}
template <class T>
void copy_pvec(T *p1, T *p2, int n)
{
    /*
    FUNCTION:
    Copy the number of n spaces in type T from p2 to p1.
    You don’t need to allocate new spaces to p1.
    */
    // NEED SOME CODES
    for (int i = 0; i < n; ++i)
        p1[i] = p2[i];
}
template <class T>
void del_pvec(T *vecs)
{
    /*
    FUNCTION:
    Delete an array.
    */
    // NEED SOME CODES
    delete[] vecs;
}
template <class T>
void display_pvec(T *vecs, int n)
{
    /*
    FUNCTION:
    Display the number of n elements using cout.
    */
    // NEED SOME CODES
    for (int i = 0; i < n; ++i)
        cout << vecs[i] << endl;
}

// P1.cpp PART2-Point-Class
class Point2D
{
private:
    int *x;
    int *y;

public:
    Point2D(int n1, int n2)
    {
        /*
        FUNCTION:
        Constructor assigns memory and value.
        n1 -> x, n2 -> y.
        */
        // NEED SOME CODES
        x = new int(n1);
        y = new int(n2);
    }
    Point2D()
    {
        /*
        FUNCTION:
        Constructor assigns memory and random value in range [0,
       999].
        */
        // NEED SOME CODES
        x = new int(rand() % 1000);
        y = new int(rand() % 1000);
    }
    Point2D(Point2D &p)
    {
        /*
        FUNCTION:
        Constructor copys data value from p.
        */
        // NEED SOME CODES
        x = new int(*p.x);
        y = new int(*p.y);
    }
    int getX()
    {
        return *x;
    }
    int getY()
    {
        return *y;
    }
    friend ostream &operator<<(ostream &out, Point2D &p);
    void operator=(Point2D &p)
    {
        /*
        FUNCTION:
        Assign values to the data members from p.
        */
        // NEED SOME CODES
        *x = p.getX();
        *y = p.getY();
    };
    virtual void display() { cout << (*this); }
};
ostream &operator<<(ostream &out, Point2D &p)
{
    /*
    FUNCTION:
    As shown in the output file, display point p.
    */
    // NEED SOME CODES
    out << "x=" << *p.x << " y=" << *p.y;
    return out;
}
class Point4D : public Point2D
{
private:
    int *z;
    int *t;

public:
    Point4D() : Point2D()
    {
        /*
        FUNCTION:
        Constructor assigns memory and random value in range [0,
       999].
        */
        // NEED SOME CODES
        z = new int(rand() % 1000);
        t = new int(rand() % 1000);
    }
    ~Point4D()
    {
        /*
        FUNCTION:
        Delete memory of data members.
       */
        // NEED SOME CODES
        delete z;
        delete t;
    }
    void display() { cout << (*this); }
    friend ostream &operator<<(ostream &out, Point4D &p);
};
ostream &operator<<(ostream &out, Point4D &p)
{
    /*
    FUNCTION:
    As shown in the output, display point p.
    */
    // NEED SOME CODES
    cout << (Point2D &)p << " z=" << *p.z << " t=" << *p.t;
    return out;
}
// P1.cpp PART3-Shape-Class
class Shape
{
protected:
    int color;
    Point2D *points;

public:
    virtual void area() = 0;
    virtual bool is_polygon() = 0;
    ~Shape() {}
};
class Polygon : virtual public Shape
{
public:
    bool is_polygon() { return true; }
};
class Circle : virtual public Shape
{
private:
    Point2D center;
    double radius;

public:
    Circle(Point2D p, double r) : center(p), radius(r) {}
    void area()
    {
        /*
        FUNCTION:
        Print the area as the output shows.
        */
        // NEED SOME CODES
        cout << "Circle Area is " << fixed << setprecision(5) << get_area() << endl;
    };
    double get_area()
    {
        /*
        FUNCTION:
        Return the area of this circle.
        */
        // NEED SOME CODES
        return radius * radius * M_PI;
    }
    bool is_polygon() { return false; }
};
class Triangle : public Polygon
{
private:
    Point2D *pvecs;

public:
    Triangle(Point2D *vecs)
    {
        pvecs = new Point2D[3];
        copy_pvec<Point2D>(pvecs, vecs, 3);
    }
    ~Triangle() { delete[] pvecs; }
    void area()
    {
        /*
        FUNCTION:
        Print the area as the output shows.
        */
        // NEED SOME CODES
        cout << pvecs[0] << endl;
        cout << pvecs[1] << endl;
        cout << pvecs[2] << endl;
        cout << "Triangle Area is " << fixed << setprecision(5) << get_area() << endl;
    };
    double get_area()
    {
        /*
        FUNCTION:
        Return the area of this triangle.
        */
        // NEED SOME CODES
        // reference: https://highscope.ch.ntu.edu.tw/wordpress/?p=66359
        Point2D &A = pvecs[0], &B = pvecs[1], &C = pvecs[2];

        int AB[2] = {B.getX() - A.getX(),  // a = Bx - Ax
                     B.getY() - A.getY()}; // b = By - Ay
        int AC[2] = {C.getX() - A.getX(),  // c = Cx - Ax
                     C.getY() - A.getY()}; // d = Cy - Ay

        int a = AB[0], b = AB[1], c = AC[0], d = AC[1];

        return 0.5 * abs(a * d - b * c);
    }
};
class Triangle_and_Circle : public Triangle, public Circle
{
public:
    Triangle_and_Circle(Point2D p, double r, Point2D *vecs) : Triangle(vecs), Circle(p, r) {}
    void area()
    {
        /*
        FUNCTION:
        Print the area as the output shows.
        */
        // NEED SOME CODES
        cout << fixed << setprecision(5) << get_area() << endl;
    };
    double get_area()
    {
        /*
        FUNCTION:
        Return the area of this triangle minus circle.
        */
        // NEED SOME CODES
        return Triangle::get_area() - Circle::get_area();
    }
    bool is_polygon() { return false; }
};

// P1.cpp PART4-main
int main()
{
    srand(1);
    cout << "===== int vecs template =====" << endl;
    int *vec_int = new_pvec<int>(3);
    display_pvec(vec_int, 3);
    del_pvec(vec_int);
    vec_int = new int[4];
    vec_int[0] = 10;
    vec_int[1] = 20;
    vec_int[2] = 30;
    vec_int[3] = 40;
    int *vec_int2 = new int[4];
    copy_pvec(vec_int2, vec_int, 4);
    display_pvec(vec_int, 3);
    del_pvec(vec_int);
    del_pvec(vec_int2);
    cout << endl;
    cout << "===== Point2D p1 =====" << endl;
    Point2D p1(0, 0);
    cout << p1 << endl;
    cout << endl;
    cout << "===== Point2D p2 =====" << endl;
    Point2D p2;
    cout << p2 << endl;
    cout << endl;
    cout << "===== Point4D p4 =====" << endl;
    Point2D *p = new Point4D;
    p->display();
    cout << endl;
    cout << "===== new vec =====" << endl;
    Point2D *vec = new_pvec<Point2D>(3);
    display_pvec(vec, 3);
    cout << endl;
    cout << "===== Circle and Triangle =====" << endl;
    Triangle_and_Circle tc(p1, 10, vec);
    tc.area();
    if (tc.is_polygon())
        cout << "This is a polygon" << endl;
    else
        cout << "This is not a polygon" << endl;
    cout << endl;
    cout << "===== Delete =====" << endl;
    del_pvec<Point2D>(vec);
    cout << endl;
    cout << "===== Area of the Circle =====" << endl;
    tc.Circle::area();
    if (tc.Circle::is_polygon())
        cout << "This is a polygon" << endl;
    else
        cout << "This is not a polygon" << endl;
    cout << endl;
    cout << "===== Area of the Triangle =====" << endl;
    tc.Triangle::area();
    if (tc.Triangle::is_polygon())
        cout << "This is a polygon" << endl;
    else
        cout << "This is not a polygon" << endl;
    cout << endl;
    return 0;
}