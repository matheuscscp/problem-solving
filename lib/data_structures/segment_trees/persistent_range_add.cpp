
#define M ((L+R)>>1)

typedef long long ll;

const int N =     1e5+5;
const int LGN =   25;
const int NLGN =  N*LGN;

int root[N],lef[4*NLGN],rig[4*NLGN],nodes=0;
ll st[4*NLGN],lz[4*NLGN];

int newNode(ll v, int pl = 0, int pr = 0, ll lzp = 0) {
  int p = ++nodes;
  st[p] = v, lef[p] = pl, rig[p] = pr, lz[p] = lzp;
  return p;
}

int newLazy(int p, int L, int R, ll v) {
  return newNode(st[p]+v*(R-L+1),lef[p],rig[p],lz[p]+v);
}
void prop(int p, int L, int R) {
  if (!lz[p] || L == R) return;
  lef[p] = newLazy(lef[p],L,M,lz[p]), rig[p] = newLazy(rig[p],M+1,R,lz[p]);
  lz[p] = 0;
}

ll rsq(int l, int r, int p, int L, int R) {
  if (r < L || R < l) return 0;
  prop(p,L,R);
  if (L == R) return st[p];
  return rsq(l,r,lef[p],L,M)+rsq(l,r,rig[p],M+1,R);
}

int add(int l, int r, ll v, int p, int L, int R) {
  if (r < L || R < l) return p;
  prop(p,L,R);
  if (l <= L && R <= r) return newLazy(p,L,R,v);
  int pl = add(l,r,v,lef[p],L,M), pr = add(l,r,v,rig[p],M+1,R);
  return newNode(st[pl]+st[pr], pl, pr);
}
