#include <algorithm>
#include <iostream>

using namespace std;

#define LL long long

int main() {
  int T; cin >> T;
  while (T--) {
    LL x, y, p, q; cin >> x >> y >> p >> q;
    LL C1 = q, C2 = (q - p), C3 = (q * x - p * y);
    if (C3 == 0) {
      cout << 0 << endl;
    }
    if (q == p) {
      cout << -1 << endl;
    }

    LL te = (-C3) % C2;
    LL smallest_b = max(0, (te == 0) ? -C3 / C2 : -C3 / C2 + 1);
    
    LL te2 = C2 * smallest_b + C3;
    LL te3 = te2 % C1;
    LL te4 = C1 - te3;

  }

  return 0;
}
