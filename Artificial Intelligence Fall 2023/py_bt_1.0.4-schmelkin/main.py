#
# Behavior Tree framework for A1 Behavior trees assignment.
# CS 131 - Artificial Intelligence
#
# version 1.0.4 - copyright (c) 2023 Santini Fabrizio. All rights reserved.
# Current Implementation: Ben Schmelkin

import bt_library as btl
import random
from behavior_tree import tree_root

from globals import BATTERY_LEVEL, GENERAL_CLEANING, SPOT_CLEANING, DUSTY_SPOT_SENSOR, HOME_PATH, IS_HOME, IS_CHARGING

# Main body of the assignment
current_blackboard = btl.Blackboard()
current_blackboard.set_in_environment(BATTERY_LEVEL, 29)
current_blackboard.set_in_environment(SPOT_CLEANING, False)
current_blackboard.set_in_environment(GENERAL_CLEANING, False)
current_blackboard.set_in_environment(DUSTY_SPOT_SENSOR, False)
current_blackboard.set_in_environment(HOME_PATH, "")
current_blackboard.set_in_environment(IS_HOME, False)
current_blackboard.set_in_environment(IS_CHARGING, False)


done = False
cyclesCompleted = 0

while not done:
    # Each cycle in this while-loop is equivalent to 1 second time

    # Step 1: Change the environment

    #   - change the battery level

    # logic to charge the battery if needed
    if (current_blackboard.get_in_environment(IS_HOME, True) == True):
        current_blackboard.set_in_environment(HOME_PATH, "")
        current_blackboard.set_in_environment(IS_CHARGING, True)
        
    if ((current_blackboard.get_in_environment(IS_CHARGING, True) == True) and (current_blackboard.get_in_environment(BATTERY_LEVEL, 100)) < 100):
        current_blackboard.set_in_environment(BATTERY_LEVEL, current_blackboard.get_in_environment(BATTERY_LEVEL, 50) + 25)

    elif (current_blackboard.get_in_environment(IS_CHARGING, True) == True):
        current_blackboard.set_in_environment(IS_CHARGING, False)
        current_blackboard.set_in_environment(IS_HOME, False)
        current_blackboard.set_in_environment(BATTERY_LEVEL, 100)

    # battery leaves home and immediately begins to drain battery
    current_blackboard.set_in_environment(BATTERY_LEVEL, current_blackboard.get_in_environment(BATTERY_LEVEL, 30) - 2)


    #   - Simulate the response of the dusty spot sensor
    current_blackboard.set_in_environment(DUSTY_SPOT_SENSOR, random.choice([True, False, False, False, False]))
    
    #   - Simulate user input commands
    if (current_blackboard.get_in_environment(SPOT_CLEANING, False) == False and current_blackboard.get_in_environment(GENERAL_CLEANING, False) == False):
        type_of_cleaning = random.choice(["s", "g", "n"])
        if (type_of_cleaning == "s"):
            current_blackboard.set_in_environment(SPOT_CLEANING, True)
            current_blackboard.set_in_environment(GENERAL_CLEANING, False)
            print("Setting Cleaning Type to: Spot")
        elif (type_of_cleaning == "g"):
            current_blackboard.set_in_environment(SPOT_CLEANING, False)
            current_blackboard.set_in_environment(GENERAL_CLEANING, True)
            print("Setting Cleaning Type to: General")
        elif (type_of_cleaning == "n"):
            current_blackboard.set_in_environment(SPOT_CLEANING, False)
            current_blackboard.set_in_environment(GENERAL_CLEANING, False)
            print("No cleaning type specified")
    

    # Step 2: Evaluating the tree
    result = tree_root.run(current_blackboard)
    cyclesCompleted += 1

    # Step 3: Determine if your solution must terminate
    if (cyclesCompleted > 15):
        continue_condition = input("Should I Continue Cleaning? (y/n): ")
        cyclesCompleted = 0

        if (continue_condition == "n"):
            print("Ending Program. Have a nice day!")
            done = True
