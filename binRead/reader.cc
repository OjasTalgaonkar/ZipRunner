#include <bitset>
#include <fstream>
#include <iostream>

int main() {
  std::string filename = "index.exe";
  std::ifstream file(filename, std::ios::binary); // Open as binary
  if (!file) {
    std::cerr << "Error: Could not open file.\n";
    return 1;
  }

  //   std::ofstream outFile("hello.txt", std::ios::out); // Explicit text mode
  //   if (!outFile) {
  //     std::cerr << "Error: Could not open output file.\n";
  //     return 1;
  //   }

  char byte;
  while (file.get(byte)) {
    std::cout << std::bitset<8>(static_cast<unsigned char>(byte))
              << " "; // Add space for readability
  }

  file.close();
  //   outFile.close();
  std::cout << "Binary data saved to hello.txt\n";
  return 0;
}
