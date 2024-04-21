#include <iostream>
#include <string>
#include "PasswordVault.h"

using namespace std;

void displayMenu() {
    cout << "Password Vault Menu:" << endl;
    cout << "1. Add Password" << endl;
    cout << "2. Retrieve Password" << endl;
    cout << "3. Update Password" << endl;
    cout << "4. Delete Password" << endl;
    cout << "5. Save Passwords to File" << endl;
    cout << "6. Load Passwords from File" << endl;
    cout << "7. Exit" << endl;

    cout << "Enter your choice: "; 
}

int getUserInput() {
    int choice;
    cin >> choice;
    return choice;
}

int main() {
    PasswordVault vault;
    while(true)
    {
        displayMenu();
        int choice = getUserInput();

        switch(choice) {
            case 1: {
                string website, username, password;
                cout << "Enter website: ";
                cin >> website;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                vault.addPassword(website, username, password);
                cout << "Password added successfully!" << endl;
                break;
            }

            case 2: {
                string website;
                cout << "Enter website: ";
                cin >> website;
                Password password = vault.retrievePassword(website);
                if (password.getWebsite() != "") {
                    cout << "Username: " << password.getUsername() << endl;
                    cout << "Password: " << password.getEncryptedPassword() << endl;
                }
                else
                    cout << "Password not found for the specified website." << endl;
                break;
            }

            case 3: {
                string website, newPassword;
                cout << "Enter website: ";
                cin >> website;
                cout << "Enter new password: ";
                cin >> newPassword;
                vault.updatePassword(website, newPassword);
                cout << "Password updated successfully!" << endl;
                break;
            }

            case 4: {
                string website;
                cout << "Enter website: ";
                cin >> website;
                vault.deletePassword(website);
                cout << "Password deleted successfully!" << endl;
                break;
            }

            case 5: {
                string filename;
                cout << "Enter filename to save passwords to: ";
                cin >> filename;
                vault.saveToFile(filename);
                cout << "Passwords saved to file successfully!" << endl;
                break;
            }
            case 6: {
                string filename;
                cout << "Enter filename to load passwords from: ";
                cin >> filename;
                vault.loadFromFile(filename);
                cout << "Passwords loaded from file successfully!" << endl;
                break;
            }
            case 7: {
                cout << "Exiting..." << endl;
                return 0;
            }
            default: {
                cout << "Invalid choice. Please enter a number between 1 and 7." << endl;
                break;
            }
        }
    }

    return 0;
}
