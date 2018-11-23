#include <CommandFlagTests.h>

#include <CommandFlag.h>

#include <StringUtil.hpp>

namespace CommandFlagTests
{
    std::list<std::function<UnitTestResult(void)>> GetUnitTests( )
    {
        static const std::list<std::function<UnitTestResult(void)>> tests
        {
            CtorTests::FlagName<utf8>,
            CtorTests::FlagName<utf16>,
            CtorTests::FullList<utf8>,
            CtorTests::FullList<utf16>,
            CtorTests::Copy<utf8>,
            CtorTests::Copy<utf16>,
            CtorTests::Move<utf8>,
            CtorTests::Move<utf16>
        };

        return tests;
    }

    namespace CtorTests
    {
        template <class T>
        UnitTestResult FlagName( )
        {
            std::unique_ptr<CLP::CommandFlag<T>> pCmdFlag;
            std::basic_string<T> flagName;

            try
            {
                flagName = StringUtil::UTFConversion::ToString<T>("/testFlag");
            }
            catch ( const std::exception& e )
            {
                SUTL_SETUP_EXCEPTION(e.what( ));
            }

            try
            {
                pCmdFlag = std::make_unique<CLP::CommandFlag<T>>(flagName);
            }
            catch ( const std::exception& e )
            {
                SUTL_SETUP_EXCEPTION(e.what( ));
            }

            SUTL_TEST_ASSERT(pCmdFlag->GetFlag( ) == flagName);
            SUTL_TEST_ASSERT(pCmdFlag->GetFlagData( ).empty( ));
            SUTL_TEST_ASSERT(!pCmdFlag->GetCallbackFunction( ));
            SUTL_TEST_ASSERT(pCmdFlag->IsFlagOptional( ) == true);
            SUTL_TEST_ASSERT(pCmdFlag->IsFlagDataAccepted( ) == false);
            SUTL_TEST_ASSERT(pCmdFlag->IsFlagDataOptional( ) == false);
            SUTL_TEST_ASSERT(pCmdFlag->IsFlagPresent( ) == false);
            SUTL_TEST_ASSERT(pCmdFlag->IsFlagDataPresent( ) == false);

            SUTL_TEST_SUCCESS( );
        }

        template <class T>
        UnitTestResult FullList( )
        {
            std::unique_ptr<CLP::CommandFlag<T>> pCmdFlag;
            std::basic_string<T> flagName;
            bool callbackSuccessful = false;
            auto callbackFunction = [&callbackSuccessful] (const CLP::CommandFlag<T>&) -> void
            {
                callbackSuccessful = true;
            };

            try
            {
                flagName = StringUtil::UTFConversion::ToString<T>("/testFlag");
            }
            catch ( const std::exception& e )
            {
                SUTL_SETUP_EXCEPTION(e.what( ));
            }

            try
            {
                pCmdFlag = std::make_unique<CLP::CommandFlag<T>>(flagName, callbackFunction, true, true, false);
            }
            catch ( const std::exception& e )
            {
                SUTL_SETUP_EXCEPTION(e.what( ));
            }

            SUTL_TEST_ASSERT(pCmdFlag->GetFlag( ) == flagName);
            SUTL_TEST_ASSERT(pCmdFlag->GetFlagData( ).empty( ));
            SUTL_TEST_ASSERT(pCmdFlag->GetCallbackFunction( ));
            try
            {
                pCmdFlag->GetCallbackFunction( )(*pCmdFlag);
            }
            catch ( const std::exception& e )
            {
                SUTL_TEST_EXCEPTION(e.what( ));
            }
            SUTL_TEST_ASSERT(callbackSuccessful);
            SUTL_TEST_ASSERT(pCmdFlag->IsFlagOptional( ) == true);
            SUTL_TEST_ASSERT(pCmdFlag->IsFlagDataAccepted( ) == true);
            SUTL_TEST_ASSERT(pCmdFlag->IsFlagDataOptional( ) == false);
            SUTL_TEST_ASSERT(pCmdFlag->IsFlagPresent( ) == false);
            SUTL_TEST_ASSERT(pCmdFlag->IsFlagDataPresent( ) == false);

            SUTL_TEST_SUCCESS( );
        }

        template <class T>
        UnitTestResult Copy( )
        {
            std::unique_ptr<CLP::CommandFlag<T>> pCmdFlag;
            std::unique_ptr<CLP::CommandFlag<T>> pCopyFlag;
            std::basic_string<T> flagName;

            bool callbackSuccessful = false;
            auto callbackFunction = [&callbackSuccessful] (const CLP::CommandFlag<T>&) -> void
            {
                callbackSuccessful = true;
            };

            try
            {
                flagName = StringUtil::UTFConversion::ToString<T>("/testFlag");
            }
            catch ( const std::exception& e )
            {
                SUTL_SETUP_EXCEPTION(e.what( ));
            }

            // Create initial CommandFlag.
            try
            {
                pCmdFlag = std::make_unique<CLP::CommandFlag<T>>(flagName, callbackFunction, true, true, false);
            }
            catch ( const std::exception& e )
            {
                SUTL_SETUP_EXCEPTION(e.what( ));
            }

            // Ensure initial conditions are as expected.
            SUTL_SETUP_ASSERT(pCmdFlag->GetFlag( ) == flagName);
            SUTL_SETUP_ASSERT(pCmdFlag->GetFlagData( ).empty( ));
            SUTL_SETUP_ASSERT(pCmdFlag->GetCallbackFunction( ));
            callbackSuccessful = false;
            try
            {
                pCmdFlag->GetCallbackFunction( )(*pCmdFlag);
            }
            catch ( const std::exception& e )
            {
                SUTL_SETUP_EXCEPTION(e.what( ));
            }
            SUTL_SETUP_ASSERT(callbackSuccessful);
            SUTL_SETUP_ASSERT(pCmdFlag->IsFlagOptional( ) == true);
            SUTL_SETUP_ASSERT(pCmdFlag->IsFlagDataAccepted( ) == true);
            SUTL_SETUP_ASSERT(pCmdFlag->IsFlagDataOptional( ) == false);
            SUTL_SETUP_ASSERT(pCmdFlag->IsFlagPresent( ) == false);
            SUTL_SETUP_ASSERT(pCmdFlag->IsFlagDataPresent( ) == false);

            // Create new CommandFlag via copy ctor.
            try
            {
                pCopyFlag = std::make_unique<CLP::CommandFlag<T>>(*pCmdFlag);
            }
            catch ( const std::exception& e )
            {
                SUTL_SETUP_EXCEPTION(e.what( ));
            }

            // Ensure pCmdFlag was not modified by the copy.
            SUTL_TEST_ASSERT(pCmdFlag != pCopyFlag);
            SUTL_TEST_ASSERT(pCmdFlag->GetFlag( ) == flagName);
            SUTL_TEST_ASSERT(pCmdFlag->GetFlagData( ).empty( ));
            SUTL_TEST_ASSERT(pCmdFlag->GetCallbackFunction( ));
            callbackSuccessful = false;
            try
            {
                pCmdFlag->GetCallbackFunction( )(*pCmdFlag);
            }
            catch ( const std::exception& e )
            {
                SUTL_TEST_EXCEPTION(e.what( ));
            }
            SUTL_TEST_ASSERT(callbackSuccessful);
            SUTL_TEST_ASSERT(pCmdFlag->IsFlagOptional( ) == true);
            SUTL_TEST_ASSERT(pCmdFlag->IsFlagDataAccepted( ) == true);
            SUTL_TEST_ASSERT(pCmdFlag->IsFlagDataOptional( ) == false);
            SUTL_TEST_ASSERT(pCmdFlag->IsFlagPresent( ) == false);
            SUTL_TEST_ASSERT(pCmdFlag->IsFlagDataPresent( ) == false);

            // Ensure pCopyFlag has the same values as pCmdFlag.
            SUTL_TEST_ASSERT(pCopyFlag->GetFlag( ) == pCmdFlag->GetFlag( ));
            SUTL_TEST_ASSERT(pCopyFlag->GetFlagData( ) == pCmdFlag->GetFlagData( ));
            SUTL_TEST_ASSERT(pCopyFlag->GetCallbackFunction( ));
            callbackSuccessful = false;
            try
            {
                pCopyFlag->GetCallbackFunction( )(*pCopyFlag);
            }
            catch ( const std::exception& e )
            {
                SUTL_TEST_EXCEPTION(e.what( ));
            }
            SUTL_TEST_ASSERT(callbackSuccessful);
            SUTL_TEST_ASSERT(pCopyFlag->IsFlagOptional( ) == pCmdFlag->IsFlagOptional( ));
            SUTL_TEST_ASSERT(pCopyFlag->IsFlagDataAccepted( ) == pCmdFlag->IsFlagDataAccepted( ));
            SUTL_TEST_ASSERT(pCopyFlag->IsFlagDataOptional( ) == pCmdFlag->IsFlagDataOptional( ));
            SUTL_TEST_ASSERT(pCopyFlag->IsFlagPresent( ) == pCmdFlag->IsFlagPresent( ));
            SUTL_TEST_ASSERT(pCopyFlag->IsFlagDataPresent( ) == pCmdFlag->IsFlagDataPresent( ));

            SUTL_TEST_SUCCESS( );
        }

        template <class T>
        UnitTestResult Move( )
        {
            std::unique_ptr<CLP::CommandFlag<T>> pCmdFlag;
            std::unique_ptr<CLP::CommandFlag<T>> pMoveFlag;
            std::basic_string<T> flagName;
            bool threw = false;

            bool callbackSuccessful = false;
            auto callbackFunction = [&callbackSuccessful] (const CLP::CommandFlag<T>&) -> void
            {
                callbackSuccessful = true;
            };

            try
            {
                flagName = StringUtil::UTFConversion::ToString<T>("/testFlag");
            }
            catch ( const std::exception& e )
            {
                SUTL_SETUP_EXCEPTION(e.what( ));
            }

            // Create initial CommandFlag.
            try
            {
                pCmdFlag = std::make_unique<CLP::CommandFlag<T>>(flagName, callbackFunction, true, true, false);
            }
            catch ( const std::exception& e )
            {
                SUTL_SETUP_EXCEPTION(e.what( ));
            }

            // Ensure initial conditions are as expected.
            SUTL_SETUP_ASSERT(pCmdFlag->GetFlag( ) == flagName);
            SUTL_SETUP_ASSERT(pCmdFlag->GetFlagData( ).empty( ));
            SUTL_SETUP_ASSERT(pCmdFlag->GetCallbackFunction( ));
            callbackSuccessful = false;
            try
            {
                pCmdFlag->GetCallbackFunction( )(*pCmdFlag);
            }
            catch ( const std::exception& e )
            {
                SUTL_SETUP_EXCEPTION(e.what( ));
            }
            SUTL_SETUP_ASSERT(callbackSuccessful);
            SUTL_SETUP_ASSERT(pCmdFlag->IsFlagOptional( ) == true);
            SUTL_SETUP_ASSERT(pCmdFlag->IsFlagDataAccepted( ) == true);
            SUTL_SETUP_ASSERT(pCmdFlag->IsFlagDataOptional( ) == false);
            SUTL_SETUP_ASSERT(pCmdFlag->IsFlagPresent( ) == false);
            SUTL_SETUP_ASSERT(pCmdFlag->IsFlagDataPresent( ) == false);

            // Create new CommandFlag via copy ctor.
            try
            {
                pMoveFlag = std::make_unique<CLP::CommandFlag<T>>(std::move(*pCmdFlag));
            }
            catch ( const std::exception& e )
            {
                SUTL_SETUP_EXCEPTION(e.what( ));
            }

            // Ensure pCmdFlag was modified by the move.
            SUTL_TEST_ASSERT(pCmdFlag != pMoveFlag);
            SUTL_TEST_ASSERT(pCmdFlag->GetFlag( ).empty( ));
            SUTL_TEST_ASSERT(pCmdFlag->GetFlagData( ).empty( ));
            SUTL_TEST_ASSERT(!pCmdFlag->GetCallbackFunction( ));
            callbackSuccessful = false;
            try
            {
                pCmdFlag->GetCallbackFunction( )(*pCmdFlag);
            }
            catch ( const std::exception& )
            {
                threw = true;
            }
            SUTL_TEST_ASSERT(!callbackSuccessful);
            SUTL_TEST_ASSERT(threw);
            SUTL_TEST_ASSERT(pCmdFlag->IsFlagOptional( ) == true);
            SUTL_TEST_ASSERT(pCmdFlag->IsFlagDataAccepted( ) == false);
            SUTL_TEST_ASSERT(pCmdFlag->IsFlagDataOptional( ) == false);
            SUTL_TEST_ASSERT(pCmdFlag->IsFlagPresent( ) == false);
            SUTL_TEST_ASSERT(pCmdFlag->IsFlagDataPresent( ) == false);

            // Ensure pMoveFlag has the same values as pCmdFlag.
            SUTL_TEST_ASSERT(pMoveFlag->GetFlag( ) != pCmdFlag->GetFlag( ));
            SUTL_TEST_ASSERT(pMoveFlag->GetFlagData( ) == pCmdFlag->GetFlagData( ));
            SUTL_TEST_ASSERT(pMoveFlag->GetCallbackFunction( ));
            callbackSuccessful = false;
            try
            {
                pMoveFlag->GetCallbackFunction( )(*pMoveFlag);
            }
            catch ( const std::exception& e )
            {
                SUTL_TEST_EXCEPTION(e.what( ));
            }
            SUTL_TEST_ASSERT(callbackSuccessful);
            SUTL_TEST_ASSERT(pMoveFlag->IsFlagOptional( ) == pCmdFlag->IsFlagOptional( ));
            SUTL_TEST_ASSERT(pMoveFlag->IsFlagDataAccepted( ) != pCmdFlag->IsFlagDataAccepted( ));
            SUTL_TEST_ASSERT(pMoveFlag->IsFlagDataOptional( ) == pCmdFlag->IsFlagDataOptional( ));
            SUTL_TEST_ASSERT(pMoveFlag->IsFlagPresent( ) == pCmdFlag->IsFlagPresent( ));
            SUTL_TEST_ASSERT(pMoveFlag->IsFlagDataPresent( ) == pCmdFlag->IsFlagDataPresent( ));

            SUTL_TEST_SUCCESS( );
        }
    }
}