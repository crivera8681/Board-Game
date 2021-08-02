#ifndef Board_H
#define Board_H
#include <iostream>
#include <vector>
using namespace std;

class board
{
public:
	void get_all_words();
	void display_board();
	void config_board_input();
	vector<int> check_edge_case(int curr_space);
	vector<string>set_legal_words();
	vector<string> solve_board(vector<string> legal_words);

private:
	int width = 0;
	int height = 0;
	string board_letters;
	vector<string> all_words;
};

#endif

