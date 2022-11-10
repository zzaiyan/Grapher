#include "_global.h"

std::vector<int> getnum(std::string s) {
  int x = 0;
  std::vector<int> v;
  for (int i = 0; i < (int)s.length(); i++) {
    if (s[i] >= '0' && s[i] <= '9') {
      while (s[i] >= '0' && s[i] <= '9' && i < (int)s.length())
        x = x * 10 + s[i] - '0', i++;
      v.push_back(x);
      x = 0;
    }
  }
  return v;
}

int MAXV = 10;
std::string Sample_graph =
    "8 0 1 680 0 2 1380 0 3 730 0 4 530 1 2 2600 1 5 960 2 3 2500 3 6 840 4 "
    "5 820 4 6 570 4 7 650 5 7 500 6 7 1140";
