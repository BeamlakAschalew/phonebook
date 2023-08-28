///// LET'S DO THIS!
//#include <iostream>
//#include <fstream>
//
//using namespace std;
//
//ifstream input;
//ofstream output;
//
//struct Contact {
//    string firstName, lastName;
//    char gender;
//    int phoneNumber;
//};
//
//void openInputFile(string fileLocation) {
//    input.open(fileLocation, ios::binary);
//}
//
//void openOutputFile(string fileLocation) {
//    output.open(fileLocation, ios::binary | ios::app);
//}
//
//void displayContact() {
//    openInputFile("../contacts.bin");
//    if (!input.is_open()) {
//        cout << "Problem opening file.";
//        exit(1);
//    } else {
//        while (!input.eof()) {
//            char c;
//            input.read((char*) &c, sizeof(c));
//            cout << c;
//        }
//    }
//}
//
//void searchContact() {
//
//}
//
//void addContact() {
//    Contact c;
//    system("cls");
//    cout << "Enter first name: ";
//    getline(cin.ignore(), c.firstName.append(" "));
//    cout << "Enter last name: ";
//    getline(cin, c.lastName);
//    cout << "Enter gender: ";
//    cin >> c.gender;
//    cout << "Enter phone number";
//    cin >> c.phoneNumber;
//
//    openOutputFile("../contacts.bin");
//    if (!output.is_open()) {
//        cout << "Problem opening file.";
//        exit(1);
//    } else {
//        output.write((char*) &c.firstName, c.firstName.size());
//        output.close();
//    }
//
//}
//void modifyContact() {
//
//}
//
//void deleteContact() {
//
//}
//
//
//int main() {
//
//    bool navigating = true;
//    int menuChoice;
//
//    while (navigating) {
//        cout << "1) View all contacts\n2) Search for a contact\n3) Add a new contact\n4) Modify existing contact\n5) Delete existing contact";
//        cin >> menuChoice;
//
//        switch (menuChoice) {
//            case 1: {
//                displayContact();
//            }
//                break;
//            case 2: {
//                searchContact();
//            }
//                break;
//            case 3: {
//                addContact();
//            }
//                break;
//            case 4: {
//                modifyContact();
//            }
//                break;
//            case 5: {
//                deleteContact();
//            }
//                break;
//            default: cout << "Invalid option.";
//        }
//    }
//
//    return 0;
//}

//#include <iostream>
//#include <fstream>
//#include <string>
//
//// Structure to hold contact information
//struct Contact {
//    std::string firstName;
//    std::string lastName;
//    char gender;
//    std::string phoneNumber;
//};
//
//// Function to write contact data to a binary file
//void writeContactsToFile(const std::string& filename, const Contact* contacts, int numContacts) {
//    std::ofstream outFile(filename, std::ios::binary);
//    if (!outFile) {
//        std::cerr << "Error opening file for writing." << std::endl;
//        return;
//    }
//
//    for (int i = 0; i < numContacts; ++i) {
//        outFile.write(contacts[i].firstName.c_str(), contacts[i].firstName.length() + 1);
//        outFile.write(contacts[i].lastName.c_str(), contacts[i].lastName.length() + 1);
//        outFile.write(&contacts[i].gender, sizeof(char));
//        outFile.write(contacts[i].phoneNumber.c_str(), contacts[i].phoneNumber.length() + 1);
//    }
//
//    outFile.close();
//}
//
//// Function to read contact data from a binary file
//void readContactsFromFile(const std::string& filename, Contact* contacts, int numContacts) {
//    std::ifstream inFile(filename, std::ios::binary);
//    if (!inFile) {
//        std::cerr << "Error opening file for reading." << std::endl;
//        return;
//    }
//
//    for (int i = 0; i < numContacts; ++i) {
//        std::getline(inFile, contacts[i].firstName, '\0');
//        std::getline(inFile, contacts[i].lastName, '\0');
//        inFile.read(&contacts[i].gender, sizeof(char));
//        std::getline(inFile, contacts[i].phoneNumber, '\0');
//    }
//
//    inFile.close();
//}
//
//int main() {
//    // Example data
//    Contact contacts[] = {
//            {"John", "Doe", 'M', "123-456-7890"},
//            {"Jane", "Smith", 'F', "987-654-3210"}
//    };
//    int numContacts = sizeof(contacts) / sizeof(contacts[0]);
//
//    // Write data to binary file
//    writeContactsToFile("../contacts.bin", contacts, numContacts);
//
//    // Read data from binary file
//    Contact readContacts[numContacts];
//    readContactsFromFile("../contacts.bin", readContacts, numContacts);
//
//    // Display read data
//    for (int i = 0; i < numContacts; ++i) {
//        std::cout << "First Name: " << readContacts[i].firstName << std::endl;
//        std::cout << "Last Name: " << readContacts[i].lastName << std::endl;
//        std::cout << "Gender: " << readContacts[i].gender << std::endl;
//        std::cout << "Phone Number: " << readContacts[i].phoneNumber << std::endl;
//        std::cout << "------------------------" << std::endl;
//    }
//
//    return 0;
//}

#include <iostream>
#include <fstream>
#include <string>

// Structure to hold contact information
struct Contact {
    std::string firstName;
    std::string lastName;
    char gender;
    std::string phoneNumber;
};

// Function to write a contact to a binary file
void writeContactToFile(const std::string& filename, const Contact& contact) {
    std::ofstream outFile(filename, std::ios::binary | std::ios::app);
    if (!outFile) {
        std::cerr << "Error opening file for writing." << std::endl;
        return;
    }

    outFile.write(contact.firstName.c_str(), contact.firstName.length() + 1);
    outFile.write(contact.lastName.c_str(), contact.lastName.length() + 1);
    outFile.write(&contact.gender, sizeof(char));
    outFile.write(contact.phoneNumber.c_str(), contact.phoneNumber.length() + 1);

    outFile.close();
}

// Function to read contact data from a binary file
void readContactsFromFile(const std::string& filename) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        std::cerr << "Error opening file for reading." << std::endl;
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
            std::cout << "First Name: " << contact.firstName << std::endl;
            std::cout << "Last Name: " << contact.lastName << std::endl;
            std::cout << "Gender: " << contact.gender << std::endl;
            std::cout << "Phone Number: " << contact.phoneNumber << std::endl;
            std::cout << "------------------------" << std::endl;
        }
    }

    inFile.close();
}

int main() {
    // Example data
    Contact newContact = {"Alice", "Johnson", 'F', "555-123-4567"};

    // Write new contact data to binary file
    writeContactToFile("../contacts.bin", newContact);

    // Read all contact data from binary file
    readContactsFromFile("../contacts.bin");

    return 0;
}


