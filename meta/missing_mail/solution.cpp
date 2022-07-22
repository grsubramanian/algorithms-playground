#include <bits/stdc++.h>
using namespace std;
// Write any include statements here

double getMaxExpectedProfit(int N, vector<int> V, int C, double S) {
  
  // Solution idea:
  // We must visit on some day first. Let's say we visit first on day k.
  // We expect the value of items in the room to be = V0 * (1 - S)^k + V1 * (1 - S)^(k - 1) + ... Vk.
  // We'll spend C to get this value, and leave the root empty after collecting things.
  // Now, the problem reduces to the same as before, but with only the remaining days.
  // 
  // Concretely,
  // P(k) - maximum expected profit to be made starting from day k assuming visit on day (k - 1) and leaving the room empty.
  // P(0) - this is the solution we are looking for.
  // Let's solve for P(k).
  // Say that the first day when we visit in day t >= k;
  // We'd expect to collect Vk * (1 - S)^(t - k) + V(k + 1) * (1 - S)^(t - k - 1) + ... Vt.
  // And we'd pay C.
  // Therefore, to optimize, all we need to do is pick some t that maximizes P(k).
  // P(k) = max over all t >=k of [(Vk * (1 - S)^(t - k) + V(k + 1) * (1 - S)^(t - k - 1) + ... Vt) - C + P(t + 1)]
  
  vector<double> maxProfit(N);
  maxProfit[N - 1] = max(0, V.back() - C);
  for (int i = N - 2; i >= 0; i--) {
  
    double expectedValueRemainingOnVisit = 0;
    for (int j = i; j < N; j++) {
      expectedValueRemainingOnVisit *= (1 - S);
      expectedValueRemainingOnVisit += V[j];
      maxProfit[i] = max(maxProfit[i], expectedValueRemainingOnVisit - C + ((j == N - 1) ? 0 : maxProfit[j + 1]));      
    } 
  }
  
  return maxProfit[0];
}

