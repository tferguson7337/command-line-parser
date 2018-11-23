#include <CommandParserTests.h>

#include <CommandParser.h>

#include <StringUtil.hpp>

namespace CommandParserTests
{
    std::list<std::function<UnitTestResult(void)>> GetUnitTests( )
    {
        static const std::list<std::function<UnitTestResult(void)>> tests
        {
            /// UTF-8 Test Functions \\\

            OptionalFlag::OptionalData::NoMatchOneOfOne<utf8>,
            OptionalFlag::OptionalData::NoMatchOneOfMany<utf8>,
            OptionalFlag::OptionalData::NoMatchManyOfMany<utf8>,
            OptionalFlag::OptionalData::NoMatchAllOfMany<utf8>,
            OptionalFlag::OptionalData::MatchOneOfOne<utf8>,
            OptionalFlag::OptionalData::MatchOneOfMany<utf8>,
            OptionalFlag::OptionalData::MatchManyOfMany<utf8>,
            OptionalFlag::OptionalData::MatchAllOfMany<utf8>,

            OptionalFlag::RequiredData::NoMatchOneOfOne<utf8>,
            OptionalFlag::RequiredData::NoMatchOneOfMany<utf8>,
            OptionalFlag::RequiredData::NoMatchManyOfMany<utf8>,
            OptionalFlag::RequiredData::NoMatchAllOfMany<utf8>,
            OptionalFlag::RequiredData::MatchOneOfOne<utf8>,
            OptionalFlag::RequiredData::MatchOneOfMany<utf8>,
            OptionalFlag::RequiredData::MatchManyOfMany<utf8>,
            OptionalFlag::RequiredData::MatchAllOfMany<utf8>,

            OptionalFlag::UnacceptedData::NoMatchOneOfOne<utf8>,
            OptionalFlag::UnacceptedData::NoMatchOneOfMany<utf8>,
            OptionalFlag::UnacceptedData::NoMatchManyOfMany<utf8>,
            OptionalFlag::UnacceptedData::NoMatchAllOfMany<utf8>,
            OptionalFlag::UnacceptedData::MatchOneOfOne<utf8>,
            OptionalFlag::UnacceptedData::MatchOneOfMany<utf8>,
            OptionalFlag::UnacceptedData::MatchManyOfMany<utf8>,
            OptionalFlag::UnacceptedData::MatchAllOfMany<utf8>,

            RequiredFlag::OptionalData::NoMatchOneOfOne<utf8>,
            RequiredFlag::OptionalData::NoMatchOneOfMany<utf8>,
            RequiredFlag::OptionalData::NoMatchManyOfMany<utf8>,
            RequiredFlag::OptionalData::NoMatchAllOfMany<utf8>,
            RequiredFlag::OptionalData::MatchOneOfOne<utf8>,
            RequiredFlag::OptionalData::MatchOneOfMany<utf8>,
            RequiredFlag::OptionalData::MatchManyOfMany<utf8>,
            RequiredFlag::OptionalData::MatchAllOfMany<utf8>,

            RequiredFlag::RequiredData::NoMatchOneOfOne<utf8>,
            RequiredFlag::RequiredData::NoMatchOneOfMany<utf8>,
            RequiredFlag::RequiredData::NoMatchManyOfMany<utf8>,
            RequiredFlag::RequiredData::NoMatchAllOfMany<utf8>,
            RequiredFlag::RequiredData::MatchOneOfOne<utf8>,
            RequiredFlag::RequiredData::MatchOneOfMany<utf8>,
            RequiredFlag::RequiredData::MatchManyOfMany<utf8>,
            RequiredFlag::RequiredData::MatchAllOfMany<utf8>,

            RequiredFlag::UnacceptedData::NoMatchOneOfOne<utf8>,
            RequiredFlag::UnacceptedData::NoMatchOneOfMany<utf8>,
            RequiredFlag::UnacceptedData::NoMatchManyOfMany<utf8>,
            RequiredFlag::UnacceptedData::NoMatchAllOfMany<utf8>,
            RequiredFlag::UnacceptedData::MatchOneOfOne<utf8>,
            RequiredFlag::UnacceptedData::MatchOneOfMany<utf8>,
            RequiredFlag::UnacceptedData::MatchManyOfMany<utf8>,
            RequiredFlag::UnacceptedData::MatchAllOfMany<utf8>,

            /// UTF-16 Test Functions \\\

            OptionalFlag::OptionalData::NoMatchOneOfOne<utf16>,
            OptionalFlag::OptionalData::NoMatchOneOfMany<utf16>,
            OptionalFlag::OptionalData::NoMatchManyOfMany<utf16>,
            OptionalFlag::OptionalData::NoMatchAllOfMany<utf16>,
            OptionalFlag::OptionalData::MatchOneOfOne<utf16>,
            OptionalFlag::OptionalData::MatchOneOfMany<utf16>,
            OptionalFlag::OptionalData::MatchManyOfMany<utf16>,
            OptionalFlag::OptionalData::MatchAllOfMany<utf16>,

            OptionalFlag::RequiredData::NoMatchOneOfOne<utf16>,
            OptionalFlag::RequiredData::NoMatchOneOfMany<utf16>,
            OptionalFlag::RequiredData::NoMatchManyOfMany<utf16>,
            OptionalFlag::RequiredData::NoMatchAllOfMany<utf16>,
            OptionalFlag::RequiredData::MatchOneOfOne<utf16>,
            OptionalFlag::RequiredData::MatchOneOfMany<utf16>,
            OptionalFlag::RequiredData::MatchManyOfMany<utf16>,
            OptionalFlag::RequiredData::MatchAllOfMany<utf16>,

            OptionalFlag::UnacceptedData::NoMatchOneOfOne<utf16>,
            OptionalFlag::UnacceptedData::NoMatchOneOfMany<utf16>,
            OptionalFlag::UnacceptedData::NoMatchManyOfMany<utf16>,
            OptionalFlag::UnacceptedData::NoMatchAllOfMany<utf16>,
            OptionalFlag::UnacceptedData::MatchOneOfOne<utf16>,
            OptionalFlag::UnacceptedData::MatchOneOfMany<utf16>,
            OptionalFlag::UnacceptedData::MatchManyOfMany<utf16>,
            OptionalFlag::UnacceptedData::MatchAllOfMany<utf16>,

            RequiredFlag::OptionalData::NoMatchOneOfOne<utf16>,
            RequiredFlag::OptionalData::NoMatchOneOfMany<utf16>,
            RequiredFlag::OptionalData::NoMatchManyOfMany<utf16>,
            RequiredFlag::OptionalData::NoMatchAllOfMany<utf16>,
            RequiredFlag::OptionalData::MatchOneOfOne<utf16>,
            RequiredFlag::OptionalData::MatchOneOfMany<utf16>,
            RequiredFlag::OptionalData::MatchManyOfMany<utf16>,
            RequiredFlag::OptionalData::MatchAllOfMany<utf16>,

            RequiredFlag::RequiredData::NoMatchOneOfOne<utf16>,
            RequiredFlag::RequiredData::NoMatchOneOfMany<utf16>,
            RequiredFlag::RequiredData::NoMatchManyOfMany<utf16>,
            RequiredFlag::RequiredData::NoMatchAllOfMany<utf16>,
            RequiredFlag::RequiredData::MatchOneOfOne<utf16>,
            RequiredFlag::RequiredData::MatchOneOfMany<utf16>,
            RequiredFlag::RequiredData::MatchManyOfMany<utf16>,
            RequiredFlag::RequiredData::MatchAllOfMany<utf16>,

            RequiredFlag::UnacceptedData::NoMatchOneOfOne<utf16>,
            RequiredFlag::UnacceptedData::NoMatchOneOfMany<utf16>,
            RequiredFlag::UnacceptedData::NoMatchManyOfMany<utf16>,
            RequiredFlag::UnacceptedData::NoMatchAllOfMany<utf16>,
            RequiredFlag::UnacceptedData::MatchOneOfOne<utf16>,
            RequiredFlag::UnacceptedData::MatchOneOfMany<utf16>,
            RequiredFlag::UnacceptedData::MatchManyOfMany<utf16>,
            RequiredFlag::UnacceptedData::MatchAllOfMany<utf16>,
        };

        return tests;
    };

    /// Test Helpers \\\

    // Callback Function Helper
    template <class T>
    class CallbackHelper
    {
    private:
        bool m_bCallbackTriggered;

    public:
        CallbackHelper( ) : m_bCallbackTriggered(false)
        { }

        ~CallbackHelper( ) = default;

        void Callback(const CLP::CommandFlag<T>&) noexcept
        {
            m_bCallbackTriggered = true;
        }

        bool CallbackTriggered( ) const noexcept
        {
            return m_bCallbackTriggered;
        }

        void ResetFlag( ) noexcept
        {
            m_bCallbackTriggered = false;
        }
    };

    // Return 
    template <class T>
    std::vector<CallbackHelper<T>>& GetCallbackHelpers( )
    {
        static std::vector<CallbackHelper<T>> vCallbackHelpers(5);

        return vCallbackHelpers;
    }

    // 
    template <class T>
    const std::basic_string<T>& GetTestFlagString(const size_t flagNum)
    {
        static const std::vector<std::basic_string<T>> flags
        {
            StringUtil::Copy::ToString<T>("/flag1"),
            StringUtil::Copy::ToString<T>("/flag2"),
            StringUtil::Copy::ToString<T>("/flag3"),
            StringUtil::Copy::ToString<T>("/flag4"),
            StringUtil::Copy::ToString<T>("/flag5"),
        };

        if ( flagNum >= flags.size( ) )
        {
            throw std::out_of_range(__FUNCTION__": arg flag number[" + std::to_string(flagNum) "] is out of range.");
        }

        return flags;
    }

    template <class T>
    const std::basic_string<T>& GetTestFlagDataString(const size_t flagNum)
    {
        static const std::vector<std::basic_string<T>> data
        {
            StringUtil::Copy::ToString<T>("\"flag_data_1\""),
            StringUtil::Copy::ToString<T>("\"flag_data_2\""),
            StringUtil::Copy::ToString<T>("\"flag_data_3\""),
            StringUtil::Copy::ToString<T>("\"flag_data_4\""),
            StringUtil::Copy::ToString<T>("\"flag_data_5\""),
        };

        if ( flagNum >= flags.size( ) )
        {
            throw std::out_of_range(__FUNCTION__": arg flag number[" + std::to_string(flagNum) "] is out of range.");
        }

        return data;
    }

    // Build and return vector of many test CommandFlag objects
    template <class T>
    std::vector<CLP::CommandFlag<T>> GetTestFlags(bool flagOpt, bool dataAcpt, bool dataOpt)
    {
        const std::vector<CLP::CommandFlag<T>> flags
        {
            CLP::CommandFlag<T>(
                GetTestFlagString<T>(0),
                GetCallbackHelpers<T>( )[0].Callback,
                flagOpt, dataAcpt, dataOpt
                ),

            CLP::CommandFlag<T>(
                GetTestFlagString<T>(1),
                GetCallbackHelpers<T>( )[1].Callback,
                flagOpt, dataAcpt, dataOpt
                ),

            CLP::CommandFlag<T>(
                GetTestFlagString<T>(2),
                GetCallbackHelpers<T>( )[2].Callback,
                flagOpt, dataAcpt, dataOpt
                ),

            CLP::CommandFlag<T>(
                GetTestFlagString<T>(3),
                GetCallbackHelpers<T>( )[3].Callback,
                flagOpt, dataAcpt, dataOpt
                ),

            CLP::CommandFlag<T>(
                GetTestFlagString<T>(4),
                GetCallbackHelpers<T>( )[4].Callback,
                flagOpt, dataAcpt, dataOpt
                ),
        };

        return flags;
    }

    // Helper macro for common test setup steps.
#define COMMON_TEST_SETUP(Quantity, flagOpt, dataAcpt, dataOpt)                     \
    for ( const auto& flag : GetQuantityTestFlags<T>(flagOpt, dataAcpt, dataOpt) )  \
    {                                                                               \
        CLP::CommandParser<T>::GetInstance( ).RegisterCommandFlag(flag);            \
    }

    // Helper macro for common test cleanup steps.
#define COMMON_TEST_CLEANUP( )                      \
    CLP::CommandParser<T>::GetInstance( ).Clear( ); \
    for ( auto& obj : GetCallbackHelpers<T>( ) )    \
    {                                               \
        obj.ResetFlag( );                           \
    }

    /// Test Function Definitions \\\

    /// Flag is optional.
    // Expected behavior:
    // If no token is found that matches the flag, the expectation is to *not* thrown an exception.
    namespace OptionalFlag
    {
        /// Additional Flag Data is optional.
        // Expected behavior: 
        // Additional token following a flag is treated as data unless it matches another registered flag.
        // If there is no following token, the expectation is to *not* throw an exception.
        namespace OptionalData
        {
            template <class T>
            std::vector<std::basic_string<T>> GetNoMatchOneCmdsData( )
            {
                static const std::vector<std::basic_string<T>> cmds
                {
                    GetTestFlagString<T>(0),
                    GetTestFlagDataString<T>(0),
                    GetTestFlagString<T>(1),
                    GetTestFlagDataString<T>(1),
                    GetTestFlagString<T>(2),
                    GetTestFlagDataString<T>(2),
                    GetTestFlagString<T>(3)
                };

                return cmds;
            }

            template <class T>
            std::vector<std::basic_string<T>> GetNoMatchManyCmds( )
            {
                static const std::vector<std::basic_string<T>> cmds
                { 
                    GetTestFlagString<T>(0),
                    GetTestFlagString<T>(1),
                    GetTestFlagDataString<T>(1),
                };

                return cmds;
            }

            template <class T>
            std::vector<std::basic_string<T>> GetNoMatchAllCmds( )
            {
                static const std::vector<std::basic_string<T>> cmds
                {

                };

                return cmds;
            }

            template <class T>
            std::vector<std::basic_string<T>> GetMatchOneCmds( )
            {
                static const std::vector<std::basic_string<T>> cmds
                {

                };

                return cmds;
            }

            template <class T>
            std::vector<std::basic_string<T>> GetMatchManyCmds( )
            {
                static const std::vector<std::basic_string<T>> cmds
                {

                };

                return cmds;
            }

            template <class T>
            std::vector<std::basic_string<T>> GetMatchAllCmds( )
            {
                static const std::vector<std::basic_string<T>> cmds
                {

                };

                return cmds;
            }

            /// Positive Test Cases \\\

            template <class T>
            UnitTestResult NoMatchOneOfOne( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            template <class T>
            UnitTestResult NoMatchOneOfMany( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            template <class T>
            UnitTestResult NoMatchManyOfMany( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            template <class T>
            UnitTestResult NoMatchAllOfMany( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            template <class T>
            UnitTestResult MatchOneOfOne( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            template <class T>
            UnitTestResult MatchOneOfMany( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            template <class T>
            UnitTestResult MatchManyOfMany( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            template <class T>
            UnitTestResult MatchAllOfMany( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }

        }

        /// Additional Flag Data is required.
        // Expected behavior: 
        // Additional token following a flag is treated as data unless it matches another registered flag.
        // If there is no following token, the expectation is to throw an exception.
        namespace RequiredData
        {
            /// Negative Test Cases \\\

            template <class T>
            UnitTestResult NoMatchOneOfOne( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            template <class T>
            UnitTestResult NoMatchOneOfMany( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            template <class T>
            UnitTestResult NoMatchManyOfMany( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            template <class T>
            UnitTestResult NoMatchAllOfMany( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            template <class T>
            UnitTestResult MatchOneOfMany( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            template <class T>
            UnitTestResult MatchManyOfMany( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            /// Positive Test Cases \\\

            template <class T>
            UnitTestResult MatchOneOfOne( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            template <class T>
            UnitTestResult MatchAllOfMany( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }

        }

        /// Additional Flag Data is unaccepted.
        // Expected behavior: 
        // Additional token following a flag that is not accepting data should match another expected flag.
        // If the additional token does not match any flag, the expectation is to throw an exception.
        namespace UnacceptedData
        {
            /// Negative Test Cases \\\

            template <class T>
            UnitTestResult NoMatchOneOfOne( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            template <class T>
            UnitTestResult NoMatchOneOfMany( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            template <class T>
            UnitTestResult NoMatchManyOfMany( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            template <class T>
            UnitTestResult NoMatchAllOfMany( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            template <class T>
            UnitTestResult MatchOneOfMany( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            template <class T>
            UnitTestResult MatchManyOfMany( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            /// Positive Test Cases \\\

            template <class T>
            UnitTestResult MatchOneOfOne( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            template <class T>
            UnitTestResult MatchAllOfMany( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }

        }
    }

    /// Flag is required.
    // Expected behavior:
    // If no token is found that matches the flag, the expectation is to thrown an exception.
    namespace RequiredFlag
    {
        /// Additional Flag Data is optional.
        // Expected behavior: 
        // Additional token following a flag is treated as data unless it matches another registered flag.
        // If there is no following token, the expectation is to *not* throw an exception.
        namespace OptionalData
        {
            /// Negative Test Cases \\\

            template <class T>
            UnitTestResult NoMatchOneOfOne( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            template <class T>
            UnitTestResult NoMatchOneOfMany( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            template <class T>
            UnitTestResult NoMatchManyOfMany( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            template <class T>
            UnitTestResult NoMatchAllOfMany( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            template <class T>
            UnitTestResult MatchOneOfMany( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            template <class T>
            UnitTestResult MatchManyOfMany( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            /// Positive Test Cases \\\

            template <class T>
            UnitTestResult MatchOneOfOne( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            template <class T>
            UnitTestResult MatchAllOfMany( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }

        }

        /// Additional Flag Data is required.
        // Expected behavior: 
        // Additional token following a flag is treated as data unless it matches another registered flag.
        // If there is no following token, the expectation is to throw an exception.
        namespace RequiredData
        {
            /// Negative Test Cases \\\

            template <class T>
            UnitTestResult NoMatchOneOfOne( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            template <class T>
            UnitTestResult NoMatchOneOfMany( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            template <class T>
            UnitTestResult NoMatchManyOfMany( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            template <class T>
            UnitTestResult NoMatchAllOfMany( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            template <class T>
            UnitTestResult MatchOneOfMany( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            template <class T>
            UnitTestResult MatchManyOfMany( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            /// Positive Test Cases \\\

            template <class T>
            UnitTestResult MatchOneOfOne( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            template <class T>
            UnitTestResult MatchAllOfMany( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }

        }

        /// Additional Flag Data is unaccepted.
        // Expected behavior: 
        // Additional token following a flag that is not accepting data should match another expected flag.
        // If the additional token does not match any flag, the expectation is to throw an exception.
        namespace UnacceptedData
        {
            /// Negative Test Cases \\\

            template <class T>
            UnitTestResult NoMatchOneOfOne( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            template <class T>
            UnitTestResult NoMatchOneOfMany( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            template <class T>
            UnitTestResult NoMatchManyOfMany( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            template <class T>
            UnitTestResult NoMatchAllOfMany( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            template <class T>
            UnitTestResult MatchOneOfMany( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            template <class T>
            UnitTestResult MatchManyOfMany( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            /// Positive Test Cases \\\

            template <class T>
            UnitTestResult MatchOneOfOne( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }


            template <class T>
            UnitTestResult MatchAllOfMany( )
            {
                SUTL_SKIP_TEST("Implementation Pending...");
            }

        }
    }
}