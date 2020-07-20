#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
using namespace std;


struct Coordinates
{
    int x;
    int y;
} ;

#define rows 1000
#define cols 1000

int world[rows][cols];


void initializeGenerator()
{
    for (int i = 0 ; i < rows; i++)
    {
        for (int j = 0 ; i <cols; j++)
        {
            world[i][j] = 0;
        }
    }

}


int main () {

  srand((unsigned) time(0));

  ofstream myfile;
  myfile.open ("data.txt");


  int office_count, working_human_count, non_working_human_count, disease_duration;

  cout<<"Please Enter the average disease duration in humans--> ";
  cin>> disease_duration;

  cout<<"Please Enter the number of offices you want to create--> ";
  cin>> office_count;

  cout<<"Please Enter the number of working humans you want to create--> ";
  cin>> working_human_count;

  cout<<"Please Enter the number of non-working humans you want to create--> ";
  cin>> non_working_human_count;



  if (office_count + working_human_count + non_working_human_count >= rows * cols)
  {
      cout<<"ERROR: Elements entered more than total space available\nEXITING\n";
      return 0;
  }

  myfile << disease_duration << "\n";
  myfile << office_count <<"\n";
  myfile << working_human_count <<"\n";
  myfile << non_working_human_count <<"\n";


  Coordinates offices[office_count];

  for (int i = 0 ; i < office_count; i++)
  {
        Coordinates Randomc;
        Randomc.x = (rand() % rows);
        Randomc.y = (rand() % cols);

        if (world[Randomc.y][Randomc.x] != -1)
        {
          world[Randomc.y][Randomc.x] = -1;
          offices[i].x = Randomc.x;
          offices[i].y = Randomc.y;
          myfile<< Randomc.y << "\t" << Randomc.x<<"\n";
        }
        else
        {
            i--;
        }
  }

  for (int i = 1 ; i <= working_human_count; i++)
  {
        Coordinates Randomc;
        Randomc.x = (rand() % rows);
        Randomc.y = (rand() % cols);

        if (world[Randomc.y][Randomc.x] == 0)
        {
          world[Randomc.y][Randomc.x] = i;

          int id = i;

          int infected = (rand() % 2);

          float Probability_of_infection = (float) (rand() % 1000)/1000;

          int index = (rand() % office_count);

          int officex = offices[index].x;
          int officey = offices[index].y;


          myfile<< id <<"\t" << Randomc.x << "\t" << Randomc.y << "\t" << infected << "\t" << Probability_of_infection<<"\t"<< officex << "\t" << officey <<"\n";
        }
        else
        {
            i--;
        }
  }

  for (int i = 1 ; i <= non_working_human_count; i++)
  {
        Coordinates Randomc;
        Randomc.x = (rand() % rows);
        Randomc.y = (rand() % cols);

        if (world[Randomc.y][Randomc.x] == 0)
        {
          world[Randomc.y][Randomc.x] = working_human_count + i;

          int id = working_human_count + i;
          int infected = (rand() % 2);

          float Probability_of_infection =  (float) (rand() % 1000)/1000;



          myfile<< id <<"\t" << Randomc.x << "\t" << Randomc.y << "\t" << infected <<" \t" << Probability_of_infection<<"\n";
        }
        else
        {
            i--;
        }
  }





  myfile.close();
  return 0;
}


















