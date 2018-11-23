// SUTL
#include <UnitTestRunner.h>

// Tests
#include <CommandFlagTests.h>
#include <CommandParserTests.h>

void AddUnitTests(UnitTestRunner<char>& utr)
{
    utr.AddUnitTests(CommandFlagTests::GetUnitTests( ));
    utr.AddUnitTests(CommandParserTests::GetUnitTests( ));
}

int main( )
{
    bool pass = false;

    UnitTestRunner<char> utr("CLP Tests");

    AddUnitTests(utr);

    pass = utr.RunUnitTests( );

    return pass ? 0 : -1;
}