// // Să se creeze tipul abstract de date (structura) – fişier, care are denumire, data şi timpul creării şi dimensiunea.
// Să se definească funcţiile de setare, de modificare a datelor, de comparare. Pentru crearea cîmpurilor textuale să se utilizeze operatorul new.
// Să se elibereze memoria. În main să se exemplifice sortarea fişierelor după cîteva criterii.

#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

struct Fisier
{
    char *denumire;
    char dataTimp[20];
    int dimensiune;
};

void seteazaFisier(Fisier *fisier, const char *denumire, const char *dataTimp, int dimensiune)
{
    fisier->denumire = new char[strlen(denumire) + 1];
    strcpy(fisier->denumire, denumire);
    strcpy(fisier->dataTimp, dataTimp);
    fisier->dimensiune = dimensiune;
}

void modificaDataTimp(Fisier *fisier, const char *newDataTimp)
{
    strcpy(fisier->dataTimp, newDataTimp);
}

int comparaDenumire(const void *a, const void *b)
{
    return strcmp(((Fisier *)a)->denumire, ((Fisier *)b)->denumire);
}

int comparaDataTimp(const void *a, const void *b)
{
    return strcmp(((Fisier *)a)->dataTimp, ((Fisier *)b)->dataTimp);
}

int comparaDimensiune(const void *a, const void *b)
{
    return ((Fisier *)a)->dimensiune - ((Fisier *)b)->dimensiune;
}

void afiseazaFisier(const Fisier &fisier)
{
    cout << fisier.denumire << " " << fisier.dataTimp << " " << fisier.dimensiune << " KB\n";
}

void afiseazaFisiere(Fisier *fisiere, int numarFisiere)
{
    for (int i = 0; i < numarFisiere; ++i)
    {
        afiseazaFisier(fisiere[i]);
    }
}

void elibereazaMemorie(Fisier *fisier)
{
    delete[] fisier->denumire;
}

int main()
{
    const int numarFisiere = 3;
    Fisier fisiere[numarFisiere];

    seteazaFisier(&fisiere[0], "Fisier3", "16-10-2023 12:30:45", 500);
    seteazaFisier(&fisiere[1], "Fisier1", "15-10-2023 10:20:30", 200);
    seteazaFisier(&fisiere[2], "Fisier2", "16-10-2023 09:15:30", 300);

    int optiune;
    do
    {
        cout << "\nMeniu:\n";
        cout << "1. Afiseaza informatii despre toate fisierele\n";
        cout << "2. Modifica data si timpul unui fisier\n";
        cout << "3. Sortare dupa denumire\n";
        cout << "4. Sortare dupa data si timp\n";
        cout << "5. Sortare dupa dimensiune\n";
        cout << "6. Iesire\n";
        cout << "Introduceti optiunea: ";
        cin >> optiune;

        switch (optiune)
        {
        case 1:
            cout << "Informatii despre toate fisierele:\n";
            afiseazaFisiere(fisiere, numarFisiere);
            break;
        case 2:
        {
            int index;
            cout << "Introduceti indexul fisierului (0, 1 sau 2): ";
            cin >> index;
            if (index >= 0 && index < numarFisiere)
            {
                char newDataTimp[20];
                cout << "Introduceti noua data si timpul (format: dd-mm-yyyy hh:mm:ss): ";
                cin.ignore(); // Ignora newline-ul din buffer
                cin.getline(newDataTimp, 20);
                modificaDataTimp(&fisiere[index], newDataTimp);
                cout << "Data si timpul au fost modificate pentru fisierul " << index << ".\n";
            }
            else
            {
                cout << "Index invalid.\n";
            }
            break;
        }
        case 3:
            qsort(fisiere, numarFisiere, sizeof(Fisier), comparaDenumire);
            cout << "Fisierele au fost sortate dupa denumire.\n";
            afiseazaFisiere(fisiere, numarFisiere);
            break;
        case 4:
            qsort(fisiere, numarFisiere, sizeof(Fisier), comparaDataTimp);
            cout << "Fisierele au fost sortate dupa data si timp.\n";
            afiseazaFisiere(fisiere, numarFisiere);
            break;
        case 5:
            qsort(fisiere, numarFisiere, sizeof(Fisier), comparaDimensiune);
            cout << "Fisierele au fost sortate dupa dimensiune.\n";
            afiseazaFisiere(fisiere, numarFisiere);
            break;
        default:
            cout << "Ati iesit idn program.\n";
        }
    } while (optiune != 6);

    // Eliberare memorie
    for (int i = 0; i < numarFisiere; ++i)
    {
        elibereazaMemorie(&fisiere[i]);
    }

    return 0;
}
