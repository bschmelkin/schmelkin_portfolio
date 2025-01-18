#
# Behavior Tree framework for A1 Behavior trees assignment.
# CS 131 - Artificial Intelligence
#
# version 1.0.4 - copyright (c) 2023 Santini Fabrizio. All rights reserved.
# Current Implementation: Ben Schmelkin

import bt_library as btl


class DoNothing(btl.Task):
        """
        Implementation of the Task "Do Nothing".
        """

        def run(self, blackboard: btl.Blackboard) -> btl.ResultEnum:
            self.print_message("Initiating Do Nothing")

            return self.report_succeeded(blackboard)
