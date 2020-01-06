#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <utility>

using namespace std;

typedef int LEVEL;
typedef int POS_IN_LEVEL;

int computeSequenceNumber(pair<LEVEL, POS_IN_LEVEL> const & position) {
  return pow(2, position.first) + position.second;
}

pair<LEVEL, POS_IN_LEVEL> childPosition(pair<LEVEL, POS_IN_LEVEL> const & parentPosition, bool left) {
  return make_pair(parentPosition.first + 1, 2 * parentPosition.second + !left);
}

pair<LEVEL, POS_IN_LEVEL> computePosition(int p, int q) {
  if (p == 1 && q == 1) {
    return make_pair(0, 0);
  }

  if (p > q) {
    return childPosition(computePosition(p - q, q), false); 
  } else {
    return childPosition(computePosition(p, q - p), true);
  }
}

int main() {
  int P; cin >> P;
  for (int t = 0; t < P; t++) {
    int K, p, q;
    scanf("%d %d/%d", &K, &p, &q);
    pair<LEVEL, POS_IN_LEVEL> position = computePosition(p, q);
    int n = computeSequenceNumber(position);
    cout << K << " " << n << endl;    
  }
  return 0;
}
