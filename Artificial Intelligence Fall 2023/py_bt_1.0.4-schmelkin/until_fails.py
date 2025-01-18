#
# Behavior Tree framework for A1 Behavior trees assignment.
# CS 131 - Artificial Intelligence
#
# version 1.0.4 - copyright (c) 2023 Santini Fabrizio. All rights reserved.
# Current Implementation: Ben Schmelkin

import bt_library as btl


class UntilFails(btl.Decorator):
    """
    Specific implementation of the Until Fails decorator.
    """

    def __init__(self, child: btl.TreeNode):
        """
        Default constructor.

        :param child: Child associated to the decorator
        """
        super().__init__(child)

    def run(self, blackboard: btl.Blackboard) -> btl.ResultEnum:
        """
        Execute the behavior of the node.

        :param blackboard: Blackboard with the current state of the problem
        :return: The result of the execution
        """
        result_child = self.child.run(blackboard)
        
        if (result_child == btl.ResultEnum.FAILED):
                return self.report_succeeded(blackboard)
        return self.report_running(blackboard)
        