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



const int N  = 123456;
const int P = 12;
int tree[4*N][P];
int lazy[4*N][P];
int arr[N];


LL add(int a,int b){
    LL res = (a+b)%mod;
    return res;
}
LL pow(LL a,LL b,LL m){
    LL res = 1;
    while(b){
        if(b&1) res = (res*a)%mod;
        a = (a*a)%mod;
        b>>=1;
    }
    return res;
}

void build(int s,int e,int index,int p){
    if(s == e){
        tree[index][p] =pow(arr[s],p,mod);
        return ;
    }
    int mid = (s+e) >> 1;
    build(s,mid,2*index,p);
    build(mid+1,e,2*index+1,p);
    tree[index][p] = add(tree[2*index][p] , tree[2*index+1][p]);
}

void relax(int s,int e,int index,int p){
    if(lazy[index] != 0){
        tree[index][p] += (e -s  +1) * lazy[index][p];
        if(s!=e){
            lazy[2*index][p] += lazy[index][p];
            lazy[2*index  + 1][p] += lazy[index][p];
        }
        lazy[index][p] = 0;
    }
}
void updaterange(int s,int e,int index,int ss,int ee,int val,int p){
    relax(s,e,index,p);
    if( s > ee || e < ss) return ;
    if(s >= ss && e <=ee ) {
        
        tree[index][p] += (e -s + 1)* val;
        if(s!=e){
            lazy[2*index][p] += val;
            lazy[2*index+1][p] += val;
        }
        return;
    }
    int mid = (s +e ) >> 1;
    updaterange(s,mid,2*index,ss,ee,val,p);
    updaterange(mid+1,e,2*index+1,ss,ee,val,p);
    tree[index][p] = add(tree[2*index][p] , tree[2*index+1][p]);
}

int queryrange(int s,int e,int index,int ss,int ee,int p){
    if(s > ee || e < ss)  return 0;
    relax(s,e,index,p);
    if(s >=ss && e <= ee) {
        return tree[index][p];
    }
    int mid = (s+e) >> 1;
    int l = queryrange(s,mid,2*index,ss,ee,p);
    int r = queryrange(mid+1,e,2*index+1,ss,ee,p);
    return add(l,r);
}
            

int main(){
#ifndef ONLINE_JUDGE
freopen("input.txt", "r", stdin);
freopen("output.txt", "w", stdout);
#endif    
    cout.precision(10);
    TC{
        int n;
        cin >> n;
        forn(i,n){
            cin >> arr[i];
        }
        int s= 0;
        int e = n-1;
        int index=  1;
        forn(i,P){
            build(s,e,index,i);
        }
        int q;
        cin >> q;
        forn(i,q){
            int x;
            cin >> x;
            // forn(z,4*n){
            //     cout << tree[z][3] << " ";
            // }
            cout << endl;
            if(x == 1){
                int pos,k;
                cin >> pos >> k;
                --pos;
                forn(j,P) updaterange(s,e,index,pos,pos,k,j);
            }else if(x == 2){
                int l,r,k;
                cin >> l >> r >> k;
                --l;--r;
                forn(j,P) updaterange(s,e,index,l,r,k,j);
            }else{
                int l,r,p;
                cin >> l >> r >> p;
                --l;--r;
                cout << queryrange(s,e,index,l,r,p) << endl;
            }
            // forn(z,4*n){
            //     cout << tree[i][3] << " ";
            // }
            
        }
    }
    

    return 0;  
}

