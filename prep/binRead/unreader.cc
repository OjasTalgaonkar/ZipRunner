#include <bitset>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

int main() {
  std::string inputFile = "hello.txt";   // Binary string file
  std::string outputFile = "output.exe"; // Reconstructed file

  std::ifstream inFile(inputFile);
  if (!inFile) {
    std::cerr << "Error: Could not open input file.\n";
    return 1;
  }

  std::ofstream outFile(outputFile, std::ios::binary);
  if (!outFile) {
    std::cerr << "Error: Could not open output file.\n";
    return 1;
  }

  std::string inputData;
  std::string line;

  while (std::getline(inFile, line)) {
    inputData += line; // Accumulate the input data
  }

  unsigned char buffer = 0;
  int bitCount = 0;
  for (char bit : inputData) {
    if (bit != '0' && bit != '1') {
      continue;
    }
    buffer = (buffer << 1) | (bit - '0'); // Add bit to buffer
    bitCount++;

    if (bitCount == 8) {
      outFile.put(buffer); // Write full byte
      buffer = 0;
      bitCount = 0;
    }
  }
}
