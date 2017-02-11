#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// http://codeforces.com/group/eqgxxTNwgd/contest/100345/problem/D

// maximum length of a number in the required representation
#define N 19

// number of states
#define S (1<<20)

// amount of available occurrences of digit d in bitmask m
#define get(d,m)  (((m)>>((d)<<1))&3)

// get bitmask obtained by subtracting one occurrence of digit d from bitmask m
#define sub(d,m)  (((m)&~(3<<((d)<<1)))|((get(d,m)-1)<<((d)<<1)))

const int full = 0x0aaaaa; // two occurrences available for each digit

// number of i-length strings satisfying the properties given we're in state j
ll f(int i, int j) {
  // dp base cases
  if (i == 0) return 1;
  // dp framework
  static ll dp[N][S];
  static bool mark[N][S];
  ll& ans = dp[i][j];
  if (mark[i][j]) return ans;
  mark[i][j] = true;
  // dp general case
  ans = 0;
  // for each possible digit to fix in the first position of the string
  for (int d = 0; d <= 9; d++) if (get(d,j)) {
    ans += f(i-1,sub(d,j)); // improve the answer with the remaining dp state
  }
  return ans;
}

// number of non-negative integers no greater than x satisfying the properties
ll g(ll x) {
  if (x == 0) return 0; // 0 is always a corner case
  // get string representation of x and its length
  stringstream ss;
  ss << x;
  string s;
  ss >> s;
  int len = s.size();
  // start answer computation
  ll ans = 0;
  // count the numbers shorter than x.
  for (int l = 1; l < len; l++) { // for each shorter length
    for (int d = 1; d <= 9; d++) { // fix the first digit (0 is not allowed)
      ans += f(l-1,sub(d,full)); // improve the answer with the remaining state
    }
  }
  // count the numbers with the same length as x.
  // to do this, we'll count the numbers with each possible prefix of the string
  // representation of x. for each fixed prefix of length i, we must fix the
  // digit at position i (0-based indexes) with all values strictly smaller than
  // s[i] and improve the answer reflecting these choices in the dp state.
  // after improving the answer with all these choices for position i, we must
  // permanently update the current state to include the digit s[i] (we must
  // extend the prefix). if the extension leads to an invalid state, then there
  // are no more numbers satisfying the properties. if the whole string fits in
  // a valid state, then x itself satisfies the properties.
  for (int i = 0, state = full; i < len; i++) {
    int si = s[i]-'0';
    // for each possible digit to fix at position i
    for (int d = (i==0); d < si; d++) if (get(d,state)) {
      ans += f(len-1-i,sub(d,state)); // improve the answer
    }
    // no more available occurrences for digit s[i] in the current state
    if (get(si,state) == 0) return ans;
    // subtract one occurrence of s[i]
    state = sub(si,state);
  }
  // if we reached this point, then x itself satisfies the properties
  ans++;
  return ans;
}

int main() {
#ifdef ONLINE_JUDGE
  freopen("exchange.in","r",stdin);
  freopen("exchange.out","w",stdout);
#endif
  ll l,r;
  scanf("%lld%lld",&l,&r);
  printf("%lld\n",g(r)-g(l-1));
  return 0;
}
