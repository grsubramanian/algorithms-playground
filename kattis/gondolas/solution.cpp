#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <vector>

using namespace std;

#define VI vector<int>
#define VVI vector<VI>
#define PI pair<int, int>
#define VPI vector<PI>
#define VVPI vector<VPI>

void dp(VI const & X, VI const & num, int total, int lg, int G, int pos, VVPI & memo) {
  if (memo[pos][G].first >= 0) {
    return;
  }
  int cost;
  int lmost;
  if (G == 0) {
    cost = 0;
    for (int i = pos; i < X.size(); i++) {
      cost += (total - X[i] + lg) * num[i];  
    }
    lmost = -1;
  } else {
    if (pos + 1 < X.size()) {
      dp(X, num, total, lg, G - 1, pos + 1, memo);
      dp(X, num, total, lg, G, pos + 1, memo);

      int acost = memo[pos + 1][G - 1].first;
      int lmostafter = memo[pos + 1][G].second;
      int bcost = memo[pos + 1][G].first + (lmostafter - X[pos]) * num[pos];
      if (acost < bcost) {
        cost = acost;
        lmost = X[pos];
      } else {
        cost = bcost;
        lmost = lmostafter;
      }
    } else {
      cost = 0;
      lmost = X[pos];
    }
  }
  // cout << "lg = " << lg << ", G = " << G << ", pos = " << pos << ", [" << cost << "," << lmost << "]" << endl; 
  memo[pos][G].first = cost;
  memo[pos][G].second = lmost;
}

int main() {
  int N, T, G; cin >> N >> T >> G;
  int total = 2*T;
  map<int, int> counts;
  for (int i = 0; i < N; i++) {
    int x; cin >> x;
    x %= total;
    auto it = counts.find(x);
    if (it != counts.end()) {
      it->second++;
    } else {
      counts.insert({x, 1});
    }
  }
  VI X;
  VI num;
  for (auto const entry : counts) {
    X.push_back(entry.first);
    num.push_back(entry.second);
  }

  if (G >= X.size()) {
    cout << 0 << endl;
  }
  int lowest = numeric_limits<int>::max();
  VVPI memo(X.size(), VPI(G, make_pair(-1, 0)));
  if (X[0] != 0) {
    dp(X, num, total, 0, G - 1, 0, memo);
    lowest = min(lowest, memo[0][G - 1].first);
  }
  for (int i = 0; i <= X.size() - G; i++) {
    for (VPI & v : memo) {
      for (PI & p : v) {
        p.first = -1;
        p.second = 0;
      }
    }
    int basecost = 0;
    for (int j = 0; j < i; j++) {
      basecost += (X[i] - X[j]) * num[j];
    }
    dp(X, num, total, X[i], G - 1, i + 1, memo);
    lowest = min(lowest, basecost + memo[i + 1][G - 1].first);
  }
  cout << lowest << endl;
  return 0;
}
