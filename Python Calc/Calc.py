from tkinter import *
import math

class Calc:
    display = '0'
    bufferVal = 0
    bufferOp = ''
    result = False
    inOp = False

    def __init__(self, myParent):

        button_width = 6
        button_pady = ".25m"
        button_padx = ".25m"

        self.displayLabel = Label(myParent, text=self.display, width = 24,
                                  anchor=E, borderwidth=2, relief="ridge")
        self.displayLabel.grid(row=0, columnspan=4, padx="4m")


        self.sqrtButton = Button(myParent, text="√", background="light cyan",
                                    width=button_width)
        self.sqrtButton.grid(row=1, column=0,
                                pady=button_pady, padx=button_padx)
        self.sqrtButton.bind("<Button-1>", self.sqrt)

        self.sqrButton = Button(myParent, text="^2", background="light cyan",
                                    width=button_width)
        self.sqrButton.grid(row=1, column=1,
                                pady=button_pady, padx=button_padx)
        self.sqrButton.bind("<Button-1>", self.sqr)

        self.clearButton = Button(myParent, text="clear", background="light cyan",
                                    width=button_width)
        self.clearButton.grid(row=1, column=2,
                                pady=button_pady, padx=button_padx)
        self.clearButton.bind("<Button-1>", self.clear)

        self.divideButton = Button(myParent, text="÷", background="light cyan",
                                    width=button_width)
        self.divideButton.grid(row=1, column=3,
                                pady=button_pady, padx=button_padx)
        self.divideButton.bind("<Button-1>", self.divide)


        self._7Button = Button(myParent, text="7", background="light cyan",
                                width=button_width)
        self._7Button.grid(row=2, column=0,
                                pady=button_pady, padx=button_padx)
        self._7Button.bind("<Button-1>", self.press7)

        self._8Button = Button(myParent, text="8", background="light cyan",
                                width=button_width)
        self._8Button.grid(row=2, column=1,
                                pady=button_pady, padx=button_padx)
        self._8Button.bind("<Button-1>", self.press8)

        self._9Button = Button(myParent, text="9", background="light cyan",
                                width=button_width)
        self._9Button.grid(row=2, column=2,
                                pady=button_pady, padx=button_padx)
        self._9Button.bind("<Button-1>", self.press9)

        self.multiplyButton = Button(myParent, text="x", background="light cyan",
                                    width=button_width)
        self.multiplyButton.grid(row=2, column=3,
                                pady=button_pady, padx=button_padx)
        self.multiplyButton.bind("<Button-1>", self.multiply)


        self._4Button = Button(myParent, text="4", background="light cyan",
                                width=button_width)
        self._4Button.grid(row=3, column=0,
                                pady=button_pady, padx=button_padx)
        self._4Button.bind("<Button-1>", self.press4)

        self._5Button = Button(myParent, text="5", background="light cyan",
                                width=button_width)
        self._5Button.grid(row=3, column=1,
                                pady=button_pady, padx=button_padx)
        self._5Button.bind("<Button-1>", self.press5)

        self._6Button = Button(myParent, text="6", background="light cyan",
                                width=button_width)
        self._6Button.grid(row=3, column=2,
                                pady=button_pady, padx=button_padx)
        self._6Button.bind("<Button-1>", self.press6)

        self.subtractButton = Button(myParent, text="-", background="light cyan",
                                    width=button_width)
        self.subtractButton.grid(row=3, column=3,
                                pady=button_pady, padx=button_padx)
        self.subtractButton.bind("<Button-1>", self.subtract)


        self._1Button = Button(myParent, text="1", background="light cyan",
                                width=button_width)
        self._1Button.grid(row=4, column=0,
                                pady=button_pady, padx=button_padx)
        self._1Button.bind("<Button-1>", self.press1)

        self._2Button = Button(myParent, text="2", background="light cyan",
                                width=button_width)
        self._2Button.grid(row=4, column=1,
                                pady=button_pady, padx=button_padx)
        self._2Button.bind("<Button-1>", self.press2)

        self._3Button = Button(myParent, text="3", background="light cyan",
                                width=button_width)
        self._3Button.grid(row=4, column=2,
                                pady=button_pady, padx=button_padx)
        self._3Button.bind("<Button-1>", self.press3)

        self.addButton = Button(myParent, text="+", background="light cyan",
                                width=button_width)
        self.addButton.grid(row=4, column=3,
                                pady=button_pady, padx=button_padx)
        self.addButton.bind("<Button-1>", self.add)


        self._0Button = Button(myParent, text="0", background="light cyan",
                                width=2*button_width, padx="1.75m")
        self._0Button.grid(row=6, column=0, columnspan=2,
                                pady=button_pady, padx=button_padx)
        self._0Button.bind("<Button-1>", self.press0)

        self.decimalButton = Button(myParent, text=".", background="light cyan",
                                width=button_width)
        self.decimalButton.grid(row=6, column=2,
                                pady=button_pady, padx=button_padx)
        self.decimalButton.bind("<Button-1>", self.decimal)

        self.equalsButton = Button(myParent, text="=", background="light cyan",
                                width=button_width)
        self.equalsButton.grid(row=6, column=3,
                                pady=button_pady, padx=button_padx)
        self.equalsButton.bind("<Button-1>", self.equals)


        myParent.bind('1', self.press1)
        myParent.bind('2', self.press2)
        myParent.bind('3', self.press3)
        myParent.bind('4', self.press4)
        myParent.bind('5', self.press5)
        myParent.bind('6', self.press6)
        myParent.bind('7', self.press7)
        myParent.bind('8', self.press8)
        myParent.bind('9', self.press9)
        myParent.bind('0', self.press0)
        myParent.bind('.', self.decimal)
        myParent.bind('+', self.add)
        myParent.bind('-', self.subtract)
        myParent.bind('*', self.multiply)
        myParent.bind('/', self.divide)
        myParent.bind('<Return>', self.equals)

    def press1(self, event):
        if self.result == True:
            self.result = False
            self.bufferVal = float(self.display)
            self.display = '1'
        else:
            if self.display == '0':
                self.display = '1'
            else:
                self.display = self.display + '1'

        self.inOp = False
        self.displayLabel["text"] = self.display

    def press2(self, event):
        if self.result == True:
            self.result = False
            self.bufferVal = float(self.display)
            self.display = '2'
        else:
            if self.display == '0':
                self.display = '2'
            else:
                self.display = self.display + '2'

        self.inOp = False
        self.displayLabel["text"] = self.display

    def press3(self, event):
        if self.result == True:
            self.result = False
            self.bufferVal = float(self.display)
            self.display = '3'
        else:
            if self.display == '0':
                self.display = '3'
            else:
                self.display = self.display + '3'

        self.inOp = False
        self.displayLabel["text"] = self.display

    def press4(self, event):
        if self.result == True:
            self.result = False
            self.bufferVal = float(self.display)
            self.display = '4'
        else:
            if self.display == '0':
                self.display = '4'
            else:
                self.display = self.display + '4'

        self.inOp = False
        self.displayLabel["text"] = self.display

    def press5(self, event):
        if self.result == True:
            self.result = False
            self.bufferVal = float(self.display)
            self.display = '5'
        else:
            if self.display == '0':
                self.display = '5'
            else:
                self.display = self.display + '5'

        self.inOp = False
        self.displayLabel["text"] = self.display

    def press6(self, event):
        if self.result == True:
            self.result = False
            self.bufferVal = float(self.display)
            self.display = '6'
        else:
            if self.display == '0':
                self.display = '6'
            else:
                self.display = self.display + '6'

        self.inOp = False
        self.displayLabel["text"] = self.display

    def press7(self, event):
        if self.result == True:
            self.result = False
            self.bufferVal = float(self.display)
            self.display = '7'
        else:
            if self.display == '0':
                self.display = '7'
            else:
                self.display = self.display + '7'

        self.inOp = False
        self.displayLabel["text"] = self.display

    def press8(self, event):
        if self.result == True:
            self.result = False
            self.bufferVal = float(self.display)
            self.display = '8'
        else:
            if self.display == '0':
                self.display = '8'
            else:
                self.display = self.display + '8'

        self.inOp = False
        self.displayLabel["text"] = self.display

    def press9(self, event):
        if self.result == True:
            self.result = False
            self.bufferVal = float(self.display)
            self.display = '9'
        else:
            if self.display == '0':
                self.display = '9'
            else:
                self.display = self.display + '9'

        self.inOp = False
        self.displayLabel["text"] = self.display

    def press0(self, event):
        if self.result == True:
            self.result = False
            self.bufferVal = float(self.display)
            self.display = '0'
        else:
            if self.display == '0':
                self.display = '0'
            else:
                self.display = self.display + '0'

        self.inOp = False
        self.displayLabel["text"] = self.display

    def decimal(self, event):
        if '.' not in self.display:
            self.display = self.display + '.'
            self.inOp = False
            self.displayLabel["text"] = self.display

    def clear(self, event):
        self.bufferVal = 0
        self.bufferOp = ''
        self.display = '0'
        self.result = False
        self.inOp = False
        self.displayLabel["text"] = self.display

    def sqrt(self, event):
        self.result = True
        self.inOp = False
        self.display = str(math.sqrt(float(self.display)))
        self.displayLabel["text"] = self.display

    def sqr(self, event):
        self.result = True
        self.inOp = False
        self.display = str(float(self.display) * float(self.display))
        self.displayLabel["text"] = self.display

    def handleOps(self):
        self.result = True
        self.inOp = False
        if self.bufferOp == '/':
            return self.bufferVal / float(self.display)
        elif self.bufferOp == '=/':
            return float(self.display) / self.bufferVal

        elif self.bufferOp == '*' or self.bufferOp == '=*':
            return self.bufferVal * float(self.display)

        elif self.bufferOp == '+' or self.bufferOp == '=+':
            return self.bufferVal + float(self.display)

        elif self.bufferOp == '-':
            return self.bufferVal - float(self.display)
        elif self.bufferOp == '=-':
            return float(self.display) - self.bufferVal

    def divide(self, event):
        if self.inOp:
            self.bufferOp = '/'
        else:
            self.inOp = True
            if len(self.bufferOp) > 0 and self.bufferOp[0] != '=':
                self.display = str(self.handleOps())
                self.bufferOp = '/'
                self.displayLabel["text"] = self.display
            else:
                self.bufferVal = float(self.display)
                self.bufferOp = '/'
                self.display = '0'
                self.result = False
                self.displayLabel["text"] = self.display

    def multiply(self, event):
        if self.inOp:
            self.bufferOp = '*'
        else:
            if len(self.bufferOp) > 0 and self.bufferOp[0] != '=':
                self.display = str(self.handleOps())
                self.bufferOp = '*'
                self.displayLabel["text"] = self.display
            else:
                self.inOp = True
                self.bufferVal = float(self.display)
                self.bufferOp = '*'
                self.display = '0'
                self.result = False
                self.displayLabel["text"] = self.display

    def add(self, event):
        if self.inOp:
            self.bufferOp = '+'
        else:
            self.inOp = True
            if len(self.bufferOp) > 0 and self.bufferOp[0] != '=':
                self.display = str(self.handleOps())
                self.bufferOp = '+'
                self.displayLabel["text"] = self.display
            else:
                self.bufferVal = float(self.display)
                self.bufferOp = '+'
                self.display = '0'
                self.result = False
                self.displayLabel["text"] = self.display

    def subtract(self, event):
        if self.inOp:
            self.bufferOp = '-'
        else:
            self.inOp = True
            if len(self.bufferOp) > 0 and self.bufferOp[0] != '=':
                self.display = str(self.handleOps())
                self.bufferOp = '-'
                self.displayLabel["text"] = self.display
            else:
                self.bufferVal = float(self.display)
                self.bufferOp = '-'
                self.display = '0'
                self.result = False
                self.displayLabel["text"] = self.display

    def equals(self, event):
        temp = self.display
        self.display = str(self.handleOps())
        if self.bufferOp[0] != '=':
            self.bufferOp = '=' + self.bufferOp
            self.bufferVal = float(temp)

        self.displayLabel["text"] = self.display

root = Tk()

calc = Calc(root)

root.mainloop()
