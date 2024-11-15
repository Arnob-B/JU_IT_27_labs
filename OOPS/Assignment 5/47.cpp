#include<iostream>
using namespace std;
#define maxi 5
class Overflow{
  const char * msg;
  public:
  Overflow():msg("overflowed"){};
    void showMsg(){
        cout<<"===ERROR==="<<endl;
        cout<<msg<<endl;
        cout<<"===END==="<<endl;
    }
};
class Underflow{
  const char * msg;
  public:
  Underflow():msg("underflowed"){};
    void showMsg(){
        cout<<"===ERROR==="<<endl;
        cout<<msg<<endl;
        cout<<"===END==="<<endl;
    }
};
class Stack{
  int top;
  int data[maxi];
  public:
  Stack(){
    top = -1;
  }
  void push(int a){
    if(top == maxi-1) throw Overflow();
    data[++top]=a;
  };
  int pop(){
    if(top <= -1) throw Underflow();
    return data[top--];
  };
  int show_top(){
    return data[top];
  }
};



int main(){
  Stack s;
  try{
    s.push(1);
    s.push(1);
    s.push(1);
    s.push(1);
    s.push(1);
    s.push(1);
  }catch(Overflow &ob){
    try{
      ob.showMsg();
      s.pop();
      s.pop();
      s.pop();
      s.pop();
      s.pop();
      s.pop();
      s.pop();
      s.pop();
    }catch(Underflow &ob){
      ob.showMsg();
    }
  }
}
