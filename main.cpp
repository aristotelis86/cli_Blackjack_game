// Just a simple command line game of Blackjack
// Aces are fixed to count as 11...

#include <iostream>
#include <array>
#include <cstdlib> // for std::rand() and std::srand()
#include <ctime> // for std::time()
#include "game_classes.h"

void printCard(const Card &card) {
	switch (card.rank) {
	case RANK_2: std::cout << '2'; break;
	case RANK_3: std::cout << '3'; break;
	case RANK_4: std::cout << '4'; break;
	case RANK_5: std::cout << '5'; break;
	case RANK_6: std::cout << '6'; break;
	case RANK_7: std::cout << '7'; break;
	case RANK_8: std::cout << '8'; break;
	case RANK_9: std::cout << '9'; break;
	case RANK_10: std::cout << "10"; break;
	case RANK_JACK: std::cout << 'J'; break;
	case RANK_QUEEN: std::cout << 'Q'; break;
	case RANK_KING: std::cout << 'K'; break;
	case RANK_ACE: std::cout << 'A'; break;
	}
	switch (card.suit) {
	case CLUB: std::cout << 'C'; break;
	case DIAMOND: std::cout << 'D'; break;
	case HEART: std::cout << 'H'; break;
	case SPADE: std::cout << 'S'; break;
	}
}

void printDeck(const std::array<Card,52> &theDeck) {
	for (const auto &card : theDeck) {
		printCard(card);
		std::cout << ' ';
	}
	std::cout << '\n';
}

void swapCard(Card &card1, Card &card2) {
	Card temp = card1;
	card1 = card2;
	card2 = temp;
}

int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);  // static used for efficiency, so we only calculate this value once
															// evenly distribute the random number across our range
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void shuffleDeck(std::array<Card, 52> &deck) {
	std::cout << "Shuffling... \n";
	using index_t = std::array<Card, 52>::size_type;
	
	for (index_t icard = 0; icard < 52; ++icard) {
		// Generate a number
		index_t rand_card = getRandomNumber(0, 51);
		//std::cout << "Swapping " << icard << " with " << rand_card << '\n';
		swapCard(deck[icard], deck[rand_card]);
	}
}

int getCardValue(const Card &card) {
	switch (card.rank) {
	case RANK_2: return 2; 
	case RANK_3: return 3;
	case RANK_4: return 4;
	case RANK_5: return 5;
	case RANK_6: return 6;
	case RANK_7: return 7;
	case RANK_8: return 8;
	case RANK_9: return 9;
	case RANK_10: return 10;
	case RANK_JACK: return 10;
	case RANK_QUEEN: return 10;
	case RANK_KING: return 10;
	case RANK_ACE: return 11;
	}
}

BlackjackResult playBlakjack(const std::array<Card, 52> &deck) {

	const Card *cardPtr = &deck[0];
	int dealerTotal = 0;
	int playerTotal = 0;

	// Initial moves
	dealerTotal += getCardValue(*cardPtr++);
	playerTotal += getCardValue(*cardPtr++);
	

	char choice;
	do {
		playerTotal += getCardValue(*cardPtr++);
		if (playerTotal > 21) return BLACKJACK_DEALER_WIN;

		std::cout << "Your current total is " << playerTotal << '\n';
		std::cout << "Do you want to [h]it or [s]tand? ";
		std::cin >> choice;
	} while (choice == 'h' || choice == 'H');

	while (dealerTotal <= 17) {
		dealerTotal += getCardValue(*cardPtr++);
		if (dealerTotal > 21) return BLACKJACK_PLAYER_WIN;
	}

	if (playerTotal > dealerTotal) return BLACKJACK_PLAYER_WIN;
	else if (playerTotal < dealerTotal) return BLACKJACK_DEALER_WIN;
	else return BLACKJACK_TIE;
}

int main()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr))); // set initial seed value to system clock
	std::rand();
	std::array<Card,52> deck;

	using index_t = std::array<Card, 52>::size_type;
	index_t icard;

	std::cout << "   Hey, let's play Blackjack! \n";
	std::cout << "-------------------------------- \n";

	char choice;
	do {

		std::cout << "Here we go: \n";
		icard = 0;
		for (int isuit = 0; isuit < MAX_SUIT; ++isuit) {
			for (int irank = 0; irank < MAX_RANK; ++irank) {
				deck[icard].suit = static_cast<Suit>(isuit);
				deck[icard].rank = static_cast<Rank>(irank);
				++icard;
			}
		}

		printDeck(deck);
		std::cout << '\n';
		shuffleDeck(deck);
		//printDeck(deck); // in case you want to verify the game is not rigged!

		BlackjackResult outcome = playBlakjack(deck);

		if (outcome == BLACKJACK_PLAYER_WIN) std::cout << "You win!\n";
		else if (outcome == BLACKJACK_DEALER_WIN) std::cout << "You lose...\n";
		else std::cout << "It's a tie...!\n";

		std::cout << '\n';
		std::cout << "Would you like to try again? ";
		std::cin >> choice;

	} while (choice != 'n');

    return 0;
}

