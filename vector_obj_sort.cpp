#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


class obj{
    public :
    int a,b,c;
    obj(){
        a=0,b=0;c=0;
    }
    obj(int aa, int bb, int cc){
        a=aa,b=bb,c=cc;
    }
    // comparator inside the DS
    bool operator <(const obj& objobj) const
    {
    return b > objobj.b;
    }
};



int main(){

    int a,b,c;
    vector<obj> p;
    for(int i = 0; i <3; i++){
        cin>>a>>b>>c;
        obj* ptr = new obj(a,b,c);
        
        //implicit address convertion
        p.push_back(*ptr);

    }

    // global comparator can also be created
    sort(p.begin(), p.end());

    for(obj i : p){
        cout<<i.a<<"\n";
    }


}
