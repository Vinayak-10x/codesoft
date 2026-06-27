#include <iostream>
using namespace std;
int main(){
    int a,b;
    char op;
    cout<<"Enter 1st operand then operator and then 3rd operand.";
    cin>>a>>op>>b;

    switch(op){
        case '+': cout<<"Addition = " <<a+b << endl; break;
        case '-': cout<< "Subtraction = " <<a-b << endl; break;
        case '*': cout<<"Multiplication = " << a*b << endl; break;
        case '/':
            if (!b ==0){
                cout<<a/b<<endl; break;
            }
            else
                cout<<"Error: division by zero is undefined"<<endl; break;
            
        case '%': cout<< a%b << endl; break;
        default : cout<<"please enter valid operator";
    }
}