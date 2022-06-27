#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "pipeline.cpp"
int padding = 0;
int fileSize = 0;

std::vector<std::vector<std::vector<uint8_t>>> chunker(int numCheckSyms, int innerChunkSize) {
    // Assuming input file is one continous file of bytes
    std::string line = readFile("../files/chunk2.txt");

    // Commented out below line as the input file will already contain check bytes
    // even though this won't be the case moving forward.
    int dataBytes = 255 - numCheckSyms;
    int outerChunkSize = dataBytes * innerChunkSize;

    // Pad with zeros until all chunks will be of even size
    // Will optimize below to insert zeros all at once
    while (line.size() % outerChunkSize != 0) {
        line.push_back('0');
        padding++;
    }

    // Write to file, now with padding
    std::ofstream file;
    file.open("../files/chunked2.txt");
    for (int i = 0; i < line.size(); i++) {
        file << line[i];
    }
    file.close();

    std::vector<std::vector<std::vector<uint8_t>>> chunks;
    std::vector<uint8_t> encodedVec = outerEncoder();

    // Iterate through each chunk (k)
    for (int k = 0; k < encodedVec.size(); k += (255 * innerChunkSize)) {
        std::vector<std::vector<uint8_t>> chunk;
        chunk.resize(255, std::vector<uint8_t>(innerChunkSize));
        // Lambda expression to stripe each chunk
        auto striper = [&](int k) {
            // i = outer codeword length
            for (int j = 0; j < innerChunkSize; j++) {
                // j = inner codeword length
                for (int i = 0; i < 255; i++) {
                    chunk[i][j] = encodedVec[k + (j * 255) + i];
                    fileSize++;
                }
            }
        };
        striper(k);
        chunks.push_back(chunk);
    }

    std::ofstream file2;
    file2.open("../files/striped2.txt");

    for (auto &chunk : chunks) {
        for (auto &outerCodeword : chunk) {
            for (auto &byte : outerCodeword) {
                file2 << byte;
            }
            file2 << '\n';
        }
    }
    file2.close();
    return chunks;
}

void dechunker(int numCheckSyms, int innerChunkSize, int padding, std::vector<std::vector<std::vector<uint8_t>>> chunks) {
    // std::string line = readFile("../files/striped2.txt");

    std::vector<std::vector<std::vector<uint8_t>>> newChunks;
    // Iterate through each chunk (k)
    for (int k = 0; k < chunks.size(); k++) {
        std::vector<std::vector<uint8_t>> chunk;
        chunk.resize(innerChunkSize, std::vector<uint8_t>(255));
        // Lambda expression to destripe each chunk
        auto destriper = [&](int k) {
            // j = inner codeword length
            for (int i = 0; i < 255; i++) {
                // j = outer codeword length
                for (int j = 0; j < innerChunkSize; j++) {
                    chunk[j][i] = unsigned(chunks[k][i][j]);
                }
            }
        };
        destriper(k);
        newChunks.push_back(chunk);
    }

    std::ofstream file3;
    file3.open("../files/dechunked2.txt");

    int count = 0;
    for (std::vector<std::vector<uint8_t>> chunk : newChunks) {
        for (std::vector<uint8_t> outerCodeword : chunk) {
            int outerCount = 1;
            for (uint8_t byte : outerCodeword) {
                if (count >= fileSize - padding) {
                    goto end;
                }
                if (outerCount > 205) {
                    break;
                }
                file3 << byte;
                count++;
                outerCount++;
            }
        }
    }
end: file3.close();
}

void compareFiles(std::string file1, std::string file2) {
    if (readFile(file1) == readFile(file2)) {
        std::cout << "Files are equal" << std::endl;
    } else {
        std::cout << "Files are not equal" << std::endl;
    }
}

int main() {
    // generateFile(10000, "../files/chunk2.txt");
    std::vector<std::vector<std::vector<uint8_t>>> vec = chunker(50, 20);
    dechunker(50, 20, padding, vec);
    compareFiles("../files/chunk2.txt", "../files/dechunked2.txt");
}