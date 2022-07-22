#include <bits/stdc++.h>
using namespace std;
// Write any include statements here

int getMaximumEatenDishCount(int N, vector<int> D, int K) {

  set<int> typesEaten;
  set<int> indicesEaten;
  
  int ans = 0;
  for (int i = 0; i < N; i++) {
    
    if (typesEaten.find(D[i]) == typesEaten.end()) {
      ans += 1;
      typesEaten.insert(D[i]);
      indicesEaten.insert(i);
    }
    
    if (typesEaten.size() > K) {
      int oldestIndexEaten = *indicesEaten.begin();
      indicesEaten.erase(oldestIndexEaten);
      typesEaten.erase(D[oldestIndexEaten]);
    }
  }
  
  return ans;
}

