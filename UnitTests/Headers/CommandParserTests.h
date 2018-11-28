#pragma once

#include <UnitTestResult.h>

#include <functional>
#include <list>

namespace CommandParserTests
{
    // Forward declaration.
    enum class TestCaseMask : uint64;

    std::list<std::function<UnitTestResult(void)>> GetUnitTests( );

    template <class, TestCaseMask, TestCaseMask, bool, bool, bool>
    UnitTestResult ParserPermutationTest( );
}