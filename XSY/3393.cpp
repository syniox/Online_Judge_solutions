#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=5005;
const int Q=502;
int n,q,pre_wzz[N];
lint dgr[N],buk_s[N],buk_t[N];
bool vis[N],wzz[26];
char str[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace H{
	const unsigned P=137;
	unsigned hsh[N],powp[N];
	inline void build(char *str,const int len){
		powp[0]=1;
		for(int i=1; i<=len; ++i){
			powp[i]=powp[i-1]*P;
		}
		for(int i=1; i<=len; ++i){
			hsh[i]=hsh[i-1]*P+(unsigned)(str[i]-'a'+1);
		}
	}
	inline unsigned get_hsh(const int l,const int r){
		return hsh[r]-hsh[l-1]*powp[r-l+1];
	}
}

class Disc{
	protected:
		unsigned buk[N],*pt;
	public:
		int tot;
		Disc(){pt=buk;}
		inline void insert(const unsigned v){
			*pt++=v;
		}
		inline void build(){
			std::sort(buk,pt);
			pt=std::unique(buk,pt);
			tot=pt-buk;
		}
		inline int ask(const unsigned v){
			return std::lower_bound(buk,pt,v)-buk+1;
		}
}D[Q];

lint solve(const int val){
	static int rm_end[N],rm_fir[N];
	static bool apl_s[N],apl_t[N];
	static lint tmp_s[N],tmp_t[N];
	const int len=q-1-val;
	memset(apl_s+1,0,D[len].tot*sizeof(bool));
	memset(apl_t+1,0,D[len].tot*sizeof(bool));
	bool flag=0;
	lint ans=0;
	for(int i=D[len].tot; i; --i){
		lint times=std::min(buk_s[i],buk_t[i]);
		flag|=buk_s[i]||buk_t[i];
		if(buk_s[i]-=times) apl_s[i]=1;
		if(buk_t[i]-=times) apl_t[i]=1;
		ans+=val*times;
	}
	if(!flag) return -1;
	for(int i=1; i<=n-len+1; ++i){
		int cur=D[len].ask(H::get_hsh(i,i+len-1));
		if(!apl_s[cur]&&!apl_t[cur]) continue;
		if(apl_s[cur]) rm_fir[cur]=D[len-1].ask(H::get_hsh(i+1,i+len-1));
		if(apl_t[cur]) rm_end[cur]=D[len-1].ask(H::get_hsh(i,i+len-2));
	}
	memset(tmp_s+1,0,D[len].tot*sizeof(lint));
	memset(tmp_t+1,0,D[len].tot*sizeof(lint));
	for(int i=D[len].tot; i; --i){
		if(buk_s[i]) tmp_s[rm_fir[i]]+=buk_s[i];
		if(buk_t[i]) tmp_t[rm_end[i]]+=buk_t[i];
	}
	memcpy(buk_s+1,tmp_s+1,D[len-1].tot*sizeof(lint));
	memcpy(buk_t+1,tmp_t+1,D[len-1].tot*sizeof(lint));
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
	//freopen("d.in","r",stdin);
#endif
	q=nxi();
	scanf("%s",str+1);
	n=strlen(str+1);
	H::build(str,n);
	wzz['o'-'a']=wzz['i'-'a']=wzz['e'-'a']=wzz['a'-'a']=1;
	wzz['s'-'a']=wzz['t'-'a']=wzz['b'-'a']=wzz['g'-'a']=1;
	for(int i=1; i<=n; ++i){
		pre_wzz[i]=pre_wzz[i-1]+wzz[str[i]-'a'];
	}
	D[0].insert(0);
	D[0].tot=1;
	for(int i=1; i<=q; ++i){
		for(int j=1; j<=n-i+1; ++j){
			D[i].insert(H::get_hsh(j,j+i-1));
		}
		D[i].build();
	}
	lint ans=q-1;
	for(int i=1; i<=n-q+1; ++i){
		int id=D[q].ask(H::get_hsh(i,i+q-1));
		if(vis[id]) continue;
		vis[id]=1;
		lint wgt=1ll<<(pre_wzz[i+q-1]-pre_wzz[i-1]);
		assert(wgt>0);
		int p1=D[q-1].ask(H::get_hsh(i,i+q-2));
		int p2=D[q-1].ask(H::get_hsh(i+1,i+q-1));
		ans+=wgt;
		dgr[p1]+=wgt;
		dgr[p2]-=wgt;
	}
	for(int i=1; i<=D[q-1].tot; ++i){
		if(dgr[i]<0) buk_s[i]-=dgr[i];
		if(dgr[i]>0) buk_t[i]+=dgr[i];
	}
	for(lint i=0,tmp=solve(i); ; tmp=solve(++i)){
		if(tmp!=-1) ans+=tmp;
		else{
			if(i) ans-=i-1;
			break;
		}
		assert(i<q);
	}
	printf("%lld\n",ans);
	return 0;
}
