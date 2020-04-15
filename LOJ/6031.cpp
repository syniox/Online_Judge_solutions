//11:32->12:27 14:18
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
typedef long long lint;
const int N=1e5+5;
const int B=320;
int n,m,q,u;
std::pair <int,int> seg[N];
std::vector <int> mpos[B][B];
char str[N];

namespace utils{
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

inline int getsum(std::vector <int> &vt,int l,int r){
	return std::lower_bound(vt.begin(),vt.end(),r+1)-std::lower_bound(vt.begin(),vt.end(),l);
}

namespace S{
	int lst,cnt,fcnt[N<<1];
	std::vector <int> lk_s[N<<1];
	struct node{
		int sz,len,lk[17],c[26];
	}tr[N<<1];
	struct _init{
		_init(){
			tr[0].lk[0]=-1;
			for(int i=0; i<N<<1; ++i){
				memset(tr[i].lk+1,-1,16*sizeof(int));
			}
		}
	}init;

	void expend(const int pos,const int c){
		int p=lst,k=lst=++cnt;
		tr[k].len=tr[p].len+1;
		tr[k].sz=1;
		for(; ~p&&!tr[p].c[c]; p=tr[p].lk[0]){
			tr[p].c[c]=k;
		}
		if(p==-1) return;
		int q=tr[p].c[c];
		if(tr[q].len==tr[p].len+1) tr[k].lk[0]=q;
		else{
			tr[++cnt]=tr[q];
			tr[cnt].len=tr[p].len+1;
			tr[cnt].sz=0;
			for(; ~p&&tr[p].c[c]==q; p=tr[p].lk[0]){
				tr[p].c[c]=cnt;
			}
			tr[k].lk[0]=tr[q].lk[0]=cnt;
		}
	}

	void dfs_lk(const int x){
		for(int &i=fcnt[x]; ~tr[x].lk[i]; ++i){
			tr[x].lk[i+1]=tr[tr[x].lk[i]].lk[i];
		}
		for(std::vector <int> ::iterator it=lk_s[x].begin(); it!=lk_s[x].end(); ++it){
			dfs_lk(*it);
			tr[x].sz+=tr[*it].sz;
		}
	}

	void build_lk_tr(){
		for(int i=1; i<=cnt; ++i){
			assert(tr[i].lk[0]>=0);
			lk_s[tr[i].lk[0]].push_back(i);
		}
		dfs_lk(0);
	}

	lint sol_s(const char *str){
		int l=nxi()+1,r=nxi()+1,n=strlen(str+1);
		lint ans=0;
		for(int i=1; i<=n; ++i){
			int p=0;
			for(int j=i; j<=n; ++j){
				p=tr[p].c[str[j]-'a'];
				if(p==0) break;
				ans+=(lint)tr[p].sz*getsum(mpos[i][j],l,r);
			}
		}
		return ans;
	}

	lint sol_b(const char *str){
		static std::vector <int> buk[N];
		int p=0,l=nxi()+1,r=nxi()+1,n=strlen(str+1);
		lint ans=0;
		for(int i=1; i<=n; ++i){
			buk[i].clear();
		}
		for(int i=l; i<=r; ++i){
			int sl=seg[i].first,sr=seg[i].second;
			buk[sr].push_back(sl);
		}
		for(int i=1; i<=n; ++i){
			if(!buk[i].empty()){
				std::sort(buk[i].begin(),buk[i].end());
			}
		}
		for(int len=0,i=1; i<=n; ++i){
			int c=str[i]-'a';
			for(; ~p&&!tr[p].c[c]; p=tr[p].lk[0]);
			if(~p){
				len=std::min(len,tr[p].len)+1;
				p=tr[p].c[c];
			}
			else len=p=0;
			int q=p;
			for(std::vector <int> ::iterator it=buk[i].begin(); it!=buk[i].end(); ++it){
				if(len<=i-*it) continue;
				for(int j=fcnt[q]-1; ~j; --j){
					if(tr[tr[q].lk[j]].len>i-*it){
						q=tr[q].lk[j];
						apn(j,fcnt[q]);
					}
				}
				ans+=tr[q].sz;
			}
		}
		return ans;
	}
}

int main(){
	n=nxi(),m=nxi(),q=nxi(),u=nxi();
	scanf("%s",str+1);
	for(int i=1; i<=n; ++i){
		S::expend(i,str[i]-'a');
	}
	S::build_lk_tr();
	for(int i=1; i<=m; ++i){
		seg[i].first=nxi()+1,seg[i].second=nxi()+1;
	}
	if(u<=B){
		for(int i=1; i<=m; ++i){
			mpos[seg[i].first][seg[i].second].push_back(i);
		}
		for(int i=1; i<=q; ++i){
			scanf("%s",str+1);
			printf("%lld\n",S::sol_s(str));
		}
	}
	else{
		for(int i=1; i<=q; ++i){
			scanf("%s",str+1);
			printf("%lld\n",S::sol_b(str));
		}
	}
	return 0;
}
