#include <iostream>
#include<fstream>
#include <vector>
#include<string>
#include<algorithm>
#include "Board.h"

using namespace std;

int main()
{
	board my_board;
	vector<string> my_results;
	vector<string> legal_words;

	my_board.config_board_input();
	my_board.get_all_words();
	legal_words = my_board.set_legal_words();
	my_results = my_board.solve_board(legal_words);

	sort(my_results.begin(), my_results.end());

	cout << "\nMy Results: " << endl;
	cout << "Number of words found: " << my_results.size() << endl;

	for (int i = 0; i < int(my_results.size()); i++)
	{
		cout << my_results[i] << endl;
	}

	return 0;
}

vector<string> board::solve_board(vector<string> legal_words)
{
	vector<int> adjacent_spaces;
	vector<string> results;
	vector<string> temp = legal_words;
	bool found_word = false;
	bool found_letter = false;
	string check_word;
	int first_space;
	int curr_space;
	char first_letter;
	display_board();

	for (int f = 0; f < int(board_letters.size()); f++)
	{
		curr_space = f;
		first_space = f;
		first_letter = board_letters[curr_space];

		legal_words.clear();

		for (int c = 0; c < int(temp.size()); c++)//creates a vector where the only strings are ones that begin with the current letter
		{
			if (first_letter == temp[c][0])
			{
				legal_words.push_back(temp[c]);
			}
		}

		if (legal_words.size() > 0)
		{
			for (int i = 0; i < int(legal_words.size()); i++)//for each word in the vector
			{
				check_word.clear();
				check_word.push_back(first_letter);
				
				for (int x = 1; x < int(legal_words[i].size()); x++)//for each letter in the current word 
				{
					adjacent_spaces = check_edge_case(curr_space);
					
					for (int y = 0; y < int(adjacent_spaces.size()); y++)//every letter that is an adjacent space
					{
						if (board_letters[adjacent_spaces[y]] == legal_words[i][x])//If the adjacent space letter equals the letter that we are checking in the word
						{
							check_word.push_back(board_letters[adjacent_spaces[y]]);
							if (check_word == legal_words[i])
							{
								found_word = true;
							}
							curr_space = adjacent_spaces[y];
							found_letter = true;
							break;
						}
						found_letter = false;
					}
					if (found_letter == false)//Did not find ANY adjacent letter in the current word, breaks the loop.
					{
						curr_space = first_space;
						break;
					}
				}

				if (found_word == true)
				{
					found_word = false;
					curr_space = first_space;
					results.push_back(legal_words[i]);
					vector<string> ::iterator it = find(temp.begin(), temp.end(), legal_words[i]);
					int index = distance(temp.begin(), it);
					temp.erase(temp.begin() + index);
					legal_words.erase(legal_words.begin() + i);
					i -= 1;
				}
			}
		}
		else
		{
			cout << "No More Words in the List, ending task...\n";
			break;
		}
	}

	return results;
}

void board::display_board()//DEBUG
{
	cout << "\nBoard:\n";

	for (int i = 0; i < int(board_letters.size()); i++)
	{
		if (i % width == 0)
		{
			cout << endl;
		}
		cout << board_letters[i]<<" ";
	}
	cout << endl;
}

vector<int> board::check_edge_case(int curr_space)
{
	vector<int> adjacent_spaces;

	if (curr_space == 0)//Top Left Corner
	{
		adjacent_spaces.push_back(curr_space + 1);
		adjacent_spaces.push_back(curr_space + 3);
		adjacent_spaces.push_back(curr_space + 4);
	}
	else if (curr_space == (width - 1))//Top Right Corner
	{
		adjacent_spaces.push_back(curr_space - 1);
		adjacent_spaces.push_back(curr_space + 2);
		adjacent_spaces.push_back(curr_space + 3);
	}
	else if (curr_space == ((width * height) - 1))//Bottom Right Corner
	{
		adjacent_spaces.push_back(curr_space - 4);
		adjacent_spaces.push_back(curr_space - 3);
		adjacent_spaces.push_back(curr_space - 1);
	}
	else if (curr_space == (width * (height - 1)))//Bottom Left Corner
	{
		adjacent_spaces.push_back(curr_space - 3);
		adjacent_spaces.push_back(curr_space - 2);
		adjacent_spaces.push_back(curr_space + 1);
	}
	else if (curr_space > 0 && curr_space < (width - 1))//Top Edge
	{
		adjacent_spaces.push_back(curr_space - 1);
		adjacent_spaces.push_back(curr_space + 1);
		adjacent_spaces.push_back(curr_space + 2);
		adjacent_spaces.push_back(curr_space + 3);
		adjacent_spaces.push_back(curr_space + 4);
	}
	else if (curr_space % width == 0)//Left Edge
	{
		adjacent_spaces.push_back(curr_space - 3);
		adjacent_spaces.push_back(curr_space - 2);
		adjacent_spaces.push_back(curr_space + 1);
		adjacent_spaces.push_back(curr_space + 3);
		adjacent_spaces.push_back(curr_space + 4);
	}
	else if ((curr_space + 1) % width == 0)//Right Edge
	{
		adjacent_spaces.push_back(curr_space - 4);
		adjacent_spaces.push_back(curr_space - 3);
		adjacent_spaces.push_back(curr_space - 1);
		adjacent_spaces.push_back(curr_space + 2);
		adjacent_spaces.push_back(curr_space + 3);
	}
	else if (curr_space < ((width * height) - 1) && curr_space >((width * height) - width))//Bottom Edge
	{
		adjacent_spaces.push_back(curr_space - 4);
		adjacent_spaces.push_back(curr_space - 3);
		adjacent_spaces.push_back(curr_space - 2);
		adjacent_spaces.push_back(curr_space - 1);
		adjacent_spaces.push_back(curr_space + 1);
	}
	else
	{
		adjacent_spaces.push_back(curr_space - 4);
		adjacent_spaces.push_back(curr_space - 3);
		adjacent_spaces.push_back(curr_space - 2);
		adjacent_spaces.push_back(curr_space - 1);
		adjacent_spaces.push_back(curr_space + 1);
		adjacent_spaces.push_back(curr_space + 2);
		adjacent_spaces.push_back(curr_space + 3);
		adjacent_spaces.push_back(curr_space + 4);
	}

	return adjacent_spaces;
}

void board::get_all_words()
{
	ifstream fin("DictionaryFile.txt");

	if (fin.fail())
	{
		cout << "Could not open file." << endl;
		return;
	}

	string word;
	bool only_letters = true;
	fin >> word;

	while (fin)
	{
		if (word.size() >= 3)//Checks to see if the Word is at least 3 characters.
		{
			for (int i = 0; i < int(word.size()); i++)//If the word is greater than 3 characters, Checks to see if every word is a letter.
			{
				if (word[i] < 91 && word[i] > 64)//Checks to see if the word contains all characters that are uppercase letters. If so, makes it lowercase.
				{
					word[i] += 32;
				}
				else if (word[i] > 96 && word[i] < 123)//Checks to see if a letter is a lowercase letter.
				{
					
				}
				else//If the character is not a letter, the boolean is set to false.
				{
					only_letters = false;
				}
			}

			if (only_letters == true)//If the word got through the checks as true, then all the characters were letters.
			{
				all_words.push_back(word);
			}
			only_letters = true;
		}
		fin >> word;
	}
}

vector<string> board::set_legal_words()
{
	vector<string> legal_words;
	bool acceptable_word = true;
	bool found_char = false;
	string word = " ";
	char letter = ' ';
	char check_letter = ' ';
	int board_char_counter[26] = { 0 };//This array is a counter for how many of each letter is in the Board. Letters correspond to each index. a = 0, b = 1, c = 3 ... z = 25.
	int word_char_counter[26] = { 0 };
	vector<string> temp_vector;

	for (int i = 0; i < int(all_words.size()); i++)//Loops for each word in the Legal Words list.
	{
		word = all_words[i];
		for (int x = 0; x < int(word.size()); x++)//Checks to see if every letter can be found on the Board.
		{
			letter = word[x];
			for (int y = 0; y < int(board_letters.size()); y++)//Checks to see if the current letter can be found on the Board.
			{
				check_letter = board_letters[y];
				if (letter == check_letter)
				{
					found_char = true;
					y = board_letters.size();
				}
			}

			if (found_char == false)
			{
				acceptable_word = false;
				x = word.size();
			}
			else
			{
				found_char = false;
			}
		}

		if (acceptable_word == true)
		{
			temp_vector.push_back(word);
		}

		acceptable_word = true;
		found_char = false;
	}

	for (int i = 0; i <int( board_letters.size()); i++)//Counts how many of each letter is on the Board.
	{
		letter = board_letters[i];

		switch (letter)
		{
		case 'a':
			board_char_counter[0] += 1;
			break;
		case 'b':
			board_char_counter[1] += 1;
			break;
		case 'c':
			board_char_counter[2] += 1;
			break;
		case 'd':
			board_char_counter[3] += 1;
			break;
		case 'e':
			board_char_counter[4] += 1;
			break;
		case 'f':
			board_char_counter[5] += 1;
			break;
		case 'g':
			board_char_counter[6] += 1;
			break;
		case 'h':
			board_char_counter[7] += 1;
			break;
		case 'i':
			board_char_counter[8] += 1;
			break;
		case 'j':
			board_char_counter[9] += 1;
			break;
		case 'k':
			board_char_counter[10] += 1;
			break;
		case 'l':
			board_char_counter[11] += 1;
			break;
		case 'm':
			board_char_counter[12] += 1;
			break;
		case 'n':
			board_char_counter[13] += 1;
			break;
		case 'o':
			board_char_counter[14] += 1;
			break;
		case 'p':
			board_char_counter[15] += 1;
			break;
		case 'q':
			board_char_counter[16] += 1;
			break;
		case 'r':
			board_char_counter[17] += 1;
			break;
		case 's':
			board_char_counter[18] += 1;
			break;
		case 't':
			board_char_counter[19] += 1;
			break;
		case 'u':
			board_char_counter[20] += 1;
			break;
		case 'v':
			board_char_counter[21] += 1;
			break;
		case 'w':
			board_char_counter[22] += 1;
			break;
		case 'x':
			board_char_counter[23] += 1;
			break;
		case 'y':
			board_char_counter[24] += 1;
			break;
		case 'z':
			board_char_counter[25] += 1;
			break;
		}
	}

	for (int i = 0; i < int(temp_vector.size()); i++)//Checks to see if there are enough instances of a letter on the Board to form a word. i.e. if there are two 'a' in a word, there needs to be two 'a' on the Board.
	{
		word = temp_vector[i];
		for (int x = 0; x < int(word.size()); x++)
		{
			letter = word[x];
			switch (letter)
			{
			case 'a':
				word_char_counter[0] += 1;
				break;
			case 'b':
				word_char_counter[1] += 1;
				break;
			case 'c':
				word_char_counter[2] += 1;
				break;
			case 'd':
				word_char_counter[3] += 1;
				break;
			case 'e':
				word_char_counter[4] += 1;
				break;
			case 'f':
				word_char_counter[5] += 1;
				break;
			case 'g':
				word_char_counter[6] += 1;
				break;
			case 'h':
				word_char_counter[7] += 1;
				break;
			case 'i':
				word_char_counter[8] += 1;
				break;
			case 'j':
				word_char_counter[9] += 1;
				break;
			case 'k':
				word_char_counter[10] += 1;
				break;
			case 'l':
				word_char_counter[11] += 1;
				break;
			case 'm':
				word_char_counter[12] += 1;
				break;
			case 'n':
				word_char_counter[13] += 1;
				break;
			case 'o':
				word_char_counter[14] += 1;
				break;
			case 'p':
				word_char_counter[15] += 1;
				break;
			case 'q':
				word_char_counter[16] += 1;
				break;
			case 'r':
				word_char_counter[17] += 1;
				break;
			case 's':
				word_char_counter[18] += 1;
				break;
			case 't':
				word_char_counter[19] += 1;
				break;
			case 'u':
				word_char_counter[20] += 1;
				break;
			case 'v':
				word_char_counter[21] += 1;
				break;
			case 'w':
				word_char_counter[22] += 1;
				break;
			case 'x':
				word_char_counter[23] += 1;
				break;
			case 'y':
				word_char_counter[24] += 1;
				break;
			case 'z':
				word_char_counter[25] += 1;
				break;
			}
		}

		for (int y = 0; y < 26; y++)
		{
			if (word_char_counter[y] > board_char_counter[y])//If at any point, the instances of a letter is greater than the number of that letter on the board, acceptable word is false.
			{
				acceptable_word = false;
				break;
			}
		}

		if (acceptable_word == true)//Adds each acceptable word to the vector.
		{
			legal_words.push_back(word);
		}
		memset(word_char_counter, 0, sizeof(word_char_counter));//resets the array to 0
		acceptable_word = true;
	}

	return legal_words;
}

void board::config_board_input()
{
	int diff = 0;
	char random;
	string temp_string;

	cout << "Enter board Width: ";
	cin >> width;

	cout << "Enter board Height: ";
	cin >> height;

	cout << "Enter a string of letters for the board: ";
	cin >> temp_string;

	for (int i = 0; i < int(temp_string.size()); i++)//Checks to see if every word is a letter.
	{
		if (temp_string[i] < 91 && temp_string[i] > 64)//Checks to see if char is an uppercase letter.
		{
			temp_string[i] += 32;
			board_letters.push_back(temp_string[i]);
		}
		else if (temp_string[i] > 96 && temp_string[i] < 123)//Checks to see if it is a lowercase letter.
		{
			board_letters.push_back(temp_string[i]);
		}
		else
		{
			cout << "Invalid input detected. Removing invalid characters...\n";
		}
	}

	if (width < 3)
	{
		cout << "Invalid board Width. Setting to default.\n";
		width = 3;
	}
	if (height < 3)
	{
		cout << "Invalid board Height. Setting to default.\n";
		height = 3;
	}

	diff = (width * height) - board_letters.size();

	if (diff > 0)
	{
		cout << "Not enough letters were entered. Filling the board with random letters...\n";

		for (int i = 0; i < diff; i++)
		{
			random = ('a' + (rand() % 26));
			board_letters.push_back(random);
		}
	}
	else if (diff < 0)
	{
		diff *= -1;
		cout << "Too many letters were entered. Removing letters to fit in board size...\n";
		for (int i = 0; i < diff; i++)
		{
			board_letters.pop_back();
		}
	}
}