#include <random>
#include <iostream>
#include <openssl/sha.h>

std::string hashPassword(const std::string& password, const std::string& salt);

std::string generateSalt();

bool compareHash(const std::string& hash1, const std::string& hash2);