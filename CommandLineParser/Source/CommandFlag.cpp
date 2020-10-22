// CLP
#include <CommandFlag.h>


namespace CLP
{
    // Constructors //

    // String Constructor
    CommandFlag::CommandFlag(_In_ const std::string& flag) :
        CommandFlag(flag, nullptr, true, false, false)
    { }

    // Full Constructor
    CommandFlag::CommandFlag(
        _In_ const std::string& flag,
        _In_ const CallbackFunction& func,
        _In_ const bool flagOpt,
        _In_ const bool dataAccepted,
        _In_ const bool dataOpt
    ) :
        m_Flag(flag),
        m_CallbackFunc(func),
        m_bCallbackTriggered(false),
        m_bFlagOptional(flagOpt),
        m_bFlagDataAccepted(dataAccepted),
        m_bFlagDataOptional(dataOpt),
        m_bFlagPresent(false),
        m_bFlagDataPresent(false)
    { }

    // Copy Constructor
    CommandFlag::CommandFlag(_In_ const CommandFlag& src) :
        CommandFlag()
    {
        *this = src;
    }

    // Move Constructor
    CommandFlag::CommandFlag(_Inout_ CommandFlag&& src) noexcept :
        CommandFlag()
    {
        *this = std::move(src);
    }

    // Destructor //

    // Default Destructor
    CommandFlag::~CommandFlag() = default;

    // Assignment Overload //

    CommandFlag& CommandFlag::operator=(_In_ const CommandFlag& src)
    {
        if (this != &src)
        {
            m_Flag = src.m_Flag;
            m_CallbackFunc = src.m_CallbackFunc;
            m_bFlagOptional = src.m_bFlagOptional;
            m_bFlagDataAccepted = src.m_bFlagDataAccepted;
            m_bFlagDataOptional = src.m_bFlagDataOptional;
            m_bFlagPresent = src.m_bFlagPresent;
            m_bFlagDataPresent = src.m_bFlagDataPresent;
        }

        return *this;
    }

    CommandFlag& CommandFlag::operator=(_Inout_ CommandFlag&& src) noexcept
    {
        if (this != &src)
        {
            m_Flag = std::move(src.m_Flag);
            m_CallbackFunc = std::move(src.m_CallbackFunc);
            m_bFlagOptional = src.m_bFlagOptional;
            m_bFlagDataAccepted = src.m_bFlagDataAccepted;
            m_bFlagDataOptional = src.m_bFlagDataOptional;
            m_bFlagPresent = src.m_bFlagPresent;
            m_bFlagDataPresent = src.m_bFlagDataPresent;

            src.m_Flag.clear();
            src.m_CallbackFunc = CallbackFunction();
            src.m_bFlagOptional = true;
            src.m_bFlagDataAccepted = false;
            src.m_bFlagDataOptional = false;
            src.m_bFlagPresent = false;
            src.m_bFlagDataPresent = false;
        }

        return *this;
    }

    // Getters //

    const std::string& CommandFlag::GetFlag() const noexcept
    {
        return m_Flag;
    }

    const std::string& CommandFlag::GetFlagData() const noexcept
    {
        return m_FlagData;
    }

    const typename CommandFlag::CallbackFunction& CommandFlag::GetCallbackFunction() const noexcept
    {
        return m_CallbackFunc;
    }

    bool CommandFlag::IsCallbackFunctionTriggered() const noexcept
    {
        return m_bCallbackTriggered;
    }

    bool CommandFlag::IsFlagOptional() const noexcept
    {
        return m_bFlagOptional;
    }

    bool CommandFlag::IsFlagDataAccepted() const noexcept
    {
        return m_bFlagDataAccepted;
    }

    bool CommandFlag::IsFlagDataOptional() const noexcept
    {
        return m_bFlagDataOptional;
    }

    bool CommandFlag::IsFlagPresent() const noexcept
    {
        return m_bFlagPresent;
    }

    bool CommandFlag::IsFlagDataPresent() const noexcept
    {
        return m_bFlagDataPresent;
    }

    // Setters //

    void CommandFlag::SetFlagData(_In_ const std::string& data)
    {
        m_FlagData = data;
    }

    void CommandFlag::SetFlagData(_In_ std::string&& data) noexcept
    {
        m_FlagData = std::move(data);
    }

    void CommandFlag::SetCallbackFunction(_In_ const CallbackFunction& func)
    {
        m_CallbackFunc = func;
    }

    void CommandFlag::SetCallbackFunctionTriggered(_In_ const bool triggered) noexcept
    {
        m_bCallbackTriggered = triggered;
    }

    void CommandFlag::SetFlagOptional(_In_ const bool flagOpt) noexcept
    {
        m_bFlagOptional = flagOpt;
    }

    void CommandFlag::SetFlagDataAccepted(_In_ const bool dataExpected) noexcept
    {
        m_bFlagDataAccepted = dataExpected;
    }

    void CommandFlag::SetFlagDataOptional(_In_ const bool dataOpt) noexcept
    {
        m_bFlagDataOptional = dataOpt;
    }

    void CommandFlag::SetFlagPresent(_In_ const bool flagPresent) noexcept
    {
        m_bFlagPresent = flagPresent;
    }

    void CommandFlag::SetFlagDataPresent(_In_ const bool dataPresent) noexcept
    {
        m_bFlagDataPresent = dataPresent;
    }

}
