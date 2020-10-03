
#include "Executive.h"
#include "player.h"
#include "display.h"
#include "Ship.h"
#include <iostream>
using namespace std;

int Executive::charToInt(char c) {return ((toupper(c) - 65));}

int Executive::numShipCoords(int shipNum)
{
	int n = 0;

	for(int i = 1; i <= shipNum; i++)
	{
		n = n+i;
	}

	return n;
}

void Executive::WaitEnter()
{
	cin.ignore();
	cout << "Press ENTER to end turn...";
	cin.get();
	for (int i = 0; i <= 50; i++) cout << endl;
}

bool Executive::validColumn(char c)
{
	if (!isalpha(c) || (toupper(c) < 65 || toupper(c) > 73))
	{
		cout << "Invalid input! Column must be A-I!: ";
		return false;
	}
	else
	{
		return true;
	}
}

void Executive::run_setup_PvP()
{
	cout << "How many ships do you want to place in the grid (choose from 1 to 5)? ";
	// This will be the number of ships used for both players.
	
	do {
		cin >> shipnum;
		if (shipnum < 1 || shipnum > 5) {
			cout << "Invalid! Must be 1-5!: ";
			cin.clear();
			cin.ignore(123, '\n');
		}
	} while (shipnum < 1 || shipnum > 5);

	player1.SetNumShips(shipnum);
	shipofplayer1.setShipNumber(numShipCoords(shipnum));

	for (int i = 1; i <= shipnum; i++)
	{
		chooseShipPosition1:

			//blank Board
			display.friendlyBoard(player1.my_ships.m_board);
			char direction = 'u'; //default direction is up

			if (i == 1)
			{
				cout << "\nPlayer 1, Where do you want to place 1X" << i << " on the grid (row(1-9) col(A-I))? ";
				while(!(cin >> row)||row < 1 || row > 9)
				{
					cout << "Invalid input! Row must be 1-9!: ";
					cin.clear();
					cin.ignore(123, '\n');
				}
				cout << "Now enter a column A-I: ";
				cin >> c_col;
				cout << "\n";
				while(!validColumn(c_col))
				{
					cin >> c_col;
				}
				col = charToInt(c_col);
			}
			else
			{
				cout << "\nChoose a pivot coordinate for 1X" << i << " ship on the grid (row(1-9) col(A-I)): ";
				while (!(cin >> row)||row < 1 || row > 9)
				{
					cout << "Invalid input! Row must be 1-9!: ";
					cin.clear();
					cin.ignore(123, '\n');
				}
				cout << "Now enter a column A-I: ";
				cin >> c_col;
				while (!validColumn(c_col))
				{
					cin >> c_col;
				}

			chooseShipDirection1:
				cout << "Up, Down, Left, or Right from pivot? (U, D, L, R): ";
				cin >> direction;
			}
			col = charToInt(c_col); // convert char to int
			row--; // decrement row by 1 for indexing array
			direction = toupper(direction);

			if (direction != 'U' && direction != 'D' && direction != 'L' && direction != 'R')
			{
				cout << "Invalid direction input!\n";
				goto chooseShipDirection1;
			}
			if (!player1.PlaceShip(i, row, col, direction))
			{
				cout << "Ship could not be placed there. \n";
				goto chooseShipPosition1;
			}
	}

	//print last time so player can see 1x5 ship placed
	display.friendlyBoard(player1.my_ships.m_board);

	cout <<" Switch to Player 2 Setting!\n";
	WaitEnter();

	/*
	player2.SetNumShips(shipnum);
	shipofplayer2.setShipNumber(numShipCoords(shipnum));

	for (int i = 1; i <= shipnum; i++)
	{
		chooseShipPosition2:

			display.friendlyBoard(player2.my_ships.m_board);
			char direction = 'u';

			if (i == 1)
			{
				cout << "\nPlayer 2, Where do you want to place 1X" << i << " on the grid (row(1-9) col(A-I))? ";
				while (!(cin >> row)||row < 1 || row > 9)
				{
					cout << "Invalid input! Row must be 1-9!: ";
					cin.clear();
					cin.ignore(123, '\n');
				}
				cout << "Now enter a column A-I: ";
				cin >> c_col;
				cout << "\n";
				while (!validColumn(c_col))
				{
					cin >> c_col;
				}
				col = charToInt(c_col);
			}
			else
			{
				cout << "\nChoose a pivot coordinate for 1X" << i << " ship on the grid (row(1-9) col(A-I)): ";
				while (!(cin >> row)||row < 1 || row > 9)
				{
					cout << "Invalid input! Row must be 1-9!: ";
					cin.clear();
					cin.ignore(123, '\n');
				}
				cout << "Now enter a column A-I: ";
				cin >> c_col;
				while (!validColumn(c_col))
				{
					cin >> c_col;
				}
			chooseShipDirection2:
				cout << "Up, Down, Left, or Right from pivot? (U, D, L, R): ";
				cin >> direction;
			}
			col = charToInt(c_col);
			row--;
			direction = toupper(direction);

			if (direction != 'U' && direction != 'D' && direction != 'L' && direction != 'R')
			{
				cout << "Invalid direction input!\n";
				goto chooseShipDirection2;
			}
			if (!player2.PlaceShip(i, row, col, direction))
			{
				cout << "Ship could not be placed there. \n";
				goto chooseShipPosition2;
			}
	}

	display.friendlyBoard(player2.my_ships.m_board);
	WaitEnter();

	run_PvP();*/

}

void Executive::run_setup_PvAi()
{
	char arr_directions[4] = {'U', 'D', 'L', 'R'};

	cout << "How many ships do you want to place in the grid (choose from 1 to 5)? ";
	cin >> shipnum;
	player1.SetNumShips(shipnum); //declares number of ships for both players
	shipofplayer1.setShipNumber(numShipCoords(shipnum));

	if (shipnum < 1 || shipnum > 5)
	{
		while (!(cin >> shipnum))
		{
			cout << "Invalid! Must be 1-5!: ";
			cin.clear();
			cin.ignore(123, '\n');
		}
	}	

	//sets the AI's difficulty
	int difficulty = 0;
	std::cout << "What difficulty would you like the AI to be (1 = easy, 2 = medium, 3 = hard)?: ";
	std::cin >> difficulty;
	while (difficulty < 1 || difficulty > 3)
	{
		std::cout << "That is not a valid difficulty, try again (1 = easy, 2 = medium, 3 = hard): ";
		std::cin >> difficulty; 
	}
	computer.setDifficulty(difficulty);
	
	//Place player 1's ships
	for (int i = 1; i <= shipnum; i++)
	{
		chooseShipPosition1:

			//blank Board
			display.friendlyBoard(player1.my_ships.m_board);
			char direction = 'u'; //default direction is up

			if (i == 1)
			{
				cout << "\nPlayer 1, Where do you want to place 1X" << i << " on the grid (row(1-9) col(A-I))? ";
				while(!(cin >> row)||row < 1 || row > 9)
				{
					cout << "Invalid input! Row must be 1-9!: ";
					cin.clear();
					cin.ignore(123, '\n');
				}
				cout << "Now enter a column A-I: ";
				cin >> c_col;
				cout << "\n";
				while(!validColumn(c_col))
				{
					cin >> c_col;
				}
				col = charToInt(c_col);
			}
			else
			{
				cout << "\nChoose a pivot coordinate for 1X" << i << " ship on the grid (row(1-9) col(A-I)): ";
				while (!(cin >> row)||row < 1 || row > 9)
				{
					cout << "Invalid input! Row must be 1-9!: ";
					cin.clear();
					cin.ignore(123, '\n');
				}
				cout << "Now enter a column A-I: ";
				cin >> c_col;
				while (!validColumn(c_col))
				{
					cin >> c_col;
				}

			chooseShipDirection1:
				cout << "Up, Down, Left, or Right from pivot? (U, D, L, R): ";
				cin >> direction;
			}
			col = charToInt(c_col); // convert char to int
			row--; // decrement row by 1 for indexing array
			direction = toupper(direction);

			if (direction != 'U' && direction != 'D' && direction != 'L' && direction != 'R')
			{
				cout << "Invalid direction input!\n";
				goto chooseShipDirection1;
			}
			if (!player1.PlaceShip(i, row, col, direction))
			{
				cout << "Ship could not be placed there. \n";
				goto chooseShipPosition1;
			}
	}

	//print last time so player can see 1x5 ship placed
	display.friendlyBoard(player1.my_ships.m_board);

	computer.SetNumShips(shipnum);
	shipofai.setShipNumber(numShipCoords(shipnum));

	//place the AI's ships
	for (int i = 1; i <= shipnum; ++i)
	{
		while (!computer.PlaceShip(i, std::rand() % 9, std::rand() % 9, arr_directions[std::rand() % 4])) {}		}

	//print last time so player can see 1x5 ship placed
	display.friendlyBoard(computer.my_ships.m_board);

	std::cout << "\nThe AI's ships have been placed.\n";

	run_PvAi();
}


void Executive::run_PvP() 
{
	cout << "\nNow play battleship!\n";

	int round = 1;
	bool player1torpedo = true;
	bool player2torpedo = true;
	string playershot = "";

	while (!shipofplayer1.isSunk() || !shipofplayer2.isSunk())
	{
		if (round % 2 == 1)
		{
			cout << "Player 1's turn!\n";
			cout << "You have been hit " << shipofplayer1.getHit() << " times\n";
			//Print boards before fire
			display.matchFrame(1, player1.enemy_ships.m_board, player1.my_ships.m_board);

			do
			{
				cout << "\nDo you want to fire a torpedo or a regular shot?";
				cout << "\nEnter torp for the torpedo and shot for the regular shot: ";

				cin >> playershot;
			} while(playershot != "torp" && playershot != "Torp" && playershot != "shot" && playershot != "Shot");

			if ((playershot == "torp" || playershot == "Torp") && player1torpedo == true)
			{
				string colorrow = "";
				cout << "\nEnter col to shoot from a column and row to shoot from a row: ";
				cin >> colorrow;

				while (colorrow != "row" && colorrow != "Row" && colorrow != "col" && colorrow != "Col")
				{
					cout << "Invalid! Must be row or col: ";
					cin >> colorrow;
				}

				if (colorrow != "row" || colorrow != "Row")
				{
					cout << "\nchoose a row between 1 and 9: ";
					while (!(cin >> row) || row < 1 || row > 9)
					{
						cout << "Invalid! Must be 1-9!: ";
						cin.clear();
						cin.ignore(123, '\n');
					}
					row --;
					firetorpedo(round, row, false, false);
					player1torpedo = false;
					if (shipofplayer2.isSunk()){
						break;
					}
				}
				else if (colorrow != "col" || colorrow != "Col")
				{
					cout << "\nchoose a Column between A and I ";
					cin >> c_col;
					while (!validColumn(c_col))
					{
						cin >> c_col;
					}
					col = charToInt(c_col);
					firetorpedo(round, col, true, false);
					player1torpedo = false;
					if (shipofplayer2.isSunk()){
						break;
					}
				}
			}
			else if((playershot == "torp" || playershot == "Torp") && player1torpedo == false)
			{
				cout << "\nyou shot your torpedo already! ";
				goto chooseFire1;
			}
			else if(playershot == "shot" || playershot == "Shot")
			{
				chooseFire1:
				cout << "\nChoose the coordinate that you want to fire (row(1 - 9) col(A - I)): ";
				while (!(cin >> row) || row < 1 || row > 9)
				{
					// cout <<"row = "<<row<<'\n';
					cout << "Invalid! Must be 1-9!: ";
					cin.clear();
					cin.ignore(123, '\n');
				}
				cin >> c_col;
				while (!validColumn(c_col))
				{
					cin >> c_col;
				}
				col = charToInt(c_col);
				row --;


				if (player2.CheckHit(row, col))
				{
					display.hit();
					shipofplayer2.setHit();
					player1.UpdateEnemyBoard(row, col, true);
					if (shipofplayer2.isSunk()){
						cout << "Player 1 wins!\n";
						break;
					}
				}

				else if(player2.my_ships.getValue(row, col) == 'X')
				{
					//cout <<player2.my_ships.getValue(row, col);
					cout << "\n\nYou've already hit that spot!\n";
					goto chooseFire1;
				}
				else if(player1.enemy_ships.getValue(row, col) == 'O')
				{
					cout <<"\n\nYou've already fire this point!\n";
					goto chooseFire1;
				}
				else
				{
					display.miss();
					player1.UpdateEnemyBoard(row, col, false);
					player2.my_ships.updateBoard(row, col, 'O');
				}
			}
		}
		else
		{
			cout << "Player 2's turn!\n";
			cout << "You have been hit " << shipofplayer2.getHit() << " times\n";
			//Print boards before fire
			display.matchFrame(2, player2.enemy_ships.m_board, player2.my_ships.m_board);

			do
			{
				cout << "\nDo you want to fie a torpedo or a regular shot?";
				cout << "\nEnter torp for the torpedo and shot for the regular shot: ";

				cin >> playershot;
			} while(playershot != "torp" && playershot != "Torp" && playershot != "shot" && playershot != "Shot");

			if ((playershot == "torp" || playershot == "Torp") && player2torpedo == true)
			{
				string colorrow = "";
				cout << "\nEnter col to shoot from a column and row to shoot from a row: ";
				cin >> colorrow;

				while (colorrow != "row" && colorrow != "Row" && colorrow != "col" && colorrow != "Col")
				{
					cout << "Invalid! Must be row or col: ";
					cin >> colorrow;
				}

				if (colorrow == "row" || colorrow == "Row")
				{
					cout << "\nchoose a row between 1 and 9: ";
					while (!(cin >> row) || row < 1 || row > 9)
					{
						cout << "Invalid! Must be 1-9!: ";
						cin.clear();
						cin.ignore(123, '\n');
					}
					row --;
					firetorpedo(round, row, false, false);
					player2torpedo = false;
					if (shipofplayer1.isSunk()){
						break;
					}
				}
				else if (colorrow == "col" || colorrow == "Col")
				{
					cout << "\nchoose a Column between A and I ";
					cin >> c_col;
					while (!validColumn(c_col))
					{
						cin >> c_col;
					}
					col = charToInt(c_col);
					firetorpedo(round, col, true, false);
					player2torpedo = false;
					if (shipofplayer1.isSunk()){
						break;
					}
				}
			}
			else if((playershot == "torp" || playershot == "Torp") && player2torpedo == false)
			{
				cout << "\nyou shot your torpedo already! ";
				goto chooseFire2;
			}
			else if(playershot == "shot" || playershot == "Shot")
			{
				chooseFire2:
				cout << "\nChoose the coordinate that you want to fire (row(1 - 9) col(A - I)): ";
				while (!(cin >> row) || row < 1 || row > 9)
				{
					cout << "Invalid! Must be 1-9!: ";
					cin.clear();
					cin.ignore(123, '\n');
				}
				cin >> c_col;
				while (!validColumn(c_col))
				{
					cin >> c_col;
				}
				col = charToInt(c_col);
				row --;

				if (player1.CheckHit(row, col))
				{
					display.hit();
					shipofplayer1.setHit();
					player2.UpdateEnemyBoard(row, col, true);
					if (shipofplayer1.isSunk()){
						cout << "Player 2 wins!\n";
						break;
					}
				}

				else if(player1.my_ships.getValue(row, col) == 'X')
				{
					//cout <<player2.my_ships.getValue(row, col);
					cout << "\n\nYou've already hit that spot!\n";
					goto chooseFire2;
				}
				else if(player2.enemy_ships.getValue(row, col) == 'O')
				{
					cout <<"\n\nYou've already fire this point!\n";
					goto chooseFire2;
				}
				else
				{
					display.miss();
					player2.UpdateEnemyBoard(row, col, false);
					player1.my_ships.updateBoard(row, col, 'O');
				}
			}
		}
		if (round % 20 == 0)
		{
	 		player1torpedo = true;
			player2torpedo = true;
		}
		round++;
		WaitEnter();
	}
}

void Executive::run_PvAi() 
{
	cout << "\nNow play battleship!\n";

	int round = 1;
	bool player1torpedo = true;
	//bool player2torpedo = true; need to add is for the AI 
	string playershot = "";

	while (!shipofplayer1.isSunk() || !shipofai.isSunk())
	{
		if (round % 2 == 1)
		{
			cout << "Player 1's turn!\n";
			cout << "You have been hit " << shipofplayer1.getHit() << " times\n";
			//Print boards before fire
			display.matchFrame(1, player1.enemy_ships.m_board, player1.my_ships.m_board);

			do
			{
				cout << "\nDo you want to fire a torpedo or a regular shot?";
				cout << "\nEnter torp for the torpedo and shot for the regular shot: ";

				cin >> playershot;
			} while(playershot != "torp" && playershot != "Torp" && playershot != "shot" && playershot != "Shot");

			if ((playershot == "torp" || playershot == "Torp") && player1torpedo == true)
			{
				string colorrow = "";
				cout << "\nEnter col to shoot from a column and row to shoot from a row: ";
				cin >> colorrow;

				while (colorrow != "row" && colorrow != "Row" && colorrow != "col" && colorrow != "Col")
				{
					cout << "Invalid! Must be row or col: ";
					cin >> colorrow;
				}

				if (colorrow != "row" || colorrow != "Row")
				{
					cout << "\nchoose a row between 1 and 9: ";
					while (!(cin >> row) || row < 1 || row > 9)
					{
						cout << "Invalid! Must be 1-9!: ";
						cin.clear();
						cin.ignore(123, '\n');
					}
					row --;
					firetorpedo(round, row, false, true);
					player1torpedo = false;
					if (shipofai.isSunk()){
						break;
					}
				}
				else if (colorrow != "col" || colorrow != "Col")
				{
					cout << "\nchoose a Column between A and I ";
					cin >> c_col;
					while (!validColumn(c_col))
					{
						cin >> c_col;
					}
					col = charToInt(c_col);
					firetorpedo(round, col, true, true);
					player1torpedo = false;
					if (shipofai.isSunk()){
						break;
					}
				}
			}
			else if((playershot == "torp" || playershot == "Torp") && player1torpedo == false)
			{
				cout << "\nyou shot your torpedo already! ";
				goto chooseFire1;
			}
			else if(playershot == "shot" || playershot == "Shot")
			{
				chooseFire1:
				cout << "\nChoose the coordinate that you want to fire (row(1 - 9) col(A - I)): ";
				while (!(cin >> row) || row < 1 || row > 9)
				{
					// cout <<"row = "<<row<<'\n';
					cout << "Invalid! Must be 1-9!: ";
					cin.clear();
					cin.ignore(123, '\n');
				}
				cin >> c_col;
				while (!validColumn(c_col))
				{
					cin >> c_col;
				}
				col = charToInt(c_col);
				row --;


				if (computer.CheckHit(row, col))
				{
					display.hit();
					shipofai.setHit();
					player1.UpdateEnemyBoard(row, col, true);
					if (shipofai.isSunk()){
						cout << "Player 1 wins!\n";
						break;
					}
				}
				else if(computer.my_ships.getValue(row, col) == 'X')
				{
					cout << computer.my_ships.getValue(row, col);
					cout << "\n\nYou've already hit that spot!\n";
					goto chooseFire1;
				}
				else if(player1.enemy_ships.getValue(row, col) == 'O')
				{
					cout <<"\n\nYou've already fire this point!\n";
					goto chooseFire1;
				}
				else
				{
					display.miss();
					player1.UpdateEnemyBoard(row, col, false);
					computer.my_ships.updateBoard(row, col, 'O');
				}
			}
		}
		else
		{
			cout << "BattleshipAI's turn!\n";
			// TODO remove the following display. it is used only for testing
			display.matchFrame(2, computer.enemy_ships.m_board, computer.my_ships.m_board);

			chooseFireAI:
			
			std::string AIshot = "";
			
			if(computer.getDifficulty() == 3){	//AI is set to Hard

				while(true){

					AIshot = computer.fireShot();
					row = AIshot[0];
					c_col = AIshot[1];

					col = charToInt(c_col);
					row --;

					if (player1.Only_CheckHit(row, col) == true){
						break;
					}
				}


			} else {	//AI is not set to Hard

				AIshot = computer.fireShot();

				row = AIshot[0];
				c_col = AIshot[1];

				col = charToInt(c_col);
				row --;
			}

			if (player1.CheckHit(row, col))
			{
				display.hit();
				shipofplayer1.setHit();
				computer.UpdateEnemyBoard(row, col, true);
				if (shipofplayer1.isSunk()){
					cout << "BattleshipAI Wins!\n";
					break;
				}
			}

			else if(player1.my_ships.getValue(row, col) == 'X')
			{
				goto chooseFireAI;
			}
			else if(computer.enemy_ships.getValue(row, col) == 'O')
			{
				goto chooseFireAI;
			}
			else
			{
				cout << AIshot << '\n';
				display.miss();
				computer.UpdateEnemyBoard(row, col, false);
				player1.my_ships.updateBoard(row, col, 'O');
			}
		}
		round++;
		WaitEnter();
	}
}


void Executive::firetorpedo(int turns, int firepostion, bool iscol, bool playerVai)
{
	if(playerVai == false) // see if you fighting the AI
	{
		if (turns % 2 == 1)// see if it's player1 or player2
		{
			if (iscol == true)// see if it's a row or col to fire from
			{
				for (int i = 0; i < 9; i++)
				{
					if (player2.CheckHit(i, firepostion))
					{
						display.hit();
						shipofplayer2.setHit();
						player1.UpdateEnemyBoard(i, firepostion, true);
						if (shipofplayer2.isSunk()){
							cout << "Player 1 wins!\n";
							break;
						}
						break;
					}
					else
					{
						player1.UpdateEnemyBoard(i, firepostion, false);
						if (player2.my_ships.getValue(i, firepostion) != 'O')
						{
							player2.my_ships.updateBoard(i, firepostion, 'O');
						}
					}
				}
			}
			else
			{
				for (int i = 0; i < 9; i++)
				{
					if (player2.CheckHit(firepostion, i))
					{
						display.hit();
						shipofplayer2.setHit();
						player1.UpdateEnemyBoard(firepostion, i, true);
						if (shipofplayer2.isSunk()){
							cout << "Player 1 wins!\n";
							break;
						}
						break;
					}
					else
					{
						player1.UpdateEnemyBoard(firepostion, i, false);
						if (player2.my_ships.getValue(firepostion, i) != 'O')
						{
							player2.my_ships.updateBoard(firepostion, i, 'O');
						}
					}
				}
			}
		}
		else
		{
			if (iscol == true) // see if it's a row or col to fire from
			{
				for (int i = 0; i < 9; i++)
				{
					if (player1.CheckHit(i, firepostion))
					{
						display.hit();
						shipofplayer1.setHit();
						player2.UpdateEnemyBoard(i, firepostion, true);
						if (shipofplayer1.isSunk()){
							cout << "Player 2 wins!\n";
							break;
						}
						break;
					}
					else
					{
						player2.UpdateEnemyBoard(i, firepostion, false);
						if (player1.my_ships.getValue(i, firepostion) != 'O')
						{
							player1.my_ships.updateBoard(i, firepostion, 'O');
						}
					}
				}
			}
			else
			{
				for (int i = 0; i < 9; i++)
				{
					if (player1.CheckHit(firepostion, i))
					{
						display.hit();
						shipofplayer1.setHit();
						player2.UpdateEnemyBoard(firepostion, i, true);
						if (shipofplayer1.isSunk()){
							cout << "Player 2 wins!\n";
							break;
						}
						break;
					}
					else
					{
						player2.UpdateEnemyBoard(firepostion, i, false);
						if (player1.my_ships.getValue(firepostion, i) != 'O')
						{
							player1.my_ships.updateBoard(firepostion, i, 'O');
						}
					}
				}
			}
		}
	}
	else
	{
		if (turns % 2 == 1)// see if it's player1 or player2
		{
			if (iscol == true)// see if it's a row or col to fire from
			{
				for (int i = 0; i < 9; i++)
				{
					if (computer.CheckHit(i, firepostion))
					{
						display.hit();
						shipofai.setHit();
						player1.UpdateEnemyBoard(i, firepostion, true);
						if (shipofplayer2.isSunk()){
							cout << "Player 1 wins!\n";
							break;
						}
						break;
					}
					else
					{
						player1.UpdateEnemyBoard(i, firepostion, false);
						if (computer.my_ships.getValue(i, firepostion) != 'O')
						{
							computer.my_ships.updateBoard(i, firepostion, 'O');
						}
					}
				}
			}
			else
			{
				for (int i = 0; i < 9; i++)
				{
					if (computer.CheckHit(firepostion, i))
					{
						display.hit();
						shipofai.setHit();
						player1.UpdateEnemyBoard(firepostion, i, true);
						if (shipofai.isSunk()){
							cout << "Player 1 wins!\n";
							break;
						}
						break;
					}
					else
					{
						player1.UpdateEnemyBoard(firepostion, i, false);
						if (computer.my_ships.getValue(firepostion, i) != 'O')
						{
							computer.my_ships.updateBoard(firepostion, i, 'O');
						}
					}
				}
			}
		}
		else
		{
			if (iscol == true) // see if it's a row or col to fire from
			{
				for (int i = 0; i < 9; i++)
				{
					if (player1.CheckHit(i, firepostion))
					{
						display.hit();
						shipofplayer1.setHit();
						computer.UpdateEnemyBoard(i, firepostion, true);
						if (shipofplayer1.isSunk()){
							cout << "Player 2 wins!\n";
							break;
						}
						break;
					}
					else
					{
						computer.UpdateEnemyBoard(i, firepostion, false);
						if (player1.my_ships.getValue(i, firepostion) != 'O')
						{
							player1.my_ships.updateBoard(i, firepostion, 'O');
						}
					}
				}
			}
			else
			{
				for (int i = 0; i < 9; i++)
				{
					if (player1.CheckHit(firepostion, i))
					{
						display.hit();
						shipofplayer1.setHit();
						computer.UpdateEnemyBoard(firepostion, i, true);
						if (shipofplayer1.isSunk()){
							cout << "Player 2 wins!\n";
							break;
						}
						break;
					}
					else
					{
						computer.UpdateEnemyBoard(firepostion, i, false);
						if (player1.my_ships.getValue(firepostion, i) != 'O')
						{
							player1.my_ships.updateBoard(firepostion, i, 'O');
						}
					}
				}
			}
		}
	}
}
