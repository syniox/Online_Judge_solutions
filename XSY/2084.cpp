#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
using namespace std;
const int N=1e5+5;
int n,q,m,pos[N];
lint ans[N];
char str[N];

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

namespace S{//0-index!
	int lst,cnt;
	struct node{
		int lk,len,c[26];
	}tr[N<<1];
	struct _init{
		_init(){tr[0].lk=-1;}
	}_init_;

	int insert(const int c){
		int p=lst,k=lst=++cnt;
		tr[k].len=tr[p].len+1;
		for(; ~p&&!tr[p].c[c]; p=tr[p].lk){
			tr[p].c[c]=k;
		}
		if(p==-1) return k;
		const int q=tr[p].c[c];
		if(tr[q].len==tr[p].len+1) tr[k].lk=q;
		else{
			tr[++cnt]=tr[q];
			tr[cnt].len=tr[p].len+1;
			for(; ~p&&tr[p].c[c]==q; p=tr[p].lk){
				tr[p].c[c]=cnt;
			}
			tr[k].lk=tr[q].lk=cnt;
		}
		return k;
	}
}

namespace T{//1-index!
	struct node{
		int f,pos,c[2];
	}tr[N<<1];

	inline bool isrt(const int x){
		return tr[tr[x].f].c[0]!=x&&tr[tr[x].f].c[1]!=x;
	}
	inline bool side(const int x){
		return tr[tr[x].f].c[1]==x;
	}
	inline void psh(const int x){
		if(tr[x].c[0]) tr[tr[x].c[0]].pos=tr[x].pos;
		if(tr[x].c[1]) tr[tr[x].c[1]].pos=tr[x].pos;
	}

	void rotate(const int x){
		const int f=tr[x].f,ff=tr[f].f,sid=side(x);
		int &p=tr[x].c[sid^1];
		tr[x].f=ff;
		if(!isrt(f)) tr[ff].c[side(f)]=x;
		tr[f].c[sid]=p;
		tr[f].f=x;
		if(p) tr[p].f=f;
		p=f;
	}

	void splay(const int x){
		static int stk[N];
		int top=0;
		for(int i=x; ; i=tr[i].f){
			stk[++top]=i;
			if(isrt(i)) break;
		}
		for(; top; --top){
			psh(stk[top]);
		}
		while(!isrt(x)){
			const int f=tr[x].f;
			if(!isrt(f)){
				rotate(side(f)==side(x)?f:x);
			}
			rotate(x);
		}
	}

	void solve(){
		static lint cf[N];//开始位置答案差分数组
		lint res=0;
		for(int i=1; i<=n; ++i){
			int x=pos[i]+1,y=0;
			for(; x; y=x,x=tr[x].f){
				splay(x);
				if(tr[x].pos){
					assert(x);
					int l=tr[x].pos-S::tr[x-1].len+1;
					int r=tr[x].pos-(tr[x].f?S::tr[tr[x].f-1].len:0);
					apx(l,i-m);
					if(l<=r){
						--cf[l],++cf[r+1];
						res-=r-l+1;
					}
				}
				tr[x].c[1]=y;
			}
			splay(pos[i]+1);
			tr[pos[i]+1].pos=i;
			if(i>m){
				res-=cf[i-m];
				cf[i-m+1]+=cf[i-m];
			}
			++cf[max(i-m+1,1)];
			--cf[i+1];
			res+=min(i,m);
			if(i>=m) ans[i-m+1]=res;
		}
	}
}

int main(){
	scanf("%s",str+1);
	n=strlen(str+1),q=nxi(),m=nxi();
	for(int i=1; i<=n; ++i){
		pos[i]=S::insert(str[i]-'a');
	}
	for(int i=1; i<=S::cnt; ++i){
		T::tr[i+1].f=S::tr[i].lk+1;
	}
	T::solve();
	while(q--){
		printf("%lld\n",ans[nxi()]);
	}
	return 0;
}
