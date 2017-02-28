#include <bits/stdc++.h>
using namespace std;

// to lower collision probability, put more prime numbers here
const int hashmod[] = {(int)1e9+7,(int)1e9+9};

const int hashlen = sizeof(hashmod)/sizeof(int);
struct Hash {
  static long long mul;
  static long long div[hashlen];
  static long long power(long long a, long long b, long long m) {
    long long ans = 1;
    while (b > 0) {
      if (b&1) ans = (ans*a)%m;
      b >>= 1;
      a = (a*a)%m;
    }
    return ans;
  }
  static void init() {
    static bool ok;
    if (ok) return;
    ok = true;
    for (int i = 0; i < hashlen; i++) {
      div[i] = power(mul,hashmod[i]-2,hashmod[i]);
    }
  }
  // non-static
  int h[hashlen];
  Hash(char s) {
    memset(h,0,sizeof h);
    operator+=(s);
  }
  Hash(const string& s = "") {
    memset(h,0,sizeof h);
    operator+=(s);
  }
  bool operator<(const Hash& o) const {
    for (int i = 0; i < hashlen; i++) if (h[i] != o.h[i]) return h[i] < o.h[i];
    return false;
  }
  bool operator==(const Hash& o) const {
    for (int i = 0; i < hashlen; i++) if (h[i] != o.h[i]) return false;
    return true;
  }
  bool operator!=(const Hash& o) const {
    for (int i = 0; i < hashlen; i++) if (h[i] != o.h[i]) return true;
    return false;
  }
  Hash& operator+=(char s) {
    int c = s+1;
    for (int i = 0; i < hashlen; i++) h[i] = (h[i]*mul+c)%hashmod[i];
    return *this;
  }
  Hash& operator+=(const string& s) {
    for (char c : s) operator+=(c);
    return *this;
  }
  Hash& operator+=(const Hash& o) {
    for (int i = 0; i < hashlen; i++) h[i] = (h[i]+o.h[i])%hashmod[i];
    return *this;
  }
  Hash& operator-=(char s) {
    int c = s+1;
    for (int i = 0; i < hashlen; i++) {
      h[i] = ((h[i]+hashmod[i]-c)*div[i])%hashmod[i];
    }
    return *this;
  }
  Hash& operator-=(const string& s) {
    for (int i = s.size()-1; 0 <= i; i--) operator-=(s[i]);
    return *this;
  }
  Hash& operator-=(const Hash& o) {
    for (int i = 0; i < hashlen; i++) {
      h[i] = (h[i]+hashmod[i]-o.h[i])%hashmod[i];
    }
    return *this;
  }
  Hash& operator*=(long long pwr) {
    for (int i = 0; i < hashlen; i++) {
      h[i] = (h[i]*power(mul,pwr,hashmod[i]))%hashmod[i];
    }
    return *this;
  }
  Hash& operator/=(long long pwr) {
    for (int i = 0; i < hashlen; i++) {
      h[i] = (h[i]*power(div[i],pwr,hashmod[i]))%hashmod[i];
    }
    return *this;
  }
  Hash operator+(char s) const {
    Hash ans = *this;
    ans += s;
    return ans;
  }
  Hash operator+(const string& s) const {
    Hash ans = *this;
    ans += s;
    return ans;
  }
  Hash operator+(const Hash& o) const {
    Hash ans = *this;
    ans += o;
    return ans;
  }
  Hash operator-(char s) const {
    Hash ans = *this;
    ans -= s;
    return ans;
  }
  Hash operator-(const string& s) const {
    Hash ans = *this;
    ans -= s;
    return ans;
  }
  Hash operator-(const Hash& o) const {
    Hash ans = *this;
    ans -= o;
    return ans;
  }
  Hash operator*(long long pwr) const {
    Hash ans = *this;
    ans *= pwr;
    return ans;
  }
  Hash operator/(long long pwr) const {
    Hash ans = *this;
    ans /= pwr;
    return ans;
  }
};
long long Hash::mul = 257;
long long Hash::div[hashlen];

int main() {
  return 0;
}
