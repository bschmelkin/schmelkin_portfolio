#
# Behavior Tree framework for A1 Behavior trees assignment.
# CS 131 - Artificial Intelligence
#
# version 1.0.4 - copyright (c) 2023 Santini Fabrizio. All rights reserved.
# Current Implementation: Ben Schmelkin

import bt_library as btl

class Priority(btl.Composite):

        def __init__(self, children: btl.NodeListType):
            """
            Default constructor.

            :param children: List of children for this node
            """
            super().__init__(children)

        def run(self, blackboard: btl.Blackboard) -> btl.ResultEnum:
            child_position = 0

            while child_position < len(self.children):
                child = self.children[child_position]
                result_child = child.run(blackboard)

                if result_child == btl.ResultEnum.SUCCEEDED:
                        return self.report_succeeded(blackboard, 0)

                if result_child == btl.ResultEnum.RUNNING:
                        return self.report_running(blackboard, child_position)

                child_position = child_position + 1

            return self.report_failed(blackboard, 0)
