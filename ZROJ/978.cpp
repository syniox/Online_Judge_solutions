#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
typedef long long lint;
const int N=1e5+5;
int n,req[32];
std::vector <lint> qb[31];
lint q,suma;

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline lint nxi(){
		lint x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=c=='-'&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

void solve(const int p,const lint *s,lint *t,int sl,int sr,int tl,int tr){
	const int mid=(tl+tr)>>1;
	int dec=-1;
	lint ans=-1e13;
	for(int i=std::max(mid,sl); i<=std::min(sr,mid+(int)qb[p].size()); ++i){
		lint res=s[i]+(i==mid?0:qb[p][i-mid-1]);
		if(res>ans){
			dec=i,ans=res;
		}
	}
	assert(~dec);
	t[mid]=ans;
	if(tl<mid) solve(p,s,t,sl,dec,tl,mid-1);
	if(tr>mid) solve(p,s,t,dec,sr,mid+1,tr);
}

int hbit(lint t){
	int ans=0;
	for(int i=32; i; --i){
		if(t>>i) ans+=i,t>>=i;
	}
	return ans;
}

bool valid(const lint t){
	static lint dp[N],fp[N];
	memset(dp,-10,sizeof(dp));
	int tmp=hbit(t),mx=0;
	if(tmp<30) dp[0]=0;
	else{
		req[31]=(int)(t>>31);
		dp[req[31]]=0;
		mx=req[31];
		tmp=30;
	}
	for(int i=tmp; ~i; --i){
		mx=std::min((mx<<1)+(int)(t>>i&1),req[i]);
		memset(fp,-10,(req[i]+1)*sizeof(fp[0]));
		for(int j=0; j<=req[i+1]; ++j){
			apx(fp[std::min((j<<1)+(int)(t>>i&1),req[i])],dp[j]);
		}
		for(int j=req[i]-1; ~j; --j){
			apx(fp[j],fp[j+1]);
		}
		solve(i,fp,dp,0,mx,0,mx);
	}
	return dp[0]>=q;
}

int main(){
	n=nxi(),q=nxi();
	for(int i=1; i<=n; ++i){
		int a=nxi();
		lint v=nxi();
		suma+=1ll<<a;
		qb[a].push_back(v);
	}
	for(int i=0; i<=30; ++i){
		req[i]=(i?(req[i-1]+1)>>1:0)+qb[i].size();
		if(qb[i].empty()) continue;
		std::sort(qb[i].begin(),qb[i].end(),std::greater <int> ());
		for(int j=1; j<(int)qb[i].size(); ++j){
			qb[i][j]+=qb[i][j-1];
		}
	}
	{
		lint l=0,r=suma,mid;
		while(l!=r){
			mid=(l+r)>>1;
			if(valid(mid)) r=mid;
			else l=mid+1;
		}
		printf("%lld\n",l);
	}
	return 0;
}
