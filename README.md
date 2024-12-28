# Battleship-solver

The goal of this task is to implement a strategy for playing a modified version of the popular Battleship game. 
The task is to hit and sink all enemy vessels. You launch a missile to a given location of the enemy field. It can hit a vessel and you will know that, or it can miss (hit the water). In case of a miss, differing from the classic game, it will report back the distances to the vessels that are in a given range (shaped as a circle around the hit point). Also each vessel will occupy a single cell from the field and it is possible to have two different vessels in adjacent cells.
As input data your program will get:
•	the size of the rectangular battle field – two integer numbers W (width) and H (height). Both are in the range [1, 1’000’000]. It is a discrete grid of cells with integer coordinates from 0 to W-1 and from 0 to H-1.
•	the number of enemy vessels – N , also an integer number in the range [1, 1’000’000].
•	the range of the missile ship detection in case of a miss – R, a number in range [1, 1’000’000].
At any step, your program will print two numbers -> the coordinates of the target cell. Then you can read from the standard input the response from the missile when it hits the field. In case you hit a vessel, the input will be a single word “Hit!”, and when you miss, the input will contain the word “Miss!”, followed by an integer number К in the range [0, N], that represents the number of vessels in the missile range and then К real numbers, representing the distances between the center of the cell that is hit and the centers of the cells where those vessels are placed. When all vessels are hit, the text “Win!” will be given as input.
Note: We will not provide a testing program (it is up to you to implement one for yourselves).
Here is an example:
Input (stdin)	Output (stdout)
	
5 5 3 10	1 2
Hit!	2 2
Miss! 2 2.236068 2.828427	0 4
Miss! 2 1.000000 5.656854	4 0
Hit!	1 4
Miss! 1 1.414214	0 3
Hit!
Win!	
And here is a map of the initial placement of the ships.
			S	
		S		
				
				
S				

