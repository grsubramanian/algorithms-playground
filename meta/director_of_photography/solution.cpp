#include <bits/stdc++.h>
using namespace std;
// Write any include statements here

vector<int> getCountOfOneCharAfterAnother(int N, string const & C, int X, int Y, char a, char b) {
  
  set<int> work;
  vector<int> output(N);
  
  for (int i = N - 1; i >= 0; i--) {
    
    if ((i + X < N) && (C[i + X] == b)) {
      work.insert(i + X);
    }
    
    if ((i + Y + 1 < N) && (C[i + Y + 1] == b)) {
      work.erase(i + Y + 1);
    }
    
    if (C[i] == a) {
      output[i] = work.size();
    }
  }
  
  return output;
}

vector<int> getCountOfOneCharBeforeAnother(int N, string const & C, int X, int Y, char a, char b) {
  
  set<int> work;
  vector<int> output(N);
  
  for (int i = 0; i < N; i++) {
    
    if ((i - X >= 0) && (C[i - X] == b)) {
      work.insert(i - X);
    }
    
    if ((i - Y - 1 >= 0) && (C[i - Y - 1] == b)) {
      work.erase(i - Y - 1);
    }
    
    if (C[i] == a) {
      output[i] = work.size();
    }
  }
  
  return output;
}

int getArtisticPhotographCount(int N, string C, int X, int Y) {
  long long ans = 0;
  
  // 1] Let's count P..A..B subsequences.
  vector<int> countOfBAfterA = getCountOfOneCharAfterAnother(N, C, X, Y, 'A', 'B');
  vector<int> countOfPBeforeA = getCountOfOneCharBeforeAnother(N, C, X, Y, 'A', 'P');
  for (int i = 0; i < N; i++) {
    ans += ((long long) countOfBAfterA[i]) * countOfPBeforeA[i];
  }
  
  // 2] Let's count B..A..P subsequences.
  vector<int> countOfPAfterA = getCountOfOneCharAfterAnother(N, C, X, Y, 'A', 'P');
  vector<int> countOfBBeforeA = getCountOfOneCharBeforeAnother(N, C, X, Y, 'A', 'B');
  for (int i = 0; i < N; i++) {
    ans += ((long long) countOfPAfterA[i]) * countOfBBeforeA[i];
  }
  
  return ans;
}

