#define INCBIN_PREFIX txt_
#define out(x) std::cout << x << std::endl

#include <iostream>
#include <string>

#include "../../incbin.h"

INCBIN(1_, "1.txt");
INCBIN(2_, "2.txt");

INCBIN(f1_, "folder/1.txt");
INCBIN(f2_, "folder/2.txt");

INCBIN(f11_, "folder/1/1.txt");
INCBIN(f12_, "folder/1/2.txt");
INCBIN(f21_, "folder/2/1.txt");
INCBIN(f22_, "folder/2/2.txt");

int
main(int argc, char* argv[])
{
  out((char*)txt_1_Data);
  out((char*)txt_2_Data);

  out((char*)txt_f1_Data);
  out((char*)txt_f2_Data);

  out((char*)txt_f11_Data);
  out((char*)txt_f12_Data);
  out((char*)txt_f21_Data);
  out((char*)txt_f22_Data);

  std::string dir = argv[0];
  int splitter = std::max((signed int)dir.find_last_of("\\"),
                          (signed int)dir.find_last_of("/"));

  dir = dir.substr(0, splitter);

  std::cout << "Current dir: " << dir << std::endl;
  std::cout << "Check it, all IncBin files are here!" << std::endl;

  return 0;
}
