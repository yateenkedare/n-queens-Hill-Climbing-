#include<iostream>
#include"RandomRestartHillClimbing.h"
#include "cspNQueen.h"

int main(void)
{
  int N;
  cout<<"Enter N :: ";
  cin>>N;

  cout<<"Select one of the following  \n\t1. Random Restart Hill Climbing\n\t2. CSP N-Queen\nEnter your choice :: ";
  int choice;
  cin>>choice;
  if(choice == 1)
  {
    RRHC.solve(N);
  }
  else if(choice == 2)
  {

  }
  return 0;
}
