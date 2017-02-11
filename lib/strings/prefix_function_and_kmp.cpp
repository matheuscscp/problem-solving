#include <bits/stdc++.h>
using namespace std;

vector<int> prefix_function(const string& s) {
  int n = s.size();
  vector<int> p(n+1,0);
  for (int q = 1; q < n; q++) {
    int u = q+1;
    p[u] = p[q]; // start with parent failure
    while (p[u] && s[p[u]] != s[q]) p[u] = p[p[u]]; // go through failure links
    if (s[p[u]] == s[q]) p[u]++; // final failure goes through the edge
  }
  return p;
}

void kmp(const string& p, const string& t, const function<void(int)>& outfunc) {
  int n = p.size();
  auto pf = prefix_function(p);
  int q = 0, len = 0;
  for (const char* s = t.c_str(); *s; s++) {
    while (q && p[q] != *s) q = pf[q]; // go through failure links
    if (p[q] == *s) q++; // final failure goes through the edge
    len++;
    if (q == n) outfunc(len-n);
  }
}

int main() {
  string t,p;
  cin >> t >> p;
  kmp(p,t,[](int pos) {
    printf("occurrence at %d\n",pos);
  });
  return 0;
}
