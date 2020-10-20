#pragma once

#include <UnitTestResult.h>

#include <cstdint>
#include <functional>
#include <list>

namespace CommandParserTests
{
    // Forward declaration.
    enum class TestCaseMask : uint64_t;

    std::list<std::function<UnitTestResult(void)>> GetUnitTests();

    template <class, TestCaseMask, TestCaseMask, bool, bool, bool>
    UnitTestResult ParserPermutationTest();
}