#include<iostream>
#include<vector>
#include<string>
#include<stdlib.h>
#include<ctype.h>

using namespace std;
#define max_prod 10

//traeting # as epsilon :
struct production{
    public:char nT;
    public: vector<string> rhs;
    public:vector<char> first;
};

void find_first(production pro,production prod[]){
    for(string str : pro.rhs){
        int curr = 0;
    if(!isalpha(str.at(curr))){
        prod[pro.nT].first.push_back(str.at(curr));
    }
    else{
        find_first(prod[str.at(curr)],prod);
        for(char c : prod[str.at(curr)].first){
            if(prod[pro.nT].first.size() == 0 || prod[pro.nT].first.back() != c){
                prod[pro.nT].first.push_back(c);
            }
            if(c != '#'){
                //if(find(pro.first.begin(),pro.first.end(),c) == pro.first.end()){
                 //prod[pro.nT].first.push_back(c);
                //}
            }
            else{
                if( !isalpha(str.at(curr+1)) && c == '#'){
                    curr++;
                    prod[pro.nT].first.push_back(str.at(curr));
                }
            }
        }
        //prod[pro.nT].first.insert(prod[pro.nT].first.end(),prod[str
        //.at(0)].first.begin(),prod[str.at(0)].first.end());

    }
    }
}

int main(){
    int n;
    cout<<"Enter the no of productions :";
    cin>>n;
    if(n > max_prod){
        cout<<"max prod limit exceed : ";
        return 0;
    }
   
    production prod[n];
    
    for(int i = 0;i<n;i++){
        cout<<"Enter the nonterminal :"<<endl;
        cin>>prod[i].nT;
        int numProd; // no of productions for each non terminal
        cout<<"Enter the no. of productions for nT : "<<prod[i].nT<<endl;
        cin>>numProd;
        for(int j = 0;j < numProd; j++){
            string str;
            cout<<prod[i].nT<<" -> ";
            cin>>str;
            prod[i].rhs.push_back(str);
        }
    }

    for(int i = 0;i < n;i++){
        find_first(prod[i],prod);
    }
    for(int i = 0;i < n;i++){
        cout<<"First : "<<prod[i].nT;
        for(int j = 0;j < prod[i].first.size();j++){
            cout<<prod[i].first.at(j);
            if(prod[i].rhs.size() - j > 1) cout<<",";
        }
        cout<<endl;
    }
    return 0;
}