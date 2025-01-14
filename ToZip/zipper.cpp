#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

struct HuffNode {
  char letter;
  int freq;
  HuffNode *left;
  HuffNode *right;
};

int main() {
  std::ifstream file("input.txt");
  std::ofstream file2("output.txt");

  HuffNode start;
  start.freq = 0;
  start.left = nullptr;
  start.right = nullptr;

  if (file.is_open()) {
    std::string line;
    std::vector<HuffNode> huffnodes;
    while (std::getline(file, line)) {
      for (char single : line) {
        for (HuffNode &temp : huffnodes) {
          if (temp.letter == single) {
            temp.freq++;
            goto outer_loop_continue;
          }
        }
        {
          HuffNode node{single, 1, nullptr, nullptr};
          huffnodes.push_back(node);
        }

      outer_loop_continue:
        continue;
      }
    }
    for (HuffNode temp : huffnodes) {
      std::cout << temp.letter << temp.freq << " ";
    }
  }
}

void addHuffNode(HuffNode *start, char single) {}
