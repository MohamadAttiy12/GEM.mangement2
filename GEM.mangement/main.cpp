#include <iostream>
#include "MembersPage.h"
#include "CoachesPage.h"
#include "FinancePage.h"

bool login() {
    Theme::header("LOGIN SYSTEM");
    std::string user, pass;
    std::cout << "Username: "; std::cin >> user;
    std::cout << "Password: "; std::cin >> pass;
    return (user == "admin" && pass == "123"); 
}

int main() {
    if (!login()) {
        Theme::setColor(12);
        std::cout << "Access Denied!\n";
        return 0;
    }

    int choice;
    MembersPage mPage;
    CoachesPage cPage;
    FinancePage fPage;

    while (true) {
        Theme::header("GMS MAIN DASHBOARD");
        std::cout << "1. Members Management\n";
        std::cout << "2. Trainers Management\n";
        std::cout << "3. Financial Records\n";
        std::cout << "0. Exit\n";
        std::cout << "\nChoice: ";
        std::cin >> choice;

        if (choice == 1) mPage.display();
        else if (choice == 2) cPage.display();
        else if (choice == 3) fPage.display();
        else if (choice == 0) break;
    }
    return 0;
}