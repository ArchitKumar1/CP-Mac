
#include<bits/stdc++.h>
using namespace std;

// #include "ext/pb_ds/assoc_container.hpp"
// #include "ext/pb_ds/tree_policy.hpp"
// using namespace __gnu_pbds;
// template<class T> 
// using ordered_set = tree<T, null_type,less<T>, rb_tree_tag,tree_order_statistics_node_update> ;
// template<class key, class value, class cmp = std::less<key>>
// using ordered_map = tree<key, value, cmp, rb_tree_tag, tree_order_statistics_node_update>;

template<class T> ostream& operator<<(ostream &os, set<T> S){os << "{ ";for(auto s:S) os<<s<<" ";return os<<"}";}
template<class T> ostream& operator<<(ostream &os, unordered_set<T> S){os << "{ ";for(auto s:S) os<<s<<" ";return os<<"}";}
template<class T> ostream& operator << (ostream& os, multiset<T> S){os << "{ ";for(auto s:S) os<<s<<" ";return os<<"}";}
//template<class T> ostream& operator<<(ostream &os, ordered_set<T> S){os << "{ ";for(auto s:S) os<<s<<" ";return os<<"}";}
template<class L, class R> ostream& operator<<(ostream &os, pair<L,R> P) {return os << "(" << P.first << "," << P.second << ")";}
template<class L, class R> ostream& operator<<(ostream &os, map<L,R> M) {os << "{ ";for(auto m:M) os<<"("<<m.first<<":"<<m.second<<") ";return os<<"}";}
template<class T> ostream& operator<<(ostream &os,vector<T> V){os<<"[ ";for(auto v:V)os<<v<<" ";return os<<"]";}


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

//reading vectors
template <class T> void RV(vector<T> &v){for(auto &c : v) cin >> c;}
template <class T> void RV(vector<vector<T>> &v){for(auto &c : v) RV(c);}


//defines and typedefs
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
#define TC int testcase; cin >> testcase;while(testcase--)
#define forn(i,n) for(int i=0;i<n;i++)
#define rep(i,n) for(int i = 1;i<=n;i++)

#define ALL(x) x.begin(),x.end()
#define int long long int
// #define LL long long int
#define PB push_back
#define EB emplace_back
#define F first
#define S second
#define endl "\n"
#define SZ(x) (int)x.size()

typedef pair<int,int>PII;
typedef vector<PII> VPII;
typedef vector<int> VI;
typedef vector<VI> VVI;

auto clk=clock();

//constants
int mod = 1e9+7;
const long long inf = 1e17;
const double eps = 1e-6;
const int  LOGN = 25;

// maths stuff
template <typename T> T pow_mod(T a,T b,int m= mod){long long  res = 1;while(b){ if(b&1) res =((long long)res*a)%m; a = ((long long)a*a)%m;b >>=1;}return res;}
template <typename T> T inv(T a){return pow_mod(a,mod-2,mod);}
template <typename T> T gcd(T a,T b){if(b == 0) return a;return gcd(b,a%b);}
template <typename T> T lcm(T a,T b){ return a*b /gcd(a,b);}
template <typename T> string to_bin(T num){string binary = "";while (num){binary += (num % 2 == 1 ? "1" : "0");num >>= 1;}reverse(binary.begin(), binary.end());return binary;}
////////////////////////////////////////////////////
struct node{
    int s,val,lazyp = 0,lazyc =0;
    int uset = -1,umul = 1,uadd = 0;
};
 
const int N = 2e5+1;
 
node tree[4*N];
int arr[N];
 

// c p s

// (x=c)*p + s

// 3. c = c1 , p=0,s=0
// 2. p = p2   p=p*p2 ,s = s*p2
// 1  s = s3   s + s3 ,



void applyset(int index,int v,int s,int e){
    tree[index].s = v;

    tree[index].uadd =0;
    tree[index].umul = 1;
    tree[index].uset = v;
    (tree[index].val = (e-s+1)*v)%=mod;
}
void applymul(int index,int v,int s,int e){
    (tree[index].s *= v)%=mod;

    (tree[index].uadd *= v)%=mod;
    (tree[index].umul *= v)%=mod;
    (tree[index].val *= v)%=mod;
}
void applyadd(int index,int v,int s,int e){
    tree[index].s = v;

    (tree[index].val += (e-s+1)*v)%=mod;
    (tree[index].uadd += v)%=mod;
}
 
 
void push(int index,int l,int r){
    int mid = (l+r)/2;
    
    if(tree[index].uset > -1){
        applyset(2*index,tree[index].uset,l,mid);
        applyset(2*index+1,tree[index].uset,mid+1,r);
        tree[index].uset = -1;
    }
    
    if(tree[index].umul != 1){
        applymul(2*index,tree[index].umul,l,mid);
        applymul(2*index+1,tree[index].umul,mid+1,r);
        tree[index].umul = 1;
    }
    if(tree[index].uadd != 0){
        applyadd(2*index,tree[index].uadd,l,mid);
        applyadd(2*index+1,tree[index].uadd,mid+1,r);
        tree[index].uadd = 0;
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
 
    tree[index].val = (tree[2*index].val + tree[2*index+1].val)%mod;
}
 
 
void update2(int s,int e,int l,int r,int v,int index, int t){
    if(s > r || e < l)return;
    if(s >= l && e <=r ) {
        if(t == 1) applyadd(index,v,s,e);
        if(t == 2) applymul(index,v,s,e);
        if(t == 3) applyset(index,v,s,e);
        return;
    }
    push(index,s,e);
    int mid = (s+e)/2;
    update2(s,mid,l,r,v,index*2,t);
    update2(mid+1,e,l,r,v,index*2+1,t);
    tree[index].val = (tree[2*index].val + tree[2*index+1].val)%mod;
}
 
 
int query(int s,int e,int l,int r,int index){
 
    if(s > r || e < l) return 0;
    if(s >= l && e <=r ) return tree[index].val;
 
    push(index,s,e);
    int mid = (s+e)/2;
    int L = query(s,mid,l,r,2*index);
    int R = query(mid+1,e,l,r,2*index+1);
    return (L+R)%mod;
 
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
           // add x to a;
           int a,b,u;
           cin >> a >>  b >> u;
           a--,b--;
            update2(0,n-1,a,b,u,1,1);
       }else if(t == 2){
            int a,b,u;
            cin >> a >>  b >> u;
            a--,b--;
            update2(0,n-1,a,b,u,1,2);
       }else if(t ==3){
            int a,b,u;
            cin >> a >>  b >> u;
            a--,b--;
             update2(0,n-1,a,b,u,1,3);
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
    
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());
	cout<<fixed<<setprecision(2);
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