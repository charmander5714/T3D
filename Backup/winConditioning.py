
def checkWin(board, startPosition): # 0 means no win met, 1 means player 1 wins, 2 means player 2 wins

	result = 0
	player = board[startPosition]
	layerNumber = 0
	rowNumber = 0
	columnNumber = 0

	# UP and DOWN
	for layerNumber in range(0, 4):
		if board[startPosition%16+16*layerNumber] != player:
			break
		else:
			layerNumber = layerNumber + 1
	if layerNumber == 4:
		return True
	
	# LEFT and RIGHT
	for columnNumber in range(0, 4):
		if board[startPosition - startPosition%4 + columnNumber] != player:
			break
		else:
			columnNumber = columnNumber + 1
	if columnNumber == 4:
		return True
	
	# FORWARD and BACKWARD
	for rowNumber in range(0, 4):
		if board[startPosition%4 + 4*rowNumber + startPosition - startPosition%16] != player:
			break
		else:
			rowNumber = rowNumber + 1
	if rowNumber == 4:
		return True

	# Same-layer diagonal checks
	if (startPosition%16)%5 == 0:	# Top Left to Bottom Right Same layer
		for rowNumber in range(0, 4):
			if board[startPosition - startPosition%16 + 5*rowNumber] != player:
				break
			else:
				rowNumber = rowNumber + 1
		if rowNumber == 4:
			return True	
	
	elif (startPosition%16)%3 == 0 and (startPosition+1)%16 > 1: # Bottom Left to Top Right Same Layer
		for rowNumber in Range(0, 4):
			if board[startPosition - startPosition%16 + 3*rowNumber+3] != player:
				break
			else:
				rowNumber = rowNumber + 1
		if rowNumber == 4:
			return True
			
	# Top layer Left Column to Bottom Layer Right Column
	if (startPosition%16 - int(floor(startPosition / 16)))%4 == 0:
		for rowNumber in range(0, 4):
			if board[startPosition%17 + 17*rowNumber] != player:
				break
			else:
				rowNumber = rowNumber + 1
		if rowNumber == 4:
			returnTrue
		
	# Top layer Right Column to Bottom Layer Left Column
	elif (startPosition%16 + int(floor(startPosition / 16)))%4 == 3:
		for rowNumber in range(0, 4):
			if board[startPosition%15 + 15*rowNumber] != player:
				break
			else:
				rowNumber = rowNumber + 1
			if rowNumber == 4:
				return True
		
	# Top layer Back Row to Bottom Layer Front Row
	if (startPosition%16-int(floor(startPosition/16)) * 4) < 4:
		for rowNumber in range(0,4):
			if board[startPosition%20 + 20*rowNumber] != player:
				break
			else:
				rowNumber = rowNumber + 1
		if rowNumber == 4:
			return True
		
	# Top layer Front Row to Bottom Layer Back Row
	elif (startPosition%16 + int(floor(startPosition / 16)) * 4)%16 > 11:
		for rowNumber in range(0, 4):
			if board[startPosition%12 + 12*rowNumber] != player:
				break
			else:
				rowNumber = rowNumber + 1
		if rowNumber == 4:
			return True
		
	# 0 to 63
	if((startPosition%16 - int(floor(startPosition / 16)) * 5) ==0):
		for rowNumber in range(0, 4):
			if board[0 + 21*rowNumber] != player:
				break
			else:
				rowNumber = rowNumber + 1
		if rowNumber == 4:
			return True

	#3 to 60
	elif((startPosition%16 - int(floor(startPosition / 16)) * 3) == 3):
		for rowNumber in range(0, 4):
			if board[3 + 19*rowNumber] != player:
				break
			else:
				rowNumber = rowNumber + 1
		if rowNumber == 4:
			return True
					
	#12 to 51
	elif (startPosition%16 + int(floor(startPosition/ 16 ))*  3) == 12:
		for rowNumber in range(0, 4):
			if board[12 + 13*rowNumber] != player:
				break
			else:
				rowNumber = rowNumber + 1
		if rowNumber == 4:
			return True
					
	#15 to 48
	elif (startPosition%16 + int(floor(startPosition / 16)) * 5) == 15:
		for rowNumber in range(0, 4):
			if board[15 + 11*rowNumber] != player:
				break
			else:
				rowNumber = rowNumber + 1
		if rowNumber == 4:
			return True
	
	return(false)

gameboard = [[[0,0,0,0], [0,1,0,0], [0,0,1,0], [0,0,0,1]], [[0,0,0,0], [0,0,0,0], [0,0,0,0], [0,0,0,0]], [[0,0,0,0], [0,0,0,0], [0,0,0,0], [0,0,0,0]], [[0,0,0,0], [0,0,0,0], [0,0,0,0], [0,0,0,0]]] 
print(checkWin(gameboard, 0))