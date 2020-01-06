#include <algorithm>
#include <iostream>

using namespace std;

int main() {
  int N; cin >> N;
  int smallest = 4127;
  bool not_smallest_at_least_once = false;
  for (int i = 0; i < N; i++) {
    int ai, bi; cin >> ai >> bi;
    if (ai != bi) {
      cout << "rated" << endl;
      return 0;
    }
    if (ai > smallest) {
      not_smallest_at_least_once = true;
    }
    smallest = min(smallest, ai);
  }
  if (not_smallest_at_least_once) {
    cout << "unrated" << endl;
  } else {
    cout << "maybe" << endl;
  }
  return 0;
}
