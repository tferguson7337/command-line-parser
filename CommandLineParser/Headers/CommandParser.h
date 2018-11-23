#pragma once

#include <CommandFlag.h>

#include <Macros.h>

#include <vector>

namespace CLP
{
    ///
    //
    //  Class   - CommandParser [SINGLETON]
    //  
    //  Purpose - Register expected flags, supplemental flag data, and respective callback functions.
    //            Parse provided command-line data against the registered CommandFlags.
    //
    ///
    template <class T>
    class CommandParser
    {
        CommandParser(const CommandParser&) = delete;
        CommandParser(CommandParser&&) = delete;
        CommandParser& operator=(const CommandParser&) = delete;
        CommandParser& operator=(CommandParser&&) = delete;

        using FlagItr = typename std::vector<CommandFlag<T>>::iterator;

    private:

        // Private Ctor and Dtor - Singleton Class
        CommandParser( );
        ~CommandParser( );

        /// Private Helper Methods \\\

        // Copy raw string array to string-object vector - return the vector.
        static std::vector<std::basic_string<T>> RawStringArrayToStringList(const T* const[ ], const int);

        // Iterate through provided arguments, set results in CommandFlags vector.
        void MatchArgsAgainstCommandFlags(const std::vector<std::basic_string<T>>&);

        // Scan registered CommandFlags for string argument match.
        FlagItr ScanForFlag(const std::basic_string<T>&);

        // Handle a flag match, potential secondary scan for expected supplemental flag data.
        const std::basic_string<T>* HandleFlagMatch(const FlagItr&, const std::basic_string<T>*, const std::basic_string<T>*);

        // Handle retrieving potentially optional flag data for flag match.
        const std::basic_string<T>* ObtainFlagData(const FlagItr&, const std::basic_string<T>*, const std::basic_string<T>*);

        // Ensure all registered command-line flags are present.
        void ValidateMatches( );

        // Invoke all registered callback functions in sequential order.
        void InvokeCallbackFunctions( ) noexcept;

        // Private implementation of parsing logic.
        void ParseCommandLineInternal(const std::vector<std::basic_string<T>>&);

        /// Private Data Members \\\

        // List of registered CommandFlags
        std::vector<CommandFlag<T>> m_CommandFlags;

    public:

        /// Static Public Method \\\

        // Get reference to singleton instance
        static CommandParser& GetInstance( );

        /// Public Methods \\\

        // Disassociates registered command flags from parser.
        void Clear( ) noexcept;

        // Register new CommandFlag object with the parser.
        void RegisterCommandFlag(const CommandFlag<T>& flag);
        void RegisterCommandFlag(CommandFlag<T>&& flag) noexcept;

        // Parse provided command line arguments.
        // Matches result in respective CommandFlag's callback function to be called.
        void ParseCommandLine(const int argc, const T* const argv[ ]);
        void ParseCommandLine(const std::vector<std::basic_string<T>>& args);
    };
}