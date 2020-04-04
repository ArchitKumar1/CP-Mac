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
auto clk=clock()

int mod = pow(10,9) +7;
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


const LL N = 1.0e5 + 5;
vector<LL> allf[N];



int main()
{
    FASTIO
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    allf[0] = {};
    for(LL x = 1;x<N;x++){
        for(LL i =1;i*i<=x;i++){
            if(x%i == 0){
                allf[x].push_back(i);
                if(x/i != i){
                    allf[x].push_back(x/i);
                }
            }
        }
    }
    
    TC{
        LL n,m;
        cin >> n >> m;
        LL arr[n],brr[m];
        forn(i,n) cin >> arr[i];
        forn(j,m) cin >> brr[j];
        unordered_map<LL,LL> xl,xr,yu,yd;
        forn(i,n){
            if(arr[i] >=0){
                xr[arr[i]] = 1;
            }else{
                xl[-arr[i]] = 1;
            }
        }
        forn(j,m){
            if(brr[j] >=0){
                yu[brr[j]] = 1;
            }else{
                yd[-brr[j]] = 1;
            }
        }
        LL ans = 0;
        for(LL c : brr){
            c = abs(c);
            vector<LL> facts = allf[c];

            for(LL f : facts){
                // trace(c,f,c*c/f);
                if(xl.find(f) != xl.end() && xr.find(c*c/f) != xr.end()){
                    ans+=1;
                }
                if(xr.find(f) != xr.end() && xl.find(c*c/f) != xl.end()){
                    if( f  != c){
                        ans +=1;
                    }
                }
            }
        }

        for(LL c : arr){
            c = abs(c);
            vector<LL> facts= allf[c];
            for(LL f : facts){
                // trace(c,f,c*c/f);
                if(yu.find(f) != yu.end() && yd.find(c*c/f) != yd.end()){
                    ans+=1;
                }
                if(yd.find(f) != yd.end() && yu.find(c*c/f) != yu.end()){
                    if( f  != c){
                        ans +=1;
                    }
                }
            }
        }
        cout << ans << endl;
    }
    VL v1 = allf[60];
    sort(ALL(v1));

    VL v2 = allf[3600];
    sort(ALL(v2));

    cout << v1 << endl;
    cout << v2 << endl;
#ifndef ONLINE_JUDGE
	cerr<<"Time elapsed: "<<(double)(clock()-clk)/CLOCKS_PER_SEC<<endl;
#endif
    
}