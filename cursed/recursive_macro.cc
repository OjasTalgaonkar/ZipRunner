#include <iostream>
#define hello(x) x > 0 ? hello(x - 1) : "recursed on"

int main() { std::cout << (hello(7)); } // doesnt work btw, macros cant eval