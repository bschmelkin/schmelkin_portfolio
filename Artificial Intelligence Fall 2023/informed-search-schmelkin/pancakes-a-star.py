#
# Pancake Uniform Cost Search Solution
# CS 131 - Artificial Intelligence
#
# Author: Ben Schmelkin

import heapq
import random

# Calculates the Gap Heurisitc of a given pancake state

def CalculateGapHeuristic(pancake_state):
        gaps = 0
        for pancakes in range(len(pancake_state) - 1):
                if abs(pancake_state[pancakes] - pancake_state[pancakes + 1]) != 1:
                        gaps += 1
        return gaps

# Definition of Stack Node which is the building block for the search tree
# Each node has an interation of the initial state with various flips applied 

class Stack_Node:
        current_state = []
        backwards_cost = 0
        path = []
        heuristic_cost = 0
        total_cost = 0
        
        def __init__(self, current_state, path, backwards_cost):
                self.current_state = current_state
                self.backwards_cost = backwards_cost
                self.heuristic_cost = CalculateGapHeuristic(self.current_state)
                self.total_cost = self.heuristic_cost + self.backwards_cost
                self.path = path.copy()
                self.path.append(self)

        def __lt__(self, other):
                return self.total_cost < other.total_cost

# Definition of Priority Queue class which defines which node to be looked at next
# Uses a heap to keep track of the value with the next greatest priority 

class Priority_Queue:
        priority_heap = []
        def __init__(self, root_node):
                self.priority_heap = [root_node]
        
        def priority_sort(self):
                heapq.heapify(self.priority_heap)

        def remove_node(self):
                return heapq.heappop(self.priority_heap)
                        
        def add_node(self, child_stack_node):
                heapq.heappush(self.priority_heap, child_stack_node)

# Logic for A star Search  

def pancake_a_star_sort(start_state):
        start_node = Stack_Node(start_state, [], 0)
        priority_queue = Priority_Queue(start_node)
        priority_queue.priority_sort()
        while priority_queue.priority_heap:
                current_node = priority_queue.remove_node()
                if current_node.current_state == sorted(current_node.current_state):
                        return current_node
                for i in range(1, len(current_node.current_state) + 1):
                        flipped_state = current_node.current_state[:i][::-1] + current_node.current_state[i:]
                        child_stack_node = Stack_Node(flipped_state, current_node.path, current_node.backwards_cost + 1)
                        priority_queue.add_node(child_stack_node)

# Program flow

initial_state = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
random.shuffle(initial_state)
solution_node = pancake_a_star_sort(initial_state)
print("Number of flips:", solution_node.backwards_cost)
print("initial State:", initial_state)
for i in range(1, len(solution_node.path) - 1):
        print("Flip #", i, solution_node.path[i].current_state)
print("Last Flip = Sorted State:", solution_node.current_state)
