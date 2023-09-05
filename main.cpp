/////// LET'S DO THIS!
//#include <iostream>
//#include <fstream>
//
//using namespace std;
//
//ifstream input;
//ofstream output;
//
//string filePath = "../contacts.bin";
//
//struct Contact {
//    string firstName;
//    string lastName;
//    string gender;
//    string phoneNumber;
//    int id;
//};
//
//void menuDisplay() {
//
//}
//
//// Function to write a contact to a binary file
//void addContact(Contact contact[]) {
//    output.open(filePath, ios::binary | ios::app);
//    if (!output) {
//        cout << "Error opening file for writing." << endl;
//        return;
//    }
//    for (int i = 0; i < 6; i++) {
//        output.write(&contact[i].firstName[0], contact[i].firstName.length() + 1);
//        output.write(contact[i].lastName.c_str(), contact[i].lastName.length() + 1);
//        output.write(&contact[i].gender[0], contact[i].gender.length() + 1);
//        output.write(contact[i].phoneNumber.c_str(), contact[i].phoneNumber.length() + 1);
//    }
//
//    output.close();
//}
//
//// Function to read contact data from a binary file
//void displayContacts() {
//    input.open(filePath, ios::binary);
//    if (!input) {
//        cout << "Error opening file for reading." << endl;
//        return;
//    }
//
//    int id = 1;
//    Contact contact;
//    bool found = false;
//
//    while (!input.eof()) {
//        contact = {};
//        char ch;
//        while (input.get(ch) && ch != '\0') {
//            contact.firstName += ch;
//        }
//
//        while (input.get(ch) && ch != '\0') {
//            contact.lastName += ch;
//        }
//
//        while (input.get(ch) && ch != '\0') {
//            contact.gender = ch;
//        }
//
//        while (input.get(ch) && ch != '\0') {
//            contact.phoneNumber += ch;
//        }
//
//        contact.id = id;
//        if (!contact.firstName.empty() || !contact.lastName.empty()) {
//            found = true;
//            cout << "ID: " << contact.id << endl;
//            cout << "First Name: " << contact.firstName << endl;
//            cout << "Last Name: " << contact.lastName << endl;
//            cout << "Gender: " << contact.gender << endl;
//            cout << "Phone Number: " << contact.phoneNumber << endl;
//            cout << "------------------------" << endl;
//        }
//
//        id++;
//    }
//
//    if (!found) {
//        cout << "No contacts found\n";
//    }
//
//    input.close();
//}
//
//void searchContact() {
//    string fname, lname;
//    cout << "Enter first name: ";
//    getline(cin.ignore(), fname);
//    cout << "Enter last name: ";
//    getline(cin.ignore(), lname);
//
//    input.open(filePath, ios::binary);
//    if (!input) {
//        cout << "Error opening file for reading." << endl;
//        return;
//    }
//    int id = 1;
//    Contact contact;
//    bool found = false;
//
//    while (!input.eof()) {
//        contact = {};
//        char ch;
//
//        contact.id = id;
//        while (input.get(ch) && ch != '\0') {
//            contact.firstName += ch;
//        }
//
//        while (input.get(ch) && ch != '\0') {
//            contact.lastName += ch;
//        }
//
//        while (input.get(ch) && ch != '\0') {
//            contact.gender = ch;
//        }
//
//        while (input.get(ch) && ch != '\0') {
//            contact.phoneNumber += ch;
//        }
//
//        if (!contact.firstName.empty() || !contact.lastName.empty()) {
//            if (contact.firstName == fname) {
//                found = true;
//                cout << "ID: " << contact.id << endl;
//                cout << "First Name: " << contact.firstName << endl;
//                cout << "Last Name: " << contact.lastName << endl;
//                cout << "Gender: " << contact.gender << endl;
//                cout << "Phone Number: " << contact.phoneNumber << endl;
//                cout << "------------------------" << endl;
//            }
//        }
//        id++;
//    }
//
//    if (!found) {
//        cout << "No contacts found\n";
//    }
//
//    input.close();
//}
//
//void modifyContact() {
//    int idInput;
//    cout << "Enter first name: ";
//    cin >> idInput;
//
//    input.open(filePath, ios::binary);
//
//    if (!input) {
//        cout << "Error opening file for reading." << endl;
//        return;
//    }
//
//    int id = 1;
//    int totalCharCount = 0;
//    int contactCharCount = 0;
//    bool found = false;
//    Contact contact;
//    int contentAfterstart, contentAfterend, contentBeforeStart, contentBeforeEnd;
//
//    while (!input.eof()) {
//        contact = {};
//        contactCharCount = 0;
//        char ch;
//
//        contact.id = id;
//        while (input.get(ch) && ch != '\0') {
//            contact.firstName += ch;
//            totalCharCount++;
//            contactCharCount++;
//        }
//        contactCharCount++;
//
//        while (input.get(ch) && ch != '\0') {
//            contact.lastName += ch;
//            totalCharCount++;
//            contactCharCount++;
//        }
//        contactCharCount++;
//
//        while (input.get(ch) && ch != '\0') {
//            contact.gender = ch;
//            totalCharCount++;
//            contactCharCount++;
//        }
//        contactCharCount++;
//
//
//        while (input.get(ch) && ch != '\0') {
//            contact.phoneNumber += ch;
//            totalCharCount++;
//            contactCharCount++;
//        }
//        contactCharCount++;
//
//            cout << "Id temp: " << id << " Id contact: " << contact.id << endl;
//            if (contact.id == idInput) {
//                cout << "fname: " << contact.firstName << endl;
//                cout << "last: " << contact.lastName << endl;
//                cout << "gender: " << contact.gender << endl;
//                cout << "phone: " << contact.phoneNumber << endl;
//                found = true;
//                cout << "found" << endl;
//                cout << "Before seek: " << input.tellg() << endl;
//                int foundIndex = input.tellg();
//                contentBeforeStart = 0;
//                contentBeforeEnd = (int)input.tellg() - contactCharCount;
//                contentAfterstart = input.tellg();
//                input.seekg(0, ios::end);
//                contentAfterend = input.tellg();
//                input.seekg(foundIndex, ios::beg);
//
//
//                    cout << "Total Char Count: " << totalCharCount << endl;
//                    cout << "Contact char count: " << contactCharCount << endl;
//
//                cout << "Before write: " << input.tellg() << endl;
//                break;
//
//            }
//        id++;
//    }
//
//    if (found) {
//
//        /// Store the string that is found before the content to be edited in a variable, Store the string that is found after the content to be edited in a variable, concatenate the three based on order, write it to a file by overwriting
//
//        string contentBefore, contentAfter;
//
//        for (int i = contentAfterstart; i < contentAfterend; i++) {
//            char c;
//            input.get(c);
//            cout << (int)c << " ";
//            contentAfter += c;
//        }
//        cout << endl << "spacer" << endl;
//        input.seekg(0, ios::beg);
////
//        for (int i = contentBeforeStart; i < contentBeforeEnd; i++) {
//            char c;
//            input.get(c);
//            cout << (int)c << " ";
//            contentBefore += c;
//        }
//
//       cout << "String before: " << contentBefore << endl;
//        cout << "String after: " << contentAfter << endl;
//
//        int choice;
//        cout << "Select the field to modify:" << endl;
//        cout << "1. First Name" << endl;
//        cout << "2. Last Name" << endl;
//        cout << "3. Gender" << endl;
//        cout << "4. Phone Number" << endl;
//        cout << "5. Exit" << endl;
//        cout << "Enter your choice: ";
//        cin >> choice;
//
//        switch (choice) {
//            case 1:
//                cout << "Enter the new First Name: ";
//                getline(cin.ignore(), contact.firstName);
//                break;
//            case 2:
//                cout << "Enter the new Last Name: ";
//                getline(cin, contact.lastName);
//
//                break;
//            case 3:
//                cout << "Enter the new Gender: ";
//                cin >> contact.gender;
//
//                break;
//            case 4:
//                cout << "Enter the new Phone Number: ";
//                getline(cin, contact.phoneNumber);
//
//                break;
//            default:
//                cout << "Invalid choice." << endl;
//                break;
//        }
//
//        ofstream opFile(filePath, ios::binary);
//        cout << "f: " << contact.firstName << endl;
//        cout << "l: " << contact.lastName << endl;
//        cout << "g: " << contact.gender << endl;
//        cout << "p: " << contact.phoneNumber << endl;
//
//
//
//        opFile.write(&contentBefore[0], contentBefore.length());
//        opFile.write(&contact.firstName[0], contact.firstName.length() + 1);
//        opFile.write(&contact.lastName[0], contact.lastName.length() + 1);
//        opFile.write(&contact.gender[0], contact.gender.length() + 1);
//        opFile.write(&contact.phoneNumber[0], contact.phoneNumber.length() + 1);
//        opFile.write(&contentAfter[0], contentAfter.length());
//        opFile.close();
//        cout << "Contact modified successfully." << endl;
//    } else {
//        cout << "Contact not found." << endl;
//    }
//
//    input.close();
//
//}
//
//void deleteContact() {
//    int idInput;
//    cout << "Enter first name: ";
//    cin >> idInput;
//
//    input.open(filePath, ios::binary);
//
//    if (!input) {
//        cout << "Error opening file for reading." << endl;
//        return;
//    }
//
//    int id = 1;
//    int totalCharCount = 0;
//    int contactCharCount = 0;
//    bool found = false;
//    Contact contact;
//    int contentAfterstart, contentAfterend, contentBeforeStart, contentBeforeEnd;
//
//    while (!input.eof()) {
//        contact = {};
//        contactCharCount = 0;
//        char ch;
//
//        contact.id = id;
//        while (input.get(ch) && ch != '\0') {
//            contact.firstName += ch;
//            totalCharCount++;
//            contactCharCount++;
//        }
//        contactCharCount++;
//
//        while (input.get(ch) && ch != '\0') {
//            contact.lastName += ch;
//            totalCharCount++;
//            contactCharCount++;
//        }
//        contactCharCount++;
//
//        while (input.get(ch) && ch != '\0') {
//            contact.gender = ch;
//            totalCharCount++;
//            contactCharCount++;
//        }
//        contactCharCount++;
//
//
//        while (input.get(ch) && ch != '\0') {
//            contact.phoneNumber += ch;
//            totalCharCount++;
//            contactCharCount++;
//        }
//        contactCharCount++;
//
//        cout << "Id temp: " << id << " Id contact: " << contact.id << endl;
//        if (contact.id == idInput) {
//            cout << "fname: " << contact.firstName << endl;
//            cout << "last: " << contact.lastName << endl;
//            cout << "gender: " << contact.gender << endl;
//            cout << "phone: " << contact.phoneNumber << endl;
//            found = true;
//            cout << "found" << endl;
//            cout << "Before seek: " << input.tellg() << endl;
//            int foundIndex = input.tellg();
//            contentBeforeStart = 0;
//            contentBeforeEnd = (int)input.tellg() - contactCharCount;
//            contentAfterstart = input.tellg();
//            input.seekg(0, ios::end);
//            contentAfterend = input.tellg();
//            input.seekg(foundIndex, ios::beg);
//
//
//            cout << "Total Char Count: " << totalCharCount << endl;
//            cout << "Contact char count: " << contactCharCount << endl;
//
//            cout << "Before write: " << input.tellg() << endl;
//            break;
//
//        }
//        id++;
//    }
//
//    if (found) {
//
//        /// Store the string that is found before the content to be edited in a variable, Store the string that is found after the content to be edited in a variable, concatenate the three based on order, write it to a file by overwriting
//
//        string contentBefore, contentAfter;
//
//        for (int i = contentAfterstart; i < contentAfterend; i++) {
//            char c;
//            input.get(c);
//            cout << (int)c << " ";
//            contentAfter += c;
//        }
//        cout << endl << "spacer" << endl;
//        input.seekg(0, ios::beg);
////
//        for (int i = contentBeforeStart; i < contentBeforeEnd; i++) {
//            char c;
//            input.get(c);
//            cout << (int)c << " ";
//            contentBefore += c;
//        }
//
//        cout << "String before: " << contentBefore << endl;
//        cout << "String after: " << contentAfter << endl;
//
//        char choice;
//        cout << "Click [Y] if you want to delete:" << endl;
//        cin >> choice;
//
//        if (choice == 'Y' || choice == 'y') {
//            ofstream opFile(filePath);
//            opFile.write(&contentBefore[0], contentBefore.length());
//            opFile.write(&contentAfter[0], contentAfter.length());
//            opFile.close();
//            cout << "Contact deleted successfully." << endl;
//        } else {
//            return;
//        }
//    } else {
//        cout << "Contact not found." << endl;
//    }
//
//    input.close();
//
//}
//
//
//
//
//int main() {
//
//    bool navigating = true;
//    int menuChoice;
//
//    Contact newContact[6] = {{.firstName = "Beamlak", .lastName = "Aschalew", .gender = "M", .phoneNumber = "0936648802"}, {.firstName = "Beemnet", .lastName = "Aschalew", .gender = "F", .phoneNumber = "0936647712"}, {.firstName = "Adil", .lastName = "Adem", .gender = "M", .phoneNumber = "0960547818"}, {.firstName = "Alazar", .lastName = "Fasil", .gender = "M", .phoneNumber = "0941412578"}, {.firstName = "Edom", .lastName = "Mulugeta", .gender = "F", .phoneNumber = "0920212223"}, {.firstName = "Edlawit", .lastName = "Solomon", .gender = "F", .phoneNumber = "0960127865"}};
//
//    while (navigating) {
//        cout << "1) View all contacts\n2) Search for a contact\n3) Add a new contact\n4) Modify existing contact\n5) Delete existing contact";
//        cin >> menuChoice;
//
//        switch (menuChoice) {
//            case 1: {
//                displayContacts();
//            }
//                break;
//            case 2: {
//               searchContact();
//               break;
//            }
//                break;
//            case 3: {
//                addContact(newContact);
//            }
//                break;
//            case 4: {
//               modifyContact();
//            }
//                break;
//            case 5: {
//               deleteContact();
//            }
//                break;
//            default: cout << "Invalid option.";
//        }
//        char choice;
//        cout << "If you want to continue using the app click [Y] else click any key";
//        cin >> choice;
//
//        if (choice == 'Y' || choice == 'y') {
//            navigating = true;
//        } else {
//            navigating = false;
//        }
//    }
//
//    return 0;
//}
//
//


#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string filePath = "../contacts.bin";

ofstream output;
ifstream input;

struct Contact {
    string firstName;
    string lastName;
    string gender;
    string phoneNumber;
    int id;
};

// Function to handle errors when opening a file
bool openFile(ifstream &file, const string &fileName) {
    file.open(fileName, ios::binary);
    if (!file) {
        cout << "Error opening file for reading: " << fileName << endl;
        return false;
    }
    return true;
}

// Function to handle errors when opening a file for writing
bool openFileForWriting(ofstream &file, const string &fileName) {
    file.open(fileName, ios::binary | ios::app);
    if (!file) {
        cout << "Error opening file for writing: " << fileName << endl;
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

// Function to display all contacts
void displayContacts() {
    if (!openFile(input, filePath)) {
        return;
    }

    int id = 1;
    Contact contact;
    bool found = false;

    while (readContact(input, contact)) {
        contact.id = id;
        found = true;
        cout << "ID: " << contact.id << endl;
        cout << "First Name: " << contact.firstName << endl;
        cout << "Last Name: " << contact.lastName << endl;
        cout << "Gender: " << contact.gender << endl;
        cout << "Phone Number: " << contact.phoneNumber << endl;
        cout << "------------------------" << endl;
        id++;
    }

    if (!found) {
        cout << "No contacts found" << endl;
    }

    input.close();
}

// Function to search for a contact by first name
void searchContact() {
    if (!openFile(input, filePath)) {
        return;
    }

    string fname;
    cout << "Enter first name: ";
    cin.ignore();
    getline(cin, fname);

    int id = 1;
    Contact contact;
    bool found = false;

    while (readContact(input, contact)) {
        contact.id = id;
        if (!contact.firstName.empty() && contact.firstName == fname) {
            found = true;
            cout << "ID: " << contact.id << endl;
            cout << "First Name: " << contact.firstName << endl;
            cout << "Last Name: " << contact.lastName << endl;
            cout << "Gender: " << contact.gender << endl;
            cout << "Phone Number: " << contact.phoneNumber << endl;
            cout << "------------------------" << endl;
        }
        id++;
    }

    if (!found) {
        cout << "No contacts found" << endl;
    }

    input.close();
}

// Function to add a contact to the binary file
void addContact() {
    if (!openFileForWriting(output, filePath)) {
        return;
    }

    Contact contact;
    cout << "Enter First Name: ";
    cin.ignore();
    getline(cin, contact.firstName);
    cout << "Enter Last Name: ";
    getline(cin, contact.lastName);
    cout << "Enter Gender: ";
    cin >> contact.gender;
    cout << "Enter Phone Number: ";
    cin >> contact.phoneNumber;

    output.write(&contact.firstName[0], contact.firstName.length() + 1);
    output.write(contact.lastName.c_str(), contact.lastName.length() + 1);
    output.write(&contact.gender[0], contact.gender.length() + 1);
    output.write(contact.phoneNumber.c_str(), contact.phoneNumber.length() + 1);

    output.close();
    cout << "Contact added successfully." << endl;
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

            cout << "Id temp: " << id << " Id contact: " << contact.id << endl;
            if (contact.id == idInput) {
                cout << "fname: " << contact.firstName << endl;
                cout << "last: " << contact.lastName << endl;
                cout << "gender: " << contact.gender << endl;
                cout << "phone: " << contact.phoneNumber << endl;
                found = true;
                cout << "found" << endl;
                cout << "Before seek: " << input.tellg() << endl;
                int foundIndex = input.tellg();
                contentBeforeStart = 0;
                contentBeforeEnd = (int)input.tellg() - contactCharCount;
                contentAfterStart = input.tellg();
                input.seekg(0, ios::end);
                contentAfterEnd = input.tellg();
                input.seekg(foundIndex, ios::beg);


                    cout << "Total Char Count: " << totalCharCount << endl;
                    cout << "Contact char count: " << contactCharCount << endl;

                cout << "Before write: " << input.tellg() << endl;
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
        cout << endl << "spacer" << endl;
        input.seekg(0, ios::beg);
//
        for (int i = contentBeforeStart; i < contentBeforeEnd; i++) {
            char c;
            input.get(c);
            cout << (int)c << " ";
            contentBefore += c;
        }

       cout << "String before: " << contentBefore << endl;
        cout << "String after: " << contentAfter << endl;

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
                cout << "Invalid choice." << endl;
                break;
        }

        ofstream opFile(filePath, ios::binary);
        cout << "f: " << contact.firstName << endl;
        cout << "l: " << contact.lastName << endl;
        cout << "g: " << contact.gender << endl;
        cout << "p: " << contact.phoneNumber << endl;



        opFile.write(&contentBefore[0], contentBefore.length());
        opFile.write(&contact.firstName[0], contact.firstName.length() + 1);
        opFile.write(&contact.lastName[0], contact.lastName.length() + 1);
        opFile.write(&contact.gender[0], contact.gender.length() + 1);
        opFile.write(&contact.phoneNumber[0], contact.phoneNumber.length() + 1);
        opFile.write(&contentAfter[0], contentAfter.length());
        opFile.close();
        cout << "Contact modified successfully." << endl;
    } else {
        cout << "Contact not found." << endl;
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
    int contentAfterstart, contentAfterend, contentBeforeStart, contentBeforeEnd;

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
            cout << "fname: " << contact.firstName << endl;
            cout << "last: " << contact.lastName << endl;
            cout << "gender: " << contact.gender << endl;
            cout << "phone: " << contact.phoneNumber << endl;
            found = true;
            cout << "found" << endl;
            cout << "Before seek: " << input.tellg() << endl;
            int foundIndex = input.tellg();
            contentBeforeStart = 0;
            contentBeforeEnd = (int)input.tellg() - contactCharCount;
            contentAfterstart = input.tellg();
            input.seekg(0, ios::end);
            contentAfterend = input.tellg();
            input.seekg(foundIndex, ios::beg);


            cout << "Total Char Count: " << totalCharCount << endl;
            cout << "Contact char count: " << contactCharCount << endl;

            cout << "Before write: " << input.tellg() << endl;
            break;

        }
        id++;
    }

    if (found) {

        /// Store the string that is found before the content to be edited in a variable, Store the string that is found after the content to be edited in a variable, concatenate the three based on order, write it to a file by overwriting

        string contentBefore, contentAfter;

        for (int i = contentAfterstart; i < contentAfterend; i++) {
            char c;
            input.get(c);
            cout << (int)c << " ";
            contentAfter += c;
        }
        cout << endl << "spacer" << endl;
        input.seekg(0, ios::beg);
//
        for (int i = contentBeforeStart; i < contentBeforeEnd; i++) {
            char c;
            input.get(c);
            cout << (int)c << " ";
            contentBefore += c;
        }

        cout << "String before: " << contentBefore << endl;
        cout << "String after: " << contentAfter << endl;

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
        cout << "Contact not found." << endl;
    }

    input.close();

    input.close();
}

int main() {
    bool navigating = true;
    int menuChoice;

    while (navigating) {
        cout << "1) View all contacts\n2) Search for a contact\n3) Add a new contact\n4) Modify existing contact\n5) Delete existing contact";
        cin >> menuChoice;

        switch (menuChoice) {
            case 1:
                displayContacts();
                break;
            case 2:
                searchContact();
                break;
            case 3: {
                addContact();
            }
                break;
            case 4:
                modifyContact();
                break;
            case 5:
                deleteContact();
                break;
            default:
                cout << "Invalid option." << endl;
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

