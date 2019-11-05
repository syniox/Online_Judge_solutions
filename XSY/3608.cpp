#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <emmintrin.h>
#include <bitset>
typedef long long lint;
const int N=1e5+5;
int n,m,fa[N];
char ss[N],st[N];

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

int find_rt(const int x){
	return fa[x]?fa[x]=find_rt(fa[x]):x;
}

class mbit{
	protected:
		static int L;
		unsigned long long v[(N>>6)+1+(((N>>6)+1)&1)];
	public:
		static void len(const int l){
			L=l;
		}
		void set(const int x){
			int p=x>>6;
			v[p]|=1ull<<(x&((1<<6)-1));
		}
		void rshift(){
			for(int i=0; i<L-1; ++i){
				v[i]=v[i]>>1|(v[i+1]&1)<<63;
			}
			v[L-1]>>=1;
		}
		friend bool any(const mbit &a,const mbit &b){
			static int res[4];
			memset(res,0,sizeof(res));
			__m128i tmp,*pa=(__m128i*)a.v,*pb=(__m128i*)b.v;
			tmp=_mm_load_si128((__m128i*)res);
			for(int i=0; i<L; i+=2,++pa,++pb){
				tmp=_mm_or_si128(tmp,_mm_and_si128(*pa,*pb));
			}
			_mm_store_si128((__m128i*)res,tmp);
			for(int i=0; i<4; ++i){
				if(res[i]) return 1;
			}
			return 0;
		}
};
int mbit::L;
mbit fs[6],ft[6];

int main(){
	scanf("%s%s",ss,st);
	n=strlen(ss);
	m=strlen(st);
	mbit::len((m>>6)+1+(((m>>6)+1)&1));
	for(int i=0; i<m; ++i){
		ft[st[i]-'a'].set(i);
		fs[ss[i]-'a'].set(i);
	}
	for(int i=0; i<n-m+1; ++i){
		memset(fa,0,sizeof(fa));
		int cnt=0;
		for(int j=0; j<6; ++j){
			for(int k=0; k<6; ++k){
				if(find_rt(j+1)==find_rt(k+1)) continue;
				if(any(fs[j],ft[k])){
					fa[find_rt(j+1)]=find_rt(k+1);
					++cnt;
				}
			}
		}
		printf("%d ",cnt);
		if(i==n-m) break;
		for(int j=0; j<6; ++j){
			fs[j].rshift();
		}
		fs[ss[i+m]-'a'].set(m-1);
	}
	puts("");
	return 0;
}
