#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include <unistd.h>
#endif
using namespace std;

// BEGIN template
#define   ff            first
#define   ss            second
#define   pb            push_back
#define   eb            emplace_back
#define   em            emplace
#define   pq            priority_queue
#define   pqmin(X)      priority_queue<X,vector<X>,greater<X>>
#define   all(X)        (X).begin(),(X).end()

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
#define   MOD           ll(99990001)
#define   N             int(4e5+5)
// END template

// http://codeforces.com/group/eqgxxTNwgd/contest/100109/problem/K

int n, x[N], y[N]; ll w[N];

int nxedge = 2, nx[N], hd[N], to[N], mark[N], pass = 1; bool off[N];
ll color[N], nxcolor = 1, lazy[N];
int frwd(int i) { return 2*i+2; }
int bkwd(int i) { return 2*i+3; }
int idx(int e) { return (e-2)/2; }

void add_edge(int u, int v) {
  int e = nxedge++;
  nx[e] = hd[u];
  hd[u] = e;
  to[e] = v;
}
void remove_edge(int e) {
  off[e] = true;
}
int edge(int e) {
  if (!e || !off[e]) return e;
  return nx[e] = edge(nx[e]);
}
ll prop(int e) {
  return w[idx(e)] = (w[idx(e)]+lazy[color[to[e]]])%MOD;
}
void paint(int u, int c, ll z) {
  color[u] = c;
  for (int e = edge(hd[u]); e; e = edge(nx[e])) if (color[to[e]] != c) {
    int v = to[e];
    w[idx(e)] = (prop(e)*z)%MOD;
    paint(v,c,z);
  }
}

int main() {
  fastio;
  // input tree
  sci(n);
  rp(i,0,n-2) {
    sci(x[i],y[i]);
    scl(w[i]);
    w[i] %= MOD;
    add_edge(x[i],y[i]);
    add_edge(y[i],x[i]);
  }
  // queries
  rp(j,2,n) {
    // input
    int i;
    sci(i);
    i--;
    // answer
    ll z = prop(frwd(i));
    // output
    printf("%lld\n",z);
    flush;
    // remove edges
    remove_edge(frwd(i));
    remove_edge(bkwd(i));
    // parallel bfs
    pass++;
    int a = x[i], b = y[i];
    queue<int> q[2];
    q[0].push(edge(hd[a])), q[1].push(edge(hd[b]));
    mark[a] = pass, mark[b] = pass;
    int mv[] = {a,b};
    int t = 0;
    while (!q[t].empty()) {
      int e = q[t].front(); q[t].pop();
      if (!e) continue;
      q[t].push(edge(nx[e]));
      if (mark[to[e]] == pass) continue;
      mark[to[e]] = pass;
      q[t].push(edge(hd[to[e]]));
      mv[t] = min(mv[t],to[e]);
      t ^= 1;
    }
    bool ok = true;
    while (ok && !q[!t].empty()) {
      int e = q[!t].front(); q[!t].pop();
      if (!e) continue;
      q[!t].push(edge(nx[e]));
      if (mark[to[e]] == pass) continue;
      ok = false;
    }
    // get smaller component
    if (ok && !t) if (mv[0] > mv[1]) t = 1;
    if (t) swap(a,b);
    // paint and lazy
    paint(a,nxcolor++,z);
    lazy[color[b]] = (lazy[color[b]]+z)%MOD;
  }
  return 0;
}
