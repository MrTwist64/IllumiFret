from tkinter import *
from functools import partial
from tkinter import filedialog
import os

FRETS = 23
STRINGS = 6

# ======================================== LED ========================================
class LED:
    _red = 0
    _green = 0
    _blue = 0
    
    def set(self, red, green, blue):
        self._red = red
        self._green = green
        self._blue = blue

    def is_empty(self):
        return self._red == 0 and self._green == 0 and self._blue == 0
    
    def get_red(self):
        return self._red
    
    def get_green(self):
        return self._green
    
    def get_blue(self):
        return self._blue

# ======================================== AniSingleFrame ========================================
# Animation Frame for LED Board
class AniFrames:
    repeatIntVar: IntVar
    nameTextBox: Entry
    nameStrVar: StringVar
    btnNew: Button
    btnNext: Button
    btnPrev: Button
    frameInfo: Button
    delayTextBox: Entry
    delayStrVar: StringVar
    btnRemove: Button

    btnArr = [[NONE for i in range(STRINGS)] for j in range(FRETS)]
    _arr = [[[LED() for i in range(STRINGS)] for j in range(FRETS)]]
    _delays = [0]
    _currArr = 0

    currColor = "#000000"

    def __init__(self):
        self.repeatIntVar = IntVar(value=1)
        self.nameStrVar = StringVar()
        self.delayStrVar = StringVar()

    def set(self, i, j, red, green, blue):
        self._arr[self._currArr][i][j].set(red, green, blue)

    def set(self, i, j, color):
        red = AniFrames.hexToInt(color[1:3])
        green = AniFrames.hexToInt(color[3:5])
        blue = AniFrames.hexToInt(color[5:7])
        self._arr[self._currArr][i][j].set(red, green, blue)
    
    def updateDelay(self, unused1, unused2, unused3):
        self._delays[self._currArr] = self.delayStrVar.get()

    def btnPress(self, i, j):
        self.btnArr[i][j].config(bg=self.currColor, activebackground=self.currColor)
        self.set(i, j, self.currColor)
    
    def hexToInt(hexStr):
        return int(hexStr, 16)

    def intToHex(num):
        return hex(num).split('x')[-1].zfill(2)
    
    def perOf255(num):
        return int(num/255*100)
    
    def numFrames(self):
        return len(self._arr)
    
    def currFrame(self):
        return self._currArr

    def printArrIsEmpty(self):
        for i in range(len(self._arr)):
            print(f"----- Frame {i} -----")
            print(f"Delay (ms): {self._delays[i]}")
            print(end="     ")
            for j in range(len(self._arr[i][0])):
                print(j, end="")
            print()

            for j, fret in enumerate(self._arr[i]):
                num = f"{j}".rjust(2)
                print(num, "|", end=" ")
                for string in fret:
                    print(int(string.is_empty()), end="")
                print()
            print()
    
    def printArrColors(self):
        for i in range(len(self._arr)):
            print(f"----- Frame {i} -----")
            for j, fret in enumerate(self._arr[i]):
                for k, string in enumerate(fret):
                    red = self._arr[i][j][k].get_red()
                    green = self._arr[i][j][k].get_green()
                    blue = self._arr[i][j][k].get_blue()
                    print(f"[{j},{k}]: {red}, {green}, {blue}")
            print()
    
    def addNewFrame(self):
        self._arr.append([[LED() for i in range(STRINGS)] for j in range(FRETS)])
        self._delays.append(0)
        self.refreshFrameInfo()
    
    def removeCurrFrame(self):
        del self._arr[self._currArr]
        del self._delays[self._currArr]
        if (len(self._arr) == 0):
            self.addNewFrame()
        elif (self._currArr >= len(self._arr)):
            self._currArr -= 1
        self.refreshFrameInfo()
        self.refreshLEDButtons()
    
    def gotoPrevFrame(self):
        self._currArr -= 1
        self.refreshFrameInfo()
        self.refreshLEDButtons()
    
    def gotoNextFrame(self):
        self._currArr += 1
        self.refreshFrameInfo()
        self.refreshLEDButtons()
    
    def refreshFrameInfo(self):
        # Frame Info
        self.frameInfo.config(text=f"{self._currArr + 1}/{len(self._arr)}")

        # Prev Button
        if(self._currArr - 1 >= 0):
            self.btnPrev.config(state=NORMAL)
        else:
            self.btnPrev.config(state=DISABLED)
        
        # Next Button
        if(self._currArr + 1 < len(self._arr)):
            self.btnNext.config(state=NORMAL)
        else:
            self.btnNext.config(state=DISABLED)
        
        # Delay Text Box
        self.delayStrVar.set(self._delays[self._currArr])
        
    def refreshLEDButtons(self):
        for i in range(len(self.btnArr)):
            for j in range(len(self.btnArr[i])):
                colorHexStr = "#"
                colorHexStr += AniFrames.intToHex(self._arr[self._currArr][i][j].get_red())
                colorHexStr += AniFrames.intToHex(self._arr[self._currArr][i][j].get_green())
                colorHexStr += AniFrames.intToHex(self._arr[self._currArr][i][j].get_blue())
                self.btnArr[i][j].config(bg=colorHexStr, activebackground=colorHexStr)
    
    def exportFile(self):
        fileName = filedialog.asksaveasfilename(defaultextension=".txt", initialdir=os.getcwd(), title="Export File", filetypes=[("Text Files", "*.txt")])
        if not fileName:
            print("earlyexit")
            return # Save file not chosen
        file = open(fileName, 'w')
        file.write(self.aniFramesToText())
        file.close()

    numToFretDict = {
        0: "0",
        1: "1",
        2: "2",
        3: "3",
        4: "4",
        5: "5",
        6: "6",
        7: "7",
        8: "8",
        9: "9",
        10: "A",
        11: "B",
        12: "C",
        13: "D",
        14: "E",
        15: "F",
        16: "G",
        17: "H",
        18: "I",
        19: "J",
        20: "K",
        21: "L",
        22: "M",
    }

    def aniFramesToText(self):
        out = ""
        tab = "  "

        # Name
        out += f"Name:{self.nameStrVar.get()};"

        # Frames
        for i, frame in enumerate(self._arr):
            out += f"\n\n"
            out += f"StartFrame:{self._delays[i]};\n"

            # Find all unique colors
            uniqueColors = {(0, 0, 0)}
            for j, fret in enumerate(frame):
                for k, string in enumerate(fret):
                    curr = (self._arr[i][j][k].get_red(), self._arr[i][j][k].get_green(), self._arr[i][j][k].get_blue())
                    uniqueColors.add(curr)
            
            for c, color in enumerate(uniqueColors):
                if color == (0, 0, 0):
                    continue
                red = AniFrames.perOf255(color[0])
                green = AniFrames.perOf255(color[1])
                blue = AniFrames.perOf255(color[2])
                out += f"{tab}Color:{red},{green},{blue};\n"
                out += f"{tab}{tab}LEDS:"
                for j, fret in enumerate(frame):
                    for k, string in enumerate(fret):
                        curr = (self._arr[i][j][k].get_red(), self._arr[i][j][k].get_green(), self._arr[i][j][k].get_blue())
                        if curr == color:
                            out += f"{k+1}{AniFrames.numToFretDict[j]},"
                if out[-1] == ',':
                    out = out[:-1:]
                out += f";\n"

            out += f"EndFrame;"
        
        # Repeat
        if self.repeatIntVar.get():
            out += f"\n\nRepeat;"

        return out

# ======================================== main() ========================================
def main():
    # ---------- Root Window ----------
    root = Tk()
    root.title("Illumifret Tab Creator")

    aniFrames = AniFrames()

    # ---------- Option Frame ----------
    optionFrame = Frame(root, relief=RAISED, padx=5, pady=5)

    def updateColorChoice(unused):
        aniFrames.currColor = f"#{AniFrames.intToHex(redScale.get())}{AniFrames.intToHex(greenScale.get())}{AniFrames.intToHex(blueScale.get())}"
        colorShowFrame.config(bg=aniFrames.currColor)
        colorShowLabel.config(text=aniFrames.currColor)

    nameFrame = Frame(optionFrame)
    Label(nameFrame, text="Name:").pack(side=LEFT)
    aniFrames.nameTextBox = Entry(nameFrame, textvariable=aniFrames.nameStrVar, width=10)
    aniFrames.nameTextBox.pack(fill=X)
    nameFrame.grid(row=0, column=0, columnspan=3, sticky=EW)

    Checkbutton(optionFrame, text="Repeat Animation", variable=aniFrames.repeatIntVar).grid(row=1, column=0, columnspan=3, sticky=EW)
    
    colorShowFrame = Frame(optionFrame, bg="#000000")
    colorShowLabel = Label(colorShowFrame, relief=RIDGE, text="#000000")
    redScale = Scale(optionFrame, from_=255, to=0, length=200, fg='red', orient='vertical', command=updateColorChoice)
    greenScale = Scale(optionFrame, from_=255, to=0, length=200, fg='green', orient='vertical', command=updateColorChoice)
    blueScale = Scale(optionFrame, from_=255, to=0, length=200, fg='blue', orient='vertical', command=updateColorChoice)
    colorShowFrame.grid(row=2, column=0, columnspan=3, sticky=EW)
    colorShowLabel.pack(padx=5, pady=5)
    redScale.grid(row=3, column=0)
    greenScale.grid(row=3, column=1)
    blueScale.grid(row=3, column=2)
    
    Button(optionFrame, relief=GROOVE, text="Export File", command=aniFrames.exportFile).grid(row=4, column=0, columnspan=3, sticky=EW)

    optionFrame.grid(row=0, column=0, sticky=NS)

    # ---------- LED Frame ----------
    ledFrame = Frame(root, padx=5, pady=5)

    frameInfoFrame = Frame(ledFrame)

    aniFrames.btnNew = Button(frameInfoFrame, relief=GROOVE, text="New Frame", command=aniFrames.addNewFrame)
    aniFrames.btnPrev = Button(frameInfoFrame, relief=GROOVE, text="Prev", command=aniFrames.gotoPrevFrame)
    aniFrames.frameInfo = Label(frameInfoFrame, text="")
    aniFrames.btnNext = Button(frameInfoFrame, relief=GROOVE, text="Next", command=aniFrames.gotoNextFrame)

    aniFrames.btnNew.grid(row=0, column=0, columnspan=3, sticky=EW)
    aniFrames.btnPrev.grid(row=1, column=0, sticky=SW)
    aniFrames.frameInfo.grid(row=1, column=1)
    aniFrames.btnNext.grid(row=1, column=2, sticky=SE)

    aniFrames.refreshFrameInfo()

    frameInfoFrame.columnconfigure(1, weight=1)
    frameInfoFrame.grid(row=0, column=0, sticky=EW)

    delayFrame = Frame(ledFrame)
    Label(delayFrame, text="Delay (ms):").pack(side=LEFT)
    aniFrames.delayStrVar.trace_add("write", aniFrames.updateDelay)
    aniFrames.delayTextBox = Entry(delayFrame, textvariable=aniFrames.delayStrVar, width=10)
    aniFrames.delayTextBox.pack(fill=X)
    delayFrame.grid(row=1, column=0, sticky=EW)

    arrayFrame = Frame(ledFrame, pady=5)
    for i in range(FRETS):
        Label(arrayFrame, text=f"{AniFrames.numToFretDict[i]}").grid(row=i, column=0)
        for j in range(STRINGS):
            aniFrames.btnArr[i][j] = Button(arrayFrame, relief=GROOVE, bg="#000000", activebackground="#000000", width=2, height=1)
            aniFrames.btnArr[i][j].config(command=partial(aniFrames.btnPress, i, j))
            aniFrames.btnArr[i][j].grid(row=i, column=j+1)
    Label(arrayFrame, text='OS').grid(row=0, column=7)
    Label(arrayFrame, text=u'\u25CF', font=('Arial', 12)).grid(row=3, column=7)
    Label(arrayFrame, text=u'\u25CF', font=('Arial', 12)).grid(row=5, column=7)
    Label(arrayFrame, text=u'\u25CF', font=('Arial', 12)).grid(row=7, column=7)
    Label(arrayFrame, text=u'\u25CF', font=('Arial', 12)).grid(row=9, column=7)
    Label(arrayFrame, text=u'\u25CF\u25CF', font=('Arial', 12)).grid(row=12, column=7)
    Label(arrayFrame, text=u'\u25CF', font=('Arial', 12)).grid(row=15, column=7)
    Label(arrayFrame, text=u'\u25CF', font=('Arial', 12)).grid(row=17, column=7)
    Label(arrayFrame, text=u'\u25CF', font=('Arial', 12)).grid(row=19, column=7)
    Label(arrayFrame, text=u'\u25CF', font=('Arial', 12)).grid(row=21, column=7)
    arrayFrame.grid(row=2, column=0, sticky=EW)

    aniFrames.btnRemove = Button(ledFrame, relief=GROOVE, text="Remove Frame", command=aniFrames.removeCurrFrame)
    aniFrames.btnRemove.grid(row=3, column=0, sticky=EW)

    ledFrame.grid(row=0, column=1, sticky=NS)

    # ---------- Root Window ----------
    root.mainloop()

if __name__ == "__main__":
    main()