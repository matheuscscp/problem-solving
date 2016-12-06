#include <bits/stdc++.h>
using namespace std;

// BEGIN template
#define ff first
#define ss second
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define eb emplace_back

#define FASTIO  std::ios::sync_with_stdio(false)
#define dbg(X)  cout << ">>> (" << #X << ") = (" << X << ")\n"
#define _       << " _ " <<
#define  rp(ITER,BEG,END) for (int ITER = BEG, ENDD = END; ITER <= ENDD; ITER++)
#define rpd(ITER,BEG,END) for (int ITER = BEG, ENDD = END; ITER >= ENDD; ITER--)
#define DEG2RAD(X)  (pi*(X)/180.0)

enum {WHITE=0,GRAY,BLACK};
enum {UNVISITED=-1};

typedef long long ll;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef complex<double> cplx;

const double pi = 2*acos(0);
const double tau = 2.0*pi;

#define oo        0x3f3f3f3f3f3f3f3fLL
#define MAXLOGN   25
#define MAX_PRIME 50000
#define MOD       1000000007
#define MAXN      200005
// END template

// G must be a simple digraph with non-negative capacities
ll edmonds_karp(const vector<vector<pair<int,ll>>>& G_, int s, int t) {
  struct edge {
    ll fw,bw;
    edge() : fw(0), bw(0) {}
    void add(int u, int v, ll d) {
      if (u < v) fw += d;
      else bw += d;
    }
    ll query(int u, int v) const {
      return u < v ? fw : bw;
    }
  };
  // init residues
  int n = G_.size();
  vector<map<int,int>> G(n);
  vector<edge> E;
  rp(u,0,n-1) for (auto& e : G_[u]) {
    int v = e.ff;
    ll c = e.ss;
    int idx;
    if (G[u].count(v)) idx = G[u][v];
    else {
      idx = E.size(); E.eb();
      G[u][v] = idx;
      G[v][u] = idx;
    }
    E[idx].add(u,v,c);
  }
  // augmentation
  vector<ii> parent(n);
  function<ll(int,ll)> augment = [&](int v, ll f) {
    if (v == s) return f;
    int u = parent[v].ff;
    auto& e = E[parent[v].ss];
    f = augment(u,min(f,e.query(u,v)));
    e.add(u,v,-f);
    e.add(v,u, f);
    return f;
  };
  // queue
  vi kew(n); int kewl = 0, kewr = 0;
  auto Qpush = [&](int x) {
    kew[kewr++] = x;
  };
  auto Qpop = [&]() {
    return kew[kewl++];
  };
  auto Qclear = [&]() {
    kewl = 0;
    kewr = 0;
  };
  auto Qempty = [&]() {
    return kewl == kewr;
  };
  // BFS loop
  ll maxflow = 0;
  for (ll f = 1; f;) {
    f = 0;
    memset(&parent[0],-1,n*sizeof(ii));
    Qclear();
    parent[s] = ii(s,-1);
    Qpush(s);
    while (!Qempty()) {
      int u = Qpop();
      if (u == t) { f = augment(t,oo); break; }
      for (auto& e_ : G[u]) {
        int v = e_.ff, idx = e_.ss;
        if (parent[v].ff >= 0 || E[idx].query(u,v) == 0) continue;
        parent[v] = ii(u,idx);
        Qpush(v);
      }
    }
    maxflow += f;
  }
  return maxflow;
}

int main() {
  return 0;
}
