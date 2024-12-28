# Battleship-solver

## Goal
The goal of this task is to implement a strategy for playing a modified version of the popular Battleship game. 
The task is to hit and sink all enemy vessels. You launch a missile to a given location of the enemy field. It can hit a vessel and you will know that, or it can miss (hit the water). In case of a miss, differing from the classic game, it will report back the distances to the vessels that are in a given range (shaped as a circle around the hit point). Also each vessel will occupy a single cell from the field and it is possible to have two different vessels in adjacent cells.

## Input
As input data your program will get:
-•	the size of the rectangular battle field – two integer numbers W (width) and H (height). Both are in the range [1, 1’000’000]. It is a discrete grid of cells with integer coordinates from 0 to W-1 and from 0 to H-1.
-•	the number of enemy vessels – N , also an integer number in the range [1, 1’000’000].
-•	the range of the missile ship detection in case of a miss – R, a number in range [1, 1’000’000].

## Output
At any step, your program will print two numbers -> the coordinates of the target cell. Then you can read from the standard input the response from the missile when it hits the field. In case you hit a vessel, the input will be a single word “Hit!”, and when you miss, the input will contain the word “Miss!”, followed by an integer number К in the range [0, N], that represents the number of vessels in the missile range and then К real numbers, representing the distances between the center of the cell that is hit and the centers of the cells where those vessels are placed. When all vessels are hit, the text “Win!” will be given as input.
Note: We will not provide a testing program (it is up to you to implement one for yourselves).

## Example
| Input (stdin) | Output (stdout)         |
|---------------|-------------------------|
| 5 5 3 10      | 1 2                    |
| Hit!          | 2 2                    |
| Miss!         | 2 2.236068 2.828427    |
| Miss!         | 2 1.000000 5.656854    |
| Hit!          | 4 0                    |
| Miss!         | 1 1.414214             |
| Hit!          | 0 3                    |
| Win!          |                        |

### And here is a map of the initial placement of the ships.
<pre>
+---+---+---+---+---+
|   |   |   | s |   |
+---+---+---+---+---+
|   |   | s |   |   |
+---+---+---+---+---+
|   |   |   |   |   |
+---+---+---+---+---+
|   |   |   |   |   |
+---+---+---+---+---+
| s |   |   |   |   |
+---+---+---+---+---+
</pre>

## Solution
The solution employs the divide-and-conquer approach to partition the battlefield grid into sections, reducing the number of cells that need to be calculated in each step of the partitioning process. This reduces the possible memory size which can overflow the stack for large partitions(milions^2). A partition is ideally square in shape and with size so that the detection radius is longer than the distance from the center of the partition to any of its corners and that distance is maximal. for the ends of the grid where such shape cannot be created the center cell is calculated accordingly off-center to its maximum distance from the up-left corner(as if normal square partition is chopped where the grid ends). Each search in a partition starts with strike in the center(all partitions are with odd sizes). **If** we strike a *Hit!* **then** we divide the partition in 4 quadrants and search into them seperatly, **else** we hit the 4 sides up,down,left,right on the center cell level using repetitive strike if the strike is a Hit! and then clearing the whole center cross(all cells at center cell x and all cells at center cell y) using **linear_bilateration**. Next when we are left with the 4 quadrants to search we use **trilateration** to determine where a Hit! can be made ensuring minimal strikes needed for the search. Thus solving the problem.
