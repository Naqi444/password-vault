#include "PasswordVault.h"
#include <fstream>
#include <iostream>
#include <openssl/aes.h>
#include <openssl/rand.h>

PasswordVault::PasswordVault() {
    unsigned char buffer[AES_KEY_SIZE];
    RAND_bytes(buffer, AES_KEY_SIZE);
    encryptionKey = std::string((char*)buffer, AES_KEY_SIZE);
}

PasswordVault::~PasswordVault() {}

void PasswordVault::addPassword(const std::string& website, const std::string& username,const std::string& password) {
    passwordList.push_back(Password(website, username, password,encryptionKey));
}

Password PasswordVault::retrievePassword(const std::string& website) const {
    int index = findPasswordIndex(website);
    if (index != -1)
        return passwordList[index];
    else
        return Password("", "" ,"","");
}

void PasswordVault::updatePassword(const std::string& website, const std::string& newPassword) {
    int index = findPasswordIndex(website);
    if (index != -1)
        passwordList[index].setEncryptedPassword(newPassword);
    else
        std::cerr << "Password not found for the specified website." << std::endl;
}

void PasswordVault::deletePassword(const std::string& website) {
    int index = findPasswordIndex(website);
    if (index != -1)
        passwordList.erase(passwordList.begin() + index);
    else
        std::cerr << "Password not found for the specified website." << std::endl;
}

void PasswordVault::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const Password& password : passwordList)
            file << password.getWebsite() << "," << password.getUsername() << "," << password.getEncryptedPassword() << std::endl;
        file.close();
    }
    else
        std::cerr << "Unable to open file: " << filename << std::endl;
}

void PasswordVault::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        passwordList.clear(); // Clear existing passwords
        std::string line;
        while (std::getline(file, line)) {
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            if (pos1 != std::string::npos && pos2 != std::string::npos) {
                std::string website = line.substr(0, pos1);
                std::string username = line.substr(pos1 + 1, pos2 - pos1 - 1);
                std::string encryptedPassword = line.substr(pos2 + 1);
                passwordList.push_back(Password(website, username, encryptedPassword,encryptionKey));
            }
        }
        file.close();
    }
    else
        std::cerr << "Unable to open file: " << filename << std::endl;
}

int PasswordVault::findPasswordIndex(const std::string& website) const {
    for (size_t i = 0; i < passwordList.size(); ++i) {
        if (passwordList[i].getWebsite() == website)
            return i;
    }
    return -1;
}

std::string PasswordVault::getEncryptionKey() const {
    return encryptionKey;
}
