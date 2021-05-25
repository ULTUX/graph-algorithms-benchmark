//
// Created by Wladyslaw Nowak on 17.04.2021.
//

#include "./Menu.h"
#include "IO/FileReader.h"

Menu::Menu() {
    printMainMenu();
}

void Menu::printMainMenu() {

    while (true) {
        cout << "Wybierz polecenie: " << endl;
        cout << "\t1. Wczytaj graf z pliku" << endl;
        cout << "\t2. Wyswietl graf" << endl;
        cout << "\t3. Algorytm Kruskala" << endl;
        cout << "\t4. Algorytm Prima" << endl;
        cout << "\t5. Algorytm Dijsktry" << endl;
        cout << "\t6. Algorytm Bellmana-Forda" << endl;
        cout << "\t7. Algorytm Forda-Fulkersona" << endl;
        cout << "\t0. Wylacz program" << endl;
        int input = getIntegerInput("Wybor: ");
        switch (input) {
            case 1: {
                printReadFromFileMenu();
                break;
            }
            case 2: {
                printGraph();
                break;
            }
            case 3: {
                kruskal();
                break;
            }
            case 4: {
                prima();
                break;
            }
            case 5: {
                dijsktra();
                break;
            }
            case 6: {
                bellmanFord();
                break;
            }
            case 7: {
                fordFulkderson();
                break;
            }
            case 0: {
                cout << "Wylaczanie programu..." << endl;
                exit(0);
            }
            default: {
                cout << "Nieznana komenda" << endl;
                break;

            }
        }
    }
}

int Menu::getIntegerInput(string message, bool mustPositive) {
    bool isNum = false;
    bool isPositive = false;
    int val;
    while (!isNum) {
        cout << message;
        string input;
        cin.clear();
        cin.sync();
        getline(cin, input);
        try {
            val = stoi(input);
            if (val > 0) isPositive = true;
            if (!mustPositive) isNum = true;
            else if (isPositive) isNum = true;
            else isNum = false;
        } catch (invalid_argument &e) {
            cout << "Wprowadzone dane nie sa liczba!" << endl;
            continue;
        }
        catch (out_of_range &e) {
            cout << "Wprowadzona liczba jest za duza!" << endl;
            continue;
        }
    }
    return val;
}

float Menu::getFloatInput(string message, bool mustPositive) {
    bool isNum = false;
    bool isPositive = false;
    float val;
    while (!isNum) {
        cout << message;
        string input;
        cin.clear();
        cin.sync();
        getline(cin, input);
        try {
            val = stof(input);
            if (val > 0) isPositive = true;
            if (!mustPositive) isNum = true;
            else if (isPositive) isNum = true;
            else isNum = false;
        } catch (invalid_argument &e) {
            cout << "Wprowadzone dane nie sa liczba!" << endl;
            continue;
        }
        catch (out_of_range &e) {
            cout << "Wprowadzona liczba jest za duza!" << endl;
            continue;
        }
    }
    return val;
}

void Menu::printException(exception &e) {
    cout << "-------------------------------\n";
    cout << endl << endl << "UWAGA: Wystapil blad: ";
    cerr << e.what() << "\n\n\n";
    cout << "-------------------------------\n";
}

void Menu::printReadFromFileMenu() {
    string fileName;
    cout<<"Prosze podac nazwe pliku: ";
    cin>>fileName;
    cout<<"Wczytywanie danych z pliku...";
    try {
        FileReader reader(fileName);
        listRep = new ListRepresentation(0, 0, 0, 0, true);
        reader.readToAdjList(listRep);

        FileReader reader2(fileName);
        matrixRep = new MatrixRepresentation(0, 0, 0, 0, true);
        reader2.readToAdjMatrix(matrixRep);
    } catch (runtime_error& e){
        printException(e);
        return;
    }

    cout<<"Dane wczytane pomyslnie."<<endl;
    printGraph();
}

void Menu::printGraph() {
    cout<<"Representacja macierzowa: "<<endl;
    matrixRep->print();
    cout<<"Reprezentacja listowa: "<<endl;
    listRep->print();
}

void Menu::kruskal() {
    KruskalList klist(0, 0);
    klist.clone(listRep);
    klist.start();

    KruskalMatrix kmatrix(0, 0);
    kmatrix.clone(matrixRep);
    kmatrix.start();
}

void Menu::dijsktra() {
    DijsktraList dlist(0,0, 0);
    dlist.clone(listRep);
    dlist.start();

    DijsktraMatrix dmatrix(0, 0, 0);
    dmatrix.clone(matrixRep);
    dmatrix.start();

}

void Menu::bellmanFord() {
    BellmanFordList bflist(0,0, 0);
    bflist.clone(listRep);
    bflist.start();

    BellmanFordMatrix bfmatrix(0, 0, 0);
    bfmatrix.clone(matrixRep);
    bfmatrix.start();
}

void Menu::fordFulkderson() {
    FordFulkersonList fflist(0, 0, 0, 0);
    fflist.clone(listRep);
    fflist.start();

    FordFulkersonMatrix ffmatrix(0, 0, 0, 0);
    ffmatrix.clone(matrixRep);
    ffmatrix.start();
}

void Menu::prima() {
    PrimsList plist(0, 0);
    plist.clone(listRep);
    plist.start();

    PrimsMatrix pmatrix(0, 0);
    pmatrix.clone(matrixRep);
    pmatrix.start();
}
