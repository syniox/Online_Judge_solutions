#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
const int N=3e5+5;
int n;
bool ol;

namespace utils{
	inline int nxi(FILE *fd=stdin){
		int x=0;
		char c;
		while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=fgetc(fd));
		while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
		return f?-x:x;
	}

	template <class T>
		inline void apx(T &x,const T y){
			x<y?x=y:0;
		}

	template <class T>
		inline void apn(T &x,const T y){
			x>y?x=y:0;
		}
}
using namespace utils;

namespace U{
	int fa[N],p1[N],p2[N],len[N];
	struct _Init{
		_Init(){
			for(int i=1; i<N; ++i) p1[i]=p2[i]=i;
		}
	}_init;
	int find_rt(const int x){
		return fa[x]?fa[x]=find_rt(fa[x]):x;
	}
}

namespace T{
	struct node{
		int sz,fa,c[2];
		bool rev;
		inline void getrev(){
			rev^=1;
			std::swap(c[0],c[1]);
		}
	}tr[N];

	inline void upd(const int k){
		tr[k].sz=tr[tr[k].c[0]].sz+tr[tr[k].c[1]].sz+1;
	}

	inline bool isrt(const int k){
		const int f=tr[k].fa;
		return tr[f].c[0]!=k&&tr[f].c[1]!=k;
	}

	inline bool side(const int k){
		return tr[tr[k].fa].c[1]==k;
	}

	inline void psh(const int k){
		if(!tr[k].rev) return;
		if(tr[k].c[0]) tr[tr[k].c[0]].getrev();
		if(tr[k].c[1]) tr[tr[k].c[1]].getrev();
		tr[k].rev=0;
	}

	void rot(const int k){
		assert(!isrt(k));
		const int f=tr[k].fa,ff=tr[f].fa;
		const bool s=side(k);
		int &p=tr[k].c[s^1];
		tr[k].fa=ff;
		if(!isrt(f)) tr[ff].c[side(f)]=k;
		tr[f].fa=k;
		tr[f].c[s]=p;
		if(p) tr[p].fa=f;
		p=f;
		upd(f);
		upd(k);
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

	void acs(int x){
		for(int y=0; x; y=x,x=tr[x].fa){
			splay(x);
			tr[x].c[1]=y;
			upd(x);
		}
	}

	void mkrt(const int x){
		acs(x),splay(x);
		tr[x].getrev();
	}

	int dis(const int x,const int y){
		mkrt(x);
		acs(y),splay(y);
		assert(tr[y].c[1]==0);
		return tr[y].sz-1;
	}
}

void lnk(const int x,const int y){
	const int r1=U::find_rt(x),r2=U::find_rt(y);
	assert(r1!=r2);
	int p1=U::p1[r1],p2=U::p2[r1],l1=U::len[r1];
	int p3=U::p1[r2],p4=U::p2[r2],l2=U::len[r2];
	int tmp,ans1,ans2,len=std::max(l1,l2);
	if(l1>l2){
		ans1=p1,ans2=p2;
	}
	else{
		ans1=p3,ans2=p4;
	}
	U::fa[r1]=r2;
	T::mkrt(x);
	T::tr[x].fa=y;
	if((tmp=T::dis(p1,p3))>len){
		ans1=p1,ans2=p3,len=tmp;
	}
	if((tmp=T::dis(p1,p4))>len){
		ans1=p1,ans2=p4,len=tmp;
	}
	if((tmp=T::dis(p2,p3))>len){
		ans1=p2,ans2=p3,len=tmp;
	}
	if((tmp=T::dis(p2,p4))>len){
		ans1=p2,ans2=p4,len=tmp;
	}
	U::p1[r2]=ans1;
	U::p2[r2]=ans2;
	U::len[r2]=len;
}

int ask(const int x){
	const int r=U::find_rt(x),p1=U::p1[r],p2=U::p2[r];
	int ans=0;
	T::mkrt(x);
	T::acs(p1),T::splay(p1);
	apx(ans,T::tr[p1].sz-1);
	T::acs(p2),T::splay(p2);
	apx(ans,T::tr[p2].sz-1);
	return ans;
}

int main(){
	ol=nxi();
	n=nxi();
	for(int ans=0,q=nxi(); q; --q){
		const int op=nxi();
		if(op==1){
			lnk(nxi()^(ans*ol),nxi()^(ans*ol));
		}
		else{
			printf("%d\n",ans=ask(nxi()^(ans*ol)));
		}
	}
	return 0;
}
