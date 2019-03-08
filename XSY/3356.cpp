#include <string>
#include <vector>
#include <cstdio>
#include <cassert>
#include "s.hpp"

static const std::string zero49="0000000000000000000000000000000000000000000000000";

static inline std::string split_str(std::string src,int start,int end){
	std::string res="";
	for(int i=start; i<=end; ++i){
		if(res==""&&src[i]=='0') continue;
		res=res+src[i];
	}
	return res==""?"0":res;
}

static inline std::string add_0(std::string src,int len){
	std::string res="";
	int src_sz=src.size();
	for(int i=src_sz; i<len; ++i){
		res+='0';
	}
	return res+src;
}

static std::string minus(std::string a,std::string b){
	std::string s;
	std::reverse(a.begin(),a.end());
	std::reverse(b.begin(),b.end());
	std::vector<int> v(std::max(a.size(),b.size()));
	for(int i=0;i<(int)a.size();++i){
		v[i]+=a[i]-'0';
	}
	for(int i=0;i<(int)b.size();++i){
		v[i]-=b[i]-'0';
	}
	for(int i=0;i+1<(int)v.size();++i){
		if(v[i]<0) --v[i+1],v[i]+=10;
	}
	assert(v.back()>=0);
	while(v.size()&&!v.back()){
		v.pop_back();
	}
	for(int i=0;i<(int)v.size();++i){
		s.push_back(v[i]+'0');
	}
	std::reverse(s.begin(),s.end());
	return s==""?"0":s;
}

static inline void add_3_ans(std::string src,std::vector <std::string> &ans){
	const int src_sz=src.size();
	ans.push_back(split_str(src,std::max(0,src_sz-6),src_sz-5));
	ans.push_back(split_str(src,std::max(0,src_sz-4),src_sz-3));
	ans.push_back(split_str(src,std::max(0,src_sz-2),src_sz-1));
}

std::vector <std::string> guess(int n,int a,int b,int t){
	std::vector <std::string> ans,qry,buk;
	for(int i=0; i<n; ++i){
		qry.push_back("0");
	}
	if(t==1){
		for(int i=0; i<n; ++i){
			qry[i]="1";
			ans.push_back(prod(qry));
			qry[i]="0";
		}
	}
	if(t==2||t==3){
		for(int i=0; (i+1)*3<=n; ++i){
			int cur=i*3;
			qry[cur]="10000",qry[cur+1]="100",qry[cur+2]="1";
			add_3_ans(prod(qry),ans);
			qry[cur]="0",qry[cur+1]="0",qry[cur+2]="0";
		}
		for(int i=n/3*3; i<n; ++i){
			qry[i]="1";
			ans.push_back(prod(qry));
			qry[i]="0";
		}
	}
	if(t==4){
		for(int i=0; i<n; i+=2){
			qry[i]="1"+zero49;
			qry[i+1]="1";
			buk.push_back(prod(qry));
			qry[i]="0";
			qry[i+1]="0";
		}
		for(int base=0; base<16; base+=8){
			std::string times="1";
			for(int i=0; i<8; i+=2){
				qry[base+i]=times;
				times+="00000000";
			}
			std::string res=prod(qry);
			for(int i=0; i<8; i+=2){
				qry[base+i]="0";
			}
			res=add_0(res,24+57);
			for(int i=0; i<8; i+=2){
				std::string last8=split_str(res,res.size()-8,res.size()-1);
				std::string ans0="",ans1="";
				ans1=minus(buk[(base+i)>>1],last8+zero49);
				ans1=add_0(ans1,57);
				ans1=split_str(ans1,ans1.size()-57,ans1.size()-1);
				ans0=minus(buk[(base+i)>>1],ans1);
				ans0=split_str(ans0,0,ans0.size()-49-1);
				if(i<6){
					res=minus(res,ans0);
					res=add_0(res,8);
					res=split_str(res,0,res.size()-8-1);
					res=add_0(res,8);
				}
				ans.push_back(ans0);
				ans.push_back(ans1);
			}
		}
	}
	return ans;
}
