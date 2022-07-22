#include <bits/stdc++.h>
using namespace std;
// Write any include statements here

long long getMaxAdditionalDinersCount(long long N, long long K, int M, vector<long long> S) {

  sort(S.begin(), S.end());
  
  long long additional = (S[0] - 1) / (K + 1) + (N - S[M - 1]) / (K + 1);

  for (int i = 1; i < M; i++) {
    long long leftmostAllowedSeatNumberWithinSpace = S[i - 1] + K + 1;
    if (leftmostAllowedSeatNumberWithinSpace >= S[i]) {
      continue;
    }
    
    additional += (S[i] - leftmostAllowedSeatNumberWithinSpace) / (K + 1);
  }
  
  return additional;
}

