#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define LL long long
#define VLL vector<LL>

LL mod(LL x) { return x % 1000000007; }

LL add(LL a, LL b) { return mod(a + b); }

LL mul(LL a, LL b) { return mod(a * b); }

LL pow(LL a, LL b) {
  LL ans = 1;
  while (b) {
    if (b % 2) {
      ans = mul(ans, a);
    }
    a = mul(a, a);
    b /= 2;
  }
  return ans;
}

LL computeCost(string const & s, int start, int end) {
  LL ans = 0;
  int nOnes = 0;
  for (int i = end; i >= start; i--) {
    if (s[end] == '1') {
      ans = add(ans, (end - i) - nOnes);
      nOnes++;
    }
  }
  return ans;
}

// Cost to swap a batch of ones over a batch of zeros.
LL computeCost(LL nOnes, LL nZeros) {
  return mul(nOnes, nZeros);
}

int main() {
  string s; cin >> s;
  VLL nOnes;
  VLL nZeros;
  VLL costs;
  VLL qPos;
  int x = 0, y = 0, start = 0;
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == '?') {
      nOnes.push_back(x);
      nZeros.push_back(y);
      costs.push_back(computeCost(s, start, i - 1));
      qPos.push_back(i);
      x = y = 0;
      start = i + 1;
    } else {
      x += s[i] == '1';
      y += s[i] == '0';
    }
  }
  nOnes.push_back(x);
  nZeros.push_back(y);
  costs.push_back(computeCost(s, start, s.size() - 1));
  LL totalCost = 0;
  for (LL cost : costs) {
    totalCost = add(totalCost, cost);
  }
  if (qPos.empty()) {
    cout << totalCost << endl;
    return 0; 
  }

  VLL nZerosSuffix(nZeros.size());
  nZerosSuffix[nZeros.size() - 1] = nZeros[nZeros.size() - 1];
  for (int k = nZeros.size() - 2; k >= 0; k--) {
    nZerosSuffix[k] = nZerosSuffix[k + 1] + nZeros[k];
  }

  // Compute all unconditional costs.
  LL ans = mul(totalCost, pow(2, qPos.size()));
  for (int k = 0; k < nOnes.size() - 1; k++) {
    ans = add(ans, mul(computeCost(nOnes[k], nZerosSuffix[k + 1]), pow(2, qPos.size())));
  }
  
  VLL nOnesPrefix(nOnes.size());
  nOnesPrefix[0] = nOnes[0];
  for (int k = 1; k < nOnes.size(); k++) {
    nOnesPrefix[k] = nOnesPrefix[k - 1] + nOnes[k];
  }

  // Compute conditional costs.
  int numQ = qPos.size();
  for (int k = numQ - 1; k >= 0; k--) {
    // Case where question mark is 0.
    ans = add(ans, mul(computeCost(nOnesPrefix[k], 1), pow(2, numQ - 1)));
    if (k > 0) {
      ans = add(ans, mul(computeCost(k, 1), pow(2, numQ - 2)));
    }

    // Case where question mark is 1.
    ans = add(ans, mul(computeCost(1, nZerosSuffix[k + 1]), pow(2, numQ - 1)));
  }
  cout << ans << endl;
  return 0;
}
