#pragma once

#include <UnitTestResult.h>

#include <functional>
#include <list>

namespace CommandFlagTests
{
    std::list<std::function<UnitTestResult(void)>> GetUnitTests( );

    namespace CtorTests
    {
        template <class T>
        UnitTestResult FlagName( );

        template <class T>
        UnitTestResult FullList( );

        template <class T>
        UnitTestResult Copy( );

        template <class T>
        UnitTestResult Move( );
    }
}
