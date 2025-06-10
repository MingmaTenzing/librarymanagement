#include <iostream>
#include "User.h"
#include "BookManager.h"
#include "BorrowerInfo.h"
using namespace std;

int main()
{
    BookManager bookManager;
    User user;
    int choice;

    while (true)
    {
        cout << "\n+------------------------------------------+";
        cout << "\n|        Library Information System        |";
        cout << "\n+------------------------------------------+\n";
        cout << "1. Administrator Login\n";
        cout << "2. User Registration\n";
        cout << "3. Borrow Book\n";
        cout << "4. Return Book\n";
        cout << "5. View All Books\n";
        cout << "6. Search Book\n";
        cout << "7. Developer Info\n";
        cout << "8. Exit\n";
        cout << "Select option: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            bookManager.managerLogin();
            break;
        case 2:
            user.addUser();
            break;
        case 3:
            user.borrowBook();
            break;
        case 4:
            user.returnBook();
            break;
        case 5:
            user.booksLoad();
            break;
        case 6:
            user.findBook();
            break;
        case 7:
            user.displayDeveloperInfo();
            break;
        case 8:
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}
