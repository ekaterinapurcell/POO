//  Să se creeze tipul abstract de date (structura) – vector, care are pointer spre float şi numărul de elemente.
// Să se definească funcţiile de iniţializare, de eliminare a vectorului, de setare/modificare a dimensiunii, de acces la elementele vectorului, de calcul a sumei elementelor pare ale vectorului.
// Ca exemplu, în funcţia main, să se realizeze căutarea poziţiei elementului minimal al vectorului

#include <iostream>

using namespace std;

struct Vector
{
    float *elemente;
    int dimensiune;
};

void initializeazaVector(Vector &vector, int dimensiune)
{
    vector.dimensiune = dimensiune;
    vector.elemente = new float[dimensiune];
    for (int i = 0; i < dimensiune; ++i)
    {
        vector.elemente[i] = 0.0f;
    }
}

void eliminaVector(Vector &vector)
{
    delete[] vector.elemente;
    vector.dimensiune = 0;
}

void seteazaElement(Vector &vector, int pozitie, float valoare)
{
    if (pozitie >= 0 && pozitie < vector.dimensiune)
    {
        vector.elemente[pozitie] = valoare;
    }
    else
    {
        cout << "Pozitie invalida.\n";
    }
}

float acceseazaElement(Vector &vector, int pozitie)
{
    if (pozitie >= 0 && pozitie < vector.dimensiune)
    {
        return vector.elemente[pozitie];
    }
    else
    {
        cout << "Pozitie invalida.\n";
        return 0.0f;
    }
}

float calculeazaSumaElementelorPare(Vector &vector)
{
    float suma = 0;
    for (int i = 0; i < vector.dimensiune; ++i)
    {
        if (static_cast<int>(vector.elemente[i]) % 2 == 0)
        {
            suma += vector.elemente[i];
        }
    }
    return suma;
}

int gasesteElementMinim(Vector &vector)
{
    int pozitieMinim = 0;

    for (int i = 1; i < vector.dimensiune; ++i)
    {
        if (vector.elemente[i] < vector.elemente[pozitieMinim])
        {
            pozitieMinim = i;
        }
    }

    return pozitieMinim;
}

int main()
{
    int dimensiune;

    cout << "Introduceti dimensiunea vectorului: ";
    cin >> dimensiune;

    Vector vector;
    initializeazaVector(vector, dimensiune);

    cout << "Introduceti " << dimensiune << " valori pentru vector:\n";
    for (int i = 0; i < dimensiune; ++i)
    {
        float valoare;
        cout << "Elementul " << i << ": ";
        cin >> valoare;
        seteazaElement(vector, i, valoare);
    }

    int pozitieMinim = gasesteElementMinim(vector);
    cout << "Elementul minim este " << acceseazaElement(vector, pozitieMinim) << " de pe pozitia " << pozitieMinim << endl;

    float sumaElementePare = calculeazaSumaElementelorPare(vector);
    cout << "Suma elementelor pare din vector este: " << sumaElementePare << endl;

    eliminaVector(vector);

    return 0;
}
