#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define LL long long
#define VLL vector<LL>

LL mymod(LL x) { return x % 1000000007; }

LL myadd(LL a, LL b) { return mymod(a + b); }

LL mymul(LL a, LL b) { return mymod(a * b); }

LL mypow(LL a, LL b) {
  if (b < 0) { return 0; }
  LL ans = 1;
  while (b) {
    if (b % 2) {
      ans = mymul(ans, a);
    }
    a = mymul(a, a);
    b /= 2;
  }
  return ans;
}

int main() {
  string s; cin >> s;
  int N = s.size();
  VLL qPos;
  for (int i = 0; i < N; i++) {
    if (s[i] == '?') { qPos.push_back(i); }
  }

  VLL nOnesPrefix(N);
  nOnesPrefix[0] = (s[0] == '1');
  for (int i = 1; i < N; i++) {
    nOnesPrefix[i] = nOnesPrefix[i - 1] + (s[i] == '1');
  }

  VLL nZerosSuffix(N);
  nZerosSuffix[N - 1] = (s[N - 1] == '0');
  for (int i = N - 2; i >= 0; i--) {
    nZerosSuffix[i] = nZerosSuffix[i + 1] + (s[i] == '0');
  }

  LL baseCost = 0;
  for (int i = 0; i < N; i++) {
    if (s[i] == '1') {
      baseCost = myadd(baseCost, nZerosSuffix[i]);
    }  
  }
  
  int nQ = qPos.size();
  LL ans = mymul(baseCost, mypow(2, nQ));
  LL temp = mypow(2, nQ - 1);
  for (int j = 0; j < nQ; j++) {
    int jqPos = qPos[j];
    ans = myadd(ans, mymul(nOnesPrefix[jqPos], temp));
    ans = myadd(ans, mymul(nZerosSuffix[jqPos], temp));
  }
  
  LL qAns = 0;
  for (int q = 1; q <= nQ; q++) {
    qAns = myadd(mymul(2, qAns), mymul(q - 1, mypow(2, q - 2)));
  }
  ans = myadd(ans, qAns);
  cout << ans << endl;
  return 0;
}
