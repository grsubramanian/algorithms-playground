#include <bits/stdc++.h>
using namespace std;
// Write any include statements here

int getMinimumDeflatedDiscCount(int N, vector<int> R) {

  vector<int> Rcpy(R);
  for (int i = 1; i < N; i++) {
    for (int j = i - 1; j >= 0; j--) {
      if (Rcpy[j + 1] > Rcpy[j]) {
        break;
      }
      
      Rcpy[j] = Rcpy[j + 1] - 1;
      if (Rcpy[j] < 1) {
        return -1; // not possible.
      }
    }
  }
  
  int ans = 0;
  for (int i = 0; i < N; i++) {
    if (Rcpy[i] != R[i]) {
      ans++;
    }
  }
  
  return ans;
}

