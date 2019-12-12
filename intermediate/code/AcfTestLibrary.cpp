#include "AcfTestLibrary.hpp"
#include "Arp/System/Core/CommonTypeName.hxx"
#include "Arp/Plc/Commons/Meta/TypeSystem/TypeSystem.h"
#include "AcfTestComponent.hpp"

namespace AcfTest
{

AcfTestLibrary::AcfTestLibrary(AppDomain& appDomain)
    : MetaLibraryBase(appDomain, ARP_VERSION_CURRENT, typeDomain)
    , typeDomain(CommonTypeName<AcfTestLibrary>().GetNamespace())
{
    this->componentFactory.AddFactoryMethod(CommonTypeName<::AcfTest::AcfTestComponent>(), &::AcfTest::AcfTestComponent::Create);
    this->InitializeTypeDomain();
}

void AcfTestLibrary::Main(AppDomain& appDomain)
{
    SingletonBase::CreateInstance(appDomain);
}

extern "C" ARP_CXX_SYMBOL_EXPORT ILibrary& ArpDynamicLibraryMain(AppDomain& appDomain)
{
    AcfTestLibrary::Main(appDomain);
    return  AcfTestLibrary::GetInstance();
}

} // end of namespace AcfTest
