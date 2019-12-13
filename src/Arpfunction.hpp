#include "Arp/System/ModuleLib/Module.h"                          // To use ArpSystemModule_Load()
#include "Arp/System/Commons/Logging.h"                           // To import Log::**()
#include <libgen.h>                                               // To import method dirname()
#include "Arp/Plc/AnsiC/Domain/PlcOperationHandler.h"             // Recall event
#include "Arp/Device/Interface/Services/IDeviceStatusService.hpp" // To collect the status of controller
#include "Arp/Device/Interface/Services/IDeviceInfoService.hpp"   // To collect information of controller

using namespace std;

using namespace Arp::System::Rsc;
using namespace Arp::Device::Interface::Services;
using namespace Arp;

class Event;
class Info_and_status;

int ACFregister(const char *kApplicationName);
void PlcOperationHandler(enum PlcOperation operation);

class Event
{
    // Recall event of PLC.
    public:
        void Event_None(void);
        void Event_Load(void);
        void Event_Unload(void);
        void Event_Setup(void);
        void Event_StartCold(void);
        void Event_StartWarm(void);
        void Event_StartHot(void);
        void Event_Stop(void);
        void Event_Reset(void);
};

class Info_and_status{
    public:
        Info_and_status();
    
    public:
        void RefreshStatus(void);
        void GetInfo(void);
    
    private:
        IDeviceInfoService::Ptr m_pDeviceInfoService;
        IDeviceStatusService::Ptr m_pDeviceStatusService;

    private: // Info
        RscVariant<512> m_rscVendorName;
        RscVariant<512> m_rscArticleName;
        RscVariant<512> m_rscArticleNumber;
        RscVariant<512> m_rscSerialNumber;
        RscVariant<512> m_rscFirmwareVersion;
        RscVariant<512> m_rscFirmwareBuildDate;
        RscVariant<512> m_rscFirmwareBuildTime;
        RscVariant<512> m_rscHardwareVersion;
        RscVariant<512> m_rscUniqueHardwareId;
    
    public:
        const char *m_szVendorName;
        const char *m_szArticleName;
        const char *m_szArticleNumber;
        const char *m_szSerialNumber;
        const char *m_szFirmwareVersion;
        const char *m_szFirmwareBuildDate;
        const char *m_szFirmwareBuildTime;
        const char *m_szHardwareVersion;
        const char *m_szUniqueHardwareId;

    private: //status
        RscVariant<512> m_rscDeviceHealth;
        RscVariant<512> m_rscCpuAverLoad;
        RscVariant<512> m_rscCpucore1Load;
        RscVariant<512> m_rscCpucore2Load;
        RscVariant<512> m_rscMemoryUsagePercent;
        RscVariant<512> m_rscBoardHumidity;
        RscVariant<512> m_rscBoardTemperatureCentigrade;
        RscVariant<512> m_rscProgramMemoryIECUsagePercent;
        RscVariant<512> m_rscDataMemoryIECUsagePercent;

    public: //status
        Arp::byte m_byDeviceHealth;
        Arp::byte m_byCpuAverLoad;
        Arp::byte m_byCpucore1Load;
        Arp::byte m_byCpucore2Load;
        Arp::byte m_byMemoryUsagePercent;
        Arp::byte m_byBoardHumidity;
        Arp::int8 m_i8BoardTemperatureCentigrade;
        Arp::byte m_byProgramMemoryIECUsagePercent;
        Arp::byte m_byDataMemoryIECUsagePercent;
};