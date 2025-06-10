#include "User.h"
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

void User::addUser()
{
    string name, id, password;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter student ID: ";
    cin >> id;
    cout << "Enter password: ";
    cin >> password;

    ifstream in("userInfo.txt");
    string line;
    while (getline(in, line))
    {
        if (line.find(id + ",") != string::npos)
        {
            cout << "Student ID already exists.\n";
            return;
        }
    }
    in.close();

    ofstream out("userInfo.txt", ios::app);
    out << name << "," << id << "," << password << "\n";
    cout << "Registration successful.\n";
    out.close();
}

void User::borrowBook()
{
    string name, id, password;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter student ID: ";
    cin >> id;
    cout << "Enter password: ";
    cin >> password;

    ifstream in("userInfo.txt");
    string line;
    bool found = false;
    while (getline(in, line))
    {
        if (line.find(name + "," + id + "," + password) != string::npos)
        {
            found = true;
            break;
        }
    }
    in.close();

    if (!found)
    {
        cout << "Invalid credentials.\n";
        return;
    }

    string bookID, title, category;
    cout << "Enter Book ID to borrow: ";
    cin >> bookID;

    ifstream booksIn("systemBooks.txt");
    ofstream tempOut("tempBooks.txt");
    bool bookFound = false;

    while (getline(booksIn, line))
    {
        if (line.find(bookID + ",") != string::npos)
        {
            bookFound = true;
            stringstream ss(line);
            getline(ss, bookID, ',');
            getline(ss, title, ',');
            getline(ss, category, ',');
        }
        else
        {
            tempOut << line << endl;
        }
    }
    booksIn.close();
    tempOut.close();
    remove("systemBooks.txt");
    rename("tempBooks.txt", "systemBooks.txt");

    if (bookFound)
    {
        ofstream borrowOut("borrowerInfo.txt", ios::app);
        borrowOut << name << "," << id << "," << bookID << "," << title << "," << category << "\n";
        cout << "Book borrowed successfully.\n";
        borrowOut.close();
    }
    else
    {
        cout << "Book ID not found.\n";
    }
}

void User::returnBook()
{
    string name, id, password;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter student ID: ";
    cin >> id;
    cout << "Enter password: ";
    cin >> password;

    ifstream in("userInfo.txt");
    string line;
    bool found = false;
    while (getline(in, line))
    {
        if (line.find(name + "," + id + "," + password) != string::npos)
        {
            found = true;
            break;
        }
    }
    in.close();
    if (!found)
    {
        cout << "Invalid user.\n";
        return;
    }

    vector<string> lines;
    ifstream borrowIn("borrowerInfo.txt");
    bool hasBorrowed = false;
    string returnBookID, savedTitle, savedCat;

    while (getline(borrowIn, line))
    {
        if (line.find(name + "," + id + ",") != string::npos)
        {
            hasBorrowed = true;
            stringstream ss(line);
            string temp;
            getline(ss, temp, ','); // name
            getline(ss, temp, ','); // id
            getline(ss, returnBookID, ',');
            getline(ss, savedTitle, ',');
            getline(ss, savedCat, ',');
            continue;
        }
        lines.push_back(line);
    }
    borrowIn.close();

    if (!hasBorrowed)
    {
        cout << "You have no borrowed books.\n";
        return;
    }

    ofstream borrowOut("borrowerInfo.txt");
    for (string l : lines)
        borrowOut << l << endl;
    borrowOut.close();

    ofstream bookOut("systemBooks.txt", ios::app);
    bookOut << returnBookID << "," << savedTitle << "," << savedCat << endl;
    bookOut.close();

    cout << "Book returned successfully.\n";
}

void User::booksLoad()
{
    ifstream in("systemBooks.txt");
    string id, title, cat;
    cout << left << setw(15) << "Book ID" << setw(30) << "Title" << setw(20) << "Category" << endl;
    while (getline(in, id, ','))
    {
        getline(in, title, ',');
        getline(in, cat);
        cout << left << setw(15) << id << setw(30) << title << setw(20) << cat << endl;
    }
    in.close();
}

void User::findBook()
{
    string keyword;
    cout << "Enter book ID or title to search: ";
    cin >> keyword;
    ifstream in("systemBooks.txt");
    string line;
    while (getline(in, line))
    {
        if (line.find(keyword) != string::npos)
        {
            cout << "Found: " << line << endl;
            return;
        }
    }
    cout << "Book not found.\n";
    in.close();
}

void User::displayDeveloperInfo()
{
    cout << "\nDeveloper: Mingma Tenzing Sherpa\n";
    cout << "Student ID: 202471178\n";
    cout << "Contact: 0420639689\n";
    cout << "Completed: June 2025\n";
}
