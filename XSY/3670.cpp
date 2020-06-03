#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=2e5+5;
const int mod=1e9+7;
int n,tot,ans,nd[N];//tot: 相同字串对 ans: 最终答案
char str[N];

namespace utils{
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

namespace LCT{
	struct node{
		int fa,c[2],len,slen,cnt,sum,tag;
	}tr[N<<1];

	inline bool isrt(const int x){
		return tr[tr[x].fa].c[0]!=x&&tr[tr[x].fa].c[1]!=x;
	}
	inline bool side(const int x){
		return tr[tr[x].fa].c[1]==x;
	}
	inline void upd(const int k){
		node *ls=tr+tr[k].c[0],*rs=tr+tr[k].c[1];
		tr[k].slen=tr[k].len+ls->slen+rs->slen;
		tr[k].sum=((lint)tr[k].cnt*tr[k].len+ls->sum+rs->sum)%mod;
	}
	inline void getpsh(const int k,const int v){
		tr[k].cnt+=v,tr[k].tag+=v;
		tr[k].sum=(tr[k].sum+(lint)tr[k].slen*v)%mod;
	}
	inline void psh(const int k){
		int &t=tr[k].tag;
		if(tr[k].c[0]) getpsh(tr[k].c[0],t);
		if(tr[k].c[1]) getpsh(tr[k].c[1],t);
		t=0;
	}

	inline void rot(const int x){
		const int f=tr[x].fa,ff=tr[f].fa,sd=side(x);
		int &p=tr[x].c[sd^1];
		tr[x].fa=ff;
		if(!isrt(f)) tr[ff].c[side(f)]=x;
		tr[f].fa=x;
		tr[f].c[sd]=p;
		if(p) tr[p].fa=f;
		p=f;
		upd(f);
		upd(x);
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
				rot(side(x)==side(f)?f:x);
			}
			rot(x);
		}
	}

	void access(int x){
		int y=0;
		for(; x; y=x,x=tr[x].fa){
			splay(x);
			tr[x].c[1]=y;
			if(y) assert(tr[y].fa==x);
			upd(x);
		}
	}

	void link_to(const int x,const int y){
		access(x),splay(x);
		tr[x].fa=y;
	}
}

namespace SAM{
	int lst,cnt;
	struct node{
		int lk,len,c[26];
	}tr[N<<1];
	struct _init{
		_init(){tr[0].lk=-1;}
	}_init_;

	int insert(int c){
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

void build_lct(){
	for(int i=1; i<=SAM::cnt; ++i){
		int f=SAM::tr[i].lk,l=SAM::tr[i].len-SAM::tr[f].len;
		LCT::tr[i].len=LCT::tr[i].slen=l;
		LCT::link_to(i,f);
	}
}

int main(){
	n=nxi();
	scanf("%s",str+1);
	for(int i=1; i<=n; ++i){
		nd[i]=SAM::insert(str[i]-'a');
	}
	build_lct();
	for(int i=1; i<=n; ++i){
		LCT::access(nd[i]);
		LCT::splay(nd[i]);
		tot=(tot+LCT::tr[nd[i]].sum)%mod;
		ans=((lint)ans+tot)%mod;
		LCT::getpsh(nd[i],1);
		printf("%d\n",ans);
	}
	return 0;
}
