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
#define   MOD           int(1e9+7)
#define   N             int(2e5+5)
// END template

// tree implementation
int to[N/*ed*/]/*vx*/, nxtedge = 1/*ed*/;
int head[N/*vx*/]/*ed*/, nxt[N/*ed*/]/*ed*/;
bool off[N/*ed*/];
map<ii,int> idx/*ed*/;
int color[N/*vx*/], nxtcolor = 1, cnt[N/*cl*/];
void add(int u, int v) {
  int e = nxtedge++;
  to[e] = v;
  nxt[e] = head[u];
  head[u] = e;
  idx[ii(u,v)] = e;
}
void remove(int u, int v) {
  off[idx[ii(u,v)]] = true;
}
int edge(int e) { // meta-path compression
  if (!e || !off[e]) return e;
  return nxt[e] = edge(nxt[e]);
}
void paint(int u, int c, int p = 0) {
  color[u] = c, cnt[c]++;
  for (int e = edge(head[u]); e; e = edge(nxt[e])) if (to[e] != p) {
    paint(to[e],c,u);
  }
}
bool connected(int u, int v) { return color[u] == color[v]; }

// http://codeforces.com/group/eqgxxTNwgd/contest/100960/problem/H
int main() {
  fastio;
  int n;
  sci(n);
  rp(u,1,n) paint(u,nxtcolor++);
  char cmd[10];
  while (true) {
    scs(cmd);
    if (cmd[0] == 'E') return 0;
    int a,b;
    sci(a,b);
    switch (cmd[0]) {
      case 'C': {
        if (cnt[color[a]] > cnt[color[b]]) swap(a,b);
        paint(a,color[b]);
        add(a,b);
        add(b,a);
        break;
      }
      case 'D': {
        remove(a,b);
        remove(b,a);
        queue<ii> q[2];
        q[0].push(ii(a,0)), q[1].push(ii(b,0));
        int e[2] = {edge(head[a]),edge(head[b])};
        int i = 0;
        while (!q[i].empty()) {
          if (!e[i]) {
            q[i].pop();
            if (!q[i].empty()) e[i] = edge(head[q[i].front().ff]);
            continue;
          }
          if (to[e[i]] == q[i].front().ss) {
            e[i] = edge(nxt[e[i]]);
            continue;
          }
          q[i].push(ii(to[e[i]],q[i].front().ff));
          e[i] = edge(nxt[e[i]]);
          i ^= 1;
        }
        if (i == 1) swap(a,b);
        paint(a,nxtcolor++);
        break;
      }
      case 'T':
        printf(connected(a,b) ? "YES\n" : "NO\n");
        flush;
        break;
    }
  }
  return 0;
}
