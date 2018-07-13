#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
const int N=50005;
int n,m,cnt,hx[N],rp[N];
//small heap
//same -> right
struct trp{
	int x,p,sz,ls,rs;
}tr[N*2*17];
struct sgt{
	int l,r,tr;
}sg[N*3];
namespace ask_data{
	int x,y,z;
}

inline void upd(int k){
	tr[k].sz=tr[tr[k].ls].sz+tr[tr[k].rs].sz+1;
}

inline char gtc(){
	static char buf[20000],*h,*t;
	if(h==t){
		t=(h=buf)+fread(buf,1,20000,stdin);
	}
	return *h++;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=gtc())>'9'||c<'0');
	while(x=x*10+c-48,(c=gtc())>='0'&&c<='9');
	return x;
}

inline int mrg(int x,int y){
	if(!x||!y) return x|y;
	if(tr[x].p>tr[y].p) swap(x,y);
	if(tr[x].x>tr[y].x){
		tr[x].ls=mrg(tr[x].ls,y);
	}
	else{
		tr[x].rs=mrg(tr[x].rs,y);
	}
	upd(x);
	return x;
}

void sg_build(int k,int x,int y){
	sg[k]=(sgt){x,y,0};
	int &rtp=sg[k].tr;
	if(x==y){
		tr[rtp=++cnt]=(trp){hx[x],rp[x],1,0,0};
		return;
	}
	int mid=(x+y)>>1;
	sg_build(k<<1,x,mid);
	sg_build(k<<1|1,mid+1,y);
	tr[rtp=++cnt]=(trp){hx[x],rp[x],1,0,0};
	for(int i=x+1;i<=y;++i){
		tr[++cnt]=(trp){hx[i],rp[i],1,0,0};
		rtp=mrg(rtp,cnt);
	}
}

int tp_rnk(int k,int v){
	if(!k) return 0;
	if(tr[k].x>v) return tp_rnk(tr[k].ls,v);
	if(tr[k].x==v) return tr[tr[k].ls].sz;
	return tp_rnk(tr[k].rs,v)+tr[tr[k].ls].sz+1;
}

int sg_rnk(int k){
	using namespace ask_data;
	int l=sg[k].l,r=sg[k].r;
	if(l>=x&&r<=y) return tp_rnk(sg[k].tr,z);
	int ans=0,mid=(l+r)>>1;
	if(x<=mid) ans+=sg_rnk(k<<1);
	if(y>mid) ans+=sg_rnk(k<<1|1);
	return ans;
}

inline int sch(){
	using namespace ask_data;
	int k=z,l=0,r=1e8+1,mid;
	while(l!=r){
		mid=(l+r)>>1;
		if(sg_rnk(1)<k) l=mid+1;
		else r=mid;
	}
	return l;
}

void mod(int k){
	using namespace ask_data;
	int l=sg[k].l,r=sg[k].r;
	if(l==r){
		tr[sg[k].tr].s=y;
		return;
	}

}

int ask_pre(int k){
	using namespace ask_data;

}

int ask_nxt(int k){
	using namespace ask_data;

}

int main(){
	srand(19260817);
	n=nxi(),m=nxi();
	for(int i=1;i<=n;++i){
		rp[i]=rand();
	}
	for(int i=1;i<=n;++i){
		hx[i]=nxi();
	}
	sg_build(1,1,n);
	for(int op,i=1;i<=m;++i){
		using namespace ask_data;
		op=nxi(),x=nxi(),y=nxi();
		switch(op){
			case 1:
				z=nxi();
				printf("%d\n",sg_rnk(1)+1);
				break;
			case 2:
				z=nxi();
				printf("%d\n",sch());
				break;
			case 3:
				mod(1);
				break;
			case 4:
				z=nxi();	
				printf("%d\n",ask_pre(1));
				break;
			case 5:
				z=nxi();
				printf("%d\n",ask_nxt(1));
				break;
		}
	}
	return 0;
}
