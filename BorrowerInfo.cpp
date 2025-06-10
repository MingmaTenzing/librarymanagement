#include "BorrowerInfo.h"

BorrowerInfo::BorrowerInfo(string name, string id, string bId, string bName, string cat)
{
    borrowerName = name;
    studentId = id;
    bookId = bId;
    bookName = bName;
    category = cat;
}

void BorrowerInfo::displayInfo()
{
    cout << left << setw(15) << borrowerName
         << setw(15) << studentId
         << setw(15) << bookId
         << setw(30) << bookName
         << setw(20) << category << endl;
}
