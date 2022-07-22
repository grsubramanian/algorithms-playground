#include <bits/stdc++.h>
using namespace std;
// Write any include statements here

long long getSecondsElapsed(long long C, int N, vector<long long> A, vector<long long> B, long long K) {

  vector<int> index(N);
  for (int i = 0; i < N; i++) {
    index[i] = i;
  }
  sort(index.begin(), index.end(), [& A](int i, int j) { return A[i] < A[j]; });
  
  long long T = 0; // Tunnel time per full rotation.
  for (int i = 0; i < N; i++) {
    T += (B[index[i]] - A[index[i]]); // could also just do B[i] - A[i]. Order does not matter here.
  }
  
  long long F = K / T; // Number of full rotations that can be made without exhausting the total tunnel time budget.
  long long R = K % T; // Tunnel time budget for the last non-full rotation wherein there is at least one tunnel that cannot be covered fully.
  
  if (R > 0) {    
    long long G = 0; // Time spent in last non-full rotation wherein there is at least one tunnel that cannot be covered fully exhausting the tunnel time budget R.
    long long r = 0; // Tunnel time in last non-full rotation.
    long long prevTEnd = 0;
    for (int i = 0; i < N; i++) {
      long long tStart = A[index[i]];
      long long tEnd = B[index[i]];
      
      // cout << "G = " << G << ", r = " << r << ", A[i] = " << tStart << ", B[i] = " << tEnd << endl;
      G += (tStart - prevTEnd); // time spent in the non-tunnel portion between the previous tunnel (if any) and this one.
      
      long long deltar = R - r;
      long long deltat = tEnd - tStart;
      if (deltar > deltat) {
        r += deltat;
        G += deltat;
      } else {
        r += deltar;
        G += deltar;
        break; // This must happen at least once, since this is guaranteed to be a non-full rotation wherein there is at least one tunnel that cannot be covered fully.
      }
      prevTEnd = tEnd;
    }
    
    return C * F + G;
    
  } else {
    // We need to discount for the time taken between the last tunnel and the end of the rotation.
    return C * F - (C - B[index.back()]);
  }
}

