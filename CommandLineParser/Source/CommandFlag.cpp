#include <CommandFlag.h>

namespace CLP
{
    // Constructors //

    // String Constructor
    template <class T>
    CommandFlag<T>::CommandFlag(_In_ const std::basic_string<T>& flag) :
        CommandFlag(flag, nullptr, true, false, false)
    { }

    // Full Constructor
    template <class T>
    CommandFlag<T>::CommandFlag(
        _In_ const std::basic_string<T>& flag, 
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
    template <class T>
    CommandFlag<T>::CommandFlag(_In_ const CommandFlag<T>& src) :
        CommandFlag()
    {
        *this = src;
    }

    // Move Constructor
    template <class T>
    CommandFlag<T>::CommandFlag(_In_ CommandFlag<T>&& src) noexcept :
        CommandFlag()
    {
        *this = std::move(src);
    }

    // Destructor //

    // Default Destructor
    template <class T>
    CommandFlag<T>::~CommandFlag() = default;

    // Assignment Overload //

    template <class T>
    CommandFlag<T>& CommandFlag<T>::operator=(_In_ const CommandFlag<T>& src)
    {
        if ( this != &src )
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

    template <class T>
    CommandFlag<T>& CommandFlag<T>::operator=(_In_ CommandFlag<T>&& src) noexcept
    {
        if ( this != &src )
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

    template <class T>
    const std::basic_string<T>& CommandFlag<T>::GetFlag() const noexcept
    {
        return m_Flag;
    }

    template <class T>
    const std::basic_string<T>& CommandFlag<T>::GetFlagData() const noexcept
    {
        return m_FlagData;
    }

    template <class T>
    const typename CommandFlag<T>::CallbackFunction& CommandFlag<T>::GetCallbackFunction() const noexcept
    {
        return m_CallbackFunc;
    }

    template <class T>
    bool CommandFlag<T>::IsCallbackFunctionTriggered() const noexcept
    {
        return m_bCallbackTriggered;
    }

    template <class T>
    bool CommandFlag<T>::IsFlagOptional() const noexcept
    {
        return m_bFlagOptional;
    }

    template <class T>
    bool CommandFlag<T>::IsFlagDataAccepted() const noexcept
    {
        return m_bFlagDataAccepted;
    }

    template <class T>
    bool CommandFlag<T>::IsFlagDataOptional() const noexcept
    {
        return m_bFlagDataOptional;
    }

    template <class T>
    bool CommandFlag<T>::IsFlagPresent() const noexcept
    {
        return m_bFlagPresent;
    }

    template <class T>
    bool CommandFlag<T>::IsFlagDataPresent() const noexcept
    {
        return m_bFlagDataPresent;
    }

    // Setters //

    template <class T>
    void CommandFlag<T>::SetFlagData(_In_ const std::basic_string<T>& data)
    {
        m_FlagData = data;
    }

    template <class T>
    void CommandFlag<T>::SetFlagData(_In_ std::basic_string<T>&& data) noexcept
    {
        m_FlagData = std::move(data);
    }

    template <class T>
    void CommandFlag<T>::SetCallbackFunction(_In_ const CallbackFunction& func)
    {
        m_CallbackFunc = func;
    }

    template <class T>
    void CommandFlag<T>::SetCallbackFunctionTriggered(_In_ const bool triggered) noexcept
    {
        m_bCallbackTriggered = triggered;
    }

    template <class T>
    void CommandFlag<T>::SetFlagOptional(_In_ const bool flagOpt) noexcept
    {
        m_bFlagOptional = flagOpt;
    }

    template <class T>
    void CommandFlag<T>::SetFlagDataAccepted(_In_ const bool dataExpected) noexcept
    {
        m_bFlagDataAccepted = dataExpected;
    }

    template <class T>
    void CommandFlag<T>::SetFlagDataOptional(_In_ const bool dataOpt) noexcept
    {
        m_bFlagDataOptional = dataOpt;
    }

    template <class T>
    void CommandFlag<T>::SetFlagPresent(_In_ const bool flagPresent) noexcept
    {
        m_bFlagPresent = flagPresent;
    }

    template <class T>
    void CommandFlag<T>::SetFlagDataPresent(_In_ const bool dataPresent) noexcept
    {
        m_bFlagDataPresent = dataPresent;
    }

    // Explicit Template Instantiation //

    template class CommandFlag<char>;
    template class CommandFlag<wchar_t>;
}