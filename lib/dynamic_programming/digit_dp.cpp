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
#define   MOD           int(1e9+9)
#define   N             int(1e3+5)
// END template

// http://codeforces.com/group/eqgxxTNwgd/contest/100345/problem/D

#define   get(d,m)      (((m)>>((d)<<1))&3)
#define   sub(d,m)      (((m)&~(3<<((d)<<1)))|((get(d,m)-1)<<((d)<<1)))

const int full = 0x0aaaaa;

// number of i-length strings in j state satisfying the properties
ll f(int i, int j) {
  if (i == 0) return 1;
  DP(ll,19,1<<20);
  rp(d,0,9) if (get(d,j)) ans += f(i-1,sub(d,j));
  return ans;
}

ll g(ll x) {
  if (x == 0) return 0;
  // get string and length
  stringstream ss;
  ss << x;
  string s;
  ss >> s;
  int len = s.size();
  // start answer computation
  ll ans = 0;
  // shorter than x
  rp(l,1,len-1) rp(d,1,9) ans += f(l-1,sub(d,full));
  // same length as x
    // first digit
    rp(d,'1',s[0]-1) ans += f(len-1,sub(d-'0',full));
    int state = sub(s[0]-'0',full);
    // other digits
    bool nomore = false;
    rp(i,1,len-1) {
      rp(d,'0',s[i]-1) if (get(d-'0',state)) ans += f(len-1-i,sub(d-'0',state));
      if (!get(s[i]-'0',state)) {
        nomore = true;
        break;
      }
      state = sub(s[i]-'0',state);
    }
    // number itself
    if (!nomore) ans++;
  return ans;
}

int main() {
#ifdef ONLINE_JUDGE
  freopen("exchange.in","r",stdin);
  freopen("exchange.out","w",stdout);
#endif
  fastio;
  ll l,r;
  scl(l), scl(r);
  printf("%lld\n",g(r)-g(l-1));
  return 0;
}
