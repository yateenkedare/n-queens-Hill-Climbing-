#include<iostream>
#include <chrono>
using namespace std;

int N = 0;
int CalculateConflictPairs(int board[], int& conflicts)
{
  conflicts = 0;
  for(int i = 0; i < N; i++)
    for(int j = i+1; j < N; j++)
      if((board[i] == board[j]) || (abs(i-j)==abs(board[i] - board[j])))
        conflicts++;
}

void SolveUsingRandomRestartHillClimbing()
{
  int i,j, currentConflicts, tempConflicts, currentRow, bestSuccessorConflict,bestSuccessorRow,bestSuccessorCol;
  bool SolutionFound = false;
  int* QueensBoard = new int[N];
  auto begin = std::chrono::high_resolution_clock::now();
  while(!SolutionFound)
  {
    for(i = 0; i < N; i++)
      QueensBoard[i] = rand() % N;
    CalculateConflictPairs(QueensBoard,currentConflicts);
    if(currentConflicts == 0)
      SolutionFound = true;
    while(currentConflicts > 0)
    {
      bestSuccessorConflict = currentConflicts;
      for(i = 0; i < N; i++)
      {
        currentRow = QueensBoard[i];
        for(j = 0; j < N; j++)
        {
          if(QueensBoard[i] != j)
          {
              QueensBoard[i] = j;
              CalculateConflictPairs(QueensBoard,tempConflicts);
              if(tempConflicts < bestSuccessorConflict)
              {
                bestSuccessorConflict = tempConflicts;
                bestSuccessorRow = j;
                bestSuccessorCol = i;
              }
              QueensBoard[i] = currentRow;
          }
        }
      }
      if(bestSuccessorConflict == currentConflicts) //local maxima
      {
        break;
      }
      else
      {
        QueensBoard[bestSuccessorCol] = bestSuccessorRow;
        currentConflicts = bestSuccessorConflict;
      }
      if(bestSuccessorConflict == 0)  //solution found
      {
        SolutionFound = true;
        break;
      }
    }//inner while
  }//outer while
  auto end = std::chrono::high_resolution_clock::now();
  for(i = 0; i < N; i++)
  {
      for(j = 0; j < N; j++)
      {
          if(QueensBoard[i] == j)
            cout<<"Q|";
          else
            cout<<"_|";
      }
      cout<<endl;
  }
  cout<<endl;
  cout << "Solved in " << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()/1000000000.0 << "s";
  delete[] QueensBoard;
}

void SolveUsingMinConflict()
{


}

int main(void)
{
  while(N<4)
  {
    cout<<"Enter N (N>=4) :: ";
    cin>>N;
  }

  int choice = 0;
  srand(time(NULL));
  while(choice < 1 || choice > 2)
  {
    cout<<"Select one of the following  \n\t1. Random Restart Hill Climbing\n\t2. Min Conflict N-Queen\nEnter your choice :: ";
    cin>>choice;
    switch (choice) {
      case 1:
      {
        SolveUsingRandomRestartHillClimbing();
      }
      break;
      case 2:
        SolveUsingMinConflict();
      break;
      default: cout<<"Incorrect input\n";
    }
  }
  return 0;
}
