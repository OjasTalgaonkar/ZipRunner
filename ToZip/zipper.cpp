#include <fstream>
#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

struct HuffNode {
  char letter;     // Character (leaf node) or '\0' (internal node)
  int freq;        // Frequency of the character
  HuffNode *left;  // Left child
  HuffNode *right; // Right child

  HuffNode(char l, int f, HuffNode *lc = nullptr, HuffNode *rc = nullptr)
      : letter(l), freq(f), left(lc), right(rc) {}
};

struct Compare {
  bool operator()(const HuffNode *a, const HuffNode *b) {
    return a->freq > b->freq; // Higher frequency => lower priority
  }
};

void generateEncodingMap(HuffNode *root, const std::string &prefix,
                         std::unordered_map<char, std::string> &encodingMap) {
  if (!root)
    return;

  if (root->letter != '\0') { // Leaf node
    encodingMap[root->letter] = prefix;
  }

  generateEncodingMap(root->left, prefix + "0", encodingMap);
  generateEncodingMap(root->right, prefix + "1", encodingMap);
}

int main() {
  std::ifstream file("input.txt");
  if (!file.is_open()) {
    std::cerr << "Failed to open input file." << std::endl;
    return 1;
  }

  // Frequency map to count occurrences of each character
  std::unordered_map<char, int> freqMap;
  std::string inputData;
  std::string line;

  while (std::getline(file, line)) {
    inputData += line; // Accumulate the input data
    for (char c : line) {
      freqMap[c]++;
    }
  }
  file.close();

  std::priority_queue<HuffNode *, std::vector<HuffNode *>, Compare> tree;

  for (const auto &entry : freqMap) {
    tree.push(new HuffNode(entry.first, entry.second));
  }

  while (tree.size() > 1) {
    HuffNode *left = tree.top();
    tree.pop();
    HuffNode *right = tree.top();
    tree.pop();

    HuffNode *parent =
        new HuffNode('\0', left->freq + right->freq, left, right);

    tree.push(parent);
  }

  HuffNode *root = tree.top();
  tree.pop();

  // Generate encoding map
  std::unordered_map<char, std::string> encodingMap;
  generateEncodingMap(root, "", encodingMap);

  std::ofstream outputFile("output.bin", std::ios::binary);
  if (!outputFile.is_open()) {
    std::cerr << "Failed to open output file." << std::endl;
    return 1;
  }

  unsigned char buffer = 0;
  int bitCount = 0;

  // Write encoded data as binary
  for (char c : inputData) {
    const std::string &code = encodingMap[c];
    for (char bit : code) {
      buffer = (buffer << 1) | (bit - '0'); // Add bit to buffer
      bitCount++;

      if (bitCount == 8) {
        outputFile.put(buffer); // Write full byte
        buffer = 0;
        bitCount = 0;
      }
    }
  }

  // Write any remaining bits (if not a full byte)
  if (bitCount > 0) {
    buffer = buffer << (8 - bitCount); // Pad remaining bits with 0
    outputFile.put(buffer);
  }

  outputFile.close();
  std::cout << "Huffman encoding written to output.bin as binary." << std::endl;

  return 0;
}
