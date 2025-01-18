#
# Behavior Tree framework for A1 Behavior trees assignment.
# CS 131 - Artificial Intelligence
#
# version 1.0.4 - copyright (c) 2023 Santini Fabrizio. All rights reserved.
# Current Implementation: Ben Schmelkin

import bt_library as btl
from globals import SPOT_CLEANING


class Spot(btl.Condition):
    """
    Implementation of the Condition "Spot".
    """
    def run(self, blackboard: btl.Blackboard) -> btl.ResultEnum:
        self.print_message("Checking If I Should Spot Clean")

        if (blackboard.get_in_environment(SPOT_CLEANING, False) == True):
                self.print_message("Initiating A Spot Clean")
                return self.report_succeeded(blackboard)

        return self.report_failed(blackboard)
