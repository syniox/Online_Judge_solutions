#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=6005;
int n,col[N],sum[3],lim[3],limb[2];
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

int san_l(char *str,const int f,const int tgt){
	int cur=0,rst=tgt>sum[f]?tgt-sum[f]:sum[f]-tgt;
	if(rst&1) return N;
	if(tgt<sum[f]){
		for(int i=n; cur<rst&&i>=1; --i){
			if(col[i]==f&&str[i]=='('){
				cur+=2,str[i]=')';
			}
		}
	}
	else{
		for(int i=1; cur<rst&&i<=n; ++i){
			if(col[i]==f&&str[i]==')'){
				cur+=2,str[i]='(';
			}
		}
	}
	assert(rst>>1>=0);
	return cur==rst?rst>>1:N;
}

bool get_lim(const char *str,const bool f){
	static int cb[N],cf[N];
	for(int i=n; i>=1; --i){
		cb[i]=cb[i+1]+(str[i]=='('&&col[i]==2);
		cf[i]=cf[i+1]+(str[i]=='('&&col[i]==f);
	}
	for(int p=0,sb=0,sf=0,i=1; i<=n; ++i){
		if(col[i]!=(f^1)){
			p+=str[i]=='('?1:-1;
		}
		sb+=str[i]==')'&&col[i]==2;
		sf+=str[i]==')'&&col[i]==f;
		const int req=(-p+1)>>1;
		const int lb=std::min(sb,cb[i+1]);
		const int lf=std::min(sf,cf[i+1]);
		apx(limb[f],req);
		apx(lim[f],req-lb);
		apx(lim[2],req-lf);
		if(lb+lf<req) return 0;
	}
	return 1;
}

int solve(const int t){
	static char oput[N];
	memset(limb,0,sizeof(limb));
	memset(lim,0,sizeof(lim));
	memcpy(oput,str,n+1);
	int ans=0;
	if((ans+=san_l(oput,2,-t))>n){
		return N;
	}
	if((ans+=san_l(oput,0,t))>n){
		return N;
	}
	if((ans+=san_l(oput,1,t))>n){
		return N;
	}
	if(!get_lim(oput,0)) return N;
	if(!get_lim(oput,1)) return N;
	ans+=lim[0]*2+lim[1]*2;
	int req2=std::max(limb[0]-lim[0],limb[1]-lim[1]);
	return ans+std::max(lim[2],req2)*2;
}

int main(){
	n=nxi();
	scanf("%s",str+1);
	for(int i=1; i<=n; ++i){
		col[i]=nxi();
		sum[col[i]]+=str[i]=='('?1:-1;
	}
	if((sum[0]+sum[2])&1||(sum[1]+sum[2])&1){
		puts("-1");
		return 0;
	}
	int ans=n+1;
	for(int i=-n; i<=n; ++i){
		apn(ans,solve(i));
	}
	printf("%d\n",ans>n?-1:ans);
	return 0;
}
