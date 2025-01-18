#
# Behavior Tree framework for A1 Behavior trees assignment.
# CS 131 - Artificial Intelligence
#
# version 1.0.4 - copyright (c) 2023 Santini Fabrizio. All rights reserved.
# Current Implementation: Ben Schmelkin

import bt_library as btl
from globals import IS_CHARGING, BATTERY_LEVEL


class Dock(btl.Task):
    """
    Implementation of the Task "Dock".
    """
    def run(self, blackboard: btl.Blackboard) -> btl.ResultEnum:
        blackboard.get_in_environment(IS_CHARGING, True)
        if (blackboard.get_in_environment(BATTERY_LEVEL, 0) < 100):
            self.print_message("Currently Docked, Charging Battery ...")
            return self.report_running(blackboard)

        self.print_message("Finished! Leaving Home")
        return self.report_succeeded(blackboard)