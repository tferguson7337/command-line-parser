// SUTL
#include <UnitTestRunner.h>

// Tests
#include <CommandFlagTests.h>
#include <CommandParserTests.h>

void AddUnitTests(UnitTestRunner& utr)
{
    utr.AddUnitTests(CommandFlagTests::GetUnitTests());
    utr.AddUnitTests(CommandParserTests::GetUnitTests());
}

int main()
{
    UnitTestRunner utr("CLP Tests");
    AddUnitTests(utr);
    utr.RunUnitTests();
    return static_cast<int>(utr.GetTestSetData().GetTestFailureCount());
}