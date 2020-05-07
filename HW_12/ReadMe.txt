This is a python3 Program. You must have python 3 installed to run.

The program looks for training data in the TrainingData directory. So please place your csv file for training there.

The program then takes in one command line argument with the Training Data file name.

Instruction to Run:
    1. Move into program directory
    2. Optional: Place new training data in training data directory
    3. Run Program:
        python3 RestaurantDecisionTreeBuilder.py Restaurant.csv

Sample output:

** COMPUTE AND PRINT TREE **
****************************

`- pat
   |- Some
   |  `- YES
   |- Full
   |  `- hun
   |     |- Yes
   |     |  `- type
   |     |     |- Thai
   |     |     |  `- fri
   |     |     |     |- No
   |     |     |     |  `- NO
   |     |     |     `- Yes
   |     |     |        `- YES
   |     |     |- Italian
   |     |     |  `- NO
   |     |     |- Burger
   |     |     |  `- YES
   |     |     `- French
   |     |        `- YES
   |     `- No
   |        `- NO
   `- None
      `- NO