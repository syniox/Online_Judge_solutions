#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
typedef long long lint;
using namespace std;
const int N=1e5+5;
int n,ms[N];
bool type[N];
//0 用户 1 服务器

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

void apl_v(int &v1,int &v2,int t,bool f){//f: 0取小 1取大
	if((t>v1)==f) swap(v1,t);
	if((t>v2)==f) swap(v2,t);
}
void apl_v(int &b1,int &v1,int &b2,int &v2,int b3,int v3,bool f){
	if((v3>v1)==f) swap(b1,b3),swap(v1,v3);
	if(b3!=b1&&((v3>v2)==f||b2==b1)) swap(b2,b3),swap(v2,v3);
}

namespace G{
	int rt,cnt,fir[N],sz[N],csz,xsz;
	int tgt,rx[N],rn[N],bel[N];
	vector <int> ch[N],ls[N],lsbl[N],lsx[N],lsn[N],lsblx[N],lsbln[N];
	bool vis[N],vld[N];
	struct edge{
		int to,wi,nx;
	}eg[N<<1];

	inline void add(const int a,const int b,const int v){
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
	}
	inline bool cmp_rn(const int x,const int y){
		return rn[x]<rn[y];
	}

	void dfs_rt(const int x,const int f){
		int xs=0;
		sz[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(!vis[y]&&y!=f){
				dfs_rt(y,x);
				apx(xs,sz[y]);
				sz[x]+=sz[y];
			}
		}
		apx(xs,csz-sz[x]);
		if(xs<xsz) xsz=xs,rt=x;
	}
	int qrt(const int x,const int csz){
		G::csz=csz,G::xsz=1e9;
		dfs_rt(x,0);
		return G::rt;
	}

	pair<int,int> dfs_path(const int x,const int f,const int rn,const int rx,const int bl){
		bel[x]=bl,G::rn[x]=rn,G::rx[x]=rx;
		if(!type[x]) ls[rt].push_back(x);
		pair<int,int> ans=type[x]?make_pair(rn,rx):make_pair((int)1e9,0);
		sz[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to,v=eg[i].wi;
			if(y!=f&&!vis[y]){
				pair<int,int> pry=dfs_path(y,x,min(rn,v),max(rx,v),bl);
				apn(ans.first,pry.first);
				apx(ans.second,pry.second);
				sz[x]+=sz[y];
			}
		}
		return ans;
	}

	int build(int x,const int csz){
		static pair<int,int> blr[N];
		x=qrt(x,csz);
		vis[x]=1;
		//get ms
		int n1=1e9,n2=1e9,x1=0,x2=0;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(vis[y]) continue;
			blr[y]=dfs_path(y,x,eg[i].wi,eg[i].wi,y);
			apl_v(n1,n2,blr[y].first,0);
			apl_v(x1,x2,blr[y].second,1);
		}
		for(vector <int> ::iterator it=ls[x].begin(); it!=ls[x].end(); ++it){
			int mn=n1==blr[bel[*it]].first?n2:n1;
			int mx=x1==blr[bel[*it]].second?x2:x1;
			apx(ms[*it],max(mx-rn[*it],rx[*it]-mn));
			if(type[x]==1) apx(ms[*it],rx[*it]-rn[*it]);
		}
		//get ls
		sort(ls[x].begin(),ls[x].end(),cmp_rn);
		const int cuser=ls[x].size();
		lsbl[x].resize(cuser);
		lsn[x].resize(cuser);
		lsx[x].resize(cuser);
		lsbln[x].resize(cuser);
		lsblx[x].resize(cuser);
		for(int i=0; i<cuser; ++i){
			lsbl[x][i]=bel[ls[x][i]];
			lsn[x][i]=rn[ls[x][i]],lsx[x][i]=rx[ls[x][i]];
			lsbln[x][i]=blr[lsbl[x][i]].first;
			lsblx[x][i]=blr[lsbl[x][i]].second;
		}
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(!vis[y]) ch[x].push_back(build(y,sz[y]));
		}
		return x;
	}

	void dfs_vld(const int x){
		int b1=0,v1=-1e9,b2=0,v2=-1e9;
		const int cuser=ls[x].size();
		for(int i=0; i<cuser; ++i){
			int vn=lsbln[x][i]==v1?v2:v1;
			vld[ls[x][i]]&=lsx[x][i]-vn>=tgt;
			if(ms[ls[x][i]]<tgt&&lsx[x][i]-lsn[x][i]<tgt)
				apl_v(b1,v1,b2,v2,lsbl[x][i],lsn[x][i],1);
		}
		b1=0,v1=2e9,b2=0,v2=2e9;
		if(!type[x]) v1=0;
		for(int i=cuser-1; ~i; --i){
			int vx=lsblx[x][i]==v1?v2:v1;
			vld[ls[x][i]]&=max(lsx[x][i],vx)-lsn[x][i]>=tgt;
			if(ms[ls[x][i]]<tgt&&lsx[x][i]-lsn[x][i]<tgt)
				apl_v(b1,v1,b2,v2,lsbl[x][i],lsx[x][i],0);
		}
		vld[x]&=v2>1e9;
		for(vector<int>::iterator it=ch[x].begin(); it!=ch[x].end(); ++it){
			dfs_vld(*it);
		}
	}

	bool qvld(const int tgt){
		G::tgt=tgt;
		memset(vld,1,sizeof(vld));
		dfs_vld(rt);
		for(int i=1; i<=n; ++i){
			if(vld[i]&&!type[i]) return 1;
		}
		return 0;
	}
}

void qans(){
	int l=0,r=1e9,mid;
	while(l!=r){
		mid=(l+r+1)>>1;
		if(G::qvld(mid)) l=mid;
		else r=mid-1;
	}
	G::qvld(l);
	for(int i=1; i<=n; ++i){
		if(G::vld[i]&&!type[i]){
			printf("%d ",i);
			break;
		}
	}
	printf("%d\n",l);
}

int main(){
	n=nxi();
	for(int p0=n,c1=0,i=1; i<=n; ++i){
		type[i]=nxi();
		if(!type[i]) p0=i;
		if((c1+=type[i]==1)==n-1){
			return printf("%d 0\n",p0),0;
		}
	}
	for(int i=1; i<n; ++i){
		const int a=nxi(),b=nxi(),v=nxi();
		G::add(a,b,v),G::add(b,a,v);
	}
	G::rt=G::build(1,n);
	qans();
	return 0;
}
