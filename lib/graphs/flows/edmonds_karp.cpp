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

// G: flow network
// s: source
// t: sink
ll edmonds_karp(const vector<vector<pair<int,ll>>>& G, int s, int t) {
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
  // residual network
  int n = G.size();
  vector<vector<ii>> Gf(n); // adjacencies
  vector<edge> Ef; // capacities
  rp(u,0,n-1) for (auto& e : G[u]) {
    int v = e.ff;
    ll c = e.ss;
    int idx = Ef.size(); Ef.eb();
    Gf[u].eb(v,idx);
    Gf[v].eb(u,idx);
    Ef[idx].add(u,v,c);
  }
  // augmentation
  vector<ii> parent(n);
  function<ll(int,ll)> augment = [&](int v, ll f) {
    if (v == s) return f;
    int u = parent[v].ff;
    auto& e = Ef[parent[v].ss];
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
  // relaxation
  vi mark(n,0); int pass = 1;
  auto relax = [&](int u, int v, int idx) {
    mark[v] = pass;
    parent[v] = ii(u,idx);
    Qpush(v);
  };
  // BFS loop
  ll maxflow = 0;
  for (ll f = 1; f > 0; pass++) {
    f = 0;
    Qclear();
    relax(s,s,-1);
    while (!Qempty()) {
      int u = Qpop();
      if (u == t) { f = augment(t,oo); break; }
      for (auto& e : Gf[u]) {
        int v = e.ff, idx = e.ss;
        if (mark[v] < pass && Ef[idx].query(u,v) > 0) relax(u,v,idx);
      }
    }
    maxflow += f;
  }
  return maxflow;
}

int main() {
  return 0;
}
