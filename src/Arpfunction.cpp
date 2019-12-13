#include "Arpfunction.hpp"
#include "Arp/System/Rsc/ServiceManager.hpp"

using namespace Arp;
using namespace std;

Event *p_Event;
Info_and_status *p_Info_and_status;
bool alreadyStarted = false;

int ACFregister(const char *kApplicationName)
{
    // Regist the project to PLCnext platform. the *.acf.setting file
    // is automatically generated.
    // Syntax:  ACFregister("applicationName");
    // Input:   const char *kApplicationName -- The name of project.
    // return:  0 success, -1 failure.
    p_Event = new Event;
    char szExePath[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", szExePath, PATH_MAX);
    string strDirPath;
    if (len != -1)
    {
        strDirPath = dirname(szExePath);
    }
    // Generate path for {applicationName}.acf.settings
    string strSettingsFile(strDirPath);
    strSettingsFile += "/";
    strSettingsFile += kApplicationName;
    strSettingsFile += ".acf.settings";
    // Regist to PLCnext platform
    if (ArpSystemModule_Load("/usr/lib", kApplicationName, strSettingsFile.c_str()) != 0)
    {
        return -1;
    }
    // Status callback
    ArpPlcDomain_SetHandler(PlcOperationHandler);
    return 0;
}


void PlcOperationHandler(enum PlcOperation operation)
{
    // PLC event callback.
    switch (operation)
    {
        break;
    case PlcOperation_Load:
        Log::Info("Call of PLC Load");
        p_Event -> Event_Load();
        break;
    case PlcOperation_Setup:
        Log::Info("Call of PLC Setup");
        p_Event -> Event_Setup();
        break;
    case PlcOperation_StartCold:
        Log::Info("Call of PLC Start Cold");
        p_Event -> Event_StartCold();
        break;
    case PlcOperation_StartWarm:
        Log::Info("Call of PLC Start Warm");
        // Make instance of Info_and_status
        if(!alreadyStarted) 
        {
            p_Info_and_status = new Info_and_status;
        }
        alreadyStarted = true;
        // Get the static information of the controller.
        p_Info_and_status -> GetInfo();
        p_Event -> Event_StartWarm();
        break;
    case PlcOperation_StartHot:
        Log::Info("Call of PLC Start Hot");
        p_Event -> Event_StartHot();
        break;
    case PlcOperation_Stop:
        Log::Info("Call of PLC Stop");
        p_Event->Event_Stop();
        break;
    case PlcOperation_Reset:
        Log::Info("Call of PLC Reset");
        p_Event->Event_Reset();
        break;
    case PlcOperation_Unload:
        Log::Info("Call of PLC Unload");
        p_Event->Event_Unload();
        break;
    case PlcOperation_None:
        Log::Info("Call of PLC None");
        p_Event->Event_None();
        break;
    default:
        Log::Error("Call of unknown PLC state");
        break;
    }
}

// Constructor - Initialize the <IDeviceInfoService> and <IDeviceStatusService> 
//                  for ServiceManager.
Info_and_status::Info_and_status() : m_szVendorName(NULL),
                                     m_szArticleName(NULL),
                                     m_szArticleNumber(NULL),
                                     m_szSerialNumber(NULL),
                                     m_szFirmwareVersion(NULL),
                                     m_szFirmwareBuildDate(NULL),
                                     m_szFirmwareBuildTime(NULL),
                                     m_szHardwareVersion(NULL),
                                     m_szUniqueHardwareId(NULL),
                                     m_byDeviceHealth(0),
                                     m_byCpuAverLoad(0),
                                     m_byCpucore1Load(0),
                                     m_byCpucore2Load(0),
                                     m_byMemoryUsagePercent(0),
                                     m_byBoardHumidity(0),
                                     m_i8BoardTemperatureCentigrade(0),
                                     m_byProgramMemoryIECUsagePercent(0),
                                     m_byDataMemoryIECUsagePercent(0)
{
    m_pDeviceInfoService = ServiceManager::GetService<IDeviceInfoService>();
    m_pDeviceStatusService = ServiceManager::GetService<IDeviceStatusService>();
}
// Get static information of the controller.
void Info_and_status ::GetInfo()
{
    m_rscVendorName = m_pDeviceInfoService->GetItem("General.VendorName");
    m_szVendorName = m_rscVendorName.GetChars();
    m_rscArticleName = m_pDeviceInfoService->GetItem("General.ArticleName");
    m_szArticleName = m_rscArticleName.GetChars();
    m_rscArticleNumber = m_pDeviceInfoService->GetItem("General.ArticleNumber");
    m_szArticleNumber = m_rscArticleNumber.GetChars();
    m_rscSerialNumber = m_pDeviceInfoService->GetItem("General.SerialNumber");
    m_szSerialNumber = m_rscSerialNumber.GetChars();
    m_rscFirmwareVersion = m_pDeviceInfoService->GetItem("General.Firmware.Version");
    m_szFirmwareVersion = m_rscFirmwareVersion.GetChars();
    m_rscFirmwareBuildDate = m_pDeviceInfoService->GetItem("General.Firmware.BuildDate");
    m_szFirmwareBuildDate = m_rscFirmwareBuildDate.GetChars();
    m_rscFirmwareBuildTime = m_pDeviceInfoService->GetItem("General.Firmware.BuildTime");
    m_szFirmwareBuildTime = m_rscFirmwareBuildTime.GetChars();
    m_rscHardwareVersion = m_pDeviceInfoService->GetItem("General.Hardware.Version");
    m_szHardwareVersion = m_rscHardwareVersion.GetChars();
    m_rscUniqueHardwareId = m_pDeviceInfoService->GetItem("General.UniqueHardwareId");
    m_szUniqueHardwareId = m_rscUniqueHardwareId.GetChars();
}
// Get the dynamic information of the controller.
void Info_and_status ::RefreshStatus()
{
    m_rscDeviceHealth = m_pDeviceStatusService->GetItem("Status.DeviceHealth");
    m_rscDeviceHealth.CopyTo(m_byDeviceHealth);
    m_rscCpuAverLoad = m_pDeviceStatusService->GetItem("Status.Cpu.0.Load.Percent");
    m_rscCpuAverLoad.CopyTo(m_byCpuAverLoad);
    m_rscCpucore1Load = m_pDeviceStatusService->GetItem("Status.Cpu.1.Load.Percent");
    m_rscCpucore1Load.CopyTo(m_byCpucore1Load);
    m_rscCpucore2Load = m_pDeviceStatusService->GetItem("Status.Cpu.2.Load.Percent");
    m_rscCpucore2Load.CopyTo(m_byCpucore2Load);
    m_rscMemoryUsagePercent = m_pDeviceStatusService->GetItem("Status.Memory.Usage.Percent");
    m_rscMemoryUsagePercent.CopyTo(m_byMemoryUsagePercent);
    m_rscBoardHumidity = m_pDeviceStatusService->GetItem("Status.Board.Humidity");
    m_rscBoardHumidity.CopyTo(m_byBoardHumidity);
    m_rscBoardTemperatureCentigrade = m_pDeviceStatusService->GetItem("Status.Board.Temperature.Centigrade");
    m_rscBoardTemperatureCentigrade.CopyTo(m_i8BoardTemperatureCentigrade);
    m_rscProgramMemoryIECUsagePercent = m_pDeviceStatusService->GetItem("Status.ProgramMemoryIEC.Usage.Percent");
    m_rscProgramMemoryIECUsagePercent.CopyTo(m_byProgramMemoryIECUsagePercent);
    m_rscDataMemoryIECUsagePercent = m_pDeviceStatusService->GetItem("Status.DataMemoryIEC.Usage.Percent");
    m_rscDataMemoryIECUsagePercent.CopyTo(m_byDataMemoryIECUsagePercent);
}
