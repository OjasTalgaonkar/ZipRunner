#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

struct HuffNode {
  char letter;
  int freq;
  HuffNode *right;
  HuffNode *left;
};

struct Compare {
  bool operator()(HuffNode a, HuffNode b) {
    // Custom comparison: smallest element has the highest priority
    return a.freq > b.freq;
  }
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

    std::sort(huffnodes.begin(), huffnodes.end(),
              [](const HuffNode &a, const HuffNode &b) {
                return a.freq < b.freq;
              }); // sorts the vector in ascending order by frequency

    std::priority_queue<HuffNode, std::vector<HuffNode>, Compare> tree;

    for (HuffNode temp : huffnodes) {
      std::cout << temp.letter << temp.freq << " ";
    }
  }
}
