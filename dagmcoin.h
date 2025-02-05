#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <vector>
#include <string>
#include <ctime>

// Define a Block structure
struct Block {
    int index; // Block index in the chain
    std::string previousHash; // Hash of the previous block
    std::string data; // Data stored in the block (e.g., transactions)
    std::string hash; // Hash of the current block
    time_t timestamp; // Timestamp of when the block was created

    Block(int idx, std::string prevHash, std::string d);
};

// Define the Blockchain class
class Blockchain {
private:
    std::vector<Block> chain; // The chain of blocks
    std::string getLatestBlockHash() const; // Helper function to get the latest block's hash
    std::string calculateHash(const Block& block) const; // Helper function to calculate a block's hash

public:
    Blockchain(); // Constructor
    void addBlock(std::string data); // Function to add a new block
    void printChain() const; // Function to print the blockchain
};

#endif // BLOCKCHAIN_H
