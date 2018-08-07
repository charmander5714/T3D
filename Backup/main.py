from graphics import *
from T3DClasses import *

# initial Application conditions

# create and setup Window display
WINDOW_WIDTH, WINDOW_HEIGHT = 1500, 900

win = GraphWin("Simple Breakout", WINDOW_WIDTH, WINDOW_HEIGHT)

# create menu
mainMenu = menu(WINDOW_WIDTH, WINDOW_HEIGHT, win)
mainMenu.display()
currentGame = game(WINDOW_WIDTH, WINDOW_HEIGHT, win)

# display loop for
while True:
	clickPoint = win.getMouse()
	# game is in menuMode
	if mainMenu.startGameButton.state == False:
		
		# check buttons in Menu for clicks
		if mainMenu.exitButton.isClicked(clickPoint):
			exit()
		elif mainMenu.startGameButton.isClicked(clickPoint):
			mainMenu.hide()
			currentGame = game(WINDOW_WIDTH, WINDOW_HEIGHT, win)
			mainMenu.startGameButton.state = True
			currentGame.display()
			# print("Game Started")
			
			
		elif mainMenu.tutorialButton.isClicked(clickPoint):
			# print("This is the tutorial")
			# Waits for the close tutorial button to close
			mainMenu.openTutorial()

		elif mainMenu.creditsButton.isClicked(clickPoint):
			# print("this is the credits")
			# waits for the close credits button to close
			mainMenu.openCredits()


	elif mainMenu.startGameButton.state == True: # Game is in play
		
		# check for button clicks in game menu
		if currentGame.forfeitButton.isClicked(clickPoint):
			if currentGame.confirmForfeit() == True: # the pop up is confirmed
				print("Game Forfeited")
				if currentGame.displayOutcome() == True: #main menu button pressed
					mainMenu.startGameButton.state = False
					currentGame.hide()
					mainMenu.display()
				else:
					mainMenu.startGameButton.state = False
					currentGame.hide()
					currentGame = game(WINDOW_WIDTH, WINDOW_HEIGHT, win)
					mainMenu.startGameButton.state = True
					currentGame.display()
			else: # user clicked cancel exit
				print("User has canceled a return to the main menu")
				pass
			
		elif currentGame.toggleBoardViewButton.isClicked(clickPoint):
			currentGame.boardView = not currentGame.boardView
			currentGame.toggle()
			print("toggle the board view 2D/3D")
			
		elif currentGame.returnToMenuButton.isClicked(clickPoint):
			if currentGame.confirmExit() == True: # the pop up is confirmed
				mainMenu.startGameButton.state = False
				currentGame.hide()
				mainMenu.display()
				pass
			else: # user clicked cancel exit
				print("User has canceled a return to the main menu")
				pass
		elif currentGame.helpButton.isClicked(clickPoint):
			print("This is the tutorial")
			currentGame.openTutorial()
		else:
			print("else")
			
		#Check for button clicks in game board
		if True:
			pass
		else:
			pass


win.close()

