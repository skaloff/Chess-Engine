#include <iostream>

typedef unsigned long long  U64;

#define getBit(bitboard, square) (bitboard & (1ULL << square))  //get used bit
#define setBit(bitboard, square) (bitboard |= (1ULL << square))  //set bit in square
#define removeBit(bitboard, square) (getBit(bitboard, square) ? bitboard ^= (1ULL << square) : 0)  //remove bit

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

void printBinary(U64 number) {
	int numBits = sizeof(U64) * 8; // Определение количества битов в числе
	for (int i = numBits - 1; i >= 0; i--) 
	{
		bool bit = (number >> i) & 1; // Проверка i-го бита
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

void PrintBitboard2(U64 bitboard)
{
	for (int rank = 7; rank >= 0; rank--)
	{
		for (int file = 0; file < 8; file++)
		{
			// Convert rank & file into square index
			int square = rank * 8 + file;

			if (file == 0)
			{
				std::cout << (rank + 1) << "  ";
			}

			std::cout << (getBit(bitboard, square) ? 1 : 0) << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "   a b c d e f g h\n";

	std::cout << "Bitboard: " << bitboard;
}


int main()
{
	U64 bitboard = 0ULL;

	setBit(bitboard, a8);
	setBit(bitboard, g3);

	PrintBitboard(bitboard);


	removeBit(bitboard, a7);
	PrintBitboard(bitboard);

	std::cout << (getBit(bitboard, g4) ? 1 : 0);


	bitboard ^= (1ULL << a7);
}