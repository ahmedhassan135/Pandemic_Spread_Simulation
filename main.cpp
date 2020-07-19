#include <iostream>
#include <cstring>
#include <cstdlib>
#include <conio.h>
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


class Human
{
    public:
    int ID;
    Coordinates current_location;
    bool infected;
    float probability_of_infection;


    int GetHumanID() { return ID; }

};

class Working : public Human
{
    public:
    Coordinates house_address;
    Coordinates office_address;
    int travelling;
    int ticks_stuck;

    void initialize_variables(int id, int Current_location_x, int Current_location_y, bool Infected, float Probability_of_infection, int Office_address_x, int Office_address_y)
    {
        ID = id;
        current_location.x = Current_location_x;
        current_location.y = Current_location_y;
        infected = Infected;
        probability_of_infection = Probability_of_infection;

        house_address.x = Current_location_x;       //Starting location is house location initially
        house_address.y = Current_location_y;
        office_address.x = Office_address_x;
        office_address.y = Office_address_y;
        travelling = 0;                         //Travelling to office at start
        ticks_stuck = 0;


    }

    Coordinates GetCurrentLocation() { return current_location; }

    Coordinates GetHouseAddress() { return house_address; }

    Coordinates GetOfficeAddress() { return office_address; }

    void SetCurrentLocation(int New_location_x, int New_location_y)
    {
        current_location.x = New_location_x;
        current_location.y = New_location_y;
    }

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




};

class NotWorking : public Human
{
    void initialize_variables(int id, int Current_location_x, int Current_location_y, bool Infected, float Probability_of_infection, int House_address_x, int House_address_y, int Office_address_x, int Office_address_y)
    {
        ID = id;
        current_location.x = Current_location_x;
        current_location.y = Current_location_y;
        infected = Infected;
        probability_of_infection = Probability_of_infection;
    }

    Coordinates GetCurrentLocation() { return current_location; }

};


#define rows 6
#define cols 6

Cell world[rows][cols];
Working h1[2];


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

    //Get office locations from file
    //Get humans from file
    //Place the humans in an array
    //Place each on the world grid


    world[2][3].occupied_by_id = 34;    //Consider putting this in human initialization function
    world[4][4].isOffice = true;        //Consider putting this in human initialization function


    h1[0].initialize_variables(34, 3, 2, false, 0.2, 4, 4 );

}


void display_world()
{

    for (int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            if (!world[i][j].isOffice)
                cout<<world[i][j].occupied_by_id<<"\t";
            else
                cout<<"W"<<"\t";
        }
        cout<<endl<<endl;
    }
}


//TODO: contact and probability of infection
//TODO: movement of a human

bool CheckIfNextBlockEmpty(int next_x, int next_y)      //returns false if next space is occupied else true if empty
{
    if (world[next_y][next_x].occupied_by_id == 0 && world[next_y][next_x].isOffice == false)
        return true;
    else
        return false;
}

void MoveHuman(Working &h1, int next_x, int next_y)
{
    //empty previous cell in the world
    world[h1.GetCurrentLocation().y][h1.GetCurrentLocation().x].occupied_by_id = 0;

    //move human
    h1.SetCurrentLocation(next_x, next_y);
    world[next_y][next_x].occupied_by_id = h1.GetHumanID();



}

void MakeMove(Working &h1)
{
    //First move in the x axis
    if (h1.GetCurrentLocation().x < h1.GetOfficeAddress().x)
    {
        //Check if next space empty
        if (CheckIfNextBlockEmpty(h1.GetCurrentLocation().x + 1, h1.GetCurrentLocation().y))
        {
            //Move to next location
            MoveHuman(h1, h1.GetCurrentLocation().x + 1, h1.GetCurrentLocation().y);
        }
    }
    else if (h1.GetCurrentLocation().x > h1.GetOfficeAddress().x)
    {
        //Check if next space empty
        if (CheckIfNextBlockEmpty(h1.GetCurrentLocation().x - 1, h1.GetCurrentLocation().y))
        {
            //Move to next location
            MoveHuman(h1, h1.GetCurrentLocation().x - 1, h1.GetCurrentLocation().y);
        }
    }
    else if (h1.GetCurrentLocation().x == h1.GetOfficeAddress().x)
    {
        if (h1.GetCurrentLocation().y < h1.GetOfficeAddress().y)
        {
            //Check if next space empty
            if (CheckIfNextBlockEmpty(h1.GetCurrentLocation().x, h1.GetCurrentLocation().y + 1))
            {
                //Move to next location
                MoveHuman(h1, h1.GetCurrentLocation().x, h1.GetCurrentLocation().y + 1);
            }
        }
        else if (h1.GetCurrentLocation().y > h1.GetOfficeAddress().y)
        {
            //Check if next space empty
            if (CheckIfNextBlockEmpty(h1.GetCurrentLocation().x, h1.GetCurrentLocation().y - 1))
            {
                //Move to next location
                MoveHuman(h1, h1.GetCurrentLocation().x, h1.GetCurrentLocation().y -1 );
            }
        }
    }



    //Second move in the y axis when x = 0
}

//TODO: Display number of people currently infected and recovered.



int main()
{
    initialize();

    while(true)
    {
        system("cls");
        display_world();
        MakeMove(h1[0]);
        //cout<<"\nLocation is "<< h1[0].GetCurrentLocation().x << endl <<endl;
        getch();
    }




    //cout<<rows<<" "<<cols<<endl;

    return 0;
}
















