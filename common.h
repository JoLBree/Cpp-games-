// Common.h


#ifndef COMMON_H
#define COMMON_H


#include <vector>
#include <string>

using namespace std;

// Enumeration of processes
enum processes{
	success = 0,
	fail_to_open_file = 1,
	wrong_usage = 2,
	cannot_read_line = 3,
	cannot_extract_dimensions = 4,
	no_good_piece_defns = 5,
	diff_vector_board_sizes = 6,
	quit = 7,
	enter_coords_done = 8,
	valid_move_made = 9,
	game_draw = 10
};

// Enumeration of array indices
enum array_indices{
	program_name = 0,
	input_game_name = 1,
	expected_args = 2
};


// Function prototypes
int usage(char program_name[], string info = "");
string makeLower(string a);

#endif /* COMMON_H */