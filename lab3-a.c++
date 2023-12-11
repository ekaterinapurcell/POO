// а) Să se creeze clasa 2-D de coordonate în plan.
// Să se definească operatorii "+" şi "-" ca funcţii prietene, iar operatorii de atribuire şi de comparare – ca metode ale clasei.
// De prevăzut posibilitatea efectuării operaţiilor atît între coordonate, cît şi între coordonate şi numere obişnuite.

#include <iostream>

class Coordonate2D
{
private:
    double x, y;

public:
    Coordonate2D(double xVal = 0.0, double yVal = 0.0) : x(xVal), y(yVal) {}

    ~Coordonate2D()
    {
        std::cout << "Obiectul Coordonate2D a fost distrus.\n";
    }

    Coordonate2D &operator=(const Coordonate2D &other)
    {
        if (this != &other)
        {
            x = other.x;
            y = other.y;
        }
        return *this;
    }

    bool operator==(const Coordonate2D &other) const
    {
        return (x == other.x && y == other.y);
    }

    Coordonate2D operator+(const Coordonate2D &other) const
    {
        return Coordonate2D(x + other.x, y + other.y);
    }

        Coordonate2D operator-(const Coordonate2D &other) const
    {
        return Coordonate2D(x - other.x, y - other.y);
    }

    Coordonate2D operator-(double val) const
    {
        return Coordonate2D(x - val, y - val);
    }

    Coordonate2D &operator+=(const Coordonate2D &other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Coordonate2D &operator-=(const Coordonate2D &other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    friend Coordonate2D operator-(double val, const Coordonate2D &coord)
    {
        return Coordonate2D(val - coord.x, val - coord.y);
    }

    friend std::ostream &operator<<(std::ostream &out, const Coordonate2D &coord)
    {
        out << "(" << coord.x << ", " << coord.y << ")";
        return out;
    }
};

int main()
{
    Coordonate2D coord1(3.0, 4.0);
    Coordonate2D coord2(1.0, 2.0);
    Coordonate2D coord3;

    coord3 = coord1 + coord2;
    std::cout << "Suma coord1 + coord2: " << coord3 << "\n";

    coord3 = coord1 - coord2;
    std::cout << "Diferenta coord1 - coord2: " << coord3 << "\n";

    coord3 = coord1 - 2.0;
    std::cout << "Diferenta coord1 - 2.0: " << coord3 << "\n";

    if (coord1 == coord2)
    {
        std::cout << "Cele doua coordonate sunt egale.\n";
    }
    else
    {
        std::cout << "Cele doua coordonate nu sunt egale.\n";
    }

    return 0;
}
