#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <vector>

using namespace std;

#define PI pair<int, int>
#define VPI vector<PI>
#define VVPI vector<VPI>

int main() {
  int N, M; cin >> N >> M;
  if (N == 1) {
    cout << "impossible" << endl;
    return 0;
  }

  VVPI orig_sched(N);
  VVPI delay_sched(N);
  while (M--) {
    int X, S, T, L; cin >> X >> S >> T >> L;
    orig_sched[X].emplace_back(S, T); 
    delay_sched[X].emplace_back(S + L, T + L); 
  }

  int prev_end = 0;
  for (int i = 1; i < N; i++) {
    int earliest_next_end = numeric_limits<int>::max();
    for (PI const & t : delay_sched[i]) {
      if (t.first >= prev_end) {
        earliest_next_end = min(earliest_next_end, t.second);
      }
    }
    prev_end = earliest_next_end;
    if (prev_end == numeric_limits<int>::max()) {
      break;
    }
  }
  int goal = prev_end - 1800; // we want to book so that we can reach by this time.
  if (goal < 0) {
    cout << "impossible" << endl;
    return 0;
  }

  for (int i = N - 1; i > 1; i--) {
    int latest_next_start = numeric_limits<int>::min();
    for (PI const & t : orig_sched[i]) {
      if (t.second <= goal) {
        latest_next_start = max(latest_next_start, t.first);
      }
    }
    goal = latest_next_start;
    if (goal == numeric_limits<int>::min()) {
      cout << "impossible" << endl;
      return 0;
    }
  }
  int earliest = numeric_limits<int>::max();
  for (PI const & t : orig_sched[1]) {
    if (t.second <= goal) {
      earliest = min(earliest, t.first);
    }
  }
  if (earliest == numeric_limits<int>::max()) {
    cout << "impossible" << endl;
    return 0;
  }

  cout << earliest << endl;
  return 0;
}
