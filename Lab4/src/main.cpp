#include <iostream>
#include <memory>

#include "array.hpp"
#include "point.hpp"
#include "figure.hpp"
#include "trapezium.hpp"
#include "rhombus.hpp"
#include "pentagram.hpp"

int main() {
    std::cout << "Input amount of figures:\n";
    size_t figure_amount;
    std::cin >> figure_amount;

    Array<std::shared_ptr<Figure<double>>> figures;

    for (size_t i = 0; i < figure_amount; ++i) {
        std::cout << "Input figure type (1 - Trapezium, 2 - Rhombus, 3 - Pentagram):\n";
        int figure_type;
        std::cin >> figure_type;

        switch (figure_type) {
            case 1: {
                auto trapezium = std::make_shared<Trapezium<double>>();
                std::cout << "Input 4 vertices (x y) of Trapezium:\n";
                trapezium->readVertices(std::cin);
                figures.push(trapezium);
                break;
            }
            case 2: {
                auto rhombus = std::make_shared<Rhombus<double>>();
                std::cout << "Input 4 vertices (x y) of Rhombus:\n";
                rhombus->readVertices(std::cin);
                figures.push(rhombus);
                break;
            }
            case 3: {
                auto pentagram = std::make_shared<Pentagram<double>>();
                std::cout << "Input 5 vertices (x y) of Pentagram:\n";
                pentagram->readVertices(std::cin);
                figures.push(pentagram);
                break;
            }
            default: {
                std::cout << "Invalid figure type. Try again.\n";
                --i;
                break;
            }
        }
    }

    long double total_area = 0.0;
    for (size_t i = 0; i < figure_amount; ++i) {
        long double current_area = figures[i]->getArea();
        total_area += current_area;
        std::cout << "Figure " << i + 1 << ":\nVertices: ";
        figures[i]->printVertices(std::cout);
        std::cout << "Area: " << current_area << "\n";
        std::cout << "Center: " << figures[i]->getCenter() << "\n\n";
    } 
    std::cout << "Total area of all figures: " << total_area << "\n";

    return 0;
}