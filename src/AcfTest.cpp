#include "iostream"
#include "Arpfunction.hpp"

using namespace std;
using namespace Arp;

bool running = false; // If the PLC is in running status.
int cnt = 0; // For testing of cold, warm and hot start.

void Event::Event_None() 
{
    // Executed code here.
}

void Event::Event_Load() 
{
    // Executed code here.
}

void Event::Event_Setup() 
{
    // Executed code here.
}

void Event::Event_StartCold() 
{
    // Executed code here.
    running = true;
}

void Event::Event_StartWarm() 
{
    // Executed code here.
    running = true;
}

void Event::Event_StartHot() 
{
    // Executed code here.
    running = true;
}

void Event::Event_Stop() 
{
    // Executed code here.
    running = false;
}

void Event::Event_Reset() 
{
    // Executed code here.
    cnt = 0;
}

void Event::Event_Unload() 
{
    // Executed code here.
}

int main() 
{
    ACFregister("AcfTest");
    while (true)
    {
        if (running == true)
        {
            cnt++;
            Log::Info("PLCnext platform is running: {}", cnt);
            if (cnt > 1000)
            {
                cnt = 0;
            }
            cout << "[" << cnt << "]: " << "System running.. " << endl;
        }
    }
    return 0;
}