# Pandemic_Spread_Simulation

Note: Upon recovery, a persons immunity to the virus increases. To factor that into the code, what I did was that when a person recovers the probability of infection is reduced by a factor of 4 
(probability_of_infection/4). This process causes a hindrance in the spread of the virus and causes a drop in infections over a period of time.

The zip file shows a simple 15x15 world grid with elements interacting with each other. This is for demonstration purpose because showing the real 1000x1000 grid is
not possible on the console. The symbol (W) represents offices, (0) represents empty spaces, (c<id>) represents humans who are not infected
and (i<id>) represents humans who are infected.

The script.cpp takes as input from the user on how long it takes for an infected human to beat the virus, this value may be set according to
the users needs it also takes inputs of how many offices to generate, how many working people exist and how many non working people exist.
After this the data is generated using random generator where appropriate. The data is stored in the data.txt file.

The main.cpp uses the data.txt as input for generating elements in the world. The humans were divided into 2 groups working and non working which
were made into child classes inheriting from the parent human class. Since some properties of both were common in each, this method encouraged code reusage 
and avoided redundancy. The world array was a structure with only 2 attributes that were essential(occupied_by and isOffice), this made the array of world lighter and less 
memory intensive since the world can be huge. The total number of people infected are shown after every 10 ticks


