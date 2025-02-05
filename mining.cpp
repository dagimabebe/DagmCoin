#include "blockchain.h"
#include <iostream>

// Function to simulate mining (Proof-of-Work)
std::string mineBlock(Blockchain& blockchain, std::string data, int difficulty) {
    std::string target(difficulty, '0'); // Create a string with 'difficulty' number of leading zeros
    Block newBlock(blockchain.getChainSize(), blockchain.getLatestBlockHash(), data);

    while (true) {
        // Calculate the hash of the new block
        std::string blockHash = blockchain.calculateHash(newBlock);

        // Check if the hash meets the difficulty requirement
        if (blockHash.substr(0, difficulty) == target) {
            newBlock.hash = blockHash; // Set the block's hash
            blockchain.addBlock(newBlock); // Add the block to the blockchain
            std::cout << "Block mined! Hash: " << blockHash << "\n";
            return blockHash;
        }

        // Increment the nonce and try again
        newBlock.timestamp = time(0); // Update timestamp
    }
}

int main() {
    Blockchain myCoin;
    int difficulty = 4; // Number of leading zeros required in the hash

    std::cout << "Mining block 1...\n";
    mineBlock(myCoin, "Block 1 Data", difficulty);

    std::cout << "Mining block 2...\n";
    mineBlock(myCoin, "Block 2 Data", difficulty);

    std::cout << "\nBlockchain:\n";
    myCoin.printChain();

    return 0;
}
