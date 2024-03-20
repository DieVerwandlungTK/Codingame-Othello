from enum import IntEnum

Pos = str
Bitboard = int
Board = tuple[Bitboard, Bitboard]

class Color(IntEnum):
    BLACK = 0
    WHITE = 1
    NONE  = 2
