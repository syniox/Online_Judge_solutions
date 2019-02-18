#include <iostream>
#include <cstdio>
#include <cstring>
const int N=5e5+5;
int n,q;

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}

inline char get_c(){
	static char *h,*t,buf[1<<16];
	return h==t?(t=(h=buf)+fread(buf,1,1<<16,stdin),h==t?EOF:*h++):*h++;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=get_c())>'9'||c<'0');
	while(x=x*10-48+c,(c=get_c())>='0'&&c<='9');
	return x;
}

namespace G{
	int cnt,fir[N],fa[N];
	int turn_p,rad_a,rad_b,rad_l,len[N],len_p[N];
	int cnd,idx[N],dis[N];
	int ecc;
	bool is_rad[N];
	struct edge{
		int to,wi,nx;
	}eg[N<<1];

	inline void add(const int a,const int b,const int v){
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
	}

	inline void dfs_rad(const int x){
		len_p[x]=x;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==fa[x]) return;
			fa[y]=x;
			dfs_rad(y);
			const int v=len[y]+eg[i].wi;
			if(len[x]+v>rad_l){
				rad_l=len[x]+v;
				turn_p=x;
				rad_a=len_p[x];
				rad_b=len_p[y];
			}
			if(len[y]+eg[i].wi>len[x]){
				len[x]=v;
				len_p[x]=len_p[y];
			}
		}
	}

	inline void dfs_ecc(int x,int fa,int dep){
		apx(ecc,dep);
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y!=fa&&!is_rad[y]) dfs_ecc(y,x,dep+eg[i].wi);
		}
	}

	inline void get_rad(){
		for(int i=rad_a; ; i=fa[i]){
			is_rad[i]=1;
			if(i==turn_p) break;
		}
		for(int i=rad_b; ; i=fa[i]){
			is_rad[i]=1;
			if(i==turn_p) break;
		}
		idx[++cnd]=rad_a;
		for(int lst=0,x=rad_a; x!=rad_b;){
			for(int i=fir[x]; i; i=eg[i].nx){
				const int y=eg[i].to;
				if(y!=lst&&is_rad[y]){
					idx[++cnd]=y;
					dis[cnd]=dis[cnd-1]+eg[i].wi;
					lst=x,x=y;
					break;
				}
			}
		}
	}

	inline int get_ans(){
		int ans=2e9;
		for(int i=1,j=1; i<=cnd; ++i){
			while(dis[i]-dis[j]>q) ++j;
			apn(ans,std::max(ecc,std::max(dis[j],dis[cnd]-dis[i])));
		}
		return ans;
	}
}

int main(){
	n=nxi(),q=nxi();
	for(int i=1; i<n; ++i){
		const int a=nxi(),b=nxi(),v=nxi();
		G::add(a,b,v);
		G::add(b,a,v);
	}
	G::dfs_rad(1);
	G::get_rad();
	for(int i=1; i<=G::cnd; ++i){
		G::dfs_ecc(G::idx[i],0,0);
	}
	printf("%d\n",G::get_ans());
	return 0;
}
