#include "AcfTestComponentProgramProvider.hpp"
#include "AcfTestProgram.hpp"

namespace AcfTest
{

IProgram::Ptr AcfTestComponentProgramProvider::CreateProgramInternal(const String& programName, const String& programType)
{
    if (programType == "AcfTestProgram")
    { 
        return std::make_shared<::AcfTest::AcfTestProgram>(this->acfTestComponent, programName);
    }

    // else unknown program
    return nullptr;
}

} // end of namespace AcfTest
