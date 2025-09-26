#include <iostream>
#include <fstream>
using namespace std;


int main(){  
  ifstream input_file("pordenes.txt");
  if(!input_file.is_open()){
      cout <<"Error: file cannot be opened" << endl;
      return 1;
  }

  return 0;
}
