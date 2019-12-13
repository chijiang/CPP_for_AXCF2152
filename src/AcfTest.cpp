#include "iostream"
#include "Arpfunction.hpp"

using namespace std;
using namespace Arp;

bool running = false; // If the PLC is in running status.
int cnt = 0; // For testing of cold, warm and hot start.
extern Info_and_status *p_Info_and_status;

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
            // Refresh all status parameters of the controller. 
            p_Info_and_status -> RefreshStatus();
            // Write all controller information into the log file.
            Log::Info("{:*^60}", "Controller Info");
            Log::Info("VendorName:{}", p_Info_and_status->m_szVendorName);
            Log::Info("ArticleName:{}", p_Info_and_status->m_szArticleName);
            Log::Info("ArticleNumber:{}", p_Info_and_status->m_szArticleNumber);
            Log::Info("SerialNumber:{}", p_Info_and_status->m_szSerialNumber);
            Log::Info("FirmwareVersion:{}", p_Info_and_status->m_szFirmwareVersion);
            Log::Info("FirmwareBuildDate:{}", p_Info_and_status->m_szFirmwareBuildDate);
            Log::Info("FirmwareBuildTime:{}", p_Info_and_status->m_szFirmwareBuildTime);
            Log::Info("HardwareVersion:{}", p_Info_and_status->m_szHardwareVersion);
            Log::Info("UniqueHardwareId:{}", p_Info_and_status->m_szUniqueHardwareId);

            // Write all controller status into the log file.
            Log::Info("{:*^60}", "Controller Status");
            Log::Info("DeviceHealth:{:d}(0:OK   1:Warning   2:ERROR)", p_Info_and_status->m_byDeviceHealth);
            Log::Info("CpuAverLoad:{:d}%", p_Info_and_status->m_byCpuAverLoad);
            Log::Info("Cpucore1Load:{:d}%", p_Info_and_status->m_byCpucore1Load);
            Log::Info("Cpucore2Load:{:d}%", p_Info_and_status->m_byCpucore2Load);
            Log::Info("MemoryUsagePercent:{:d}%", p_Info_and_status->m_byMemoryUsagePercent);
            Log::Info("BoardHumidity:{:d}%", p_Info_and_status->m_byBoardHumidity);
            Log::Info("BoardTemperatureCentigrade:{:d}°C", p_Info_and_status->m_i8BoardTemperatureCentigrade);
            Log::Info("ProgramMemoryIECUsagePercent:{:d}%", p_Info_and_status->m_byProgramMemoryIECUsagePercent);
            Log::Info("DataMemoryIECUsagePercent:{:d}%", p_Info_and_status->m_byDataMemoryIECUsagePercent);
            
            cnt++;
            Log::Info("PLCnext platform is running: {}", cnt);
            if (cnt > 1000)
            {
                cnt = 0;
            }
        }
        sleep(1);
    }
    return 0;
}