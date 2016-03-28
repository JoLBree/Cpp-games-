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
	game_draw = 10,
	could_not_allocate_memory = 11
};

// Enumeration of array indices
enum array_indices{
	program_name = 0,
	input_game_name = 1,
	expected_name_args = 2,
	gomoku_board_size = 3,
	gomoku_win_length = 4
};

// Enumeration of static numbers
enum constants{
	gomoku_default_board_size = 19,
	gomoku_default_win_length = 5,
	tictactoe_default_board_size = 3,
	tictactoe_default_win_length = 3,
	ascii_upper_letters_start = 65,
	ascii_upper_letters_end = 90,
	ascii_upper_lower_difference = 32,
	min_board_size = 1,
	min_win_length = 3,
	buffer_size = 2
};


// Function prototypes
int usage(char program_name[], string info = "");
string makeLower(string a);

#endif /* COMMON_H */