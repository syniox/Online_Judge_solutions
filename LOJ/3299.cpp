#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=2e6+5;
int n,type[N],dgr[N],val[N],nxtf[N];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	static char cbuf[20000],*ct=cbuf;
	inline void putc(char c){
		*ct++=c;
		if(ct==cbuf+20000){
			fwrite(cbuf,1,ct-cbuf,stdout);
			ct=cbuf;
		}
	}
	struct _end{
		~_end(){ fwrite(cbuf,1,ct-cbuf,stdout); }
	}_end_;
	inline char getc(){
		static char buf[20000],*h,*t;
		if(h==t){
			t=(h=buf)+fread(buf,1,20000,stdin);
			if(h==t) return EOF;
		}
		return *h++;
	}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getc())>'9'||c<'0')&&c!='-');
		const bool f=c=='-'&&(c=getc());
		while(x=x*10-48+c,(c=getc())>='0'&&c<='9');
		return f?-x:x;
	}
	void puti(int x){
		static char buf[20];
		if(x==0) putc('0');
		char *c=buf;
		for(; x; x/=10) *c++=x%10+48;
		while(c!=buf) putc(*--c);
	}
}
using namespace utils;

namespace D{
	int cnt,v[N];
	inline void insert(const int x){
		v[++cnt]=x;
	}
	inline void build(){
		std::sort(v+1,v+cnt+1);
		cnt=std::unique(v+1,v+cnt+1)-v-1;
	}
	inline int ask(const int x){
		return std::lower_bound(v+1,v+cnt+1,x)-v;
	}
}

//最后一个冰<=火的位置
namespace T{
	int n,tr[2][N],res,ans,cf[2][N];
	inline void init(const int len){n=len;}
	inline void add(const int p,int x,const int v){
		for(; x<=n; x+=x&-x) tr[p][x]+=v;
	}
	inline void add(const int l,const int r,const int p,const int v){
		add(p,l,v),add(p,r+1,-v);
		cf[p][l]+=v,cf[p][r+1]-=v;
	}
	inline int qry(const int p,int x){
		int ans=0;
		for(; x; x-=x&-x) ans+=tr[p][x];
		return ans;
	}
	inline void ask(){
		res=ans=0;
		int cntf=0,cnti=0;
		for(int i=20; ~i; --i){
			int p=res+(1<<i);
			if(p<=n&&cnti+tr[0][p]<=cntf+tr[1][p]){
				res=p;
				cnti+=tr[0][p],cntf+=tr[1][p];
			}
		}
		ans=std::min(cnti,cntf);
		if(res==n) return;
		cnti+=cf[0][res+1],cntf+=cf[1][res+1];
		int tmp=std::min(cnti,cntf);
		if(tmp<ans) return;
		ans=tmp,res=cntf=0;
		for(int i=20; ~i; --i){
			int p=res+(1<<i);
			if(p<=n&&cntf+tr[1][p]>=ans)
				cntf+=tr[1][p],res=p;
		}
	}
}

//#include <ctime>
int main(){
	//freopen("d.in","r",stdin);//!!!!!
	//clock_t beg=clock();
	n=nxi();
	for(int i=1; i<=n; ++i){
		if(nxi()==1){
			type[i]=nxi(),dgr[i]=nxi(),val[i]=nxi();
			D::insert(dgr[i]);
		}else{
			type[i]=2,val[i]=nxi();
		}
	}
	D::build();
	for(int i=1; i<=n; ++i){
		if(type[i]==2) continue;
		dgr[i]=D::ask(dgr[i]);
	}
	T::init(D::cnt);
	for(int i=1; i<=n; ++i){
		int p=type[i]==2?val[i]:i,t=type[p],v=p==i?val[p]:-val[p];
		if(t==0) 
			T::add(dgr[p],D::cnt,t,v);
		if(t==1)
			T::add(1,dgr[p],t,v);
		T::ask();
		/*
		if(T::ans==0) puts("Peace");
		else printf("%d %d\n",D::v[T::res],T::ans*2);
		*/
		if(T::ans==0) putc('P'),putc('e'),putc('a'),putc('c'),putc('e'),putc('\n');
		else puti(D::v[T::res]),putc(' '),puti(T::ans*2),putc('\n');
	}
	//eprintf("%.3lf\n",(double)(clock()-beg)/CLOCKS_PER_SEC);
	return 0;
}
