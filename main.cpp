#include <iostream>
#include <fstream>
#include <cstdint>

int main() {
  std::fstream file;
  int myuint = 0xFFFF;
  std::cout<<sizeof(myuint);
  file.open("test.bin", std::ios::app | std::ios::binary);
  file.write(reinterpret_cast<char*>(&myuint), sizeof(myuint)); // or with recent C++: reinterpret_cast<std::byte*>
}