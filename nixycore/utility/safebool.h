/*
    The Nixy Library
    Code covered by the MIT License

    Author: mutouyun (http://darkc.at)
*/

#pragma once

#include "nixycore/general/general.h"

//////////////////////////////////////////////////////////////////////////
NX_BEG
//////////////////////////////////////////////////////////////////////////

namespace private_safe_bool
{
    class detail
    {
    public:
        typedef void (detail::*bool_type)(void) const;
        void this_type_does_not_support_comparisons(void) const {}
    protected:
        detail() {}
        detail(const detail&) {}
        detail& operator=(const detail&) { return *this; }
        ~detail() {}
    };
};

template <typename T>
class safe_bool : private_safe_bool::detail
    // private or protected inheritance is very important here 
    // as it triggers the access control violation in main.
{
public:
    operator bool_type() const
    {
        return (static_cast<const T*>(this))->checkSafeBool() ? 
            &private_safe_bool::detail::this_type_does_not_support_comparisons : 0;
    }
protected:
    ~safe_bool() {}
};

/*
    Some helpful operators
*/

template <typename T>
bool operator==(const safe_bool<T>& lhs, bool b)
{
    if (lhs)
        return b;
    else
        return (!b);
}

template <typename T>
bool operator!=(const safe_bool<T>& lhs, bool b)
{
    if (lhs)
        return (!b);
    else
        return b;
}

template <typename T>
bool operator==(bool b, const safe_bool<T>& rhs)
{
    return operator==(rhs, b);
}

template <typename T>
bool operator!=(bool b, const safe_bool<T>& rhs)
{
    return operator!=(rhs, b);
}

template <typename T, typename U>
bool operator==(const safe_bool<T>& lhs, const safe_bool<U>& /*rhs*/)
{
    lhs.this_type_does_not_support_comparisons();
    return false;
}

template <typename T, typename U>
bool operator!=(const safe_bool<T>& lhs, const safe_bool<U>& /*rhs*/)
{
    lhs.this_type_does_not_support_comparisons();
    return false;
}

//////////////////////////////////////////////////////////////////////////
NX_END
//////////////////////////////////////////////////////////////////////////
