from OthelloGUI.GUI import OthelloGUI
from OthelloGUI.OthelloTypes import Color

import tkinter as tk
import sys
import subprocess
from enum import IntEnum

class Mode(IntEnum):
    PLAYER_VS_PLAYER = 0
    PLAYER_VS_AI = 1
    AI_VS_AI = 2

class Player():
    def __init__(self, color: Color, isAI: bool) -> None:
        self.color = color
        self.isAI = isAI
        self.AIexe = None
    
    def activate(self) -> None:
        if self.isAI:
            self.AIexe = subprocess.Popen('../main/build/main.exe'.split(), stdin=subprocess.PIPE, stdout=subprocess.PIPE)
            self.AIexe.stdin.write((str(self.color) + '\n').encode('utf-8'))
            self.AIexe.stdin.flush()
    
    def kill(self) -> None:
        if self.isAI:
            self.AIexe.kill()
    
    def getMove(self, blackPieces: int, whitePieces: int) -> None:
        if self.isAI:
            sendMessage = str(blackPieces) + '\n' + str(whitePieces) + '\n'
            self.AIexe.stdin.write(sendMessage.encode('utf-8'))
            self.AIexe.stdin.flush()

            receivedMessage = self.AIexe.stdout.readline().decode('utf-8').strip()
            self.AIexe.stdout.flush()

            return int(receivedMessage)
        else:
            return None

class Game(OthelloGUI):
    def __init__(self, mode: Mode, AIcolor: Color=Color.BLACK) -> None:
        super().__init__()

        self.mode = mode
        self.AIcolor = AIcolor
        self.turn = Color.BLACK
        

        if self.mode == Mode.PLAYER_VS_PLAYER:
            self.blackPlayer = Player(Color.BLACK, False)
            self.whitePlayer = Player(Color.WHITE, False)

        elif self.mode == Mode.PLAYER_VS_AI:
            if self.AIcolor == Color.BLACK:
                self.blackPlayer = Player(Color.BLACK, True)
                self.whitePlayer = Player(Color.WHITE, False)
            else:
                self.blackPlayer = Player(Color.BLACK, False)
                self.whitePlayer = Player(Color.WHITE, True)
        
        elif self.mode == Mode.AI_VS_AI:
            self.blackPlayer = Player(Color.BLACK, True)
            self.whitePlayer = Player(Color.WHITE, True)
        
        else:
            print('Invalid mode')
            sys.exit(1)

        self.blackPlayer.activate()
        self.whitePlayer.activate()

        self.legalButtons = []
        self.root.protocol('WM_DELETE_WINDOW', self.closeAI)
        self.drawStoneNumber(self.turn)
    
    def AI(self)->None:
        if self.othello.getLegalBoard(self.turn):
            if self.turn==Color.BLACK:
                move = self.blackPlayer.getMove(self.othello.blackPieces, self.othello.whitePieces)
            else:
                move = self.whitePlayer.getMove(self.othello.blackPieces, self.othello.whitePieces)
            self.othello.makeMove(move, self.turn)

        if not self.othello.getLegalBoard(self.turn):
            self.turn = Color(self.turn^1)
            if not self.othello.getLegalBoard(self.turn):
                self.blackPlayer.kill()
                self.whitePlayer.kill()
                self.turn = Color.NONE
                print('Game Over')

        else:
            self.turn = Color(self.turn^1)
 
        self.drawStoneNumber(self.turn)
        self.showGrid()

    def getCoord(self, event)->None:
        x = int(event.widget.cget('text')[0])
        y = int(event.widget.cget('text')[2])

        mask = self.othello.coord2mask(x, y)
        self.othello.makeMove(mask, self.turn)
        
        if not self.othello.getLegalBoard(self.turn):
            self.turn = Color(self.turn^1)
            if not self.othello.getLegalBoard(self.turn):
                self.blackPlayer.kill()
                self.whitePlayer.kill()
                self.turn = Color.NONE
                print('Game Over')

        else:
            self.turn = Color(self.turn^1)
        
        self.drawStoneNumber(self.turn)
        self.showGrid()
        
    
    def showGrid(self)->None:
        for button in self.legalButtons:
            button.place_forget()
        self.legalButtons = []

        legalBoard = self.othello.getLegalBoard(self.turn)
        mask = 0x8000000000000000
        for _ in range(self.othello.BOARD_SIZE_DOUBLE):
            x, y = self.othello.mask2coord(mask)
            try:
                self.canvas.delete(str(x) + '_' + str(y))
            except:
                pass
            
            color = ''
            if mask&self.othello.blackPieces:
                color = 'black'
            elif mask&self.othello.whitePieces:
                color = 'white'
            elif mask&legalBoard:
                if self.mode==Mode.PLAYER_VS_PLAYER or (self.mode==Mode.PLAYER_VS_AI and self.turn!=self.AIcolor):
                    color = '#3498db'
                    self.legalButtons.append(
                        tk.Button(self.canvas, image=self.pixel_virtual,
                                  width=self.RECT_SIZE-self.CIRCLE_OFFSET*2,
                                  height=self.RECT_SIZE-self.CIRCLE_OFFSET*2,
                                  bg=color, text=str(x) + '_' + str(y))
                                        )
                    self.legalButtons[-1].bind('<ButtonPress>', self.getCoord)
                    self.legalButtons[-1].place(x=self.OFFSET_X+self.RECT_SIZE*x,
                                                y=self.OFFSET_Y+self.RECT_SIZE*y)
                mask >>= 1
                continue
            
            if color != '':
                self.canvas.create_oval(self.OFFSET_X+self.RECT_SIZE*x+self.CIRCLE_OFFSET,
                                        self.OFFSET_Y+self.RECT_SIZE*y+self.CIRCLE_OFFSET,
                                        self.OFFSET_X+self.RECT_SIZE*(x+1)-self.CIRCLE_OFFSET,
                                        self.OFFSET_Y+self.RECT_SIZE*(y+1)-self.CIRCLE_OFFSET,
                                        outline='black', width=2, fill=color, tag=str(x) + '_' + str(y))
            mask >>= 1
        
        if self.mode == Mode.AI_VS_AI:
            if self.turn != Color.NONE:
                self.root.after(10, self.AI)
        elif self.mode == Mode.PLAYER_VS_AI:
            if self.turn == self.AIcolor:
                self.root.after(10, self.AI)
        elif self.mode == Mode.PLAYER_VS_PLAYER:
            pass
        
    def closeAI(self)->None:
        self.blackPlayer.kill()
        self.whitePlayer.kill()
        self.root.destroy()
    
    def show(self)->None:
        self.canvas.place(x=0, y=0)
        self.showGrid()
        self.root.mainloop()

if __name__=='__main__':
    try: 
        mode = Mode(int(input('Select mode (0: Player vs Player, 1: Player vs AI, 2: AI vs AI): ')))
    
    except:
        print('Invalid input. Please input 0, 1 or 2.')
        sys.exit(1)
    
    if mode == Mode.PLAYER_VS_AI:
        try:
            AIColor = Color(int(input('Select AI color (0: Black, 1: White): ')))
        except:
            print('Invalid input. Please input 0 or 1.')
            sys.exit(1)
        if AIColor != Color.BLACK and AIColor != Color.WHITE:
            print('Invalid input. Please input 0 or 1.')
            sys.exit(1)
    
    game = Game(mode)
    game.show()