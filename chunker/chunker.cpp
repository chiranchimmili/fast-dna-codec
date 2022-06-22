#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void chunker(int numCheckSyms, int innerChunkSize) {
    std::ifstream file;
    file.open("../files/chunk.txt");

    std::string line;
    getline(file, line);

    int dataBytes = 255 - numCheckSyms;
    int outerChunkSize = dataBytes * innerChunkSize;

    std::vector<std::vector<std::vector<uint8_t>>> chunks;
    for (int k = 0; k < line.size(); k += outerChunkSize) {
        std::vector<std::vector<uint8_t>> chunk(innerChunkSize, std::vector<uint8_t>(dataBytes));
        auto striper = [&](int k) {
            for (int i = 0; i < dataBytes; i++) {
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