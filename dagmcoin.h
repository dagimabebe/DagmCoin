#ifndef DAGIMCOIN_H
#define DAGIMCOIN_H

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <openssl/sha.h>

// A struct to represent a single block in the blockchain
struct Block {
    int index; // Position of the block in the blockchain
    std::string previousHash; // The hash of the previous block
    std::time_t timestamp; // Time the block was created
    std::string data; // Data stored in the block
    std::string hash; // The hash of this block

    // Constructor
    Block(int idx, std::string prevHash, std::string blockData) 
        : index(idx), previousHash(prevHash), timestamp(std::time(nullptr)), data(blockData) {
        hash = calculateHash();
    }

    // Function to calculate the hash of the block
    std::string calculateHash() {
        std::string input = std::to_string(index) + previousHash + std::to_string(timestamp) + data;
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256((unsigned char*)input.c_str(), input.size(), hash);
        std::string hashStr;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            hashStr += sprintf("%02x", hash[i]);
        }
        return hashStr;
    }
};

#endif // DAGIMCOIN_H
