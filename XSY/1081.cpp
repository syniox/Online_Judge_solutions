#include<iostream>
#include<cstdio>
#include<cstring>
#include<cassert>
const int N=514;
int n,m,u[N],lj[N],dep[N<<1],fir[N<<1],cur[N<<1],wj[2][N];
struct edge{
	int to,wi,nx;
}eg[N*N];

inline void apx(int &x,const int y){
	if(x<y) x=y;
}

inline char get_c(){
	static char buf[20000],*h,*t;
	if(h==t){
		t=(h=buf)+fread(buf,1,20000,stdin);
	}
	return h==t?EOF:*h++;
}

inline int nxi(){
	int x=0,f=1;
	char c;
	while((c=get_c())>'9'||c<'0') if(c=='-') f=-1;
	while(x=x*10-48+c,(c=get_c())>='0'&&c<='9');
	return x*f;
}

inline void add(const int a,const int b,const int v){
	static int cnt=1;
//	printf("add: %d %d %d\n",a,b,v);
	eg[++cnt]=(edge){b,v,fir[a]};
	fir[a]=cnt;
	eg[++cnt]=(edge){a,0,fir[b]};
	fir[b]=cnt;
}

inline int cbit(int x){
	x=(x&0x55555555)+((x&0xaaaaaaaa)>>1);
	x=(x&0x33333333)+((x&0xcccccccc)>>2);
	x=(x&0x0f0f0f0f)+((x&0xf0f0f0f0)>>4);
	x=(x&0x00ff00ff)+((x&0x00ff00ff)>>8);
	x=(x&0x0000ffff)+((x&0xffff0000)>>16);
	return x;
}

inline void build_side(const int i,const int l,const int r,const bool f){
	if(l>r) return;
	const bool fx=cbit(i)&1;
	int id,tp=-1;
	for(int j=l;j<=r;++j){
		const int p=nxi()+1024;
		if(tp<p) id=j,tp=p;
	}
	if(fx^f){
//		printf("0 %d: id%d %d\n",i,id,tp);
		wj[0][i]=id;
		add((N-1)<<1,i,tp);
	}
	else{
//		printf("1 %d: id%d %d\n",i,id,tp);
		wj[1][i]=id;
		add(i+N,(N<<1)-1,tp);
	}
}

inline bool dinic_bfs(){
	static int que[N<<1];
	int hd=0,tl=1;
	memset(dep,0,sizeof(dep));
	dep[(N-1)<<1]=1;
	que[0]=(N-1)<<1;
	while(hd!=tl){
		const int x=que[hd++];
		for(int i=cur[x]=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(!dep[y]&&eg[i].wi){
				dep[y]=dep[x]+1;
				que[tl++]=y;
			}
		}
	}
	return dep[(N<<1)-1];
}

int dinic_dfs(const int x,const int t){
	if(x==(N<<1)-1) return t;
	int tt=t,tp;
	for(int &i=cur[x];i;i=eg[i].nx){
		const int y=eg[i].to,v=eg[i].wi;
		if(dep[y]==dep[x]+1&&v&&(tp=dinic_dfs(y,std::min(v,tt)))){
			eg[i].wi-=tp;
			eg[i^1].wi+=tp;
			tt-=tp;
			if(!tt) break;
		}
	}
	return t-tt;
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("a.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	n=1<<n,m=1<<m;
	for(int i=0;i<n;++i) lj[i]=nxi();
	for(int i=0;i<n;++i) u[i]=nxi();
	for(int i=0;i<n;++i){
		add(i,i+N,1e8);
		build_side(i,0,lj[i]-1,0);
		build_side(i,lj[i],m-1,1);
		const bool ibit=cbit(i)&1;
		for(int j=0;j<i;++j){
			if(cbit(i^j)==1){
//				printf("make %d %d\n",i,j);
				if(ibit) add(i,j+N,u[i]^u[j]);
				else add(j,i+N,u[i]^u[j]);
			}
		}
	}
	int ans=0;
	while(dinic_bfs()){
		ans+=dinic_dfs((N-1)<<1,1e8);
	}
/*	for(int i=0;i<n;++i){
		printf("%d %d\n",wj[0][i],wj[1][i]);
	}*/
	for(int i=0;i<n;++i){
		printf("%d ",wj[dep[i]==0][i]);
	}
	puts("");

	return 0;
}
