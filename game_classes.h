#ifndef GAME_CLASSES_H
#define GAME_CLASSES_H

enum Rank
{
	RANK_2,
	RANK_3,
	RANK_4,
	RANK_5,
	RANK_6,
	RANK_7,
	RANK_8,
	RANK_9,
	RANK_10,
	RANK_JACK,
	RANK_QUEEN,
	RANK_KING,
	RANK_ACE,
	MAX_RANK
};

enum Suit
{
	CLUB,
	DIAMOND,
	HEART,
	SPADE,
	MAX_SUIT
};

enum BlackjackResult
{
	BLACKJACK_PLAYER_WIN,
	BLACKJACK_DEALER_WIN,
	BLACKJACK_TIE
};


struct Card {
	Rank rank;
	Suit suit;
};

#endif

