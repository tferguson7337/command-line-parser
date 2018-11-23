#pragma once

#include <UnitTestResult.h>

#include <functional>
#include <list>

namespace CommandParserTests
{
    std::list<std::function<UnitTestResult(void)>> GetUnitTests( ); 

    /// Flag is optional.
    // Expected behavior:
    // If no token is found that matches the flag, the expectation is to *not* thrown an exception.
    namespace OptionalFlag
    {
        /// Additional Flag Data is optional.
        // Expected behavior: 
        // Additional token following a flag is treated as data, even if it matches another registered flag.
        // If there is no following token, the expectation is to *not* throw an exception.
        namespace OptionalData
        {
            // NoMatchXOfY means X/Y registered flags were not matched when parsing.
            // MatchXOfY means X/Y registered flags were matched when parsing.

            /// Positive Test Cases \\\

            template <class T>
            UnitTestResult NoMatchOneOfOne( );

            template <class T>
            UnitTestResult NoMatchOneOfMany( );

            template <class T>
            UnitTestResult NoMatchManyOfMany( );

            template <class T>
            UnitTestResult NoMatchAllOfMany( );

            template <class T>
            UnitTestResult MatchOneOfOne( );

            template <class T>
            UnitTestResult MatchOneOfMany( );

            template <class T>
            UnitTestResult MatchManyOfMany( );

            template <class T>
            UnitTestResult MatchAllOfMany( );
        }

        /// Additional Flag Data is required.
        // Expected behavior: 
        // Additional token following a flag is treated as data, even if it matches another registered flag.
        // If there is no following token, the expectation is to throw an exception.
        namespace RequiredData
        {
            // NoMatchXOfY means X/Y data for registered flags were not found when parsing.
            // MatchXOfY means X/Y data for registered flags were found when parsing.

            /// Negative Test Cases \\\

            template <class T>
            UnitTestResult NoMatchOneOfOne( );

            template <class T>
            UnitTestResult NoMatchOneOfMany( );

            template <class T>
            UnitTestResult NoMatchManyOfMany( );

            template <class T>
            UnitTestResult NoMatchAllOfMany( );

            template <class T>
            UnitTestResult MatchOneOfMany( );

            template <class T>
            UnitTestResult MatchManyOfMany( );

            /// Positive Test Cases \\\

            template <class T>
            UnitTestResult MatchOneOfOne( );

            template <class T>
            UnitTestResult MatchAllOfMany( );
        }

        /// Additional Flag Data is unaccepted.
        // Expected behavior: 
        // Additional token following a flag that is not accepting data should match another expected flag.
        // If the additional token does not match any flag, the expectation is to throw an exception.
        namespace UnacceptedData
        {
            // NoMatchXOfY means X/Y unaccepted data for registered flags was found when parsing.
            // MatchXOfY means X/Y unaccepted data for registered flags were not found when parsing.

            /// Negative Test Cases \\\

            template <class T>
            UnitTestResult NoMatchOneOfOne( );

            template <class T>
            UnitTestResult NoMatchOneOfMany( );

            template <class T>
            UnitTestResult NoMatchManyOfMany( );

            template <class T>
            UnitTestResult NoMatchAllOfMany( );

            template <class T>
            UnitTestResult MatchOneOfMany( );

            template <class T>
            UnitTestResult MatchManyOfMany( );

            /// Positive Test Cases \\\

            template <class T>
            UnitTestResult MatchOneOfOne( );

            template <class T>
            UnitTestResult MatchAllOfMany( );
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
            // NoMatchXOfY means X/Y registered flags were not matched when parsing.
            // MatchXOfY means X/Y registered flags were matched when parsing.

            /// Negative Test Cases \\\

            template <class T>
            UnitTestResult NoMatchOneOfOne( );

            template <class T>
            UnitTestResult NoMatchOneOfMany( );

            template <class T>
            UnitTestResult NoMatchManyOfMany( );

            template <class T>
            UnitTestResult NoMatchAllOfMany( );

            template <class T>
            UnitTestResult MatchOneOfMany( );

            template <class T>
            UnitTestResult MatchManyOfMany( );

            /// Positive Test Cases \\\

            template <class T>
            UnitTestResult MatchOneOfOne( );

            template <class T>
            UnitTestResult MatchAllOfMany( );
        }

        /// Additional Flag Data is required.
        // Expected behavior: 
        // Additional token following a flag is treated as data unless it matches another registered flag.
        // If there is no following token, the expectation is to throw an exception.
        namespace RequiredData
        {
            // NoMatchXOfY means X/Y data for registered flags were not found when parsing.
            // MatchXOfY means X/Y data for registered flags were found when parsing.

            /// Negative Test Cases \\\

            template <class T>
            UnitTestResult NoMatchOneOfOne( );

            template <class T>
            UnitTestResult NoMatchOneOfMany( );

            template <class T>
            UnitTestResult NoMatchManyOfMany( );

            template <class T>
            UnitTestResult NoMatchAllOfMany( );

            template <class T>
            UnitTestResult MatchOneOfMany( );

            template <class T>
            UnitTestResult MatchManyOfMany( );

            /// Positive Test Cases \\\

            template <class T>
            UnitTestResult MatchOneOfOne( );

            template <class T>
            UnitTestResult MatchAllOfMany( );
        }

        /// Additional Flag Data is unaccepted.
        // Expected behavior: 
        // Additional token following a flag that is not accepting data should match another expected flag.
        // If the additional token does not match any flag, the expectation is to throw an exception.
        namespace UnacceptedData
        {
            // NoMatchXOfY means X/Y unaccepted data for registered flags was found when parsing.
            // MatchXOfY means X/Y unaccepted data for registered flags were not found when parsing.

            /// Negative Test Cases \\\

            template <class T>
            UnitTestResult NoMatchOneOfOne( );

            template <class T>
            UnitTestResult NoMatchOneOfMany( );

            template <class T>
            UnitTestResult NoMatchManyOfMany( );

            template <class T>
            UnitTestResult NoMatchAllOfMany( );

            template <class T>
            UnitTestResult MatchOneOfMany( );

            template <class T>
            UnitTestResult MatchManyOfMany( );

            /// Positive Test Cases \\\

            template <class T>
            UnitTestResult MatchOneOfOne( );

            template <class T>
            UnitTestResult MatchAllOfMany( );
        }
    }
}