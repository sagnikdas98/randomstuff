#include<iostream>
#include<stdlib.h>
#include<vector>
#include<queue>
#include<fstream>
#include<algorithm>

using namespace std;

class process{
    public :
    int pid, at, bt,tat,wt;
    static int quant, clk, totalwt, totaltat;
    process(int a,int c, int b){
    pid = a;
    at = b;
    bt = c;
	tat = -1;
	wt = -bt;
    } 

	bool operator <(process obj) const {
        return (bt <  obj.bt);
    }
	void calcother(){
		tat = clk - at;
		wt += tat;
		totaltat += tat;
		totalwt += wt;
	}
};

int process::clk=0;
int process::totaltat=0;
int process::totalwt=0;
int process::quant=1;

int main(){

    vector<process*> pp;
    int ia,ib,ic,p=0,n,vi=0;

    process* temp;

    fstream myfile("inpu.txt", ios_base::in);
    myfile>>n;

    for(int i = 0; i <n; i++){
        myfile>>ib>>ic;
        pp.push_back((new process(i+1,ib,ic)));
    }
    myfile>>ia;
    process::quant = ia;

    queue<process*> qq;

    cout<<"Process order:"<<endl;

    while(vi < n || !qq.empty() ){

        
		while((vi < n) && (process::clk >= pp[vi]->at)){
            qq.push(pp[vi]);
            vi++;
        }
		sort(qq.front(), qq.back());

        temp = qq.front();
		process::clk += (*temp).bt;
		(*temp).calcother();
		qq.pop(); 
		cout<<(*temp).pid<<endl;      
    }

	cout<<"Avg TAT & Avg WT:"<<(process::totaltat)/n<<", "<<(process::totalwt)/n<<endl;

    return 0;
}
