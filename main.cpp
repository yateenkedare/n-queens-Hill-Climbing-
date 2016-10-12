#include<iostream>
#include<vector>
#include <chrono>
using namespace std;

int N = 0, max_steps = 0;
void CalculateConflictPairs(int board[], int& conflicts)
{
  conflicts = 0;
  for(int i = 0; i < N; i++)
    for(int j = i+1; j < N; j++)
      if((board[i] == board[j]) || (abs(i-j)==abs(board[i] - board[j])))
        conflicts++;
}

void ConflictsCol(int board[], int &col, int &conflict)
{
  conflict = 0;
  for(int i = 0; i < col; i++)
  {
    if(board[col] == board[i] || abs(col - i) == abs(board[col] - board[i]))
      conflict++;
  }
  for(int i = col+1; i < N; i++)
  {
    if(board[col] == board[i] || abs(col - i) == abs(board[col] - board[i]))
      conflict++;
  }
}

void SolveUsingRandomRestartHillClimbing()
{
  int i,j, currentConflicts, tempConflicts, currentRow, bestSuccessorConflict,bestSuccessorRow,bestSuccessorCol,numberOfRandomRestart=0;
  bool SolutionFound = false;
  int* QueensBoard = new int[N];
  auto begin = std::chrono::high_resolution_clock::now();
  while(!SolutionFound)
  {
    numberOfRandomRestart++;
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
      if(bestSuccessorConflict >= currentConflicts) //local maxima
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
  cout<<"\nNumber of Random Restart  "<<numberOfRandomRestart<<endl;
  delete[] QueensBoard;
}

void SolveUsingMinConflict()
{
  int i,j, currentConflicts =-1, currentRow, tempConflicts, bestSuccessorRow, bestSuccessorConflict,numberOfRandomRestart=0;
  int randomCol,count, colConflicts, tempcolConflicts, lastRandomCol;
  bool SolutionFound = false;
  int* QueensBoard = new int[N];
  auto begin = std::chrono::high_resolution_clock::now();
  while(!SolutionFound)
  {
    if(currentConflicts == 0)
    {
        SolutionFound = true;
        break;
    }
    count = 0;
    numberOfRandomRestart++;
    for(i = 0; i < N; i++)
      QueensBoard[i] = rand() % N;
    CalculateConflictPairs(QueensBoard,currentConflicts);
    while(currentConflicts > 0 && count < max_steps)
    {
      vector<int> cols_with_collisions;
      for (i = 0; i < N; i++)
      {
        ConflictsCol(QueensBoard, i, colConflicts);
        if (colConflicts > 0)
          cols_with_collisions.push_back(i);
      }
      randomCol = cols_with_collisions[rand()%cols_with_collisions.size()];

      count++;
      currentRow = QueensBoard[randomCol];
      ConflictsCol(QueensBoard, randomCol, colConflicts);
      vector<int> successors;
      for(i = 0; i < N; i++)
      {
        QueensBoard[randomCol] = i;
        ConflictsCol(QueensBoard, randomCol, tempConflicts);
        if(tempConflicts < colConflicts)
          successors.push_back(i);
      }
      if(successors.size() > 0)
        QueensBoard[randomCol] = successors[rand()%successors.size()];
      else
        QueensBoard[randomCol] = currentRow;
      CalculateConflictPairs(QueensBoard,currentConflicts);
      /*bestSuccessorConflict = currentConflicts;
      for(i = 0; i < N; i++)    //row
      {
        if(i != currentRow)
        {
          QueensBoard[randomCol] = i;
          CalculateConflictPairs(QueensBoard,tempConflicts);
          if(tempConflicts < bestSuccessorConflict)
          {
            bestSuccessorConflict = tempConflicts;
            bestSuccessorRow = i;
          }
        }
      }
      if(bestSuccessorConflict < currentConflicts)
      {
        QueensBoard[randomCol] = bestSuccessorRow;
        currentConflicts = bestSuccessorConflict;
      }*/
    }
  }
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
  cout<<"\nNumber of Random Restart  "<<numberOfRandomRestart<<endl;
  delete[] QueensBoard;

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
        SolveUsingRandomRestartHillClimbing();
      break;
      case 2:
      {
        cout<<"Enter Max steps :: ";
        cin>>max_steps;
        max_steps *= N;
        SolveUsingMinConflict();
      }
      break;
      default: cout<<"Incorrect input\n";
    }
  }
  return 0;
}
