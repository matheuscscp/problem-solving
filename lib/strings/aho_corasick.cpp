#include <bits/stdc++.h>
using namespace std;

// maximum sum of the lengths of all patterns
#define N int(1e6+5)

// alphabet size
#define A 52

// ascii ---> [0, A)
int cvt(char c) {
  return islower(c) ? c-'a' : c-'A'+26;
}

// aho corasick trie
// node 0 is the root (empty string, the ultimate failure node).
// failure paths are compressed, so nodes[q].adj[a] is always the correct state.
struct trie {
  // node stuff
  int adj[A], id, len, f, out;
  
  // static stuff
  static trie nodes[N];
  static int nxt;
  static void reset() { memset(nodes,0,sizeof nodes); nxt = 1; }
  static void insert(const char* s, int id) {
    int q = 0, len = 0;
    for (; *s; s++) {
      int a = cvt(*s);
      if (!nodes[q].adj[a]) nodes[q].adj[a] = nxt++;  // create node
      q = nodes[q].adj[a];                            // go through the edge
      len++;
    }
    nodes[q].id = id;   // pattern id
    nodes[q].len = len; // pattern length
  }
  static void aho_corasick() {
    queue<int> Q;
    // failure, output and failure compression are always ready for root and
    // its children.
    for (int a = 0; a < A; a++) if (nodes[0].adj[a]) Q.push(nodes[0].adj[a]);
    // bfs
    while (!Q.empty()) {
      int q = Q.front(); Q.pop();
      for (int a = 0; a < A; a++) if (nodes[q].adj[a]) {
        int u = nodes[q].adj[a];
        Q.push(u);
        // find failure link
        int f = nodes[q].f; // start with parent failure
        f = nodes[f].adj[a]; // final failure goes through the edge
        // set links
        nodes[u].f = f;                                   // failure link
        nodes[u].out = (nodes[f].id ? f : nodes[f].out);  // output link
      } else nodes[q].adj[a] = nodes[nodes[q].f].adj[a];  // failure compression
    }
  }
  static void match(const char* s, const function<void(int,int)>& outfunc) {
    int q = 0, len = 0;
    for (; *s; s++) {
      q = nodes[q].adj[cvt(*s)]; // go through the edge
      len++;
      // output
      if (nodes[q].id) outfunc(nodes[q].id,len-nodes[q].len); // current state
      for (int u = nodes[q].out; u; u = nodes[u].out) {       // output links
        outfunc(nodes[u].id,len-nodes[u].len);
      }
    }
  }
};
trie trie::nodes[N];
int trie::nxt;

// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1620
int main() {
  int k;
  scanf("%d",&k);
  while (k--) {
    trie::reset();
    // read text
    static char t[int(1e5+5)];
    scanf("%s",t);
    // read patterns
    int q;
    scanf("%d",&q);
    map<string,int> go; int nxt = 1; // this stuff handles...
    static int id[int(1e3+5)];       // ...repeated patterns
    for (int i = 1; i <= q; i++) {
      static char p[int(1e3+5)];
      scanf("%s",p);
      if (!go.count(p)) { // new pattern
        trie::insert(p,nxt);
        go[p] = nxt++;
      }
      id[i] = go[p];
    }
    // match
    trie::aho_corasick();
    vector<bool> found(q+1,false);
    trie::match(t,[&](int id, int pos) { found[id] = true; });
    // output
    for (int i = 1; i <= q; i++) printf(found[id[i]] ? "y\n" : "n\n");
  }
  return 0;
}
