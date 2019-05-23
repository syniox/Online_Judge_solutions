#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
const int N=1e5+5;
int n,m,pos[N],ans[N];
char str[N];
struct data{
	int id,x;
};
std::vector <data> qbuk[N];

namespace utils{
	template <class T> inline void apx(T &x,const T y){
		x<y?x=y:0;
	}
	template <class T> inline void apn(T &x,const T y){
		x>y?x=y:0;
	}
	inline int nxi(FILE *fd=stdin){
		int x=0;
		char c;
		while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=fgetc(fd));
		while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

namespace B{
	int tr[N];
	inline void apl(int x,const int v){
		if(tr[x]>=v) return;
		for(; x<=n&&tr[x]<v; x+=x&-x) tr[x]=v;
	}
	inline int ask(int x){
		int ans=0;
		for(; x; x-=x&-x) apx(ans,tr[x]);
		return ans;
	}
}

namespace S{
	int cnt,lst;
	struct node{
		int lk,len,c[2];
	}tr[N<<1];
	struct _Init{
		_Init(){tr[0].lk=-1;}
	}_init;

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
			tr[k].lk=tr[q].lk=cnt;
		}
		return k;
	}
}

namespace T{
	struct node{
		int v,fa,c[2];
	}tr[N<<1];

	inline bool isrt(const int k){
		return tr[tr[k].fa].c[0]!=k&&tr[tr[k].fa].c[1]!=k;
	}

	inline bool side(const int k){
		return tr[tr[k].fa].c[1]==k;
	}

	inline void psh(const int x){
		if(tr[x].c[0]) tr[tr[x].c[0]].v=tr[x].v;
		if(tr[x].c[1]) tr[tr[x].c[1]].v=tr[x].v;
	}

	inline void build(){
		for(int i=1; i<=S::cnt; ++i){
			tr[i].fa=S::tr[i].lk;
		}
	}

	void rot(const int k){
		assert(!isrt(k));
		const int f=tr[k].fa,s=side(k);
		int &p=tr[k].c[s^1];
		tr[k].fa=tr[f].fa;
		if(!isrt(f)) tr[tr[f].fa].c[side(f)]=k;
		tr[f].fa=k;
		tr[f].c[s]=p;
		tr[p].fa=f;
		p=f;
	}

	void splay(const int x){
		static int stk[N];
		int top=0;
		for(int i=x; ; i=tr[i].fa){
			stk[++top]=i;
			if(isrt(i)) break;
		}
		for(; top; --top){
			psh(stk[top]);
		}
		while(!isrt(x)){
			const int f=tr[x].fa;
			if(!isrt(f)){
				rot(side(f)==side(x)?f:x);
			}
			rot(x);
		}
	}

	void acs(int x){
		for(int y=0; x; y=x,x=tr[x].fa){
			splay(x);
			if(tr[x].v){
				B::apl(n-tr[x].v+1,S::tr[x].len);
			}
			tr[x].c[1]=y;
		}
	}
}

int main(){
	n=nxi(),m=nxi();
	scanf("%s",str+1);
	for(int i=1; i<=n; ++i){
		pos[i]=S::insert(str[i]-'0');
	}
	T::build();
	for(int i=1; i<=m; ++i){
		int x=nxi(),y=nxi();
		qbuk[y].push_back((data){i,x});
	}
	for(int i=1; i<=n; ++i){
		T::acs(pos[i]);
		T::splay(pos[i]);
		T::tr[pos[i]].v=i;
		for(std::vector <data> ::iterator it=qbuk[i].begin(); it!=qbuk[i].end(); ++it){
			ans[it->id]=B::ask(n-(it->x)+1);
		}
	}
	for(int i=1; i<=m; ++i){
		printf("%d\n",ans[i]);
	}
	return 0;
}
