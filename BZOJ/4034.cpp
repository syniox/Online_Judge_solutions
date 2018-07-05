#include<iostream>
#include<cstdio>
#include<cstring>
#include<cassert>
using namespace std;
typedef long long lint;
const int N=1e5+5;
int n,m,cnt,hx[N],fir[N];
int sz[N],fa[N],dfn[N],nfd[N],son[N],top[N];
struct edge{
    int to,nx;
}eg[N<<1];
struct node{
    int l,r;
    lint s,f;
}tr[N*3];
 
inline void add(int a,int b){
    eg[++cnt]=(edge){b,fir[a]};
    fir[a]=cnt;
}
 
inline void upd(int k){
    tr[k].s=tr[k<<1].s+tr[k<<1|1].s;
}
 
inline int nxi(){
    int x=0;
    char c;
    while((c=getchar())>'9'||c<'0');
    while(x=x*10+c-48,(c=getchar())>='0'&&c<='9');
    return x;
}
 
void dfs1(int x){
    sz[x]=1;
    for(int i=fir[x];i;i=eg[i].nx){
        int y=eg[i].to;
        if(!sz[y]){
            fa[y]=x;
            dfs1(y);
            sz[x]+=sz[y];
            if(sz[son[x]]<sz[y]) son[x]=y;
        }
    }
}
 
void dfs2(int x){
    dfn[x]=++cnt;
    nfd[cnt]=x;
    top[x]=son[fa[x]]==x?top[fa[x]]:x;
    if(son[x]) dfs2(son[x]);
    for(int i=fir[x];i;i=eg[i].nx){
        int y=eg[i].to;
        if(!dfn[y]) dfs2(y);
    }
}
 
inline void p_ad(int k,lint f){
    tr[k].f+=f;
    tr[k].s+=f*(tr[k].r-tr[k].l+1);
}
 
inline void psh(int k){
    lint &f=tr[k].f;
    if(f&&tr[k].l!=tr[k].r){
        p_ad(k<<1,f);
        p_ad(k<<1|1,f);
        f=0;
    }
}
 
void build(int k,int x,int y){
    tr[k]=(node){x,y,0,0};
    if(x==y){
        tr[k].s=hx[nfd[x]];
        return;
    }
    int mid=(x+y)>>1;
    build(k<<1,x,mid);
    build(k<<1|1,mid+1,y);
    upd(k);
}
 
void mod(int k,int x,int y,int v){
    psh(k);
    int l=tr[k].l,r=tr[k].r,mid=(l+r)>>1;
    if(l>=x&&r<=y){
        tr[k].s+=(lint)(r-l+1)*(lint)v;
        tr[k].f+=v;
        return;
    }
    if(x<=mid) mod(k<<1,x,y,v);
    if(y>mid) mod(k<<1|1,x,y,v);
    upd(k);
}
 
lint ask(int k,int x,int y){
    psh(k);
    int l=tr[k].l,r=tr[k].r,mid=(l+r)>>1;;
    if(l>=x&&r<=y) return tr[k].s;
    if(y<=mid) return ask(k<<1,x,y);
    if(x>mid) return ask(k<<1|1,x,y);
    return ask(k<<1,x,y)+ask(k<<1|1,x,y);
}
 
inline lint ask_t(int x){
    lint ans(0);
    while(x){
        ans+=ask(1,dfn[top[x]],dfn[x]);
        x=fa[top[x]];
    }
    return ans;
}
 
int main(){
    n=nxi(),m=nxi();
    for(int i=1;i<=n;++i) scanf("%d",hx+i);//!!
    for(int a,b,i=1;i<n;++i){
        a=nxi(),b=nxi();
        add(a,b);
        add(b,a);
    }
    cnt=0;
    dfs1(1);
    dfs2(1);
    build(1,1,n);
    for(int a,b;m--;){
        a=nxi(),b=nxi();
        switch(a){
            case 1:
                scanf("%d",&a);
                mod(1,dfn[b],dfn[b],a);
                break;
            case 2:
                scanf("%d",&a);
                mod(1,dfn[b],dfn[b]+sz[b]-1,a);
                break;
            case 3:
                printf("%lld\n",ask_t(b));
        }
    }
    return 0;
}
