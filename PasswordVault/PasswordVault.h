#ifndef PASSWORD_VAULT_H
#define PASSWORD_VAULT_H

#include <string>
#include <vector>
#include "Password.h"

class PasswordVault {

public:
    PasswordVault();
    ~PasswordVault();
    void addPassword(const std::string& website, const std::string& username, const std::string& password);
    Password retrievePassword(const std::string& website) const;
    void updatePassword(const std::string& website, const std::string& newPassword);
    void deletePassword(const std::string& website);
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    std::string getEncryptionKey() const;

private:
    std::vector<Password> passwordList;
    int findPasswordIndex(const std::string& website) const;
    std::string encryptionKey;
};

#endif
