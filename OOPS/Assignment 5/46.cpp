#include<iostream>
using namespace std;

class A{
  public:
    class Error {
      const char * errMsg;
      public:
      Error(const char * err):errMsg(err){};
      void showErrorMsg(){
        cout<<"===ERROR==="<<endl;
        cout<<errMsg<<endl;
        cout<<"===END==="<<endl;
      }
    };
    void throwExp(){
      throw Error("Got a sample error");
    }
};


int main(){
  A obj; 
  try{
    obj.throwExp();
  }catch(A::Error &obj){
    obj.showErrorMsg();
  }
}
