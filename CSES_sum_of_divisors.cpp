
#include<bits/stdc++.h>
using namespace std;

#include "ext/pb_ds/assoc_container.hpp"
#include "ext/pb_ds/tree_policy.hpp"
using namespace __gnu_pbds;
template<class T> 
using ordered_set = tree<T, null_type,less<T>, rb_tree_tag,tree_order_statistics_node_update> ;
template<class key, class value, class cmp = std::less<key>>
using ordered_map = tree<key, value, cmp, rb_tree_tag, tree_order_statistics_node_update>;

template<class T> ostream& operator<<(ostream &os, set<T> S){os << "{ ";for(auto s:S) os<<s<<" ";return os<<"}";}
template<class T> ostream& operator<<(ostream &os, unordered_set<T> S){os << "{ ";for(auto s:S) os<<s<<" ";return os<<"}";}
template<class T> ostream& operator << (ostream& os, multiset<T> S){os << "{ ";for(auto s:S) os<<s<<" ";return os<<"}";}
template<class T> ostream& operator<<(ostream &os, ordered_set<T> S){os << "{ ";for(auto s:S) os<<s<<" ";return os<<"}";}
template<class L, class R> ostream& operator<<(ostream &os, pair<L,R> P) {return os << "(" << P.first << "," << P.second << ")";}
template<class L, class R> ostream& operator<<(ostream &os, map<L,R> M) {os << "{ ";for(auto m:M) os<<"("<<m.first<<":"<<m.second<<") ";return os<<"}";}
template<class T> ostream& operator<<(ostream &os,vector<T> V){os<<"[ ";for(auto v:V)os<<v<<" ";return os<<"]";}

//read
template<class T> istream& operator>>(istream &is,vector<T> &V){for(auto &x : V) is >> x;return is;}
template<class T> istream& operator>>(istream &is,vector<vector<T>> &V){for(auto &x : V) is >> x;return is;}

//output 
void print(){cout << endl;}template <typename T, typename... Types> void print(T var1, Types... var2){cout << var1 << " ";  print(var2...);}
//input 
void read(){}template <typename T, typename... Types> void read(T& var1, Types&... var2){cin >> var1; read(var2...);}

#ifdef LOCAL
#define trace(...) __f(#__VA_ARGS__,__VA_ARGS__)
template<typename Arg1>
void __f(const char* name,Arg1&& arg1){cout<<name<<" : "<<arg1<<endl;}
template<typename Arg1,typename... Args>
void __f(const char* names,Arg1&& arg1,Args&&... args){const char* comma=strchr(names+1,',');cout.write(names,comma-names)<<" : "<<arg1<<" | ";__f(comma+1,args...);}
#else
#define trace(...) 1
#endif


//defines and typedefs
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
#define TC int testcase; cin >> testcase;while(testcase--)
#define forn(i,n)  for(int i=0;i<n;i++)
#define rep(i,a,b) for(int i = a;i<=b;i++)

// #define LL long long int
#define ALL(x)    x.begin(),x.end()
#define int       long long int
#define PB        push_back
#define EB        emplace_back
#define F         first
#define S         second
#define endl      "\n"
#define SZ(x)     (int)x.size()

typedef pair<int,int>  PII;
typedef vector<PII>    VPII;
typedef vector<int>    VI;
typedef vector<VI>     VVI;

auto clk=clock();

//constants
const int MOD       = 1e9+7;
const long long inf = 1e17;
const double eps    = 1e-6;
const int  LOGN     = 25;

// maths stuff
template <class T,class U>T pow_mod(T a,T b,int m= MOD){long long  res = 1;while(b){ if(b&1) res =((long long)res*a)%m; a = ((long long)a*a)%m;b >>=1;}return res;}
template <typename T> T inv(T a){return pow_mod(a,MOD-2,MOD);}
template <typename T> T gcd(T a,T b){if(b == 0) return a;return gcd(b,a%b);}
template <typename T> T LCM(T a,T b){ return a*b /gcd(a,b);}
template <typename T> string to_bin(T num){string binary = "";while (num){binary += (num % 2 == 1 ? "1" : "0");num >>= 1;}reverse(binary.begin(), binary.end());return binary;}
////////////////////////////////////////////////////

template <int32_t MOD_> struct modnum {
    static constexpr int32_t MOD = MOD_;
    static_assert(MOD_ > 0, "MOD must be positive");
private:
    using ll = long long;
    int32_t v;
    static int32_t minv(int32_t a, int32_t m) {a %= m;assert(a);return a == 1 ? 1 : int32_t(m - ll(minv(m, a)) * ll(m) / a);}
public:
    modnum() : v(0) {}
    modnum(ll v_) : v(int32_t(v_ % MOD)) { if (v < 0) v += MOD; }
    explicit operator int32_t() const { return v; }
    friend std::ostream& operator << (std::ostream& out, const modnum& n) { return out << int32_t(n); }
    friend std::istream& operator >> (std::istream& in, modnum& n) { ll v_; in >> v_; n = modnum(v_); return in; }
 
    friend bool operator == (const modnum& a, const modnum& b) { return a.v == b.v; }
    friend bool operator != (const modnum& a, const modnum& b) { return a.v != b.v; }
 
    modnum inv() const {modnum res;res.v = minv(v, MOD);return res;}
    friend modnum inv(const modnum& m) { return m.inv(); }
    modnum neg() const {modnum res;res.v = v ? MOD-v : 0;return res;}
    friend modnum neg(const modnum& m) { return m.neg(); }
    modnum operator- () const {return neg();}
    modnum operator+ () const {return modnum(*this);}
    modnum& operator ++ () {v ++;if (v == MOD) v = 0;return *this;}
    modnum& operator -- () {if (v == 0) v = MOD;v --;return *this;}
    modnum& operator += (const modnum& o) {v -= MOD-o.v;v = (v < 0) ? v + MOD : v;return *this;}
    modnum& operator -= (const modnum& o) {v -= o.v;v = (v < 0) ? v + MOD : v;return *this;}
    modnum& operator *= (const modnum& o) {v = int32_t(ll(v) * ll(o.v) % MOD);return *this;}
    modnum& operator /= (const modnum& o) {return *this *= o.inv();}
 
    friend modnum operator ++ (modnum& a, int32_t) { modnum r = a; ++a; return r; }
    friend modnum operator -- (modnum& a, int32_t) { modnum r = a; --a; return r; }
    friend modnum operator + (const modnum& a, const modnum& b) { return modnum(a) += b; }
    friend modnum operator - (const modnum& a, const modnum& b) { return modnum(a) -= b; }
    friend modnum operator * (const modnum& a, const modnum& b) { return modnum(a) *= b; }
    friend modnum operator / (const modnum& a, const modnum& b) { return modnum(a) /= b; }
};
using num = modnum<(int)(MOD)>;


  
void __Solve__(){

   int n;
   cin >> n;
    
   num ans = 0;

}   

signed main()
{
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());
	cout<<fixed<<setprecision(12);
    FASTIO
#ifdef LOCAL 
    freopen("input.txt", "r", stdin);freopen("output.txt", "w", stdout);
#endif 
    int test_case = 1;
    //cin >> test_case;
    forn(i,test_case){
        //cout << "Case #" << i+1<<": ";
        __Solve__();
    }
#ifdef LOCAL
	cerr<<"Time elapsed: "<<(double)(clock()-clk)/CLOCKS_PER_SEC<<"  seconds" << "\n";
#endif
}