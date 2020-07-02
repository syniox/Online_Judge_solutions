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
int g,sumn,summ,ans,nxt[N];
bool n0,m0,vn[N],vm[N<<1];
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
	memset(v,0,mod);
	bool have_0=0;
	int offs=(lint)s*invn%mod;
	for(int i=1; i<=n; ++i){
		int tmp=(buk[i]-offs+mod)%mod;
		if(!tmp) have_0=1;
		else v[invg[tmp]]=1;
	}
	return have_0;
}

int getg(const int mod){
	static int cnp,prm[N];
	static bool npr[N];
	for(int i=2; i<mod; ++i){
		if(!npr[i]) prm[++cnp]=i;
		for(int j=1; j<=cnp&&i*prm[j]<mod; ++i){
			npr[i*prm[j]]=1;
			if(i%prm[j]==0) break;
		}
	}
	int cnt=0;
	for(int i=1; i<=cnp; ++i){
		if((mod-1)%prm[i]==0) prm[++cnt]=prm[i];
	}
	for(int i=2; i<mod; ++i){
		bool f=1;
		for(int j=1; f&&j<=cnt; ++j){
			f&=fpow(i,(mod-1)/prm[j])!=1;
		}
		if(f) return i;
	}
	return 0;
}

int main(){
	n=nxi(),m=nxi(),mod=nxi();
	g=getg(mod);
	invg[1]=0,pwg[0]=1;
	for(int j=1,i=g; i!=1; ++j,i=(lint)i*g%mod){
		pwg[j]=i,invg[i]=j;
	}
	n-=n0=getv(vn,n,sumn);
	m-=m0=getv(vm,m,summ);
	if(m0^n0){
		if(n0||m) puts("0");
		else printf("1\n0 %lld\n",(lint)summ*invn%mod);
		return 0;
	}
	if(m+m0==1){
		int x=0;
		if(m){
			for(; !vm[x]; ++x);
			x=pwg[x];
		}
		abuk[0].push_back((x+(lint)summ*invn)%mod);
	}
	const int kmplen=mod-1;
	nxt[0]=-1;
	for(int i=1,j=-1; i<kmplen; ++i){
		while(~j&&vn[j+1]!=vn[i]) j=nxt[j];
		nxt[i]=j+=vn[j+1]==vn[i];
	}
	memcpy(vm+kmplen,vm,kmplen);
	for(int i=0,j=-1; i<(kmplen)*2-1; ++i){
		while(~j&&vn[j+1]!=vm[i]) j=nxt[j];
		if((j+=vn[j+1]==vm[i])==kmplen-1){
			j=nxt[j];
			int resa=pwg[i-mod+2];
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
