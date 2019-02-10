#pragma once

#include <functional>
#include <string>
#include <utility>

namespace CLP
{
    template <class T>
    class CommandFlag
    {
    public:

        template <class T>
        using CallbackFunction = std::function<void(const CommandFlag<T>&)>;

    private:

        /// Private Data Members \\\

        std::basic_string<T> m_Flag;
        std::basic_string<T> m_FlagData;

        CallbackFunction<T> m_CallbackFunc;
        bool m_bCallbackTriggered;

        bool m_bFlagOptional;
        bool m_bFlagDataAccepted;
        bool m_bFlagDataOptional;

        bool m_bFlagPresent;
        bool m_bFlagDataPresent;

    public:

        /// Constructors \\\

        explicit CommandFlag(_In_ const std::basic_string<T>& flag = std::basic_string<T>( ));
        CommandFlag(
            _In_ const std::basic_string<T>& flag, 
            _In_ const CallbackFunction<T>& func, 
            _In_ const bool& flagOpt, 
            _In_ const bool& dataAccepted, 
            _In_ const bool& dataOpt
        );
        CommandFlag(_In_ const CommandFlag& src);
        CommandFlag(_In_ CommandFlag&& src) noexcept;

        /// Destructor \\\

        ~CommandFlag( );

        /// Assignment Overload \\\

        CommandFlag& operator=(_In_ const CommandFlag& src);
        CommandFlag& operator=(_In_ CommandFlag&& src) noexcept;

        /// Getters \\\

        const std::basic_string<T>& GetFlag( ) const noexcept;
        const std::basic_string<T>& GetFlagData( ) const noexcept;
        const CallbackFunction<T>& GetCallbackFunction( ) const noexcept;
        const bool& IsCallbackFunctionTriggered( ) const noexcept;
        const bool& IsFlagOptional( ) const noexcept;
        const bool& IsFlagDataAccepted( ) const noexcept;
        const bool& IsFlagDataOptional( ) const noexcept;
        const bool& IsFlagPresent( ) const noexcept;
        const bool& IsFlagDataPresent( ) const noexcept;

        /// Setters \\\

        void SetFlagData(_In_ const std::basic_string<T>& data);
        void SetFlagData(_In_ std::basic_string<T>&& data) noexcept;
        void SetCallbackFunction(_In_ const CallbackFunction<T>& func);
        void SetCallbackFunctionTriggered(_In_ const bool& triggered) noexcept;
        void SetFlagOptional(_In_ const bool& flagOpt) noexcept;
        void SetFlagDataAccepted(_In_ const bool& dataExpected) noexcept;
        void SetFlagDataOptional(_In_ const bool& dataOpt) noexcept;
        void SetFlagPresent(_In_ const bool& flagPresent) noexcept;
        void SetFlagDataPresent(_In_ const bool& dataPresent) noexcept;
    };
}