/////// LET'S DO THIS!
/// TODO: show contact list after modification or deletion
/// TODO: make a proper system("cls") across all functions
/// TODO: modularize read and write into functions

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

string filePath = "contacts.bin";

ofstream output;
ifstream input;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

struct Contact {
    string firstName;
    string lastName;
    string gender;
    string phoneNumber;
    int id;
};

void printMenu() {
    system("cls");
    cout << "8888888b.  888    888  .d88888b.  888b    888 8888888888 888888b.    .d88888b.   .d88888b.  888    d8P  \n"
            "888   Y88b 888    888 d88P\" \"Y88b 8888b   888 888        888  \"88b  d88P\" \"Y88b d88P\" \"Y88b 888   d8P   \n"
            "888    888 888    888 888     888 88888b  888 888        888  .88P  888     888 888     888 888  d8P    \n"
            "888   d88P 8888888888 888     888 888Y88b 888 8888888    8888888K.  888     888 888     888 888d88K     \n"
            "8888888P\"  888    888 888     888 888 Y88b888 888        888  \"Y88b 888     888 888     888 8888888b    \n"
            "888        888    888 888     888 888  Y88888 888        888    888 888     888 888     888 888  Y88b   \n"
            "888        888    888 Y88b. .d88P 888   Y8888 888        888   d88P Y88b. .d88P Y88b. .d88P 888   Y88b  \n"
            "888        888    888  \"Y88888P\"  888    Y888 8888888888 8888888P\"   \"Y88888P\"   \"Y88888P\"  888    Y88b \n";
    cout << string(3, '\n');
    cout << "1) View all contacts\n2) Search for a contact\n3) Add a new contact\n4) Modify existing contact\n5) Delete existing contact\n6) Import contacts from another file\n7) Fuzzy Search";
}

void printIndividualContact(Contact c) {
    cout << string(30, '-') << endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    cout << "ID: ";
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << string(3, ' ') << c.id << endl;
    cout << string(30, '-') << endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    cout << "First Name: ";
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout <<  c.firstName;
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    cout << "\nLast Name: ";
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << c.lastName;
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    cout << "\nGender: ";
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << c.gender;
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    cout << "\nPhone Number: ";
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << c.phoneNumber << endl;
    cout << string(30, '-') << "\n\n";
}

void coloredErrorMessage(string errorMessage) {
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    cout << errorMessage << endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

// Function to handle errors when opening a file
bool openFile(ifstream &file, const string &fileName) {
    file.open(fileName, ios::binary);
    if (!file) {
        coloredErrorMessage("Error opening file for reading: " + fileName);
        return false;
    }
    return true;
}

// Function to handle errors when opening a file for writing
bool openFileForWriting(ofstream &file, const string &fileName) {
    file.open(fileName, ios::binary | ios::app);
    if (!file) {
        coloredErrorMessage("Error opening file for writing: " + fileName);
        return false;
    }
    return true;
}

// Function to read a contact from the binary file
bool readContact(ifstream &file, Contact &contact) {
    char ch;
    contact = {};

    while (file.get(ch) && ch != '\0') {
        contact.firstName += ch;
    }
    while (file.get(ch) && ch != '\0') {
        contact.lastName += ch;
    }
    while (file.get(ch) && ch != '\0') {
        contact.gender = ch;
    }
    while (file.get(ch) && ch != '\0') {
        contact.phoneNumber += ch;
    }

    return !contact.firstName.empty() || !contact.lastName.empty();
}

bool verifyNames(string name) {
    for (int i = 0; i < name.length(); i++) {
        if (!isalpha(name[i]) || name.empty()) {
            return false;
        }
    }

    return true;
}

bool verifyGender(char gender) {
    if (gender == 'M' || gender == 'm' || gender == 'F' || gender == 'f') {
        return true;
    } else {
        return false;
    }
}

bool verifyPhoneNumber(string number) {
    for (int i = 0; i < number.length(); i++) {
        if (!isdigit(number[i]) || number.empty()) {
            return false;
        }
    }
    return true;
}

// Function to display all contacts
void displayContacts() {
    system("cls");
    if (!openFile(input, filePath)) {
        return;
    }

    int id = 1;
    Contact contact;
    bool found = false;

    while (readContact(input, contact)) {
        contact.id = id;
        found = true;
        printIndividualContact(contact);
        id++;
    }

    if (!found) {
        coloredErrorMessage("No contacts found");
    }

    input.close();
}

// Function to search for a contact by first name
void searchContact() {
    if (!openFile(input, filePath)) {
        return;
    }

    system("cls");

    string fname, lname;
    cout << "Enter first name: ";
    cin.ignore();
    getline(cin, fname);

    cout << "Enter last name: ";
    getline(cin, lname);

    int id = 1;
    Contact contact;
    bool found = false;

    while (readContact(input, contact)) {
        contact.id = id;
        if (!contact.firstName.empty() && contact.firstName == fname && contact.lastName == lname) {
            found = true;
            printIndividualContact(contact);
        }
        id++;
    }

    if (!found) {
        coloredErrorMessage("No contacts found");
    }

    input.close();
}

// Function to add a contact to the binary file
void addContact() {
    if (!openFileForWriting(output, filePath)) {
        return;
    }

    Contact contact;

    firstNameEntry: cout << "Enter First Name: ";
    cin.ignore();
    getline(cin, contact.firstName);
    if(!verifyNames(contact.firstName)) {
        coloredErrorMessage("First name is invalid, try again");
        goto firstNameEntry;
    }

    lastNameEntry: cout << "Enter Last Name: ";
    getline(cin, contact.lastName);
    if(!verifyNames(contact.lastName)) {
        coloredErrorMessage("Last name is invalid, try again");
        goto lastNameEntry;
    }

    genderEntry: cout << "Enter Gender: ";
    cin >> contact.gender;
    if(!verifyGender(contact.gender[0])) {
        coloredErrorMessage("Invalid gender, try again");
        goto genderEntry;
    }

    phoneEntry: cout << "Enter Phone Number: ";
    cin >> contact.phoneNumber;
    if(!verifyGender(contact.gender[0])) {
        coloredErrorMessage("Invalid phone number, try again");
        goto phoneEntry;
    }

    output.write(&contact.firstName[0], contact.firstName.length() + 1);
    output.write(&contact.lastName[0], contact.lastName.length() + 1);
    output.write(&contact.gender[0], contact.gender.length() + 1);
    output.write(&contact.phoneNumber[0], contact.phoneNumber.length() + 1);

    output.close();
    cout << "Contact added successfully.\nIf you want to add more contacts press [Y] press any other key to exit registration" << endl;
    char choice;
    cin >> choice;
    if (choice == 'Y' || choice == 'y') {
        addContact();
    }
}

// Function to modify an existing contact
void modifyContact() {
    if (!openFile(input, filePath)) {
        return;
    }

    int idInput;
    cout << "Enter ID: ";
    cin >> idInput;

    int id = 1;
    int totalCharCount = 0;
    int contactCharCount = 0;
    bool found = false;
    Contact contact;
    int contentAfterStart, contentAfterEnd, contentBeforeStart, contentBeforeEnd;

    while (!input.eof()) {
        contact = {};
        contactCharCount = 0;
        char ch;

        contact.id = id;
        while (input.get(ch) && ch != '\0') {
            contact.firstName += ch;
            totalCharCount++;
            contactCharCount++;
        }
        contactCharCount++;

        while (input.get(ch) && ch != '\0') {
            contact.lastName += ch;
            totalCharCount++;
            contactCharCount++;
        }
        contactCharCount++;

        while (input.get(ch) && ch != '\0') {
            contact.gender = ch;
            totalCharCount++;
            contactCharCount++;
        }
        contactCharCount++;


        while (input.get(ch) && ch != '\0') {
            contact.phoneNumber += ch;
            totalCharCount++;
            contactCharCount++;
        }
        contactCharCount++;

            if (contact.id == idInput) {
                found = true;
                int foundIndex = input.tellg();
                contentBeforeStart = 0;
                contentBeforeEnd = (int)input.tellg() - contactCharCount;
                contentAfterStart = input.tellg();
                input.seekg(0, ios::end);
                contentAfterEnd = input.tellg();
                input.seekg(foundIndex, ios::beg);
                break;

            }
        id++;
    }

    if (found) {

        /// Store the string that is found before the content to be edited in a variable, Store the string that is found after the content to be edited in a variable, concatenate the three based on order, write it to a file by overwriting

        string contentBefore, contentAfter;

        for (int i = contentAfterStart; i < contentAfterEnd; i++) {
            char c;
            input.get(c);
            cout << (int)c << " ";
            contentAfter += c;
        }

        input.seekg(0, ios::beg);
//
        for (int i = contentBeforeStart; i < contentBeforeEnd; i++) {
            char c;
            input.get(c);
            cout << (int)c << " ";
            contentBefore += c;
        }

        int choice;
        cout << "Select the field to modify:" << endl;
        cout << "1. First Name" << endl;
        cout << "2. Last Name" << endl;
        cout << "3. Gender" << endl;
        cout << "4. Phone Number" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the new First Name: ";
                getline(cin.ignore(), contact.firstName);
                break;
            case 2:
                cout << "Enter the new Last Name: ";
                getline(cin, contact.lastName);

                break;
            case 3:
                cout << "Enter the new Gender: ";
                cin >> contact.gender;

                break;
            case 4:
                cout << "Enter the new Phone Number: ";
                getline(cin, contact.phoneNumber);

                break;
            default:
                coloredErrorMessage("Invalid choice.");
                break;
        }

        ofstream opFile(filePath, ios::binary);

        opFile.write(&contentBefore[0], contentBefore.length());
        opFile.write(&contact.firstName[0], contact.firstName.length() + 1);
        opFile.write(&contact.lastName[0], contact.lastName.length() + 1);
        opFile.write(&contact.gender[0], contact.gender.length() + 1);
        opFile.write(&contact.phoneNumber[0], contact.phoneNumber.length() + 1);
        opFile.write(&contentAfter[0], contentAfter.length());
        opFile.close();
        cout << "Contact modified successfully.\n If you want to continue modifying contacts click [Y] else click any other key: ";
        char continueChoice;

        cin >> continueChoice;
        if (continueChoice == 'Y' || continueChoice == 'y') {
            modifyContact();
        }
    } else {
        coloredErrorMessage("Contact not found.");
    }

    input.close();
}

// Function to delete an existing contact
void deleteContact() {
    if (!openFile(input, filePath)) {
        return;
    }

    int idInput;
    cout << "Enter ID: ";
    cin >> idInput;

    int id = 1;
    int totalCharCount = 0;
    int contactCharCount = 0;
    bool found = false;
    Contact contact;
    int contentAfterStart, contentAfterEnd, contentBeforeStart, contentBeforeEnd;

    while (!input.eof()) {
        contact = {};
        contactCharCount = 0;
        char ch;

        contact.id = id;
        while (input.get(ch) && ch != '\0') {
            contact.firstName += ch;
            totalCharCount++;
            contactCharCount++;
        }
        contactCharCount++;

        while (input.get(ch) && ch != '\0') {
            contact.lastName += ch;
            totalCharCount++;
            contactCharCount++;
        }
        contactCharCount++;

        while (input.get(ch) && ch != '\0') {
            contact.gender = ch;
            totalCharCount++;
            contactCharCount++;
        }
        contactCharCount++;


        while (input.get(ch) && ch != '\0') {
            contact.phoneNumber += ch;
            totalCharCount++;
            contactCharCount++;
        }
        contactCharCount++;

        cout << "Id temp: " << id << " Id contact: " << contact.id << endl;
        if (contact.id == idInput) {
            found = true;
            int foundIndex = input.tellg();
            contentBeforeStart = 0;
            contentBeforeEnd = (int)input.tellg() - contactCharCount;
            contentAfterStart = input.tellg();
            input.seekg(0, ios::end);
            contentAfterEnd = input.tellg();
            input.seekg(foundIndex, ios::beg);
            break;
        }
        id++;
    }

    if (found) {

        /// Store the string that is found before the content to be edited in a variable, Store the string that is found after the content to be edited in a variable, concatenate the three based on order, write it to a file by overwriting

        string contentBefore, contentAfter;

        for (int i = contentAfterStart; i < contentAfterEnd; i++) {
            char c;
            input.get(c);
            cout << (int)c << " ";
            contentAfter += c;
        }
        input.seekg(0, ios::beg);
//
        for (int i = contentBeforeStart; i < contentBeforeEnd; i++) {
            char c;
            input.get(c);
            cout << (int)c << " ";
            contentBefore += c;
        }

        char choice;
        cout << "Click [Y] if you want to delete:" << endl;
        cin >> choice;

        if (choice == 'Y' || choice == 'y') {
            ofstream opFile(filePath);
            opFile.write(&contentBefore[0], contentBefore.length());
            opFile.write(&contentAfter[0], contentAfter.length());
            opFile.close();
            cout << "Contact deleted successfully." << endl;
        } else {
            return;
        }
    } else {
        coloredErrorMessage("Contact not found.");
    }

    input.close();
}

void importContacts() {
    string externalFilePath;
    Contact contact;
    cout << "Enter the absolute path of the contact file: ";
    getline(cin.ignore(), externalFilePath);

    input.open(externalFilePath, ios::binary);


    if (!input) {
        coloredErrorMessage("The file specified doesn't exist");
        return;
    } else {
        output.open(filePath, ios::app | ios::binary);

        cout << "File found!\n";
        int totalContactCount = 0;
        while (readContact(input, contact)) {
            output.write(&contact.firstName[0], contact.firstName.length() + 1);
            output.write(&contact.lastName[0], contact.lastName.length() + 1);
            output.write(&contact.gender[0], contact.gender.length() + 1);
            output.write(&contact.phoneNumber[0], contact.phoneNumber.length() + 1);

            totalContactCount++;
        }
        input.close();
        output.close();

        if (totalContactCount >= 1) {
            cout << "Contacts added successfully!\nTotal contacts added: " << totalContactCount << endl;
        } else {
            coloredErrorMessage("No contacts added");
        }
    }
}

void searchByPhoneNumber() {
    if (!openFile(input, filePath)) {
        return;
    }

    string phoneNumber;
    cout << "Enter phone number: ";
    cin.ignore();
    getline(cin, phoneNumber);

    int id = 1;
    Contact contact;
    bool found = false;

    while (readContact(input, contact)) {
        contact.id = id;
        if (!contact.firstName.empty() && contact.phoneNumber == phoneNumber) {
            found = true;
            printIndividualContact(contact);
        }
        id++;
    }

    if (!found) {
        coloredErrorMessage("No contacts found");
    }

    input.close();
}

void fuzzySearch() {

    system("cls");
    if (!openFile(input, filePath)) {
        return;
    }

    string fname, lname, combined;
    int nameLength;

    cout << "Enter first name: ";
    getline(cin.ignore(), fname);

    cout << "Enter last name: ";
    getline(cin, lname);

    combined = fname + lname;

    int id = 1;
    Contact contact;
    bool found = false;

    string dividedName;
    nameLength = combined.length() / 4;

    if (nameLength <= 0) {
        dividedName = combined;
    } else {
        for (int i = 0; i < nameLength; i++) {
            string part = combined.substr(i * 4, 4);
            dividedName += part.append(" ");
        }
    }

    while (readContact(input, contact)) {
        string tempName = dividedName;
        contact.id = id;
        string base = contact.firstName + contact.lastName;

        while (tempName.length() >= 3) {
            unsigned int spacePos = tempName.find(' ');
            string temp = tempName.substr(0, spacePos);
            int foundPosition = base.find(temp);
            if (foundPosition > base.length()) {
                continue;
            } else {
                found = true;
                printIndividualContact(contact);
                break;
            }
            tempName = tempName.substr(spacePos + 1);
        }
        id++;
    }

    if (!found) {
        coloredErrorMessage("No contacts found");
    }

    input.close();
}

void advancedSearch() {
    cout << "[1] Search by phone number\n";
    cout << "[2] Fuzzy search\n";
    cout << "[3] Combination search\n";


}

int main() {
    SetConsoleTitle("Phonebook App");
    bool navigating = true;
    int menuChoice;

    while (navigating) {
        printMenu();
        cin >> menuChoice;

        switch (menuChoice) {
            case 1:
                displayContacts();
                break;
            case 2:
                searchContact();
                break;
            case 3:
                addContact();
                break;
            case 4:
                modifyContact();
                break;
            case 5:
                deleteContact();
                break;
            case 6:
                importContacts();
                break;
            case 7:
                fuzzySearch();
                break;
            default:
                coloredErrorMessage("Invalid option.");
        }

        char choice;
        cout << "If you want to continue using the app, press [Y]; otherwise, press any key: ";
        cin >> choice;

        if (choice != 'Y' && choice != 'y') {
            navigating = false;
        }
    }

    return 0;
}

