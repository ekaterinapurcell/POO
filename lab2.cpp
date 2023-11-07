// Să se creeze clasa Set – mulţimea numerelor întregi, utilizînd memoria dinamică.
// Să se definească constructorii: implicit şi de copiere.
// Să se definească funcţiile: de adăugare a unui element nou în mulţime; de determinare a apartenenţei elementului la mulţime; de adunare, scădere şi intersecţie a două mulţimi.

#include <iostream>
#include <set>

class Set
{
private:
    std::set<int> elements;

public:
    // Constructor implicit
    Set() {}

    // Constructor de copiere
    Set(const Set &other) : elements(other.elements) {}

    // Funcție pentru adăugarea unui element în mulțime
    void addElement(int element)
    {
        elements.insert(element);
    }

    // Funcție pentru determinarea apartenenței unui element la mulțime
    bool containsElement(int element) const
    {
        return elements.find(element) != elements.end();
    }

    // Funcție pentru adunarea a două mulțimi
    Set unionSets(const Set &other) const
    {
        Set resultSet(*this);
        for (int element : other.elements)
        {
            resultSet.addElement(element);
        }
        return resultSet;
    }

    // Funcție pentru scăderea a două mulțimi
    Set differenceSets(const Set &other) const
    {
        Set resultSet(*this);
        for (int element : other.elements)
        {
            resultSet.elements.erase(element);
        }
        return resultSet;
    }

    // Funcție pentru intersecția a două mulțimi
    Set intersectionSets(const Set &other) const
    {
        Set resultSet;
        for (int element : elements)
        {
            if (other.containsElement(element))
            {
                resultSet.addElement(element);
            }
        }
        return resultSet;
    }

    // Funcție pentru afișarea mulțimii
    void display() const
    {
        for (int element : elements)
        {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
};

void showMenu()
{
    std::cout << "Meniu:" << std::endl;
    std::cout << "1. Adauga element in multime" << std::endl;
    std::cout << "2. Verifica apartenenta elementului" << std::endl;
    std::cout << "3. Aduna doua multimi" << std::endl;
    std::cout << "4. Scade doua multimi" << std::endl;
    std::cout << "5. Intersectia a doua multimi" << std::endl;
    std::cout << "6. Iesire" << std::endl;
}

int main()

{
    Set set1, set2, resultSet;
    int choice, element;

    // Adăugare elemente inițiale în multimea set1
    set1.addElement(1);
    set1.addElement(2);
    set1.addElement(3);

    // Adăugare elemente inițiale în multimea set2
    set2.addElement(3);
    set2.addElement(4);
    set2.addElement(5);

    // Afișarea elementelor inițiale ale mulțimilor
    std::cout << "Multimea 1: ";
    set1.display();
    std::cout << "Multimea 2: ";
    set2.display();

    do
    {
        showMenu();
        std::cout << "Introduceti optiunea: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            std::cout << "Introduceti elementul: ";
            std::cin >> element;
            set1.addElement(element);
            break;
        case 2:
            std::cout << "Introduceti elementul pentru verificare: ";
            std::cin >> element;
            if (set1.containsElement(element))
            {
                std::cout << "Elementul apartine multimii." << std::endl;
            }
            else
            {
                std::cout << "Elementul nu apartine multimii." << std::endl;
            }
            break;
        case 3:
            resultSet = set1.unionSets(set2);
            std::cout << "Rezultatul adunarii: ";
            resultSet.display();
            break;
        case 4:
            resultSet = set1.differenceSets(set2);
            std::cout << "Rezultatul scaderii: ";
            resultSet.display();
            break;
        case 5:
            resultSet = set1.intersectionSets(set2);
            std::cout << "Rezultatul intersectiei: ";
            resultSet.display();
            break;
        case 6:
            std::cout << "La revedere!";
            break;
        default:
            std::cout << "Optiune invalida! Va rugam sa reintroduceti." << std::endl;
        }
    } while (choice != 6);

    return 0;
}
