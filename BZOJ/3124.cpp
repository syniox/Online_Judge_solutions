#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=2e5+5;
int n;

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
	int cnt,fir[N];
	int mid1,mid2,rad_a,rad_b;
	lint rad;
	bool type;
	struct edge{
		int to,wi,nx;
	}eg[N<<1];

	inline void add(const int a,const int b,const int v){
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
	}
}

namespace D{
	using namespace G;
	int dis_fa[N],fa[N],pos[N];
	lint dep[N],len[N];

	inline void dfs_len(const int x){
		pos[x]=x;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==fa[x]) continue;
			dep[y]=dep[x]+eg[i].wi;
			fa[y]=x;
			dis_fa[y]=eg[i].wi;
			dfs_len(y);
			const lint v=len[y]+eg[i].wi;
			if(len[x]+v>rad){
				rad=len[x]+v;
				rad_a=pos[x],rad_b=pos[y];
			}
			if(v>len[x]){
				len[x]=v;
				pos[x]=pos[y];
			}
		}
	}

	inline void get_mid(){
		mid1=dep[rad_a]>dep[rad_b]?rad_a:rad_b;
		lint sum=0;
		for(; sum<<1<rad; mid2=mid1,mid1=fa[mid1]){
			sum+=dis_fa[mid1];
		}
		if(sum<<1==rad){
			type=1,mid2=mid1;
		}
	}
}

namespace S{
	using namespace G;
	int ind[N],pt[N];
	lint xlen[N];

	inline void dfs_len(const int x,const int fa){
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==fa||y==mid1||y==mid2) continue;
			dfs_len(y,x);
			const lint v=xlen[y]+eg[i].wi;
			if(xlen[x]<v){
				xlen[x]=v,ind[x]=0;
			}
			if(xlen[x]==v){
				pt[x]=y,++ind[x];
			}
		}
	}

	inline int extend(int x){
		int ans=0;
		for(; ind[x]==1; x=pt[x]) ++ans;
		return ans;
	}

	inline int sol1(){
		int ans=0;
		dfs_len(mid1,0);
		if(ind[mid1]>2) return 0;
		for(int i=fir[mid1]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(xlen[y]+eg[i].wi==xlen[mid1]){
				ans+=extend(y)+1;
			}
		}
		return ans;
	}

	inline int sol2(){
		dfs_len(mid1,0);
		dfs_len(mid2,0);
		return extend(mid1)+extend(mid2)+1;
	}
}

int main(){
	n=nxi();
	for(int i=1; i<n; ++i){
		const int a=nxi(),b=nxi(),v=nxi();
		G::add(a,b,v);
		G::add(b,a,v);
	}
	D::dfs_len(1);
	printf("%lld\n",G::rad);
	D::get_mid();
	printf("%d\n",G::type?S::sol1():S::sol2());
	return 0;
}
