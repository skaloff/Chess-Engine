#include <iostream>

typedef unsigned long long  U64;

#define getBit(bitboard, square) (bitboard & (1ULL << square))  //check if this bit is used
#define setBit(bitboard, square) (bitboard |= (1ULL << square))  //set bit in square
#define removeBit(bitboard, square) (getBit(bitboard, square) ? bitboard ^= (1ULL << square) : 0)  //remove bit

const U64 notAfile = 18374403900871474942ULL;
const U64 notHfile = 9187201950435737471ULL;
const U64 notGHfile = 4557430888798830399ULL;
const U64 notABfile = 18229723555195321596ULL;

enum Board
{
	a1, b1, c1, d1, e1, f1, g1, h1,
	a2, b2, c2, d2, e2, f2, g2, h2,
	a3, b3, c3, d3, e3, f3, g3, h3,
	a4, b4, c4, d4, e4, f4, g4, h4,
	a5, b5, c5, d5, e5, f5, g5, h5,
	a6, b6, c6, d6, e6, f6, g6, h6,
	a7, b7, c7, d7, e7, f7, g7, h7,
	a8, b8, c8, d8, e8, f8, g8, h8
};

enum Side { white, black };

void printBinary(U64 number) 
{
	int numBits = sizeof(U64) * 8;

	for (int i = numBits - 1; i >= 0; i--) 
	{
		bool bit = (number >> i) & 1;
		std::cout << bit;
	}
	std::cout << std::endl;
}

void PrintBitboard(U64 bitboard)
{
	for (int rank = 7; rank >= 0; rank--) 
	{
		for (int file = 0; file < 8; file++) 
		{		
			//convert rank & file into square index
			int square = rank * 8 + file;

			if (!file)
			{
				std::cout << rank + 1 << "  ";
			}

			std::cout << (getBit(bitboard, square) ? 1 : 0) << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "   a b c d e f g h\n";

	std::cout << "\n   Bitboard: " << (bitboard);
	std::cout << "\n";
}

//pawn attacks table

U64 pawnAttacks[2][64];
U64 knightAttacks[64];

U64 PawnAttackMask(int Side, int square)
{
	U64 attacks = 0ULL;
	U64 bitboard = 0ULL;

	setBit(bitboard, square);

	if (!Side) //if white
	{
		if ((bitboard << 7) & notHfile)
			attacks |= (bitboard << 7);
		if ((bitboard << 9) & notAfile)
			attacks |= (bitboard << 9);
	}
	else //if black
	{
		if ((bitboard >> 7) & notAfile)
			attacks |= (bitboard >> 7);
		if ((bitboard >> 9) & notHfile)
			attacks |= (bitboard >> 9);
	}

	return attacks;
};

U64 KnightAttackMask(int square)
{
	U64 bitboard = 0ULL;
	U64 attacks = 0ULL;

	setBit(bitboard, square);

	if ((bitboard << 6) & notGHfile)
		attacks |= (bitboard << 6);
	if ((bitboard << 10) & notABfile)
		attacks |= (bitboard << 10);
	if ((bitboard << 15) & notHfile)
		attacks |= (bitboard << 15);
	if ((bitboard << 17) & notAfile)
		attacks |= (bitboard << 17);
	if ((bitboard >> 6) & notABfile)
		attacks |= (bitboard >> 6);
	if ((bitboard >> 10) & notGHfile)
		attacks |= (bitboard >> 10);
	if ((bitboard >> 15) & notAfile)
		attacks |= (bitboard >> 15);
	if ((bitboard >> 17) & notHfile)
		attacks |= (bitboard >> 17);

	return attacks;
}

void InitPawnAttacks()
{
	for (int square = 0; square < 64; square++)
	{
		pawnAttacks[white][square] = PawnAttackMask(white, square);
		pawnAttacks[black][square] = PawnAttackMask(black, square);
	}
}

void InitKnightAttacks()
{
	for (int square = 0; square < 64; square++)
	{
		knightAttacks[square] = KnightAttackMask(square);
	}
}

int main()
{
	U64 bitboard = 0ULL;
	InitPawnAttacks();
	InitKnightAttacks();
	/*bitboard = PawnAttackMask(white, c1);
	PrintBitboard(bitboard);*/

	bitboard = KnightAttackMask(b4);

	for (int square = 0; square < 64; square++)
	{
		PrintBitboard(knightAttacks[square]);
	}

}