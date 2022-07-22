// DOES NOT WORK YET.
//

#include <bits/stdc++.h>
using namespace std;

template<typename T>
void print(vector<T> const & v) {
  cout << "[";
  for (T const & t: v) {
    cout << t << ", ";
  }
  cout << "]\n";
}

vector<int> getTopFrontier(vector<double> const & xValues, vector<double> const & yValues) {
  // Sort by decreasing x values, and for a given x value by decreasing y values.
  int N = xValues.size();
  vector<int> index(N);
  for (int i = 0; i < N; i++) {
    index[i] = i;
  }
  sort(index.begin(), index.end(), [&xValues, &yValues](int i, int j) {
    if (xValues[i] > xValues[j]) {
      return true;
    } else if (xValues[i] < xValues[j]) {
      return false;
    }
    return yValues[i] > yValues[j];
  });
  // print(index);

  vector<int> frontier;
  double threshold = 0;
  for (int i = 0; i < N; i++) {
    int idx = index[i];
    if (yValues[idx] <= threshold) {
      continue;
    } else {
      threshold = yValues[idx];
      frontier.push_back(idx);
    }
  }
  return frontier;
}

vector<int> getWorthyFirstWarriors(vector<double> const & impact, vector<double> const & health) {
  return getTopFrontier(impact, health);
}

vector<int> getWorthySecondWarriors(vector<double> const & impact, vector<double> const & damage) {
  return getTopFrontier(impact, damage);
}

double computeImpact(double h1, double d1, double h2, double d2) {
  return h1 * (d1 + d2) + h2 * d2;
}

double removeAndHandleDuplicates(
  vector<int> const & H, vector<int> const & D, int B,
  vector<double> & health, vector<double> & damage, vector<double> & impact) {

  double bestSolutionUsingDuplicatedWarriors = 0;

  map<pair<int, int>, int> warriorCount;

  for (int i = 0; i < H.size(); i++) {
    int h = H[i];
    int d = D[i];
    auto it = warriorCount.find(make_pair(h, d));
    if (it == warriorCount.end()) {
      // first occurrence.
      warriorCount.insert(make_pair(make_pair(h, d), 1));
      health.push_back(h);
      damage.push_back(d);
      impact.push_back(((double) h) * d);
    } else {
      if (it->second == 1) {
        bestSolutionUsingDuplicatedWarriors = max(bestSolutionUsingDuplicatedWarriors, computeImpact(h, d, h, d));
      }
      it->second++;
    }
  }
  return bestSolutionUsingDuplicatedWarriors / B;
}

double getMaxDamageDealtBruteForce(
  vector<double> const & health,
  vector<double> const & damage,
  int B,
  vector<int> const & worthyFirstWarriors,
  vector<int> const & worthySecondWarriors) {

  double ans = 0;
  for (int wfw : worthyFirstWarriors) {
    for (int wsw : worthySecondWarriors) {
      if (wfw == wsw) {
        continue;
      }
      ans = max(ans, computeImpact(health[wfw], damage[wfw], health[wsw], damage[wsw]));
    }
  }
  return ans / B;
}

double getMaxDamageDealt(int N, vector<int> H, vector<int> D, int B) {

  // First of all, if there are duplicate warriors, we'll up-front consider those. This should only take
  // O(N), since for each duplicated warrior, we only have to try the combo once.

  // 1] Consider two warriors W1 and W2. If either D1 > D2 and H1 = H2, or D1 = D2 and H1 > H2,
  // then W1 could replace W2 either as the first or second warrior to fight the boss.

  // 2] Similarly, if either D1*H1 > D2*H2 and H1 = H2, or D1*H1 = D2*H2 and H1 > H2,
  // then W1 could replace W2 as the first warrior to fight the boss.

  // 3] And yet again, if either D1*H1 > D2*H2 and D1 = D2, or D1*H1 = D2*H2 and D1 > D2,
  // then W1 could replace W2 as the second warrior to fight the boss.

  // All three of the above are similar problems, and can be solved by plotting
  // the corresponding points in a 2D plane. For the first problem, we'd plot (D, H), for
  // the second (D*H, H) and the third (D*H, D). The problem boils down to finding the top-most
  // frontier, which can be solved in O(N * logN) time.

  // If the frontier contains only a single point, then we could use that point
  // as the first or second warrior, and find the complementary warrior from the rest. There are some
  // edge cases around duplicate warriors which we'll have to handle properly.

  // After we have done this pre-filtering, in case we have more than one worthy warrior to go in
  // as the first and more than one worthy warrior to go in as the second, then we need an efficient
  // algorithm to pick the optimal pair. We can't try out all possibilities since it will take O(N^2)
  // time in general.

  // If we can identify for each warrior that could go in second, the health range of the first warrior
  // for which the second warrior is an optimal pairing, then we're done, because we could then iterate
  // through each possible first warrior, and use binary search to identify the second warrior who they
  // are best paired with. This can run in O(N * logN) time. So, all we need to do is identify the health
  // ranges. Given a first warrior with health h, the additional damage done by a second warrior (D1, H1) is
  // equal to D1*h + D1*H1. We could model each candidate second warrior as a straight 2D x-y line with
  // y-intercept D*H, and slope D. The x-axis represents health in this setup. Because we have already
  // eliminated unworthy / identical warriors, we can be sure that there don't exist two lines such that
  // one has both greater y-intercept and greater slope. These lines will then form a piecewise linear
  // top frontier. Each piece represents a range of x-values (H in our case) for which the top frontier
  // line possesses the highest y-value (total impact in our case). And that's all the setup required
  // for doing the binary search mentioned above.

  ///////////
  // Phase 1: Detect and handle duplicates.
  ///////////

  vector<double> health;
  vector<double> damage;
  vector<double> impact;

  double ans = removeAndHandleDuplicates(H, D, B, health, damage, impact);
  print(health);
  print(damage);
  print(impact);

  ///////////
  // Phase 2: Eliminate unworthy warriors.
  ///////////

  vector<int> allWarriors(health.size());
  for (int i = 0; i < health.size(); i++) {
    allWarriors[i] = i;
  }

  vector<int> worthyFirstWarriors = getWorthyFirstWarriors(impact, health);
  print(worthyFirstWarriors);
  vector<int> worthySecondWarriors = getWorthySecondWarriors(impact, damage);
  print(worthySecondWarriors);
  if (worthyFirstWarriors.size() < 20) {
    ans = max(
      ans,
      getMaxDamageDealtBruteForce(health, damage, B, worthyFirstWarriors, allWarriors));
  }

  if (worthySecondWarriors.size() < 20) {
    ans = max(
      ans,
      getMaxDamageDealtBruteForce(health, damage, B, allWarriors, worthySecondWarriors));
  }

  ///////////
  // Phase 3: Efficiently solve for optimal solution given worthy warriors.
  ///////////
  // TODO
  return ans;
}
