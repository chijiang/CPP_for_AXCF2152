#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Meta/TypeSystem/TypeSystem.h"
#include "AcfTestProgram.hpp"
#include "AcfTestLibrary.hpp"

namespace AcfTest
{

using namespace Arp::Plc::Commons::Meta;

    
    void AcfTestLibrary::InitializeTypeDomain()
    {
        this->typeDomain.AddTypeDefinitions
        (
            // Begin TypeDefinitions
            {
                {   // ProgramDefinition: AcfTest::AcfTestProgram
                    DataType::Program, CTN<AcfTest::AcfTestProgram>(), sizeof(::AcfTest::AcfTestProgram), alignof(::AcfTest::AcfTestProgram), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                    }
                },
            }
            // End TypeDefinitions
        );
    }

} // end of namespace AcfTest

