#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <istream>
#include <algorithm>
#include <iostream>

#include "readverify.h"

using std::string; using std::vector;
using std::ifstream; using std::istringstream;

vector<string> tokstring(string line) {
  istringstream str(line);
  std::istream_iterator<string> it(str);
  std::istream_iterator<string> end;
  vector<string> res(it, end);
  return res;
}

vector< vector<string> > readVerify(string fileIn) {

  // Abrir arquivo
  ifstream f(fileIn);

  string line;
  vector< vector<string> > words;
  // Ler arquivo até o fim
  while(std::getline(f, line)) {
    vector<string> w = tokstring(line);
    words.push_back(w);
  }

  return words;
}
