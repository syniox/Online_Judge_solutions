#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long lint;
const int N=1e6+5;
int n,m,mod,invn,pwg[N],invg[N];
int sumn,summ,ans;
bool n0,m0,vn[N],nxt[N],vm[N<<1];
vector <int> abuk[N];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
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

inline int fpow(int x,int t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

bool getv(bool *v,int &n,int &s){
	static int buk[N];
	for(int i=1; i<=n; ++i){
		v[nxi()%mod]=1;
	}
	s=n=0;
	for(int i=0; i<mod; ++i){
		if(v[i]){
			buk[++n]=i;
			s=(s+i)%mod;
		}
	}
	invn=fpow(n,mod-2);
	int offs=(lint)s*invn%mod;
	memset(v,0,mod);
	bool have_0=0;
	for(int i=1; i<=n; ++i){
		int tmp=(buk[i]-offs+mod)%mod;
		if(!tmp) have_0=1;
		else v[invg[tmp]]=1;
	}
	return have_0;
}

int main(){
	n=nxi(),m=nxi(),mod=nxi();
	invg[1]=0,pwg[0]=1;
	for(int j=1,i=2; i!=1; ++j,i=(i<<1)%mod){
		pwg[j]=i,invg[i]=j;
	}
	n-=n0=getv(vn,n,sumn);
	m-=m0=getv(vm,m,summ);
	if(m0^n0){
		if(n0||m) puts("0");
		else printf("1\n0 %lld\n",(lint)summ*invn%mod);
		return 0;
	}
	for(int i=1,j=0; i<mod; ++i){
		while(j&&vn[j]!=vn[i]) j=nxt[j-1];
		nxt[i]=j+=vn[j]==vn[i];
	}
	memcpy(vm+mod,vm,mod);
	for(int i=0,j=0; i<mod*2-1; ++i){
		while(j&&vn[j]!=vm[i]) j=nxt[j-1];
		if((j+=vn[j]==vm[i])==mod){
			j=nxt[j-1];
			int resa=pwg[i-mod+1];
			assert(resa);
			if(n+n0==mod){
				for(int k=0; k<mod; ++k)
					abuk[resa].push_back(k);
				ans+=mod;
			}else{
				++ans;
				int f=((summ-(lint)resa*sumn)%mod+mod)%mod;
				abuk[resa].push_back((lint)f*invn%mod);
			}
		}
	}
	printf("%d\n",ans);
	for(int i=0; i<mod; ++i){
		for(vector<int>::iterator it=abuk[i].begin(); it!=abuk[i].end(); ++it){
			printf("%d %d\n",i,*it);
		}
	}
	return 0;
}
