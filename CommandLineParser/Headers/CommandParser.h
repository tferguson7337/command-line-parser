#pragma once

// CLP
#include "CommandFlag.h"

// CC
#include <CCAPIAnnotations.h>
#include <CCSharedPointer.h>

// C++/STL
#include <memory>
#include <string>
#include <vector>


namespace CLP
{
    //
    //
    //  Class   - CommandParser [SINGLETON]
    //  
    //  Purpose - Register expected flags, supplemental flag data, and respective callback functions.
    //            Parse provided command-line data against the registered CommandFlags.
    //
    //
    class CommandParser
    {
        CommandParser(const CommandParser&) = delete;
        CommandParser(CommandParser&&) = delete;
        CommandParser& operator=(const CommandParser&) = delete;
        CommandParser& operator=(CommandParser&&) = delete;

        using FlagItr = std::vector<CommandFlagPtr>::iterator;

    private:

        // Private Ctor and Dtor - Singleton Class
        CommandParser();
        ~CommandParser();

        // Private Helper Methods //

        // Copy raw string array to string-object vector - return the vector.
        static std::vector<std::string> RawStringArrayToStringList(_In_count_(n) const char* const a[ ], _In_ const int n);

        // Iterate through provided arguments, set results in CommandFlags vector.
        void MatchArgsAgainstCommandFlags(_In_ const std::vector<std::string>&);

        // Scan registered CommandFlags for string argument match.
        FlagItr ScanForFlag(_In_ const std::string&);

        // Handle a flag match, potential secondary scan for expected supplemental flag data.
        const std::string* HandleFlagMatch(_In_ const FlagItr&, _In_ const std::string*, _In_opt_ const std::string*);

        // Handle retrieving potentially optional flag data for flag match.
        const std::string* ObtainFlagData(_In_ const FlagItr&, _In_ const std::string*, _In_opt_ const std::string*);

        // Ensure all registered command-line flags are present.
        void ValidateMatches();

        // Invoke all registered callback functions in sequential order.
        void InvokeCallbackFunctions() noexcept;

        // Private implementation of parsing logic.
        void ParseCommandLineInternal(_In_ const std::vector<std::string>&);

        // Private Data Members //

        // List of registered CommandFlags
        std::vector<CommandFlagPtr> m_CommandFlags;

    public:

        // Static Public Method //

        // Get reference to singleton instance
        static CommandParser& GetInstance();

        // Getter //

        // Note: Copy intentional.
        const std::vector<CommandFlagPtr> GetRegisteredCommandFlags() const noexcept;

        // Public Methods //

        // Disassociates registered command flags from parser.
        void Clear() noexcept;

        // Register new CommandFlag object with the parser.
        template <typename... Args>
        void RegisterCommandFlag(Args&&... args)
        {
            m_CommandFlags.emplace_back(std::forward<Args>(args)...);
        }

        // Parse provided command line arguments.
        // Matches result in respective CommandFlag's callback function to be called.
        void ParseCommandLine(_In_ const int argc, _In_count_(argc) const char* const argv[ ]);
        void ParseCommandLine(_In_ const std::vector<std::string>& args);
    };
}
