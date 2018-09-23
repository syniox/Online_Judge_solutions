// luogu-judger-enable-o2
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
const int N=2e5+2;
int n,ql,qr,hx[N],dp[N];
std::deque <int> dq;

template <class T> inline void apx(T &x,const T y){
    if(x<y) x=y;
}

inline int nxi(){
    int x=0;
    char c;
    while(((c=getchar())>'9'||c<'0')&&c!='-');
    const bool f=(c=='-')&&(c=getchar());
    while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
    return f?-x:x;
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("a.in","r",stdin);
#endif
    n=nxi(),ql=nxi(),qr=nxi(),nxi();
    for(int i=1;i<=n;++i){
        hx[i]=nxi();
    }
    for(int i=ql;i<=n;++i){
        while(!dq.empty()&&dp[dq.front()]<=dp[i-ql]){
            dq.pop_front();
        }
        dq.push_front(i-ql);
        if(i-qr-1>=0){
            if(dq.back()==i-qr-1) dq.pop_back();
        }
        dp[i]=dp[dq.back()]+hx[i];
    }
    int ans=-2e9;
    for(int i=n-qr+1;i<=n;++i){
        apx(ans,dp[i]);
    }
    printf("%d\n",ans);
    return 0;
}
