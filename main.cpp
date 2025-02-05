#include <iostream>
#include <vector>
#include <string>
#include "DagimCoin.h"

// A simple class to represent the blockchain
class Blockchain {
private:
    std::vector<Block> chain; // A vector to store the blocks

public:
    // Constructor to create the genesis block (the first block)
    Blockchain() {
        chain.emplace_back(0, "0", "Genesis Block");
    }

    // Function to add a new block to the blockchain
    void addBlock(std::string data) {
        Block newBlock(chain.size(), getLatestBlock().hash, data);
        chain.push_back(newBlock);
        std::cout << "Block added: " << newBlock.hash << std::endl;
    }

    // Function to get the latest block in the blockchain
    Block getLatestBlock() {
        return chain.back();
    }

    // Function to display the entire blockchain
    void displayChain() {
        for (const auto& block : chain) {
            std::cout << "Block " << block.index << "\n";
            std::cout << "Previous Hash: " << block.previousHash << "\n";
            std::cout << "Timestamp: " << std::ctime(&block.timestamp);
            std::cout << "Data: " << block.data << "\n";
            std::cout << "Hash: " << block.hash << "\n\n";
        }
    }

    // Function to validate the entire blockchain
    bool isChainValid() {
        for (size_t i = 1; i < chain.size(); i++) {
            const Block& currentBlock = chain[i];
            const Block& previousBlock = chain[i - 1];

            // Check if the current block's previous hash matches the previous block's hash
            if (currentBlock.previousHash != previousBlock.hash) {
                return false; // Integrity fail
            }

            // Check if the current block's hash is correct
            if (currentBlock.hash != currentBlock.calculateHash()) {
                return false; // Integrity fail
            }
        }
        return true; // The chain is valid
    }
};

int main() {
    Blockchain dagimCoin; // Create the blockchain instance

    std::string command;
    std::string data;

    std::cout << "Welcome to the DagimCoin Blockchain Simulator!" << std::endl;

    while (true) {
        std::cout << "Enter command (add, display, validate, exit): ";
        std::cin >> command;

        if (command == "add") {
            std::cout << "Enter block data: ";
            std::cin.ignore(); // Ignore leftover newline
            std::getline(std::cin, data);
            dagimCoin.addBlock(data);
        } else if (command == "display") {
            dagimCoin.displayChain();
        } else if (command == "validate") {
            if (dagimCoin.isChainValid()) {
                std::cout << "Blockchain is valid." << std::endl;
            } else {
                std::cout << "Blockchain is invalid!" << std::endl;
            }
        } else if (command == "exit") {
            break; // Exit the loop
        } else {
            std::cout << "Unknown command." << std::endl;
        }
    }

    return 0;
}
