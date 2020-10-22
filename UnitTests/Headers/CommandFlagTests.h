#pragma once

#include <UnitTestResult.h>

#include <functional>
#include <list>

namespace CommandFlagTests
{
    std::list<std::function<UnitTestResult(void)>> GetUnitTests();

    namespace CtorTests
    {
        UnitTestResult FlagName();
        UnitTestResult FullList();
        UnitTestResult Copy();
        UnitTestResult Move();
    }
}
