from OthelloGUI.GUI import OthelloGUI
from OthelloGUI.OthelloTypes import Color

import tkinter as tk
import sys
import subprocess

class Game(OthelloGUI):
    def __init__(self, AIColor: Color) -> None:
        super().__init__()
        self.legalButtons = []
        self.AIColor = AIColor
        self.turn = Color.BLACK

        self.AIExe = subprocess.Popen('../main/build/main.exe'.split(), stdin=subprocess.PIPE, stdout=subprocess.PIPE)
        self.AIExe.stdin.write((str(AIColor) + '\n').encode('utf-8'))
        self.AIExe.stdin.flush()

        self.gui.protocol('WM_DELETE_WINDOW', self.closeAI)

        self.drawStoneNumber(self.turn)
    
    def AI(self)->None:
        if self.othello.getLegalBoard(self.turn):
            sendMessage = str(self.othello.blackPieces) + '\n' + str(self.othello.whitePieces) + '\n'

            self.AIExe.stdin.write(sendMessage.encode('utf-8'))
            self.AIExe.stdin.flush()

            receivedMessage = self.AIExe.stdout.readline().decode('utf-8').strip()
            self.AIExe.stdout.flush()

            move = int(receivedMessage)
            self.othello.makeMove(move, self.AIColor)

        if not self.othello.getLegalBoard(self.turn):
            self.turn = Color(self.turn^1)
            if not self.othello.getLegalBoard(self.turn):
                self.AIExe.kill()
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
                self.AIExe.kill()
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
                if self.turn != self.AIColor:
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

        if self.turn == self.AIColor:
                self.gui.after(10, self.AI)

            
        
    def closeAI(self)->None:
        self.AIExe.kill()
        self.gui.destroy()
    
    def show(self)->None:
        self.canvas.place(x=0, y=0)
        self.showGrid()
        self.gui.mainloop()

if __name__=='__main__':
    try:
        AIColor = Color(int(input('Select AI color (0: Black, 1: White): ')))
    except:
        print('Invalid input. Please input 0 or 1.')
        sys.exit(1)
    if AIColor != Color.BLACK and AIColor != Color.WHITE:
        print('Invalid input. Please input 0 or 1.')
        sys.exit(1)
    
    game = Game(AIColor)
    game.show()