#
# Sudoku.py
# CS 131 - Artificial Intelligence
# Assignment 4
#
# Author: Ben Schmelkin

class Sudoku:
        def __init__(self, puzzle):
                self.puzzle = puzzle

        # recursively go through unassigned indices and populate, back track as needed
        def recursive_solve_sudoku(self):
                unassigned = self.find_minimum_value_remaining()

                if not unassigned:
                        return True

                potential_values = self.potential_values(unassigned)

                for num in potential_values:
                        if self.valid_assignment(unassigned, num):
                                self.puzzle[unassigned[0]][unassigned[1]] = num

                                if self.recursive_solve_sudoku():
                                        return True

                                self.puzzle[unassigned[0]][unassigned[1]] = 0

                return False

        # find which unassigned cell has the least amount of potential values to assign to it
        def find_minimum_value_remaining(self):
                unassigned = []
                for i in range(9):
                        for j in range(9):
                                if self.puzzle[i][j] == 0:
                                        unassigned.append((i, j))
                return min(unassigned, key=lambda x: self.minimum_remaining_value(x)) if unassigned else None

        # using the rules of sudoku, find the values in the row, col, and box of the index and take all the values that are not in that set
        def potential_values(self, index):
                row = index[0]
                col = index[1]
                assigned_in_row = set(self.puzzle[row])
                assigned_in_col = set(self.puzzle[r][col] for r in range(9))

                assigned_in_box = set()
                starting_row, starting_col = 3 * (row // 3), 3 * (col // 3)
                for i in range(3):
                        for j in range(3):
                                if self.puzzle[starting_row + i][starting_col + j] == 0:
                                        assigned_in_box.add(self.puzzle[starting_row + i][starting_col + j])

                all_assigned_values = assigned_in_row | assigned_in_col | assigned_in_box
                return [num for num in range(1, 10) if num not in all_assigned_values]

        # return the length of the potential values for an index
        def minimum_remaining_value(self, index):
                return len(self.potential_values(index))

        # check if the assignment valid in this index
        def valid_assignment(self, index, assignment):
                row = index[0]
                col = index[1]
                return (self.valid_row(row, assignment) and self.valid_col(col, assignment) and self.valid_box(row, col, assignment))

        # check if the assignment value is in the row
        def valid_row(self, row, assignment):
                return assignment not in self.puzzle[row]

        # check if the assignment value is in the col
        def valid_col(self, col, assignment):
                return all(self.puzzle[row][col] != assignment for row in range(9))

        # check if the assignment value is in the box
        def valid_box(self, row, col, assignment):
                starting_row, starting_col = 3 * (row // 3), 3 * (col // 3)
                for i in range(3):
                        for j in range(3):
                                if self.puzzle[starting_row + i][starting_col + j] == assignment:
                                        return False
                return True

puzzle_board_easy = [
        [6, 0, 8, 7, 0, 2, 1, 0, 0],
        [4, 0, 0, 0, 1, 0, 0, 0, 2],
        [0, 2, 5, 4, 0, 0, 0, 0, 0],
        [7, 0, 1, 0, 8, 0, 4, 0, 5],
        [0, 8, 0, 0, 0, 0, 0, 7, 0],
        [5, 0, 9, 0, 6, 0, 3, 0, 1],
        [0, 0, 0, 0, 0, 6, 7, 5, 0],
        [2, 0, 0, 0, 9, 0, 0, 0, 8],
        [0, 0, 6, 8, 0, 5, 2, 0, 3]
]

puzzle_board_hard = [
        [0, 7, 0, 0, 4, 2, 0, 0, 0],
        [0, 0, 0, 0, 0, 8, 6, 1, 0],
        [3, 9, 0, 0, 0, 0, 0, 0, 7],
        [0, 0, 0, 0, 0, 4, 0, 0, 9],
        [0, 0, 3, 0, 0, 0, 7, 0, 0],
        [5, 0, 0, 1, 0, 0, 0, 0, 0],
        [8, 0, 0, 0, 0, 0, 0, 7, 6],
        [0, 5, 4, 8, 0, 0, 0, 0, 0],
        [0, 0, 0, 6, 1, 0, 0, 5, 0]
]

board = puzzle_board_easy

choice = input("Would you like to solve the 'easy' or 'hard' sudoku? ")

while choice != "easy" and choice != "hard":
        choice = input("Would you like to solve the 'easy' or 'hard' sudoku?")
if choice == "easy":
        board = puzzle_board_easy
else:
        board = puzzle_board_hard

sudoku_solver = Sudoku(board)

print("Initial Puzzle:")
for row in sudoku_solver.puzzle:
    print(row)

if sudoku_solver.recursive_solve_sudoku():
    print("Solution: ")
    for row in sudoku_solver.puzzle:
        print(row)
else:
    print("No solution found.")
