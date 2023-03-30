//
// Created by reece on 29/03/23.
//

#pragma once

namespace vulren::util
{

/// Wrapper is an interface that allows a class to implicitly convert to a reference to it's held type.
/// \tparam T The type that the class wraps.
template <typename T>
class Wrapper
{
public:
    /// Retrieves the value held by the class.
    /// \return The value held by the class.
    virtual T& get() = 0;

    /// Retrieves the value held by the class.
    /// \return The value held by the class.
    inline operator T&()
    { return get(); }
};

/// ValWrapper is an interface that allows a class to implicitly convert to it's held type.
/// \tparam T The type that the class wraps.
template <typename T>
class ValWrapper
{
public:
    /// Retrieves the value held by the class.
    /// \return The value held by the class.
    virtual T get() = 0;

    /// Retrieves the value held by the class.
    /// \return The value held by the class.
    inline operator T()
    { return get(); }
};


/// PtrWrapper is an interface that allows a class to implicitly convert to a pointer of it's held type.
/// \tparam T The type of pointer that the class wraps.
template <typename T>
class PtrWrapper
{
public:
    /// Retrieves the pointer held by the class
    /// \return The pointer held by the class
    virtual T* get() = 0;

    /// Retrieves the pointer held by the class
    /// \return The pointer held by the class
    inline operator T*()
    { return get(); }

    /// Retrieves the pointer held by the class
    /// \return The pointer held by the class
    inline T* operator *()
    { return get(); }

    /// Retrieves the pointer held by the class
    /// \return The pointer held by the class
    inline T* operator ->()
    { return get(); }
};

}