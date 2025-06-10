#include "BookManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

void BookManager::managerLogin()
{
    string name, pass;
    cout << "Enter administrator name: ";
    cin >> name;
    cout << "Enter password: ";
    cin >> pass;

    ifstream in("ManagerData.txt");

    if (!in.is_open())
    {
        cout << "not openeing";
    }
    string line;
    bool valid = false;
    while (getline(in, line))
    {

        if (line == name + "," + pass + ",")
        {
            valid = true;

            break;
        }
    }
    in.close();

    if (!valid)
    {
        cout << "Invalid credentials.\n";
        return;
    }

    int choice;
    cout << "\n1. Add Book\n2. Remove Book\n3. View Borrowed Books\nSelect option: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        addBook();
        break;
    case 2:
        removeBook();
        break;
    case 3:
        viewBorrowedBooks();
        break;
    default:
        cout << "Invalid option.\n";
    }
}

void BookManager::addBook()
{
    string id, title, category;
    cout << "Enter Book ID: ";
    cin >> id;
    cout << "Enter Title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter Category: ";
    getline(cin, category);

    ifstream in("systemBooks.txt");
    string line;
    while (getline(in, line))
    {
        if (line.find(id + ",") != string::npos)
        {
            cout << "Book ID already exists.\n";
            return;
        }
    }
    in.close();

    ofstream out("systemBooks.txt", ios::app);
    out << id << "," << title << "," << category << endl;
    cout << "Book added successfully.\n";
    out.close();
}

void BookManager::removeBook()
{
    string id;
    cout << "Enter Book ID to remove: ";
    cin >> id;

    ifstream in("systemBooks.txt");
    ofstream out("tempBooks.txt");
    string line;
    bool removed = false;

    while (getline(in, line))
    {
        if (line.find(id + ",") != string::npos)
        {
            removed = true;
            continue;
        }
        out << line << endl;
    }
    in.close();
    out.close();
    remove("systemBooks.txt");
    rename("tempBooks.txt", "systemBooks.txt");

    cout << (removed ? "Book removed.\n" : "Book ID not found.\n");
}

void BookManager::viewBorrowedBooks()
{
    ifstream in("borrowerInfo.txt");
    string name, id, bookID, title, category;
    cout << left << setw(15) << "Name" << setw(15) << "Student ID" << setw(15) << "Book ID"
         << setw(30) << "Title" << setw(20) << "Category" << endl;

    string line;
    while (getline(in, line))
    {
        stringstream ss(line);
        getline(ss, name, ',');
        getline(ss, id, ',');
        getline(ss, bookID, ',');
        getline(ss, title, ',');
        getline(ss, category);

        cout << left << setw(15) << name << setw(15) << id << setw(15) << bookID
             << setw(30) << title << setw(20) << category << endl;
    }
    in.close();
}
