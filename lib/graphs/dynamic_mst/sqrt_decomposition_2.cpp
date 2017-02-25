#include <bits/stdc++.h>
using namespace std;

// problem: http://codeforces.com/gym/101246/problem/L
// tutorial: http://codeforces.com/blog/entry/50554

const int N = 4e4+5;

// input
int n,m,u[N],v[N],w[N],e[N],c[N];

// set comparison
struct cmp {bool operator()(int i, int j) { return w[i]!=w[j]?w[i]<w[j]:i<j; }};
typedef set<int,cmp> edgeset;

// lazy flag
struct {
  int mark[N],pass;
  void init() { pass++; }
  bool get(int i) { return mark[i] == pass; }
  void set(int i) { mark[i] = pass; }
} flag;

// lazy dsu
struct dsu {
  int mark[N],pass,p[N];
  void init() { pass++; }
  int Find(int x) { prop(x); return p[x]==x?x:p[x]=Find(p[x]); }
  bool Union(int x, int y) {
    x = Find(x), y = Find(y);
    if (x == y) return false;
    p[x] = y;
    return true;
  }
  void prop(int x) {
    if (mark[x] == pass) return;
    mark[x] = pass;
    p[x] = x;
  }
} d1, d2;

int main() {
#ifdef ONLINE_JUDGE
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
#endif
  // input
  scanf("%d%d",&n,&m);
  edgeset large;
  for (int i = 1; i <= m; i++) {
    scanf("%d%d%d",u+i,v+i,w+i);
    large.insert(i);
  }
  int t;
  scanf("%d",&t);
  for(int i = 1; i <= t; i++) scanf("%d%d",e+i,c+i);
  // for each block of sqrt(t) updates
  for (int l = 1, b = sqrt(t); l <= t; l += b) {
    int r = min(l+b-1,t);
    // mark updated edges, initialize first dsu and initialize small set
    flag.init();
    d1.init();
    edgeset sml;
    for (int i = l; i <= r; i++) {
      flag.set(e[i]), d1.Union(u[e[i]],v[e[i]]), sml.insert(e[i]);
    }
    // select O(n) possibly useful from non-updated edges
    static int idx[N]; int cnt = 0;
    d2.init();
    for (int i : large) if (!flag.get(i) && d2.Union(u[i],v[i])) idx[++cnt] = i;
    // select certainly useful from non-updated edges and fill small set
    d2.init();
    int forest = 0;
    for (int i = 1; i <= cnt; i++) {
      if (d1.Union(u[idx[i]],v[idx[i]])) { // certainly useful, O(n) edges
        d2.Union(u[idx[i]],v[idx[i]]);
        forest += w[idx[i]];
      }
      else sml.insert(idx[i]); // possibly useful, O(sqrt(t)) edges
    }
    // answer queries
    for (int i = l; i <= r; i++) {
      // update sets
      large.erase(e[i]);
      sml.erase(e[i]);
      w[e[i]] = c[i];
      large.insert(e[i]);
      sml.insert(e[i]);
      // kruskal
      d1.init();
      int mst = 0;
      for (int i : sml) if (d1.Union(d2.Find(u[i]),d2.Find(v[i]))) mst += w[i];
      printf("%d\n",forest+mst);
    }
  }
  return 0;
}
