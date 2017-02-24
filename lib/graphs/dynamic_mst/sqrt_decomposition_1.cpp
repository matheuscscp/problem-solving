#include <bits/stdc++.h>
using namespace std;

// problem: http://codeforces.com/gym/101047/problem/I
// tutorial: http://codeforces.com/blog/entry/50554

const int N = 3e4+5;

struct edge {
  int u,v,w,id;
  edge() : id(0) {}
  bool operator<(const edge& o) const { return w < o.w; }
  void read() { scanf("%d%d%d",&u,&v,&w); }
};

// lazy dsu
struct dsu {
  int mark[N], p[N], pass;
  dsu() : pass(1) {}
  void reset() { pass++; }
  int Find(int x) {
    if (mark[x] != pass) {
      mark[x] = pass;
      p[x] = x;
    }
    return p[x] == x ? x : p[x] = Find(p[x]);
  }
  void Union(int x, int y) { p[Find(x)] = Find(y); }
};

int kruskal(const multiset<edge>& edges, vector<edge>* mst = nullptr) {
  static dsu uf;
  uf.reset();
  int ans = 0;
  for (auto& e : edges) if (uf.Find(e.u) != uf.Find(e.v)) {
    uf.Union(e.u,e.v);
    if (mst) mst->push_back(e);
    ans += e.w;
  }
  return ans;
}

int main() {
  int t;
  scanf("%d",&t);
  while (t--) {
    // input
    int n,m,q;
    scanf("%d%d%d",&n,&m,&q);
    multiset<edge> edges;
    for (int i = 1; i <= m; i++) {
      edge e;
      e.read();
      edges.insert(e);
    }
    static edge query[N];
    for (int i = 1; i <= q; i++) {
      query[i].read();
      query[i].id = i;
    }
    // initial large mst
    vector<edge> largemst;
    kruskal(edges,&largemst);
    // answer each block
    for (int l = 1, b = sqrt(q)+1; l <= q; l += b) {
      int r = min(l+b-1,q);
      // current large mst is the initial mst for the queries of this block
      vector<edge> initial;
      largemst.swap(initial);
      // compute next large mst
      for (int i = l; i <= r; i++) edges.insert(query[i]);
      kruskal(edges,&largemst);
      // compute forest
      static dsu uf;
      uf.reset();
      int forest = 0;
      for (auto& e : largemst) if (e.id < l) {
        uf.Union(e.u,e.v);
        forest += e.w;
      }
      // compute initial compressed mst
      multiset<edge> eds;
      for (auto& e : initial) if (uf.Find(e.u) != uf.Find(e.v)) {
        auto tmp = e;
        tmp.u = uf.Find(e.u), tmp.v = uf.Find(e.v);
        eds.insert(tmp);
      }
      // answer each query
      for (int i = l; i <= r; i++) {
        auto tmp = query[i];
        tmp.u = uf.Find(tmp.u), tmp.v = uf.Find(tmp.v);
        eds.insert(tmp);
        printf("%d\n",forest+kruskal(eds));
      }
    }
  }
  return 0;
}
