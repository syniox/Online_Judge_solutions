#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
#include <algorithm>
#include <cmath>
typedef long long lint;
const int N=1e6+5;
int m,q,opt[N],exicnt[N],lstpos[N];
struct _pair{
	lint x,y;
	friend bool operator < (const _pair &a,const _pair &b){
		return a.x==b.x?a.y<b.y:a.x<b.x;
	}
	friend bool operator == (const _pair &a,const _pair &b){
		return a.x==b.x&&a.y==b.y;
	}
	friend _pair operator - (const _pair &a,const _pair &b){
		return (_pair){a.x-b.x,a.y-b.y};
	}
}ans,chn[N];
std::vector <_pair> mod_t[N];

inline __int128 crs(const _pair &a,const _pair &b){
	return (__int128)a.x*b.y-(__int128)a.y*b.x;
}

inline char get_c(){
	static char *h,*t,buf[20000];
	if(h==t){
		t=(h=buf)+fread(buf,1,20000,stdin);
		if(h==t) return EOF;
	}
	return *h++;
}

template <class T> inline T nxi(){
	T x=0;
	char c;
	while(((c=get_c())>'9'||c<'0')&&(c!='-'));
	const bool f=(c=='-')&&(c=get_c());
	while(x=x*10-48+c,(c=get_c())>='0'&&c<='9');
	return f?-x:x;
}

template <class T> class _Disc{
	public:
		T buk[N],*tl;
		int tot;
		_Disc(){tl=buk;}
		inline void insert(const T &v){
			*tl++=v;
		}
		inline void build(){
			std::sort(buk,tl);
			tl=std::unique(buk,tl);
			tot=tl-buk;
		}
		inline int ask(const T &v){
			return std::lower_bound(buk,tl,v)-buk+1;
		}
};
_Disc <_pair> D;

namespace T{
	std::vector <_pair> m_list[N<<1],q_list[N<<1];
	int x,y;
	_pair v;

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	void mod_t(const int l,const int r){
		if(l>=x&&r<=y){
			m_list[idx(l,r)].push_back(v);
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) mod_t(l,mid);
		if(y>mid) mod_t(mid+1,r);
	}

	void solve(const int t){
		static _pair stk[N];
		if(q_list[t].empty()) return;
		int hd=0,tl=0;
		for(int i=0,j=0; i<(int)q_list[t].size(); ++i){
			for(; j<(int)m_list[t].size()&&m_list[t][j].x<=q_list[t][i].x; ++j){
				_pair cur=m_list[t][j];
				for(; tl>hd+1&&crs(stk[tl-1]-stk[tl-2],cur-stk[tl-1])<0; --tl);
				stk[tl++]=cur;
			}
			if(hd==tl) continue;
			_pair cur=q_list[t][i];
			for(; hd<tl-1&&crs(stk[hd]-cur,stk[hd+1]-cur)>=0; ++hd);
			if((ans.x==0&&ans.y==1)||crs(ans,stk[hd]-cur)>0){
				ans=stk[hd]-cur;
			}
		}
	}

	void build(const int l,const int r){
		const int k=idx(l,r);
		if(l==r){
			solve(k);
			return;
		}
		const int mid=(l+r)>>1;
		const int ls=idx(l,mid),rs=idx(mid+1,r);
		build(l,mid);
		build(mid+1,r);
		q_list[k].resize(q_list[ls].size()+q_list[rs].size());
		std::merge(q_list[ls].begin(),q_list[ls].end(),
				q_list[rs].begin(),q_list[rs].end(),q_list[k].begin());
		q_list[ls]=std::vector <_pair>();
		q_list[rs]=std::vector <_pair>();
		solve(k);
	}

	inline void ask(const int x,const _pair cur){
		q_list[idx(x,x)].push_back(cur);
	}

	inline void mod(const int x,const int y,const _pair cur){
		T::x=x,T::y=y,T::v=cur;
		mod_t(1,m);
	}
}

__float128 f128_sqrt(__float128 x){
	assert(x>=1);
	__float128 l=0,r=x,mid;
	for(int i=0; i<1e3; ++i){
		mid=(l+r)*0.5;
		if(mid*mid>x) r=mid;
		else l=mid;
	}
	return l;
}

void f128_print(__float128 x,int c,char end='\n'){
	static int s[50];
	if(x<0){
		x=-x;
		putchar('-');
	}
	for(int i=0; i<=c+1; ++i){
		for(int j=9; ~j; --j){
			if((__float128)j<x){
				x-=s[i]=j;
				break;
			}
		}
		x*=10;
	}
	if(s[c+1]>=5){
		++s[c];
		for(int i=c; i&&s[i]>=10; --i){
			s[i]-=10;
			++s[i-1];
		}
	}
	printf("%d.",s[0]);
	for(int i=1; i<=c; ++i){
		printf("%d",s[i]);
	}
	putchar(end);
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("d.in","r",stdin);
#endif
	ans.y=1ll;
	nxi<int>();
	m=nxi<int>(),q=nxi<int>();
	for(int i=1; i<=m; ++i){
		opt[i]=nxi<int>();
		_pair cur;
		cur.x=nxi<lint>(),cur.y=nxi<lint>();
		if(opt[i]!=3) D.insert(cur);
		chn[i]=cur;
	}
	D.build();
	for(int i=1; i<=m; ++i){
		_pair cur=chn[i];
		const int id=D.ask(cur);
		assert(id);
		if(opt[i]==1){
			if(!exicnt[id]++) lstpos[id]=i;
		}
		if(opt[i]==2){
			if(!--exicnt[id]){
				mod_t[id].push_back((_pair){lstpos[id],i-1});
				lstpos[id]=0;
			}
		}
		if(opt[i]==3){
			if(id<=D.tot&&D.buk[id-1]==cur){
				printf("1.");
				for(int i=1; i<=q; ++i) putchar('0');
				puts("");
				return 0;
			}
			T::ask(i,cur);
		}
	}
	for(int i=1; i<=D.tot; ++i){
		if(lstpos[i]){
			mod_t[i].push_back((_pair){lstpos[i],m});
		}
	}
	for(int i=1; i<=D.tot; ++i){
		for(std::vector <_pair> ::iterator it=mod_t[i].begin(); it!=mod_t[i].end(); ++it){
			T::mod(it->x,it->y,D.buk[i-1]);
		}
	}
	T::build(1,m);
	__float128 res=(__float128)ans.y*ans.y+(__float128)ans.x*ans.x;
	res=-(__float128)ans.y/f128_sqrt(res);
	f128_print(res,q);
	return 0;
}
