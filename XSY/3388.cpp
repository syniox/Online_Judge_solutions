#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
typedef long long lint;
const int N=1e6+5;
int n,val[N];
lint m;

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
		for(int y=x/10; x; x=y,y=x/10){
			*pt++=x-y*10+'0';
		}
		while(pt!=tmp) put_c(*--pt);
	}
}
using IO::nxi;
using IO::pti;
using IO::get_c;
using IO::put_c;

inline void solve(){
	std::priority_queue <int> pq;
	int len=0;
	while(len<=n&&m>=n-len-1){
		m-=n-++len;
	}
	if(len){
		for(int i=1; i<=len; ++i){
			pq.push(val[i]);
			val[i]=i;
		}
		for(int i=len+1; i<=n; ++i){
			if(val[i]<pq.top()){
				pq.push(val[i]);
				val[i]=pq.top();
				pq.pop();
			}
		}
	}
	for(int j=1; j<=m; ++j){
		if(val[len+1]>val[len+1+j]){
			std::swap(val[len+1],val[len+1+j]);
		}
	}
	for(int i=1; i<=n; ++i){
		pti(val[i]);
		put_c(' ');
	}
	put_c('\n');
}

int main(){
	n=nxi<int>(),m=nxi<lint>();
	for(int i=1; i<=n; ++i){
		val[i]=nxi<int>();
	}
	solve();
	return 0;
}
