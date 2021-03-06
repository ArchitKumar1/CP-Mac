
#pragma GCC optimize("O3")
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("unroll-loops")
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


//make vectors
template <typename T> vector<T> GV(int n){return vector<T>(n);}
template <typename T> vector<vector<T>> GV(int n,int m){return vector<vector<T>>(n,vector<T>(m));}
template <typename T> vector<vector<vector<T>>> GV(int n,int m,int o){return vector<vector<vector<T>>>(n,vector<vector<T>>(m,vector<T>(o)));}

//reading vectors
template <class T> void RV(vector<T> &v){for(auto &c : v) cin >> c;}
template <class T> void RV(vector<vector<T>> &v){for(auto &c : v) RV(c);}
template <class T> void RV(vector<vector<vector<T>>> &v){for(auto &c : v) RV(c);}


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

typedef pair<int,int>PII;
typedef vector<PII> VPII;
typedef vector<int> VI;
typedef vector<VI> VVI;

auto clk=clock();

//constants
const int mod = 1e9+7;
const long long inf = 1e17;
const double eps = 1e-6;
const int  LOGN = 25;

// maths stuff
template <class T,class U>T pow_mod(T a,T b,int m= mod){long long  res = 1;while(b){ if(b&1) res =((long long)res*a)%m; a = ((long long)a*a)%m;b >>=1;}return res;}
template <typename T> T inv(T a){return pow_mod(a,mod-2,mod);}
template <typename T> T gcd(T a,T b){if(b == 0) return a;return gcd(b,a%b);}
template <typename T> T lcm(T a,T b){ return a*b /gcd(a,b);}
template <typename T> string to_bin(T num){string binary = "";while (num){binary += (num % 2 == 1 ? "1" : "0");num >>= 1;}reverse(binary.begin(), binary.end());return binary;}
////////////////////////////////////////////////////


 

 
struct node{
    int s,val = 0,lazy1= 0,lazy2 =0,mini = 1e9;
    bool lz2 = 0;
};
 
const int N = 2e5+1;
 
node tree[4*N];
int arr[N];
int brr[N];
int pos[N];
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
        tree[index].val = arr[s];
        return;
    }
    int mid = (s+e)/2;
    build(s,mid,index*2);
    build(mid+1,e,index*2+1);
 
    tree[index].val = tree[2*index].val + tree[2*index+1].val;
    //tree[index].mini = max(tree[2*index].mini, tree[2*index+1].mini);
}
 
void update(int s,int e,int p,int v,int index){
    if( s > p || e < p) return;
    if(s == e){
        tree[index].s = v;
        tree[index].val = v;
        return;
    }
    int mid = (s+e)/2;
    update(s,mid,p,v,index*2);
    update(mid+1,e,p,v,index*2+1);
    //tree[index].mini = max(tree[2*index].mini, tree[2*index+1].mini);
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
 
    int mid = (s+e)/2;
    int L = query(s,mid,l,r,2*index);
    int R = query(mid+1,e,l,r,2*index+1);
    return L+R;
 
}
 
int n,q;

VPII Q[N];
  
void __Solve__(){
    
   cin >> n >> q;
   forn(i,n){
       cin >> arr[i];
   } 

    forn(i,q){
        int a,b;
        cin >> a >> b;
        a--;b--;
        Q[b].push_back({a,i});
    }
    map<int,int> m1;

    
    for(int i = 0;i<n;i++){
        update(0,n-1,i,1,1);
        if(m1.find(arr[i]) != m1.end() ){
            update(0,n-1,m1[arr[i]],0,1);
        }
        m1[arr[i]] = i;
        for(PII p : Q[i]){
            ans[p.S] = query(0,n-1,p.F,i,1);
        }

    }
    forn(i,q){
        cout << ans[i] << endl;
    }
 
   
}
signed main()
{
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());
	cout<<fixed<<setprecision(25);
    FASTIO
#ifdef LOCAL 
    freopen("input.txt", "r", stdin);freopen("output.txt", "w", stdout);
#endif 
    int test_case = 1;
    //cin >> test_case;
    forn(i,test_case){
        //Google Code Jam
        //cout << "Case #" << i+1<<": ";
        __Solve__();
    }
#ifdef LOCAL
	cerr<<"Time elapsed: "<<(double)(clock()-clk)/CLOCKS_PER_SEC<<"  seconds" << "\n";
#endif
}