#ifndef WORKNOTWOLF_CURVES_H
#define WORKNOTWOLF_CURVES_H

#include <vector>
#include <cmath>
#include <iostream>

struct Point {
    double x, y, z;

    Point(double x, double y, double z);

    friend std::ostream &operator<<(std::ostream &os, const Point &vec);
};

struct Vector3D : public Point {
    Vector3D(double x, double y, double z);

    friend std::ostream &operator<<(std::ostream &os, const Point &vec);
};

class Geometric_Curves {
protected:
    Point center;
public:
    Geometric_Curves(double x, double y, double z);

    explicit Geometric_Curves(Point point);

    virtual ~Geometric_Curves() noexcept;

    virtual Point getPoint(double t) = 0;

    virtual Vector3D getDerivative(double t) = 0;
};

class Ellipse : public Geometric_Curves {
public:
    double radius_one, radius_two;

    Ellipse(double x, double y, double z, double r_one, double r_two);

    Ellipse(Point point, double r_one, double r_two);

    Ellipse(double x, double y, double r_one, double r_two);

    Point getPoint(double t) override;

    Vector3D getDerivative(double t) override;
};

class Circle : public Ellipse {
public:
    Circle(double r, double x, double y, double z);

    Circle(Point point, double r);

    Circle(double x, double y, double r);
};

class Helix : public Geometric_Curves {
    double radius, step;

public:
    Helix(double x, double y, double z, double r, double st);

    Helix(Point point, double r, double st);

    Point getPoint(double t) override;

    Vector3D getDerivative(double t) override;
};


#endif //WORKNOTWOLF_CURVES_H
