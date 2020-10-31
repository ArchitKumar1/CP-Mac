
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
template <class T,class U>T pow_mod(T a,T b,int m= mod){long long  res = 1;while(b){ if(b&1) res =((long long)res*a)%m; a = ((long long)a*a)%m;b >>=1;}return res;}
template <typename T> T inv(T a){return pow_mod(a,mod-2,mod);}
template <typename T> T gcd(T a,T b){if(b == 0) return a;return gcd(b,a%b);}
template <typename T> T lcm(T a,T b){ return a*b /gcd(a,b);}
template <typename T> string to_bin(T num){string binary = "";while (num){binary += (num % 2 == 1 ? "1" : "0");num >>= 1;}reverse(binary.begin(), binary.end());return binary;}
////////////////////////////////////////////////////



struct Q{
    int L,R,id;
};

const int N = 21000;
const int block = 150;


unordered_map<int,int>BIT;
int arr[N+1];
int ans[N+1];
Q queries[N+1];

int INF = 1e9+10;
bool cmp(Q a,Q b){
    if( (a.L/block) == (b.L/block)){
        if((a.L/block) &1){
            return a.R < b.R;
        }else{
            return a.R > b.R;
        }
    }else{
        return a.L/block < b.L/block;
    }
}

void add_f(int i,int val){
    while(i < INF){
        BIT[i] += val;
        i += (i&-i);
    }
}
int sum_f( int i){
    int ans = 0LL;
    while(i > 0){
        ans += BIT[i];
        i -= (i&-i);
    }
    return ans;
}

int fans = 0;

void add(int i,int type){
    //trace(i,type,1);
    if(type == 0){
        fans += sum_f(arr[i]-1);
    }else{
        fans += (sum_f(INF) -sum_f(arr[i]));
    }
    add_f(arr[i],1);
}
void remove(int i,int type){
    //trace(i,type,2);
    add_f(arr[i],-1);
    if(type == 0){
        fans -= sum_f(arr[i]-1);
    }else{
        fans -= (sum_f(INF) -sum_f(arr[i]));
    }
    
}

void __Solve__(){
    int n;
    cin >> n;
    forn(i,n) {
        cin >> arr[i];
        arr[i]+=3;
    }
    map<int,int> m1;
    map<int,int> val;
    int pos = 2;
    
    for(int c : arr){
        if(m1[c] == 0){
            m1[c] += 1;
            val[c] = pos++;
        }else{
            continue;
        }
    }

    int q;
    cin >> q;
    forn(i,q){
        cin >> queries[i].L >> queries[i].R;
        queries[i].L--,queries[i].R--;
        queries[i].id = i;
    }
    sort(queries,queries+q,cmp);

    int L = 0;
    int R = -1;

    for(int i = 0;i<q;i++){
        Q query = queries[i];
        int l = query.L;
        int r = query.R;
        int id = query.id;
        while(L < l){
            remove(L++,0);
        }
        while(L > l){
            add(--L,0);
        }
        while(R < r){
            add(++R,1);
        }
        while(R > r){
            remove(R--,1);
        }
        ans[id] = fans;
    }
    forn(i,q){
        cout << ans[i] << endl;
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