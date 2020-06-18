#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e5+5;
int ls,ans,to_ans[4][4];
lint dp[N][4];
lint n;
char str[N];
struct data{
	int v[4];
	data(){ memset(v,10,sizeof(v)); }
	void add(){++v[0],++v[1],++v[2],++v[3];}
	friend data operator * (const data &a,const data &b){
		data c;
		for(int i=0; i<4; ++i) c.v[i]=std::min(a.v[i],b.v[i]);
		return c;
	}
};

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
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

namespace S{
	int cnt,lst;
	struct node{
		int lk,len,c[4];
	}tr[N<<1];
	struct _init{
		_init(){tr[0].lk=-1;}
	}_init_;

	inline void insert(const int c){
		int p=lst,k=lst=++cnt;
		tr[k].len=tr[p].len+1;
		for(; ~p&&!tr[p].c[c]; p=tr[p].lk){
			tr[p].c[c]=k;
		}
		if(p==-1) return;
		int q=tr[p].c[c];
		if(tr[q].len==tr[p].len+1) tr[k].lk=q;
		else{
			tr[++cnt]=tr[q];
			tr[cnt].len=tr[p].len+1;
			for(; ~p&&tr[p].c[c]==q; p=tr[p].lk){
				tr[p].c[c]=cnt;
			}
			tr[k].lk=tr[q].lk=cnt;
		}
	}

	bool vis[N<<1];
	data dat[N<<1];
	data get_to(const int x){
		if(vis[x]) return dat[x];
		vis[x]=1;
		for(int i=0; i<4; ++i){
			int y=tr[x].c[i];
			if(!y){
				dat[x].v[i]=1;
				continue;
			}
			data tmp=get_to(y);
			if(x==0){
				memcpy(to_ans[i],tmp.v,sizeof(to_ans[i]));
			}else{
				tmp.add();
				dat[x]=dat[x]*tmp;
			}
		}
		return dat[x];
	}
}

struct mtrx{
	lint v[4][4];
	friend mtrx operator * (const mtrx &a,const mtrx &b){
		mtrx c;
		memset(c.v,60,sizeof(c.v));
		for(int i=0; i<4; ++i){
			for(int j=0; j<4; ++j){
				for(int k=0; k<4; ++k)
					apn(c.v[i][k],a.v[i][j]+b.v[j][k]);
			}
		}
		return c;
	}
	bool any(){
		for(int i=0; i<4; ++i){
			for(int j=0; j<4; ++j){
				if(v[i][j]<n) return 1;
			}
		}
		return 0;
	}
}base[65];

lint solve(){
	int cnt=1;
	for(; ; ++cnt){
		base[cnt]=base[cnt-1]*base[cnt-1];
		if(!base[cnt].any()) break;
	}
	mtrx cur=base[cnt-1];
	lint ans=1ll<<(cnt-1);
	for(int i=cnt-2; ~i; --i){
		mtrx tmp=cur*base[i];
		if(tmp.any()) cur=tmp,ans+=1ll<<i;
	}
	return ans+1;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("d.in","r",stdin);
#endif
	n=nxi();
	memset(to_ans,10,sizeof(to_ans));
	scanf("%s",str+1);
	ls=strlen(str+1);
	for(int i=1; i<=ls; ++i){
		S::insert(str[i]-'A');
	}
	S::get_to(0);
	for(int i=0; i<4; ++i){
		for(int j=0; j<4; ++j){
			base[0].v[i][j]=to_ans[i][j]<=ls?to_ans[i][j]:1e18;
		}
	}
	printf("%lld\n",solve());
	return 0;
}
