# T3D classes
from graphics import *

def inside(point, rectangle):
	""" Is point inside rectangle? """

	ul = rectangle.getP1()  # assume p1 is upper left
	lr = rectangle.getP2()  # assume p2 is lower right 

	return ul.getX() < point.getX() < lr.getX() and ul.getY() < point.getY() < lr.getY()

class menu():
	def __init__(self, W, H, win):
		self.win = win
		self.W = W
		self.H = H
		self.createMain()

	def createMain(self):
		sizeX=self.W/2
		sizeY=self.H/9
		self.startGameButton = button(False, "gray", "Start Game", 	self.W/2-sizeX/2 , self.H/2-sizeY/2-sizeY*3 , self.W/2+sizeX/2 , self.H/2+sizeY/2-sizeY*3 , self.win)
		self.tutorialButton = button(False, "gray", "View Tutorial",self.W/2-sizeX/2 , self.H/2-sizeY/2-sizeY*1 , self.W/2+sizeX/2 , self.H/2+sizeY/2-sizeY*1 , self.win)
		self.creditsButton = button(False, "gray", "Credits", 		self.W/2-sizeX/2 , self.H/2-sizeY/2+sizeY*1 , self.W/2+sizeX/2 , self.H/2+sizeY/2+sizeY*1 , self.win)
		self.exitButton = button(False, "gray", "Exit",				self.W/2-sizeX/2 , self.H/2-sizeY/2+sizeY*3 , self.W/2+sizeX/2 , self.H/2+sizeY/2+sizeY*3 , self.win)
		
	def display(self):
		self.startGameButton.display()
		self.tutorialButton.display()
		self.creditsButton.display()
		self.exitButton.display()

	def hide(self):
		self.startGameButton.hide()
		self.tutorialButton.hide()
		self.creditsButton.hide()
		self.exitButton.hide()


	def startGame(self):
		#displayBoard
		return game() # returns a new game

	def exitApplication(self):
		exit()

	def openCredits(self):
		sizeX=self.W/2
		sizeY=self.H/2
		
		# draw and display a tutorial
		creditsWindow = button(False, "white", "This is the\n credits Window",self.W/2-sizeX/2,self.H / 2-sizeY/2,self.W/2+sizeX/2,self.H / 2+sizeY/2, self.win)
		creditsWindow.display()
		#create a close tutorial button and display it
		closeButton = button(False, "white", "Close", 	sizeX/2+5,sizeY/2+5,sizeX/2+80,sizeY/2+40, self.win)
		closeButton.display()

		# wait for the close tutorial button to close
		while True:
			clicker = self.win.getMouse()
			if clicker is None:  # so we can substitute checkMouse() for getMouse()
				pass
			elif closeButton.isClicked(clicker):
				creditsWindow.hide()
				closeButton.hide()
				break

	def closeCredits(self):
		pass

	
	def openTutorial(self):

		sizeX=self.W/2
		sizeY=self.H/2
		
		# draw and display a tutorial
		tutorialWindow = button(False, "white", "This is the tutorial Window",self.W/2-sizeX/2,self.H / 2-sizeY/2,self.W/2+sizeX/2,self.H / 2+sizeY/2, self.win)
		tutorialWindow.display()
		#create a close tutorial button and display it
		closeButton = button(False, "white", "Close", 	sizeX/2+5,sizeY/2+5,sizeX/2+80,sizeY/2+40, self.win)
		closeButton.display()

		# wait for the close tutorial button to close
		while True:
			clicker = self.win.getMouse()
			if clicker is None:  # so we can substitute checkMouse() for getMouse()
				pass
			elif closeButton.isClicked(clicker):
				tutorialWindow.hide()
				closeButton.hide()
				break
		# return to rest of main menu after exiting tutorial
	def closeTutorial(self):
		pass

	def endGame(self):
		pass

	def displayOutcome(self):
		pass

class game():
	def __init__(self, W, H, win):
		self.gameStatus = True
		self.playerTurn = 1
		self.boardView = True # True = 3D, False = 2D
		self.gameResult = 0
		self.mainMenuButton = False
		self.forfeitButton = False
		self.boardViewButton = False
		self.confirmButton = False
		self.cancelButton = False
		self.angle = 0

		self.win = win
		self.W = W
		self.H = H
		self.createGameButtons()
		#self.board = [layer(), layer(), layer(), layer()]

	def createGameButtons(self):
		sizeX=self.W/5
		sizeY=self.H/10
		self.returnToMenuButton = button(False, "gray", "Main Menu", sizeX/2 , self.H-3*sizeY/2 , 3*sizeX/2 , self.H-sizeY/2 , self.win)
		self.toggleBoardViewButton = button(False, "gray", "2-D View", 	self.W/2-sizeX/2 , self.H-4*sizeY/2 , self.W/2+sizeX/2 , self.H-sizeY/2 , self.win)
		self.forfeitButton = button(False, "gray", "Forfeit Game", 		self.W-3*sizeX/2 , self.H-3*sizeY/2 , self.W-sizeX/2 , self.H-sizeY/2 , self.win)
		self.helpButton = button(False, "light blue", "?", self.W-50 , 10 , self.W-10 , 50 , self.win)
		self.gameBoard=board(self.W, self.H, self.win)
		self.playerText = textObject("red","", self.W/2, self.H/10, self.win)

	def toggle(self):
		if self.boardView:
			self.gameBoard.hide3DBoard()
			self.gameBoard.display2DBoard()
			self.toggleBoardViewButton.updateText("2D-View")
		else:
			self.gameBoard.hide2DBoard()
			self.gameBoard.display3DBoard()
			self.toggleBoardViewButton.updateText("3D-View")
	
	def nextTurn(self):
		if self.winCondition():
			self.gameResult=2-self.playerTurn%2
			return True
		elif self.playerTurn>63:
			return True
		self.playerTurn = self.playerTurn+1
		self.playerText.updateText(2-self.playerTurn%2)
		return False

	def winCondition(self):
		pass

	def display(self):
		self.toggleBoardViewButton.display()
		self.returnToMenuButton.display()
		self.forfeitButton.display()
		self.helpButton.display()
		self.playerText.updateText(2-self.playerTurn%2)
		if self.boardView:
			self.gameBoard.display2DBoard()
			self.toggleBoardViewButton.updateText("2D-View")
		else:
			self.gameBoard.display3DBoard()
			self.toggleBoardViewButton.updateText("3D-View")
			
	def hide(self):
		self.toggleBoardViewButton.hide()
		self.returnToMenuButton.hide()
		self.forfeitButton.hide()
		self.helpButton.hide()
		self.playerText.updateText(0)
		if self.boardView:
			self.gameBoard.hide2DBoard()
		else:
			self.gameBoard.hide3DBoard()
			
	def setBoardView(self):
		pass

	def getBoardView(self):
		pass

	def getPlayerTurn(self):
		pass

	def setPlayerTurn(self, playerTurn):
		self.playerTurn = playerTurn

	def getGameStatus(self):
		pass

	def setGameStatus(self):
		pass

	def getGameResult(self):
		pass

	def openTutorial(self):

		sizeX=self.W/2
		sizeY=self.H/2
		
		# draw and display a tutorial
		tutorialWindow = button(False, "white", "This is the tutorial Window",self.W/2-sizeX/2,self.H / 2-sizeY/2,self.W/2+sizeX/2,self.H / 2+sizeY/2, self.win)
		tutorialWindow.display()
		#create a close tutorial button and display it
		closeButton = button(False, "white", "Close", 	sizeX/2+5,sizeY/2+5,sizeX/2+80,sizeY/2+40, self.win)
		closeButton.display()

		# wait for the close tutorial button to close
		while True:
			clicker = self.win.getMouse()
			if clicker is None:  # so we can substitute checkMouse() for getMouse()
				pass
			elif closeButton.isClicked(clicker):
				tutorialWindow.hide()
				closeButton.hide()
				break
		# return to rest of main menu after exiting tutorial

	def cancelPopUp(self):
		pass

	def confirmExit(self):

		sizeX=self.W/2
		sizeY=self.H/2
		
		# draw and display confirm exit to main menu button
		confirmExitWindow = button(False, "white", "Do you really want to \nreturn to the main menu?",self.W/2-sizeX/2,self.H / 2-sizeY/2,self.W/2+sizeX/2,self.H / 2+sizeY/2, self.win)
		confirmExitWindow.display()

		#create a close tutorial button and display it
		confirmExitButton = button(False, "white", "Confirm Exit", 	3*sizeX/2-200,  3*sizeY/2-50,  3*sizeX/2-5,  3*sizeY/2-5, self.win)
		confirmExitButton.display()

		cancelExitButton = button(False, "white", "Cancel Exit", 	sizeX/2+5,  3*sizeY/2-50,  sizeX/2+200,  3*sizeY/2-5, self.win)
		cancelExitButton.display()

		# wait for the close tutorial button to close
		while True:
			clicker = self.win.getMouse()
			if clicker is None:  # so we can substitute checkMouse() for getMouse()
				pass
			elif confirmExitButton.isClicked(clicker):
				print("confirm exit clicked")
				confirmExitButton.hide()
				confirmExitWindow.hide()
				cancelExitButton.hide()
				return True

			elif cancelExitButton.isClicked(clicker):
				print("Cancel exit clicked")
				confirmExitButton.hide()
				confirmExitWindow.hide()
				cancelExitButton.hide()
				return False
			else:
				print("else")

	def confirmForfeit(self):
		sizeX=self.W/2
		sizeY=self.H/2
		
		# draw and display confirm Forfeit to main menu button
		confirmForfeitWindow = button(False, "white", "Do you really want to \nforfeit? Your opponent is guarenteed to win",self.W/2-sizeX/2,self.H / 2-sizeY/2,self.W/2+sizeX/2,self.H / 2+sizeY/2, self.win)
		confirmForfeitWindow.display()

		#create a close tutorial button and display it
		confirmForfeitButton = button(False, "white", "Confirm forfeit", 	3*sizeX/2-200,  3*sizeY/2-50,  3*sizeX/2-5,  3*sizeY/2-5, self.win)
		confirmForfeitButton.display()

		cancelForfeitButton = button(False, "white", "Cancel forfeit", 	sizeX/2+5,  3*sizeY/2-50,  sizeX/2+200,  3*sizeY/2-5, self.win)
		cancelForfeitButton.display()

		# wait for the close tutorial button to close
		while True:
			clicker = self.win.getMouse()
			if clicker is None:  # so we can substitute checkMouse() for getMouse()
				pass
			elif confirmForfeitButton.isClicked(clicker):
				print("confirm forfeit clicked")
				confirmForfeitButton.hide()
				confirmForfeitWindow.hide()
				cancelForfeitButton.hide()
				self.gameResult= self.playerTurn%2+1
				return True

			elif cancelForfeitButton.isClicked(clicker):
				print("Cancel forfeit clicked")
				confirmForfeitButton.hide()
				confirmForfeitWindow.hide()
				cancelForfeitButton.hide()
				return False
			else:
				print("else")

	def getBoardPosition(self, Layer, row, col):
		pass

	def checkWinCondition(self):
		pass

	# Includes methods to return to main menu without forfeiting
	def goToMainMenu(self):
		pass
		
	def displayOutcome(self):
		sizeX=self.W/2
		sizeY=self.H/2
		
		if self.gameResult == 1:
			winnerWindow = button(False, "pink", "Player 1 wins!",self.W/2-sizeX/2,self.H / 2-sizeY/2,self.W/2+sizeX/2,self.H / 2+sizeY/2, self.win)
			winnerWindow.display()		
		elif self.gameResult == 2:
			winnerWindow = button(False, "light blue", "Player 2 wins!",self.W/2-sizeX/2,self.H / 2-sizeY/2,self.W/2+sizeX/2,self.H / 2+sizeY/2, self.win)
			winnerWindow.display()		
		else:
			winnerWindow = button(False, "light green", "It's a tie!",self.W/2-sizeX/2,self.H / 2-sizeY/2,self.W/2+sizeX/2,self.H / 2+sizeY/2, self.win)
			winnerWindow.display()

		#create a close tutorial button and display it
		mainMenuExitButton = button(False, "white", "Main Menu", 	3*sizeX/2-200,  3*sizeY/2-50,  3*sizeX/2-5,  3*sizeY/2-5, self.win)
		mainMenuExitButton.display()

		playAgainButton = button(False, "white", "Play Again", 	sizeX/2+5,  3*sizeY/2-50,  sizeX/2+200,  3*sizeY/2-5, self.win)
		playAgainButton.display()

		# wait for the close tutorial button to close
		while True:
			clicker = self.win.getMouse()
			if clicker is None:  # so we can substitute checkMouse() for getMouse()
				pass
			elif mainMenuExitButton.isClicked(clicker):
				print("confirm forfeit clicked")
				mainMenuExitButton.hide()
				winnerWindow.hide()
				playAgainButton.hide()
				return True

			elif playAgainButton.isClicked(clicker):
				print("Cancel forfeit clicked")
				mainMenuExitButton.hide()
				winnerWindow.hide()
				playAgainButton.hide()
				return False
			else:
				print("else")

class board():
	def __init__(self, W, H, win):
		self.W=W
		self.H=H
		self.win=win
		self.layerPositions = [layer('#ff1ab3', 0, self.W, self.H, self.win), layer('#ff8000', 1, self.W, self.H, self.win), layer('#b3b300', 2, self.W, self.H, self.win), layer('#39ac73', 3, self.W, self.H, self.win)]
		pass

	def display2DBoard(self):
		self.layerPositions[0].display2DLayer()
		self.layerPositions[1].display2DLayer()
		self.layerPositions[2].display2DLayer()
		self.layerPositions[3].display2DLayer()
		
	def hide2DBoard(self):
		self.layerPositions[0].hide2DLayer()
		self.layerPositions[1].hide2DLayer()
		self.layerPositions[2].hide2DLayer()
		self.layerPositions[3].hide2DLayer()	

	def display3DBoard(self):
		pass

	def hide3DBoard(self):
		pass
		
	def addMarker(self, layerNumber, click, player):
		return self.layerPositions[layerNumber].addMarker(click, player)

	def readMarker(self, layerNumber, row, col):
		return self.layerPositions[layerNumber].readMarker(row, col)

class layer():
	def __init__(self, layerColor, layerNumber, W, H, win):
		self.layerColor=layerColor
		self.layerNumber=layerNumber
		self.W=W
		self.H=H
		self.win=win
		if self.W/6 < self.H/2:
			self.size = self.W/6
		else:
			self.size = self.H/2
		self.centerX = (1.5*self.layerNumber+0.75)*(self.W/6)
		self.centerY = self.W/4
		self.createLayer()
		self.markerPosition = [[marker(0, Point(0,0), 0, self.win) for x in range(4)] for y in range(4)] 
		pass

	def createLayer(self):
		self.grid()
		self.text= Text(Point(self.centerX,self.centerY+self.size/2+20),"Layer "+str(self.layerNumber))
		self.text.setSize(30)
		self.text.setFill(self.layerColor)

	def grid(self):
		self.v1Line = Line(Point(self.centerX-self.size/2,self.centerY-self.size/4), Point(self.centerX+self.size/2,self.centerY-self.size/4))
		self.x1Line = Line(Point(self.centerX-self.size/4,self.centerY-self.size/2), Point(self.centerX-self.size/4,self.centerY+self.size/2))
		self.v1Line.setFill(self.layerColor)
		self.x1Line.setFill(self.layerColor)
		self.v2Line = Line(Point(self.centerX-self.size/2,self.centerY), Point(self.centerX+self.size/2,self.centerY))
		self.x2Line = Line(Point(self.centerX,self.centerY-self.size/2), Point(self.centerX,self.centerY+self.size/2))
		self.v2Line.setFill(self.layerColor)
		self.x2Line.setFill(self.layerColor)
		self.v3Line = Line(Point(self.centerX-self.size/2,self.centerY+self.size/4), Point(self.centerX+self.size/2,self.centerY+self.size/4))
		self.x3Line = Line(Point(self.centerX+self.size/4,self.centerY-self.size/2), Point(self.centerX+self.size/4,self.centerY+self.size/2))
		self.v3Line.setFill(self.layerColor)
		self.x3Line.setFill(self.layerColor)
		if self.layerNumber==0:
			self.layerButton = button(False, "#ffe6f7", "", self.centerX-self.size/2, self.centerY-self.size/2, self.centerX+self.size/2, self.centerY+self.size/2, self.win)
			self.buttons = [[button(False, "#ffe6f7", "", self.centerX-self.size/2+self.size/4*x, self.centerY-self.size/2+self.size/4*y, self.centerX-self.size/2+self.size/4*(x+1), self.centerY-self.size/2+self.size/4*(y+1), self.win) for y in range(4)] for x in range(4)]
		elif self.layerNumber==1:
			self.layerButton = button(False, "#ffe5cc", "", self.centerX-self.size/2, self.centerY-self.size/2, self.centerX+self.size/2, self.centerY+self.size/2, self.win)
			self.buttons = [[button(False, "#ffe5cc", "", self.centerX-self.size/2+self.size/4*x, self.centerY-self.size/2+self.size/4*y, self.centerX-self.size/2+self.size/4*(x+1), self.centerY-self.size/2+self.size/4*(y+1), self.win) for y in range(4)] for x in range(4)]
		elif self.layerNumber==2:
			self.layerButton = button(False, "#ffffb3", "", self.centerX-self.size/2, self.centerY-self.size/2, self.centerX+self.size/2, self.centerY+self.size/2, self.win)
			self.buttons = [[button(False, "#ffffb3", "", self.centerX-self.size/2+self.size/4*x, self.centerY-self.size/2+self.size/4*y, self.centerX-self.size/2+self.size/4*(x+1), self.centerY-self.size/2+self.size/4*(y+1), self.win) for y in range(4)] for x in range(4)]
		elif self.layerNumber==3:
			self.layerButton = button(False, "#c6ecd9", "", self.centerX-self.size/2, self.centerY-self.size/2, self.centerX+self.size/2, self.centerY+self.size/2, self.win)
			self.buttons = [[button(False, "#c6ecd9", "", self.centerX-self.size/2+self.size/4*x, self.centerY-self.size/2+self.size/4*y, self.centerX-self.size/2+self.size/4*(x+1), self.centerY-self.size/2+self.size/4*(y+1), self.win) for y in range(4)] for x in range(4)]


	def display2DLayer(self):
		for x in range(4):
			for y in range(4):
				self.buttons[x][y].display()
		self.layerButton.display()
		self.v1Line.draw(self.win)
		self.x1Line.draw(self.win)
		self.v2Line.draw(self.win)
		self.x2Line.draw(self.win)
		self.v3Line.draw(self.win)
		self.x3Line.draw(self.win)
		self.text.draw(self.win)
		for y in range(4):
			for x in range(4):
				self.buttons[x][y].hide()
				if self.markerPosition[x][y].val!=0:
					self.markerPosition[x][y].display()


	def hide2DLayer(self):
		self.v1Line.undraw()
		self.x1Line.undraw()
		self.v2Line.undraw()
		self.x2Line.undraw()
		self.v3Line.undraw()
		self.x3Line.undraw()
		self.text.undraw()
		self.layerButton.hide()
		for y in range(4):
			for x in range(4):
				self.buttons[x][y].hide()
				if self.markerPosition[x][y].val!=0:
					self.markerPosition[x][y].hide()
		
	def addMarker(self, click, player):
		for y in range(4):
			for x in range(4):
				if self.buttons[x][y].isClicked(click):
					if self.markerPosition[x][y].val!=0:
						return False
					else:
						self.markerPosition[x][y]=marker(player,Point(self.centerX-self.size/2+self.size/4*(x+0.5), self.centerY-self.size/2+self.size/4*(y+0.5)),self.size/8,self.win)
						self.markerPosition[x][y].display()
						return True

	def readMarker(self, row, col):
		return self.layerPositions[layerNumber].readMarker(row, col)

class marker( ):
	def __init__(self, val, center, radius, win):
		if val==1:
			self.color = "red"
			self.val = val
		elif val==2:
			self.color = "blue"
			self.val = val
		else:
			self.color = "gray"
			self.val = val
		self.markerCircle = Circle(center,radius)
		self.markerCircle.setFill(self.color)
		self.win=win

	def display(self):
		self.markerCircle.draw(self.win)

	def hide(self):
		self.markerCircle.undraw()


class cross(marker):
	def __init__(self):
		self.color = 'blue'
		pass
	pass

class naught(marker):
	def __init__(self):
		self.color = 'blue'
		pass
	pass

class button():
	def __init__(self, initState, color, text, x1, y1, x2, y2, win):
		self.state = initState
		self.color = color
		self.text = text
		self.x1 = x1
		self.y1 = y1
		self.x2 = x2
		self.y2 = y2
		self.win = win
		self.box = Rectangle(Point(self.x1,self.y1), Point(self.x2, self.y2))
		self.text = Text(Point((self.x1+self.x2)/2,(self.y1+self.y2)/2),self.text)
		self.box.setFill(self.color)

	def updateText(self, newText):
		self.text = Text(Point((self.x1+self.x2)/2,(self.y1+self.y2)/2),newText)
		self.hide()
		self.display()

	def display(self):
		self.box.draw(self.win)
		self.text.draw(self.win)

	def hide(self):
		self.box.undraw()
		self.text.undraw()

	def isClicked(self, point):
		ul = self.box.getP1()  # assume p1 is upper left
		lr = self.box.getP2()  # assume p2 is lower right 
		return ul.getX() < point.getX() < lr.getX() and ul.getY() < point.getY() < lr.getY()

class textObject():
	def __init__(self, color, text, x, y, win):
		self.color = color
		self.text = text
		self.x = x
		self.y = y
		self.win = win
		self.text = Text(Point(self.x,self.y),self.text)
		self.updateText(0)

	def updateText(self, playerID):
		if playerID == 1:
			self.text.setText("Player 1's turn")
			self.text.setFill("red")
			self.text.setStyle("bold")
			self.text.setSize(36)
			self.hide()
			self.display()

		elif playerID == 2:
			self.text.setText("Player 2's turn")
			self.text.setFill("blue")
			self.text.setStyle("bold")
			self.text.setSize(36)
			self.hide()
			self.display()
		
		else:
			self.text.setText("")
			self.hide()
			self.display()
	def display(self):
		self.text.draw(self.win)

	def hide(self):
		self.text.undraw()
