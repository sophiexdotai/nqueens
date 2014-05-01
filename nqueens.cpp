#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

using std::vector;

// Joe Tannenbaum

// pretty-prints a chessboard; 0's are empty spaces, 1's are queens
void pprint(unsigned int n, std::vector< std::vector< unsigned int > > Q) {
	bool found;
	for(unsigned int i=0; i<n; ++i){
		for(unsigned int j=0; j<n; ++j) {
			found = false;
			for(unsigned int q=0; q < Q.size(); ++q) {
				if(Q[q][0] == j and Q[q][1] == i){
					found = true;
					std::cout << "1 ";
				}
			}
			if(!found)
				std::cout << "0 ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

// determines if a given set of queens are promising
bool promising(unsigned int n, std::vector< std::vector< unsigned int > > Q) {
	int x1, y1, x2, y2;
	for (unsigned int i=0; i<Q.size(); ++i) {
		x1 = Q[i][0];
		y1 = Q[i][1];
		for (unsigned int j=i+1; j<Q.size(); ++j) {
			x2 = Q[j][0];
			y2 = Q[j][1];

			// each check looks for:
			if(x1 == x2) return false; // horizontally attacking
			
			if(y1 == y2) return false; // vertically attacking
			
			int x1_old = x1; int y1_old = y1;
			x1++; y1++;
			while(x1 < n and y1 < n) { // lower right diag attacking
				if(x1 == x2 and y1 == y2)
					return false;
				x1++; y1++;
			}
			
			x1 = x1_old; y1 = y1_old;
			x1--; y1--;
			while(x1 >= 0 and y1 >= 0) { // upper left diag attacking
				if(x1 == x2 and y1 == y2)
					return false;
				x1--; y1--;
			}
			
			x1 = x1_old; y1 = y1_old;
			x1--; y1++;
			while(x1 >= 0 and y1 < n) { // lower left diag attacking
				if(x1 == x2 and y1 == y2)
					return false;
				x1--; y1++;
			}
			
			x1 = x1_old; y1 = y1_old;
			x1++; y1--;
			while(x1 < n and y1 >= 0) { // upper right diag attacking
				if(x1 == x2 and y1 == y2)
					return false;
				x1++; y1--;
			}
			x1 = x1_old; y1 = y1_old;
		}
	}

	return true;
}

// solves the n-queens problem recursively using backtracking
std::vector< std::vector< unsigned int > > nqueens_solve(unsigned int n, std::vector< std::vector< unsigned int > > Q, int at_row, int at_col) {

	std::vector< unsigned int > new_queen;
	new_queen.push_back(at_col);
	new_queen.push_back(at_row);
	Q.push_back(new_queen);

	unsigned int new_y = at_row+1;
	unsigned int new_x = 0;
	while(1) { // test ahead to next row
		std::vector< unsigned int > test_queen;
		test_queen.push_back(new_x);
		test_queen.push_back(new_y);
		Q.push_back(test_queen);

		if(promising(n, Q)) {
			if(Q.size() == n) return Q; // we did it!
			Q.pop_back();
			return nqueens_solve(n, Q, new_y, new_x);
		} else {
			Q.pop_back();
		}
		new_x++;
		
		if (new_x >= n) { // this happens when the new_queen is non-p
			unsigned int prev_col = Q.back()[0];
			Q.pop_back();
			while(prev_col+1 == n){ // backtrack as far as needed
				at_row--;
				prev_col = Q.back()[0];
				Q.pop_back();
			}
			return nqueens_solve(n, Q, at_row, prev_col+1);
		}

	}
	return Q; // should never get to this point, unless maybe n<4

}

int main(int argc, char *argv[]){
    if (argc < 2) {
        std::cout << "Usage: submission n" << '\n';
        return 1;
    }
    unsigned int n = atoi(argv[1]);
    
    std::vector< std::vector< unsigned int > > Q; // vector for queen coords
    
	Q = nqueens_solve(n, Q, 0, 0);
	std::cout << "finished, printing final board with " << Q.size() << " queens:\n";
	pprint(n, Q);
    
}
