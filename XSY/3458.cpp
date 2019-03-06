#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
const int N=1.1e6+5;
const int mod=1e9+7;
int n,mp[128];
char ch[N],idx_ch[4];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void init(){
	mp['A']=0,mp['C']=1,mp['G']=2,mp['T']=3;
	idx_ch[0]='A',idx_ch[1]='C';
	idx_ch[2]='G',idx_ch[3]='T';
}

namespace O{
	const int SIZE=2e6+5;
	char buf[SIZE],*h=buf,*t=h+SIZE;
	inline void flush(){
		fwrite(buf,1,h-buf,stdout);
		h=buf;
	}
	struct _Flusher{
		~_Flusher(){flush();}
	}_flusher;
	inline void put_c(char c){
		*h++=c;
		if(h==t) flush();
	}
	inline void write(char *ch,int cnt){
		if(t-h<cnt) flush();
		memcpy(h,ch,cnt);
		h+=cnt;
	}
	template <class T> inline void put_i(T x){
		static char ch[20];
		char *pt=ch;
		for(T y=x/10; x; x=y,y=x/10){
			*pt++=x-y*10+'0';
		}
		while(pt!=ch) put_c(*--pt);
	}
}

namespace S{
	int lst,cnt,bel,rt[N],nxt[4];
	int ans;
	bool vis[N*3];
	class node{
		public:
			int lk,len,c[4];
	}tr[N*3];

	inline void insert(int c){
		int p=lst,k=lst=++cnt;
		tr[k].len=tr[p].len+1;
		for(; p&&!tr[p].c[c]; p=tr[p].lk){
			tr[p].c[c]=k;
		}
		if(!p) tr[k].lk=rt[bel];
		else{
			int q=tr[p].c[c];
			if(tr[q].len==tr[p].len+1) tr[k].lk=q;
			else{
				tr[++cnt]=tr[q];
				tr[cnt].len=tr[p].len+1;
				for(; p&&tr[p].c[c]==q; p=tr[p].lk){
					tr[p].c[c]=cnt;
				}
				tr[k].lk=tr[q].lk=cnt;
			}
		}
	}

	inline void build(const int bel){
		rt[bel]=lst=++cnt;
		S::bel=bel;
		int len=strlen(ch+1);
		for(int i=1; i<=len; ++i){
			insert(mp[(int)ch[i]]);
		}
	}

	void dfs_lk(const int k){
		vis[k]=1;
		for(int i=0; i<4; ++i){
			if(tr[k].c[i]){
				if(!vis[tr[k].c[i]]) dfs_lk(tr[k].c[i]);
			}
			else tr[k].c[i]=nxt[i];
		}
	}

	inline void link(const int bel){
		dfs_lk(rt[bel]);
		for(int i=0; i<4; ++i){
			if(tr[rt[bel]].c[i]){
				nxt[i]=tr[rt[bel]].c[i];
			}
		}
	}

	void dfs_route(const int k){
		static char route[N*3];
		static int pt;
		for(int i=0; i<4; ++i){
			if(!tr[k].c[i]) continue;
			route[pt++]=idx_ch[i];
			route[pt++]='\n';
			O::write(route,pt);
			--pt;
			++ans;
			dfs_route(tr[k].c[i]);
			--pt;
		}
	}

	int dfs_dp(const int k){
		static int dp[N*3];
		if(dp[k]) return dp[k];
		dp[k]=1;
		for(int i=0; i<4; ++i){
			if(tr[k].c[i]) dp[k]=(dp[k]+dfs_dp(tr[k].c[i]))%mod;
		}
		return dp[k];
	}
}

int main(){
	init();
	n=nxi();
	for(int i=1; i<=n; ++i){
		scanf("%s",ch+1);
		S::build(i);
	}
	for(int i=n; i; --i){
		S::link(i);
	}
	if(nxi()){
		O::put_c('\n');
		S::dfs_route(S::rt[1]);
		O::put_i((S::ans+1)%mod);
		O::put_c('\n');
	}
	else{
		printf("%d\n",S::dfs_dp(S::rt[1]));
	}
	return 0;
}
