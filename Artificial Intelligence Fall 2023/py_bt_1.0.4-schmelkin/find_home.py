#
# Behavior Tree framework for A1 Behavior trees assignment.
# CS 131 - Artificial Intelligence
#
# Version 1.0.4 - copyright (c) 2023 Santini Fabrizio. All rights reserved.
#

import bt_library as btl
from globals import HOME_PATH


class FindHome(btl.Task):
    """
    Implementation of the Task "Find Home".
    """
    def run(self, blackboard: btl.Blackboard) -> btl.ResultEnum:
        self.print_message("Looking for a home")
        blackboard.set_in_environment(HOME_PATH, "Up Left Left Up Right")
        self.print_message("Stored Home Path")

        return self.report_succeeded(blackboard)
