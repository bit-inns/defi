#include <iostream>

#include "blob.h"


int main(int argc, char* argv[]) {
  using uint16t = blob<16>;
  uint16t n("f1a8"), m("0001");
  uint16t i("0f02"), j("0f02");
  std::cout << (n > m ? "true" : "false") << std::endl;
  std::cout << (i == j ? "true" : "false") << std::endl;
  std::cout << n << "\n" << m << std::endl;
  return 0;
}