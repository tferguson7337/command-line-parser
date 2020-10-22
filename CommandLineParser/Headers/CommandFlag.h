#pragma once

// CC
#include <CCAPIAnnotations.h>
#include <CCSharedPointer.h>

// C++/STL
#include <functional>
#include <string>


namespace CLP
{
    class CommandFlag
    {
    public:

        using CallbackFunction = std::function<void(const CommandFlag&)>;

    private:

        // Private Data Members //

        std::string m_Flag;
        std::string m_FlagData;

        CallbackFunction m_CallbackFunc;
        bool m_bCallbackTriggered;

        bool m_bFlagOptional;
        bool m_bFlagDataAccepted;
        bool m_bFlagDataOptional;

        bool m_bFlagPresent;
        bool m_bFlagDataPresent;

    public:

        // Constructors //

        explicit CommandFlag(_In_ const std::string& flag = std::string());
        CommandFlag(
            _In_ const std::string& flag,
            _In_ const CallbackFunction& func,
            _In_ const bool flagOpt,
            _In_ const bool dataAccepted,
            _In_ const bool dataOpt
        );
        CommandFlag(_In_ const CommandFlag& src);
        CommandFlag(_Inout_ CommandFlag&& src) noexcept;

        // Destructor //

        ~CommandFlag();

        // Assignment Overload //

        CommandFlag& operator=(_In_ const CommandFlag& src);
        CommandFlag& operator=(_Inout_ CommandFlag&& src) noexcept;

        // Getters //

        const std::string& GetFlag() const noexcept;
        const std::string& GetFlagData() const noexcept;
        const CallbackFunction& GetCallbackFunction() const noexcept;
        bool IsCallbackFunctionTriggered() const noexcept;
        bool IsFlagOptional() const noexcept;
        bool IsFlagDataAccepted() const noexcept;
        bool IsFlagDataOptional() const noexcept;
        bool IsFlagPresent() const noexcept;
        bool IsFlagDataPresent() const noexcept;

        // Setters //

        void SetFlagData(_In_ const std::string& data);
        void SetFlagData(_In_ std::string&& data) noexcept;
        void SetCallbackFunction(_In_ const CallbackFunction& func);
        void SetCallbackFunctionTriggered(_In_ const bool triggered) noexcept;
        void SetFlagOptional(_In_ const bool flagOpt) noexcept;
        void SetFlagDataAccepted(_In_ const bool dataExpected) noexcept;
        void SetFlagDataOptional(_In_ const bool dataOpt) noexcept;
        void SetFlagPresent(_In_ const bool flagPresent) noexcept;
        void SetFlagDataPresent(_In_ const bool dataPresent) noexcept;
    };

    using CommandFlagPtr = CC::SharedPointer<CommandFlag>;
}
