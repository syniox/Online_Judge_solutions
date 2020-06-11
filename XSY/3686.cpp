#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
#include <set>
typedef long long lint;
const int N=3e5+5;
int n,ans,fl[N],pos[N];
char str[N];

namespace utils{
#define eprintf(fmt,...) fprintf(stderr,fmt,__VA_ARGS__)
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
	static char s[N<<1];
	static int pr[N<<1];
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
}

namespace SAM{
	int cnt,lst,cnd,dfn[N<<1],idx[N<<1],dep[N<<1],fa[N<<1][20];
	std::vector <int> g[N<<1];
	struct node{
		int len,c[26];
	}tr[N<<1];
	struct _init{
		_init(){memset(fa,-1,sizeof(fa));}
	}_init_;

	int insert(const int c){
		int p=lst,k=lst=++cnt;
		tr[k].len=tr[p].len+1;
		for(; ~p&&!tr[p].c[c]; p=fa[p][0]){
			tr[p].c[c]=k;
		}
		if(p==-1){
			fa[k][0]=0; return k;
		}
		int q=tr[p].c[c];
		if(tr[q].len==tr[p].len+1) fa[k][0]=q;
		else{
			tr[++cnt]=tr[q];
			tr[cnt].len=tr[p].len+1;
			fa[cnt][0]=fa[q][0];
			for(; ~p&&tr[p].c[c]==q; p=fa[p][0]){
				tr[p].c[c]=cnt;
			}
			fa[q][0]=fa[k][0]=cnt;
		}
		return k;
	}

	void dfs_fa(const int x){
		idx[dfn[x]=++cnd]=x;
		for(int i=1; ~fa[x][i-1]; ++i){
			fa[x][i]=fa[fa[x][i-1]][i-1];
		}
		for(std::vector <int> ::iterator it=g[x].begin(); it!=g[x].end(); ++it){
			dep[*it]=dep[x]+1;
			dfs_fa(*it);
		}
	}
	void build(){
		for(int i=1; i<=cnt; ++i){
			assert(~fa[i][0]);
			g[fa[i][0]].push_back(i);
		}
		dfs_fa(0);
	}
	int getlca(int x,int y){
		if(dep[x]<dep[y]) std::swap(x,y);
		for(int d=dep[x]-dep[y],i=0; i<20; ++i){
			if(d>>i&1) x=fa[x][i];
		}
		if(x==y) return x;
		for(int i=19; ~i; --i){
			if(fa[x][i]!=fa[y][i])
				x=fa[x][i],y=fa[y][i];
		}
		return fa[x][0];
	}
	void getcommon(const int p1,const int l1,const int p2,const int l2,int &x,int &y){
		int lca=getlca(p1,p2);
		x=std::max(tr[p1].len-l1,tr[p2].len-l2);
		y=tr[lca].len;
	}

	int solve(const int p,const int len){
		static int dl[N];
		static std::set <int> sd;
		std::set <int> ::iterator it=sd.lower_bound(dfn[p]);
		int ans=0;
		if(it==sd.end()&&it==sd.begin()){
		}else if(it==sd.end()||it==sd.begin()){
			if(it==sd.end()) --it;
			int x,y;
			getcommon(idx[*it],dl[*it],p,len,x,y);
			ans=y-x;
		}else{
			int x1,y1,x2,y2;
			getcommon(idx[*it],dl[*it],p,len,x2,y2);
			--it;
			getcommon(idx[*it],dl[*it],p,len,x1,y1);
			if(x1<y2||x2<y1)
				ans=std::max(y1,y2)-std::min(x1,x2);
			else
				ans=std::max(0,y1-x1)+std::max(0,y2-x2);
		}
		dl[dfn[p]]=len;
		sd.insert(it,dfn[p]);
		return len-std::max(0,ans);
	}
}

int main(){
	n=nxi();
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
