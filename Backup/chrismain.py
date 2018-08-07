from graphics import *

WINDOW_WIDTH, WINDOW_HEIGHT = 1000, 800
win = GraphWin("Simple Breakout", WINDOW_WIDTH, WINDOW_HEIGHT)

def button(x1,y1,x2,y2,color,name):
	box = Rectangle(Point(x1,y1), Point(x2, y2))  # points are ordered ll, ur
	box.setFill(color)
	text = Text(Point((x1+x2)/2,(y1+y2)/2),name)
	return box, text

def drawButton(box,text):
	global win
	box.draw(win)
	text.draw(win)
	return
	
def inside(point, rectangle):
    """ Is point inside rectangle? """

    ll = rectangle.getP1()  # assume p1 is ll (lower left)
    ur = rectangle.getP2()  # assume p2 is ur (upper right)

    return ll.getX() < point.getX() < ur.getX() and ll.getY() < point.getY() < ur.getY()

def displayMainMenu():
	sizeX=WINDOW_WIDTH/2
	sizeY=WINDOW_HEIGHT/9
	centerPoint = Point(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2)
	startGameButton, startGameButtonText = button(WINDOW_WIDTH/2-sizeX/2,WINDOW_HEIGHT / 2-sizeY/2-sizeY*3,WINDOW_WIDTH/2+sizeX/2,WINDOW_HEIGHT / 2+sizeY/2-sizeY*3,"gray", "Start Game")
	exitButton, exitButtonText = button(WINDOW_WIDTH/2-sizeX/2,WINDOW_HEIGHT / 2-sizeY/2-sizeY*1,WINDOW_WIDTH/2+sizeX/2,WINDOW_HEIGHT / 2+sizeY/2-sizeY*1,"gray", "Exit")
	creditButton, creditButtonText = button(WINDOW_WIDTH/2-sizeX/2,WINDOW_HEIGHT / 2-sizeY/2+sizeY*1,WINDOW_WIDTH/2+sizeX/2,WINDOW_HEIGHT / 2+sizeY/2+sizeY*1,"gray", "Credits")
	tutorialButton, tutorialButtonText = button(WINDOW_WIDTH/2-sizeX/2,WINDOW_HEIGHT / 2-sizeY/2+sizeY*3,WINDOW_WIDTH/2+sizeX/2,WINDOW_HEIGHT / 2+sizeY/2+sizeY*3,"gray", "Tutorial")
	drawButton(startGameButton, startGameButtonText)
	drawButton(exitButton, exitButtonText)
	drawButton(creditButton, creditButtonText)
	drawButton(tutorialButton, tutorialButtonText)
	return startGameButton, exitButton, creditButton, tutorialButton

def displayTutorial():
	sizeX=WINDOW_WIDTH/2
	sizeY=WINDOW_HEIGHT/2
	centerPoint = Point(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2)
	tutorialWindow, tutorialText = button(WINDOW_WIDTH/2-sizeX/2,WINDOW_HEIGHT / 2-sizeY/2,WINDOW_WIDTH/2+sizeX/2,WINDOW_HEIGHT / 2+sizeY/2,"white", "This is the tutorial")
	closeButton, closeButtonText = button(sizeX/2+5,sizeY/2+5,sizeX/2+80,sizeY/2+40,"white", "Close")
	drawButton(tutorialWindow, tutorialText)
	drawButton(closeButton, closeButtonText)
	return closeButton, tutorialWindow

while True:
	startGameButton, exitButton, creditButton, tutorialButton=displayMainMenu()
	clickPoint = win.getMouse()
	if clickPoint is None:  # so we can substitute checkMouse() for getMouse()
		pass
	elif inside(clickPoint, startGameButton):
		gameStatus=True
	elif inside(clickPoint, exitButton):
		break
	elif inside(clickPoint, tutorialButton):
		closeButton, tutorialWindow=displayTutorial()
		while True:
			clicker = win.getMouse()
			if clicker is None:  # so we can substitute checkMouse() for getMouse()
				pass
			elif inside(clicker, closeButton):
				tutorialWindow.undraw()
				closeButton.undraw()
				break


win.close()