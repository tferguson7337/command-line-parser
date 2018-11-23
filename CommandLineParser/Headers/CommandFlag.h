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

        explicit CommandFlag(const std::basic_string<T>& flag = std::basic_string<T>( ));
        CommandFlag(const std::basic_string<T>& flag, const CallbackFunction<T>& func, const bool flagOpt, const bool dataAccepted, const bool dataOpt) noexcept;
        CommandFlag(const CommandFlag& src);
        CommandFlag(CommandFlag&& src) noexcept;

        /// Destructor \\\

        ~CommandFlag( );

        /// Assignment Overload \\\

        CommandFlag& operator=(const CommandFlag& src);
        CommandFlag& operator=(CommandFlag&& src) noexcept;

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

        void SetFlagData(const std::basic_string<T>& data);
        void SetFlagData(std::basic_string<T>&& data) noexcept;
        void SetCallbackFunction(const CallbackFunction<T>& func);
        void SetCallbackFunctionTriggered(const bool triggered) noexcept;
        void SetFlagOptional(const bool flagOpt) noexcept;
        void SetFlagDataAccepted(const bool dataExpected) noexcept;
        void SetFlagDataOptional(const bool dataOpt) noexcept;
        void SetFlagPresent(const bool flagPresent) noexcept;
        void SetFlagDataPresent(const bool dataPresent) noexcept;
    };
}