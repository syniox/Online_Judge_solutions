#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <thread>
#include <cmath>
#include <unistd.h>
const int N=28;
int n,q,sampl_ans[50005];
//smp->sample
int cnt_ans,ans_img[50005];

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

struct img{
	double x[N][N];

	img operator - (const img &b) const {
		img c;
		for(int i=0; i<N; ++i){
			for(int j=0; j<N; ++j){
				c.x[i][j]=fabs(x[i][j]-b.x[i][j]);
			}
		}
		return c;
	}
	void read(){
		for(int i=0; i<N; ++i){
			for(int j=0; j<N; ++j){
				scanf("%lf",&x[i][j]);
			}
		}
	}
	void sanitize(){
		double max_psnr=0;
		for(int i=0; i<N; ++i){
			for(int j=0; j<N; ++j){
				apx(max_psnr,x[i][j]);
			}
		}
		if(max_psnr<1e-8) return;
		for(int i=0; i<N; ++i){
			for(int j=0; j<N; ++j){
				x[i][j]/=max_psnr;
			}
		}
	}
	double psnr(){
		double _sum=0;
		for(int i=0; i<N; ++i){
			for(int j=1; j<N; ++j){
				_sum+=x[i][j];
			}
		}
		double _mean=_sum/(N*N);
		double _mse=0;
		for(int i=0; i<N; ++i){
			for(int j=0; j<N; ++j){
				_mse+=(x[i][j]-_mean)*(x[i][j]-_mean);
			}
		}
		_mse=_mse/(N*N);
	return 10*log10(1/_mse);
	}
}org_img[50005],data_img[50005];

void build(const int idx,const int l,const int r){
	for(int i=l; i<=r; ++i){
		img cur_img=data_img[i];
		cur_img.sanitize();
		double max_psnr=-1;
		int ans=-1;
		for(int j=1; j<=n; ++j){
			img dif=cur_img-org_img[j];
			double tp=dif.psnr();
			if(tp>max_psnr){
				ans=j,max_psnr=tp;
			}
		}
		ans_img[i]=sampl_ans[ans];
		if(i%100==0){
			std::cerr<<"thread "<<idx<<": "<<i<<" done.\n";
		}
	}
	++cnt_ans;
}

int main(){
	memset(ans_img,-1,sizeof(ans_img));
	std::fstream nx_sampl;
	std::fstream nx_ans;
	std::fstream nx_data;
	nx_sampl.open("training.in");
	nx_ans.open("training.out");
	nx_data.open("test.in");

	freopen("test-th.out","w",stdout);

	n=20000;
	q=10000;

	for(int i=1; i<=n; ++i){
		for(int j=0; j<28; ++j){
			for(int k=0; k<28; ++k){
				nx_sampl>>org_img[i].x[j][k];
			}
		}
		org_img[i].sanitize();
		nx_ans>>sampl_ans[i];
	}
	for(int i=1; i<=q; ++i){
		for(int j=0; j<28; ++j){
			for(int k=0; k<28; ++k){
				nx_data>>data_img[i].x[j][k];
			}
		}
	}
	std::thread t1(build,1,1,q>>1);
	t1.detach();
	std::thread t2(build,2,(q>>1)+1,q);
	t2.detach();
	while(cnt_ans!=2) sleep(1);
	for(int i=1; i<=q; ++i){
		printf("%d\n",ans_img[i]);
	}
	return 0;
}
