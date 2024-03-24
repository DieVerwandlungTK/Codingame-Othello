import tkinter as tk
from .OthelloPy import Othello
from .OthelloTypes import Color

class OthelloGUI():
    OFFSET_X = 10
    OFFSET_Y = 10
    RECT_SIZE = 60
    CIRCLE_OFFSET = 3

    def __init__(self)->None:
       self.othello = Othello()
       self.root = tk.Tk()
       self.root.geometry("500x700")
       self.root.title("Othello")
       self.canvas = tk.Canvas(self.root, width=500, height = 700)
       self.pixel_virtual = tk.PhotoImage(width=1, height=1)
       self.StoneStr = tk.StringVar()
       self.stoneLabel = tk.Label(self.canvas, textvariable=self.StoneStr, font=('', 50))
       self.stoneLabel.place(x=250, y=600, anchor=tk.CENTER)

       self.drawBoard()

    def drawBoard(self)->None:
        for x in range(self.othello.BOARD_SIZE):
            for y in range(self.othello.BOARD_SIZE):
                self.canvas.create_rectangle(
                    self.OFFSET_X + self.RECT_SIZE * x,
                    self.OFFSET_Y + self.RECT_SIZE * y,
                    self.OFFSET_X + self.RECT_SIZE * (x + 1),
                    self.OFFSET_Y + self.RECT_SIZE * (y + 1),
                    fill="green"
                )
    
    def drawStoneNumber(self, turn: Color)->None:
        black = self.othello.popcount(self.othello.blackPieces)
        white = self.othello.popcount(self.othello.whitePieces)
        s = '● '
        s += str(black)
        s += ' - '
        s += str(white)
        s += ' ○'

        if turn == Color.BLACK:
            s = '*' + s + ' '
        elif turn == Color.WHITE:
            s = ' ' + s + '*'
        else:
            s = ' ' + s + ' '

        self.StoneStr.set(s)

    
    
