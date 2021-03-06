#include"Board.h"
#include"Common.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

enum MoveType
{
	Normal,
	Quit,
};

MoveType GetPlayerInput(Cell &);
bool ConvertStringToPosition(string s, Cell & c);
string ToLower(string s);
void PrintInstructions();

int main()
{
	Board brd = Board();
	bool want_quit = false;

	PrintInstructions();

	while (true)
	{
		brd.draw();
		cout << endl;
		cout << "It's " << KindToString(brd.getCurPlayer()) << "'s Turn." << endl << endl;

		while (true)
		{
			Cell p;

			MoveType const mt = GetPlayerInput(p);

			if (mt == MoveType::Quit)
			{
				want_quit = true;
				break;
			}
			else if (mt == MoveType::Normal)
			{
				if (brd.PlacePiece(p))
				{
					brd.nextTurn();
					break;
				}
			}
		}

		if (brd.winner() != Winner::I)
		{
			int white_count = 0;
			int black_count = 0;
			brd.Count(white_count, black_count);

			if (brd.winner() != Winner::D)
			{
				cout << "\n\n\n--------------------Congrats! " << WinnerToString(brd.winner()) << " have won!--------------------\n\n\n" << endl;
				cout << "-------------------- White : " << white_count << "--------- " << "Black : " << black_count << " --------------------" << endl << endl;
				brd.draw();
				break;
			}
			else
			{
				cout << "--------------------Draw!--------------------" << endl;
				cout << "-------------------- White : " << white_count << "--------- "   << "Black : " << black_count << " --------------------" << endl << endl;
			}
		}

		if (want_quit)
			break;
	}

	system("pause");
	return 0;
}

MoveType GetPlayerInput(Cell & position)
{
	while (true)
	{
		cout << "Your move: ";
		string spos = " ";
		std::getline(std::cin, spos); // Beacause  OF SOME REASONS !!
		spos = ToLower(spos);
		if (spos == "quit")
		{
			cout << endl;
			return MoveType::Quit;
		}
		else if (ConvertStringToPosition(spos, position))
		{
			cout << endl;
			return MoveType::Normal;
		}
	}
}

bool ConvertStringToPosition(string pos, Cell & output)
{
	if (pos.size() == 2 && (pos[0] >= 'a' && pos[0] <= 'h') && (pos[1] >= '1' && pos[1] <= '8'))
	{
		output.x = pos[0] - 'a';
		output.y = pos[1] - '1';
		return true;
	}
	return false;
}

string ToLower(string s)
{
	for (int i = 0; i < int(s.size()); ++i)
		if (s[i] >= 'A' && s[i] <= 'Z')
			s[i] += 'a' - 'A';
	return s;
}

void PrintInstructions()
{
	cout << "\n---------Othello Game---------" << endl << endl;
	cout << "Instructions : \n\n"
		<< "1 - If you want to quit the game type 'quit' and then press enter.\n\n"
		<< "2 - To place you piece, enter the column character followed by the row number   (For Example = a5)\n\n*Note* column character is not case sensitive\n\n"
		<< "3 - visit the game rules and intro at :\n'http://www.site-constructor.com/othello/othellorules.html' \n\n"
		<< "4 - Please report any bug you see :  levent.cpp@gmail.com\n\n"
 		<< "5 - You can download the source file at : www.github.com\\leventcpp\\Othello \n\n"
		<< "6 - Programmed By levent cpp - 2015\n\n"
		<< "7 - Thank you and have a good day.\n\n"
		<< endl ;
}