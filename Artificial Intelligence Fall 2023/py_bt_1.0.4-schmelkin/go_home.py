#
# Behavior Tree framework for A1 Behavior trees assignment.
# CS 131 - Artificial Intelligence
#
# version 1.0.4 - copyright (c) 2023 Santini Fabrizio. All rights reserved.
# Current Implementation: Ben Schmelkin

import bt_library as btl
import random
from globals import HOME_PATH, IS_HOME


class GoHome(btl.Task):
    """
    Implementation of the Task "Go Home".
    """
    def run(self, blackboard: btl.Blackboard) -> btl.ResultEnum:
        self.print_message("Going Home - Path = " +  blackboard.get_in_environment(HOME_PATH, ""))
        probability_array = [True, False]

        self.print_message("Cleaning Floor")

        if (random.choice(probability_array) == False):
            self.print_message("Making My Way Home")
            return self.report_running(blackboard)

        self.print_message("I'm Home")
        blackboard.set_in_environment(IS_HOME, True)
        return self.report_succeeded(blackboard)
        