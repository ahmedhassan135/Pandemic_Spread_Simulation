# Pandemic_Spread_Simulation

Note: Upon recovery, a persons immunity to the virus increases. To factor that into the code, what I did was that when a person recovers the probability of infection is reduced by a factor of 4 
(probability_of_infection/4). This process causes a hindrance in the spread of the virus and causes a drop in infections over a period of time.

The zip file shows a simple 15x15 world grid with elements interacting with each other. This is for demonstration purpose because showing the real 1000x1000 grid is
not possible on the console. The symbol (W) represents offices, (0) represents empty spaces, (c<id>) represents humans who are not infected
and (i<id>) represents humans who are infected.

The script.cpp takes as input from the user on how long it takes for an infected human to beat the virus, this value may be set according to
the users needs it also takes inputs of how many offices to generate, how many working people exist and how many non working people exist.
After this the data is generated using random generator where appropriate. The data is stored in the data.txt file.

The main.cpp uses the data.txt as input for generating elements in the world. In the problem statement there was only one "subject/actor/noun", which using
convention of object oriented paradigm means it should be a class, and that was humans. The humans were divided into 2 groups working and non working which
were made into child classes inheriting from the parent human class. Since some properties of both were common in each, this method encouraged code reusage 
and avoided redundancy. The world arrat was a structure with only 2 attributes that were essential(occupied_by and isOffice), this made the array of world lighter and less 
memory intensive since the world can be huge. The total number of people infected are shown after every 10 ticks

Work Breakdown:
-> The first phase of work was to identify individual actors from the problem statement that had an essential part in the problem.

-> Then the strategy of possible solutions of how the problem could be solved was thought up and the best out of those was selected.

-> The next phase included how to make a simple visualization technique with a small manageable world and few elements. This helped debugging 
   and testing various functions, methods and code during the process of developement.
   
-> The problem was divided into different modules

-> The code was written and each time a module was completed, the module was tested and then integrated and tested again.

-> Once all the modules were completed and tested the world was then expanded to huge sizes like 1000x1000 and tested again.

-> Minor bugs and fixes were implemented.

-> Once the whole code was working, the code was optimized, e.g search algorithm was updated to Binary Search instead of Linear search which
   brought the search time complexity from O(N) to O(Log(n)) and code speedup was achieved.
   
-> Finally the code was then refactored and cleaned up to look more presentable and understandable.



