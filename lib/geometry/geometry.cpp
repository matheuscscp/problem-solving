#include <bits/stdc++.h>
using namespace std;

// BEGIN template
#define MAXN      200005
#define MAXLOGN   25
#define MOD       10007
#define oo        0x3f3f3f3f3f3f3f3fL
#define MAX_PRIME 50000
#define EPS       1e-9

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
#define LSOne(X)  ((X)&(-(X)))
#define LESS(X,Y) ((X)+EPS < (Y))
#define LEQ(X,Y)  (!LESS(Y,X))
#define EQLS(X,Y) (fabs((X)-(Y)) < EPS)

enum {WHITE=0,GRAY,BLACK};
enum {UNVISITED=-1};

typedef long long ll;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef complex<double> cplx;

int pass = 1;
const double pi = 2*acos(0);
const double tau = 2.0*pi;
const double pi_2 = pi/2.0;
const double deg2rad = pi/180.0;

struct pt2 {
  double x,y;
  pt2(double x = 0, double y = 0) : x(x), y(y) {}
  double dist(const pt2& o) const { return hypot(x-o.x,y-o.y); }
  double length() const { return hypot(x,y); }
  pt2 rotate(double rad) {
    pt2 ans;
    double c = cos(rad), s = sin(rad);
    ans.x = x*c-y*s;
    ans.y = x*s+y*c;
    return ans;
  }
  void add(const pt2& o) {
    x += o.x;
    y += o.y;
  }
  pt2 operator*(double s) const {
    pt2 ans;
    ans.x = x*s;
    ans.y = y*s;
    return ans;
  }
  pt2 operator+(const pt2& o) const {
    pt2 ans;
    ans.x = x+o.x;
    ans.y = y+o.y;
    return ans;
  }
  pt2 operator-(const pt2& o) const {
    pt2 ans;
    ans.x = x-o.x;
    ans.y = y-o.y;
    return ans;
  }
  pt2 operator-() const {
    pt2 ans;
    ans.x = -x;
    ans.y = -y;
    return ans;
  }
  bool operator==(const pt2& o) const {
    return EQLS(x,o.x) && EQLS(y,o.y);
  }
  bool operator!=(const pt2& o) const {
    return !operator==(o);
  }
  bool operator<(const pt2& o) const {
    if (!EQLS(x,o.x)) return LESS(x,o.x);
    return LESS(y,o.y);
  }
  pt2 unit() const {
    auto len = length();
    return pt2(x/len,y/len);
  }
};
pt2 operator*(double s, const pt2& v) {
  return v*s;
}
ostream& operator<<(ostream& os, const pt2& P) {
  return os << "(" << P.x << ", " << P.y << ")";
}
double D(const pt2& P, const pt2& Q, const pt2& R) {
  /*
        |Px Py 1|
    D = |Qx Qy 1|
        |Rx Ry 1|
  */
  return P.x*Q.y + P.y*R.x + Q.x*R.y - (R.x*Q.y + R.y*P.x + Q.x*P.y);
}
struct pt3 {
  double x,y,z;
  pt3(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
  double dist(const pt3& o = pt3()) const {
    return sqrt((x-o.x)*(x-o.x)+(y-o.y)*(y-o.y)+(z-o.z)*(z-o.z));
  }
  double length() const {
    return sqrt(x*x+y*y+z*z);
  }
};

struct line2 {
  double a,b,c;
  void fix() {
    auto k = !EQLS(a,0) ? a : b;
    a /= k;
    b /= k;
    c /= k;
  }
  line2(double a=0, double b=0, double c=0) : a(a), b(b), c(c) { fix(); }
  line2(const pt2& P, const pt2& Q) {
    a = P.y-Q.y;
    b = Q.x-P.x;
    c = P.x*Q.y-P.y*Q.x;
    fix();
  }
  double x(double y) const {
    return -(b*y+c)/a;
  }
  double y(double x) const {
    return -(a*x+c)/b;
  }
  bool operator==(const line2& o) const {
    return EQLS(a,o.a) && EQLS(b,o.b) && EQLS(c,o.c);
  }
  bool parallel(const line2& o) const {
    return EQLS(a,o.a) && EQLS(b,o.b) && !EQLS(c,o.c);
  }
  double dist(const pt2& p) const {
    return fabs(a*p.x+b*p.y+c)/hypot(a,b);
  }
  pt2 closest(const pt2& p) const {
    auto den = a*a+b*b;
    return pt2((b*(b*p.x - a*p.y) - a*c)/den,(a*(-b*p.x + a*p.y) - b*c)/den);
  }
};
pt2 intersection(const line2& r, const line2& s) {
  auto det = r.a*s.b - r.b*s.a;
  return pt2((-r.c*s.b + s.c*r.b)/det,(-s.c*r.a + r.c*s.a)/det);
}
struct lineseg2 {
  pt2 A,B;
  lineseg2(const pt2& A = pt2(), const pt2& B = pt2()) : A(A), B(B) {}
  bool contains(const pt2& P) const {
    if (LESS(0,line2(A,B).dist(P))) return false;
    if (EQLS(A.x,B.x)) return LEQ(min(A.y,B.y),P.y) && LEQ(P.y,max(A.y,B.y));
    return LEQ(min(A.x,B.x),P.x) && LEQ(P.x,max(A.x,B.x));
  }
  pt2 closest(const pt2& P) const {
    auto Q = line2(A,B).closest(P);
    if (contains(Q)) return Q;
    return LESS(P.dist(A),P.dist(B)) ? A : B;
  }
  bool intersects(const lineseg2& o) const {
    auto d1 = D(A,B,o.A);
    auto d2 = D(A,B,o.B);
    if ((EQLS(d1,0) && contains(o.A)) || (EQLS(d2,0) && contains(o.B)))
      return true;
    auto d3 = D(o.A,o.B,A);
    auto d4 = D(o.A,o.B,B);
    if ((EQLS(d3,0) && o.contains(A)) || (EQLS(d4,0) && o.contains(B)))
      return true;
    return LESS(d1*d2,0) && LESS(d3*d4,0);
  }
};
bool inside(const vector<lineseg2>& ls, const pt2& P) {
  for (auto& l : ls) if (LESS(D(l.A,l.B,P),0)) return false;
  return true;
}

struct circle {
  pt2 C;
  double r;
  circle(const pt2& C_ = pt2(), double r_ = 0) : C(C_), r(r_) {}
  double arc(double rad = tau) const { return rad*r; }
  double sector(double rad = tau) const { return rad*r*r/2; }
  double chord(double rad = pi) const { return 2*r*sin(rad/2); }
  double segment(double rad = pi) const { return r*r*(rad - sin(rad))/2; }
  static bool rad2pt(const pt2& P, const pt2& Q, double r, circle& c) {
    double d2 = (P.x - Q.x) * (P.x - Q.x) + (P.y - Q.y) * (P.y - Q.y);
    double det = r * r / d2 - 0.25;
    if (det < 0.0) return false;
    double h = sqrt(det);
    auto x = (P.x + Q.x) * 0.5 + (P.y - Q.y) * h;
    auto y = (P.y + Q.y) * 0.5 + (Q.x - P.x) * h;
    c = circle(pt2(x, y), r);
    return true;
  }
};

struct triangle {
  // side opposed to vertex
  double a; pt2 A;
  double b; pt2 B;
  double c; pt2 C;
  triangle(double a_ = 0, double b_ = 0, double c_ = 0) : a(a_), b(b_), c(c_) {
    if (!ok()) return;
    /*
      Y
      /\
      |
      |       C
      |  b  ´   \
      |   ´      \ a
      | ´         \
   ---A------------B---------> X
      |     c (largest side)
    */
    double l[3] = {a,b,c};
    sort(l,l+3);
    a = l[0], b = l[1], c = l[2];
    A = pt2(0,0);
    B = pt2(c,0);
    double Cx = (b*b + c*c - a*a)/(2*c);
    C = pt2(Cx,sqrt(b*b - Cx*Cx));
  }
  triangle(const pt2& P, const pt2& Q, const pt2& R) : A(P), B(Q), C(R) {
    if (LESS(D(A,B,C),0)) swap(B,C);
    a = B.dist(C); // opposed to A
    b = C.dist(A); // opposed to B
    c = A.dist(B); // opposed to C
  }
  static bool read_pts(triangle& t) {
    pt2 v[3];
    rp(i,0,2) if (!(cin >> v[i].x >> v[i].y)) return false;
    t = triangle(v[0],v[1],v[2]);
    return true;
  }
  bool ok() const {
    return LESS(a,b+c) && LESS(b,a+c) && LESS(c,a+b);
  }
  int pythagoras() const {
    double l[3] = {a,b,c};
    sort(l,l+3);
    auto cmp = l[2]*l[2] - (l[0]*l[0]+l[1]*l[1]);
    return LESS(cmp,0) ? -1 : (EQLS(0,cmp) ? 0 : 1);
  }
  bool acute() const {
    return pythagoras() <  0;
  }
  bool right() const {
    return pythagoras() == 0;
  }
  bool obtuse() const {
    return pythagoras() >  0;
  }
  bool equilateral() const {
    return EQLS(a,b) && EQLS(b,c);
  }
  bool isosceles() const {
    return EQLS(a,b) || EQLS(b,c) || EQLS(a,c);
  }
  bool strict_isosceles() const {
    return isosceles() && !equilateral();
  }
  bool scalene() const {
    return !isosceles();
  }
  double perimeter() const {
    return a+b+c;
  }
  double semiperimeter() const {
    return perimeter()/2;
  }
  double area() const { // heron's formula: area = sqrt(s(s-a)(s-b)(s-c))
    auto s = semiperimeter();
    return sqrt(s)*sqrt(s-a)*sqrt(s-b)*sqrt(s-c);
  }
  double angleA() const { // law of cosines: a² = b² + c² - 2bc cos(angleA)
    return acos( ( a*a - b*b - c*c ) / (-2*b*c) );
  }
  double angleB() const { // law of cosines: b² = a² + c² - 2ac cos(angleB)
    return acos( ( b*b - a*a - c*c ) / (-2*a*c) );
  }
  double angleC() const { // law of cosines: c² = a² + b² - 2ab cos(angleC)
    return acos( ( c*c - a*a - b*b ) / (-2*a*b) );
  }
  bool contains(const pt2& P) const {
    return LEQ(0,D(A,B,P)) && LEQ(0,D(B,C,P)) && LEQ(0,D(C,A,P));
  }
  // 1) intersection of medians (vertices to midpoints of opposite sides)
  // 2) always inside
  // 3) distances to midpoints equals 1/3 of medians lengths
  pt2 barycenter() const { // or centroid, or center of mass
    return pt2((A.x+B.x+C.x)/3,(A.y+B.y+C.y)/3);
  }
  // 1) intersection of altitudes
  // 2) inside only if acute (if right, is the vertex with the right angle)
  pt2 orthocenter() const {
    double tA = tan(angleA()), tB = tan(angleB()), tC = tan(angleC());
    double t = tA+tB+tC;
    return pt2((A.x*tA+B.x*tB+C.x*tC)/t,(A.y*tA+B.y*tB+C.y*tC)/t);
  }
  // 1) intersection of angle bisectors
  // 2) always inside
  circle incircle() const {
    auto p = perimeter();
    return circle(pt2((a*A.x+b*B.x+c*C.x)/p,(a*A.y+b*B.y+c*C.y)/p),2*area()/p);
  }
  // 1) intersection of perpendicular bisectors
  // 2) inside only if acute (if right, coincides with hypotenuse midpoint)
  // 3) same distance from all vertices
  // 4) smallest circle containing non-obtuse triangles (largest side gives
  // diameter for obtuses)
  circle circumcircle() const {
    auto d2 = 2*D(A,B,C);
    auto A2 = A.length(); A2 *= A2;
    auto B2 = B.length(); B2 *= B2;
    auto C2 = C.length(); C2 *= C2;
    double Sx = D(pt2(A2,A.y),pt2(B2,B.y),pt2(C2,C.y));
    double Sy = D(pt2(A.x,A2),pt2(B.x,B2),pt2(C.x,C2));
    return circle(pt2(Sx/d2,Sy/d2),a*b*c/(4*area()));
  }
  // 1) aligns barycenter, orthocenter, circumcenter and, if isosceles, incenter
  // 2) equilateral triangles don't have an euler line
  line2 euler() const {
    return line2(barycenter(),orthocenter());
  }
};

struct rectangle {
  pt2 bl, tr;
  rectangle(const pt2& P = pt2(), const pt2& Q = pt2(), bool fix = true) :
  bl(min(P.x,Q.x),min(P.y,Q.y)),
  tr(max(P.x,Q.x),max(P.y,Q.y)) {
    if (!fix) bl = P, tr = Q;
  }
  bool ok() const { return bl.x < tr.x && bl.y < tr.y; }
  rectangle intersection(const rectangle& o) const {
    if (!ok()) return *this;
    if (!o.ok()) return o;
    auto lx = max(bl.x,o.bl.x), rx = min(tr.x,o.tr.x);
    auto by = max(bl.y,o.bl.y), ty = min(tr.y,o.tr.y);
    return rectangle(pt2(lx,by),pt2(rx,ty),false);
  }
};
// END template

int main() {
  return 0;
}
