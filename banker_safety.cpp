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

  static int resrcN;
	static vector<int> available;
	
	process(int id){
		pid = id;
    fin = false;
		}	

  void readinputAlloc(int resrc){
      allocated.push_back(resrc);
    }
  void readinputMax(int resrc){
      maxalloc.push_back(resrc);
      
    }
  void calcneed(){
    for(int i=0; i< resrcN; i++)
      need.push_back(maxalloc[i] - allocated[i]);
  }

  static void readinputAvail(int ele){
    available.push_back(ele);
  }

  bool allocatethis(){
    fin = true;
    for(int i: available){
      available[i] += allocated[i];
     
    }
    cout<<pid<<endl;
    return true;
  }

  bool trythis(){
    if(!fin){

      for(int i:available){
        if(available[i] < need[i])
        return false;
      }
      return allocatethis();
    }
    return false;
  }
};

int process::resrcN = 0;
vector<int> process::available;
vector<process*> pp;




int main(){

	int n,m,ele;

	fstream myfile("inpu.txt",ios_base::in);
	myfile>>n>>m;

  process::resrcN = m;

  for(int i = 0; i< n; i++){
    pp.push_back(new process(i+1));
    for(int j=0; j<m; j++){
      myfile>>ele;
      pp[i]->readinputAlloc(ele);
    }
    }

  for(int i = 0; i<n; i++){
    for(int j=0; j<m; j++){
      myfile>>ele;
      pp[i]->readinputMax(ele);
    }
    pp[i]->calcneed();
    }
  for(int j=0; j<m; j++){
      myfile>>ele;
      process::readinputAvail(ele);
    }
for(int i =0;i<n;i++)
for(vector<process*>::iterator p = pp.begin(); p != pp.end(); p++ ){

    if((*p)->trythis()){
      pp.erase(p);
      break;
      }
}

if(pp.empty())
  cout<<"Valid Sequence";
else cout<<"invalid";
}
