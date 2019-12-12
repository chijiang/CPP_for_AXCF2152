#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Esm/ProgramProviderBase.hpp"

namespace AcfTest
{

using namespace Arp;
using namespace Arp::Plc::Commons::Esm;

//forwards
class AcfTestComponent;

class AcfTestComponentProgramProvider : public ProgramProviderBase
{

public:   // construction/destruction
    AcfTestComponentProgramProvider(AcfTestComponent& acfTestComponentArg);
    virtual ~AcfTestComponentProgramProvider() = default;

public:   // IProgramProvider operations
    IProgram::Ptr CreateProgramInternal(const String& programName, const String& programType) override;

private:   // deleted methods
    AcfTestComponentProgramProvider(const AcfTestComponentProgramProvider& arg) = delete;
    AcfTestComponentProgramProvider& operator=(const AcfTestComponentProgramProvider& arg) = delete;

private: // fields
    AcfTestComponent& acfTestComponent;
};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class AcfTestComponentProgramProvider

inline AcfTestComponentProgramProvider::AcfTestComponentProgramProvider(AcfTestComponent& acfTestComponentArg)
    : acfTestComponent(acfTestComponentArg)
{
}

} // end of namespace AcfTest
