#
# Knapsack.py
# CS 131 - Artificial Intelligence
#
# Author: Ben Schmelkin

import random
MAX_WEIGHT = 250

# Backpack class to hold the state of a backpack
class Backpack:
        current_items = []
        total_importance = 0
        total_weight = 0
        total_fitness = 0

        def __init__(self, state):
                self.current_items = state
                self.total_weight = self.total_weight()
                self.total_importance = self.total_importance()
                self.total_fitness = self.total_fitness()


        def total_weight(self):
                total_weight_counter = 0
                for item in self.current_items:
                        total_weight_counter += item[2]
                return total_weight_counter

        def total_importance(self):
                total_importance_counter = 0
                for item in self.current_items:
                        total_importance_counter += item[1]
                return total_importance_counter

        # if the list is not valid, set the fitness to 0
        def total_fitness(self):
                if self.total_weight > MAX_WEIGHT or (len(self.current_items) != len(set(self.current_items))):
                        return 0
                else:
                        return self.total_importance + self.total_weight
        

# Genetic Algorithm class to hold logic to find the most ideal backpack
class Genetic_Algorithm:
        # sets the intial population from user input and assigns class variables
        def __init__(self):
                self.current_population = []
                self.best_fitness = 0
                self.best_fitness_counter = 0
                self.population_size = 0
                while self.population_size < 20 or self.population_size > 40:
                        self.population_size = int(input("Choose a number between 20 and 40: "))
                # make population even just so splitting in half is easier
                if self.population_size % 2 != 0:
                                print("adding 1 to initial population size to have an even number")
                                self.population_size += 1
                
        # creates an intial population with the number of elements input from the user
        def create_population(self):
                print("########## INITIAL POPULATION ##########")
                for i in range(self.population_size):
                        potential_items = list(all_items)
                        new_backpack_items = []
                        new_backpack_weight = 0
                        while new_backpack_weight <= MAX_WEIGHT:
                                random_to_add = random.choice(potential_items)
                                new_backpack_weight += random_to_add[2]
                                new_backpack_items.append(random_to_add)
                                potential_items.remove(random_to_add)
                        # remove the item that made the weight over 250
                        new_backpack_items.pop()
                        new_backpack = Backpack(new_backpack_items)
                        if new_backpack.total_fitness > self.best_fitness:
                                self.best_fitness = new_backpack.total_fitness
                        self.current_population.append(new_backpack)
                self.current_population = sorted(self.current_population, key=lambda x: x.total_fitness, reverse=True)
                print("Best Initial Backpack:", self.current_population[0].current_items)
                print("Total Importance Value:", self.current_population[0].total_importance)
                print("Total Weight", self.current_population[0].total_weight) 
                print("Best Fitness (importance + weight):", self.current_population[0].total_fitness)

        # main loop logic to find the best backpack
        def run_genetic_algorithm(self):
                self.create_population()
                # if the top fitness is the same for 5 times in a row, return the value the loop converged on
                while self.best_fitness_counter < 10:
                        self.cull_population()
                        # make new population to have children added to
                        new_population = list(self.current_population)
                        # create the same amount of children as the current population size so the size is the same as the initial
                        for i in range(self.population_size):
                                random_x = random.choice(self.current_population)
                                random_y = random.choice(self.current_population)
                                # ensure that random_x and random_y are not the same
                                while random_x == random_y:
                                        random_x = random.choice(self.current_population)
                                        random_y = random.choice(self.current_population)
                                child = self.reproduce(random_x, random_y)
                                # 10% chance of mutation
                                random_chance = random.randint(1, 10)
                                if random_chance == 1:
                                        child = self.mutate(child)
                                new_population.append(child)
                        self.current_population = new_population
                        self.population_size = len(new_population)
                        self.current_population = sorted(self.current_population, key=lambda x: x.total_fitness, reverse=True)
                        # if the best fitness is the same, add one to the counter
                        if self.best_fitness == self.current_population[0].total_fitness:
                                self.best_fitness_counter += 1
                        # else, set the fitness to the new best
                        else:
                                self.best_fitness = self.current_population[0].total_fitness
                                self.best_fitness_counter = 0
                # return the best backpack at the end
                return self.current_population[0]
                

        # crossover one element from y into x and return the resulting child
        def reproduce(self, x, y):
                # Find random indices for crossover
                random_index_x = random.randint(0, len(x.current_items) - 1)
                random_index_y = random.randint(0, len(y.current_items) - 1)
                # Create child_items by swapping elements from parents
                child_items = list(x.current_items)
                child_items[random_index_x] = y.current_items[random_index_y]

                return Backpack(child_items)


        # splits population in half
        def cull_population(self):
                split_index = len(self.current_population) // 2
                first_half = self.current_population[:split_index]  
                self.current_population = list(first_half)
                self.population_size = self.population_size // 2
                

        # mutates child
        def mutate(self, child):
                random_index_child = random.randint(0, len(child.current_items) - 1)
                random_index_all_items = random.randint(0, len(all_items) - 1)
                child.current_items[random_index_child] = all_items[random_index_all_items]

                return Backpack(child.current_items)


# First element is ID, Second is Importance, Third is Weight
all_items = [(1, 6, 20), (2, 5, 30), (3, 8, 60), (4, 7, 90), (5, 6, 50), (6, 9, 70), (7, 4, 30), (8, 5, 30), (9, 4, 70), (10, 9, 20), (11, 2, 20), (12, 1, 60)]

ge = Genetic_Algorithm()
best_backpack = ge.run_genetic_algorithm()

print("########## RESULT OF GENETIC ALGORITHM ##########")
print("Best Backpack:", best_backpack.current_items)
print("Total Importance Value:", best_backpack.total_importance)
print("Total Weight", best_backpack.total_weight) 
print("Best Fitness (importance + weight):", best_backpack.total_fitness)