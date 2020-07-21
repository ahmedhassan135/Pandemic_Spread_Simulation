#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <conio.h>
#include <ctime>
using namespace std;


struct Cell
{
    int occupied_by_id; //ID of human that occupies it if any
    bool isOffice;
};

struct Coordinates
{
    int x;
    int y;
};

#define rows 1000
#define cols 1000

Cell world[rows][cols];
int disease_duration = 0;


class Human
{
    public:
    int ID;
    Coordinates current_location;
    bool infected;
    float probability_of_infection;
    int infectionTimerCountdown;


    int GetHumanID() { return ID; }

    void DecrementInfectionTimerCountdown()
    {
        if (infectionTimerCountdown == 1 || infectionTimerCountdown == 0)
        {
            infectionTimerCountdown = 0;
            infected = false;

            probability_of_infection = probability_of_infection / 4;            //immunity increases after recovery so probability decreases by 4
        }
        else
            infectionTimerCountdown--;
    }

    void CatchesInfection()
    {
        infected = true;
        infectionTimerCountdown = disease_duration;
    }

};

class Working : public Human
{
    public:
    Coordinates house_address;
    Coordinates office_address;
    int travelling;
    int ticks_stuck;

    Working()
    {
        travelling = 0;                         //Travelling to office at start
        ticks_stuck = 0;
    }


    void SetCurrentLocation(int New_location_x, int New_location_y)
    {
        if(world[New_location_y][New_location_x].occupied_by_id != 0)
            cout<<"\nERROR: Location ("<<New_location_x<<","<<New_location_y<<") "<<"already occupied, cannot set new location for: "<<ID<<endl;
        else
        {
            world[current_location.y][current_location.x].occupied_by_id = 0;
            current_location.x = New_location_x;
            current_location.y = New_location_y;
            world[New_location_y][New_location_x].occupied_by_id = ID;
        }

    }

    void initialize_variables(int id, int Current_location_x, int Current_location_y, bool Infected, float Probability_of_infection, int Office_address_x, int Office_address_y)
    {
        ID = id;
        SetCurrentLocation(Current_location_x, Current_location_y);
        probability_of_infection = Probability_of_infection;

        house_address.x = Current_location_x;       //Starting location is house location initially
        house_address.y = Current_location_y;
        office_address.x = Office_address_x;
        office_address.y = Office_address_y;

        world[current_location.y][current_location.x].occupied_by_id = ID;

        if (Infected)
        {
            CatchesInfection();
            //infectionTimerCountdown = 8;
        }
        else
            infectionTimerCountdown = 0;


    }

    Coordinates GetCurrentLocation() { return current_location; }

    Coordinates GetHouseAddress() { return house_address; }

    Coordinates GetOfficeAddress() { return office_address; }



    void SetHouseAddress(int New_house_address_x, int New_house_address_y)
    {
        house_address.x = New_house_address_x;
        house_address.y = New_house_address_y;
    }


    void SetOfficeAddress(int New_Office_address_x, int New_Office_address_y)
    {
        office_address.x = New_Office_address_x;
        office_address.y = New_Office_address_y;
    }

    void IncrementTickStuck() { ticks_stuck++; }

    void resetTicksStuck() { ticks_stuck = 0; }




};

class NotWorking : public Human
{
    public:
    void initialize_variables(int id, int Current_location_x, int Current_location_y, bool Infected, float Probability_of_infection)
    {
        ID = id;
        current_location.x = Current_location_x;
        current_location.y = Current_location_y;
        infected = Infected;
        probability_of_infection = Probability_of_infection;


        world[current_location.y][current_location.x].occupied_by_id = ID;

        if (Infected)
        {
            CatchesInfection();
            //infectionTimerCountdown = 8;
        }
        else
            infectionTimerCountdown = 0;
    }

    Coordinates GetCurrentLocation() { return current_location; }



};

int office_count = 0;
int working_count = 0;
int not_working_count = 0;
Working h1[250000];          //Humans Declaration
NotWorking h2[250000];


void initialize()
{
    for (int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            world[i][j].occupied_by_id = 0;
            world[i][j].isOffice = false;
        }
    }



    ifstream file("data.txt");
    if(file.eof())
        return;

    file>>disease_duration;
    file>>office_count;
    file>>working_count;
    file>>not_working_count;

    for (int i = 0; i < office_count; i++ )
    {
        int x,y;

        file>>y;
        file>>x;
        world[y][x].isOffice = true;

    }

    for (int i = 1; i <= working_count; i++ )
    {
        int id, x, y, officex, officey;
        bool infected;
        float probability_infection;

        file>>id;
        file>>x;
        file>>y;
        file>>infected;
        file>>probability_infection;
        file>>officex;
        file>>officey;

        //cout<<id<<"\t"<< x<<"\t"<<  y<<"\t"<<  infected<<"\t"<<  probability_infection<<"\t"<<  officex<<"\t"<<  officey<<endl;
        //system("pause");

        h1[i].initialize_variables(id, x, y, infected, probability_infection, officex, officey);


    }


    for (int i = 1; i <= not_working_count; i++ )
    {
        int id, x, y;
        bool infected;
        float probability_infection;

        file>>id;
        file>>x;
        file>>y;
        file>>infected;
        file>>probability_infection;

        //cout<<id<<"\t"<< x<<"\t"<<  y<<"\t"<<  infected<<"\t"<<  probability_infection<<"\t"<<  officex<<"\t"<<  officey<<endl;
        //system("pause");

        h2[i].initialize_variables(id, x, y, infected, probability_infection);


    }

}

Human findHumanByID(int id)
{
    /*if (id <= working_count)
        return h1[id];
    else if (id > working_count)
        return h2[id - working_count];
    */



    //Binary search implementation, should the order of id's change, Use this approach.
    int l = 1;
    int r = working_count;


    while (l <= r)
    {
        int m = l + (r - l) / 2;

        if (h1[m].GetHumanID() == id)
            return h1[m];

        if (h1[m].GetHumanID() < id)
            l = m + 1;

        else
            r = m - 1;
    }

    l = 1;
    r = not_working_count;


    while (l <= r)
    {
        int m = l + (r - l) / 2;

        if (h2[m].GetHumanID() == id)
            return h2[m];

        if (h2[m].GetHumanID() < id)
            l = m + 1;

        else
            r = m - 1;
    }


    //Linear Search method. (Slowest)
    /*for (int i = 1 ; i <= working_count; i++)
    {
        if (h1[i].GetHumanID() == id)
            return h1[i];
    }

    for (int i = 1 ; i <= not_working_count; i++)
    {
        if (h2[i].GetHumanID() == id)
            return h2[i];
    }*/



}

int CountNumberInfected()
{
    int Total_infected_count = 0;
    for (int i = 1 ; i <= working_count ; i++)
    {
        if (h1[i].infected)
        {
            Total_infected_count++;
        }

    }

    for (int i = 1 ; i <= not_working_count ; i++)
    {
        if (h2[i].infected)
        {
            Total_infected_count++;
        }

    }
    return Total_infected_count;

}

void display_world()
{

    for (int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            if (!world[i][j].isOffice)
            {
                if (world[i][j].occupied_by_id != 0)
                {
                    if (findHumanByID(world[i][j].occupied_by_id).infected)
                        cout<<"i"<<world[i][j].occupied_by_id<<"\t";                //Denote infected as 'i' followed by ID
                    else
                        cout<<"c"<<world[i][j].occupied_by_id<<"\t";                //Denote clear/not infected as 'c' followed by ID
                }
                else
                    cout<<world[i][j].occupied_by_id<<"\t";                         //Denote empty spaces as '0' or simply what occupies them which is 0

            }
            else
                cout<<"W"<<"\t";
        }
        cout<<endl<<endl;
    }



    cout<<"Total infected people: " << CountNumberInfected()<<endl<<endl;


}



void MoveToHouse(Working &h1);

//movement of a human
bool CheckIfNextBlockEmpty(Working &h1, int next_x, int next_y)      //returns false if next space is occupied else true if empty
{
    if (world[next_y][next_x].occupied_by_id == 0 && world[next_y][next_x].isOffice == false)
    {
        return true;
    }
    else
    {
        if (world[next_y][next_x].occupied_by_id != 0)      //increment ticks stuck
        {
            h1.IncrementTickStuck();
            return false;
        }
        else if (h1.GetOfficeAddress().x == next_x && h1.GetOfficeAddress().y == next_y)
        {
            h1.travelling = 1;
            MoveToHouse(h1);
            return false;
        }
        else if (world[next_y][next_x].isOffice == true)                //If some other work office comes in the way of traveling human
        {
            //If obstruction is in the next x cell.
            if (h1.GetCurrentLocation().x != next_x && world[h1.GetCurrentLocation().y + 1][h1.GetCurrentLocation().x].occupied_by_id == 0 && h1.GetCurrentLocation().y + 1 < rows && world[h1.GetCurrentLocation().y + 1][h1.GetCurrentLocation().x].isOffice == false)
                h1.SetCurrentLocation(h1.GetCurrentLocation().x, h1.GetCurrentLocation().y + 1);
            else if (h1.GetCurrentLocation().x != next_x && world[h1.GetCurrentLocation().y - 1][h1.GetCurrentLocation().x].occupied_by_id == 0 && h1.GetCurrentLocation().y - 1 >= 0 &&world[h1.GetCurrentLocation().y - 1][h1.GetCurrentLocation().x].isOffice == false)
                h1.SetCurrentLocation(h1.GetCurrentLocation().x, h1.GetCurrentLocation().y - 1);

            //If obstruction is in the next y cell.     skip 1 y and check if the work is one skip away as well
            else if (h1.GetCurrentLocation().y != next_y && world[h1.GetCurrentLocation().y + 2][h1.GetCurrentLocation().x].occupied_by_id == 0 && h1.GetCurrentLocation().y + 2 < rows)
                h1.SetCurrentLocation(h1.GetCurrentLocation().x, h1.GetCurrentLocation().y + 2);


            return false;
        }
    }

}

void MoveHuman(Working &h1, int next_x, int next_y)
{
    //empty previous cell in the world
    world[h1.GetCurrentLocation().y][h1.GetCurrentLocation().x].occupied_by_id = 0;

    //move human
    h1.SetCurrentLocation(next_x, next_y);



}

void MoveToWork(Working &h1)
{
    //First move in the x axis
    if (h1.GetCurrentLocation().x < h1.GetOfficeAddress().x)
    {
        //Check if next space empty
        if (CheckIfNextBlockEmpty(h1, h1.GetCurrentLocation().x + 1, h1.GetCurrentLocation().y))
        {
            //Move to next location
            MoveHuman(h1, h1.GetCurrentLocation().x + 1, h1.GetCurrentLocation().y);
        }
    }
    else if (h1.GetCurrentLocation().x > h1.GetOfficeAddress().x)
    {
        //Check if next space empty
        if (CheckIfNextBlockEmpty(h1, h1.GetCurrentLocation().x - 1, h1.GetCurrentLocation().y))
        {
            //Move to next location
            MoveHuman(h1, h1.GetCurrentLocation().x - 1, h1.GetCurrentLocation().y);
        }
    }

    //Second move in the y axis when x = 0
    else if (h1.GetCurrentLocation().x == h1.GetOfficeAddress().x && h1.GetCurrentLocation().y != h1.GetOfficeAddress().y)
    {
        if (h1.GetCurrentLocation().y < h1.GetOfficeAddress().y)
        {
            //Check if next space empty
            if (CheckIfNextBlockEmpty(h1, h1.GetCurrentLocation().x, h1.GetCurrentLocation().y + 1))
            {
                //Move to next location
                MoveHuman(h1, h1.GetCurrentLocation().x, h1.GetCurrentLocation().y + 1);
            }
        }
        else if (h1.GetCurrentLocation().y > h1.GetOfficeAddress().y)
        {
            //Check if next space empty
            if (CheckIfNextBlockEmpty(h1, h1.GetCurrentLocation().x, h1.GetCurrentLocation().y - 1))
            {
                //Move to next location
                MoveHuman(h1, h1.GetCurrentLocation().x, h1.GetCurrentLocation().y -1 );
            }
        }
    }
    else if (h1.GetCurrentLocation().x == h1.GetOfficeAddress().x && h1.GetCurrentLocation().y == h1.GetOfficeAddress().y)
        h1.travelling = 1;

}

void MoveToHouse(Working &h1)
{
    //First move in the x axis
    if (h1.GetCurrentLocation().x < h1.GetHouseAddress().x)
    {
        //Check if next space empty
        if (CheckIfNextBlockEmpty(h1, h1.GetCurrentLocation().x + 1, h1.GetCurrentLocation().y))
        {
            //Move to next location
            MoveHuman(h1, h1.GetCurrentLocation().x + 1, h1.GetCurrentLocation().y);
        }
    }
    else if (h1.GetCurrentLocation().x >  h1.GetHouseAddress().x)
    {
        //Check if next space empty
        if (CheckIfNextBlockEmpty(h1, h1.GetCurrentLocation().x - 1, h1.GetCurrentLocation().y))
        {
            //Move to next location
            MoveHuman(h1, h1.GetCurrentLocation().x - 1, h1.GetCurrentLocation().y);
        }
    }

    //Second move in the y axis when x = 0
    else if (h1.GetCurrentLocation().x ==  h1.GetHouseAddress().x)
    {
        if (h1.GetCurrentLocation().y <  h1.GetHouseAddress().y)
        {
            //Check if next space empty
            if (CheckIfNextBlockEmpty(h1, h1.GetCurrentLocation().x, h1.GetCurrentLocation().y + 1))
            {
                //Move to next location
                MoveHuman(h1, h1.GetCurrentLocation().x, h1.GetCurrentLocation().y + 1);
            }
        }
        else if (h1.GetCurrentLocation().y >  h1.GetHouseAddress().y)
        {
            //Check if next space empty
            if (CheckIfNextBlockEmpty(h1, h1.GetCurrentLocation().x, h1.GetCurrentLocation().y - 1))
            {
                //Move to next location
                MoveHuman(h1, h1.GetCurrentLocation().x, h1.GetCurrentLocation().y -1 );
            }
        }
    }

    if (h1.GetCurrentLocation().x == h1.GetHouseAddress().x && h1.GetCurrentLocation().y == h1.GetHouseAddress().y)     //Upon reaching home start going back to office
        h1.travelling = 0;

}


bool outOfBounds(int y, int x)
{
    if (y > 0 && x > 0 && y < rows && x < cols)
        return false;
    else
        return true;

}

void MoveToAnyFreeSpace(Working &h1, int x, int y)
{
    if (world[y-1][x-1].occupied_by_id == 0 && world[y-1][x-1].isOffice != true && outOfBounds(y-1, x-1) == false)
        h1.SetCurrentLocation(x-1,y-1);
    else if (world[y-1][x].occupied_by_id == 0 && world[y-1][x].isOffice != true && outOfBounds(y-1, x) == false)
        h1.SetCurrentLocation(x,y-1);
    else if (world[y-1][x+1].occupied_by_id == 0 && world[y-1][x+1].isOffice != true && outOfBounds(y-1, x+1) == false)
        h1.SetCurrentLocation(x+1,y-1);
    else if (world[y][x-1].occupied_by_id == 0 && world[y][x-1].isOffice != true && outOfBounds(y, x-1) == false)
        h1.SetCurrentLocation(x-1,y);
    else if (world[y][x].occupied_by_id == 0 && world[y][x].isOffice != true && outOfBounds(y, x) == false)
        h1.SetCurrentLocation(x,y);
    else if (world[y][x+1].occupied_by_id == 0 && world[y][x+1].isOffice != true && outOfBounds(y, x+1) == false)
        h1.SetCurrentLocation(x+1,y);
    else if (world[y+1][x-1].occupied_by_id == 0 && world[y+1][x-1].isOffice != true && outOfBounds(y+1, x-1) == false)
        h1.SetCurrentLocation(x-1,y+1);
    else if (world[y+1][x].occupied_by_id == 0 && world[y+1][x].isOffice != true && outOfBounds(y+1, x) == false)
        h1.SetCurrentLocation(x,y+1);
    else if (world[y+1][x+1].occupied_by_id == 0 && world[y+1][x+1].isOffice != true && outOfBounds(y+1, x+1) == false)
        h1.SetCurrentLocation(x+1,y+1);

    h1.resetTicksStuck();

}

void MakeMove(Working &h1)
{
    if (h1.ticks_stuck > 8)
        MoveToAnyFreeSpace(h1, h1.GetCurrentLocation().x, h1.GetCurrentLocation().y);
    //Go to work
    else if (h1.travelling == 0)
        MoveToWork(h1);
    else
        MoveToHouse(h1);
    //Go back home





}


bool SearchNeighborhood(int x, int y)       //checks neighborhood for infected humans  return true if any neighbor has disease
{


    if (world[y-1][x-1].occupied_by_id != 0 && findHumanByID(world[y-1][x-1].occupied_by_id).infected == true)
        return true;
    else if (world[y-1][x].occupied_by_id != 0 && findHumanByID(world[y-1][x].occupied_by_id).infected == true)
        return true;
    else if (world[y-1][x+1].occupied_by_id != 0 && findHumanByID(world[y-1][x+1].occupied_by_id).infected == true)
        return true;
    else if (world[y][x-1].occupied_by_id != 0 && findHumanByID(world[y][x-1].occupied_by_id).infected == true)
        return true;
    else if (world[y][x].occupied_by_id != 0 && findHumanByID(world[y][x].occupied_by_id).infected == true)
        return true;
    else if (world[y][x+1].occupied_by_id != 0 && findHumanByID(world[y][x+1].occupied_by_id).infected == true)
        return true;
    else if (world[y+1][x-1].occupied_by_id != 0 && findHumanByID(world[y+1][x-1].occupied_by_id).infected == true)
        return true;
    else if (world[y+1][x].occupied_by_id != 0 && findHumanByID(world[y+1][x].occupied_by_id).infected == true)
        return true;
    else if (world[y+1][x+1].occupied_by_id != 0 && findHumanByID(world[y+1][x+1].occupied_by_id).infected == true)
        return true;

    return false;
}


//contact and probability of infection
bool isInfected(float probability)      //returns true if human contracts disease, false if human does not.
{

    /*Probability (p) is calculated to the
      nearest 3 decimal places. So by multiplying
      with 1000 the decimal is removed. For example
      0.250 becomes 250. Then a random number from
      1<n<1000 is generated the the random number (rn) lies
      in the range of 1<rn<p then subject is infected. Else
      if random number > p i.e 250 in this case, then subject
      is not infected. This works because the
      numbers generated are of a uniform distribution so
      1<n<250 has a probability of 0.250 and 251<n<1000 has
      a probability of 1-p i.e 0.750 in this case.
    */

    int RandomNumber = 1 + (rand() % 1000);
    //cout<<"Random number generated is: "<< RandomNumber<<endl;
    probability = probability * 1000;
    if (probability >= RandomNumber)
        return true;
    else
        return false;
}

//Check and see if any neighbors have virus and uses a probabilistic model to predict if human catches virus
void CheckAndEvaluateNeighborhood()
{
    for (int i = 1 ; i <= working_count; i++)
    {
        if (!h1[i].infected)
        {
           // cout<<"All possible Neighbours : "<< h1[i].current_location.x<<" "<< h1[i].current_location.y<<"    "<<SearchNeighborhood(h1[i].current_location.x, h1[i].current_location.y)<<endl;
           if (SearchNeighborhood(h1[i].current_location.x, h1[i].current_location.y))
            {
                if(isInfected(h1[i].probability_of_infection))              //call isInfected function if neighborhood human has disease
                {
                    //cout<<"\nInfection caught: "<<h1[i].GetHumanID()<<endl;
                    h1[i].CatchesInfection();
                    //h1[i].infected = true;
                }
            }
        }


    }

    for (int i = 1 ; i <= not_working_count; i++)
    {
        if (!h2[i].infected)
        {
            //cout<<"All possible Neighbours : "<< h2[i].current_location.x<<" "<< h2[i].current_location.y<<"    "<<SearchNeighborhood(h2[i].current_location.x, h1[i].current_location.y)<<endl;
            if (SearchNeighborhood(h2[i].current_location.x, h2[i].current_location.y))
            {
                if(isInfected(h2[i].probability_of_infection))              //call isInfected function if neighborhood human has disease
                {
                    //cout<<"\nInfection caught: "<<h2[i].GetHumanID()<<endl;
                    h2[i].CatchesInfection();
                    //h2[i].infected = true;
                }
            }
        }

    }
}

void UpdateInfectionTimers()
{
    for (int i = 1 ; i <= working_count; i++)
    {
        if (h1[i].infected)
        {
           h1[i].DecrementInfectionTimerCountdown();
        }


    }

    for (int i = 1 ; i <= not_working_count; i++)
    {
        if (h2[i].infected)
        {
            h2[i].DecrementInfectionTimerCountdown();
        }

    }

}


void tick()
{
    for (int i = 1 ; i <= working_count; i++)
    {
           MakeMove(h1[i]);
    }
}


int main()
{
    srand((unsigned) time(0));

    initialize();
    cout<<"Initialization complete\n\n";
    //display_world();



    //system("pause");

    int k = 0;

    while(k < 1000)
    {
        system("cls");

        CheckAndEvaluateNeighborhood();             //check neighborhood for infected people

        UpdateInfectionTimers();

        //display_world();

        tick();
        //system("pause");

        if (k%10 == 0)
        {
            cout<<"Total infected people: " << CountNumberInfected()<<endl<<endl;
            system("pause");
        }

        k++;


    }

    return 0;
}
















