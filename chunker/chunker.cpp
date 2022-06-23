#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "fileGen.cpp"

void chunker(int numCheckSyms, int innerChunkSize) {
    // Assuming input file is one continous file of bytes
    std::string line = readFile("../files/chunk.txt");

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

    std::ofstream file;
    file.open("../files/chunked.txt");

    for (auto &chunk : chunks) {
        for (auto &outerCodeword : chunk) {
            for (auto &byte : outerCodeword) {
                file << static_cast<unsigned char>(byte);
            }
        }
    }
    file.close();
}

void dechunker(int numCheckSyms, int innerChunkSize, int padding) {
    std::string line = readFile("../files/chunked.txt");

    int outerChunkSize = 255 * innerChunkSize;
    std::vector<std::vector<std::vector<uint8_t>>> chunks;
    // Iterate through each chunk (k)
    for (int k = 0; k < line.size(); k += outerChunkSize) {
        std::vector<std::vector<uint8_t>> chunk;
        chunk.resize(255, std::vector<uint8_t>(innerChunkSize));
        // Lambda expression to destripe each chunk
        auto destriper = [&](int k) {
            // j = inner codeword length
            for (int j = 0; j < innerChunkSize; j++) {
                // j = outer codeword length
                for (int i = 0; i < 255; i++) {
                    chunk[i][j] = line[k + (j * 255) + i];
                }
            }
        };
        destriper(k);
        chunks.push_back(chunk);
    }
    std::ofstream file;
    file.open("../files/dechunked.txt");

    int count = 0;
    for (auto &chunk : chunks) {
        for (auto &outerCodeword : chunk) {
            for (auto &byte : outerCodeword) {
                if (count >= line.size() - padding) {
                    goto end;
                }
                file << static_cast<unsigned char>(byte);
                count++;
            }
        }
    }
    end:
    file.close();
}

void compareFiles(std::string file1, std::string file2) {
    if (readFile(file1) == readFile(file2)) {
        std::cout << "Files are equal" << std::endl;
    } else { 
        std::cout << "Files are not equal" << std::endl;
    }
}

int main() {
    generateFile(10000);
    chunker(50, 20);
    dechunker(50, 20, 200);
    compareFiles("../files/chunk.txt", "../files/dechunked.txt");
}