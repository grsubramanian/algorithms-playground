#include <algorithm>
#include <iostream>

using namespace std;

bool match(int s, int p) {
  int i = (s / 50) % 475;
  for (int j = 0; j < 25; j++) {
    i = (96 * i + 42) % 475;
    if (p == (26 + i)) { return true; }
  }
  return false;
}

int main() {

  int p, x, y; cin >> p >> x >> y;
  int best = 238;
  for (int k = 0; k < 475; k++) {
    if (match(x + 50 * k, p)) {
      best = (k + 1) / 2;
      break;
    }
  }

  int k = 0;
  while ((x - 50) >= y) {
    x -= 50;
    if (match(x, p)) {
      best = 0;
      break;
    }
  }
  cout << best << endl;
  return 0;
}
