#include <iostream>
#include <memory>
#include <random>
#include "curves.h"

const int SOME_THRESHOLD = 5000;


int main() {
    std::vector<std::shared_ptr<Geometric_Curves>> all;
    std::random_device random_device;
    std::mt19937 engine{random_device()};
    std::uniform_int_distribution<size_t> type(0, 2);
    std::uniform_real_distribution<> pos(-100, 100);
    std::uniform_real_distribution<> rad_step(0, 100);
    all.reserve(100000);
    for (size_t i = 0; i < 100000; i++) {
        switch (type(engine)) {
            case 0:
                all.push_back(std::make_shared<Ellipse>(pos(engine), pos(engine), rad_step(engine), rad_step(engine)));
                break;
            case 1:
                all.push_back(std::make_shared<Helix>(pos(engine), pos(engine), pos(engine), rad_step(engine),
                                                      rad_step(engine)));
                break;
            case 2:
                all.push_back(std::make_shared<Circle>(pos(engine), pos(engine), rad_step(engine)));
                break;
        }
    }
    std::vector<std::shared_ptr<Circle>> circles;
    for (const auto &i: all) {
        if (auto circ = std::dynamic_pointer_cast<Circle>(i)) {
            circles.push_back(circ);
            std::cout << "Circle position at t = Pi/4 " << i->getPoint(M_PI / 4) << '\n';
            std::cout << "Circle derivatives at t = Pi/4 " << i->getDerivative(M_PI / 4) << '\n';
        } else if (std::dynamic_pointer_cast<Ellipse>(i)) {
            std::cout << "Ellipse position at t = Pi/4 " << i->getPoint(M_PI / 4) << '\n';
            std::cout << "Ellipse derivatives at t = Pi/4 " << i->getDerivative(M_PI / 4) << '\n';
        } else if (std::dynamic_pointer_cast<Helix>(i)) {
            std::cout << "Helix position at t = Pi/4 " << i->getPoint(M_PI / 4) << '\n';
            std::cout << "Helix derivatives at t = Pi/4 " << i->getDerivative(M_PI / 4) << '\n';
        }
    }

    std::sort(circles.begin(), circles.end(), [](std::shared_ptr<Circle> &a, std::shared_ptr<Circle> &b) {
        return a->radius_one < b->radius_one;
    });

    double radii_sum = 0;

    if (circles.size() >= SOME_THRESHOLD) {
#pragma omp parallel for reduction(+ : radii_sum) shared(circles)
        for (const auto &i: circles) {
            radii_sum += i->radius_one;
        }
    } else {
        for (const auto &i: circles) {
            radii_sum += i->radius_one;
        }
    }
    std::cout << "sum of radii: " << radii_sum << '\n';

    return 0;

}