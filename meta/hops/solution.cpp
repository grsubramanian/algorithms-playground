#include <bits/stdc++.h>
using namespace std;
// Write any include statements here

long long getSecondsRequired(long long N, int F, vector<long long> P) {

  // Groups are contiguous groups of frogs. We'll capture the sizes of these groups
  // and also the gaps between the groups.
  vector<long long> groupSizes;
  vector<long long> gapSizes;

  // To do this efficiently, we'll sort the positions of the frogs.
  sort(P.begin(), P.end());
  
  long long prevFrogPosition = -1;
  for (int i = 0; i < P.size(); i++) {
    if (P[i] > prevFrogPosition + 1) {
      // New group starts.
      groupSizes.push_back(1);

      if (prevFrogPosition >= 1) {
        // We don't care about gaps left of the leftmost frog group.
        gapSizes.push_back(P[i] - prevFrogPosition - 1);  
      }
    } else {
      groupSizes[groupSizes.size() - 1]++;
    }
    
    prevFrogPosition = P[i];
  }
  gapSizes.push_back(N - P.back() - 1); // the gap from the rightmost frog group until the exit lily.
  
  // At this point, for every group, there should be a gap ahead of it. The rightmost gap may be a gap of size 0.
  
  long long ans = 0;
  for (int j = 0; j < groupSizes.size(); j++) {
    ans += gapSizes[j]; // we'll have the group j do a rolling march through the gap ahead of it until either it merges with the group (j + 1) in case there is such a group, or it reaches the end.
    if (j + 1 < groupSizes.size()) {
      groupSizes[j + 1] += groupSizes[j];
    }
  }
  ans += groupSizes.back(); // the fully merged group now does a rolling march to exit.
  return ans;
}

