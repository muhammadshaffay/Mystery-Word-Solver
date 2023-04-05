# Mystery-Word-Solver
Mystery Word Solver : C++ program that locates words within a grid, providing exact indexes.

Mystery word puzzle is a word game that consists of the letters of words placed in a grid, which usually has a square shape. The objective of this puzzle is to find and mark all the words hidden inside the box.

Grid Creation:
The first step is to create a grid using grid.txt characters. Think of the grid as a 2-D array where each index has a character in it. The space separation of characters in the text file indicates different rows of grid. You can break down this part into further functions like:<br>
ReadFile()
PopulateGrid()

Word Finder:
Another text file is provided wordList.txt that contains the list of words to be searched. Create another array to store these words. Create a function that finds the existence as well as location of each word in the grid. The word may exist horizontally, vertically or diagonally. The starting index (row+column), the ending index as well as direction has to be calculated against each word found.<br>
searchWord()
