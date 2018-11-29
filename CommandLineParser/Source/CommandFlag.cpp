#include "../Headers/CommandFlag.h"

#include "../../Common/Headers/Types.h"

namespace CLP
{
    /// Constructors \\\

    // String Constructor
    template <class T>
    CommandFlag<T>::CommandFlag(const std::basic_string<T>& flag) :
        CommandFlag(flag, nullptr, true, false, false)
    { }

    // Full Constructor
    template <class T>
    CommandFlag<T>::CommandFlag(const std::basic_string<T>& flag, const CallbackFunction<T>& func, const bool flagOpt, const bool dataAccepted, const bool dataOpt) noexcept :
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
    CommandFlag<T>::CommandFlag(const CommandFlag<T>& src) :
        CommandFlag( )
    {
        *this = src;
    }

    // Move Constructor
    template <class T>
    CommandFlag<T>::CommandFlag(CommandFlag<T>&& src) noexcept :
        CommandFlag( )
    {
        *this = std::move(src);
    }

    /// Destructor \\\

    // Default Destructor
    template <class T>
    CommandFlag<T>::~CommandFlag( ) = default;

    /// Assignment Overload \\\

    template <class T>
    CommandFlag<T>& CommandFlag<T>::operator=(const CommandFlag<T>& src)
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
    CommandFlag<T>& CommandFlag<T>::operator=(CommandFlag<T>&& src) noexcept
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

            src.m_Flag.clear( );
            src.m_CallbackFunc = CallbackFunction<T>( );
            src.m_bFlagOptional = true;
            src.m_bFlagDataAccepted = false;
            src.m_bFlagDataOptional = false;
            src.m_bFlagPresent = false;
            src.m_bFlagDataPresent = false;
        }

        return *this;
    }

    /// Getters \\\

    template <class T>
    const std::basic_string<T>& CommandFlag<T>::GetFlag( ) const noexcept
    {
        return m_Flag;
    }

    template <class T>
    const std::basic_string<T>& CommandFlag<T>::GetFlagData( ) const noexcept
    {
        return m_FlagData;
    }

    template <class T>
    const CommandFlag<T>::CallbackFunction<T>& CommandFlag<T>::GetCallbackFunction( ) const noexcept
    {
        return m_CallbackFunc;
    }

    template <class T>
    const bool& CommandFlag<T>::IsCallbackFunctionTriggered( ) const noexcept
    {
        return m_bCallbackTriggered;
    }

    template <class T>
    const bool& CommandFlag<T>::IsFlagOptional( ) const noexcept
    {
        return m_bFlagOptional;
    }

    template <class T>
    const bool& CommandFlag<T>::IsFlagDataAccepted( ) const noexcept
    {
        return m_bFlagDataAccepted;
    }

    template <class T>
    const bool& CommandFlag<T>::IsFlagDataOptional( ) const noexcept
    {
        return m_bFlagDataOptional;
    }

    template <class T>
    const bool& CommandFlag<T>::IsFlagPresent( ) const noexcept
    {
        return m_bFlagPresent;
    }

    template <class T>
    const bool& CommandFlag<T>::IsFlagDataPresent( ) const noexcept
    {
        return m_bFlagDataPresent;
    }

    /// Setters \\\

    template <class T>
    void CommandFlag<T>::SetFlagData(const std::basic_string<T>& data)
    {
        m_FlagData = data;
    }

    template <class T>
    void CommandFlag<T>::SetFlagData(std::basic_string<T>&& data) noexcept
    {
        m_FlagData = std::move(data);
    }

    template <class T>
    void CommandFlag<T>::SetCallbackFunction(const CallbackFunction<T>& func)
    {
        m_CallbackFunc = func;
    }

    template <class T>
    void CommandFlag<T>::SetCallbackFunctionTriggered(const bool triggered) noexcept
    {
        m_bCallbackTriggered = triggered;
    }

    template <class T>
    void CommandFlag<T>::SetFlagOptional(const bool flagOpt) noexcept
    {
        m_bFlagOptional = flagOpt;
    }

    template <class T>
    void CommandFlag<T>::SetFlagDataAccepted(const bool dataExpected) noexcept
    {
        m_bFlagDataAccepted = dataExpected;
    }

    template <class T>
    void CommandFlag<T>::SetFlagDataOptional(const bool dataOpt) noexcept
    {
        m_bFlagDataOptional = dataOpt;
    }

    template <class T>
    void CommandFlag<T>::SetFlagPresent(const bool flagPresent) noexcept
    {
        m_bFlagPresent = flagPresent;
    }

    template <class T>
    void CommandFlag<T>::SetFlagDataPresent(const bool dataPresent) noexcept
    {
        m_bFlagDataPresent = dataPresent;
    }

    /// Explicit Template Instantiation \\\

    template class CommandFlag<utf8>;
    template class CommandFlag<utf16>;
}