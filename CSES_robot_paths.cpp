
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
template <class T,class U>T pow_mod(T a,T b,int m= mod){long long  res = 1;while(b){ if(b&1) res =((long long)res*a)%m; a = ((long long)a*a)%m;b >>=1;}return res;}
template <typename T> T inv(T a){return pow_mod(a,mod-2,mod);}
template <typename T> T gcd(T a,T b){if(b == 0) return a;return gcd(b,a%b);}
template <typename T> T lcm(T a,T b){ return a*b /gcd(a,b);}
template <typename T> string to_bin(T num){string binary = "";while (num){binary += (num % 2 == 1 ? "1" : "0");num >>= 1;}reverse(binary.begin(), binary.end());return binary;}
////////////////////////////////////////////////////

const int OFFSET = 1.1e6;
const int N = 3e6;


struct fenwick{
    vector<int> BIT;
    int N;
    fenwick(int n){
        N = n;
        BIT.assign(n,0);
    }
    void add(int pos,int val ){
        for(;pos<N;pos+=pos&-pos){
            BIT[pos]+= val;
        }
    }
    int sum(int pos){
        int ans = 0;
        for(;pos>0;pos-=pos&-pos){
            ans += BIT[pos];
        }
        return ans;
    }
    int sum(int l,int r){
        return sum(r) -sum(l-1);
    } 
};

struct event{
    int x;
    int type = 0;
    int id;
    bool operator<(const event &o) const{
        if(x != o.x){
            return x < o.x;
        }else {
            return type < o.type;
        }
    }
    void apply(){
        x += OFFSET;
    }
};
vector<event> all;

void __Solve__(){
    

    int n;
    cin >> n;
    all.resize(n);
    vector<array<int,4>> segs(n);
    forn(i,n){
        forn(j,4){
            cin >> segs[i][j];
            segs[i][j] += OFFSET;
        }
    }
    forn(i,n){
        int x1= segs[i][0],x2= segs[i][2];
        int y1= segs[i][1],y2= segs[i][3];
        if(y1 == y2){
            event e1;
            e1.x = x1,e1.id =i,e1.type = -1; 
            all.push_back(e1);
            event e2;
            e2.x = x2,e2.id =i,e2.type = 1; 
            all.push_back(e2);
        }else{
            event e1;
            e1.x = x1,e1.id =i,e1.type = 0; 
            all.push_back(e1);
        }
    }
    

    sort(ALL(all));

    fenwick ft(N);

    int ans = 0;
    for(auto e : all){
        if(e.type == -1 || e.type == 1){
            int id = e.id;
            int y = segs[id][3];
            ft.add(y,e.type*-1);
        }else{
            int id = e.id;
            int y1 = segs[id][1];
            int y2 = segs[id][3];

            ans += ft.sum(y1,y2);
        }
    }
    cout << ans << endl;
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