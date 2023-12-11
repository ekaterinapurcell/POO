// a) Să se creeze o ierarhie a claselor Figură de şah - clasa abstractă, care conţine câmpul – culoare.
//  Creaţi pentru toate figurile clase derivate, care conţin denumirea figurii şi coordonatele poziţiei pe tablă.
//  Pentru setarea cîmpurilor textuale, utilizaţi operatorul new.
//  Determinaţi fluxul de ieşire şi fluxul de intrare, constructorul de copiere, operatorul de atribuire prin funcţiile corespunzătoare ale clasei de bază.

#include <iostream>
#include <map>

class FiguraDeSah {
private:
    std::string culoare;
    std::string denumire;
    int pozitieX;
    int pozitieY;

public:
    FiguraDeSah(const std::string& culoare, const std::string& denumire, int x, int y)
        : culoare(culoare), denumire(denumire), pozitieX(x), pozitieY(y) {
        std::cout << "Constructor FiguraDeSah pentru " << denumire << std::endl;
    }

    FiguraDeSah(const FiguraDeSah& other)
        : culoare(other.culoare), denumire(other.denumire), pozitieX(other.pozitieX), pozitieY(other.pozitieY) {
        std::cout << "Constructor de copiere FiguraDeSah pentru " << denumire << std::endl;
    }

    FiguraDeSah& operator=(const FiguraDeSah& other) {
        if (this != &other) {
            culoare = other.culoare;
            denumire = other.denumire;
            pozitieX = other.pozitieX;
            pozitieY = other.pozitieY;
            std::cout << "Operator de atribuire FiguraDeSah pentru " << denumire << std::endl;
        }
        return *this;
    }

    ~FiguraDeSah() {
        std::cout << "Destructor FiguraDeSah pentru " << denumire << std::endl;
    }

    friend std::istream& operator>>(std::istream& in, FiguraDeSah& figura);
    friend std::ostream& operator<<(std::ostream& out, const FiguraDeSah& figura);
};

std::istream& operator>>(std::istream& in, FiguraDeSah& figura) {
    in >> figura.culoare >> figura.denumire >> figura.pozitieX >> figura.pozitieY;
    return in;
}

std::ostream& operator<<(std::ostream& out, const FiguraDeSah& figura) {
    out << "Figura de tip " << figura.denumire << " cu culoare " << figura.culoare
        << " se afla la pozitia (" << figura.pozitieX << ", " << figura.pozitieY << ").\n";
    return out;
}

class FiguriSah {
private:
    FiguraDeSah* tabla[8][8] = {nullptr};

public:
    FiguriSah(const std::map<std::string, FiguraDeSah*>& figuri) {
        for (const auto& pair : figuri) {
            FiguraDeSah* figura = pair.second;
            int x = figura->pozitieX;
            int y = figura->pozitieY;

            if (x >= 0 && x < 8 && y >= 0 && y < 8 && tabla[x][y] == nullptr) {
                tabla[x][y] = new FiguraDeSah(*figura);
            } else {
                std::cerr << "Eroare: Pozitie (" << x << ", " << y << ") este ocupata sau invalida.\n";
            }
        }
    }

    ~FiguriSah() {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                delete tabla[i][j];
            }
        }
    }

    FiguriSah(const FiguriSah& other) {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                tabla[i][j] = (other.tabla[i][j] != nullptr) ? new FiguraDeSah(*(other.tabla[i][j])) : nullptr;
            }
        }
    }

    FiguriSah& operator=(const FiguriSah& other) {
        if (this != &other) {
            for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 8; ++j) {
                    delete tabla[i][j];
                    tabla[i][j] = (other.tabla[i][j] != nullptr) ? new FiguraDeSah(*(other.tabla[i][j])) : nullptr;
                }
            }
        }
        return *this;
    }

    void eliminaFigura(int x, int y) {
        if (x >= 0 && x < 8 && y >= 0 && y < 8) {
            delete tabla[x][y];
            tabla[x][y] = nullptr;
        } else {
            std::cerr << "Eroare: Pozitie (" << x << ", " << y << ") invalida.\n";
        }
    }

    void afisareTabla() const {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (tabla[i][j] != nullptr) {
                    std::cout << *tabla[i][j];
                }
            }
        }
    }
};

int main() {
    std::map<std::string, FiguraDeSah*> figuri;
    figuri["Figura1"] = new FiguraDeSah("Alb", "Turn", 2, 3);
    figuri["Figura2"] = new FiguraDeSah("Negru", "Cal", 5, 6);
    figuri["Figura3"] = new FiguraDeSah("Alb", "Regina", 1, 1);
    figuri["Figura4"] = new FiguraDeSah("Negru", "Pion", 7, 7);

    FiguriSah figuriSah(figuri);
    figuriSah.afisareTabla();

    // Test eliminare figura
    int x = 3, y = 5; // Exemplu pozitie pentru eliminare figura
    figuriSah.eliminaFigura(x, y);
    figuriSah.afisareTabla();

    // Eliberare memorie
    for (const auto& pair : figuri) {
        delete pair.second;
    }

    return 0;
}
