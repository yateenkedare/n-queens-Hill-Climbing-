using namespace std;
class randomRestartHillClimbing{
public:
  int N;
  void solve(int inputSize)
  {
    N = inputSize;
    srand(time(NULL));
    hillClimbing();
  }
private:
  int calcHeuristic(int col, int row, int board[])
  {
    int h= 0;
    for(int i = col+1; i < N; i++)
    {
      if(row == board[i] || ( abs(col-i) == abs(row - board[i]) ) )
        h+=1;
    }
    return h;
  }

  void hillClimbing()
  {
    //cout<<"\n Random Restart\n";
    int board[N] = {};
    for(int i = 0; i < N; i++)
    {  board[i] = rand() % N;
     //cout<<board[i]<<"  ";
    }

    int boardHeuristic;
    for(int i = 0; i < N-1; i++)
      boardHeuristic+=calcHeuristic(i,board[i],board);

    if(boardHeuristic == 0)
    {
      cout<<"Solution Found\n";
      for(int i = 0; i < N; i++)
        cout<<board[i];
    }
    int bestSuccessorHeuristic;
    int SuccessorHeuristic = 0;
    int bestSuccessorCol = -1;
    int bestSuccessorRow = -1;
    while(boardHeuristic != 0)
    {
      bestSuccessorHeuristic = boardHeuristic;
      for(int col = 0; col < N; col++)    //iterating through cols
      {
        for(int row = 0; row < N; row++)      //swapping rows
        {
          SuccessorHeuristic = 0;
          if(row != board[col])
          {
            for(int i = 0; i < N; i++)
              SuccessorHeuristic+=calcHeuristic(i,row,board);

      //      cout<<"\nSuccessor heuristic  col::"<<col<<"  row::"<<row<<"  SH::"<<SuccessorHeuristic;
            if(SuccessorHeuristic < bestSuccessorHeuristic)
            {
              bestSuccessorHeuristic = SuccessorHeuristic;
              bestSuccessorCol = col;
              bestSuccessorRow = row;
            }
          }
        }
      }
      if(bestSuccessorHeuristic == 0)
      {
        board[bestSuccessorCol] = bestSuccessorRow;   //placing the queen in position
        boardHeuristic = bestSuccessorHeuristic;
        cout<<"\nSolution ::\n";
        for(int i=0;i<N;i++)
        {
          cout<<board[i]<<"  ";
        }
        return;
      }
      if(bestSuccessorHeuristic == boardHeuristic)
      {
        hillClimbing();                               //random restart
        return;
      }
      else
      {
        board[bestSuccessorCol] = bestSuccessorRow;   //placing the queen in position
        boardHeuristic = bestSuccessorHeuristic;
      }

      // cout<<"\nNext board Position\n";
      // for(int i=0;i<N;i++)
      // {
      //   cout<<board[i]<<"  ";
      // }
    }

  }
}RRHC;
