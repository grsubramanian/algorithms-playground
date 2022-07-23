#include <algorithm>
#include <iostream>

using namespace std;

class Rational {
  public:
    Rational(long long num, long long den) : num_(num), den_(den) {}
    Rational(long long longval) : num_(longval), den_(1) {}
    Rational(Rational const & other) : num_(other.num()), den_(other.den()) {}

    long long num() const { return num_; }
    long long den() const { return den_; }

    Rational operator+(Rational const & other) {
      return Rational(num_ * other.den() + den_ * other.num(), den_ * other.den());
    }

    static Rational reverse(Rational const & r) {
      return Rational(r.den(), r.num());
    }

  private:
    long long num_;
    long long den_;
};

ostream & operator<<(ostream & o, Rational const & r) {
  o << "(" << r.num() << "," << r.den() << ")";
  return o;
}

long long partial_base(long long i) {
  if (i % 3 == 0) {
    return 2 * i / 3;
  }

  return 1;
}

Rational get_convergent(int num) {
  Rational curr(partial_base(num));
  for (long long i = num-1; i >= 2; i--) {
    Rational curr_rev = Rational::reverse(curr);
    curr = curr_rev + Rational(partial_base(i));
  }

  Rational ans(Rational::reverse(curr) + Rational(2));
  return ans;
}

int main() {
  for (int i = 2; i < 100; i++) {
    Rational ans(get_convergent(i));
    cout << "i = " << i << ", ans = " << ans << endl;
  }
  return 0;
}
