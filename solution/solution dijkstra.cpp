#include <bits/stdc++.h>
using namespace std;
#define fast ios_base::sync_with_stdio(false);cin.tie(NULL);
#define int long long
#define pb push_back
#define mp make_pair
#define READS(x); string x;cin >> x;
#define READ(x); int x;cin >> x;
#define DOUREAD(x,y); int x,y;cin >> x >> y;
#define TRIREAD(x,y,z); int x,y,z;cin >> x >> y >> z;
const int MAXN = 2e5+69;
int SEG[4*MAXN],ANZ[MAXN];
void BUILD(int l,int r,int ID){
    SEG[ID] = 1e18;
    if(l == r){
        return;
    }
    int mid = (l+r)>>1;
    BUILD(l,mid,2*ID);
    BUILD(mid+1,r,2*ID+1);
}
void UP(int l,int r,int u,int v,int VAL,int ID){
    if(v < l || r < u) return;
    if(u <= l && r <= v){
        SEG[ID] = min(SEG[ID],VAL);
        return;
    }
    int mid = (l+r)>>1;
    UP(l,mid,u,v,VAL,2*ID);
    UP(mid+1,r,u,v,VAL,2*ID+1);
}
void CAL(int l,int r,int ID){
    if(l == r){
        ANZ[l] = SEG[ID];
        return;
    }
    int mid = (l+r)>>1;
    SEG[2*ID] = min(SEG[2*ID],SEG[ID]);
    SEG[2*ID+1] = min(SEG[2*ID+1],SEG[ID]);
    CAL(l,mid,2*ID);
    CAL(mid+1,r,2*ID+1);
}
int N,M;
struct EDGE{
    int fi,se;
    int NUM;
};
vector<EDGE> ADJ[MAXN];
struct NODE{
    int DIZ;
    int DES;
    bool operator < (const NODE other) const{
        return other.DIZ < DIZ;
    }
};
priority_queue<NODE> Q1,Q2;
int DIS1[MAXN],DIS2[MAXN];
int PATH[MAXN],ID[MAXN],L[MAXN],R[MAXN],MARK[MAXN];
signed main(){fast 
    cin >> N >> M;
    for(int i = 1; i <= M ;i++){
        int U,V,W; cin >> U >> V >> W;
        ADJ[U].pb({V,W,i});
        ADJ[V].pb({U,W,i});
    }
    for(int i = 1;  i<= N ; i++) DIS1[i] = DIS2[i] = 1e18;
    Q1.push({0,1});
    Q2.push({0,N});
    DIS1[1] = DIS2[N] = 0;
    while(!Q1.empty()){
        auto Z = Q1.top();
        Q1.pop();
        int U = Z.DES;
        if(Z.DIZ != DIS1[U]) continue;
        for(auto X : ADJ[U]){
            int V = X.fi,WEI = X.se;
            if(DIS1[V] > DIS1[U] + WEI){
                DIS1[V] = DIS1[U] + WEI;
                Q1.push({DIS1[V],V});
            }
        }
    }
    while(!Q2.empty()){
        auto Z = Q2.top();
        Q2.pop();
        int U = Z.DES;
        if(Z.DIZ != DIS2[U]) continue;
        for(auto X : ADJ[U]){
            int V = X.fi,WEI = X.se;
            if(DIS2[V] > DIS2[U] + WEI){
                DIS2[V] = DIS2[U] + WEI;
                Q2.push({DIS2[V],V});
            }
        }
    }
    int CNT = 0;
    int CUR = 1;
    while(CUR != N){
        CNT++;
        PATH[CNT] = CUR;
        ID[CUR] = CNT;
        for(auto X : ADJ[CUR]){
            int V = X.fi,WEI = X.se;
            if(DIS2[CUR] == DIS2[V] + WEI){
                MARK[X.NUM] = 1;
                CUR = V;
                break;
            }
        }
    }
    CNT++;
    PATH[CNT] = N;
    ID[N] = CNT;
    for(int i = 1; i <= CNT ; i++){
        queue<int> Q;
        int ROOT = PATH[i];
        Q.push(ROOT);
        L[ROOT] = i;
        while(!Q.empty()){
            int U = Q.front();
            Q.pop();
            for(auto X : ADJ[U]){
                int V = X.fi,WEI = X.se;
                if((DIS1[V] == DIS1[U] + WEI) && (!ID[V]) && (L[V] == 0)){
                    L[V] = i;
                    Q.push(V);
                }
            }
        }
    }
    for(int i = CNT; i >= 1 ; i--){
        queue<int> Q;
        int ROOT = PATH[i];
        Q.push(ROOT);
        R[ROOT] = i;
        while(!Q.empty()){
            int U = Q.front();
            Q.pop();
            for(auto X : ADJ[U]){
                int V = X.fi,WEI = X.se;
                if((DIS2[V] == DIS2[U] + WEI) && (!ID[V]) && (R[V] == 0)){
                    R[V] = i;
                    Q.push(V);
                }
            }
        }
    }
    BUILD(1,CNT,1);
    for(int NODE = 1; NODE <= N ; NODE++){
        for(auto X : ADJ[NODE]){
            if(!MARK[X.NUM] && (L[NODE] > 0) && (R[X.fi] > 0) && (L[NODE] < R[X.fi])){
                int VAL = DIS1[NODE] + X.se + DIS2[X.fi];
                UP(1,CNT,L[NODE],R[X.fi]-1,VAL,1);
            }
        }
    }
    CAL(1,CNT,1);
    int MAXI = 0;
    int CUT = 0;
    for(int i = 1; i <= CNT-1 ; i++){
        if(ANZ[i] > MAXI){
            MAXI = ANZ[i];
            CUT = 1;
        }
        else if(MAXI == ANZ[i]) CUT++;
    }
    if(MAXI == DIS1[N]) CUT = M;
    cout << MAXI << " " << CUT << '\n';
}