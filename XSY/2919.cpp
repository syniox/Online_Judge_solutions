#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
typedef long long lint;
const int N=205;
int n,cnt,cnp,hx[N],cs[N],fr[N],pre[N],num[N],que[N],fir[N],prm[6000];
bool blk[N],vis[N],npr[40000],map[N][N];
lint dis[N];
struct edge{
    int to,wi,nx;
    lint cs;
}eg[50000];
 
template<class T1,class T2> inline void apn(T1 &a,T2 b){
    if(a>b) a=b;
}
 
inline int nxi(){
    int x=0;
    char c;
    while((c=getchar())>'9'||c<'0');
    while(x=x*10+c-48,(c=getchar())>='0'&&c<='9');
    return x;
}
 
inline void add(int a,int b,int v,lint c){
    eg[++cnt]=(edge){b,v,fir[a],c};
    fir[a]=cnt;
    eg[++cnt]=(edge){a,0,fir[b],-c};
    fir[b]=cnt;
}
 
inline void get_prm(){
    int top=sqrt(1e9);
    for(int i=2;i<=top;++i){
        if(!npr[i]) prm[++cnp]=i;
        for(int j=1;j<=cnp&&i*prm[j]<=top;++j){
            npr[i*prm[j]]=1;
            if(i%prm[j]==0) break;
        }
    }
}
 
inline bool jdg(int x,int y){
    x=hx[x],y=hx[y];
    if(x==0||y==0||x%y) return 0;
    int p=x/y,q=sqrt(p)+1;
    for(int i=1;prm[i]<=q&&prm[i]!=p;++i){
        if(p%prm[i]==0) return 0;
    }
    return 1;
}
 
void get_blk(int t){
    int hd=0,tl=1;
    que[0]=t;
    blk[t]=1;
    vis[t]=1;
    while(hd!=tl){
        int x=que[hd++];
        for(int i=1;i<=n;++i){
            if(map[x][i]&&!vis[i]){
                vis[i]=1;
                blk[i]=blk[x]^1;
                que[tl++]=i;
            }
        }
    }
}
 
void build(){
    for(int i=1;i<=n;++i){
        if(blk[i]) add(0,i,num[i],0);
        else add(i,N-1,num[i],0);
        for(int j=1;j<=n;++j){
            if(map[i][j]&&blk[i]) add(i,j,3e7,(lint)cs[i]*cs[j]);
        }
    }
}
 
bool spfa(){
    memset(dis,-4,sizeof(dis));
    int hd=0,tl=1;
    que[0]=0;
    dis[0]=0;
    while(hd!=tl){
        int x=que[hd];
        if(++hd==N) hd=0;
        vis[x]=0;
        for(int i=fir[x];i;i=eg[i].nx){
            int y=eg[i].to;
            lint c=dis[x]+eg[i].cs;
            if(eg[i].wi&&dis[y]<c){
                dis[y]=c;
                pre[y]=i;
                fr[y]=x;
                if(!vis[y]){
                    vis[y]=1;
                    if(c>dis[que[hd]]){
                        if(--hd==-1) hd=N-1;
                        que[hd]=y;
                    }else{
                        que[tl]=y;
                        if(++tl==N) tl=0;
                    }
                }
            }
        }
    }
    return dis[N-1]>-1e10;
}
 
int main(){
    get_prm();
    cnt=1;
    n=nxi();
    for(int i=1;i<=n;++i){
        hx[i]=nxi();
    }
    for(int i=1;i<=n;++i){
        num[i]=nxi();
    }
    for(int i=1;i<=n;++i){
        scanf("%d",cs+i);
    }
    for(int i=1;i<n;++i){
        for(int j=i+1;j<=n;++j){
            if(jdg(i,j)||jdg(j,i)) map[i][j]=map[j][i]=1;
        }
    }
    for(int i=1;i<=n;++i){
        if(!vis[i]) get_blk(i);
    }
    build();
    memset(vis,0,sizeof(vis));
    lint ans(0),tot(0);
    while(spfa()){
        lint lt=1e12,w=dis[N-1];
        int x=N-1;
        for(;x;x=fr[x]) apn(lt,eg[pre[x]].wi);
        if(w<0) apn(lt,tot/(-w));
 
        x=N-1;
        for(;x;x=fr[x]){
            eg[pre[x]].wi-=lt;
            eg[pre[x]^1].wi+=lt;
        }
        tot+=w*lt;
        ans+=lt;
        if(tot<-w) break;
    }
    printf("%lld\n",ans);
    return 0;
}
