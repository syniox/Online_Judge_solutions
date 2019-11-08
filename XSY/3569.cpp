#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=3005;
const int mod=1e9+9;
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

class _bit{
	protected:
		int tr[N];
	public:
		inline void clear(){
			memset(tr+1,0,n*sizeof(int));
		}
		inline void add(int x,const int v){
			for(; x<=n; x+=x&-x) tr[x]=(tr[x]+v)%mod;
		}
		inline int ask(int x){
			int ans=0;
			for(; x; x-=x&-x) ans=(ans+tr[x])%mod;
			return ans;
		}
}B[N];

namespace S{
	int hbit[N],rnk[N],sa[N],lcp[17][N];//往前
	struct _init{
		_init(){
			for(int i=2; i<N; ++i){
				hbit[i]=hbit[i>>1]+1;
			}
		}
	}init;

	inline int get_rk(const int x){
		return x<=n?rnk[x]:0;
	}

	void qsort(int *sa,const int *rnk,const int *idx){
		static int buk[N];
		const int lim=std::max(n,26);
		memset(buk+1,0,lim*sizeof(int));
		for(int i=1; i<=n; ++i){
			++buk[rnk[i]];
		}
		for(int i=1; i<=lim; ++i){
			buk[i]+=buk[i-1];
		}
		for(int i=n; i>=1; --i){
			sa[buk[rnk[idx[i]]]--]=idx[i];
		}
	}

	void build(){
		static int tmp[N];
		for(int i=1; i<=n; ++i){
			tmp[i]=i;
			rnk[i]=str[i]-'a'+1;
		}
		qsort(sa,rnk,tmp);
		for(int w=1,cnt_rk=0; cnt_rk<n&&w<n; w<<=1){
			for(int i=1; i<=w; ++i){
				tmp[i]=n-w+i;
			}
			cnt_rk=w;
			for(int i=1; i<=n; ++i){
				if(sa[i]>w) tmp[++cnt_rk]=sa[i]-w;
			}
			qsort(sa,rnk,tmp);
			cnt_rk=0;
			for(int i=1; i<=n; ++i){
				if(rnk[sa[i]]!=rnk[sa[i-1]]||get_rk(sa[i]+w)!=get_rk(sa[i-1]+w)){
					++cnt_rk;
				}
				tmp[sa[i]]=cnt_rk;
			}
			memcpy(rnk+1,tmp+1,n*sizeof(int));
		}
		for(int i=1,p=0; i<=n; ++i){
			p=std::max(p-1,0);
			if(rnk[i]==1) continue;
			for(int j=sa[rnk[i]-1]; i+p<=n&&j+p<=n&&str[i+p]==str[j+p]; ++p);
			lcp[0][rnk[i]]=p;
		}
		for(int i=1; 1<<i<=n; ++i){
			for(int j=1<<i; j<=n; ++j){
				lcp[i][j]=std::min(lcp[i-1][j],lcp[i-1][j-(1<<(i-1))]);
			}
		}
	}

	int get_lcp(int x,int y){
		x=rnk[x],y=rnk[y];
		if(x>y) std::swap(x,y);
		int p=hbit[y-x];
		return std::min(lcp[p][x+(1<<p)],lcp[p][y]);
	}
}

int main(){
	while(~scanf("%s",str+1)){
		n=strlen(str+1);
		S::build();
		for(int i=1; i<=n; ++i){
			B[i].clear();
		}
		B[1].add(1,1);
		for(int i=1; i<=n; ++i){
			for(int j=i; j<n; ++j){
				const int cur=B[i].ask(j);
				if(!cur) continue;
				int l=S::get_lcp(i,j+1);
				if(l>=j-i+1){
					B[j+1].add(j+(j-i+1)+1,cur);
				}
				else if(str[j+l+1]>str[i+l]){
					B[j+1].add(j+l+1,cur);
				}
			}
		}
		int ans=0;
		for(int i=1; i<=n; ++i){
			//fprintf(stderr,"%d: %d\n",i,B[i].ask(n));
			ans=(ans+B[i].ask(n))%mod;
		}
		printf("%d\n",ans);
	}
	return 0;
}
