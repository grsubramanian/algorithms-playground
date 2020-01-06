#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <vector>

using namespace std;

struct Data {
  int quot;
  int rem;
  int factor;

  Data(int quott, int remm, int factorr)
    : quot(quott), rem(remm), factor(factorr) {}
};

int total_cost(Data & data, vector<int> & cost) {
  int ans = 0;
  if (data.quot > 0) {
    ans += cost[data.quot];
    ans += 2 * data.factor  - 1;
  }

  if (data.rem > 0) {
    ans += 2 * data.rem - 1;
  }

  if (data.quot > 0 && data.rem > 0) {
    ans++;
  }
  ans++;

  return ans;
}

void dp(int N, vector<int> & cost, map<int, Data> & dataMap) {
  if (cost[N] >= 0) { return; }

  Data best(0, N, 1);
  int best_cost = total_cost(best, cost);
  for (int factor = 2; factor <= (N/2); factor++) {
    dp(N / factor, cost, dataMap);
    Data curr(N / factor, N % factor, factor);
    int curr_cost = total_cost(curr, cost);
    if (curr_cost < best_cost) {
      best = curr;
      best_cost = curr_cost;
    }
  }
  dataMap.insert(make_pair(N, best));
  cost[N] = best_cost;
}

void execute(int N, map<int, Data> & dataMap, vector<string> & output) {
 
  if (N == 1) {
    output.push_back("ST A");
  }
  else {
    Data data = dataMap.find(N)->second;
    
    if (data.quot > 0) {
      execute(data.quot, dataMap, output);
      for (int i = 0; i < data.factor; i++) {
        output.push_back("PH A");
      }
      for (int i = 0; i < data.factor - 1; i++) {
        output.push_back("AD");
      }
    }
    if (data.rem > 0) {
      for (int i = 0; i < data.rem; i++) {
        output.push_back("PH X");
      }
      for (int i = 0; i < data.rem - 1; i++) {
        output.push_back("AD");
      }
    }

    if (data.quot > 0 && data.rem > 0) {
      output.push_back("AD");
    }
    output.push_back("PL A");
  }
}

int main() {

  int N; cin >> N;
  if (N == 0) {
    cout << "ZE A" << endl;
  } else {
    vector<int> cost(N + 1, -1);
    cost[0] = 0;
    cost[1] = 1;
    map<int, Data> dataMap;
    dataMap.insert(make_pair(2, Data(0, 2, 1)));

    // Precomputation.
    dp(N, cost, dataMap);

    // Execution.
    vector<string> output;
    output.push_back("ST X"); // always set to 1.
    execute(N, dataMap, output);  
    for (string inst : output) {
      cout << inst << endl;
    }
  }
  cout << "DI A" << endl;
  return 0;
}
