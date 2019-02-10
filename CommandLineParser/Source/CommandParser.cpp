#include "../Headers/CommandParser.h"

#include "../../Common/Headers/StringUtil.h"
#include "../../Common/Headers/Types.h"

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
    std::vector<std::basic_string<T>> CommandParser<T>::RawStringArrayToStringList(_In_count_(n) const T* const a[ ], _In_ const int& n)
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
    void CommandParser<T>::MatchArgsAgainstCommandFlags(_In_ const std::vector<std::basic_string<T>>& args)
    {
        for ( size_t i = 0; i < args.size( ); i++ )
        {
            const std::basic_string<T>* pCurrentArg = &args[i];
            const std::basic_string<T>* pNextArg = ((i + 1) == args.size( )) ? nullptr : &args[i + 1];

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
    typename CommandParser<T>::FlagItr CommandParser<T>::ScanForFlag(_In_ const std::basic_string<T>& str)
    {
        for ( FlagItr itr = m_CommandFlags.begin( ), end = m_CommandFlags.end( ); itr != end; itr++)
        {
            if ( StringUtil::Compare<T>(itr->GetFlag( ), str, false) )
            {
                return itr;
            }
        }

        return m_CommandFlags.end( );
    }

    // Handle a flag match, potential secondary scan for expected supplemental flag data.
    template <class T>
    const std::basic_string<T>* CommandParser<T>::HandleFlagMatch(_In_ const FlagItr& matchItr, _In_ const std::basic_string<T>* pCurr, _In_opt_ const std::basic_string<T>* pNext)
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
    const std::basic_string<T>* CommandParser<T>::ObtainFlagData(_In_ const FlagItr& matchItr, _In_ const std::basic_string<T>* pCurr, _In_opt_ const std::basic_string<T>* pNext)
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
        for ( CommandFlag<T>& cmdFlag : m_CommandFlags )
        {
            const auto& func = cmdFlag.GetCallbackFunction( );
            if ( cmdFlag.IsFlagPresent( ) && func )
            {
                func(cmdFlag);
                cmdFlag.SetCallbackFunctionTriggered(true);
            }
        }
    }

    // Private implementation of parsing logic.
    template <class T>
    void CommandParser<T>::ParseCommandLineInternal(_In_ const std::vector<std::basic_string<T>>& args)
    {
        // Scan for flag matches, assign any data to flag, mark flag as matched.
        MatchArgsAgainstCommandFlags(args);

        // Ensure all required flags are matched and required data is assigned - throw if condition is not met.
        ValidateMatches( );

        // Invoke callback functions of all matched flags, in order of registration.
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

/// Code Analysis is complaining about inconsistent SAL annotations
/// for the following methods.  It's wrong; disable the warnings here.
#pragma warning(push)
#pragma warning(disable:28251)

    // Register a new command flag [Copy]
    template <class T>
    void CommandParser<T>::RegisterCommandFlag(_In_ const CommandFlag<T>& flag)
    {
        m_CommandFlags.push_back(flag);
    }

    // Register a new command flag [Move]
    template <class T>
    void CommandParser<T>::RegisterCommandFlag(_In_ CommandFlag<T>&& flag) noexcept
    {
        m_CommandFlags.push_back(std::move(flag));
    }

    // Parse provided command line arguments.
    // Matches result in respective CommandFlag's callback function to be called.
    template <class T>
    void CommandParser<T>::ParseCommandLine(_In_ const int& argc, _In_count_(argc) const T* const argv[ ])
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
    void CommandParser<T>::ParseCommandLine(_In_ const std::vector<std::basic_string<T>>& args)
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

#pragma warning(pop)

    /// Explicit Template Instantiations \\\

    template class CommandParser<utf8>;
    template class CommandParser<utf16>;
}