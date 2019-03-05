#include<iostream>
#include<stdlib.h>
#include<vector>
#include<queue>
#include<fstream>

using namespace std;
class process{
    public :
    int pid, bt, at;
    static int quant, clk;
    process(int a,int c, int b){
    pid = a;
    bt = b;
    at = c;
    } 
};
int process::clk=0;
int process::quant=1;
int main(){

    vector<process> pp;
    int ia,ib,ic,p=0,n,vi=1;
    process* temp;

    std::fstream myfile("inpu.txt", std::ios_base::in);
    myfile>>n;
    for(int i = 0; i <n; i++){
        myfile>>ib>>ic;
        pp.push_back(*(new process(i+1,ib,ic)));
    }
    myfile>>ia;
    pp[0].quant = ia;

    queue<process> qq;
    qq.push(pp[0]);



    cout<<"Process order:"<<endl;

    while(!qq.empty()){

        temp = &(qq.front());
        cout<<(*temp).pid<<"-> ";
        
        if((*temp).bt >= (*temp).quant){
            (*temp).bt-=(*temp).quant;
            (*temp).clk+=(*temp).quant;
            if((*temp).bt > 0) 
                qq.push(*temp);
            qq.pop();
        }
        else{
            (*temp).clk+=(*temp).bt;
            qq.pop();
        }

        while((vi < n) && ((*temp).clk >= pp[vi].at)){
            qq.push(pp[vi]);
            vi++;
        }
        
    }
    return 0;
}
