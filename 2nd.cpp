#include<bits/stdc++.h>
using namespace std;
template<class T> ostream& operator<<(ostream &os,vector<T> V){
    os<<"[ ";for(auto v:V)os<<v<<" ";return os<<"]";
}
template<class L,class R> ostream& operator<<(ostream &os,pair<L,R> P){
    return os<<"("<<P.first<<","<<P.second<<")";
}

#define ALL(x) x.begin(),x.end()
#define LL long long int
#define PB push_back
#define EB emplace_back
#define F first
#define S second
#define endl "\n"
#define l() cout << endl;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL);
#define TC int t; cin >> t;while(t--)
#define forn(i,n) for(int i=0;i<n;i++)

const int mod = pow(10,9)+7;
const int inf = 2e9;
const LL linf = 2e18;
const double eps = 1e-9;


////////////////////////////



void solve(){
    LL n,m;
    cin >> n >> m;
    LL arr[n];
    forn(i,n) cin >> arr[i];
    LL sum[51][2];
    LL diff[51];
    LL sure= 0;
    LL ans = 0;
    for(int i =50;i>=0;i--){
        LL cnt = 0;
        sum[i][0] = 0;
        sum[i][1] = 0;
        for(int x :arr){
            if(x&(1LL << i)){
                sum[i][1] +=1;
            }else{
                sum[i][0] +=1;
            }
        }
        diff[i] = abs(sum[i][0] - sum[i][1]);
        sure += (1LL << i) * min(sum[i][0],sum[i][1]);
    }
    LL already= sure;
    
    if(sure > m){
        cout << "-1" << endl;
        return;
    }
    for(int i =50;i>=0;i--){
    
        LL extra = (1LL << i) * diff;
        LL naya  = already + extra;
        if(naya <=m){
            already = naya;
        }else{
            cout << naya << endl;
            return;
        }
    }
    cout << naya << endl;
    return ;
}

int main(){

#ifndef ONLINE_JUDGE
freopen("input.txt", "r", stdin);
freopen("output.txt", "w", stdout);
#endif    
    
    int t;
    cin >> t;
    for(int i=1;i<=t;i++){
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;

}