#include <bits/stdc++.h>
using namespace std;

// =============================================================================
// BEGIN template
// =============================================================================
#ifdef ONLINE_JUDGE
  #define fastio            std::ios::sync_with_stdio(false)
  #define dbg(X)
  #define _                 _
#else
  #include <unistd.h>
  #define fastio
  #define dbg(X)            cerr << ">>> (" << #X << ") = (" << X << ")\n"
  #define _                 << " _ " <<
#endif
#define   ff                first
#define   ss                second
#define   pb                push_back
#define   eb                emplace_back
#define   em                emplace
#define   pq                priority_queue
#define   M                 ((L+R)>>1)
#define   pqmin(X)          priority_queue<X,vector<X>,greater<X>>
#define   all(X)            (X).begin(),(X).end()
#define   sci1(X)           scanf("%d",&(X))
#define   sci2(X,Y)         scanf("%d%d",&(X),&(Y))
#define   sci3(X,Y,Z)       scanf("%d%d%d",&(X),&(Y),&(Z))
#define   scl(X)            scanf("%lld",&(X))
#define   scs(X)            scanf("%s",X)
#define   flush             fflush(stdout)
#define   pc(X)             __builtin_popcountll(X)
#define   lg(X)             (63 - __builtin_clzll(X))
#define   LG(X)             (lg(X)+((1<<lg(X)) < (X)))
#define   rp(i,FIRST,LAST)  for (ll i = (FIRST), _L = (LAST), _inc = ((FIRST) > (LAST) ? -1 : 1); i != _L + _inc; i += _inc)

// functions
void reopen(const string& name) {
#ifdef ONLINE_JUDGE
  char fn[256];
  sprintf(fn,"%s.in",name.c_str());
  freopen(fn,"r",stdin);
  sprintf(fn,"%s.out",name.c_str());
  freopen(fn,"w",stdout);
#endif
}

// dps
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

// overloads
#define GET_SCI(_1,_2,_3,NAME,...) NAME
#define sci(...) GET_SCI(__VA_ARGS__,sci3,sci2,sci1)(__VA_ARGS__)
#define GET_DP(_1,_2,_3,_4,NAME,...) NAME
#define DP(...) GET_DP(__VA_ARGS__,DP3,DP2,DP1)(__VA_ARGS__)

// types
typedef   long long     ll;
typedef   pair<int,int> ii;
typedef   vector<int>   vi;
typedef   vector<bool>  vb;
typedef   set<int>      si;

// constants
const ll  oo =          0x3f3f3f3f3f3f3f3fll;
const int LGN =         25;
const int MOD =         1e9+7;
const int N =           3e5+5;
const int NLGN =        N*LGN;
// =============================================================================
// END template
// =============================================================================

ll ft[N];
void add(int i, ll x) {
  for (; i <= N-5; i += i&(-i)) ft[i] += x;
}
void add(int l, int r, ll x) {
  add(l,x), add(r+1,-x);
}
ll pointQuery(int i) {
  ll ans = 0; for (; i; i -= i&(-i)) ans += ft[i]; return ans;
}

int m,cur=0,lef[N],rig[N],a[N];
void go(int x) {
  while (cur < x) {
    cur++;
    if (lef[cur] > rig[cur]) add(lef[cur],m,a[cur]), add(1,rig[cur],a[cur]);
    else add(lef[cur],rig[cur],a[cur]);
  }
  while (cur > x) {
    if (lef[cur] > rig[cur]) add(lef[cur],m,-a[cur]), add(1,rig[cur],-a[cur]);
    else add(lef[cur],rig[cur],-a[cur]);
    cur--;
  }
}

vi sectors[N];
int desired[N],guys[N],ans[N];
void solve(int l, int r, int L, int R) {
  if (r < l || R < L) return;
  go(M);
  int m;
  {
    int nxt = l;
    vi lf,rg;
    rp(i,l,r) {
      int guy = guys[i];
      ll sum = 0; for (int sec : sectors[guy]) {
        sum += pointQuery(sec);
        if (sum > desired[guy]) break;
      }
      if (sum >= desired[guy]) {
        lf.pb(guy);
        ans[guy] = M;
      } else {
        rg.pb(guy);
      }
    }
    for (int x : lf) guys[nxt++] = x;
    m = nxt-1;
    for (int x : rg) guys[nxt++] = x;
  }
  if (L == R) return;
  solve(l,m,L,M), solve(m+1,r,M+1,R);
}

int main() {
  // http://www.spoj.com/problems/METEORS/
  fastio;
  int n;
  sci(n,m);
  rp(i,1,m) {
    int o;
    sci(o);
    sectors[o].pb(i);
  }
  rp(i,1,n) {
    sci(desired[i]);
    guys[i] = i;
  }
  int k;
  sci(k);
  rp(i,1,k) sci(lef[i],rig[i],a[i]);
  solve(1,n,1,k);
  rp(i,1,n) {
    if (!ans[i]) printf("NIE\n");
    else printf("%d\n",ans[i]);
  }
  return 0;
}




























// prevent atom from erasing the empty lines in the end of the file
