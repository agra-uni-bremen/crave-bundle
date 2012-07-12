#include <crave/ConstrainedRandom.hpp>

using crave::rand_obj;
using crave::randv;
using crave::rand_vec;
using crave::_i;
using crave::reference;

#define IF_THEN(a, b) !(a) || (b)
#define IF_THEN_ELSE(a, b, c) (!(a) || (b)) && ((a) || (c))

template<typename T> 
struct my_randv : randv<T> {
	my_randv() : randv<T>(0) { }
};

class sudoku : public rand_obj {
public:
    my_randv<int> result_sudoku[9][9]; // variable to store solved sudoku
    int           given_sudoku[9][9];  // variable to hold given sudoku

	sudoku(rand_obj* parent = 0) : rand_obj(parent) {
        // constraint keep_given_sudoku, needed to copy given values to solved sudoku
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				constraint( IF_THEN( reference(given_sudoku[i][j]) != 0, result_sudoku[i][j]() == reference(given_sudoku[i][j]) ) );

        // constraint possible_values, only number from 1 to 9 are allowed
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
                constraint( (result_sudoku[i][j]() >= 1) && (result_sudoku[i][j]() <= 9) );

        // constraint rows, every number must appear exactly one time in one row
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				for (uint k = j + 1; k < 9; k++)
                	constraint( result_sudoku[i][j]() != result_sudoku[i][k]() );

        // constraint columns, every number must appear exactly one time in one column
		for (int j = 0; j < 9; j++)
			for (int i = 0; i < 9; i++)
				for (int k = i + 1; k < 9; k++)
                	constraint( result_sudoku[i][j]() != result_sudoku[k][j]() );

        // constraint regions, every number must appear exactly one time in one region
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				constraint
	                ( result_sudoku[i][j]() != result_sudoku[(i + 1) % 3 + i - (i % 3)][ j                       ]() )
    	            ( result_sudoku[i][j]() != result_sudoku[(i + 2) % 3 + i - (i % 3)][ j                       ]() )

	                ( result_sudoku[i][j]() != result_sudoku[ i                       ][(j + 1) % 3 + j - (j % 3)]() )
	                ( result_sudoku[i][j]() != result_sudoku[(i + 1) % 3 + i - (i % 3)][(j + 1) % 3 + j - (j % 3)]() )
	                ( result_sudoku[i][j]() != result_sudoku[(i + 2) % 3 + i - (i % 3)][(j + 1) % 3 + j - (j % 3)]() )

	                ( result_sudoku[i][j]() != result_sudoku[ i                       ][(j + 2) % 3 + j - (j % 3)]() )
 	                ( result_sudoku[i][j]() != result_sudoku[(i + 1) % 3 + i - (i % 3)][(j + 2) % 3 + j - (j % 3)]() )
	                ( result_sudoku[i][j]() != result_sudoku[(i + 2) % 3 + i - (i % 3)][(j + 2) % 3 + j - (j % 3)]() );

	} 
 
    void solve(int given[9][9]) {
		int count = 0;

		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++) {
				given_sudoku[i][j] = given[i][j];
	            if (given_sudoku[i][j] != 0)
                    count++;
			}

        std::cout << "Number of given fields: " << count << std::endl;
        std::cout << "Solution:" << std::endl;

        if (next()) { //run the solver
			for (int i = 0; i < 9; i++)
				for (int j = 0; j < 9; j++) {
                    std::cout << result_sudoku[i][j];
                    if (j==8) {
                        if ((i==2) || (i==5))
                            std::cout << std::endl;
                        std::cout << std::endl;
					}
                    else if ((j == 2) || (j == 5))
                        std::cout << "   ";
                    else
                        std::cout << "  ";
				}
		}
        else 
			std::cout << "Fehler!";
	}

};

int given_sudoku[9][9] = { 	
	{0,0,0, 0,0,0, 0,1,2},
	{0,5,0, 4,0,0, 0,0,0},
	{0,0,0, 0,0,0, 0,3,0},

	{7,0,0, 6,0,0, 4,0,0},
	{0,0,1, 0,0,0, 0,0,0},
	{0,0,0, 0,8,0, 0,0,0},

	{9,2,0, 0,0,0, 8,0,0},
	{0,0,0, 0,5,1, 7,0,0},
	{0,0,0, 0,0,3, 0,0,0}  
};

int main (int argc , char *argv[]) {
	sudoku s;
	s.solve( given_sudoku );
	return 0;
}
