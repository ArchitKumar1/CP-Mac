// #pragma GCC optimize("O3")
// #pragma comment(linker, "/stack:200000000")
// #pragma GCC optimize("unroll-loops")


#ifndef _GLIBCXX_NO_ASSERT
#include <cassert>
#endif
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#if __cplusplus >= 201103L
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cwchar>
#include <cwctype>
#endif

// C++
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#if __cplusplus >= 201103L
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#endif

using namespace std;

template<class T> ostream& operator<<(ostream &os,vector<T> V){os<<"[ ";for(auto v:V)os<<v<<" ";return os<<"]";}
template<class L,class R> ostream& operator<<(ostream &os,pair<L,R> P){return os<<"("<<P.first<<","<<P.second<<")";}


#ifndef ONLINE_JUDGE
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

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL);
#define TC int t; cin >> t;while(t--)
#define forn(i,n) for(int i=0;i<n;i++)

#define ALL(x) x.begin(),x.end()
#define LL long long int
#define PB push_back
#define EB emplace_back
#define F first
#define S second
#define endl "\n"

typedef pair<int,int>PII;
typedef vector<PII> VPII;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<LL> VL;
typedef vector<VL> VLL;
typedef pair<LL,LL>PLL;
typedef vector<PLL> VPLL;
auto clk=clock();

const int mod = pow(10,9) +7;
const int inf = 2e9;
const LL linf = 2e18;
const double eps = 1e-9;

template <typename T,typename U>void add_mod(T &a, U b){a = (LL)a+b;a = (a+mod)%mod;}
template <typename T,typename U>void mul_mod(T &a, U b){a = ((LL)a*b)%mod;}
template <typename T,typename U>T add_mod1(T a, U b){a = (LL)a+b;a = (a+mod)%mod;return a;}
template <typename T,typename U>T mul_mod1(T a, U b){a = ((LL)a*b)%mod;return a;}
template <typename T> T add_mod(vector<T> v){LL sum=0; for(T x : v) sum = (sum + x)%mod;return (T)sum;}
template <typename T> T mul_mod(vector<T> v){ LL sum = 1LL;for(T x : v)sum = (sum * x)%mod;return (T)sum;}
template <typename T>string to_bin(T num){string binary = "";while (num){binary += (num % 2 == 1 ? "1" : "0");num >>= 1;}reverse(binary.begin(), binary.end());return binary;}
template <typename T> T gcd(T a,T b){if(b == 0) return a;return gcd(b,a%b);}
int pow_mod(int a,int b,int m= mod){LL res = 1;while(b){ if(b&1) res =((LL)res*a)%m; a = ((LL)a*a)%m;b >>=1;}return res;}
/////////////////////////////////////////////


VI arr;
int n;

VVI dp;
    

int main()
{
    FASTIO
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
   TC{
        cin >> n;
        arr = VI(n);
        dp = VVI(n+1,VI(2,INT_MAX));
        
        dp[0][0] = 0;
        dp[0][1] = 0;

        for(int i = 1;i<=n;i++){
            for(int j = 0;j<1;j++){
                if(j){
                    if(i-1>=0)dp[i][j] = min(dp[i][j],dp[i-1][j^1]);
                    if(i-2>=0)dp[i][j] = min(dp[i][j],dp[i-2][j^1]);
                }else{
                    if(i-1>=0)dp[i][j] = min(dp[i][j],arr[i-1] + dp[i-1][j^1]);
                    if(i-2>=0)dp[i][j] = min(dp[i][j],arr[i-1]+arr[i-2]+dp[i-2][j^1]);
                }
            }
        }
        cout << dp[n][0] << " " << dp[n][1] << endl;
   }

   
    

#ifndef ONLINE_JUDGE
	cerr<<"Time elapsed: "<<(double)(clock()-clk)/CLOCKS_PER_SEC<<endl;
#endif
    
}