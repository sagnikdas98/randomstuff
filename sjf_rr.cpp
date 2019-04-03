#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<algorithm>
#include<stdlib.h>
using namespace std;

class process{
    public:
    int pid, at,bt,wt,tat, sbt;
    static int clk, quant, totaltat, totalwt;

    process(int a, int b, int c){
        pid = a;
        at = b;
        bt = c;
        sbt = c;
        wt = -bt;
    }
    void calc(){
        tat= clk - at;
        wt += tat;
        totaltat += tat;
        totalwt += wt;
    }
};

int process::clk = 0;
int process::quant = 2;
int process::totaltat = 0;
int process::totalwt = 0;

bool cmp( process* a, process* b){
    return(a->bt < b->bt);
}

vector<process*> pp;

void display(int n){
    cout<<"\nPID\tAT\tBT\tTAT\tWT"<<endl;
    for(int i=0; i< n; i++){
        cout<<pp[i]->pid<<"\t"<<pp[i]->at<<"\t"<<pp[i]->sbt<<"\t"<<pp[i]->tat<<"\t"<<pp[i]->wt<<endl;
    }
    cout<<"Avg TAT : "<<(process::totaltat)/n<<endl;
    cout<<"Avg WT : "<<(process::totalwt)/n<<endl;
}

void sjf(int n){

    int vi = 0;
    vector<process*> qq;
    process *temp;

    while(!qq.empty() || vi<n){

        while((vi<n) && process::clk >= pp[vi]->at)
                qq.push_back(pp[vi++]);

		if(qq.size()>1)	
            sort(qq.begin(), qq.end(), cmp);
        if(!qq.empty()){
            temp = qq[0];
            process::clk += temp->bt;
            temp->calc();
            qq.erase(qq.begin());
            cout<<temp->pid<<"->";
        }
    }
    display(n);
}

void rr(int n){

    int vi = 0;
    queue<process*> qq;
    process *temp;

    while(!qq.empty() || vi<n){

        while((vi<n) && (process::clk>=pp[vi]->at))
            qq.push(pp[vi++]);

        if(!qq.empty()){
            
            temp = qq.front();

            if(temp->bt > process::quant){
                qq.pop();
                temp->bt -= process::quant;
                process::clk += process::quant;
                qq.push(temp);
            }
            else{
                process::clk += temp->bt;
                temp->calc();
                qq.pop();
            }
            cout<<temp->pid<<"->";
        }
    }
    display(n);
}

int main(){
    int n,iat,ibt;
    fstream myfile("inpu.txt", ios_base::in);
    myfile>>n;

    for(int i=0; i< n; i++){
        myfile>>iat>>ibt;
        pp.push_back(new process(i+1,iat, ibt));
    }

    myfile>>iat>>ibt;

    if(iat==0)
        sjf(n);
    else{
        process::quant = ibt;
        rr(n);
    }
}
