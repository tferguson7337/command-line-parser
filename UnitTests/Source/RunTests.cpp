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
    bool pass = false;

    UnitTestRunner utr("CLP Tests");

    AddUnitTests(utr);

    pass = utr.RunUnitTests();

    return 0;
}