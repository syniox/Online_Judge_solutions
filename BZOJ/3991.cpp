#include<iostream>
#include<cstdio>
#include<cstring>
#include<set>
using namespace std;
typedef long long lint;
const int N=1e5+5;
int n,m,cnt,fir[N],dfn[N],nfd[N],dep[N],fa[N][18];
lint ans,dis[N][18];
bool vis[N];
set<int> st;
struct edge{
    int to,wi,nx;
}eg[N<<1];
 
inline void add(int a,int b,int v){
    eg[++cnt]=(edge){b,v,fir[a]};
    fir[a]=cnt;
}
 
inline int nxi(){
    int x=0;
    char c;
    while((c=getchar())>'9'||c<'0');
    while(x=x*10+c-48,(c=getchar())>='0'&&c<='9');
    return x;
}
 
void init(int x){
    dfn[x]=++cnt;
    nfd[cnt]=x;
    for(int i=1;fa[x][i-1];++i){
        fa[x][i]=fa[fa[x][i-1]][i-1];
        dis[x][i]=dis[x][i-1]+dis[fa[x][i-1]][i-1];
    }
    for(int i=fir[x];i;i=eg[i].nx){
        int y=eg[i].to;
        if(!dfn[y]){
            dep[y]=dep[x]+1;
            fa[y][0]=x;
            dis[y][0]=eg[i].wi;
            init(y);
        }
    }
}
 
inline lint lca(int x,int y){
    if(dep[x]>dep[y]) swap(x,y);
    int tp=dep[y]-dep[x];
    lint t=0;
    for(int i=0;i<18;++i){
        if((1<<i)&tp) t+=dis[y][i],y=fa[y][i];
    }
    if(x==y) return t;
    for(int i=17;~i;--i){
        if(fa[x][i]!=fa[y][i]){
            t+=dis[x][i]+dis[y][i];
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return t+dis[x][0]+dis[y][0];
}
 
int g_p(int x){
    return x<=*st.begin()?*(--st.end()):*(--st.lower_bound(x));
}
 
int g_n(int x){
    return x>=*(--st.end())?*st.begin():*st.upper_bound(x);
}
 
inline void ins(int x){
    vis[x]=1;
    st.insert(dfn[x]);
    int l=nfd[g_p(dfn[x])],r=nfd[g_n(dfn[x])];
    ans+=lca(x,l)+lca(x,r)-lca(l,r);
}
 
inline void del(int x){
    vis[x]=0;
    st.erase(dfn[x]);
    int l=nfd[g_p(dfn[x])],r=nfd[g_n(dfn[x])];
    ans+=lca(l,r)-lca(l,x)-lca(x,r);
}
 
int main(){
#ifndef ONLINE_JUDGE
    freopen("a.in","r",stdin);
#endif
    n=nxi(),m=nxi();
    for(int a,b,c,i=1;i<n;++i){
        a=nxi(),b=nxi(),c=nxi();
        add(a,b,c);
        add(b,a,c);
    }
    cnt=0;
    init(1);
    for(int x,i=1;i<=m;++i){
        x=nxi();
        if(!vis[x]) ins(x);
        else del(x);
        printf("%lld\n",ans);
    }
    return 0;
}
