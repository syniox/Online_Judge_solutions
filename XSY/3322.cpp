#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=1e5+5;
int n,w_val[N],d_val[N];
lint pre_w[N];
char ch[N<<1];

template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int get_res(const int round,const int x,const int y){
	switch((x-y+3)%3){
		case 0:
			return d_val[round];
		case 1:
			return 0;
		case 2:
			return w_val[round];
	}
	return 0;
}

inline lint get_pre_w(int l,int r){
	return l>r?0:pre_w[r]-pre_w[l-1];
}

namespace SAM{
	int lst,cnt,end[N<<2];
	struct node{
		int lk,len,c[3];
	}tr[N<<2];

	inline void init(){
		tr[0].lk=-1;
	}

	inline void expend(const int c,const int cur){
		int p=lst,k=lst=++cnt;
		tr[k].len=tr[p].len+1;
		end[k]=cur;
		for(; ~p&&!tr[p].c[c]; p=tr[p].lk){
			tr[p].c[c]=k;
		}
		if(p==-1) return;
		int q=tr[p].c[c];
		if(tr[q].len==tr[p].len+1) tr[k].lk=q;
		else{
			tr[++cnt]=tr[q];
			tr[cnt].len=tr[p].len+1;
			end[cnt]=end[q];
			for(; ~p&&tr[p].c[c]==q; p=tr[p].lk){
				tr[p].c[c]=cnt;
			}
			tr[q].lk=tr[k].lk=cnt;
		}
	}
}

namespace SFT{
	int len[N<<2],son[N<<2][3];
	lint dp[N<<2];

	lint get_ans(int x,int l){
		if(dp[x]) return dp[x];
		lint ans=0;
		for(int i=0;i<3;++i){
			lint tp=1e15;
			for(int j=0;j<3;++j){
				if(son[x][j]){
					const int s_len=std::min(n,len[son[x][j]]);
					const lint res=get_res(l+1,i,j)+get_pre_w(l+2,s_len);
					apn(tp,res+(s_len<n?get_ans(son[x][j],s_len):0));
				}
			}
			if(tp!=1e15) apx(ans,tp);
		}
//		printf("x:%d l:%d ans:%lld\n",x,l,ans);
		return dp[x]=ans;
	}
}

inline void build_sft(){
	/*
	for(int i=0;i<=SAM::cnt;++i){
		using namespace SAM;
		printf("%d: lk%d,len%d end%d ",i,tr[i].lk,tr[i].len,end[i]);
		printf("[s0]%d [s1]%d [s2]%d\n",tr[i].c[0],tr[i].c[1],tr[i].c[2]);
	}
	*/
	for(int i=1;i<=SAM::cnt;++i){
		SFT::len[i]=SAM::tr[i].len;
		int fa=SAM::tr[i].lk;
//		printf("%d [%d,pos%d]-> %d\n",fa,ch[SAM::end[i]+SAM::tr[fa].len],SAM::end[i]+SAM::tr[fa].len,i);
		SFT::son[fa][(int)ch[SAM::end[i]+SAM::tr[fa].len]]=i;
	}
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("b.in","r",stdin);
#endif
	SAM::init();
	n=nxi();
	scanf("%s",ch+1);
	for(int i=1;i<=n;++i){
		switch(ch[i]){
			case 'r':
				ch[i]=0;
				break;
			case 's':
				ch[i]=1;
				break;
			case 'p':
				ch[i]=2;
				break;
		}
	}
	memcpy(ch+n+1,ch+1,n-1);
	for(int i=(n<<1)-1; i; --i){
		SAM::expend(ch[i],i);
	}
	for(int i=1;i<=n;++i){
		w_val[i]=nxi(),d_val[i]=nxi();
		pre_w[i]=pre_w[i-1]+w_val[i];
	}
	build_sft();
	printf("%lld\n",SFT::get_ans(0,0));
	return 0;
}
