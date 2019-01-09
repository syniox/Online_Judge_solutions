#include <iostream>
#include <cstdio>
#include <cstring>
const int N=1e5+5;
int n,m,pt_ans,ans[N];

namespace IO{
	const int SIZE=1<<16;
	char ibuf[SIZE],*ih,*it,obuf[SIZE],*oh=obuf,*ot=obuf+SIZE;
	inline void flush(){
		fwrite(obuf,1,oh-obuf,stdout);
		oh=obuf;
	}
	struct Flusher{
		~Flusher(){flush();};
	}_flusher;
	inline void put_c(const char c){
		*oh++=c;
		if(oh==ot) flush();
	}
	inline char get_c(){
		if(ih==it){
			it=(ih=ibuf)+fread(ibuf,1,SIZE,stdin);
			if(ih==it) return EOF;
		}
		return *ih++;
	}
	template <class T> inline T nxi(){
		T x=0;
		char c;
		while((c=getchar())>'9'||c<'0');
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return x;
	}
	template <class T> inline void pti(T x){
		static char tmp[20];
		char *pt=tmp;
		if(!x) put_c('0');
		for(T y=x/10; x; x=y,y=x/10){
			*pt++=x-y*10+'0';
		}
		while(pt!=tmp) put_c(*--pt);
	}
}
using IO::nxi;
using IO::pti;
using IO::get_c;
using IO::put_c;

namespace G{
	int cnt,fir[N];
	bool vis[N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	inline void dfs(const int x,const int fa){
		if(vis[x]) ans[++pt_ans]=x;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y!=fa) dfs(y,x);
		}
	}
}

int main(){
	n=nxi<int>(),m=nxi<int>();
	for(int i=1; i<n; ++i){
		int a=nxi<int>(),b=nxi<int>();
		nxi<int>();
		G::add(a,b);
		G::add(b,a);
	}
	for(int i=1; i<=m; ++i){
		G::vis[nxi<int>()]=1;
	}
	G::dfs(1,1);
	for(int i=1,j=i+(m>>1); j<=m; ++i,++j){
		pti(ans[i]),put_c(' ');
		pti(ans[j]),put_c('\n');
	}
	return 0;
}
