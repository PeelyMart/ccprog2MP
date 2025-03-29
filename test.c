#include <stdio.h>


int luckyWin(int board[][3], int player){
  for(int i = 0; i < 3; i++){
    if(board[i][0] == player && board[i][1] == player &&  board[i][2] == player){
      return 1;
    }
    if(board[0][i] == player && board[1][i] == player &&  board[2][i] == player){
      return 1;
    }
  }
  if(board[0][0] == player && board[1][1] == player && board[2][2] == player){
      return 1;
    }
  if(board[0][2] == player && board[1][1] == player && board[2][0] == player){
      return 1;
    }
  return 0;

}


int winCheck(int board[][3], int *type){
  int luckyOne = luckyWin(board, 1); 
  int winOne = 0;
  int luckyTwo = luckyWin(board, 2);
  int winTwo = 0; 
  if(luckyOne != luckyTwo){
    if(luckyOne == 1){
      *type = 1;
      return 1;
    }
    if(luckyTwo == 1){
      *type =1;
      return 2;
    }
  }
  else if(luckyOne == luckyTwo){ //if both have a lucky win or if both dont
    for(int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++){
        if(board[i][j] == 1){
          winOne++;
        }
        if(board[i][j] == 2){
          winTwo++;
        }
      }
    }
    if(winOne > winTwo){
      *type = 2; //type 2 win - majority win
      return 1;
    }
    if(winOne < winTwo){
      *type = 2; 
      return 2;
    } 
  }
  else {
    *type = 3; //draw type
    return 0; //draw

  }
  return 0;
}



int ElementalAffinity(int x, int y){
  int matrix[8][8] = {
    {3, 2, 1, 1, 3, 3, 1, 2},
    {1, 3, 2, 3, 3, 1, 2, 1},
    {2, 1, 3, 1, 2, 1, 2, 3},
    {2, 3 ,2, 3, 1, 2, 3, 1},
    {3, 3, 1 ,2, 3, 1, 2, 2},
    {3, 2, 2, 1, 2, 3, 2, 1},
    {2, 1, 1, 3, 1, 1, 3, 2},
    {1, 2, 3, 2, 1, 2, 1, 3}
  };

  return matrix[x][y];
}

int main(){
  int type;
  int board[3][3] = {
      {1, 2, 1},
      {2, 3, 2},
      {1, 2, 1}
    };
  printf("%d", winCheck(board, &type));
  //printf("%d", type);
  

}

