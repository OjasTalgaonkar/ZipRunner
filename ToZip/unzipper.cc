#include <cstddef>
#include <cstdio>
#include <fstream>
#include <iostream>

struct HuffNode {
  char letter;     // Character (leaf node) or '\0' (internal node)
  int freq;        // Frequency of the character
  HuffNode *left;  // Left child
  HuffNode *right; // Right child

  HuffNode(char l) : letter(l) {}
  bool operator==(const HuffNode *b) {
    return this->freq > b->freq; // Higher frequency => lower priority
  }
};

HuffNode *deserializeTree(std::ifstream &zip, int &number) {
  if (number <= 0) {
    return nullptr;
  }
  HuffNode *newNode;
  char nodeType;
  zip.get(nodeType);
  number--;
  std::cout << " " << nodeType;

  switch (nodeType) {
  case 'N':
    return nullptr;
    break;
  case 'I':
    newNode = new HuffNode('\0');
    newNode->left = deserializeTree(zip, number);
    newNode->right = deserializeTree(zip, number);
    break;
  case 'L':
    char letter;
    zip.get(letter);
    std::cout << " " << letter;
    number--;
    newNode = new HuffNode(letter);

    // read both Ns for nulls after the letter
    newNode->left = deserializeTree(zip, number);
    newNode->right = deserializeTree(zip, number);
  }
  return newNode;
}

HuffNode *readZipFile(std::ifstream &zip, std::string &holder) {
  char marker;

  if (!zip.get(marker) || marker != '%') {
    throw std::runtime_error("File does not start with '%'");
  }

  int number;
  zip.read(reinterpret_cast<char *>(&number), sizeof(number));

  if (!zip.get(marker) || marker != '%') {
    throw std::runtime_error("Missing closing '%' for the number.");
  }

  std::cout << "Number read: " << number << std::endl;
  HuffNode *root = deserializeTree(zip, number);
  std::cout << "separator";
  char byte;
  char bit;
  while (zip.get(byte)) {
    std::cout << byte;
    for (int i = 7; i >= 0; i--) { // Start with the MSB (i = 7)
      bit = ((byte >> i) & 1) +
            '0'; // Extract the i-th bit, convert to '0' or '1'
      holder += bit;
    }
  }
  return root;
}

int main() {
  std::ifstream zip("filesToTEst\\output.bin", std::ios::binary);
  if (!zip) {
    printf("File doesnt open!", stderr);
    return 0;
  }

  HuffNode *root = nullptr;
  std::string holder = "";
  root = readZipFile(zip, holder);
  // std::cout << holder;
  if (root->letter != '\0') { // tree build check
    std::cout << "this aint built right";
  }

  if (root->right == nullptr) {
    std::cout << "right not made";
  }
  if (root->left == nullptr) {
    std::cout << "left not made";
  }

  // HuffNode *currentNode = root;
  // for (char c : holder) {
  //   if (c == '1') {
  //     currentNode = currentNode->right;
  //     std::cout << " works-right ";
  //   } else if (c == '0') {
  //     currentNode = currentNode->left;
  //     std::cout << " works-left ";
  //   }

  //   if (currentNode->left == nullptr && currentNode->right == nullptr) {
  //     std::cout << currentNode->letter; // Output the decoded character
  //     currentNode = root;               // Reset to root for the next
  //   }
  // }
}