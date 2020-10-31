#pragma GCC optimize("O3")
//#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("unroll-loops")
 
#include<bits/stdc++.h>
 
using namespace std;
 
template<class T> ostream& operator<<(ostream &os,vector<T> V){os<<"[ ";for(auto v:V)os<<v<<" ";return os<<"]";}
template<class L,class R> ostream& operator<<(ostream &os,pair<L,R> P){return os<<"("<<P.first<<","<<P.second<<")";}
 
#ifdef LOCAL
#define trace(...) __f(#__VA_ARGS__,__VA_ARGS__)
template<typename Arg1>
void __f(const char* name,Arg1&& arg1){
	cout<<name<<" : "<<arg1<<endl;
}
template<typename Arg1,typename... Args>
void __f(const char* names,Arg1&& arg1,Args&&... args){
		const char* comma=strchr(names+1,',');cout.write(names,comma-names)<<" : "<<arg1<<" | ";__f(comma+1,args...);
}
#else
#define trace(...) 1
#endif
 
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
#define TC int testcase; cin >> testcase;while(testcase--)
#define forn(i,n) for(int i=0;i<n;i++)
#define rep(i,a,b) for(int i = a;i<=b;i++)
 
#define ALL(x) x.begin(),x.end()
#define int long long int
// #define LL long long int
#define PB push_back
#define EB emplace_back
#define F first
#define S second
#define endl "\n"
 
typedef pair<int,int>PII;
typedef vector<PII> VPII;
typedef vector<int> VI;
typedef vector<VI> VVI;
 
auto clk=clock();
 
int mod = 7340033;
const long long inf = 1e17;
const double eps = 1e-6;
const int  LOGN = 25;
 
 
template <class T>
void RV(vector<T> v){
    for(T &c : v) cin >> c;
}
template <class T>
void RV(vector<vector<T>> v){
    int n = v.size();
    for(vector<T> &c : v) RV(c);
}
template <class T>
vector<T> V(int n,T value = 0){
    vector<T> v(n,value);
    return v;
}
template <class T>
vector<vector<T>> V(int n,int m,T value = 0){
    vector<vector<T>> v(n,vector<T>(m,value));
    return v;
}
 
int pow_mod(int a,int b,int m= mod){
    long long  res = 1;
    while(b){ if(b&1) res =((long long)res*a)%m; a = ((long long)a*a)%m;b >>=1;}
    return res;
}
template <typename T> 
T gcd(T a,T b){
    if(b == 0) return a;return gcd(b,a%b);
}
template <typename T> 
T lcm(T a,T b){ 
    return a*b /gcd(a,b);
}
template <typename T,typename U>
T add(T a, U b){
    a = (long long)a+b;a = (a+mod)%mod;return a;
}
template <typename T,typename U>
T mul(T a, U b){
    a = ((long long)a*b)%mod;return a;
}
template <typename T>
T add(vector<T> v){
    long long sum=0; for(T x : v) sum = (sum + x)%mod;return (T)sum;
}
template <typename T> 
T mul(vector<T> v){ 
    long long  sum = 1LL;for(T x : v)sum = (sum * x)%mod;return (T)sum;
}
template <typename T>
string to_bin(T num){
    string binary = "";
    while (num){binary += (num % 2 == 1 ? "1" : "0");num >>= 1;}
    reverse(binary.begin(), binary.end());
    return binary;
}
////////////////////////////////////////////////////
 
 
struct node{
    int s,val,lazy1= 0,lazy2 =0;
    bool lz2 = 0;
};
 
const int N = 2e5+1;
 
node tree[4*N];
int arr[N];
 
 
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
        tree[index].val = arr[s];
        return;
    }
    int mid = (s+e)/2;
    build(s,mid,index*2);
    build(mid+1,e,index*2+1);
 
    tree[index].val = tree[2*index].val + tree[2*index+1].val;
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
    if(s >= l && e <=r ) return tree[index].val;
 
    push(index,s,e);
    int mid = (s+e)/2;
    int L = query(s,mid,l,r,2*index);
    int R = query(mid+1,e,l,r,2*index+1);
    return L+R;
 
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
           int a,b,u;
           cin >> a >>  b >> u;
           a--,b--;
            update2(0,n-1,a,b,u,1,1);
       }else if(t == 2){
           int a,b,u;
           cin >> a >>  b >> u;
           a--,b--;
            update2(0,n-1,a,b,u,1,2);
       }else{
            int a,b;
            cin >> a >>  b ;
            a--,b--;
             cout << query(0,n-1,a,b,1) << endl;
        }
 
   }
   
}
 
signed main()
{
    // srand(chrono::high_resolution_clock::now().time_since_epoch().count());
	// cout<<fixed<<setprecision(12);
    FASTIO
#ifdef LOCAL 
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
 #endif 
    int test_case = 1;
    //  cin >> test_case;
    while(test_case--){
        __Solve__();
    }
#ifdef LOCAL
	cerr<<"Time elapsed: "<<(double)(clock()-clk)/CLOCKS_PER_SEC<<"  seconds" << "\n";
#endif
    
}