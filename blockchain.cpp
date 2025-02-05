#include "blockchain.h"
#include <sstream>
#include <iomanip>
#include <openssl/sha.h> // For SHA-256 hashing

// Block constructor
Block::Block(int idx, std::string prevHash, std::string d)
    : index(idx), previousHash(prevHash), data(d), timestamp(time(0)) {
    // Calculate the hash for this block
    hash = calculateHash(*this);
}

// Blockchain constructor
Blockchain::Blockchain() {
    // Create the genesis block (first block in the chain)
    Block genesisBlock(0, "0", "Genesis Block");
    chain.push_back(genesisBlock);
}

// Function to get the hash of the latest block in the chain
std::string Blockchain::getLatestBlockHash() const {
    return chain.back().hash;
}

// Function to calculate the SHA-256 hash of a block
std::string Blockchain::calculateHash(const Block& block) const {
    std::stringstream ss;
    ss << block.index << block.previousHash << block.data << block.timestamp;

    std::string input = ss.str();
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input.c_str(), input.size());
    SHA256_Final(hash, &sha256);

    std::stringstream hashStream;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        hashStream << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    return hashStream.str();
}

// Function to add a new block to the blockchain
void Blockchain::addBlock(std::string data) {
    int newIndex = chain.size();
    std::string previousHash = getLatestBlockHash();
    Block newBlock(newIndex, previousHash, data);
    chain.push_back(newBlock);
}

// Function to print the blockchain
void Blockchain::printChain() const {
    for (const Block& block : chain) {
        std::cout << "Block #" << block.index << "\n";
        std::cout << "Previous Hash: " << block.previousHash << "\n";
        std::cout << "Data: " << block.data << "\n";
        std::cout << "Hash: " << block.hash << "\n";
        std::cout << "Timestamp: " << std::asctime(std::localtime(&block.timestamp)) << "\n";
        std::cout << "-------------------------\n";
    }
}
