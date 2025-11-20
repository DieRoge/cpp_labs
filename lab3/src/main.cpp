#include <iostream>

#include "figure.h"
#include "octagon.h"
#include "hexagon.h"
#include "triangle.h"
#include "vector-figure.h"

int main()
{
    VectorFigure v;
    std::cout << "Input number of figures: ";
    int n;
    std::cin >> n;
    std::cout << "1 - Triangle\n2 - Hexagon\n3 - Octagon\n";

    for (int i = 0; i < n; ++i)
    {
        char c;
        std::cin >> c;
        Figure* f = nullptr;

        if (c == '1')
        {
            f = new Triangle();
        }
        else if (c == '2')
        {
            f = new Hexagon();
        }
        else if (c == '3')
        {
            f = new Octagon();
        }
        else
        {
            std::cout << "Invalid figure type\n";
            continue;
        }

        std::cin >> *f;
        v.push(f);
    }

    std::cout << "\nFigures info:\n";
    for (size_t i = 0; i < v.len(); ++i)
    {
        Figure* fig = v[i];
        std::cout << "Figure " << i << ": ";
        std::cout << *fig;
        std::cout << " Area: " << fig->Area();
        std::cout << " Center: " << fig->Center();
        std::cout << std::endl;
    }

    std::cout << "Total area: " << v.TotalArea() << std::endl;

    std::cout << "\nInput erase index: ";
    size_t ind;
    std::cin >> ind;

    if (ind < v.len())
    {
        v.erase(ind);
        std::cout << "Erased successfully\n";
    }
    else
    {
        std::cout << "Invalid index\n";
    }

    std::cout << "Remaining figures: " << v.len() << std::endl;
    return 0;
}