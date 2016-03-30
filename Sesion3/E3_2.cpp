#include <fstream>
#include <iostream>
//#include <string>
using namespace std;

int main()
{
    char FileName[20];
    char EmployeeName[40], Address[50], City[20], State[32], ZIPCode[10];

    // 1. Descomenta la siguiente seccion para crear un archivo

    cout << "Enter the Following pieces of information\n";
    cout << "Empl Name: "; cin >> ws;
    cin.getline(EmployeeName, 40);
    cout << "Address:   "; cin >> ws;
    cin.getline(Address, 50);
    cout << "City:      "; cin >> ws;
    cin.getline(City, 20);
    cout << "State:     "; cin >> ws;
    cin.getline(State, 32);
    cout << "ZIP Code:  "; cin >> ws;
    cin.getline(ZIPCode, 10);

    cout << "\nEnter the name of the file you want to create: ";
    cin >> FileName;
    ofstream EmplRecords(FileName, ios::out);

    EmplRecords << EmployeeName << "\n" << Address << "\n" << City << "\n" << State << "\n" << ZIPCode;


    // 2. Descomenta la seccion siguiente para abrir un archivo existente.
/*
    cout << "Enter the name of the file you want to open: ";
    cin >> FileName;

    ifstream EmplRecords(FileName);

    EmplRecords.getline(EmployeeName, 40, '\n');
    EmplRecords.getline(Address, 50);
    EmplRecords.getline(City, 20);
    EmplRecords.getline(State, 32);
    EmplRecords.getline(ZIPCode, 10);

    cout << "\n -=- Employee Information -=-";
    cout << "\nEmpl Name: " << EmployeeName;
    cout << "\nAddress:   " << Address;
    cout << "\nCity:      " << City;
    cout << "\nState:     " << State;
    cout << "\nZIP Code:  " << ZIPCode;
*/

    cout << "\n\n";
    return 0;
}
