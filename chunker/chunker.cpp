#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void chunker(int numCheckSyms, int innerChunkSize) {
    std::ifstream file;
    file.open("../files/chunk.txt");

    // Assuming input file will be one continous string of bytes
    std::string line;
    getline(file, line);

    // Commented out below line as the input file will already contain check bytes
    // even though this won't be the case moving forward.
    // int dataBytes = 255 - numCheckSyms;
    int outerChunkSize = 255 * innerChunkSize;

    // Pad with zeros until all chunks will be of even size
    // Will optimize below to insert zeros all at once
    int padding = 0;
    while (line.size() % outerChunkSize != 0) {
        line.push_back('0');
        padding++;
    }

    std::vector<std::vector<std::vector<uint8_t>>> chunks;
    // Iterate through each chunk (k)
    for (int k = 0; k < line.size(); k += outerChunkSize) {
        std::vector<std::vector<uint8_t>> chunk;
        chunk.resize(innerChunkSize, std::vector<uint8_t>(255));

        // Lambda expression to stripe each chunk
        auto striper = [&](int k) {
            // i = outer codeword length
            for (int i = 0; i < 255; i++) {
                // j = inner codeword length
                for (int j = 0; j < innerChunkSize; j++) {
                    chunk[j][i] = line[k + (i * innerChunkSize) + j];
                }
            }
        };
        striper(k);
        chunks.push_back(chunk);
    }
}

int main() {
    chunker(50, 20);
}