  #include <iostream>
#include <cstdio>
#include <cstring>
const int N=3e5+5;
int n,xdif,val[N];
int len[2],idx[2][N];
int lk_cnt[N],lk_min[N][2];//fake: need to calc everytime 
bool vis[N],exi[31][2];

template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}
template <class T> inline void xswp(T &x,T &y){
	if(x<y) std::swap(x,y);
}

inline char get_c(){
	static char *h,*t,buf[1<<16];
	if(h==t){
		t=(h=buf)+fread(buf,1,1<<16,stdin);
		if(h==t) return EOF;
	}
	return *h++;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=get_c())>'9'||c<'0');
	while(x=x*10-48+c,(c=get_c())>='0'&&c<='9');
	return x;
}

inline void init(){
	memset(lk_min,60,(n+1)*sizeof(lk_min[0]));
}

inline bool get_dif(){
	for(int i=30; i>=0; --i){
		int tp=exi[i][0]+exi[i][1];
		if(tp==2){
			xdif=i;
			return 1;
		}
	}
	return 0;
}

namespace T{
	int cnt,ans=1e9+5;
	struct node{
		int s,nidx1,nidx2,c[2];
	}tr[N*31];

	inline void clear(const int k){
		tr[k].nidx1=tr[k].nidx2=N;
		tr[k].s=tr[k].c[0]=tr[k].c[1]=0;
	}

	inline void clear(){
		cnt=0;
		clear(0);
	}

	inline void upd_idx(int k,int x){
		xswp(tr[k].nidx1,x);
		xswp(tr[k].nidx2,x);
	}

	inline void merge_idx(const int k,int &n1,int &n2){
		int tmp1=tr[k].nidx1,tmp2=tr[k].nidx2;
		xswp(n2,tmp2);
		xswp(n1,tmp1);
		xswp(n2,tmp1);
	}

	inline void insert(int x){
		int p=0;
		for(int i=30; i>=0; --i){
			upd_idx(p,x);
			++tr[p].s;
			int &k=tr[p].c[val[x]>>i&1];
			if(!k) k=++cnt,clear(k);
			p=k;
		}
		++tr[p].s;
		upd_idx(p,x);
	}

	inline void build(int idx[],int len){
		for(int i=1; i<=len; ++i) insert(idx[i]);
	}

	inline int get_ans(int v){
		int ans=0,p=0;
		for(int i=30; i>=0; --i){
			bool tmp=v>>i&1;
			if(!tr[p].c[tmp]){
				ans|=1<<i;
				p=tr[p].c[tmp^1];
			}
			p=tr[p].c[tmp];
		}
		return ans;
	}

	inline void get_lk_util(int x){
		const int v=val[x];
		int ans=0,p=0;
		int &n1=lk_min[x][1],&n2=lk_min[x][2];
		for(int i=30; i>=0; --i){
			const bool tmp=v>>i&1;
			const bool lim=ans>>i&1;
			if(!lim){
				if(!tr[p].c[tmp]) break;
				p=tr[p].c[tmp];
			}
			else{
				int k=tr[p].c[tmp];
				if(k){
					ans+=tr[k].s;
					merge_idx(k,n1,n2);
				}
				p=tr[p].c[tmp^1];
			}
		}
		merge_idx(p,n1,n2);
		lk_cnt[x]=ans+tr[p].s;
	}

	inline void get_lk(int idx[],int len){
		if(ans>=1e9+5){
			for(int i=1; i<=len; ++i){
				apn(ans,get_ans(val[idx[i]]));
			}
		}
		for(int i=1; i<=len; ++i){
			get_lk_util(val[idx[i]]);
		}
	}
}

inline void solve(){

}

int main(){
	n=nxi();
	init();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
		for(int i=0; i<31; ++i){
			exi[i][val[i]>>i&1]=1;
		}
	}
	if(!get_dif()){
		for(int i=1; i<=n; ++i){
			printf("%d ",i);
		}
		puts("");
		return 0;
	}
	for(int i=1; i<=n; ++i){
		bool tmp=xdif>>i&1;
		idx[tmp][++len[tmp]]=i;
	}
	T::build(idx[0],len[0]);
	T::get_lk(idx[1],len[1]);
	T::clear();
	T::build(idx[1],len[1]);
	T::get_lk(idx[0],len[0]);
	solve();
	for(int i=1; i<=n; ++i){
		printf("%d ",ans[i]);
	}
	puts("");
	return 0;
}
