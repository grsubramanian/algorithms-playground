#include <bits/stdc++.h>
using namespace std;
// Write any include statements here

int getNumThrees(int numOnes, int numTwos, vector<int> const & S) {
  
  int numThrees = 0;
  for (int s : S) {
    
    int sM3 = s % 3;
    if (sM3 == 0) {
      if (numOnes == 1 && numTwos == 1) {
        numThrees = max(numThrees, (s - 3) / 3);
      } else {
        numThrees = max(numThrees, s / 3); 
      }
    } else if (sM3 == 1) {
      if (numOnes == 1) {
        numThrees = max(numThrees, (s - 1) / 3);
      } else {
        if (numTwos == 2 && s >= 4) {
          numThrees = max(numThrees, (s - 4) / 3);
        } else {
          return numeric_limits<int>::max() - 3; // indicates no solution.
        }
      }
    } else {
      // sM3 == 2
      if (numTwos > 0) {
        numThrees = max(numThrees, (s - 2) / 3);
      } else {
        return numeric_limits<int>::max() - 3; // indicates no solution.
      }
    }
    
  }
  return numThrees;
}

int getMinProblemCount(int N, vector<int> S) {
  
  bool needOnes = false;
  bool needTwos = false;
  
  for (int s : S) {
    int sM3 = s % 3;
    if (sM3 == 1) {
      needOnes = true;
    } else if (sM3 == 2) {
      needTwos = true;
    }
  }
  
  int ans;
  if (!needOnes) {
    if (!needTwos) {
      // Need only 3-point problems.
      ans = getNumThrees(0, 0, S);
    } else {
      // Need a single 2-point problem, and rest all 3-point problems.
      ans = 1 + getNumThrees(0, 1, S);
    }
  } else {
    if (!needTwos) {
      // Need a single 1-point problem, and rest all 3-point problems.
      ans = 1 + getNumThrees(1, 0, S);
    } else {
      // Most complex case.
      // If we pick 1 1-point problem, and 1 2-point problem, we could save one one 3-point problem.
      ans = 1 + 1 + getNumThrees(1, 1, S);
      
      // If we pick 2 2-point problems, we could use those to replace a 1-point problem, and a 3-point problem.
      ans = min(ans, 2 + getNumThrees(0, 2, S));
    }
  }
  
  return ans;
}

