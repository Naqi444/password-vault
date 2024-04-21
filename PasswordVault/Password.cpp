#include "Password.h"
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <cstring>

Password::Password(const std::string& website, const std::string& username, const std::string& encryptedPassword, const std::string& encryptionKey) 
    : website(website), username(username), encryptedPassword(encryptedPassword), encryptionKey(encryptionKey) {}

std::string Password::getWebsite() const {
    return website;
}

std::string Password::getUsername() const {
    return username;
}

std::string Password::getEncryptedPassword() const {
    return encryptedPassword;
}

void Password::setEncryptedPassword(const std::string& encryptedPassword) {
    this->encryptedPassword = encryptAES(encryptedPassword, encryptionKey);
}


std::string Password::encryptAES(const std::string& plaintext, const std::string& key) {
    unsigned char iv[AES_BLOCK_SIZE];
    RAND_bytes(iv, AES_BLOCK_SIZE);

    AES_KEY aesKey;
    AES_set_encrypt_key((const unsigned char*)key.c_str(), 256, &aesKey);

    int encryptedLength = plaintext.length() + AES_BLOCK_SIZE;
    unsigned char encryptedText[encryptedLength];
    memset(encryptedText, 0, sizeof(encryptedText));

    AES_cbc_encrypt((const unsigned char*)plaintext.c_str(), encryptedText, plaintext.length(), &aesKey, iv, AES_ENCRYPT);

    std::string ciphertext;
    ciphertext.append((char*)iv, AES_BLOCK_SIZE);
    ciphertext.append((char*)encryptedText, encryptedLength);

    return ciphertext;
}

// AES decryption function
std::string Password::decryptAES(const std::string& ciphertext, const std::string& key) {
    unsigned char iv[AES_BLOCK_SIZE];
    memcpy(iv, ciphertext.c_str(), AES_BLOCK_SIZE);

    AES_KEY aesKey;
    AES_set_decrypt_key((const unsigned char*)key.c_str(), 256, &aesKey);

    int decryptedLength = ciphertext.length() - AES_BLOCK_SIZE;
    unsigned char decryptedText[decryptedLength];
    memset(decryptedText, 0, sizeof(decryptedText));

    AES_cbc_encrypt((const unsigned char*)ciphertext.c_str() + AES_BLOCK_SIZE, decryptedText, decryptedLength, &aesKey, iv, AES_DECRYPT);

    return std::string((char*)decryptedText);
}
