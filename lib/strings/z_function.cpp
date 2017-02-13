#include <bits/stdc++.h>
using namespace std;

vector<int> z_function(const string& s) {
  int n = s.size();
  vector<int> z(n,0);
  // invariant: [l, r] is the rightmost scanned segment s.t. s[l..r] = s[0..r-l]
  for (int i = 1, l = 0, r = -1; i < n; i++) {
    // use previously calculated values of z to improve the running time to O(n)
    if (i <= r) z[i] = min(z[i-l],r-i+1);
    // trivial algorithm
    while (i+z[i] < n && s[z[i]] == s[i+z[i]]) z[i]++;
    // invariant maintenance
    if (i+z[i]-1 > r) l = i, r = i+z[i]-1;
  }
  return z;
}

int main() {
  string t,p;
  cin >> t >> p;
  auto z = z_function(p+"$"+t);
  int n = p.size(), k = z.size();
  for (int i = n+1; i < k; i++) {
    if (z[i] == n) printf("occurrence at %d\n",i-(n+1));
  }
  return 0;
}
