#include <iostream>
#include <vector>
#include "DagimCoin.h"

// A simple class to represent the blockchain
class Blockchain {
private:
    std::vector<Block> chain; // A vector to store the blocks

public:
    // Constructor to create the genesis block (the first block)
    Blockchain() {
        // Create the first block (genesis block) and add it to the chain
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
};

int main() {
    Blockchain dagimCoin; // Create the blockchain instance

    // Adding blocks to the blockchain
    dagimCoin.addBlock("First block after Genesis");
    dagimCoin.addBlock("Second block with some data");
    dagimCoin.addBlock("Third block contains important information");

    // Display the entire blockchain
    dagimCoin.displayChain();

    return 0;
}
