// CLP
#include <CommandParser.h>

// CC
#include <CCStringUtil.h>

// C++/STL
#include <stdexcept>


namespace CLP
{
    // Private Constructor/Destructor //

    // Default Ctor [Private]
    CommandParser::CommandParser() = default;

    // Default Dtor [Private]
    CommandParser::~CommandParser() = default;

    // Private Helper Methods //

    // Copy raw string array to string-object vector - return the vector.
    std::vector<std::string> CommandParser::RawStringArrayToStringList(_In_count_(n) const char* const a[], _In_ const int n)
    {
        std::vector<std::string> args;

        // Copy C-strings to string vector.
        for (int i = 0; i < n; i++)
        {
            const char* const str = a[i];
            if (!str || (str[0] == '\0'))
            {
                // Skip invalid input.
                continue;
            }

            args.push_back(str);
        }

        return args;
    }

    // Iterate through provided arguments, set results in CommandFlags vector.
    void CommandParser::MatchArgsAgainstCommandFlags(_In_ const std::vector<std::string>& args)
    {
        for (size_t i = 0; i < args.size(); i++)
        {
            const std::string* pCurrentArg = &args[i];
            const std::string* pNextArg = ((i + 1) == args.size()) ? nullptr : &args[i + 1];

            FlagItr matchItr = ScanForFlag(*pCurrentArg);
            if (matchItr != m_CommandFlags.cend())
            {
                if (HandleFlagMatch(matchItr, pCurrentArg, pNextArg) == pNextArg)
                {
                    // pNextArg is data that was assigned to matched flag, so skip it for next loop iteration.
                    i++;
                }
            }
        }
    }

    // Scan registered CommandFlags for string argument match.
    typename CommandParser::FlagItr CommandParser::ScanForFlag(_In_ const std::string& str)
    {
        for (FlagItr itr = m_CommandFlags.begin(), end = m_CommandFlags.end(); itr != end; itr++)
        {
            const auto& ptr = *itr;
            // TODO: Add way for user to toggle case-insensitive comparisons on a per-flag basis.
            if (CC::StringUtil::Compare(ptr->GetFlag(), str, false))
            {
                return itr;
            }
        }

        return m_CommandFlags.end();
    }

    // Handle a flag match, potential secondary scan for expected supplemental flag data.
    const std::string* CommandParser::HandleFlagMatch(_In_ const FlagItr& matchItr, _In_ const std::string* pCurr, _In_opt_ const std::string* pNext)
    {
        const std::string* ret = pCurr;
        auto& ptr = *matchItr;

        // Set that we found the flag.
        ptr->SetFlagPresent(true);

        // See if we're expecting additional flag data (possibly optional).
        if (ptr->IsFlagDataAccepted())
        {
            ret = ObtainFlagData(matchItr, pCurr, pNext);
        }

        return ret;
    }

    // Handle retrieving potentially optional flag data for flag match.
    const std::string* CommandParser::ObtainFlagData(_In_ const FlagItr& matchItr, _In_ const std::string* pCurr, _In_opt_ const std::string* pNext)
    {
        const FlagItr matchEnd = m_CommandFlags.end();
        FlagItr nextMatchItr = matchEnd;
        auto& ptr = *matchItr;

        // If we're on the last flag, then there's no more data to look for.
        if (!pNext)
        {
            return pCurr;
        }

        // See if the next string matches a registered flag.
        nextMatchItr = ScanForFlag(*pNext);

        // Handle case where we have no match (next string is data).
        if (nextMatchItr == matchEnd)
        {
            ptr->SetFlagDataPresent(true);
            ptr->SetFlagData(*pNext);
        }

        return ptr->IsFlagDataPresent() ? pNext : pCurr;
    }

    // Ensure all registered command-line flags are present.
    void CommandParser::ValidateMatches()
    {
        for (const auto& cmdFlag : m_CommandFlags)
        {
            if (!cmdFlag->IsFlagOptional() && !cmdFlag->IsFlagPresent())
            {
                throw std::invalid_argument("required flag[" + cmdFlag->GetFlag() + "] not found.");
            }

            if (cmdFlag->IsFlagDataAccepted() && !cmdFlag->IsFlagDataOptional() && !cmdFlag->IsFlagDataPresent())
            {
                throw std::invalid_argument("required flag data for flag[" + cmdFlag->GetFlag() + "] not found.");
            }
        }
    }

    // Invoke all registered callback functions in sequential order.
    void CommandParser::InvokeCallbackFunctions() noexcept
    {
        for (auto& cmdFlag : m_CommandFlags)
        {
            const auto& func = cmdFlag->GetCallbackFunction();
            if (cmdFlag->IsFlagPresent() && func)
            {
                func(*cmdFlag);
                cmdFlag->SetCallbackFunctionTriggered(true);
            }
        }
    }

    // Private implementation of parsing logic.
    void CommandParser::ParseCommandLineInternal(_In_ const std::vector<std::string>& args)
    {
        // Scan for flag matches, assign any data to flag, mark flag as matched.
        MatchArgsAgainstCommandFlags(args);

        // Ensure all required flags are matched and required data is assigned - throw if condition is not met.
        ValidateMatches();

        // Invoke callback functions of all matched flags, in order of registration.
        InvokeCallbackFunctions();
    }

    // Static Public Method //

    // Return reference to singleton instance.
    CommandParser& CommandParser::GetInstance()
    {
        static CommandParser instance;
        return instance;
    }

    // Getter //

    // Note: Copy intentional.
    const std::vector<CommandFlagPtr> CommandParser::GetRegisteredCommandFlags() const noexcept
    {
        return m_CommandFlags;
    }

    // Public Methods //

    // Clear any registered command flags.
    void CommandParser::Clear() noexcept
    {
        m_CommandFlags.clear();
    }

    // Parse provided command line arguments.
    // Matches result in respective CommandFlag's callback function to be called.
    void CommandParser::ParseCommandLine(_In_ const int argc, _In_count_(argc) const char* const argv[])
    {
        if (!m_CommandFlags.empty() && argc > 0)
        {
            ParseCommandLineInternal(RawStringArrayToStringList(argv, argc));
        }
    }

    // Parse provided command line arguments.
    // Matches result in respective CommandFlag's callback function to be called.
    void CommandParser::ParseCommandLine(_In_ const std::vector<std::string>& args)
    {
        if (!m_CommandFlags.empty() && !args.empty())
        {
            ParseCommandLineInternal(args);
        }
    }
}
