#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
using namespace std;

int main () {
  ofstream myfile;
  myfile.open ("data.txt");
  myfile << "Writing this to a file.\n";
  myfile.close();
  return 0;
}
