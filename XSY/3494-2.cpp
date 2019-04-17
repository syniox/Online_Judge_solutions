#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
const int N=1e5+5;
int n,q,pos[N],ans[N];
char str[N];
struct _qry{
	int x,y,id;
}qry[N];

inline bool cmp_y(const _qry &a,const _qry &b){
	return a.y<b.y;
}

template <class T> inline void apx(T &x,const T y){
	x<y?x=y:0;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace SGT{
	int x,len;//x处为1
	struct node{
		int v1,v2;//v1: constant
	}tr[N<<1];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	void mod_t(const int l,const int r){
		const int k=idx(l,r);
		if(r<=x-len){
			apx(tr[k].v1,len);
			return;
		}
		if(r<=x&&l>x-len){
			apx(tr[k].v2,x-r+1);
			return;
		}
		const int mid=(l+r)>>1;
		mod_t(l,mid);
		if(x>mid) mod_t(mid+1,r);
	}

	int ask_t(const int l,const int r){
		int res=tr[idx(l,r)].v1,tmp=tr[idx(l,r)].v2;
		if(tmp) apx(res,tmp+(r-x));
		if(l==r) return res;
		const int mid=(l+r)>>1;
		if(x>mid) return std::max(res,ask_t(mid+1,r));
		return std::max(res,ask_t(l,mid));
	}

	inline void mod(const int x,const int len){
		assert(len);
		SGT::x=x,SGT::len=len;
		mod_t(1,n);
	}

	inline int ask(const int x){
		SGT::x=x;
		return ask_t(1,n);
	}
}

namespace LCT{
	struct node{
		int fa,pos,len,c[2];
	}tr[N<<1];

	inline bool isrt(const int k){
		return tr[tr[k].fa].c[0]!=k&&tr[tr[k].fa].c[1]!=k;
	}

	inline bool side(const int k){
		return tr[tr[k].fa].c[1]==k;
	}

	inline void psh(const int k){
		if(tr[k].c[0]) tr[tr[k].c[0]].pos=tr[k].pos;
		if(tr[k].c[1]) tr[tr[k].c[1]].pos=tr[k].pos;
	}

	inline void rot(const int k){
		assert(!isrt(k));
		const int f=tr[k].fa,ff=tr[f].fa;
		const bool sid=side(k);
		int &p=tr[k].c[sid^1];
		tr[k].fa=ff;
		if(!isrt(f)) tr[ff].c[side(f)]=k;
		tr[f].fa=k;
		tr[f].c[sid]=p;
		if(p) tr[p].fa=f;
		p=f;
	}

	inline void splay(const int k){
		static int stk[N];
		int top=0;
		for(int x=k; ; x=tr[x].fa){
			stk[++top]=x;
			if(isrt(x)) break;
		}
		for(; top; --top){
			psh(stk[top]);
		}
		while(!isrt(k)){
			const int f=tr[k].fa;
			if(!isrt(f)){
				rot(side(k)==side(f)?f:k);
			}
			rot(k);
		}
	}

	inline void acs(int x,const int pos){
		for(int y=0; x; y=x,x=tr[x].fa){
			splay(x);
			psh(x);
			if(x>1&&tr[x].pos){
				SGT::mod(tr[x].pos,tr[x].len);
			}
			tr[x].c[1]=y;
			tr[x].pos=pos;
		}
	}
}

namespace SAM{
	int lst,cnt;
	struct node{
		int lk,len,c[26];
	}tr[N<<1];

	inline void init(){
		tr[0].lk=-1;
	}

	void insert(const int c){
		int p=lst,k=lst=++cnt;
		tr[k].len=tr[p].len+1;
		for(; ~p&&!tr[p].c[c]; p=tr[p].lk){
			tr[p].c[c]=k;
		}
		if(p==-1) return;
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
	}
}

int main(){
	n=nxi(),q=nxi();
	scanf("%s",str+1);
	SAM::init();
	for(int i=1; i<=n; ++i){
		SAM::insert(str[i]-'a');
		pos[i]=SAM::lst;
	}
	for(int i=0; i<=SAM::cnt; ++i){
		LCT::tr[i+1].len=SAM::tr[i].len;
		LCT::tr[i+1].fa=SAM::tr[i].lk+1;
	}
	for(int i=1; i<=q; ++i){
		qry[i].id=i;
		qry[i].x=nxi(),qry[i].y=nxi();
	}
	std::sort(qry+1,qry+q+1,cmp_y);
	for(int i=1,j=1; i<=n; ++i){
		LCT::acs(pos[i]+1,i);
		for(; j<=q&&qry[j].y==i; ++j){
			ans[qry[j].id]=SGT::ask(qry[j].x);
		}
	}
	for(int i=1; i<=q; ++i){
		printf("%d\n",ans[i]);
	}
	return 0;
}
