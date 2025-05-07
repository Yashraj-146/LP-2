#include <iostream>
#include<vector>
using namespace std;

bool isSafe(int row, int col, vector<vector<int> > &board, int n) {
  // Check row and column attacks
  for (int i = 0; i < n; i++) {
    if (board[row][i] == 1 || board[i][col] == 1) return false;
  }
  // Check diagonal attacks

  // Top left diagonal
  int i = row, j = col;
  while (i >= 0 && j >= 0) {
    if (board[i][j] == 1) return false;
    i--;
    j--;
  }

  // Bottom left diagonal
  i = row, j = col;
  while (i < n && j >= 0) {
    if (board[i][j] == 1) return false;
    i++;
    j--;
  }

  // Top right diagonal
  i = row, j = col;
  while (i >= 0 && j < n) {
    if (board[i][j] == 1) return false;
    i--;
    j++;
  }

  // Bottom right diagonal
  i = row, j = col;
  while (i < n && j < n) {
    if (board[i][j] == 1) return false;
    i++;
    j++;
  }

  return true;
}

bool solveNQueens(vector<vector<int> > &board, int col, int n) {
  if (col >= n) {
    return true;
  }

  for (int i = 0; i < n; i++) {
    if (isSafe(i, col, board, n)) {
      board[i][col] = 1;

      // Recur for the next queen
      if (solveNQueens(board, col + 1, n)) {
        return true;
      }

      // Backtrack if placing the queen doesn't lead to a solution
      board[i][col] = 0;
    }
  }
  return false;
}

void printSolution(vector<vector<int> > &board, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (board[i][j] == 1) {
        cout << "Q ";
      } else {
        cout << ". ";
      }
    }
    cout << endl;
  }
}

int main() {
  int n;
  cout << "Enter the board size (n): ";
  cin >> n;
  
  vector<vector<int> > board(n, vector<int>(n, 0));
  
  if (solveNQueens(board, 0, n)) {
    cout << "Solution exists:" << endl;
    printSolution(board, n);
  } else {
    cout << "No solution exists" << endl;
  }

  return 0;
}
