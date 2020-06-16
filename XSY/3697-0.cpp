#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <unistd.h>
#include <sys/mman.h>
#include <set>
typedef long long lint;
const int N=1e5+5;
int n,m,q;
bool used[N];
struct blk{
	int x,id;
	friend bool operator < (const blk &a,const blk &b){
		return a.x<b.x;
	}
};
std::set <blk> s1[N<<1],s2[N<<1];
//s1: x+y=i, s2: y-x+m+1=i

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	char *ibuf;
	struct _Init{
		_Init(){ibuf=(char*)mmap(0,lseek(0,0,SEEK_END),PROT_READ,MAP_PRIVATE,0,0);}
	}_init;
	inline int nxi(){
		int x=0;
		char c;
		while((c=*ibuf++)>'9'||c<'0');
		while(x=x*10-48+c,(c=*ibuf++)>='0'&&c<='9');
		return x;
	}
}
using namespace utils;

void set_blk(int x,int y,int id){
	s1[x+y].insert((blk){x,id});
	s2[y-x+m+1].insert((blk){x,id});
}
void getpre(std::set <blk> ::iterator &it,std::set <blk> &st,const int x){
	if(st.size()==2){
		it=st.begin(); return;
	}
	it=st.upper_bound((blk){x,0});
	--it;
	while(used[it->id]) st.erase(it--);
}
void getnxt(std::set <blk> ::iterator &it,std::set <blk> &st,const int x){
	if(st.size()==2){
		it=st.end(),--it; return;
	}
	it=st.upper_bound((blk){x,0});
	while(used[it->id]) st.erase(it++);
}

int solve0_1(int &x,int &y,int &d,int &q,std::set <blk> ::iterator it){//d->1
	int ans=x-it->x*2;
	y+=ans,x-=ans,d=1;
	if(it->id) --q,used[it->id]=1;
	return ans;
}
int solve0_2(int &x,int &y,int &d,int &q,std::set <blk> ::iterator it){//d->3
	int ans=x-it->x*2+1;
	y+=ans,x-=ans,d=3;
	if(it->id) --q,used[it->id]=1;
	return ans;
}
int solve1_1(int &x,int &y,int &d,int &q,std::set <blk> ::iterator it){//d->0
	int ans=it->x*2-x-2;
	y+=ans,x+=ans,d=0;
	if(it->id) --q,used[it->id]=1;
	return ans;
}
int solve1_2(int &x,int &y,int &d,int &q,std::set <blk> ::iterator it){//d->2
	int ans=it->x*2-x-1;
	y+=ans,x+=ans,d=2;
	if(it->id) --q,used[it->id]=1;
	return ans;
}
int solve2_1(int &x,int &y,int &d,int &q,std::set <blk> ::iterator it){//d->3
	int ans=it->x*2-x-2;
	y-=ans,x+=ans,d=3;
	if(it->id) --q,used[it->id]=1;
	return ans;
}
int solve2_2(int &x,int &y,int &d,int &q,std::set <blk> ::iterator it){//d->1
	int ans=it->x*2-x-1;
	y-=ans,x+=ans,d=1;
	if(it->id) --q,used[it->id]=1;
	return ans;
}
int solve3_1(int &x,int &y,int &d,int &q,std::set <blk> ::iterator it){//d->2
	int ans=x-it->x*2;
	y-=ans,x-=ans,d=2;
	if(it->id) --q,used[it->id]=1;
	return ans;
}
int solve3_2(int &x,int &y,int &d,int &q,std::set <blk> ::iterator it){//d->0
	int ans=x-it->x*2+1;
	y-=ans,x-=ans,d=0;
	if(it->id) --q,used[it->id]=1;
	return ans;
}

void oput_set(std::set <blk> &st){
	for(std::set <blk> ::iterator it=st.begin(); it!=st.end(); ++it){
		eprintf("(x%d id%d),",it->x,it->id);
	}
	eprintf("\n");
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("d.in","r",stdin);
#endif
	m=nxi(),n=nxi(),q=nxi();
	for(int i=1; i<=q; ++i){
		int x=nxi(),y=nxi();//右上角
		set_blk(x,y,i);
	}
	for(int i=0; i<=m+1; ++i){
		set_blk(i,0,0),set_blk(i,n+1,0);
	}
	for(int i=1; i<=n; ++i){
		set_blk(0,i,0),set_blk(m+1,i,0);
	}
	//向左上，右上，右下，左下走,点坐标*2
	lint ans=0;
	for(int x=m,y=0,d=0; q;){//考虑get整体-1
		std::set <blk> ::iterator i1,i2;
		assert(x<=m*2&&x>=0&&y<=n*2&&y>=0);
		//eprintf("x%d y%d %d\n",x,y,d);
		if(d==0){
			getpre(i1,s1[(x+y)/2+1],x/2);//d->1
			getpre(i2,s1[(x+y)/2+2],x/2);//d->3
			if(i1->x>=i2->x){
				ans+=solve0_1(x,y,d,q,i1);
			}else{
				ans+=solve0_2(x,y,d,q,i2);
			}
		}else if(d==1){
			getnxt(i1,s2[((y-x)>>1)+m+1],x/2+(x&1));//d->0
			getnxt(i2,s2[((y-x)>>1)+m+2],x/2+(x&1));//d->2
			if(i1->x<=i2->x){
				ans+=solve1_1(x,y,d,q,i1);
			}else{
				ans+=solve1_2(x,y,d,q,i2);
			}
		}else if(d==2){
			getnxt(i1,s1[(x+y)/2+2],x/2+(x&1));//d->3
			getnxt(i2,s1[(x+y)/2+1],x/2+(x&1));//d->1
			if(i1->x<=i2->x){
				ans+=solve2_1(x,y,d,q,i1);
			}else{
				ans+=solve2_2(x,y,d,q,i2);
			}
		}else if(d==3){
			getpre(i1,s2[((y-x)>>1)+m+2],x/2);//d->2
			getpre(i2,s2[((y-x)>>1)+m+1],x/2);//d->0
			if(i1->x>=i2->x){
				ans+=solve3_1(x,y,d,q,i1);
			}else{
				ans+=solve3_2(x,y,d,q,i2);
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
}
