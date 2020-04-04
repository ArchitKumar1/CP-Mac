#include<bits/stdc++.h>
using namespace std;
template<class T> ostream& operator<<(ostream &os,vector<T> V){
    os<<"[ ";for(auto v:V)os<<v<<" ";return os<<"]";
}
template<class L,class R> ostream& operator<<(ostream &os,pair<L,R> P){
    return os<<"("<<P.first<<","<<P.second<<")";
}

const int mod = pow(10,9)+7;
const int inf = 2e9;
const long long linf = 2e18;
const double eps = 1e-9;

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

template<typename T,typename U>void mmul(T &a,U b){a =((long long int)(a*b)%mod);}
template<typename T,typename U>void madd(T &a,U b){a =((long long int)(a+b)%mod);}
template<typename T>T gcd(T a,T b){if(b == 0) return a;else return gcd(b,a%b);}


////////////////////////////

vector<vector<pair<int,int>>>G;
vector<int> in,out;


bool diff(string s){
    set<char> ss;
    for(char c : s)ss.insert(c);
    return (ss.size() == 6);
}

map<int,char> m1;
int main(){
#ifndef ONLINE_JUDGE
freopen("input.txt", "r", stdin);
freopen("output.txt", "w", stdout);
#endif    
    
    vector<string> all;
    for(int i=0;i<=23;i++){
        for(int j = 0;j<=59;j++){
            for(int k = 0;k<=59;k++){
                string si =to_string(i);
                string sj =to_string(j);
                string sk =to_string(k);
                if(si.size() == 1) si ='0' +si;
                if(sj.size() == 1) sj ='0' +sj;
                if(sk.size() == 1) sk ='0' +sk;
                string time = si+sj+sk;
                if(diff(time)) all.PB(time);
            }
        }
    }
    // for(string c : all){
    //     cout << c << endl;
    // }

    TC{
        string s;
        cin >> s;
        string t = "";
        t = t + s[0] + s[1] + s[3]+s[4] +s[6]+s[7];
        //cout <<t << "s " << endl;
        int pos = lower_bound(all.begin(),all.end(),t)- all.begin();
        //cout << "pos" << pos <<endl;
        if(pos == all.size()){
            pos = 0;
        }
        string temp2 = all[pos];
        string ans = "";
        ans = ans + temp2[0]+ temp2[1] +":"+temp2[2]+ temp2[3]+":" +temp2[4] +temp2[5] ;
        cout <<ans <<endl;

    }
    
    return 0;  
}
