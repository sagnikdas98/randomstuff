#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <vector>
#include <boost/algorithm/string.hpp> 
using namespace std;

int main() 
{
        
    char *  s;
    vector<string> fields; 

    fstream myfile("input.txt",ios_base::in);
    fstream omyfile("output.txt",ios_base::out);

    while (myfile.getline(s,20)) {
        
        boost::split(fields, s, boost::is_any_of(" "));

        if (fields.size() == 2) {
            omyfile<<"LD R0, "<<fields[1]<<endl;
            omyfile<<"ST "<<fields[0]<<", R0"<<endl;
        } 
        else if (fields.size() == 4) {

            omyfile<<"LD R0, "<<fields[1]<<endl;

            switch (fields[2][0]) {
                case '+':
                    omyfile<<"ADD R0, "<<fields[3]<<endl;
                    break;
                case '-':
                    omyfile<<"SUB R0, "<<fields[3]<<endl;
                    break;
                case '*':
                    omyfile<<"MUL R0, "<<fields[3]<<endl;
                    break;
                case '/':
                    omyfile<<"DIV R0, "<<fields[3]<<endl;
                    break;
                default:
                    omyfile<<"Unsupported Operator"<<endl;;
            }
            omyfile<<"ST "<<fields[0]<<", R0"<<endl;
        }
    }
    myfile.close();
    omyfile.close();
   
}


/*
>>> cat input.txt
T1 -B
T2 C + D
T3 T1 + T2
A T3
