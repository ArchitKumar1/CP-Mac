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
#define ll unsigned long long int
#define vvi vector<vector<ll>>
#define MOD 1000000007
#define M 1000000007

void mat_mul(ll a[2][2], ll b[2][2])
{
    ll f=(a[0][0]*b[0][0]+a[0][1]*b[1][0])%MOD;
    ll s=(a[0][0]*b[0][1]+a[0][1]*b[1][1])%MOD;
    ll t=(a[1][0]*b[0][0]+a[1][1]*b[1][0])%MOD;
    ll ft=(a[1][0]*b[0][1]+a[1][1]*b[1][1])%MOD;
    
    a[0][0]=f;
    a[0][1]=s;
    a[1][0]=t;
    a[1][1]=ft;
}

void expo(ll a[2][2],ll n){
    
    ll res[2][2];
    res[0][0]=1;
    res[0][1]=0;
    res[1][0]=0;
    res[1][1]=1;

    while (n > 0) {
        if (n & 1)
            mat_mul(res,a);

        mat_mul(a,a);
        n >>= 1;
    }
    
    a[0][0]=res[0][0];
    a[0][1]=res[0][1];
    a[1][0]=res[1][0];
    a[1][1]=res[1][1];

}

int main(){
    
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int t;
    cin>>t;

    while(t--){
        ll n,m;
        cin>>n>>m;
        
        m=m%MOD;
        
        ll a[2][2];
        
        a[0][0]=(m-1);
	    a[0][1]=(m-1);
	    a[1][0]=1;
	    a[1][1]=0;
	    
        if(n==1){
            cout<<m%MOD<<endl;
            continue;
        }

        expo(a, n-1);

        //cout<<m<<" "<<p[0][0]<<" "<<p[1][0]<<endl;

        int ans = ((a[0][0] + a[1][0])%M*m)%M;

        cout<<ans<<endl; 
    }
}