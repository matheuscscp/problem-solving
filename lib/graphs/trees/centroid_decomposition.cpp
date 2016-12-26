#include <bits/stdc++.h>
using namespace std;

#define   MAXLOGN 25
#define   MAXN    int(1e5+5)

// tree adjacency lists
vector<int> T[MAXN];

// centroid tree adjacency lists
vector<int> C[MAXN];

// centroid tree parents (pnt[root] == 0)
int pnt[MAXN];

// centroid tree levels (lvl[root] == 0)
int lvl[MAXN];

// call centroid(arbitrary root). returns the root of the centroid tree
int centroid(int u = 1, int p = 0, int lv = 0) {
  static int tot[MAXN], maxc[MAXN];
  static bool vis[MAXN];
  // dfs
  tot[u] = 1;
  maxc[u] = -1;
  for (int v : T[u]) if (!vis[v] && v != p) {
    centroid(v,u);
    tot[u] += tot[v];
    if (maxc[u] < 0 || tot[v] > tot[maxc[u]]) maxc[u] = v;
  }
  if (p) return 0;
  // find centroid, remove it and build new level
  int r = u, half = tot[u]>>1;
  while (half && tot[maxc[r]] > half) r = maxc[r];
  vis[r] = true;
  lvl[r] = lv;
  for (int v : T[r]) if (!vis[v]) {
    int c = centroid(v,0,lv+1);
    C[r].push_back(c);
    pnt[c] = r;
  }
  return r;
}

// call dfs(centroid tree root). fills dist[u][level]
int dist[MAXN][MAXLOGN];
void dfs(int r, int u = 0, int p = 0, int d = 0) {
  static bool vis[MAXN];
  // dfs
  if (!u) u = r;
  dist[u][lvl[r]] = d;
  for (int v : T[u]) if (!vis[v] && v != p) dfs(r,v,u,d+1/*w(u,v)*/);
  if (p) return;
  // remove centroid and dfs next level
  vis[r] = true;
  for (int v : C[r]) dfs(v);
}

int main() {
  return 0;
}
