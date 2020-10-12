
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
int MRL = 10;

// maths stuff
template <class T,class U>T pow_mod(T a,T b,int m= mod){long long  res = 1;while(b){ if(b&1) res =((long long)res*a)%m; a = ((long long)a*a)%m;b >>=1;}return res;}
template <typename T> T inv(T a){return pow_mod(a,mod-2,mod);}
template <typename T> T gcd(T a,T b){if(b == 0) return a;return gcd(b,a%b);}
template <typename T> T lcm(T a,T b){ return a*b /gcd(a,b);}
template <typename T> string to_bin(T num,int pad = 32){string binary = "";while (num){binary += (num % 2 == 1 ? "1" : "0");num >>= 1;}reverse(binary.begin(), binary.end());binary = string(pad-binary.size(),'0')+binary;return binary;}
////////////////////////////////////////////////////



struct Point {
    int x,y;
    Point(int x,int y) : x(x),y(y) {};

    Point N(){
        if((y+2*x)>0){
            return Point(x,y+2*x);
        }
        if((y+2*x)<0){
            return Point(-x,-y-2*x);
        }
        return Point(-1e9,-1e9);
    }
    Point S(){
        if((y-2*x)>0){
            return Point(x,y-2*x);
        }
        if((y-2*x)<0){
            return Point(-x,-y+2*x);
        }
        return Point(-1e9,-1e9);
    }
    Point E(){
        return Point(x+2*y,y);
    }
    Point W(){
        return Point(x-2*y,y);
    }
    bool operator<(const Point& p) const{
        return p.x < p.y;
    }
    
};



ostream& operator<<(ostream &os,Point &p){
    os<<"[ ";cout << p.x << ", " <<p.y;return os<<"]";
}



void __Solve__(){
    
   int x1,y1,x2,y2;
   cin >> x1 >> y1 >> x2 >> y2;

    Point s(x1,y1);
    Point e(x2,y2);

    int cost = 0;
    queue<Point> q;
    q.push(s);
    bool found = 0;
    map<pair<int,int>,int> m1;

    while(q.size() && !found){
        int l = q.size();
        forn(i,l){
            Point p = q.front();q.pop();
            if(p.x == e.x && p.y == e.y){
                found = 1;
                break;
            }
            //trace(p);
            // cout << "MB\n";
            // for(auto x: m1){
            //     cout << x.first.first << " " << x.first.second << " " << x.second << endl;
            // }
            // cout << "ME\n";
            if(m1[{p.x,p.y}] == 1){ 
                //cout <<"DMG\n";
                continue;
            }
            m1[{p.x,p.y}] = 1;
            
            Point pn = p.N(),ps = p.S(),pe = p.E(),pw= p.W();
            if(p.x == 1 && p.y == 1){
                q.push(Point(-1,1));
            }
            if(p.x == -1 && p.y == 1){
                q.push(Point(1,1));
            }
            if(pn.x!= -1e9) q.push(pn);
            if(ps.x!= -1e9) q.push(ps);
            q.push(pe);
            q.push(pw);
            //trace(p,pn,ps,pe,pw);
        }
        //cout << endl;
        cost += 1;
    }
    cout << cost-1 << endl;
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
    cin >> test_case;
    forn(i,test_case){
        //cout << "Case #" << i+1<<": ";
        __Solve__();
    }
#ifdef LOCAL
	cerr<<"Time elapsed: "<<(double)(clock()-clk)/CLOCKS_PER_SEC<<"  seconds" << "\n";
#endif
}