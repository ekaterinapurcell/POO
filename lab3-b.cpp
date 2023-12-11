// b) Să se creeze clasa List – coadă. Să se definească operatorii "+" – de adunare a listelor, "-" – de scădere( ca la mulţimi) ca funcţii prietene.
// Să se definească operatorii de comparare "==", "!=", "<", ">" ca metode ale clasei.
// Să se supraîncarce operatorii "<<" şi ">>" pentru ieşiri/intrări de obiecte, precum şi pentru inserarea/eliminarea elementelor în/din coadă.
// Clasa trebuie să fie absolut funcţională, adică să conţină toţi constructorii necesari şi destructorul.
// Pentru simplificarea lucrului să se utilizeze clasa sau structura ListItem pentru reprezentarea elementelor listei spre care referă List.

#include <iostream>
#include <locale>

using namespace std;

struct ListItem
{
    int data;
    ListItem *next;

    ListItem(int val) : data(val), next(nullptr) {}
};

class List
{
private:
    ListItem *front;
    ListItem *rear;

public:
    List() : front(nullptr), rear(nullptr) {}

    ~List()
    {
        while (front != nullptr)
        {
            ListItem *temp = front;
            front = front->next;
            delete temp;
        }
        rear = nullptr;
    }

    List operator+(const List &other) const
    {
        List result = *this;
        ListItem *currentOther = other.front;

        while (currentOther != nullptr)
        {
            result.push(currentOther->data);
            currentOther = currentOther->next;
        }

        return result;
    }

    List operator-(const List &other) const
    {
        List result;
        ListItem *currentThis = front;
        ListItem *currentOther = other.front;

        while (currentThis != nullptr)
        {
            bool foundInOther = false;
            while (currentOther != nullptr)
            {
                if (currentThis->data == currentOther->data)
                {
                    foundInOther = true;
                    break;
                }
                currentOther = currentOther->next;
            }

            if (!foundInOther)
            {
                result.push(currentThis->data);
            }

            currentThis = currentThis->next;
            currentOther = other.front;
        }

        return result;
    }

    bool operator==(const List &other) const
    {
        ListItem *currentThis = front;
        ListItem *currentOther = other.front;

        while (currentThis != nullptr && currentOther != nullptr)
        {
            if (currentThis->data != currentOther->data)
            {
                return false;
            }

            currentThis = currentThis->next;
            currentOther = currentOther->next;
        }

        return (currentThis == nullptr && currentOther == nullptr);
    }

    bool operator!=(const List &other) const
    {
        return !(*this == other);
    }

    bool operator<(const List &other) const
    {
        ListItem *currentThis = front;
        ListItem *currentOther = other.front;

        while (currentThis != nullptr && currentOther != nullptr)
        {
            if (currentThis->data < currentOther->data)
            {
                return true;
            }
            else if (currentThis->data > currentOther->data)
            {
                return false;
            }

            currentThis = currentThis->next;
            currentOther = currentOther->next;
        }

        return (currentThis == nullptr && currentOther != nullptr);
    }

    bool operator>(const List &other) const
    {
        return !(*this < other || *this == other);
    }

    friend ostream &operator<<(ostream &os, const List &lista)
    {
        ListItem *current = lista.front;
        while (current != nullptr)
        {
            os << current->data << " ";
            current = current->next;
        }
        return os;
    }

    friend istream &operator>>(istream &is, List &lista)
    {
        int val;
        cout << "Introduceti elementele listei (0 pentru a incheia, separati cu spatiu): ";
        while (true)
        {
            is >> val;
            if (val == 0)
            {
                break;
            }
            lista.push(val);
        }
        return is;
    }

    void push(int val)
    {
        ListItem *newItem = new ListItem(val);
        if (rear == nullptr)
        {
            front = rear = newItem;
        }
        else
        {
            rear->next = newItem;
            rear = newItem;
        }
    }

    void pop()
    {
        if (front != nullptr)
        {
            ListItem *temp = front;
            front = front->next;
            delete temp;

            if (front == nullptr)
            {
                rear = nullptr;
            }
        }
    }
};

int main()
{

    List lista1, lista2;

    cout << "Introduceti elementele primei liste:\n";
    cin >> lista1;

    cout << "Introduceti elementele celei de-a doua liste:\n";
    cin >> lista2;

    List sumaListelor = lista1 + lista2;
    cout << "Suma listelor: " << sumaListelor << "\n";

    List diferentaListelor = lista1 - lista2;
    cout << "Diferenta listelor: " << diferentaListelor << "\n";

    if (lista1 == lista2)
    {
        cout << "Listele sunt egale.\n";
    }
    else
    {
        cout << "Listele nu sunt egale.\n";
    }

    return 0;
}
