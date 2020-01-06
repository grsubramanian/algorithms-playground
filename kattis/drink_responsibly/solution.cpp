#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

int bt(vector<int> const & cost, vector<double> const & unit, int M, double U, int pos, map<tuple<int, double, int>, int> & memo) {
  tuple<int, double, int> tup(M, U, pos);
  auto it = memo.find(tup);
  if (it != memo.end()) {
    return it->second;
  }

  if (pos == cost.size()) {
    bool nothingLeft = (M == 0) && (U == 0);
    return nothingLeft ? 0 : -1;
  }

  int maxdrinks;
  if (cost[pos] == 0 && unit[pos] == 0) {
    maxdrinks = 0; // no point drinking free non-alcoholic drinks.
  } else {
    if (cost[pos] > 0) {
      maxdrinks = M / cost[pos];
    } else {
      maxdrinks = numeric_limits<int>::max();
    }
    if (unit[pos] > 0) {
      maxdrinks = min(maxdrinks, (int) (U / unit[pos]));
    }
  }

  int drinks = 0;
  for (; drinks <= maxdrinks; drinks++) {
    int sub_drinks = bt(cost, unit, M - drinks * cost[pos], U - drinks * unit[pos], pos + 1, memo);
    if (sub_drinks >= 0) {
      break;
    }
  }
  if (drinks == (maxdrinks + 1)) {
    drinks = -1;
  }
  memo.insert({tup, drinks});
  return drinks;
}

int main() {
  double m, U; int d;
  cin >> m >> U >> d;
  int M = m * 100;

  vector<int> cost;
  vector<double> unit;
  vector<string> name;
  for (int i = 0; i < d; i++) {
    string s; cin >> s;
    name.emplace_back(s);
    
    int strength; cin >> strength;
    int num, den; char dummy; cin >> num >> dummy >> den;
    double num_units = ((double) strength) / den;
    unit.push_back(num_units);
    
    double c; cin >> c;
    cost.push_back(c * 100);
  }

  map<tuple<int, double, int>, int> memo;
  bt(cost, unit, M, U, 0, memo);

  if (memo[make_tuple(M, U, 0)] < 0) {
    cout << "IMPOSSIBLE" << endl;
  } else {
    int Mtemp = M;
    double Utemp = U;
    for (int i = 0; i < d; i++) {
      int drinks = memo[make_tuple(Mtemp, Utemp, i)];
      if (drinks > 0) {
        cout << name[i] << " " << drinks << endl;
      }
      Mtemp -= drinks * cost[i];
      Utemp -= drinks * unit[i];
    }
  }

  return 0;
}
