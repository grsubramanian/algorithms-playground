#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

#define VI vector<int>
#define SI set<int>
#define VSI vector<SI>

bool contains(int selected, int bean) {
  return selected & (1 << bean);
}

void sett(int & selected, int bean) {
  selected |= (1 << bean);
}

void unsett(int & selected, int bean) {
  selected &= ~(1 << bean);
}

int bt(VI const & num, VSI const & fbeans, int farmer, int & selected) {
  int ans = 0;
  if (farmer == fbeans.size()) {
    for (int b = 0; b < num.size(); b++) {
      if (!contains(selected, b)) {
        ans += num[b];
      }
    }
  } else {
    bool flag = false;
    for (int b : fbeans[farmer]) {
      if (contains(selected, b)) {
        flag = true;
      }
    }
    if (flag) {
      ans = bt(num, fbeans, farmer + 1, selected);
    } else {
      for (int b : fbeans[farmer]) {
        sett(selected, b);
        ans = max(ans, bt(num, fbeans, farmer + 1, selected));
        unsett(selected, b);
      }
    }
  }
  return ans;
}

int main() {
  int B; cin >> B;
  VI num(B);
  for (int b = 0; b < B; b++) {
    cin >> num[b];
  }
  int T; cin >> T;
  VSI fbeans(T, SI());
  for (int t = 0; t < T; t++) {
    int M; cin >> M;
    for (int b = 0; b < M; b++) {
      int temp; cin >> temp;
      fbeans[t].insert(temp - 1);
    }
  }
  int selected = 0;
  cout << bt(num, fbeans, 0, selected) << endl;
  return 0;
}
