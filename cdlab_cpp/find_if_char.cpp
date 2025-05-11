#include<iostream>
#include<vector>
#include<string>

using namespace std;

int main(){

    vector<string> strings;
    //string str = "Singh555";
    int count = 0;
    vector<string> havenum;
    for(int i = 0;i < strings.size();i++){
        for(int j = 0;j< strings[i].length();j++){
            if(isdigit(strings[i].at(j))){
                havenum.push_back(strings[i]);
                break;
            }
        }
    }
}