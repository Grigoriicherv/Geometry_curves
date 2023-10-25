#include "curves.h"

Point::Point(double x, double y, double z) : x(x), y(y), z(z) {}

std::ostream &operator<<(std::ostream &os, const Point &vec) {
    return os << "[" << vec.x << " " << vec.y << " " << vec.z << "]";
}

Vector3D::Vector3D(double x, double y, double z) : Point(x, y, z) {}

std::ostream &operator<<(std::ostream &os, const Vector3D &vec) {
    return os << "[" << vec.x << " " << vec.y << " " << vec.z << "]";
}

Geometric_Curves::Geometric_Curves(double x, double y, double z) : center(x, y, z) {}

Geometric_Curves::Geometric_Curves(Point point) : center(point) {}

Geometric_Curves::~Geometric_Curves() noexcept = default;

Circle::Circle(Point point, double r) : Ellipse(point, r, r) {}

Circle::Circle(double x, double y, double z, double r) : Ellipse(x, y, z, r, r) {}

Circle::Circle(double x, double y, double r) : Ellipse(x, y, r, r) {}

Ellipse::Ellipse(double x, double y, double z, double r_one, double r_two)
        : Geometric_Curves(x, y, z), radius_two(r_one), radius_one(r_two) {}

Ellipse::Ellipse(double x, double y, double r_one, double r_two)
        : Geometric_Curves(x, y, 0), radius_one(r_two), radius_two(r_one) {}


Ellipse::Ellipse(Point point, double r_one, double r_two) : Geometric_Curves(point), radius_two(r_one),
                                                            radius_one(r_two) {}

Vector3D Ellipse::getDerivative(double t) {
    double dx = -radius_one * sin(t);
    double dy = radius_two * cos(t);
    return {dx, dy, 0};
}

Point Ellipse::getPoint(double t) {
    double x = this->center.x + radius_one * cos(t);
    double y = this->center.y + radius_two * sin(t);
    return {x, y, this->center.z};
}

Helix::Helix(double x, double y, double z, double r, double st) : Geometric_Curves(x, y, z), radius(r), step(st) {}

Helix::Helix(Point point, double r, double st) : Geometric_Curves(point), radius(r), step(st) {}

Vector3D Helix::getDerivative(double t) {
    double dx = -radius * sin(t);
    double dy = radius * cos(t);
    double dz = step / (M_PI * 2);
    return {dx, dy, dz};
}

Point Helix::getPoint(double t) {
    double x = this->center.x + radius * cos(t);
    double y = this->center.y + radius * sin(t);
    double z = this->center.z + step * t / (M_PI * 2);
    return {x, y, z};
}
