#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e6+5;
int n;
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

namespace S{
	int sa[N],rk[N];

	inline int get_rk(const int x){
		return x>n?-1:rk[x];
	}

	void qsort(int *sa,const int *rk,const int *idx){
		static int buk[N];
		int m=std::max(n,26);
		memset(buk,0,m*sizeof(int));
		for(int i=1; i<=n; ++i){
			++buk[rk[i]];
		}
		for(int i=1; i<=m; ++i){
			buk[i]+=buk[i-1];
		}
		for(int i=n; i>=1; --i){
			sa[buk[rk[idx[i]]]--]=idx[i];
		}
	}

	void build(){
		static int tmp[N];
		for(int i=1; i<=n; ++i){
			rk[i]=str[i]==' '?0:str[i]-'A'+1;
			tmp[i]=i;
		}
		qsort(sa,rk,tmp);
		for(int w=1,cnt_rk=1; cnt_rk<n&&w<n; w<<=1){
			for(int i=1; i<=w; ++i){
				tmp[i]=n-w+i;
			}
			cnt_rk=w;
			for(int i=1; i<=n; ++i){
				if(sa[i]>w) tmp[++cnt_rk]=sa[i]-w;
			}
			qsort(sa,rk,tmp);
			cnt_rk=0;
			for(int i=1; i<=n; ++i){
				cnt_rk+=rk[sa[i]]!=rk[sa[i-1]]||get_rk(sa[i]+w)!=get_rk(sa[i-1]+w);
				tmp[sa[i]]=cnt_rk;
			}
			memcpy(rk+1,tmp+1,n*sizeof(int));
		}
	}
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		char c;
		while((c=getchar())>'Z'||c<'A');
		str[i]=c;
	}
	str[n+1]=' ';
	for(int i=1; i<=n; ++i){
		str[n+i+1]=str[n-i+1];
	}
	n=n<<1|1;
	S::build();
	for(int i=1,j=1,k=n>>1; i*2<n; ++i){
		if(S::rk[j]>S::rk[n-k+1]) putchar(str[k--]);
		else putchar(str[j++]);
		if(i%80==0) puts("");
	}
	puts("");
	return 0;
}
