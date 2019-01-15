#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
const int N=1e5+5;
const int S=320;
int n,val[N],lis[N],invlis[N];
bool type;

template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}
template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}
bool cmp_val(int x,int y){
	return val[x]<val[y];
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void make_lis(int st,int ed,const int step,int lis[]){
	static int buk[N];
	int pt=lis[st]=1;
	for(int i=st; i!=ed; i+=step){
		int l=0,r=pt,mid;
		while(l!=r){
			mid=(l+r)>>1;
			if(buk[mid]==val[i]||((buk[mid]<val[i])==(step<0))) r=mid;
			else l=mid+1;
		}
		if(l==pt) buk[pt++]=val[i];
		else buk[l]=val[i];
		lis[i]=l;
	}
}

inline void make_invlis(int st,int ed,const int step,int lis[]){
	static int buk[N];
	int pt=1;
	buk[0]=1e9+5;
	for(int i=st; i!=ed; i+=step){
		int l=0,r=pt,mid;
		while(l!=r){
			mid=(l+r)>>1;
			if(buk[mid]>val[i]) l=mid+1;
			else r=mid;
		}
		if(l==pt) buk[pt++]=val[i];
		else buk[l]=val[i];
		lis[i]=l;
	}
}

namespace D{
	int pt,mp[N];
	inline void ins(const int v){
		mp[pt++]=v;
	}
	inline void build(){
		std::sort(mp,mp+pt);
		pt=std::unique(mp,mp+pt)-mp;
	}
	inline int ask(const int v){
		return std::lower_bound(mp,mp+pt,v)-mp+1;
	}
}

namespace B{
	int cnt_blk,idx[S][S+5],blkans[S][S];
	std::vector <int> stt[S];//one less

	inline void build(){
		static int buk[N];
		const int remain=(n-1)%S+1;
		int pt_buk=0;
		++cnt_blk;
		for(int i=1,j=1; i<=n; ++i,++j){
			if(j==S+1) j=1,++cnt_blk;
			idx[cnt_blk][j]=i;
		}
		for(int i=1; i<cnt_blk; ++i){
			std::sort(idx[i]+1,idx[i]+S+1,cmp_val);
		}
		std::sort(idx[cnt_blk]+1,idx[cnt_blk]+remain+1,cmp_val);

		for(int i=1; i<=cnt_blk; ++i){
			blkans[i][cnt_blk+1]=blkans[i-1][cnt_blk+1];
			for(int j=i==S*i+(i==cnt_blk?remain:S); j>S*i; --j){
				apx(blkans[i][cnt_blk+1],lis[j]);
				apx(pt_buk,lis[j]);
				apn(buk[lis[j]],val[j]);
			}
			int ans=blkans[i][cnt_blk+1];
			for(int j=1; j<=pt_buk; ++j){
				stt[i].push_back(buk[j]);
			}
			for(int j=n; j>=S*i; --j){
				if(j%S==0){
					blkans[i][j/S+1]=ans;
				}
				int l=1,r=pt_buk,mid;
				while(l!=r){
					mid=(l+r)>>1;
					if(buk[mid]>val[j]) r=mid;
					else l=mid+1;
				}
				apx(ans,l-1+invlis[j]);
			}
		}
	}

	inline int solve(const int l,const int r){
		static bool mark_l[N],mark_r[N];
		//need tweak
		//fixed once
		const int bel_l=(l-1)/S+1,bel_r=(r-1)/S+1;
		const int lim_l=bel_l==cnt_blk?(n-1)%S+1:S;
		const int lim_r=bel_r==cnt_blk?(n-1)%S+1:S;
		int ans=blkans[bel_l-1][bel_r+1];
		int pt_l=(bel_l-1)*S+1,pt_r=(bel_r-1)*S+lim_r;

		for(int i=r; i<=pt_r; ++i){
			mark_r[i]=1;
			int pos=std::upper_bound(stt[bel_l-1].begin(),stt[bel_l-1].end(),val[i])-stt[bel_l-1].begin();
			apx(ans,invlis[i]+pos);
		}
		for(int i=pt_l; i<=l; ++i){
			mark_l[i]=1;
		}
		for(int i=1,j=1; i<=lim_l&&j<=lim_r; ++j){
			const int x=idx[bel_r][j];
			if(!mark_r[x]) continue;
			for(; i<=lim_l&&(!mark_l[idx[bel_l][i]]||val[idx[bel_l][i]]<val[x]); ++i){
				if(mark_l[idx[bel_l][i]]){
					apx(ans,lis[idx[bel_l][i]]+invlis[x]);
				}
			}
		}
		for(int i=r; i<=pt_r; ++i) mark_r[i]=0;
		for(int i=pt_l; i<=l; ++i) mark_l[i]=0;
		return ans;
	}
}

int main(){
	n=nxi(),type=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
		D::ins(val[i]);
	}
	D::build();
	for(int i=1; i<=n; ++i){
		val[i]=D::ask(val[i]);
	}
	//undone?
	make_lis(1,n+1,1,lis);
	make_invlis(n,0,-1,invlis);
	B::build();
	for(int ans=0,q=nxi(); q; --q){
		int l=nxi(),r=nxi();
		if(type) l^=ans,r^=ans;
		printf("%d\n",ans=B::solve(l-1,r+1));
	}
	return 0;
}
