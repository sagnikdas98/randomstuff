#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class example{

    public :
    int a,b,c;

    example(int aa, int bb, int cc){
        a=aa;
        b=bb;
        c=cc;
    }

    bool operator <(example obj) const {
        return (b <  obj.b);
    }
};


//bool cmp(example oa, example ob){
    //return (oa.b < ob.b); }


int main(){

    int ia,ib,ic;

    vector<example> p;

    for(int i = 0; i <3; i++){

        cout<<"Enter for object: "<<(i+1)<<"\n";
        cin>>ia>>ib>>ic;
        p.push_back(*(new example(ia,ib,ic)));
    }

    sort(p.begin(), p.end());
    //sort(p.begin(), p.end(),cmp);

    for(example i : p){
        cout<<i.a<<"\n";
    }


}
