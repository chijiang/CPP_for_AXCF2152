﻿#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Esm/ProgramBase.hpp"
#include "Arp/System/Commons/Logging.h"
#include "AcfTestComponent.hpp"

namespace AcfTest
{

using namespace Arp;
using namespace Arp::System::Commons::Diagnostics::Logging;
using namespace Arp::Plc::Commons::Esm;

//#program
//#component(AcfTest::AcfTestComponent)
class AcfTestProgram : public ProgramBase, private Loggable<AcfTestProgram>
{
public: // typedefs

public: // construction/destruction
    AcfTestProgram(AcfTest::AcfTestComponent& acfTestComponentArg, const String& name);
    AcfTestProgram(const AcfTestProgram& arg) = delete;
    virtual ~AcfTestProgram() = default;

public: // operators
    AcfTestProgram&  operator=(const AcfTestProgram& arg) = delete;

public: // properties

public: // operations
    void    Execute() override;

public: /* Ports
           =====
           Ports are defined in the following way:
           //#port
           //#attributes(Input|Retain)
           //#name(NameOfPort)
           boolean portField;

           The attributes comment define the port attributes and is optional.
           The name comment defines the name of the port and is optional. Default is the name of the field.
        */

private: // fields
    AcfTest::AcfTestComponent& acfTestComponent;

};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class ProgramBase
inline AcfTestProgram::AcfTestProgram(AcfTest::AcfTestComponent& acfTestComponentArg, const String& name)
: ProgramBase(name)
, acfTestComponent(acfTestComponentArg)
{
}

} // end of namespace AcfTest
