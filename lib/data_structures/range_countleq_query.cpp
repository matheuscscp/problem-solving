#include <bits/stdc++.h>
using namespace std;

// BIT to find number of elements <= x in range [l, r] supporting updates.
// all elements a[i] must be such that 1 <= a[i] <= N (but you can always
// compress the input numbers, if necessary!)

// maximum number of different elements
const int N = 2e5+5;

// block size
const int M = 2e3;

// input array
int a[N];

struct bit {
  int ft[N+5];
  void add(int i, int x) {
    for (; i <= N; i += i&-i) ft[i] += x;
  }
  int query(int i) {
    int ans = 0; for (; i > 0; i -= i&-i) ans += ft[i]; return ans;
  }
} block[(N+M-1)/M+5];

int getblock(int i) { return (i-1)/M+1; }
int blockright(int b) { return b*M; }
int blockleft(int b) { return blockright(b-1)+1; }

void update(int i, int x) {
  int b = getblock(i);
  block[b].add(a[i],-1);
  a[i] = x;
  block[b].add(a[i],1);
}

int query(int l, int r, int x) {
  if (r < l) return 0;
  int L = getblock(l), R = getblock(r), ans = 0;
  if (L == R) {
    for (int i = l; i <= r; i++) ans += (a[i] <= x);
    return ans;
  }
  for (int i = l; i <= blockright(L); i++) ans += (a[i] <= x);
  for (int b = L+1; b <= R-1; b++) ans += block[b].query(x);
  for (int i = blockleft(R); i <= r; i++) ans += (a[i] <= x);
  return ans;
}

int main() {
  return 0;
}
