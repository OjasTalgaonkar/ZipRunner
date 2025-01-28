
#include <fstream>
#include <iostream>
#include <istream>

struct HuffNode {
  char letter;     // Character (leaf node) or '\0' (internal node)
  int freq;        // Frequency of the character
  HuffNode *left;  // Left child
  HuffNode *right; // Right child

  HuffNode(char l) : letter(l) {}
};

struct Compare {
  bool operator()(const HuffNode *a, const HuffNode *b) {
    return a->freq > b->freq; // Higher frequency => lower priority
  }
};

HuffNode *deserializeTree(HuffNode *&root, int &maxNodes, std::ifstream &is) {
  if (maxNodes == 0) {
    return nullptr;
  }

  char nodeType;
  is.get(nodeType); // Read the node type ('L' or 'I')
  maxNodes--;
  std::cout << nodeType << " " << maxNodes;

  if (nodeType == 'N') { // Null node
    return nullptr;
  } else if (nodeType == 'L') { // Leaf node
    char letter;
    is.get(letter);              // Read the letter for the leaf
    root = new HuffNode(letter); // Create a new leaf node
    maxNodes--;
    std::cout << letter;
    deserializeTree(root->left, maxNodes, is); // these two fixed it
    deserializeTree(root->right, maxNodes, is);
    return root;
  } else if (nodeType == 'I') { // Internal node
    root = new HuffNode('\0');  // Create an internal node with no letter
    deserializeTree(root->left, maxNodes, is);  // Build the left subtree
    deserializeTree(root->right, maxNodes, is); // Build the right subtree
  }

  return root;
}

void deserializeWrapper(std::ifstream &is, HuffNode *root) {
  char marker;

  // Ensure the file starts with '%'
  if (!is.get(marker) || marker != '%') {
    throw std::runtime_error("File does not start with '%'");
  }

  // Read the binary number (assume 4 bytes for an `int`)
  int number;
  is.read(reinterpret_cast<char *>(&number), sizeof(number));

  // Check for the closing '%'
  if (!is.get(marker) || marker != '%') {
    throw std::runtime_error("Missing closing '%' for the number.");
  }

  // Print the extracted number
  std::cout << "Number read: " << number << std::endl;

  deserializeTree(root, number, is);

  // Proceed with deserialization logic for the tree...
}

int main() {
  std::ifstream file("output.bin", std::ios::binary); // Open in binary mode
  if (!file.is_open()) {
    std::cerr << "Failed to open the file." << std::endl;
    return 1;
  }

  HuffNode *root = nullptr;

  try {
    deserializeWrapper(file, root);
    // char letter;
    // while (file.get(letter)) {
    //   std::cout << letter;
    // }
  } catch (const std::runtime_error &e) {
    std::cerr << "Error during deserialization: " << e.what() << std::endl;
  }

  file.close();
  return 0;
}