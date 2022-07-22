#include <iostream>
#include <vector>

using namespace std;

long long getMinRotationTime(long long x, long long y, long long N) {
  return min(abs(x - y), N - max(x, y) + min(x, y));
}

// code uses 1-indexing.
int get(vector<int> const & C, int index1) {
  return C[index1 - 1];
}

long long getMinCodeEntryTime(int N, int M, vector<int> C) {
  
  vector<vector<long long>> memo(M + 1, vector<long long>(M, numeric_limits<long long>::max()));
  memo[1][0] = getMinRotationTime(1, get(C, 1), N);
  for (int i = 2; i <= M; i++) {
    memo[i][0] = getMinRotationTime(get(C, i - 1), get(C, i), N) + memo[i - 1][0];
    cout << "memo[" << i << "][0] = " << memo[i][0] << endl;
    
    memo[i][i - 1] = getMinRotationTime(1, get(C, i), N) + memo[i - 1][0];
    cout << "memo[" << i << "][" << (i - 1) << "] = " << memo[i][i - 1] << endl;
    
    for (int j = 1; j < i - 1; j++) {
      memo[i][j] = getMinRotationTime(get(C, i - 1), get(C, i), N) + memo[i - 1][j];
      cout << "memo[" << i << "][" << j << "] = " << memo[i][j] << endl;
 
      memo[i][i - 1] = min(memo[i][i - 1], getMinRotationTime(get(C, j), get(C, i), N) + memo[i - 1][j]);
      cout << "memo[" << i << "][" << (i - 1) << "] updated to " << memo[i][i - 1] << endl;
    }
  }
  
  long long ans = numeric_limits<long long>::max();
  for (int j = 0; j < M; j++) {
    ans = min(ans, memo[M][j]);
  }
  return ans;
}

int main(int argc, char ** argv) {
  cout << getMinCodeEntryTime(3, 3, {1, 2, 3}) << endl;
}
