// Common.h


#ifndef COMMON_H
#define COMMON_H


#include <vector>
#include <array>
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
	could_not_allocate_memory = 11,
	gamebase_ptr_is_null = 12,
	gamebase_ptr_is_not_null = 13,
	wrong_save_arg_num = 14,
	invalid_piece = 15,
	bad_board = 16,
	bad_moves = 17
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
	sudoku_default_board_size = 9,
	sudoku_default_win_length = 0,
	ascii_upper_letters_start = 65,
	ascii_upper_letters_end = 90,
	ascii_upper_lower_difference = 32,
	min_board_size = 1,
	min_win_length = 3,
	buffer_size = 2,
	save_state_args = 7,
	axes_parts = 20,
	largest_sudoku_tile = 9,
	sudoku_square_length = 3,
	largest_one_digit_num = 9,
	num_player_types = 5
};

// types of games
enum game_type{
	dummy_game = 0,
	tic_tac_toe = 1,
	gomoku = 2,
	sudoku = 3
};

enum axes_type{
	norm_axes = 1,
	sudoku_axes = 2
};

// Function prototypes
int usage(char program_name[], string info = "");
string makeLower(string a);

//const static int square_starts[] = { 12, 15, 18, 45, 48, 51, 78, 81, 84 }; // THESE ARE NOT HARDCODED CONSTANTS. Please don't make me give them individual enum values. The rules of sudoku are set. If these indices need to be changed, they can all be changed here.

const static array<int, 9> square_starts = { 12, 15, 18, 45, 48, 51, 78, 81, 84 };

#endif /* COMMON_H */
