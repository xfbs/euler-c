# Problem 534: Weak Queens
The classical eight queens puzzle is the well known problem of placing
eight chess queens on a 8×8 chessboard so that no two queens threaten
each other. Allowing configurations to reappear in rotated or mirrored
form, a total of 92 distinct configurations can be found for eight
queens. The general case asks for the number of distinct ways of placing
n queens on a n×n board, e.g. you can find 2 distinct configurations for
n=4. Lets define a weak queen on a n×n board to be a piece which can
move any number of squares if moved horizontally, but a maximum of n−1−w
squares if moved vertically or diagonally, 0≤w
