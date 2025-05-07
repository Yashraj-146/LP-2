#include<iostream>
#include<vector>
using namespace std;

class NQueens {
public:
    int n;
    vector<int> board;
    vector<bool> rowLookup;
    vector<bool> d1;
    vector<bool>d2;

    NQueens(int size) {
        n = size;
        board = vector<int>(size, -1);
        rowLookup = vector<bool>(size, false);
        d1 = vector<bool>(2 * size - 1, false);
        d2 = vector<bool>(2 * size - 1, false);
    }

    void solver() {
        if(solve(0)) {
            cout<<"Solution Exits! for "<<n<<" sized board"<<endl;
            printBoard();
        } else {
            cout<<"Solution doesn't exist for "<<n<<" sized board";
        }
    }

    void printBoard() {
        for(int i = 0; i<n; i++) 
        {
            for(int j = 0; j < n; j++)
            {
                if(board[j] == i)
                    cout<<"1";
                else
                    cout<<"0";
            }
            cout<<endl;
        }
    }

    bool solve(int col) {
        if(col == n)
            return true;
        
        for(int row = 0; row<n; row++){
            if(!rowLookup[row] && !d1[row+col] && !d2[row-col+n-1]) {
                board[col] = row;   //Place queen
                rowLookup[row] = d1[row+col] = d2[row-col+n-1] = true;

                if(solve(col+1))
                    return true;
                
                rowLookup[row] = d1[row+col] = d2[row-col+n-1] = false;
            }
        }
        return false;
    }
};

int main()
{
    int n;
    cout<<"Enter board size: ";
    cin>>n;

    NQueens sol(n);
    sol.solver();

    return 0;
}