///// LET'S DO THIS!
#include <iostream>
#include <fstream>

using namespace std;

ifstream input;
ofstream output;

struct Contact {
    string firstName;
    string lastName;
    char gender;
    string phoneNumber;
    int id;
};

// Function to write a contact to a binary file
void addContact(string filename, Contact contact[]) {
    ofstream outFile(filename, ios::binary | ios::app);
    if (!outFile) {
        cerr << "Error opening file for writing." << endl;
        return;
    }
    for (int i = 0; i < 6; i++) {
        outFile.write(&contact[i].firstName[0], contact[i].firstName.length() + 1);
        //cout << "String size: " << contact.firstName.length() + 1 << endl;
        outFile.write(contact[i].lastName.c_str(), contact[i].lastName.length() + 1);
        outFile.write(&contact[i].gender, sizeof(char) + 1);
        outFile.write(contact[i].phoneNumber.c_str(), contact[i].phoneNumber.length() + 1);
    }

    outFile.close();
}

// Function to read contact data from a binary file
void displayContacts(const string& filename) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cerr << "Error opening file for reading." << endl;
        return;
    }

    int id = 1;
    while (!inFile.eof()) {
        Contact contact;

        char ch;
        while (inFile.get(ch) && ch != '\0') {
            contact.firstName += ch;
        }

        while (inFile.get(ch) && ch != '\0') {
            contact.lastName += ch;
        }

        while (inFile.get(ch) && ch != '\0') {
            contact.gender = ch;
        }

        while (inFile.get(ch) && ch != '\0') {
            contact.phoneNumber += ch;
        }

        contact.id = id;

        if (!contact.firstName.empty() || !contact.lastName.empty()) {
            cout << "ID: " << contact.id << endl;
            cout << "First Name: " << contact.firstName << endl;
            cout << "Last Name: " << contact.lastName << endl;
            cout << "Gender: " << contact.gender << endl;
            cout << "Phone Number: " << contact.phoneNumber << endl;
            cout << "------------------------" << endl;
        }
        id++;
    }

    inFile.close();
}

void searchContact(string filename) {
    string fname, lname;
    cout << "Enter first name: ";
    getline(cin.ignore(), fname);
    cout << "Enter last name: ";
    getline(cin.ignore(), lname);

    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cerr << "Error opening file for reading." << endl;
        return;
    }
    int id = 1;
    while (!inFile.eof()) {
        Contact contact;

        char ch;

        contact.id = id;
        while (inFile.get(ch) && ch != '\0') {
            contact.firstName += ch;
        }

        while (inFile.get(ch) && ch != '\0') {
            contact.lastName += ch;
        }

        while (inFile.get(ch) && ch != '\0') {
            contact.gender = ch;
        }

        while (inFile.get(ch) && ch != '\0') {
            contact.phoneNumber += ch;
        }

        if (!contact.firstName.empty() || !contact.lastName.empty()) {
            if (contact.firstName == fname) {
                cout << "ID: " << contact.id << endl;
                cout << "First Name: " << contact.firstName << endl;
                cout << "Last Name: " << contact.lastName << endl;
                cout << "Gender: " << contact.gender << endl;
                cout << "Phone Number: " << contact.phoneNumber << endl;
                cout << "------------------------" << endl;
            }
        }
        id++;
    }

    inFile.close();
}

void modifyContact(string filename) {
    int idInput;
    cout << "Enter first name: ";
    cin >> idInput;

    fstream inFile(filename, ios::binary | ios::in | ios::out);
    if (!inFile) {
        cerr << "Error opening file for reading." << endl;
        return;
    }

    int id = 1;
    int totalCharCount = 0;
    int contactCharCount = 0;
    bool found = false;
    Contact contact;
    int contentAfterstart, contentAfterend, contentBeforeStart, contentBeforeEnd;

    while (!inFile.eof()) {
        contactCharCount = 0;
        char ch;

        contact.id = id;
        while (inFile.get(ch) && ch != '\0') {
            contact.firstName += ch;
            totalCharCount++;
            contactCharCount++;
        }
        contactCharCount++;

        while (inFile.get(ch) && ch != '\0') {
            contact.lastName += ch;
            totalCharCount++;
            contactCharCount++;
        }
        contactCharCount++;

        while (inFile.get(ch) && ch != '\0') {
            contact.gender = ch;
            totalCharCount++;
            contactCharCount++;
        }
        contactCharCount++;


        while (inFile.get(ch) && ch != '\0') {
            contact.phoneNumber += ch;
            totalCharCount++;
            contactCharCount++;
        }
        contactCharCount++;

            cout << "Id temp: " << id << " Id contact: " << contact.id << endl;
            if (contact.id == idInput) {
                found = true;
                cout << "found" << endl;
                cout << "Before seek: " << inFile.tellg() << endl;
                int foundIndex = inFile.tellg();
                contentBeforeStart = 0;
                contentBeforeEnd = (int)inFile.tellg() - contactCharCount;
                contentAfterstart = inFile.tellg();
                inFile.seekg(0, ios::end);
                contentAfterend = inFile.tellg();
                inFile.seekg(foundIndex, ios::beg);

                if (id == 1) {
                    inFile.seekp(0, ios::beg);
                } else {
                    cout << "Total Char Count: " << totalCharCount << endl;
                    cout << "Contact char count: " << contactCharCount << endl;
                   // inFile.seekp(-contactCharCount, ios::cur);
                }

                cout << "Before write: " << inFile.tellp() << endl;
                break;

            }
        id++;
    }

    if (found) {

        /// Store the string that is found before the content to be edited in a variable, Store the string that is found after the content to be edited in a variable, concatenate the three based on order, write it to a file by overwriting

        cout << "Content before start: " << contentBeforeStart << endl;
        cout << "Content before end: " << contentBeforeEnd << endl;
        cout << "Content after start: " << contentAfterstart << endl;
        cout << "Content after end: " << contentAfterend << endl;


        string contentBefore, contentAfter;

        for (int i = contentAfterstart; i < contentAfterend; i++) {
            char c;
            inFile.get(c);
            contentAfter += c;
        }

        inFile.seekg(0, ios::beg);
//
        for (int i = contentBeforeStart; i < contentBeforeEnd; i++) {
            char c;
            inFile.get(c);
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
                inFile.write(&contact.firstName[0], contact.firstName.length());
                cout << "After first name: " << inFile.tellp() << endl;
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


//        inFile.write(&contact.lastName[0], contact.lastName.length() + 1);
//        cout << "After last name: " << inFile.tellp() << endl;
//        inFile.write(&contact.gender, sizeof(char) + 1);
//        cout << "After gender name: " << inFile.tellp() << endl;
//        inFile.write(&contact.phoneNumber[0], contact.phoneNumber.length() + 1);
//        cout << "After phone name: " << inFile.tellp() << endl;

        cout << "Contact modified successfully." << endl;
    } else {
        cout << "Contact not found." << endl;
    }

    inFile.close();
}




int main() {

    bool navigating = true;
    int menuChoice;

    Contact newContact[6] = {{.firstName = "Beamlak", .lastName = "Aschalew", .gender = 'M', .phoneNumber = "0936648802"}, {.firstName = "Beemnet", .lastName = "Aschalew", .gender = 'F', .phoneNumber = "0936647712"}, {.firstName = "Adil", .lastName = "Adem", .gender = 'M', .phoneNumber = "0960547818"}, {.firstName = "Alazar", .lastName = "Fasil", .gender = 'M', .phoneNumber = "0941412578"}, {.firstName = "Edom", .lastName = "Mulugeta", .gender = 'F', .phoneNumber = "0920212223"}, {.firstName = "Edlawit", .lastName = "Solomon", .gender = 'F', .phoneNumber = "0960127865"}};

    while (navigating) {
        cout << "1) View all contacts\n2) Search for a contact\n3) Add a new contact\n4) Modify existing contact\n5) Delete existing contact";
        cin >> menuChoice;

        switch (menuChoice) {
            case 1: {
                displayContacts("../contacts.bin");
            }
                break;
            case 2: {
               searchContact("../contacts.bin");
               break;
            }
                break;
            case 3: {
                addContact("../contacts.bin", newContact);
            }
                break;
            case 4: {
               modifyContact("../contacts.bin");
            }
                break;
            case 5: {
               // deleteContact();
            }
                break;
            default: cout << "Invalid option.";
        }
    }

    return 0;
}


