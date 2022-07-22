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
  if (lastDigit == 0) {
    return false;
  }
  x /= 10;
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

int getNextUniform(long long x) {
  // Assume not uniform.

  int nx = getNumDigits(x);
  int msdx = getMostSignificantDigit(x);
  long long ans = 0;
  while (x > 0) {
    ans *= 10;
    ans += msdx;
    x /= 10;
  }
  return ans;
}

// The problem is with this method. It makes the wrong assumption that
// if the MSD is 1, then the number of digits in the previous uniform number is smaller.
// This is not true. Consider the number 12 for example. The smaller uniform number is 11.
int getPreviousUniform(long long x) {
  // Assume not uniform.

  int nx = getNumDigits(x);
  int msdx = getMostSignificantDigit(x);
  
  bool oneFewerDigit;
  int digitToUse;
  if (msdx == 1) {
    // previous uniform number has 1 fewer number of digits.
    oneFewerDigit = true;
    digitToUse = 9;
  } else {
    oneFewerDigit = false;
    digitToUse = msdx - 1;
  }
  
  long long ans = 0;
  while (x > 0) {
    ans *= 10;
    ans += digitToUse;
    x /= 10;
  }
  
  if (oneFewerDigit) {
    ans /= 10;
  }
  return ans;
}


int getUniformIntegerCountInInterval(long long A, long long B) {

  int nA = getNumDigits(A);
  int nB = getNumDigits(B);
  
  int msdA = getMostSignificantDigit(A); // This is the digit with which the next uniform number at or after A starts.
  bool iuA = isUniform(A);
  long long uA = iuA ? A : getNextUniform(A);
  int msduA = msdA;

  int msdB = getMostSignificantDigit(B);
  bool iuB = isUniform(B);
  long long uB = iuB ? B : getPreviousUniform(B);
  int nuB = iuB ? nB : getNumDigits(uB);
  int msduB = iuB ? msdB : getMostSignificantDigit(uB);
  
  int ans = 0;
  if (nB > nA) {
    ans += 9 * (nB - nA - 1); // for each number of digits in between, there are 9 uniform numbers.
    ans += (9 - msduA + 1); // for the uniform numbers larger or equal than A but with the same number of digits as A.
    ans += ((nuB == nB) ? msduB : 0); // for the uniform numbers smaller than or equal to B but with the same number of digits as B.
  } else {
    if (uA <= uB) {
      ans += (msduB - msduA + 1); // just including the uniform numbers at or just after A, and equal to B or before B, with the same number od digits as A and B.
    }
  }
  
  return ans;
}

int main(int argc, char ** argv) {

  cout << getMostSignificantDigit(1234912) << ", " << getMostSignificantDigit(920) << endl;

  cout << getNumDigits(489299012) << ", " << getNumDigits(2) << endl;

  cout << isUniform(7777) << ", " << isUniform(212) << endl;

  cout << getNextUniform(99) << ", " << getNextUniform(101) << ", " << getNextUniform(4444) << ", " << getNextUniform(2011) << endl;

  cout << getPreviousUniform(101) << ", " << getPreviousUniform(212) << ", " << getPreviousUniform(4444444) << ", " << getPreviousUniform(9099) << endl;

}
