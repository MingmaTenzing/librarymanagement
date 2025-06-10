#ifndef BORROWERINFO_H
#define BORROWERINFO_H

#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

class BorrowerInfo
{
public:
    string borrowerName;
    string studentId;
    string bookId;
    string bookName;
    string category;

    BorrowerInfo();                                                             // Default constructor
    BorrowerInfo(string name, string id, string bId, string bName, string cat); // Only declare
    void displayInfo();                                                         // Only declare
};

#endif
