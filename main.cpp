#include <iostream>
using namespace std;


struct Cell
{
    int occupied_by_id; //ID of human that occupies it if any
    bool isOffice;
};



class Human
{
    public:
    int ID;
    int current_location_x;
    int current_location_y;
    bool infected;
    float probability_of_infection;
};

class Working : public Human
{
    public:
    int house_address_x;
    int house_address_y;
    int office_address_x;
    int office_address_y;
    int travelling;
    int ticks_stuck;
};

class NotWorking : public Human
{

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
















