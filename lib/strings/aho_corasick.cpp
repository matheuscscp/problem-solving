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
#define   MOD           int(1e6+3)
#define   N             int(1e6+5)
// END template

#define   A             52
#define   M             int(1e3+5)

int trie[N][A], nxt;
int f[N];
bitset<M> words[N];

int cvt(char c) {
  if (islower(c)) return c-'a';
  return c+26-'A';
}

int insert(const char* s, int id) {
  int q = 0;
  for (; *s; s++) {
    int i = cvt(*s);
    if (!trie[q][i]) trie[q][i] = nxt++;
    q = trie[q][i];
  }
  words[q][id] = 1;
  return q;
}

void aho_corasick() {
  queue<int> Q;
  rp(i,0,A-1) if (trie[0][i]) Q.push(trie[0][i]);
  while (!Q.empty()) {
    int q = Q.front(); Q.pop();
    rp(i,0,A-1) if (trie[q][i]) {
      int u = trie[q][i];
      Q.push(u);
      f[u] = f[q];
      while (f[u] && !trie[f[u]][i]) f[u] = f[f[u]];
      f[u] = trie[f[u]][i];
      words[u] |= words[f[u]];
    } else trie[q][i] = trie[f[q]][i];
  }
}

int main() {
  fastio;
  int k;
  sci(k);
  rp(t,1,k) {
    memset(trie,0,sizeof trie); nxt = 1;
    memset(f,0,sizeof f);
    memset(words,0,sizeof words);
    static char S[int(1e5+5)];
    scs(S);
    int n;
    sci(n);
    rp(i,1,n) {
      static char b[M];
      scs(b);
      insert(b,i);
    }
    aho_corasick();
    bitset<M> ans;
    const char* s = S;
    for (int q = 0; *s; s++) {
      q = trie[q][cvt(*s)];
      ans |= words[q];
    }
    rp(i,1,n) printf(ans[i] ? "y\n" : "n\n");
  }
  return 0;
}
