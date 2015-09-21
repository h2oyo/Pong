// Pong.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "sfwdraw.h"
#include <iostream>
#include <chrono>
#include <thread>
struct Player
{
	float xpos;
	float ypos;
	float xpos2;
	float ypos2;
};
int width = 800;
int height = 600;


float xacc = 0, yacc = 0;	  // acceleration
float xvel = 0, yvel = 0;
float xacc1 = 0, yacc1 = 0;
float xvel1 = 150, yvel1 = 150;
float xacc2 = 0, yacc2 = 0;
float xvel2 = 0, yvel2 = 0;	  // velocity
float speed = 100;
float speed1 = 10;
float speed2 = 10;
int player1score = 0;
int player2score = 0;
float xpos1 = 400;
float ypos1 = 300;

int Score[2] = { player1score, player2score};

void Walls()
{
	sfw::drawLine(5, 5, 5, height - 5);
	sfw::drawLine(5, 5, width - 5, 5);

	sfw::drawLine(width - 5, height - 5, 5, height - 5);
	sfw::drawLine(width - 5, height - 5, width - 5, 5);

}


void Player1 ()
{
	Player player1;

	player1.xpos = 25;
	player1.ypos = 250;
	player1.xpos2 = 25;
	player1.ypos2 = 350;
	
	player1.ypos += yvel ;
	player1.ypos2 += yvel;

	yacc = 0;
	
	if (sfw::getKey('w')&& player1.ypos > 10 ) yacc = -speed1;
	if (sfw::getKey('s') && player1.ypos <490) yacc = speed1;
	
	yvel += yacc;

	
	sfw::drawLine(player1.xpos, player1.ypos, player1.xpos2, player1.ypos2);
	sfw::drawLine(player1.xpos + 20, player1.ypos, player1.xpos2 + 20, player1.ypos2);
	sfw::drawLine(player1.xpos, player1.ypos, player1.xpos2+20, player1.ypos2-100);
	sfw::drawLine(player1.xpos +20, player1.ypos +100, player1.xpos2, player1.ypos2);
	

	//homeboy Izaac helped me with this
	if (xpos1 < player1.xpos + 30
		&&
		xpos1 > player1.xpos2
		&&
		ypos1 < player1.ypos + 100
		&&
		ypos1 > player1.ypos
		&&
		ypos1 > player1.xpos)
	{
	
		xvel1 = -xvel1* 1.1;
		std::cout << xvel1 << "\n";
	}
	if (xvel1 > 200)
	{
		xvel = 200;
	}
	if (xvel1 < -200)
	{
		xvel = -200;
	}
	

}
void Player2()
{
	Player player2;
	player2.xpos = 725;
	player2.xpos2 = 725;
	player2.ypos = 250;
	player2.ypos2 = 350;

	player2.ypos += yvel2;
	player2.ypos2 += yvel2;

	yacc2 = xacc2 = 0;

	if (sfw::getKey('o') && player2.ypos> 10) yacc2 = -speed2;
	if (sfw::getKey('l') && player2.ypos <490) yacc2 = speed2;
	xvel2 += xacc2;
	yvel2 += yacc2;

	sfw::drawLine(player2.xpos, player2.ypos, player2.xpos2, player2.ypos2);
	sfw::drawLine(player2.xpos + 20, player2.ypos, player2.xpos2 + 20, player2.ypos2);
	sfw::drawLine(player2.xpos, player2.ypos, player2.xpos2 + 20, player2.ypos2 - 100);
	sfw::drawLine(player2.xpos + 20, player2.ypos + 100, player2.xpos2, player2.ypos2);

	if (xpos1 > player2.xpos - 10
		&&
		xpos1 < player2.xpos2
		&&
		ypos1 > player2.ypos
		&&
		ypos1 < player2.ypos + 100
		&&
		ypos1 < player2.xpos)
	{
			xvel1 = -xvel1 * 1.1;

	}
	if (xvel1 > 200)
	{
		xvel = 200;
	}
	if (xvel1 < -200)
	{
		xvel = -200;
	}

}

void Ball()
{
	// we haven't covered frame independent movement yet,
	// but we'll use some euler integration
	// we also haven't gotten into vector math yet,
	// so we'll use cardinal speeds float xpos = 400, ypos = 300;
	

	xpos1 -= xvel1 * sfw::getDeltaTime();
	ypos1 -= yvel1 * sfw::getDeltaTime();

	xvel1 -= xacc1 * sfw::getDeltaTime();
	yvel1 -= yacc1 * sfw::getDeltaTime();
	sfw::drawCircle(xpos1, ypos1, 5);

	if (ypos1 +10  > 600)
	{
		yvel1  = -yvel1 ;
	
	}

	if (ypos1 +10  < 20)
	{
		yvel1 = -yvel1 ;
	}

	
		if (xpos1 > 795)
		{
			player1score++;
			std::cout << "Player 1 Score:" << player1score << "\n";
			
			xpos1 = 400, ypos1 = 300;
			xvel1 = 150, yvel1 = 150;
		

		}
		if (xpos1 < 0)
		{
			player2score++;
			std::cout << "Player 2 Score:" << player2score << "\n";
	
			xpos1 = 400, ypos1 = 300;
			xvel1 = 150, yvel1 = 150;
		}

	}

int main()

{
	std::cout << "Ready to play Pong?" << "\n";
	system("pause");

		sfw::initContext(width, height, "Pong");
	

	// then we need to update our buffers, poll for input, etc.
	while (sfw::stepContext())
	{
		
		
		Walls();
		Player1();
		Player2();
		Ball();
		if (player1score > 4)
		{
			std::cout << "Player 1 wins" << "\n" <<"Player 1 Score:" << player1score << "\n" << "Player 2 Score:" << player2score << "\n";
			sfw::termContext();
			system("pause");
		}

		if (player2score > 4)
		{
			std::cout << "Player 2 wins" << "\n" << "Player 2 Score:" << player2score << "\n" << "Player 1 Score:" << player1score << "\n";
			sfw::termContext();
			system("pause");
		}

	}
	//395 405 250 350
	sfw::termContext();
	
    return 0;
}


