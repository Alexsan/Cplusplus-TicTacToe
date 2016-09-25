#include <iostream>
#include <ctime>

char tttBoard[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8' };
char tempBoard[9];
int *p1, *p2, *ai;
int whoseTurn = 0;
int scoreCnt = 0;

int score(int winner);
void drawBoard(char *board);
int playerMove(int *whoseTurn, char *board);
int win(char *board);
int minimax(char *board, int player, int aiGoesFirst);
int depth();
int score(int winner);
int aiMove(int *aiTurn, char *board, int aiGoesFirst);

template <typename T, size_t N>
size_t countof(T(&array)[N])
{
	return N;
}

void drawBoard(char *board)
{
	std::cout << "     |     |     " << std::endl;
	std::cout << "  " << board[0] << "  |  " << board[1] << "  |  " << board[2] << std::endl;
	std::cout << "_____|_____|_____" << std::endl;
	std::cout << "     |     |     " << std::endl;
	std::cout << "  " << board[3] << "  |  " << board[4] << "  |  " << board[5] << std::endl;
	std::cout << "_____|_____|_____" << std::endl;
	std::cout << "     |     |     " << std::endl;
	std::cout << "  " << board[6] << "  |  " << board[7] << "  |  " << board[8] << std::endl;
	std::cout << "     |     |     " << std::endl;
}

int playerMove(int *whoseTurn, char *board)
{
	int choice;

	std::cout << "This turn is for Player " << *whoseTurn << std::endl;
	std::cout << "Enter a number: ";
	if (*whoseTurn % 2 != 0)
	{
		do
		{
			std::cin >> choice;
		} while ((board[choice] == 'x' || board[choice] == 'o') || (choice > 9 || choice < 0));
		board[choice] = 'x';
		std::cout << "This is the mark for player: " << board[choice] << std::endl;
		return *whoseTurn + 1;
	}
	else
	{
		do
		{
			std::cin >> choice;
		} while ((board[choice] == 'x' || board[choice] == 'o') || (choice > 9 || choice < 0));
		board[choice] = 'o';
		std::cout << "This is the mark for player: " << board[choice] << std::endl;
		return *whoseTurn - 1;
	}
}

int win(char *board)
{
	unsigned wins[8][3] = { { 0,1,2 },{ 3,4,5 },{ 6,7,8 },{ 0,3,6 },{ 1,4,7 },{ 2,5,8 },{ 0,4,8 },{ 2,4,6 } };
	for (int i = 0; i < 8; ++i)
	{
		if (board[wins[i][0]] == board[wins[i][1]] && board[wins[i][0]] == board[wins[i][2]])
		{
			if (board[wins[i][2]] == 'x')
			{
				return 1;
			}
			else if (board[wins[i][2]] == 'o')
			{
				return 2;
			}
		}
	}
	return 0;
}

int minimax(char *board, int player, int aiGoesFirst)
{
	int winner = win(tttBoard);
	if (winner != 0)
	{
		winner = winner * -1;
		return winner;
	}

	int move = -1;
	int score = -2;
	int i, playerTurn;
	char mark;

	if (player == 2)
	{
		mark = 'o';
		playerTurn = player - 1;

	}
	else
	{
		mark = 'x';
		playerTurn = player + 1;

	}

	for (i = 0; i < 9; ++i)
	{
		if (board[i] != 'x' && board[i] != 'o')
		{
			board[i] = mark;
			int thisScore = -minimax(board, playerTurn, aiGoesFirst);
			if (thisScore > score)
			{
				score = thisScore;
				move = i;
			}
			board[i] = tempBoard[i];
		}
	}
	if (move == -1)	// If move is not recommended, return the score as 0
	{
		return 0;
	}
	return score;
}

//***** depth(): Function that calculates positions left in the game after moves from ai and players *****//
int depth()
{
	int j = 0;
	for (unsigned int i = 0; i < countof(tttBoard); i++)
	{
		if (tttBoard[i] != 'x' && tttBoard[i] != 'o')
		{
			j++;
		}
	}
	scoreCnt = j;
	return scoreCnt;
}

int score(int winner)
{
	if (winner == 1)
	{
		return 10 - depth();
	}
	else if (winner == 2)
	{
		return depth() - 10;
	}
	else
	{
		return 0;
	}
}

int aiMove(int *aiTurn, char *board, int aiGoesFirst)
{
	int move = -1;
	int score = -2;
	int i, playerTurn, aiStrat;
	char mark, altMark;

	srand((unsigned int)time(NULL));
	aiStrat = rand() % 2 + 1;
	std::cout << "The ai strat is based on " << aiStrat << std::endl;

	if (*aiTurn == 1)
	{
		mark = 'x';
		altMark = 'o';
		playerTurn = *aiTurn + 1;
		std::cout << "Human player is turn " << playerTurn << " with mark " << altMark << "\n";
	}
	else
	{
		mark = 'o';
		altMark = 'x';
		playerTurn = *aiTurn - 1;
		std::cout << "Human player is turn " << playerTurn << " with mark " << altMark << "\n";
	}

	if (aiStrat == 2)
	{
		for (i = 8; i > 0; --i)
		{
			if (board[i] != mark && board[i] != altMark)
			{
				std::cout << "Testing " << board[i] << " iterator " << i << "\n";
				board[i] = mark;
				std::cout << "This is the initial score from aiMove: " << score << "\n";
				int tempScore = -minimax(board, playerTurn, aiGoesFirst);
				std::cout << "This is the modified score from aiMove: " << tempScore << "\n";
				board[i] = tempBoard[i];
				if (tempScore > score)
				{
					score = tempScore;
					std::cout << "This is the minmax score for ai: " << score << std::endl;
					move = i;
				}
			}
		}
	}
	else if (aiStrat == 1)
	{
		for (i = 0; i < 9; ++i)
		{
			if (board[i] != mark && board[i] != altMark)
			{
				std::cout << "Testing " << board[i] << " iterator " << i << "\n";
				board[i] = mark;
				std::cout << "This is the initial score from aiMove: " << score << "\n";
				int tempScore = -minimax(board, playerTurn, aiGoesFirst);
				std::cout << "This is the modified score from aiMove: " << tempScore << "\n";
				board[i] = tempBoard[i];
				if (tempScore > score)
				{
					score = tempScore;
					std::cout << "This is the minmax score for ai: " << score << std::endl;
					move = i;
				}
			}
		}
	}

	std::cout << "This is the aiMove for ai: " << move << std::endl;
	std::cout << "This is the mark for ai: " << mark << std::endl;
	board[move] = mark;

	if (*aiTurn % 2 != 0)	// This means that ai was player 1
	{
		std::cout << "The original aiTurn: " << *aiTurn << std::endl;
		std::cout << "Whose turn is this: " << *aiTurn + 1 << std::endl;
		return *aiTurn + 1;
	}
	else    // This means that ai was player 2
	{
		std::cout << "The original aiTurn: " << *aiTurn << std::endl;
		std::cout << "Whose turn is this: " << *aiTurn - 1 << std::endl;
		return *aiTurn - 1;
	}
}

int main()
{
	int *orderOfPlayerPtr = &whoseTurn;
	char mpOption;
	int aiGoesFirst = 0;
	std::cout << "Versus AI (y) or Player (n):  " << std::endl;
	std::cin >> mpOption;

	std::cout << std::endl;
	std::cout << "Pick 1(X) or 2(O): " << std::endl;
	std::cin >> whoseTurn;

	if (whoseTurn == 1)
		aiGoesFirst = 2;
	else
		aiGoesFirst = 1;

	strcpy_s(tempBoard, 10, tttBoard);

	std::cout << "Here is the game board. Begin! " << std::endl;
	drawBoard(tttBoard);

	if (mpOption == 'y')
	{
		if (aiGoesFirst == 1)
		{
			do
			{
				*orderOfPlayerPtr = *orderOfPlayerPtr - 1;
				std::cout << "Computer's turn: " << *orderOfPlayerPtr << std::endl;
				std::cout << "Whose turn value: " << whoseTurn << std::endl;
				whoseTurn = aiMove(orderOfPlayerPtr, tttBoard, aiGoesFirst) - 1;
				std::cout << "Whose turn value: " << whoseTurn << std::endl;
				drawBoard(tttBoard);
				std::cout << "The value of depth is: " << depth() << std::endl;
				std::cout << "The winner is: " << win(tttBoard) << std::endl;
				if (depth() == 1 || win(tttBoard) != 0)
					break;

				*orderOfPlayerPtr = *orderOfPlayerPtr + 1;
				std::cout << "Player's turn: " << *orderOfPlayerPtr << std::endl;
				std::cout << "Whose turn value: " << whoseTurn << std::endl;
				whoseTurn = playerMove(orderOfPlayerPtr, tttBoard) + 1;
				std::cout << "Whose turn value: " << whoseTurn << std::endl;
				drawBoard(tttBoard);
				std::cout << "The value of depth is: " << depth() << std::endl;
				std::cout << "The winner is: " << win(tttBoard) << std::endl;
				if (depth() == 1 || win(tttBoard) != 0)
					break;
			} while (win(tttBoard) == 0 && depth() != 1);
		}
		else
		{
			do
			{
				*orderOfPlayerPtr = *orderOfPlayerPtr;
				std::cout << "Player's turn: " << *orderOfPlayerPtr << std::endl;
				std::cout << "Whose turn value: " << whoseTurn << std::endl;
				whoseTurn = playerMove(orderOfPlayerPtr, tttBoard);
				std::cout << "Whose turn value: " << whoseTurn << std::endl;
				drawBoard(tttBoard);
				std::cout << "The value of depth is: " << depth() << std::endl;
				std::cout << "The winner is: " << win(tttBoard) << std::endl;
				if (depth() == 1 || win(tttBoard) != 0)
					break;

				*orderOfPlayerPtr = *orderOfPlayerPtr;
				std::cout << "Computer's turn: " << *orderOfPlayerPtr << std::endl;
				std::cout << "Whose turn value: " << whoseTurn << std::endl;
				whoseTurn = aiMove(orderOfPlayerPtr, tttBoard, aiGoesFirst);
				std::cout << "Whose turn value: " << whoseTurn << std::endl;
				drawBoard(tttBoard);
				std::cout << "The value of depth is: " << depth() << std::endl;
				std::cout << "The winner is: " << win(tttBoard) << std::endl;
				if (depth() == 1 || win(tttBoard) != 0)
					break;
			} while (win(tttBoard) == 0 && depth() != 1);
		}
	}
	else
	{
		if (*orderOfPlayerPtr == 2)
			*orderOfPlayerPtr = *orderOfPlayerPtr - 1;

		do
		{
			std::cout << "Player's turn: " << *orderOfPlayerPtr << std::endl;
			whoseTurn = playerMove(orderOfPlayerPtr, tttBoard);
			drawBoard(tttBoard);
			std::cout << "The results are: " << win(tttBoard) << std::endl;
		} while (win(tttBoard) == 0 && depth() != 1);
	}


	if (win(tttBoard) == 1 && depth() == 1)
	{
		std::cout << "'x' player wins." << std::endl;
	}
	else if (win(tttBoard) == 2 && depth() == 1)
	{
		std::cout << "'o' player wins." << std::endl;
	}

	if (depth() == 1 && win(tttBoard) == 0)
	{
		std::cout << "It's a draw." << std::endl;
	}

	return 0;
}