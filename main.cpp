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
void addContact(const string& filename, const Contact& contact) {
    ofstream outFile(filename, ios::binary | ios::app);
    if (!outFile) {
        cerr << "Error opening file for writing." << endl;
        return;
    }

    outFile.write(&contact.firstName[0], contact.firstName.length() + 1);
    cout << "String size: " << contact.firstName.length() + 1 << endl;
    outFile.write(contact.lastName.c_str(), contact.lastName.length() + 1);
    outFile.write(&contact.gender, sizeof(char));
    outFile.write(contact.phoneNumber.c_str(), contact.phoneNumber.length() + 1);

    outFile.close();
}

// Function to read contact data from a binary file
void displayContacts(const string& filename) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cerr << "Error opening file for reading." << endl;
        return;
    }

    while (!inFile.eof()) {
        Contact contact;

        char ch;
        while (inFile.get(ch) && ch != '\0') {
            contact.firstName += ch;
        }

        while (inFile.get(ch) && ch != '\0') {
            contact.lastName += ch;
        }

        inFile.read(&contact.gender, sizeof(char));

        while (inFile.get(ch) && ch != '\0') {
            contact.phoneNumber += ch;
        }

        if (!contact.firstName.empty() || !contact.lastName.empty()) {
            cout << "ID: " << contact.id << endl;
            cout << "First Name: " << contact.firstName << endl;
            cout << "Last Name: " << contact.lastName << endl;
            cout << "Gender: " << contact.gender << endl;
            cout << "Phone Number: " << contact.phoneNumber << endl;
            cout << "------------------------" << endl;
        }

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

        inFile.read(&contact.gender, sizeof(char));

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

    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cerr << "Error opening file for reading." << endl;
        return;
    }
    int id = 1;
    int charCount = 0;
    while (id <= idInput && !inFile.eof()) {
        Contact contact;


        char ch;

        contact.id = id;
        while (inFile.get(ch) && ch != '\0') {
            contact.firstName += ch;
            charCount++;
        }

        while (inFile.get(ch) && ch != '\0') {
            contact.lastName += ch;
            charCount++;
        }

        inFile.read(&contact.gender, sizeof(char));
        charCount++;

        while (inFile.get(ch) && ch != '\0') {
            contact.phoneNumber += ch;
            charCount++;

        }

        if (!contact.firstName.empty() || !contact.lastName.empty()) {
            if (contact.id == idInput) {
                streampos pos = inFile.tellg();

                // Move the file pointer back to the start of the contact's record
                if (idInput == 1) {
                    inFile.seekg(0, ios::beg);
                } else {
                    inFile.seekg(charCount);
                }

               cout << inFile.tellg();

                // Write the modified contact back to the file
               // inFile.write(reinterpret_cast<const char*>(&contact), sizeof(Contact));
            }
        }
        id++;
        cout << "itaeration finished" << endl;
        break;
    }

    inFile.close();
}




int main() {

    bool navigating = true;
    int menuChoice;

    Contact newContact = {"ABC", "uiop", 'M', "555-123-4567"};

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


