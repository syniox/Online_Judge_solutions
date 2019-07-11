#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e5+5;
int n,hbit[N],len[N],loop[N];
char str[N];

namespace utils{
	template <class T> inline void apn(T &x,const T y){x>y?x=y:0;}
	template <class T> inline void apx(T &x,const T y){x<y?x=y:0;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

void init(){
	for(int i=2; i<=n; ++i){
		hbit[i]=hbit[i>>1]+1;
	}
}

namespace B{
	int tr[N];
	inline void init(){
		for(int i=1; i<=n; ++i) tr[i]=n+1;
	}
	inline void apl(int x,const int v){
		for(; x<=n&&tr[x]>v; x+=x&-x) tr[x]=v;
	}
	inline int ask(int x){
		int ans=n+1;
		for(; x; x-=x&-x) apn(ans,tr[x]);
		return ans;
	}
}

namespace SA{
	int n,sa[N],rnk[N],hgt[17][N];

	inline int get_rk(const int x){
		return x>n?0:rnk[x];
	}

	void qsort(int *sa,const int *rnk,const int *idx){
		static int buk[N];
		const int lim=std::max(n,26);
		memset(buk+1,0,lim*sizeof(buk[0]));
		for(int i=1; i<=n; ++i){
			++buk[rnk[i]];
		}
		for(int i=1; i<=n; ++i){
			buk[i]+=buk[i-1];
		}
		for(int i=n; i>=1; --i){
			sa[buk[rnk[idx[i]]]--]=idx[i];
		}
	}

	void build(const char *str,const int n){
		static int tmp[N];
		SA::n=n;
		for(int i=1; i<=n; ++i){
			tmp[i]=i;
			rnk[i]=str[i]-'a'+1;
		}
		qsort(sa,rnk,tmp);
		for(int w=1,cnt_rk=0; cnt_rk<n; w<<=1){
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
			p=std::max(0,p-1);
			if(rnk[i]==1) continue;
			for(int j=sa[rnk[i]-1]; j+p<=n&&i+p<=n&&str[j+p]==str[i+p]; ++p);
			hgt[0][rnk[i]]=p;
		}
		for(int i=1; i<17; ++i){
			for(int j=1<<i; j<=n; ++j){
				hgt[i][j]=std::min(hgt[i-1][j],hgt[i-1][j-(1<<(i-1))]);
			}
		}
	}

	int get_lcp(int x,int y){
		x=rnk[x],y=rnk[y];
		if(x>y) std::swap(x,y);
		int l=hbit[y-x];
		return std::min(hgt[l][x+(1<<l)],hgt[l][y]);
	}

	void get_ans(){
		for(int i=n; i>=1; --i){
			int nxt=B::ask(rnk[i]);
			if(nxt>n) len[i]=n-i+1,loop[i]=1;
			else{
				int lcp=get_lcp(i,nxt);
				len[i]=nxt-i;
				loop[i]=1+(lcp>=len[i])*loop[nxt];
			}
			B::apl(rnk[i],i);
		}
	}
}

int main(){
	scanf("%s",str+1);
	n=strlen(str+1);
	B::init();
	init();
	SA::build(str,n);
	SA::get_ans();
	for(int q=nxi(); q; --q){
		const int l=nxi(),k=nxi();
		if(loop[l]%k){
			printf("%d %d\n",l,l+(loop[l]+k-1)/k*len[l]-1);
		}
		else{
			printf("%d %d\n",l+len[l]*(loop[l]-loop[l]/k),n);
		}
	}
	return 0;
}
