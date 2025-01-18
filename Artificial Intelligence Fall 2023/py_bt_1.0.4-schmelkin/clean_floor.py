#
# Behavior Tree framework for A1 Behavior trees assignment.
# CS 131 - Artificial Intelligence
#
# version 1.0.4 - copyright (c) 2023 Santini Fabrizio. All rights reserved.
# Current Implementation: Ben Schmelkin

import bt_library as btl
import random


class CleanFloor(btl.Task):
        """
        Implementation of the Task "Clean Floor".
        """

        def run(self, blackboard: btl.Blackboard) -> btl.ResultEnum:
            probability_array = [True, True, True, True, True, True, True, True, True, True, False]

            self.print_message("Cleaning Floor")

            if (random.choice(probability_array) == False):
                self.print_message("Done Cleaning Floor")
                return self.report_failed(blackboard) 

            return self.report_succeeded(blackboard)
                        

