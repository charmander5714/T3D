from graphics import *

WIDTH, HEIGHT = 500, 500

BOB_SIZE = 30
BOB_DISTANCE = 5

def main():
	win = GraphWin("Animation", WIDTH, HEIGHT)

	# Create Bob in the middle of the window
	cornerB1 = Point(WIDTH/2 + BOB_SIZE/2, HEIGHT/2 + BOB_SIZE/2)
	cornerB2 = Point(WIDTH/2 - BOB_SIZE/2, HEIGHT/2 - BOB_SIZE/2)

	Bob = Rectangle(cornerB1, cornerB2)
	Bob.setFill('blue')
	Bob.draw(win)

	dy = BOB_DISTANCE
	while True:
		for _ in range(500):
			Bob.move(0, dy)

			center = Rectangle.getCenter(Bob)
			centerY = Point.getY(center)

			# If too close to edge, reverse direction
			if centerY < BOB_SIZE/2 or centerY > HEIGHT - BOB_SIZE/2:
				dy = -dy

	win.close()

main()