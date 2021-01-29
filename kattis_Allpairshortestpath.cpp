
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

template<typename T,typename U> void umax(T &a,U b){if (b > a) a = b;}
template<typename T,typename U> void umin(T &a,U b){if (b < a) a = b;}

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
#define ALL(x)       x.begin(),x.end()
#define int          long long int
#define PB           push_back
#define EB           emplace_back
#define F            first
#define S            second
#define endl         "\n"
#define SZ(x)        (int)x.size()

typedef pair<int,int>    PII;
typedef vector<PII>      VPII;
typedef vector<int>      VI;
typedef vector<VI>       VVI;

auto clk=clock();

//constants
const int MOD          = 1e9+7;
const long long inf    = 1e17;
const double eps       = 1e-6;
const int  LOGN        = 25;

// maths stuff
template <typename T> T pow_mod(T a,T b,int m= MOD){long long  res = 1;while(b){ if(b&1) res =((long long)res*a)%m; a = ((long long)a*a)%m;b >>=1;}return res;}
template <typename T> T inv(T a){return pow_mod(a,MOD-2,MOD);}
template <typename T> T gcd(T a,T b){ if(b == 0) return a;return gcd(b,a%b);}
template <typename T> T LCM(T a,T b){ return a*b /gcd(a,b);}
template <typename T> string to_bin(T num){string binary = "";while (num){binary += (num % 2 == 1 ? "1" : "0");num >>= 1;}reverse(binary.begin(), binary.end());return binary;}
////////////////////////////////////////////////////

struct node{
    int s,val,lazy1= 0,lazy2 =0,psum = 0;
    bool lz2 = 0;
};
 
const int N = 2e5+1;
 
node tree[4*N];
int arr[N];
int rooms[N];
int ans[N];
 
 
 
 
void apply1(int index,int v,int s,int e){
    tree[index].s += v;
    tree[index].val += (e-s+1)*v;
    tree[index].lazy1 += v;
}
void apply2(int index,int v,int s,int e){
    tree[index].s = v;
    tree[index].val = (e-s+1)*v;
    tree[index].lazy2 = v;
    tree[index].lazy1 = 0;
}
 
void push(int index,int l,int r){
    int mid = (l+r)/2;
    
    if(tree[index].lazy2){
        apply2(2*index,tree[index].lazy2,l,mid);
        apply2(2*index+1,tree[index].lazy2,mid+1,r);
        tree[index].lazy2 = 0;
    }
    
    if(tree[index].lazy1){
        apply1(2*index,tree[index].lazy1,l,mid);
        apply1(2*index+1,tree[index].lazy1,mid+1,r);
        tree[index].lazy1 = 0;
    }
    
    
    
}
void build(int s,int e,int index){
    if(s == e){
        tree[index].s = arr[s];
        tree[index].psum = arr[s];
        return;
    }
    int mid = (s+e)/2;
    build(s,mid,index*2);
    build(mid+1,e,index*2+1);
 
    //tree[index].val = tree[2*index].val + tree[2*index+1].val;
    tree[index].psum = tree[2*index].psum + tree[2*index+1].psum;
}
 
void update(int s,int e,int p,int v,int index){
    if( s > p || e < p) return;
    if(s == e){
        arr[p] = v;
        tree[index].s = v;
        tree[index].mini = v;
        return;
    }
    int mid = (s+e)/2;
    update(s,mid,p,v,index*2);
    update(mid+1,e,p,v,index*2+1);
    tree[index].psum = tree[2*index].psum + tree[2*index+1].psum;
}
void update2(int s,int e,int l,int r,int v,int index, int t){
    if(s > r || e < l)return;
    if(s >= l && e <=r ) {
        if(t == 2) apply2(index,v,s,e);
        else apply1(index,v,s,e);
        return;
    }
    push(index,s,e);
    int mid = (s+e)/2;
    update2(s,mid,l,r,v,index*2,t);
    update2(mid+1,e,l,r,v,index*2+1,t);
    tree[index].val = tree[2*index].val + tree[2*index+1].val;
}
 
 
int query(int s,int e,int l,int r,int index){
 
    if(s > r || e < l) return 0;
    if(s >= l && e <=r ) return tree[index].psum;
 
    int mid = (s+e)/2;
    int L = query(s,mid,l,r,2*index);
    int R = query(mid+1,e,l,r,2*index+1);
    return L + R;
 
}
 
int n,q;

void __Solve__(){
   cin >> n >> q;
   forn(i,n) cin >> arr[i];
   build(0,n-1,1);
 
    while(q--){
       int t;
       cin >> t;
       if(t == 1){
           int k,v;
           cin >> k >> v;
            k--;
            update(0,n-1,k,v,1);
       }else{
            int a,b;
            cin >> a >> b; a--;b--;
             cout << query(0,n-1,a,b,1) << endl;
        }
 
   }
    
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