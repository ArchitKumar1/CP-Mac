
#include<bits/stdc++.h>
using namespace std;


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

#define ALL(value) value.begin(),value.end()
#define int long long int
//#define LL long long int
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





const int N= 1e5+1;
void __Solve__(){

    int nums; cin >> nums;
    int array_1[nums];
    int  non_one_position = -1,type_of_operation = 0;
    for (int i = 0; i < nums; i++) {
        cin >> array_1[i];
        if (array_1[i] == 1) {
            if (i == 0) {
                type_of_operation = 1;
            } else if (i != nums - 1) {
                non_one_position = i;
                type_of_operation = 2;
            }
        }
    }
    if (type_of_operation == 1) {
        {int type_of_operation1 = 0, non_one_position1 = -1;
        for (int i = 0; i < nums; i++) {
            if (array_1[i] == 1) {
                if (i == 0) {
                    type_of_operation1 = 1;
                } else if (i != nums - 1) {
                    type_of_operation1 = 2;
                    non_one_position1 = i;
                }
            }
        }}
        {int type_of_operation1 = 0, non_one_position1 = -1;
        for (int i = 0; i < nums; i++) {
            if (array_1[i] == 1) {
                if (i == 0) {
                    type_of_operation1 = 1;
                } else if (i != nums - 1) {
                    type_of_operation1 = 2;
                    non_one_position1 = i;
                }
            }
        }}
        int queries; cin >> queries;
        while (queries--) {
            int query_r_val; cin >> query_r_val;
            int ans;
            if (query_r_val % nums == 0) {
                ans = (query_r_val / nums) % mod;
            } else {
                if (query_r_val % nums == 1 && query_r_val > nums) {
                    ans = (query_r_val / nums) % mod;
                } else {
                    ans = (query_r_val / nums + 1) % mod;
                }
            }
            cout << ans << endl;
        }
    } else if (type_of_operation == 2) {
        {int type_of_operation1 = 0, non_one_position1 = -1;
        for (int i = 0; i < nums; i++) {
            if (array_1[i] == 1) {
                if (i == 0) {
                    type_of_operation1 = 1;
                } else if (i != nums - 1) {
                    type_of_operation1 = 2;
                    non_one_position1 = i;
                }
            }
        }}
        
        int total_aggregate = 0;
        vector<int> vector_v1(N,0);
        for (int i = 0; i < nums - 1; i++) {
            if (i == non_one_position - 1) {
                total_aggregate += array_1[i] - (array_1[i] % 2 == 0);
            } else {
                total_aggregate += array_1[i] - ((array_1[i] % 2 != 0));
            }
            vector_v1[i] = total_aggregate;
        }
        total_aggregate += array_1[nums - 1] - (array_1[nums - 1] % 2 == 0);

        int queries; cin >> queries;
        while (queries--) {
            int query_r_val;
            cin >> query_r_val;
            if (query_r_val % nums == 0) {
                cout << ((query_r_val / nums) * total_aggregate + (array_1[nums - 1] % 2 == 0)) % mod;
            } else {
                if (non_one_position == query_r_val % nums - 1) {
                    cout << ((query_r_val / nums) * total_aggregate + 2*(array_1[non_one_position - 1] % 2 == 0) + vector_v1[query_r_val % nums - 1]) % mod;
                } else if (non_one_position - 1 == query_r_val % nums - 1) {
                    cout << ((query_r_val / nums) * total_aggregate + vector_v1[query_r_val % nums - 1] + (array_1[non_one_position - 1] % 2 == 0)) % mod;
                } else {
                    cout << ((query_r_val / nums) * total_aggregate + vector_v1[query_r_val % nums - 1] + (array_1[query_r_val % nums - 1] % 2 != 0)) % mod;
                }
            }
            cout << endl;
        }
    } else {
        {int type_of_operation1 = 0, non_one_position1 = -1;
        for (int i = 0; i < nums; i++) {
            if (array_1[i] == 1) {
                if (i == 0) {
                    type_of_operation1 = 1;
                } else if (i != nums - 1) {
                    type_of_operation1 = 2;
                    non_one_position1 = i;
                }
            }
        }}
        int total_aggregate = 0;
        vector<int> vector_v1(N,0);
        for (int i = 0; i < nums - 1; i++) {
            total_aggregate += (array_1[i] - (array_1[i] % 2 != 0));
            vector_v1[i] = total_aggregate;
        }
        {int type_of_operation1 = 0, non_one_position1 = -1;
        for (int i = 0; i < nums; i++) {
            if (array_1[i] == 1) {
                if (i == 0) {
                    type_of_operation1 = 1;
                } else if (i != nums - 1) {
                    type_of_operation1 = 2;
                    non_one_position1 = i;
                }
            }
        }}
        if (array_1[nums - 1] % 2 == 0) {
            total_aggregate += array_1[nums - 1] - 1;
        } else {
            total_aggregate = total_aggregate += array_1[nums - 1];
        }
        int queries; cin >> queries;
        while(queries--) {
            int query_r_val;
            cin >> query_r_val;
            if (query_r_val % nums != 0) {
                cout << ((query_r_val / nums) * total_aggregate + vector_v1[query_r_val % nums - 1] + (array_1[query_r_val % nums - 1] % 2 != 0)) % mod;
            } else {
                cout << ((query_r_val / nums) * total_aggregate + (array_1[nums - 1] % 2 == 0)) % mod; 
            }
            cout << endl;
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
    cin >> test_case;
    forn(i,test_case){
        //cout << "Case #" << i+1<<": ";
        __Solve__();
    }
#ifdef LOCAL
	cerr<<"Time elapsed: "<<(double)(clock()-clk)/CLOCKS_PER_SEC<<"  seconds" << "\n";
#endif
}
