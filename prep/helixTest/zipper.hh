#include <fstream>
#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

namespace helix {
struct HuffNode {
  char letter;     // Character (leaf node) or '\0' (internal node)
  int freq;        // Frequency of the character
  HuffNode *left;  // Left child
  HuffNode *right; // Right child

  HuffNode(char l, int f, HuffNode *lc = nullptr, HuffNode *rc = nullptr)
      : letter(l), freq(f), left(lc), right(rc) {}
};

struct Compare {
  bool operator()(const HuffNode *a, const HuffNode *b);
};

void serializeTreeToBuffer(HuffNode *root, ::std::string &buffer,
                           int *bitcount);

void generateEncodingMap(
    HuffNode *root, const ::std::string &prefix,
    ::std::unordered_map<char, ::std::string> &encodingMap);

} // namespace helix