#include <iostream>
using namespace std;
int main() {
  unsigned char c = 0;
  for (; c < 255; c++) {
    cout << (int) c << ", " << c << endl;
  }
  cout << (int) c << ", " << c << endl;
  return 0;
}
