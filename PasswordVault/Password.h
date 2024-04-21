#ifndef PASSWORD_H
#define PASSWORD_H

#include <string>

#define AES_KEY_SIZE 32

class Password {
public:
    Password(const std::string& website, const std::string& username, const std::string& encryptedPassword, const std::string& encryptionKey);

    std::string getWebsite() const;
    std::string getUsername() const;
    std::string getEncryptedPassword() const;

    void setEncryptedPassword(const std::string& encryptedPassword);

    static std::string encryptAES(const std::string& plaintext, const std::string& key);
    static std::string decryptAES(const std::string& ciphertext, const std::string& key);

private:
    std::string website;
    std::string username;
    std::string encryptedPassword;
    std::string encryptionKey;
};

#endif
