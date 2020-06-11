#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
#include <fstream>
#include <set>
typedef long long lint;
const int N=3e5+5;
int n,ans,fl[N],pos[N],lg2[N<<1];
char str[N];

namespace utils{
#define eprintf(fmt,...) fprintf(stderr,fmt,##__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=c=='-'&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

void manacher(){
	char *s=new char[N<<1];
	int *pr=new int[N<<1];
	memset(fl,10,sizeof(fl));
	for(int i=1; i<=n; ++i){
		s[i*2-1]=str[i],s[i*2]='#';
	}
	for(int r=0,p=0,i=1; i<n*2; ++i){
		if(i<r) pr[i]=std::min(r-i,pr[p*2-i]);
		for(; i-pr[i]>0&&i+pr[i]<n*2; ++pr[i]){
			if(s[i-pr[i]-1]!=s[i+pr[i]+1]) break;
		}
		if(i+pr[i]>r) p=i,r=i+pr[i];
		apn(fl[(i+pr[i]+1)>>1],((i-pr[i])>>1)+1);
	}
	for(int i=n; i; --i){
		apn(fl[i],fl[i+1]+1);
	}
	delete[] s;
	delete[] pr;
}

namespace SAM{
	int cnt,lst,cnd,dfn[N<<1],idx[N<<1],dep[N<<1];
	int fa[N<<1],sz[N<<1],son[N<<1],top[N<<1];
	int odgr[N<<1],*g[N<<1];
	struct node{
		int lk,len,c[26];
	}tr[N<<1];
	struct _init{
		_init(){tr[0].lk=-1;}
	}_init_;

	int insert(const int c){
		int p=lst,k=lst=++cnt;
		tr[k].len=tr[p].len+1;
		for(; ~p&&!tr[p].c[c]; p=tr[p].lk){
			tr[p].c[c]=k;
		}
		if(p==-1) return k;
		int q=tr[p].c[c];
		if(tr[q].len==tr[p].len+1) tr[k].lk=q;
		else{
			tr[++cnt]=tr[q];
			tr[cnt].len=tr[p].len+1;
			for(; ~p&&tr[p].c[c]==q; p=tr[p].lk){
				tr[p].c[c]=cnt;
			}
			tr[q].lk=tr[k].lk=cnt;
		}
		return k;
	}

	void dfs_son(const int x){
		for(int i=0; i<odgr[x]; ++i){
			const int y=g[x][i];
			dep[y]=dep[x]+1;
			dfs_son(y);
			if(!son[x]||sz[y]>sz[son[x]]) son[x]=y;
			sz[x]+=sz[y];
		}
	}
	void dfs_top(const int x,const int t){
		idx[dfn[x]=++cnd]=x;
		top[x]=t;
		if(son[x]) dfs_top(son[x],top[x]);
		for(int i=0; i<odgr[x]; ++i){
			if(g[x][i]!=son[x]) dfs_top(g[x][i],g[x][i]);
		}
	}
	void build(){
		for(int i=1; i<=cnt; ++i){
			++odgr[fa[i]=tr[i].lk];
		}
		for(int i=0; i<=cnt; ++i){
			if(!odgr[i]) continue;
			g[i]=new int[odgr[i]];
			odgr[i]=0;
		}
		for(int i=1; i<=cnt; ++i){
			int f=tr[i].lk;
			g[f][odgr[f]++]=i;
		}
		dfs_son(0);
		dfs_top(0,0);
	}
	inline int getlca(int x,int y){
		while(top[x]!=top[y]){
			if(dep[top[x]]>dep[top[y]]) x=fa[top[x]];
			else y=fa[top[y]];
		}
		return dep[x]<dep[y]?x:y;
	}
	inline int getcommon(const int p1,const int l1,const int p2,const int l2){
		int lca=getlca(p1,p2);
		return std::min(tr[lca].len,std::min(l1,l2));
	}

	int bsearch(const int p,const int len){
		int l=dfn[top[p]],r=dfn[p],mid;
		while(l!=r){
			mid=(l+r)>>1;
			if(tr[idx[mid]].len>=len) r=mid;
			else l=mid+1;
		}
		return idx[l];
	}
	void getf(int &p,const int len){
		while(~fa[top[p]]&&tr[fa[top[p]]].len>=len)
			p=fa[top[p]];
	}
	int solve(int p,const int len){
		static int dl[N<<1];
		static std::set <int> sd;
		getf(p,len);
		p=bsearch(p,len);
		std::set <int> ::iterator it=sd.lower_bound(dfn[p]);
		int ans=0;
		if(it==sd.end()&&it==sd.begin()){
		}else if(it==sd.end()||it==sd.begin()){
			if(it==sd.end()) --it;
			ans=getcommon(idx[*it],dl[*it],p,len);
		}else{
			int r1=getcommon(idx[*it],dl[*it],p,len);
			--it;
			int r2=getcommon(idx[*it],dl[*it],p,len);
			ans=std::max(r1,r2);
		}
		apx(dl[dfn[p]],len);
		sd.insert(it,dfn[p]);
		return len-std::max(0,ans);
	}
}

int main(){
	n=nxi();
	for(int i=2; i<=n; ++i){
		lg2[i]=lg2[i>>1]+1;
	}
	scanf("%s",str+1);
	manacher();
	for(int i=1; i<=n; ++i){
		pos[i]=SAM::insert(str[i]-'a');
	}
	SAM::build();
	for(int i=1; i<=n; ++i){
		printf("%d\n",ans+=SAM::solve(pos[i],i-fl[i]+1));
	}
	return 0;
}
