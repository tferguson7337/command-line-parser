#include "../Headers/CommandParser.h"

#include "../Common/Headers/StringUtil.hpp"
#include "../Common/Headers/Types.h"

#include <stdexcept>

namespace CLP
{
    /// Private Constructor/Destructor \\\

    // Default Ctor [Private]
    template <class T>
    CommandParser<T>::CommandParser( ) = default;

    // Default Dtor [Private]
    template <class T>
    CommandParser<T>::~CommandParser( ) = default;

    /// Private Helper Methods \\\

    // Copy raw string array to string-object vector - return the vector.
    template <class T>
    std::vector<std::basic_string<T>> CommandParser<T>::RawStringArrayToStringList(const T* const a[ ], const int n)
    {
        std::vector<std::basic_string<T>> args;

        // Copy C-strings to string vector.
        for ( int i = 0; i < n; i++ )
        {
            const T* const str = a[i];
            if ( !str )
            {
                throw std::invalid_argument(__FUNCTION__": unexpected null argument string.");
            }
            else if ( str[0] == T('\0') )
            {
                throw std::invalid_argument(__FUNCTION__": unexpected empty argument string.");
            }

            args.push_back(str);
        }

        return args;
    }

    // Iterate through provided arguments, set results in CommandFlags vector.
    template <class T>
    void CommandParser<T>::MatchArgsAgainstCommandFlags(const std::vector<std::basic_string<T>>& args)
    {
        for ( size_t i = 0; i < args.size( ); i++ )
        {
            const std::basic_string<T>* pCurrentArg = &args[i];
            const std::basic_string<T>* pNextArg = (i + 1 == args.size( )) ? nullptr : &args[i + 1];

            FlagItr matchItr = ScanForFlag(*pCurrentArg);
            if ( matchItr != m_CommandFlags.cend( ) )
            {
                if ( HandleFlagMatch(matchItr, pCurrentArg, pNextArg) == pNextArg )
                {
                    // pNextArg is data that was assigned to matched flag, so skip it for next loop iteration.
                    i++;
                }
            }
        }
    }

    // Scan registered CommandFlags for string argument match.
    template <class T>
    typename CommandParser<T>::FlagItr CommandParser<T>::ScanForFlag(const std::basic_string<T>& str)
    {
        for ( FlagItr itr = m_CommandFlags.begin( ), end = m_CommandFlags.end( ); itr != end; itr++ )
        {
            if ( itr->GetFlag( ) == str )
            {
                return itr;
            }
        }

        return m_CommandFlags.end( );
    }

    // Handle a flag match, potential secondary scan for expected supplemental flag data.
    template <class T>
    const std::basic_string<T>* CommandParser<T>::HandleFlagMatch(const FlagItr& matchItr, const std::basic_string<T>* pCurr, const std::basic_string<T>* pNext)
    {
        const std::basic_string<T>* ret = pCurr;
       
        // Set that we found the flag.
        matchItr->SetFlagPresent(true);

        // See if we're expecting additional flag data (possibly optional).
        if ( matchItr->IsFlagDataAccepted( ) )
        {
            ret = ObtainFlagData(matchItr, pCurr, pNext);
        }

        return ret;
    }

    // Handle retrieving potentially optional flag data for flag match.
    template <class T>
    const std::basic_string<T>* CommandParser<T>::ObtainFlagData(const FlagItr& matchItr, const std::basic_string<T>* pCurr, const std::basic_string<T>* pNext)
    {
        const FlagItr matchEnd = m_CommandFlags.end( );
        FlagItr nextMatchItr = matchEnd;

        // If we're on the last string and we require data, throw failure.
        if ( !pNext )
        {
            if ( !matchItr->IsFlagDataOptional( ) )
            {
                const std::string msg(
                    __FUNCTION__": flag[\"" +
                    StringUtil::UTFConversion::ToString<utf8>(*pCurr) +
                    "\"]" +
                    " requires additional data, but none was found."
                );

                throw std::invalid_argument(msg);
            }
            
            return pCurr;
        }

        // See if the next string matches a registered flag.
        nextMatchItr = ScanForFlag(*pNext);

        // Handle case where next string matched a registered flag.
        if ( nextMatchItr != matchEnd )
        {
            if ( !matchItr->IsFlagDataOptional( ) )
            {
                const std::string msg(
                    __FUNCTION__": flag[\"" +
                    StringUtil::UTFConversion::ToString<utf8>(*pCurr) +
                    "\"]" +
                    " requires additional data, but none was found."
                );

                throw std::invalid_argument(msg);
            }
        }
        // Handle case where we have no match (next string is data).
        else
        {
            matchItr->SetFlagDataPresent(true);
            matchItr->SetFlagData(*pNext);
        }

        return matchItr->IsFlagDataPresent( ) ? pNext : pCurr;
    }

    // Ensure all registered command-line flags are present.
    template <class T>
    void CommandParser<T>::ValidateMatches( )
    {
        for ( const auto& cmdFlag : m_CommandFlags )
        {
            if ( !cmdFlag.IsFlagOptional( ) && !cmdFlag.IsFlagPresent( ) )
            {
                throw std::invalid_argument(
                    __FUNCTION__": required flag[" +
                    StringUtil::UTFConversion::ToString<utf8>(cmdFlag.GetFlag( )) + 
                    "] not found."
                );
            }
            
            if ( cmdFlag.IsFlagDataAccepted( ) && !cmdFlag.IsFlagDataOptional( ) && !cmdFlag.IsFlagDataPresent( ) )
            {
                throw std::invalid_argument(
                    __FUNCTION__": required flag data for flag[" +
                    StringUtil::UTFConversion::ToString<utf8>(cmdFlag.GetFlag( )) + 
                    "] not found."
                );
            }
        }
    }

    // Invoke all registered callback functions in sequential order.
    template <class T>
    void CommandParser<T>::InvokeCallbackFunctions( ) noexcept
    {
        for ( auto& cmdFlag : m_CommandFlags )
        {
            if ( cmdFlag.IsFlagPresent( ) )
            {
                cmdFlag.GetCallbackFunction( )(cmdFlag);
                cmdFlag.SetCallbackFunctionTriggered(true);
            }
        }
    }

    // Private implementation of parsing logic.
    template <class T>
    void CommandParser<T>::ParseCommandLineInternal(const std::vector<std::basic_string<T>>& args)
    {
        MatchArgsAgainstCommandFlags(args);
        ValidateMatches( );
        InvokeCallbackFunctions( );
    }

    /// Static Public Method \\\

    // Return reference to singleton instance.
    template <class T>
    CommandParser<T>& CommandParser<T>::GetInstance( )
    {
        if constexpr ( !std::is_same_v<T, utf8> && !std::is_same_v<T, utf16> )
        {
            static const std::string msg(
                std::to_string(__FUNCTION__": unsupported parser type[") +
                typeid(T).name( ) + "]"
            );

            throw std::invalid_argument(msg);
        }

        static CommandParser instance;
        return instance;
    }

    /// Getter \\\

    template <class T>
    const std::vector<CommandFlag<T>>& CommandParser<T>::GetRegisteredCommandFlags( ) const noexcept
    {
        return m_CommandFlags;
    }

    /// Public Methods \\\

    // Clear any registered command flags.
    template <class T>
    void CommandParser<T>::Clear( ) noexcept
    {
        m_CommandFlags.clear( );
    }

    // Register a new command flag [Copy]
    template <class T>
    void CommandParser<T>::RegisterCommandFlag(const CommandFlag<T>& flag)
    {
        m_CommandFlags.push_back(flag);
    }

    // Register a new command flag [Move]
    template <class T>
    void CommandParser<T>::RegisterCommandFlag(CommandFlag<T>&& flag) noexcept
    {
        m_CommandFlags.push_back(std::move(flag));
    }

    // Parse provided command line arguments.
    // Matches result in respective CommandFlag's callback function to be called.
    template <class T>
    void CommandParser<T>::ParseCommandLine(const int argc, const T* const argv[ ])
    {
        if ( m_CommandFlags.empty( ) )
        {
            throw std::logic_error(__FUNCTION__": No registered command flags.");
        }

        if ( argc <= 0 )
        {
            throw std::invalid_argument(
                __FUNCTION__": Invalid argument count[" +
                std::to_string(argc) +
                "]."
            );
        }

        ParseCommandLineInternal(RawStringArrayToStringList(argv, argc));
    }

    // Parse provided command line arguments.
    // Matches result in respective CommandFlag's callback function to be called.
    template <class T>
    void CommandParser<T>::ParseCommandLine(const std::vector<std::basic_string<T>>& args)
    {
        if ( m_CommandFlags.empty( ) )
        {
            throw std::logic_error(__FUNCTION__": No registered command flags.");
        }

        if ( args.empty( ) )
        {
            throw std::invalid_argument(__FUNCTION__": attempted to parse empty vector of arguments.");
        }

        ParseCommandLineInternal(args);
    }

    /// Explicit Template Instantiations \\\

    template CommandParser<utf8>& CommandParser<utf8>::GetInstance( );
    template CommandParser<utf16>& CommandParser<utf16>::GetInstance( );

    template const std::vector<CLP::CommandFlag<utf8>>& CommandParser<utf8>::GetRegisteredCommandFlags( ) const noexcept;
    template const std::vector<CLP::CommandFlag<utf16>>& CommandParser<utf16>::GetRegisteredCommandFlags( ) const noexcept;

    template void CommandParser<utf8>::Clear( ) noexcept;
    template void CommandParser<utf16>::Clear( ) noexcept;

    template void CommandParser<utf8>::RegisterCommandFlag(const CommandFlag<utf8>& flag);
    template void CommandParser<utf16>::RegisterCommandFlag(const CommandFlag<utf16>& flag);
    template void CommandParser<utf8>::RegisterCommandFlag(CommandFlag<utf8>&& flag) noexcept;
    template void CommandParser<utf16>::RegisterCommandFlag(CommandFlag<utf16>&& flag) noexcept;

    template void CommandParser<utf8>::ParseCommandLine(const int argc, const utf8* const argv[ ]);
    template void CommandParser<utf16>::ParseCommandLine(const int argc, const utf16* const argv[ ]);
    template void CommandParser<utf8>::ParseCommandLine(const std::vector<std::basic_string<utf8>>&);
    template void CommandParser<utf16>::ParseCommandLine(const std::vector<std::basic_string<utf16>>&);
}