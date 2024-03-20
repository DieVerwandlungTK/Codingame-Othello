from OthelloTypes import *

class Othello():
    BOARD_SIZE = 8
    BOARD_SIZE_DOUBLE = 64
    def __init__(self) -> None:
        self.blackPieces = 0x0000000810000000
        self.whitePieces = 0x0000001008000000
    
    def setBoard(self, board: Board) -> None:
        self.blackPieces, self.whitePieces = board
    
    def getLegalBoard(self, color: Color) -> Bitboard:
        if color == Color.BLACK:
            player = self.blackPieces
            opponent = self.whitePieces
        else:
            player = self.whitePieces
            opponent = self.blackPieces

        horizontalMasked = opponent & 0x7e7e7e7e7e7e7e7e
        # 上下端の番人
        verticalMasked = opponent & 0x00FFFFFFFFFFFF00
        # 全辺の番人
        diagonalMasked = opponent & 0x007e7e7e7e7e7e00
        # 空きマスのみにビットが立っているボード
        empty = ~(player | opponent)

        legal_board = 0

        # 8方向チェック
        directions = [
            (1, horizontalMasked),   
            (8, verticalMasked),    
            (7, diagonalMasked),    
            (9, diagonalMasked)
        ]

        for dir, masked in directions:
            tmp = masked & (player << dir)
            for _ in range(5):
                tmp |= masked & (tmp << dir)
            legal_board |= empty & (tmp << dir)

            tmp = masked & (player >> dir)
            for _ in range(5):
                tmp |= masked & (tmp >> dir)
            legal_board |= empty & (tmp >> dir)

        return legal_board
    
    def getShiftedBoard(self, board: Bitboard, k: int)->Bitboard:
        if   k == 0:  # up
            return (board << 8) & 0xffffffffffffff00
        elif k == 1:  # right up
            return (board << 7) & 0x7f7f7f7f7f7f7f00
        elif k == 2:  # right
            return (board >> 1) & 0x7f7f7f7f7f7f7f7f
        elif k == 3:  # right down
            return (board >> 9) & 0x007f7f7f7f7f7f7f
        elif k == 4:  # down
            return (board >> 8) & 0x00ffffffffffffff
        elif k == 5:  # left down
            return (board >> 7) & 0x00fefefefefefefe
        elif k == 6:  # left
            return (board << 1) & 0xfefefefefefefefe
        elif k == 7:  # left up
            return (board << 9) & 0xfefefefefefefe00
        else:
            return 0
    
    def makeMove(self, pos: Bitboard, color: Color)->None:
        if color == Color.BLACK:
            player = self.blackPieces
            opponent = self.whitePieces
        else:
            player = self.whitePieces
            opponent = self.blackPieces

        rev = 0
        for k in range(8):
            tmp = 0
            mask = self.getShiftedBoard(pos, k)
            while mask != 0 and (mask & opponent) != 0:
                tmp |= mask
                mask = self.getShiftedBoard(mask, k)
            if (mask & player) != 0:
                rev |= tmp
            
        player ^= pos | rev
        opponent ^= rev
    
        if color==Color.BLACK:
            self.setBoard((player, opponent))
        else:
            self.setBoard((opponent, player))
    
    def popcount(x):
        x = x - ((x >> 1) & 0x5555555555555555)

        x = (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333)

        x = (x + (x >> 4)) & 0xf0f0f0f0f0f0f0f
        x = x + (x >> 8)
        x = x + (x >> 16)
        x = x + (x >> 32)
        return x & 0x7f
    
    def mask2coord(self, mask: Bitboard)->tuple[int, int]:
        for i in range(self.BOARD_SIZE_DOUBLE):
            if mask & 1:
                return (i//8, i%8)
            mask >>= 1
    
    def coord2mask(self, x: int, y: int)->Bitboard:
        return 1 << (x*8 + y)