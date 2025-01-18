#
# Behavior Tree framework for A1 Behavior trees assignment.
# CS 131 - Artificial Intelligence
#
# version 1.0.4 - copyright (c) 2023 Santini Fabrizio. All rights reserved.
# Current Implementation: Ben Schmelkin

import bt_library as btl
from globals import GENERAL_CLEANING


class GeneralCleaning(btl.Condition):
    """
    Implementation of the Condition "General Cleaning".
    """
    def run(self, blackboard: btl.Blackboard) -> btl.ResultEnum:
        self.print_message("Checking If I Should General Clean")

        if (blackboard.get_in_environment(GENERAL_CLEANING, False) == True):
                self.print_message("Initiating A General Clean")
                return self.report_succeeded(blackboard)
        return self.report_failed(blackboard)