﻿#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/System/Core/AppDomain.hpp"
#include "Arp/System/Core/Singleton.hxx"
#include "Arp/System/Core/Library.h"
#include "Arp/Plc/Commons/Meta/MetaLibraryBase.hpp"
#include "Arp/Plc/Commons/Meta/TypeSystem/TypeDomain.hpp"

namespace AcfTest
{

using namespace Arp::System::Acf;
using namespace Arp::Plc::Commons::Meta;
using namespace Arp::Plc::Commons::Meta::TypeSystem;

class AcfTestLibrary : public MetaLibraryBase, public Singleton<AcfTestLibrary>
{
public: // typedefs
    typedef Singleton<AcfTestLibrary> SingletonBase;

public: // construction/destruction
    AcfTestLibrary(AppDomain& appDomain);
    virtual ~AcfTestLibrary() = default;

public: // static operations (called through reflection)
    static void Main(AppDomain& appDomain);

private: // methods
    void InitializeTypeDomain();

private: // deleted methods
    AcfTestLibrary(const AcfTestLibrary& arg) = delete;
    AcfTestLibrary& operator= (const AcfTestLibrary& arg) = delete;

private:  // fields
    TypeDomain typeDomain;
};

extern "C" ARP_CXX_SYMBOL_EXPORT ILibrary& ArpDynamicLibraryMain(AppDomain& appDomain);

///////////////////////////////////////////////////////////////////////////////
// inline methods of class AcfTestLibrary

} // end of namespace AcfTest
