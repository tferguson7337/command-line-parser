#include <CommandParserTests.h>

#include <CommandParser.h>

#include <CCStringUtil.h>

namespace CommandParserTests
{

    enum class TestCaseMask : uint64_t
    {
        OneOfOne = 0,
        OneOfMany = 1,
        ManyOfMany = 2,
        AllOfMany = 3,
        Match = 4,

        MAX = Match << 1,
        BEGIN = OneOfOne,

        QuantityMask = Match - 1,
    };

    using TestCaseMaskType = std::underlying_type_t<TestCaseMask>;

    constexpr TestCaseMask operator~(const TestCaseMask& rhs)
    {
        return static_cast<TestCaseMask>(~static_cast<TestCaseMaskType>(rhs));
    }

    constexpr TestCaseMask operator|(const TestCaseMask& lhs, const TestCaseMask& rhs)
    {
        return static_cast<TestCaseMask>(static_cast<TestCaseMaskType>(lhs) | static_cast<TestCaseMaskType>(rhs));
    }

    constexpr TestCaseMask operator&(const TestCaseMask& lhs, const TestCaseMask& rhs)
    {
        return static_cast<TestCaseMask>(static_cast<TestCaseMaskType>(lhs) & static_cast<TestCaseMaskType>(rhs));
    }

    constexpr TestCaseMask operator^(const TestCaseMask& lhs, const TestCaseMask& rhs)
    {
        return static_cast<TestCaseMask>(static_cast<TestCaseMaskType>(lhs) ^ static_cast<TestCaseMaskType>(rhs));
    }

    constexpr TestCaseMask& operator|=(TestCaseMask& lhs, const TestCaseMask& rhs)
    {
        return lhs = lhs | rhs;
    }

    constexpr TestCaseMask& operator&=(TestCaseMask& lhs, const TestCaseMask& rhs)
    {
        return lhs = lhs & rhs;
    }

    constexpr TestCaseMask& operator^=(TestCaseMask& lhs, const TestCaseMask& rhs)
    {
        return lhs = lhs ^ rhs;
    }


#define INCREMENT_TEST_CASE_MASK(m) m = static_cast<TestCaseMask>(static_cast<TestCaseMaskType>(m) + 1)

    //
    //  Returns list of unit test functions to be run.
    //
    std::list<std::function<UnitTestResult(void)>> GetUnitTests()
    {
        // Disable warning for using too much memory off of the stack.
    #pragma warning( push )
    #pragma warning( disable : 6262 )
        static const std::list<std::function<UnitTestResult(void)>> tests
        {
            // Optional Flag - Optional Data

            // Flag-Case - Match One-of-One
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::OneOfOne, TestCaseMask::Match | TestCaseMask::OneOfOne, true, true, true>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::OneOfOne, TestCaseMask::OneOfOne, true, true, true>,

            // Flag-Case - Match One-of-Many
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::OneOfMany, TestCaseMask::Match | TestCaseMask::OneOfMany, true, true, true>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::OneOfMany, TestCaseMask::OneOfMany, true, true, true>,

            // Flag-Case - Match Many-of-Many
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::ManyOfMany, TestCaseMask::Match | TestCaseMask::OneOfMany, true, true, true>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::ManyOfMany, TestCaseMask::Match | TestCaseMask::ManyOfMany, true, true, true>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::ManyOfMany, TestCaseMask::Match | TestCaseMask::AllOfMany, true, true, true>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::ManyOfMany, TestCaseMask::OneOfMany, true, true, true>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::ManyOfMany, TestCaseMask::ManyOfMany, true, true, true>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::ManyOfMany, TestCaseMask::AllOfMany, true, true, true>,

            // Flag-Case - Match All-of-Many
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::AllOfMany, TestCaseMask::Match | TestCaseMask::OneOfMany, true, true, true>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::AllOfMany, TestCaseMask::Match | TestCaseMask::ManyOfMany, true, true, true>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::AllOfMany, TestCaseMask::Match | TestCaseMask::AllOfMany, true, true, true>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::AllOfMany, TestCaseMask::OneOfMany, true, true, true>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::AllOfMany, TestCaseMask::ManyOfMany, true, true, true>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::AllOfMany, TestCaseMask::AllOfMany, true, true, true>,

            // Flag-Case - No-Match One-of-One
            ParserPermutationTest<TestCaseMask::OneOfOne, TestCaseMask::OneOfOne, true, true, true>,
            ParserPermutationTest<TestCaseMask::OneOfOne, TestCaseMask::AllOfMany, true, true, true>,

            // Flag-Case - No-Match One-of-Many
            ParserPermutationTest<TestCaseMask::OneOfMany, TestCaseMask::Match | TestCaseMask::OneOfMany, true, true, true>,
            ParserPermutationTest<TestCaseMask::OneOfMany, TestCaseMask::Match | TestCaseMask::ManyOfMany, true, true, true>,
            ParserPermutationTest<TestCaseMask::OneOfMany, TestCaseMask::Match | TestCaseMask::AllOfMany, true, true, true>,
            ParserPermutationTest<TestCaseMask::OneOfMany, TestCaseMask::OneOfMany, true, true, true>,
            ParserPermutationTest<TestCaseMask::OneOfMany, TestCaseMask::ManyOfMany, true, true, true>,
            ParserPermutationTest<TestCaseMask::OneOfMany, TestCaseMask::AllOfMany, true, true, true>,

            // Flag-Case - No-Match Many-of-Many
            ParserPermutationTest<TestCaseMask::ManyOfMany, TestCaseMask::Match | TestCaseMask::OneOfMany, true, true, true>,
            ParserPermutationTest<TestCaseMask::ManyOfMany, TestCaseMask::Match | TestCaseMask::ManyOfMany, true, true, true>,
            ParserPermutationTest<TestCaseMask::ManyOfMany, TestCaseMask::Match | TestCaseMask::AllOfMany, true, true, true>,
            ParserPermutationTest<TestCaseMask::ManyOfMany, TestCaseMask::OneOfMany, true, true, true>,
            ParserPermutationTest<TestCaseMask::ManyOfMany, TestCaseMask::ManyOfMany, true, true, true>,
            ParserPermutationTest<TestCaseMask::ManyOfMany, TestCaseMask::AllOfMany, true, true, true>,

            // Flag-Case - No-Match All-of-Many
            ParserPermutationTest<TestCaseMask::AllOfMany, TestCaseMask::OneOfOne, true, true, true>,
            ParserPermutationTest<TestCaseMask::AllOfMany, TestCaseMask::AllOfMany, true, true, true>,

            // Optional Flag - Required Data

            // Flag-Case - Match One-of-One
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::OneOfOne, TestCaseMask::Match | TestCaseMask::OneOfOne, true, true, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::OneOfOne, TestCaseMask::OneOfOne, true, true, false>,

            // Flag-Case - Match One-of-Many
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::OneOfMany, TestCaseMask::Match | TestCaseMask::OneOfMany, true, true, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::OneOfMany, TestCaseMask::OneOfMany, true, true, false>,

            // Flag-Case - Match Many-of-Many
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::ManyOfMany, TestCaseMask::Match | TestCaseMask::OneOfMany, true, true, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::ManyOfMany, TestCaseMask::Match | TestCaseMask::ManyOfMany, true, true, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::ManyOfMany, TestCaseMask::Match | TestCaseMask::AllOfMany, true, true, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::ManyOfMany, TestCaseMask::OneOfMany, true, true, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::ManyOfMany, TestCaseMask::ManyOfMany, true, true, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::ManyOfMany, TestCaseMask::AllOfMany, true, true, false>,

            // Flag-Case - Match All-of-Many
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::AllOfMany, TestCaseMask::Match | TestCaseMask::OneOfMany, true, true, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::AllOfMany, TestCaseMask::Match | TestCaseMask::ManyOfMany, true, true, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::AllOfMany, TestCaseMask::Match | TestCaseMask::AllOfMany, true, true, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::AllOfMany, TestCaseMask::OneOfMany, true, true, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::AllOfMany, TestCaseMask::ManyOfMany, true, true, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::AllOfMany, TestCaseMask::AllOfMany, true, true, false>,

            // Flag-Case - No-Match One-of-One
            ParserPermutationTest<TestCaseMask::OneOfOne, TestCaseMask::OneOfOne, true, true, false>,
            ParserPermutationTest<TestCaseMask::OneOfOne, TestCaseMask::AllOfMany, true, true, false>,

            // Flag-Case - No-Match One-of-Many
            ParserPermutationTest<TestCaseMask::OneOfMany, TestCaseMask::Match | TestCaseMask::OneOfMany, true, true, false>,
            ParserPermutationTest<TestCaseMask::OneOfMany, TestCaseMask::Match | TestCaseMask::ManyOfMany, true, true, false>,
            ParserPermutationTest<TestCaseMask::OneOfMany, TestCaseMask::Match | TestCaseMask::AllOfMany, true, true, false>,
            ParserPermutationTest<TestCaseMask::OneOfMany, TestCaseMask::OneOfMany, true, true, false>,
            ParserPermutationTest<TestCaseMask::OneOfMany, TestCaseMask::ManyOfMany, true, true, false>,
            ParserPermutationTest<TestCaseMask::OneOfMany, TestCaseMask::AllOfMany, true, true, false>,

            // Flag-Case - No-Match Many-of-Many
            ParserPermutationTest<TestCaseMask::ManyOfMany, TestCaseMask::Match | TestCaseMask::OneOfMany, true, true, false>,
            ParserPermutationTest<TestCaseMask::ManyOfMany, TestCaseMask::Match | TestCaseMask::ManyOfMany, true, true, false>,
            ParserPermutationTest<TestCaseMask::ManyOfMany, TestCaseMask::Match | TestCaseMask::AllOfMany, true, true, false>,
            ParserPermutationTest<TestCaseMask::ManyOfMany, TestCaseMask::OneOfMany, true, true, false>,
            ParserPermutationTest<TestCaseMask::ManyOfMany, TestCaseMask::ManyOfMany, true, true, false>,
            ParserPermutationTest<TestCaseMask::ManyOfMany, TestCaseMask::AllOfMany, true, true, false>,

            // Flag-Case - No-Match All-of-Many
            ParserPermutationTest<TestCaseMask::AllOfMany, TestCaseMask::OneOfOne, true, true, false>,
            ParserPermutationTest<TestCaseMask::AllOfMany, TestCaseMask::AllOfMany, true, true, false>,

            // Optional Flag - Data Unaccepted

            // Flag-Case - Match One-of-One
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::OneOfOne, TestCaseMask::Match | TestCaseMask::OneOfOne, true, false, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::OneOfOne, TestCaseMask::OneOfOne, true, false, false>,

            // Flag-Case - Match One-of-Many
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::OneOfMany, TestCaseMask::Match | TestCaseMask::OneOfMany, true, false, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::OneOfMany, TestCaseMask::OneOfMany, true, false, false>,

            // Flag-Case - Match Many-of-Many
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::ManyOfMany, TestCaseMask::Match | TestCaseMask::OneOfMany, true, false, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::ManyOfMany, TestCaseMask::Match | TestCaseMask::ManyOfMany, true, false, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::ManyOfMany, TestCaseMask::Match | TestCaseMask::AllOfMany, true, false, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::ManyOfMany, TestCaseMask::OneOfMany, true, false, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::ManyOfMany, TestCaseMask::ManyOfMany, true, false, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::ManyOfMany, TestCaseMask::AllOfMany, true, false, false>,

            // Flag-Case - Match All-of-Many
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::AllOfMany, TestCaseMask::Match | TestCaseMask::OneOfMany, true, false, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::AllOfMany, TestCaseMask::Match | TestCaseMask::ManyOfMany, true, false, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::AllOfMany, TestCaseMask::Match | TestCaseMask::AllOfMany, true, false, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::AllOfMany, TestCaseMask::OneOfMany, true, false, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::AllOfMany, TestCaseMask::ManyOfMany, true, false, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::AllOfMany, TestCaseMask::AllOfMany, true, false, false>,

            // Flag-Case - No-Match One-of-One
            ParserPermutationTest<TestCaseMask::OneOfOne, TestCaseMask::OneOfOne, true, false, false>,
            ParserPermutationTest<TestCaseMask::OneOfOne, TestCaseMask::AllOfMany, true, false, false>,

            // Flag-Case - No-Match One-of-Many
            ParserPermutationTest<TestCaseMask::OneOfMany, TestCaseMask::Match | TestCaseMask::OneOfMany, true, false, false>,
            ParserPermutationTest<TestCaseMask::OneOfMany, TestCaseMask::Match | TestCaseMask::ManyOfMany, true, false, false>,
            ParserPermutationTest<TestCaseMask::OneOfMany, TestCaseMask::Match | TestCaseMask::AllOfMany, true, false, false>,
            ParserPermutationTest<TestCaseMask::OneOfMany, TestCaseMask::OneOfMany, true, false, false>,
            ParserPermutationTest<TestCaseMask::OneOfMany, TestCaseMask::ManyOfMany, true, false, false>,
            ParserPermutationTest<TestCaseMask::OneOfMany, TestCaseMask::AllOfMany, true, false, false>,

            // Flag-Case - No-Match Many-of-Many
            ParserPermutationTest<TestCaseMask::ManyOfMany, TestCaseMask::Match | TestCaseMask::OneOfMany, true, false, false>,
            ParserPermutationTest<TestCaseMask::ManyOfMany, TestCaseMask::Match | TestCaseMask::ManyOfMany, true, false, false>,
            ParserPermutationTest<TestCaseMask::ManyOfMany, TestCaseMask::Match | TestCaseMask::AllOfMany, true, false, false>,
            ParserPermutationTest<TestCaseMask::ManyOfMany, TestCaseMask::OneOfMany, true, false, false>,
            ParserPermutationTest<TestCaseMask::ManyOfMany, TestCaseMask::ManyOfMany, true, false, false>,
            ParserPermutationTest<TestCaseMask::ManyOfMany, TestCaseMask::AllOfMany, true, false, false>,

            // Flag-Case - No-Match All-of-Many
            ParserPermutationTest<TestCaseMask::AllOfMany, TestCaseMask::OneOfOne, true, false, false>,
            ParserPermutationTest<TestCaseMask::AllOfMany, TestCaseMask::AllOfMany, true, false, false>,

            // Required Flag - Optional Data

            // Flag-Case - Match One-of-One
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::OneOfOne, TestCaseMask::Match | TestCaseMask::OneOfOne, false, true, true>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::OneOfOne, TestCaseMask::OneOfOne, false, true, true>,

            // Flag-Case - Match One-of-Many
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::OneOfMany, TestCaseMask::Match | TestCaseMask::OneOfMany, false, true, true>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::OneOfMany, TestCaseMask::OneOfMany, false, true, true>,

            // Flag-Case - Match Many-of-Many
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::ManyOfMany, TestCaseMask::Match | TestCaseMask::OneOfMany, false, true, true>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::ManyOfMany, TestCaseMask::Match | TestCaseMask::ManyOfMany, false, true, true>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::ManyOfMany, TestCaseMask::Match | TestCaseMask::AllOfMany, false, true, true>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::ManyOfMany, TestCaseMask::OneOfMany, false, true, true>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::ManyOfMany, TestCaseMask::ManyOfMany, false, true, true>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::ManyOfMany, TestCaseMask::AllOfMany, false, true, true>,

            // Flag-Case - Match All-of-Many
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::AllOfMany, TestCaseMask::Match | TestCaseMask::OneOfMany, false, true, true>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::AllOfMany, TestCaseMask::Match | TestCaseMask::ManyOfMany, false, true, true>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::AllOfMany, TestCaseMask::Match | TestCaseMask::AllOfMany, false, true, true>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::AllOfMany, TestCaseMask::OneOfMany, false, true, true>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::AllOfMany, TestCaseMask::ManyOfMany, false, true, true>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::AllOfMany, TestCaseMask::AllOfMany, false, true, true>,

            // Flag-Case - No-Match One-of-One
            ParserPermutationTest<TestCaseMask::OneOfOne, TestCaseMask::OneOfOne, false, true, true>,
            ParserPermutationTest<TestCaseMask::OneOfOne, TestCaseMask::AllOfMany, false, true, true>,

            // Flag-Case - No-Match One-of-Many
            ParserPermutationTest<TestCaseMask::OneOfMany, TestCaseMask::Match | TestCaseMask::OneOfMany, false, true, true>,
            ParserPermutationTest<TestCaseMask::OneOfMany, TestCaseMask::Match | TestCaseMask::ManyOfMany, false, true, true>,
            ParserPermutationTest<TestCaseMask::OneOfMany, TestCaseMask::Match | TestCaseMask::AllOfMany, false, true, true>,
            ParserPermutationTest<TestCaseMask::OneOfMany, TestCaseMask::OneOfMany, false, true, true>,
            ParserPermutationTest<TestCaseMask::OneOfMany, TestCaseMask::ManyOfMany, false, true, true>,
            ParserPermutationTest<TestCaseMask::OneOfMany, TestCaseMask::AllOfMany, false, true, true>,

            // Flag-Case - No-Match Many-of-Many
            ParserPermutationTest<TestCaseMask::ManyOfMany, TestCaseMask::Match | TestCaseMask::OneOfMany, false, true, true>,
            ParserPermutationTest<TestCaseMask::ManyOfMany, TestCaseMask::Match | TestCaseMask::ManyOfMany, false, true, true>,
            ParserPermutationTest<TestCaseMask::ManyOfMany, TestCaseMask::Match | TestCaseMask::AllOfMany, false, true, true>,
            ParserPermutationTest<TestCaseMask::ManyOfMany, TestCaseMask::OneOfMany, false, true, true>,
            ParserPermutationTest<TestCaseMask::ManyOfMany, TestCaseMask::ManyOfMany, false, true, true>,
            ParserPermutationTest<TestCaseMask::ManyOfMany, TestCaseMask::AllOfMany, false, true, true>,

            // Flag-Case - No-Match All-of-Many
            ParserPermutationTest<TestCaseMask::AllOfMany, TestCaseMask::OneOfOne, false, true, true>,
            ParserPermutationTest<TestCaseMask::AllOfMany, TestCaseMask::AllOfMany, false, true, true>,

            // Required Flag - Required Data

            // Flag-Case - Match One-of-One
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::OneOfOne, TestCaseMask::Match | TestCaseMask::OneOfOne, false, true, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::OneOfOne, TestCaseMask::OneOfOne, false, true, false>,

            // Flag-Case - Match One-of-Many
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::OneOfMany, TestCaseMask::Match | TestCaseMask::OneOfMany, false, true, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::OneOfMany, TestCaseMask::OneOfMany, false, true, false>,

            // Flag-Case - Match Many-of-Many
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::ManyOfMany, TestCaseMask::Match | TestCaseMask::OneOfMany, false, true, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::ManyOfMany, TestCaseMask::Match | TestCaseMask::ManyOfMany, false, true, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::ManyOfMany, TestCaseMask::Match | TestCaseMask::AllOfMany, false, true, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::ManyOfMany, TestCaseMask::OneOfMany, false, true, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::ManyOfMany, TestCaseMask::ManyOfMany, false, true, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::ManyOfMany, TestCaseMask::AllOfMany, false, true, false>,

            // Flag-Case - Match All-of-Many
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::AllOfMany, TestCaseMask::Match | TestCaseMask::OneOfMany, false, true, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::AllOfMany, TestCaseMask::Match | TestCaseMask::ManyOfMany, false, true, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::AllOfMany, TestCaseMask::Match | TestCaseMask::AllOfMany, false, true, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::AllOfMany, TestCaseMask::OneOfMany, false, true, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::AllOfMany, TestCaseMask::ManyOfMany, false, true, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::AllOfMany, TestCaseMask::AllOfMany, false, true, false>,

            // Flag-Case - No-Match One-of-One
            ParserPermutationTest<TestCaseMask::OneOfOne, TestCaseMask::OneOfOne, false, true, false>,
            ParserPermutationTest<TestCaseMask::OneOfOne, TestCaseMask::AllOfMany, false, true, false>,

            // Flag-Case - No-Match One-of-Many
            ParserPermutationTest<TestCaseMask::OneOfMany, TestCaseMask::Match | TestCaseMask::OneOfMany, false, true, false>,
            ParserPermutationTest<TestCaseMask::OneOfMany, TestCaseMask::Match | TestCaseMask::ManyOfMany, false, true, false>,
            ParserPermutationTest<TestCaseMask::OneOfMany, TestCaseMask::Match | TestCaseMask::AllOfMany, false, true, false>,
            ParserPermutationTest<TestCaseMask::OneOfMany, TestCaseMask::OneOfMany, false, true, false>,
            ParserPermutationTest<TestCaseMask::OneOfMany, TestCaseMask::ManyOfMany, false, true, false>,
            ParserPermutationTest<TestCaseMask::OneOfMany, TestCaseMask::AllOfMany, false, true, false>,

            // Flag-Case - No-Match Many-of-Many
            ParserPermutationTest<TestCaseMask::ManyOfMany, TestCaseMask::Match | TestCaseMask::OneOfMany, false, true, false>,
            ParserPermutationTest<TestCaseMask::ManyOfMany, TestCaseMask::Match | TestCaseMask::ManyOfMany, false, true, false>,
            ParserPermutationTest<TestCaseMask::ManyOfMany, TestCaseMask::Match | TestCaseMask::AllOfMany, false, true, false>,
            ParserPermutationTest<TestCaseMask::ManyOfMany, TestCaseMask::OneOfMany, false, true, false>,
            ParserPermutationTest<TestCaseMask::ManyOfMany, TestCaseMask::ManyOfMany, false, true, false>,
            ParserPermutationTest<TestCaseMask::ManyOfMany, TestCaseMask::AllOfMany, false, true, false>,

            // Flag-Case - No-Match All-of-Many
            ParserPermutationTest<TestCaseMask::AllOfMany, TestCaseMask::OneOfOne, false, true, false>,
            ParserPermutationTest<TestCaseMask::AllOfMany, TestCaseMask::AllOfMany, false, true, false>,

            // Required Flag - Unaccepted Data

            // Flag-Case - Match One-of-One
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::OneOfOne, TestCaseMask::Match | TestCaseMask::OneOfOne, false, false, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::OneOfOne, TestCaseMask::OneOfOne, false, false, false>,

            // Flag-Case - Match One-of-Many
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::OneOfMany, TestCaseMask::Match | TestCaseMask::OneOfMany, false, false, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::OneOfMany, TestCaseMask::OneOfMany, false, false, false>,

            // Flag-Case - Match Many-of-Many
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::ManyOfMany, TestCaseMask::Match | TestCaseMask::OneOfMany, false, false, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::ManyOfMany, TestCaseMask::Match | TestCaseMask::ManyOfMany, false, false, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::ManyOfMany, TestCaseMask::Match | TestCaseMask::AllOfMany, false, false, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::ManyOfMany, TestCaseMask::OneOfMany, false, false, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::ManyOfMany, TestCaseMask::ManyOfMany, false, false, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::ManyOfMany, TestCaseMask::AllOfMany, false, false, false>,

            // Flag-Case - Match All-of-Many
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::AllOfMany, TestCaseMask::Match | TestCaseMask::OneOfMany, false, false, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::AllOfMany, TestCaseMask::Match | TestCaseMask::ManyOfMany, false, false, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::AllOfMany, TestCaseMask::Match | TestCaseMask::AllOfMany, false, false, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::AllOfMany, TestCaseMask::OneOfMany, false, false, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::AllOfMany, TestCaseMask::ManyOfMany, false, false, false>,
            ParserPermutationTest<TestCaseMask::Match | TestCaseMask::AllOfMany, TestCaseMask::AllOfMany, false, false, false>,

            // Flag-Case - No-Match One-of-One
            ParserPermutationTest<TestCaseMask::OneOfOne, TestCaseMask::OneOfOne, false, false, false>,
            ParserPermutationTest<TestCaseMask::OneOfOne, TestCaseMask::AllOfMany, false, false, false>,

            // Flag-Case - No-Match One-of-Many
            ParserPermutationTest<TestCaseMask::OneOfMany, TestCaseMask::Match | TestCaseMask::OneOfMany, false, false, false>,
            ParserPermutationTest<TestCaseMask::OneOfMany, TestCaseMask::Match | TestCaseMask::ManyOfMany, false, false, false>,
            ParserPermutationTest<TestCaseMask::OneOfMany, TestCaseMask::Match | TestCaseMask::AllOfMany, false, false, false>,
            ParserPermutationTest<TestCaseMask::OneOfMany, TestCaseMask::OneOfMany, false, false, false>,
            ParserPermutationTest<TestCaseMask::OneOfMany, TestCaseMask::ManyOfMany, false, false, false>,
            ParserPermutationTest<TestCaseMask::OneOfMany, TestCaseMask::AllOfMany, false, false, false>,

            // Flag-Case - No-Match Many-of-Many
            ParserPermutationTest<TestCaseMask::ManyOfMany, TestCaseMask::Match | TestCaseMask::OneOfMany, false, false, false>,
            ParserPermutationTest<TestCaseMask::ManyOfMany, TestCaseMask::Match | TestCaseMask::ManyOfMany, false, false, false>,
            ParserPermutationTest<TestCaseMask::ManyOfMany, TestCaseMask::Match | TestCaseMask::AllOfMany, false, false, false>,
            ParserPermutationTest<TestCaseMask::ManyOfMany, TestCaseMask::OneOfMany, false, false, false>,
            ParserPermutationTest<TestCaseMask::ManyOfMany, TestCaseMask::ManyOfMany, false, false, false>,
            ParserPermutationTest<TestCaseMask::ManyOfMany, TestCaseMask::AllOfMany, false, false, false>,

            // Flag-Case - No-Match All-of-Many
            ParserPermutationTest<TestCaseMask::AllOfMany, TestCaseMask::OneOfOne, false, false, false>,
            ParserPermutationTest<TestCaseMask::AllOfMany, TestCaseMask::AllOfMany, false, false, false>
        };
    #pragma warning( pop )

        return tests;
    }

    // Test Helpers //

    // Callback Function Helper
    
    class CallbackHelper
    {
    private:
        bool m_bCallbackTriggered;

    public:
        CallbackHelper() : m_bCallbackTriggered(false)
        { }

        ~CallbackHelper() = default;

        void Callback(const CLP::CommandFlag&) noexcept
        {
            m_bCallbackTriggered = true;
        }

        bool CallbackTriggered() const noexcept
        {
            return m_bCallbackTriggered;
        }

        void ResetFlag() noexcept
        {
            m_bCallbackTriggered = false;
        }
    };


    
    std::vector<CallbackHelper>& GetCallbackHelpers()
    {
        static std::vector<CallbackHelper> vCallbackHelpers(5);

        return vCallbackHelpers;
    }


    
    const std::string& GetTestFlagString(const size_t idx)
    {
        static const std::vector<std::string> flags
        {
            CC::StringUtil::UTFConversion<CC::ReturnType::CppString, char>("/flag1"),
            CC::StringUtil::UTFConversion<CC::ReturnType::CppString, char>("/flag2"),
            CC::StringUtil::UTFConversion<CC::ReturnType::CppString, char>("/flag3"),
            CC::StringUtil::UTFConversion<CC::ReturnType::CppString, char>("/flag4"),
            CC::StringUtil::UTFConversion<CC::ReturnType::CppString, char>("/flag5"),
        };

        if ( idx >= flags.size() )
        {
            throw std::out_of_range("arg flag number[" + std::to_string(idx) + "] is out of range.");
        }

        return flags[idx];
    }

    
    const std::string& GetTestFlagDataString(const size_t idx)
    {
        static const std::vector<std::string> data
        {
            CC::StringUtil::UTFConversion<CC::ReturnType::CppString, char>("\"flag_data_1\""),
            CC::StringUtil::UTFConversion<CC::ReturnType::CppString, char>("\"flag_data_2\""),
            CC::StringUtil::UTFConversion<CC::ReturnType::CppString, char>("\"flag_data_3\""),
            CC::StringUtil::UTFConversion<CC::ReturnType::CppString, char>("\"flag_data_4\""),
            CC::StringUtil::UTFConversion<CC::ReturnType::CppString, char>("\"flag_data_5\""),
        };

        if ( idx >= data.size() )
        {
            throw std::out_of_range("arg index[" + std::to_string(idx) + "] is out of range.");
        }

        return data[idx];
    }

    
    const std::string& GetNonRegisteredFlagString(const size_t idx)
    {
        static const std::vector<std::string> nonFlags
        {
            CC::StringUtil::UTFConversion<CC::ReturnType::CppString, char>("\"non_flag_1\""),
            CC::StringUtil::UTFConversion<CC::ReturnType::CppString, char>("\"non_flag_2\""),
            CC::StringUtil::UTFConversion<CC::ReturnType::CppString, char>("\"non_flag_3\""),
            CC::StringUtil::UTFConversion<CC::ReturnType::CppString, char>("\"non_flag_4\""),
            CC::StringUtil::UTFConversion<CC::ReturnType::CppString, char>("\"non_flag_5\""),
        };

        if ( idx >= nonFlags.size() )
        {
            throw std::out_of_range("arg index[" + std::to_string(idx) + "] is out of range.");
        }

        return nonFlags[idx];
    }

    template <size_t idx>
    void InvokeCallback(const CLP::CommandFlag& cf)
    {
        const std::vector<CallbackHelper>& callbackHelpers = GetCallbackHelpers();

        if ( idx >= callbackHelpers.size() )
        {
            throw std::out_of_range("arg index[" + std::to_string(idx) + "] is out of range.");
        }

        callbackHelpers[idx].Callback(cf);
    }

    class CaseMatrixElem
    {
    private:
        bool m_bValid;
        TestCaseMask m_FlagCase;
        TestCaseMask m_DataCase;
        size_t m_FlagCount;
        size_t m_DataCount;

    public:
        CaseMatrixElem(const bool v, const TestCaseMask fCase, const TestCaseMask dCase, const size_t fCount, const size_t dCount) noexcept :
            m_bValid(v),
            m_FlagCase(fCase),
            m_DataCase(dCase),
            m_FlagCount(fCount),
            m_DataCount(dCount)
        { }

        CaseMatrixElem(const CaseMatrixElem& src) noexcept :
            m_bValid(src.m_bValid),
            m_FlagCase(src.m_FlagCase),
            m_DataCase(src.m_DataCase),
            m_FlagCount(src.m_FlagCount),
            m_DataCount(src.m_DataCount)
        { }

        CaseMatrixElem(CaseMatrixElem&& src) noexcept :
            m_bValid(src.m_bValid),
            m_FlagCase(src.m_FlagCase),
            m_DataCase(src.m_DataCase),
            m_FlagCount(src.m_FlagCount),
            m_DataCount(src.m_DataCount)
        { }

        ~CaseMatrixElem() = default;

        CaseMatrixElem& operator=(const CaseMatrixElem& src) noexcept
        {
            if ( this != &src )
            {
                m_bValid = src.m_bValid;
                m_FlagCase = src.m_FlagCase;
                m_DataCase = src.m_DataCase;
                m_FlagCount = src.m_FlagCount;
                m_DataCount = src.m_DataCount;
            }

            return *this;
        }

        CaseMatrixElem& operator=(CaseMatrixElem&& src) noexcept
        {
            if ( this != &src )
            {
                m_bValid = src.m_bValid;
                m_FlagCase = src.m_FlagCase;
                m_DataCase = src.m_DataCase;
                m_FlagCount = src.m_FlagCount;
                m_DataCount = src.m_DataCount;
            }

            return *this;
        }

        bool IsValid() const noexcept
        {
            return m_bValid;
        }

        TestCaseMask GetFlagCase() const noexcept
        {
            return m_FlagCase;
        }

        TestCaseMask GetDataCase() const noexcept
        {
            return m_DataCase;
        }

        size_t GetFlagCount() const noexcept
        {
            return m_FlagCount;
        }

        size_t GetDataCount() const noexcept
        {
            return m_DataCount;
        }
    };

    std::vector<std::vector<CaseMatrixElem>> BuildTestCaseMatrix()
    {
        constexpr auto mt = [ ](const bool v, const size_t f = 0, const size_t d = 0) -> std::tuple<bool, size_t, size_t>
        {
            return std::make_tuple(v, f, d);
        };

        static const std::vector<std::vector<std::tuple<bool, size_t, size_t>>> validitySizeMatrix
        {

/*

            |----------------------------- No-Match Case -----------------------|---------------------------- Match Case ---------------------------|

                    O/O                O/M              M/M              A/M             O/O                O/M              M/M              A/M
*/
/*  |---  */
/*  | O/O */{ mt(true, 0, 0),  mt(false, 0, 0), mt(false, 0, 0), mt(true, 0, 0),  mt(true, 1, 0),  mt(false, 0, 0), mt(false, 0, 0), mt(false, 0, 0) },
/*  |     */
/* N| O/M */{ mt(false, 0, 0), mt(true, 4, 3),  mt(true, 2, 1),  mt(false, 0, 0), mt(false, 0, 0), mt(true, 1, 0),  mt(true, 3, 2),  mt(true, 5, 4)  },
/*  |     */
/* M| M/M */{ mt(false, 0, 0), mt(true, 4, 2),  mt(true, 2, 1),  mt(false, 0, 0), mt(false, 0, 0), mt(false, 0, 0), mt(true, 3, 2),  mt(true, 5, 3)  },
/*  |     */
/* C| A/M */{ mt(true, 0, 0),  mt(true, 4, 0),  mt(true, 2, 0),  mt(true, 0, 0),  mt(false, 0, 0), mt(false, 0, 0), mt(true, 3, 0),  mt(true, 5, 0)  },
/*  |---  */
/*  | O/O */{ mt(false, 0, 0), mt(false, 0, 0), mt(false, 0, 0), mt(false, 0, 0), mt(true, 1, 1),  mt(false, 0, 0), mt(false, 0, 0), mt(false, 0, 0) },
/*  |     */
/* M| O/M */{ mt(false, 0, 0), mt(true, 4, 1),  mt(true, 2, 1),  mt(false, 0, 0), mt(false, 0, 0), mt(true, 1, 1),  mt(true, 3, 1),  mt(true, 5, 1)  },
/*  |     */
/* C| M/M */{ mt(false, 0, 0), mt(true, 4, 2),  mt(true, 2, 1),  mt(false, 0, 0), mt(false, 0, 0), mt(false, 0, 0), mt(true, 3, 2),  mt(true, 5, 3)  },
/*  |     */
/*  | A/M */{ mt(false, 0, 0), mt(true, 4, 4),  mt(true, 2, 2),  mt(false, 0, 0), mt(false, 0, 0), mt(false, 0, 0), mt(true, 3, 3),  mt(true, 5, 5)  }
/*  |---  */
        };

        std::vector<std::vector<CaseMatrixElem>> caseMatrix;
        for ( TestCaseMask flagCase = TestCaseMask::BEGIN; flagCase != TestCaseMask::MAX; INCREMENT_TEST_CASE_MASK(flagCase) )
        {
            std::vector<CaseMatrixElem> caseMatrixRow;
            for ( TestCaseMask dataCase = TestCaseMask::BEGIN; dataCase != TestCaseMask::MAX; INCREMENT_TEST_CASE_MASK(dataCase) )
            {
                const size_t flagIdx = static_cast<size_t>(flagCase);
                const size_t dataIdx = static_cast<size_t>(dataCase);
                const std::tuple<bool, size_t, size_t>& t = validitySizeMatrix[flagIdx][dataIdx];

                caseMatrixRow.push_back(CaseMatrixElem(std::get<0>(t), flagCase, dataCase, std::get<1>(t), std::get<2>(t)));
            }

            caseMatrix.push_back(std::move(caseMatrixRow));
        }

        return caseMatrix;
    }

    const std::vector<std::vector<CaseMatrixElem>>& GetTestCaseMatrix()
    {
        static const std::vector<std::vector<CaseMatrixElem>> caseMatrix = BuildTestCaseMatrix();
        return caseMatrix;
    }

    const CaseMatrixElem& GetTestCaseMatrixElement(const TestCaseMask& flagCase, const TestCaseMask& dataCase)
    {
        const size_t dataCaseNum = static_cast<size_t>(dataCase);
        const size_t flagCaseNum = static_cast<size_t>(flagCase);

        if ( dataCaseNum >= 8 || flagCaseNum >= 8 || !GetTestCaseMatrix()[dataCaseNum][flagCaseNum].IsValid() )
        {
            throw std::invalid_argument("invalid case argument - flag[" + std::to_string(flagCaseNum) + "] data[" + std::to_string(dataCaseNum) + "].");
        }

        return GetTestCaseMatrix()[flagCaseNum][dataCaseNum];
    }

    
    std::vector<std::string> GetTestCmdLineArgs(const TestCaseMask& flagCase, const TestCaseMask& dataCase)
    {
        std::vector<std::string> args;
        const CaseMatrixElem& elem = GetTestCaseMatrixElement(flagCase, dataCase);

        const size_t flagCount = elem.GetFlagCount();
        size_t dataCount = elem.GetDataCount();
        size_t extraCount = (flagCount > 0) ? flagCount - 1 : 0;

        if ( extraCount != 0 )
        {
            --extraCount;
            args.push_back(GetNonRegisteredFlagString(0));
        }

        for ( size_t i = 0; i < flagCount; i++ )
        {
            args.push_back(GetTestFlagString(i));

            if ( dataCount != 0 && dataCount + i >= flagCount )
            {
                --dataCount;
                args.push_back(GetTestFlagDataString(i));

                if ( extraCount != 0 )
                {
                    --extraCount;
                    args.push_back(GetNonRegisteredFlagString(0));
                }
            }
        }

        return args;
    }

    // Build and return vector of required test CommandFlag objects
    std::vector<CLP::CommandFlagPtr> BuildTestFlags(bool flagOpt, bool dataAcpt, bool dataOpt)
    {
        std::vector<CLP::CommandFlagPtr> flags;

        for ( size_t i = 0; i < 5; i++ )
        {
            auto flag = CC::MakeSharedPointer<CLP::CommandFlag>(GetTestFlagString(i));

            flag->SetCallbackFunction(std::bind(&CallbackHelper::Callback, &GetCallbackHelpers()[i], std::placeholders::_1));
            flag->SetFlagOptional(flagOpt);
            flag->SetFlagDataAccepted(dataAcpt);
            flag->SetFlagDataOptional(dataOpt);

            flags.push_back(std::move(flag));
        }

        return flags;
    }

    // Helper macro for common test cleanup steps.
#define COMMON_TEST_CLEANUP()                      \
    CLP::CommandParser::GetInstance().Clear(); \
    for ( auto& obj : GetCallbackHelpers() )    \
    {                                               \
        obj.ResetFlag();                           \
    }

    // Helper macro for common test setup steps.
#define COMMON_TEST_SETUP(flagCase, dataCase, flagOpt, dataAcpt, dataOpt)       \
    COMMON_TEST_CLEANUP();                                                     \
    for ( const auto& flag : BuildTestFlags(flagOpt, dataAcpt, dataOpt) )    \
    {                                                                           \
        CLP::CommandParser::GetInstance().RegisterCommandFlag(flag);        \
    }


    template <TestCaseMask flagCase, TestCaseMask dataCase, bool flagOpt, bool dataAcpt, bool dataOpt>
    UnitTestResult ParserPermutationTest()
    {
        const std::vector<CLP::CommandFlagPtr> registeredFlags = CLP::CommandParser::GetInstance().GetRegisteredCommandFlags();
        const CaseMatrixElem& elem = GetTestCaseMatrixElement(flagCase, dataCase);
        const size_t flagCount = elem.GetFlagCount();
        size_t dataCount = elem.GetDataCount();

        bool threw = false;
        std::vector<std::string> cmds = GetTestCmdLineArgs(flagCase, dataCase);

        COMMON_TEST_SETUP(flagCase, dataCase, flagOpt, dataAcpt, dataOpt);

        // Attempt to parse the mocked-up command-line arguments.
        try
        {
            CLP::CommandParser::GetInstance().ParseCommandLine(cmds);
        }
        catch ( const std::invalid_argument& )
        {
            threw = true;
        }
        catch ( const std::logic_error& e )
        {
            SUTL_TEST_EXCEPTION(e.what());
        }
        catch ( const std::exception& e )
        {
            SUTL_TEST_EXCEPTION(e.what());
        }

        for ( size_t i = 0; i < registeredFlags.size(); i++ )
        {
            const CLP::CommandFlagPtr& flag = registeredFlags[i];
            bool expectingFlagMatch = !cmds.empty() && (i < flagCount || !flagOpt);
            bool expectingFlagData = expectingFlagMatch && dataAcpt && (!dataOpt || ((dataCount + i) >= flagCount));

            SUTL_TEST_ASSERT(flag->IsFlagDataAccepted() == dataAcpt);
            SUTL_TEST_ASSERT(flag->IsFlagDataOptional() == dataOpt);
            SUTL_TEST_ASSERT(flag->IsFlagOptional() == flagOpt);

            if ( !threw )
            {
                SUTL_TEST_ASSERT(flag->IsFlagPresent() == expectingFlagMatch);
            }
            
            SUTL_TEST_ASSERT(flag->IsCallbackFunctionTriggered() == (expectingFlagMatch && !threw));
            SUTL_TEST_ASSERT(threw || !expectingFlagData || (flag->IsFlagDataPresent() && flag->GetFlagData() == GetTestFlagDataString(i)));
        }

        COMMON_TEST_CLEANUP();

        SUTL_TEST_SUCCESS();
    }
}