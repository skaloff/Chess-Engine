#include <iostream>

typedef unsigned long long  U64;

#define getBit(bitboard, square) (bitboard & (1ULL << square))  //check if this bit is used
#define setBit(bitboard, square) (bitboard |= (1ULL << square))  //set bit in square
#define removeBit(bitboard, square) (getBit(bitboard, square) ? bitboard ^= (1ULL << square) : 0)  //remove bit

const U64 notAfile = 18374403900871474942ULL;
const U64 notHfile = 9187201950435737471ULL;
const U64 notGHfile = 4557430888798830399ULL;
const U64 notABfile = 18229723555195321596ULL;

U64 pawnAttacks[2][64];
U64 knightAttacks[64];
U64 kingAttacks[64];
U64 bishopAttacks[64];
U64 rookAttacks[64];

enum Board
{
	a8, b8, c8, d8, e8, f8, g8, h8,
	a7, b7, c7, d7, e7, f7, g7, h7,
	a6, b6, c6, d6, e6, f6, g6, h6,
	a5, b5, c5, d5, e5, f5, g5, h5,
	a4, b4, c4, d4, e4, f4, g4, h4,
	a3, b3, c3, d3, e3, f3, g3, h3,
	a2, b2, c2, d2, e2, f2, g2, h2,
	a1, b1, c1, d1, e1, f1, g1, h1
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
	for (int rank = 0; rank < 8; rank++) 
	{
		for (int file = 0; file < 8; file++) 
		{		
			//convert rank & file into square index
			int square = rank * 8 + file;

			if (!file)
			{
				std::cout << (8 - rank) << "  ";
			}

			std::cout << (getBit(bitboard, square) ? 1 : 0) << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "   a b c d e f g h\n";

	std::cout << "\n   Bitboard: " << (bitboard);
	std::cout << "\n";
}

U64 pawnAttackMask(int Side, int square)
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

U64 knightAttackMask(int square)
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

U64 kingAttackMask(int square)
{
	U64 bitboard = 0ULL;
	U64 attacks = 0ULL;

	setBit(bitboard, square);

	if ((bitboard << 1) & notAfile)
		attacks |= (bitboard << 1);
	if ((bitboard << 7) & notHfile)
		attacks |= (bitboard << 7);
	attacks |= (bitboard << 8);
	if ((bitboard << 9) & notAfile)
		attacks |= (bitboard << 9);
	if ((bitboard >> 1) & notHfile)
		attacks |= (bitboard >> 1);
	if ((bitboard >> 7) & notAfile)
		attacks |= (bitboard >> 7);
	attacks |= (bitboard >> 8);
	if ((bitboard >> 9) & notHfile)
		attacks |= (bitboard >> 9);

	return attacks;
}

U64 bishopAttackMask(int square)
{
	U64 attacks = 0ULL;

	int r, f;

	int tr = square / 8;
	int tf = square % 8;

	for (r = tr + 1, f = tf + 1; r < 7 && f < 7; r++, f++)
		attacks |= (1ULL << (r * 8 + f));
	for (r = tr - 1, f = tf - 1; r > 0 && f > 0; r--, f--)
		attacks |= (1ULL << (r * 8 + f));
	for (r = tr + 1, f = tf - 1; r < 7 && f > 0; r++, f--)
		attacks |= (1ULL << (r * 8 + f));
	for (r = tr - 1, f = tf + 1; r > 0 && f < 7; r--, f++)
		attacks |= (1ULL << (r * 8 + f));
	
	return attacks;
}

U64 bishopAttackMaskOnTheFly(int square, U64 block)
{
	U64 attacks = 0ULL;

	int r, f;

	int tr = square / 8;
	int tf = square % 8;

	for (r = tr + 1, f = tf + 1; r <= 7 && f <= 7; r++, f++)
	{
		attacks |= (1ULL << (r * 8 + f));
		if ((1ULL << (r * 8 + f)) & block) break;
	}
	for (r = tr - 1, f = tf - 1; r >= 0 && f >= 0; r--, f--)
	{
		attacks |= (1ULL << (r * 8 + f));
		if ((1ULL << (r * 8 + f)) & block) break;
	}
	for (r = tr + 1, f = tf - 1; r <= 7 && f >= 0; r++, f--)
	{
		attacks |= (1ULL << (r * 8 + f));
		if ((1ULL << (r * 8 + f)) & block) break;
	}
	for (r = tr - 1, f = tf + 1; r >= 0 && f <= 7; r--, f++)
	{
		attacks |= (1ULL << (r * 8 + f));
		if ((1ULL << (r * 8 + f)) & block) break;
	}

	return attacks;
}

U64 rookAttackMask(int square)
{
	U64 attacks = 0ULL;

	int r, f;

	int tr = square / 8;
	int tf = square % 8;

	for (r = tr + 1; r <= 6; r++)
		attacks |= (1ULL << (r * 8 + tf));
	for (r = tr - 1; r >= 1; r--)
		attacks |= (1ULL << (r * 8 + tf));
	for (f = tf + 1; f <= 6; f++)
		attacks |= (1ULL << (tr * 8 + f));
	for (f = tf - 1; f >= 1; f--)
		attacks |= (1ULL << (tr * 8 + f));

	return attacks;
}

U64 rookAttackMaskOnTheFly(int square, U64 block)
{
	U64 attacks = 0ULL;

	int r, f;

	int tr = square / 8;
	int tf = square % 8;

	for (r = tr + 1; r <= 7; r++)
	{
		attacks |= (1ULL << (r * 8 + tf));
		if ((1ULL << (r * 8 + tf)) & block) break;
	}
	for (r = tr - 1; r >= 0; r--)
	{
		attacks |= (1ULL << (r * 8 + tf));
		if ((1ULL << (r * 8 + tf)) & block) break;
	}
	for (f = tf + 1; f <= 7; f++)
	{
		attacks |= (1ULL << (tr * 8 + f));
		if ((1ULL << (tr * 8 + f)) & block) break;
	}
	for (f = tf - 1; f >= 0; f--)
	{
		attacks |= (1ULL << (tr * 8 + f));
		if ((1ULL << (tr * 8 + f)) & block) break;
	}
	return attacks;
}

void initPawnAttacks()
{
	for (int square = 0; square < 64; square++)
	{
		pawnAttacks[white][square] = pawnAttackMask(white, square);
		pawnAttacks[black][square] = pawnAttackMask(black, square);
	}
}

void initKnightAttacks()
{
	for (int square = 0; square < 64; square++)
	{
		knightAttacks[square] = knightAttackMask(square);
	}
}

void initKingAttacks()
{
	for (int square = 0; square < 64; square++)
	{
		kingAttacks[square] = kingAttackMask(square);
	}
}

void initBishopAttacks()
{
	for (int square = 0; square < 64; square++)
	{
		bishopAttacks[square] = bishopAttackMask(square);
	}
}

void initRookAttacks()
{
	for (int square = 0; square < 64; square++)
	{
		rookAttacks[square] = rookAttackMask(square);
	}
}

int main()
{
	U64 block = 0ULL;
	U64 bitboard = 0ULL;
	initPawnAttacks();
	initKnightAttacks();
	initKingAttacks();
	initBishopAttacks();
	initRookAttacks();
	setBit(block, e3);
	setBit(block, f6);
	setBit(block, c3);
	PrintBitboard(block);

	bitboard = rookAttackMaskOnTheFly(f3, block);
	PrintBitboard(bitboard);


    /*for (int square = 0; square < 64; square++)
	{
		PrintBitboard(rookAttacks[square]);
	}*/

}