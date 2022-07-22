#include <iostream>
using namespace std;
// Write any include statements here

int getNumDigits(long long x) {
  int ans = 0;
  while (x > 0) {
    ans++;
    x /= 10;
  }
  return ans;
}

bool isUniform(long long x) {
  int lastDigit = x % 10;
  while (x > 0) {
    int digit = x % 10;
    if (digit != lastDigit) {
      return false;
    }
    x /= 10;
  }
  return true;
}

int getMostSignificantDigit(long long x) {
  int ans = 0;
  while (x > 0) {
    int digit = x % 10;
    ans = digit;
    x /= 10;
  }
  return ans;
}

long long createUniform(int digit, int repeat) {
  long long ans = 0;
  for (int i = 0; i < repeat; i++) {
    ans *= 10;
    ans += digit;
  }
  return ans;
}

int getNumUniformNumbersLessThan(long long x) {
  int nx = getNumDigits(x);
  int msdx = getMostSignificantDigit(x);
  
  // Check if the uniform number created with the most significant digit is strictly smaller than the given number.
  // If so, we can add that into the counting as well.
  return 9 * (nx - 1) + (msdx - 1) + (createUniform(msdx, nx) < x ? 1 : 0);
}

int getUniformIntegerCountInInterval(long long A, long long B) {

  int nulA = getNumUniformNumbersLessThan(A);
  int nulB = getNumUniformNumbersLessThan(B);
  return nulB - nulA + (isUniform(B) ? 1 : 0);
}

int main(int argc, char ** argv) {
  for (long long i = 1; i < 1000000000000L; i++) {
    cout << "Ans for i = " << i << " = " << getNumUniformNumbersLessThan(i) << endl;
  }
}
