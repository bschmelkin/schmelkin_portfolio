#
# Behavior Tree framework for A1 Behavior trees assignment.
# CS 131 - Artificial Intelligence
#
# version 1.0.4 - copyright (c) 2023 Santini Fabrizio. All rights reserved.
# Current Implementation: Ben Schmelkin

import bt_library as btl

from battery_less_than_30 import BatteryLessThan30
from find_home import FindHome
from globals import BATTERY_LEVEL, GENERAL_CLEANING, SPOT_CLEANING, DUSTY_SPOT_SENSOR, HOME_PATH, IS_CHARGING, IS_HOME
from sequence import Sequence
from priority import Priority
from go_home import GoHome
from dock import Dock
from spot import Spot
from clean_spot import CleanSpot
from done_spot import DoneSpot
from general_cleaning import GeneralCleaning
from dusty_spot import DustySpot
from until_fails import UntilFails
from clean_floor import CleanFloor
from done_general import DoneGeneral
from do_nothing import DoNothing

# Instantiate the tree according to the assignment.

########################################################################################################################

tree_root = Priority(
    [
        Sequence(
            [
                BatteryLessThan30(),
                FindHome(),
                GoHome(),
                Dock()
            ]
        ),
        btl.Selection(
            [
                Sequence(
                        [
                            Spot(),
                            btl.Timer(20, CleanSpot()),
                            DoneSpot()
                        ]     
                ),
                Sequence(
                    [
                        GeneralCleaning(),
                        Sequence(
                            [
                                Priority(
                                    [
                                        Sequence(
                                            [
                                                DustySpot(),
                                                btl.Timer(35, CleanSpot())
                                            ]
                                        ),
                                        UntilFails(CleanFloor())
                                    ]
                                ), 
                                DoneGeneral()
                            ]
                        )
                    ]
                )
            ]    
        ),
        DoNothing()
    ]
)
 