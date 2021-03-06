#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include <unistd.h>
#endif
using namespace std;

// BEGIN template
#define   ff            first
#define   ss            second
#define   mp            make_pair
#define   mt            make_tuple
#define   pb            push_back
#define   eb            emplace_back
#define   pq            priority_queue
#define   pqmin(X)      priority_queue<X,vector<X>,greater<X>>

#ifdef ONLINE_JUDGE
  #define fastio        std::ios::sync_with_stdio(false)
  #define dbg(X)
  #define _             _
#else
  #define fastio
  #define dbg(X)        cerr << ">>> (" << #X << ") = (" << X << ")\n"
  #define _             << " _ " <<
#endif
#define   sci1(X)       scanf("%d",&(X))
#define   sci2(X,Y)     scanf("%d%d",&(X),&(Y))
#define   sci3(X,Y,Z)   scanf("%d%d%d",&(X),&(Y),&(Z))
#define   scl(X)        scanf("%lld",&(X))
#define   scs(X)        scanf("%s",X)
#define   flush         fflush(stdout)
#define   lg(X)         (63 - __builtin_clzll(X))
#define   LG(X)         (lg(X)+((1<<lg(X)) < (X)))
#define    rp(i,L,R)    for (int i = L, __R = R; i <= __R; i++)
#define   rpd(i,R,L)    for (int i = R, __L = L; __L <= i; i--)

#define GET_SCI(_1,_2,_3,NAME,...) NAME
#define sci(...) GET_SCI(__VA_ARGS__,sci3,sci2,sci1)(__VA_ARGS__)

#define DP1(type,X)\
  static type dp[X];\
  static bool mark[X];\
  auto& ans = dp[i];\
  if (mark[i]) return ans;\
  mark[i] = true;

#define DP2(type,X,Y)\
  static type dp[X][Y];\
  static bool mark[X][Y];\
  auto& ans = dp[i][j];\
  if (mark[i][j]) return ans;\
  mark[i][j] = true;

#define DP3(type,X,Y,Z)\
  static type dp[X][Y][Z];\
  static bool mark[X][Y][Z];\
  auto& ans = dp[i][j][k];\
  if (mark[i][j][k]) return ans;\
  mark[i][j][k] = true;

#define GET_DP(_1,_2,_3,_4,NAME,...) NAME
#define DP(...) GET_DP(__VA_ARGS__,DP3,DP2,DP1)(__VA_ARGS__)

typedef   long long     ll;
typedef   pair<int,int> ii;
typedef   vector<int>   vi;
typedef   vector<bool>  vb;

#define   oo            0x3f3f3f3f3f3f3f3fLL
#define   LGN           25
#define   MOD           int(1e9+7)
#define   N             int(2e5+5)
// END template

// returns parent vector (idom[source] == 0)
vi dominator_tree(const vector<vi>& dag, int source) {
  int n = dag.size();
  // step 1
  vi idom(n);
  rp(u,0,n-1) idom[u] = u;
  // step 2
  vi deg(n,0);
  function<void(int)> dfs1 = [&](int u) {
    for (int v : dag[u]) {
      deg[v]++;
      if (deg[v] == 1) dfs1(v);
    }
  };
  dfs1(source);
  // step 3
    // lca
    vector<vi> dp(n,vi(LG(n)+5,-1));
    function<int(int,int)> f = [&](int u, int i) {
      if (i == 0) return idom[u];
      auto& ans = dp[u][i];
      if (ans >= 0) return ans;
      return ans = f(f(u,i-1),i-1);
    };
    vi l(n,0);
    auto lca = [&](int u, int v) {
      if (l[u] < l[v]) swap(u,v);
      int k = LG(l[u]);
      rpd(i,k,0) if (l[f(u,i)] >= l[v]) u = f(u,i);
      if (u == v) return v;
      rpd(i,k,0) if (f(u,i) != f(v,i)) u = f(u,i), v = f(v,i);
      return idom[u];
    };
  // dfs
  function<void(int)> dfs2 = [&](int u) {
    for (int v : dag[u]) {
      // step 3.1
      idom[v] = (idom[v] == v ? u : lca(idom[v],u));
      l[v] = l[idom[v]]+1;
      // step 3.2
      deg[v]--;
      if (deg[v] == 0) dfs2(v);
    }
  };
  dfs2(source);
  return idom;
}

int main() {
  return 0;
}
