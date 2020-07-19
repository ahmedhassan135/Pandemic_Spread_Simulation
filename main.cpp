#include <iostream>
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
};

class Working : public Human
{
    public:
    Coordinates house_address;
    Coordinates office_address;
    int travelling;
    int ticks_stuck;

    void initialize_variables(int id, int Current_location_x, int Current_location_y, bool Infected, float Probability_of_infection, int House_address_x, int House_address_y, int Office_address_x, int Office_address_y)
    {
        ID = id;
        current_location.x = Current_location_x;
        current_location.y = Current_location_y;
        infected = Infected;
        probability_of_infection = Probability_of_infection;

        house_address.x = House_address_x;
        house_address.y = House_address_y;
        office_address.x = Office_address_x;
        office_address.y = Office_address_y;
        travelling = 0;                         //Travelling to office at start
        ticks_stuck = 0;


    }

    Coordinates GetCurrentLocation()
    {
        return current_location;
    }

    Coordinates GetHouseAddress()
    {
        return house_address;
    }

    Coordinates GetOfficeAddress()
    {
        return office_address;
    }

    void SetCurrentLocation(int Current_location_x, int Current_location_y)
    {
        current_location.x = Current_location_x;
        current_location.y = Current_location_y;
    }

    void SetHouseAddress(int House_address_x, int House_address_y)
    {
        house_address.x = House_address_x;
        house_address.y = House_address_y;
    }


    void SetOfficeAddress(int Office_address_x, int Office_address_y)
    {
        office_address.x = Office_address_x;
        office_address.y = Office_address_y;
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

    Coordinates GetCurrentLocation()
    {
        return current_location;
    }

};


#define rows 6
#define cols 6

Cell world[rows][cols];


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


    //world[2][3].occupied_by_id = 34;
}


void display_world()
{
    for (int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            cout<<world[i][j].occupied_by_id<<"\t";
        }
        cout<<endl<<endl;
    }
}


//TODO: contact and probability of infection
//TODO: movement of a human

//TODO: Display number of people currently infected and recovered.



int main()
{
    initialize();
    display_world();



    //cout<<rows<<" "<<cols<<endl;

    return 0;
}
















