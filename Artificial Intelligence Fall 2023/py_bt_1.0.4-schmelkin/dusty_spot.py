#
# Behavior Tree framework for A1 Behavior trees assignment.
# CS 131 - Artificial Intelligence
#
# version 1.0.4 - copyright (c) 2023 Santini Fabrizio. All rights reserved.
# Current Implementation: Ben Schmelkin

import bt_library as btl
from globals import DUSTY_SPOT_SENSOR


class DustySpot(btl.Condition):
    """
    Implementation of the Condition "Dusty Spot".
    """
    def run(self, blackboard: btl.Blackboard) -> btl.ResultEnum:
        self.print_message("Receiving Input From Dusty Spot Sensor")

        if (blackboard.get_in_environment(DUSTY_SPOT_SENSOR, False) == True):
            self.print_message("Dusty Spot Found! Initiating a Spot Clean")
            return self.report_succeeded(blackboard)

        return self.report_failed(blackboard)
