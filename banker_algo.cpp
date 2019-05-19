#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

class process{
    
    public:
    int pid;
    bool fin;

    vector<int> allocated;
    vector<int> maxalloc;
    vector<int> need;

    static bool checkRequest;
    static int resrcN;
    static vector<int> available;
    static vector<int> request;
	
    process(int id){
        pid = id;
        fin = false;
    }	

    void calcneed(){
        for(int i=0; i< resrcN; i++)
        need.push_back(maxalloc[i] - allocated[i]);
    }

    bool allocatethis(){
        fin = true;
        for(int i=0; i< resrcN; i++)
            available[i] += allocated[i];
        cout<<pid<<endl;
        return true;
    }
 
    bool trythis(){
        if(!fin){

            for(int i=0; i< resrcN; i++)
                if(available[i] < need[i])
                    return false;
            return allocatethis();
        }
        return false;
    }

    void checkreq(){

        checkRequest=true;
        for(int i=0; i< resrcN; i++)
            if(request[i]>need[i]){
                checkRequest = false;
                cout<<"Request Not Possible"<<endl;
                break;
            }
    }

    void tryrequest(){ 

        if(checkRequest){
            for(int i=0; i< resrcN; i++)
                if(request[i]>available[i])
                    return;
            for(int i=0; i< resrcN; i++){ 
                available[i]-=request[i];
                allocated[i] += request[i]; 
                need[i] -= request[i];
            }
            checkRequest = false;
            cout<<"Request Satisfied"<<endl;
        }
    }

};


bool process::checkRequest = false;
int process::resrcN = 0;

vector<int> process::available;
vector<int> process::request;
vector<process*> pp;
process *temp = NULL;




int main(){

    int n,m,ele;

    fstream myfile("inpu.txt",ios_base::in);
    myfile>>n>>m;

    process::resrcN = m;

    for(int i = 0; i< n; i++){
        pp.push_back(new process(i+1));
        for(int j=0; j<m; j++){
            myfile>>ele;
            pp[i]->allocated.push_back(ele);
        }
    }

    for(int i = 0; i<n; i++){
        for(int j=0; j<m; j++){
            myfile>>ele;
            pp[i]->maxalloc.push_back(ele);
        }
        pp[i]->calcneed();
    }

    for(int j=0; j<m; j++){
        myfile>>ele;
        process::available.push_back(ele);
    }


    myfile>>ele;
    if(ele>0);
        temp = pp[ele-1];

    for(int j=0; j<m; j++){
        myfile>>ele;
        process::request.push_back(ele);
    }

    temp->checkreq();

    for(int i =0;i<n;i++){

        temp->tryrequest();
        for(vector<process*>::iterator p = pp.begin(); p != pp.end(); p++ ){

            if((*p)->trythis()){
                pp.erase(p);
                break;
            }
        }
    }
    if(pp.empty())
        cout<<"Valid Sequence";
    else cout<<"invalid";
}
