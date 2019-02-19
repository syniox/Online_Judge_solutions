#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=2e5+5;
int n;

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
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
	int cnt,fa[N],fir[N],xpos[N];
	int cnr,turn_p,rad_a,rad_b,idx[N];
	lint rad,xlen[N],dis[N];
	bool is_rad[N];
	struct edge{
		int to,wi,nx;
	}eg[N<<1];

	inline void add(const int a,const int b,const int v){
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
	}

	void dfs_rad(const int x){
		xpos[x]=x;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==fa[x]) continue;
			fa[y]=x;
			dfs_rad(y);
			const lint v=xlen[y]+eg[i].wi;
			if(xlen[x]+v>rad){
				turn_p=x;
				rad_a=xpos[x],rad_b=xpos[y];
				rad=xlen[x]+v;
			}
			if(v>xlen[x]){
				xlen[x]=v;
				xpos[x]=xpos[y];
			}
		}
	}

	lint dfs_ecc(const int x,const int fa){
		lint dep=0;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(!is_rad[y]&&y!=fa){
				apx(dep,dfs_ecc(y,x)+eg[i].wi);
			}
		}
		return dep;
	}

	inline lint solve(){
		for(int i=rad_a; i; i=fa[i]){
			is_rad[i]=1;
			if(i==turn_p) break;
		}
		for(int i=rad_b; i; i=fa[i]){
			is_rad[i]=1;
			if(i==turn_p) break;
		}
		idx[++cnr]=rad_a;
		for(int lst=0,x=rad_a; x!=rad_b; ){
			for(int i=fir[x]; i; i=eg[i].nx){
				const int y=eg[i].to;
				if(is_rad[y]&&y!=lst){
					lst=x;
					idx[++cnr]=x=y;
					dis[cnr]=dis[cnr-1]+eg[i].wi;
					break;
				}
			}
		}
		lint ans=0;
		for(int i=1; i<=cnr; ++i){
			lint a=dis[i];
			lint b=dis[cnr]-dis[i];
			apx(ans,dfs_ecc(idx[i],0)+std::min(a,b));
		}
		return ans+rad;
	}
}

int main(){
	n=nxi(),nxi();
	for(int i=1; i<n; ++i){
		const int a=nxi(),b=nxi(),v=nxi();
		G::add(a,b,v);
		G::add(b,a,v);
	}
	G::dfs_rad(1);
	printf("%lld\n",G::solve());
	return 0;
}
