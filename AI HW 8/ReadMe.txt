HOW TO RUN:
This is a maven project so ensure that you have maven and jdk 1.8 installed on your
machine. 
From there move in the AI_HW_8 directory.
Compile:
mvn compile
Execute: 
mvn exec:java -Dexec.mainClass=Main

Format of input document. 
Title your document:
mdp_input.txt
Place it in the following folder:
/AI_HW_8/src/main/resources

There is one already there for your convienance. 

The format is the same as the format given to us originally from the TA.
Use snake case to specify all of your parameters etc. 
The order of variables should not matter as long as they are all there 
Seperate lists with commas 
All "#" at beggining of lines will be seen as comments and will not be parsed. 

Expected format example:
#size of the gridworld

size : 5 4

#list of location of walls

walls : 2 2 , 2 3

#list of terminal states (row,column,reward)

terminal_states : 5 3 -3 , 5 4 +2, 4 2 +1

#reward in non-terminal states

reward : -0.04

#transition probabilites

transition_probabilities : 0.8 0.1 0.1 0

discount_rate : 0.85

epsilon : 0.001 
