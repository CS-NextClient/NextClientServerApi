/*
 *  Copyright (c) 2017-2021 Michele Caini
 *  https://github.com/skypjack/entt/wiki/Crash-Course:-events,-signals-and-everything-in-between#delegate
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include <cssdk/public/os_defs.h>
#include <cassert>
#include <cstddef>
#include <functional>
#include <tuple>
#include <type_traits>
#include <utility>

// ReSharper disable CppFunctionIsNotImplemented
// ReSharper disable CppNonExplicitConvertingConstructor

namespace core::detail
{
    /**
     * @brief Transcribes the constness of a type to another type.
     *
     * @tparam To The type to which to transcribe the constness.
     * @tparam From The type from which to transcribe the constness.
    */
    template <typename To, typename From>
    struct ConstnessAs
    {
        /**
         * @brief The type resulting from the transcription of the constness.
        */
        using Type = std::remove_const_t<To>;
    };

    /**
     * @brief Transcribes the constness of a type to another type.
     *
     * @tparam To The type to which to transcribe the constness.
     * @tparam From The type from which to transcribe the constness.
    */
    template <typename To, typename From>
    struct ConstnessAs<To, const From>
    {
        /**
         * @brief The type resulting from the transcription of the constness.
        */
        using Type = std::add_const_t<To>;
    };

    /**
     * @brief Alias template to facilitate the transcription of the constness.
     *
     * @tparam To The type to which to transcribe the constness.
     * @tparam From The type from which to transcribe the constness.
    */
    template <typename To, typename From>
    using ConstnessAsType = typename ConstnessAs<To, From>::Type;

    /**
     * @brief A class to use to push around lists of types, nothing more.
     *
     * @tparam T Types provided by the type list.
    */
    template <typename... T>
    struct TypeList
    {
        /**
         * @brief List type.
        */
        using Type = TypeList;

        /**
         * @brief Compile-time number of elements in the type list.
        */
        static constexpr auto size = sizeof...(T);
    };

    /**
     * @brief Primary template isn't defined on purpose.
    */
    template <std::size_t, typename>
    struct TypeListElement;

    /**
     * @brief Provides compile-time indexed access to the types of a type list.
     *
     * @tparam T First type provided by the type list.
     * @tparam Other Other types provided by the type list.
    */
    template <std::size_t Index, typename T, typename... Other>
    struct TypeListElement<Index, TypeList<T, Other...>> : TypeListElement<Index - 1U, TypeList<Other...>>
    {
    };

    /**
     * @brief Provides compile-time indexed access to the types of a type list.
     *
     * @tparam T First type provided by the type list.
     * @tparam Other Other types provided by the type list.
    */
    template <typename T, typename... Other>
    struct TypeListElement<0U, TypeList<T, Other...>>
    {
        /**
         * @brief Searched type.
        */
        using Type = T;
    };

    /**
     * @brief Helper type.
     *
     * @tparam List Type list to search into.
    */
    template <std::size_t Index, typename List>
    using TypeListElementType = typename TypeListElement<Index, List>::Type;

    template <typename Ret, typename... Args>
    auto FunctionPointer(Ret (*)(Args...)) -> Ret (*)(Args...);

    template <typename Ret, typename Type, typename... Args, typename Other>
    auto FunctionPointer(Ret (*)(Type, Args...), Other&&) -> Ret (*)(Args...);

    template <typename Class, typename Ret, typename... Args, typename... Other>
    auto FunctionPointer(Ret (Class::*)(Args...), Other&&...) -> Ret (*)(Args...);

    template <typename Class, typename Ret, typename... Args, typename... Other>
    auto FunctionPointer(Ret (Class::*)(Args...) const, Other&&...) -> Ret (*)(Args...);

    template <typename Class, typename Type, typename... Other>
    auto FunctionPointer(Type Class::*, Other&&...) -> Type (*)();

    template <typename... Type>
    using FunctionPointerType = decltype(detail::FunctionPointer(std::declval<Type>()...));

    template <typename... Class, typename Ret, typename... Args>
    [[nodiscard]] constexpr auto IndexSequenceFor(Ret (*)(Args...))
    {
        return std::index_sequence_for<Class..., Args...>{};
    }
}

namespace core
{
    /**
     * @brief Used to wrap a function or a member of a specified type.
    */
    template <auto>
    struct DelegateArgType
    {
    };

    /**
     * @brief Constant of type \c DelegateArgType used to disambiguate calls.
    */
    template <auto Func>
    inline constexpr DelegateArgType<Func> DELEGATE_ARG{};

    /**
     * @brief Basic delegate implementation.\n
     * Primary template isn't defined on purpose. All the specializations give a compile-time error
     * unless the template parameter is a function type.
    */
    template <typename>
    class Delegate;

    /**
     * @brief Utility class to use to send around functions and members.
     *
     * Unmanaged delegate for function pointers and members.
     * Users of this class are in charge of disconnecting instances before deleting them.
     *
     * A delegate can be used as a general purpose invoker without memory overhead
     * for free functions possibly with payloads and bound or unbound members.
     *
     * @tparam Ret Return type of a function type.
     * @tparam Args Types of arguments of a function type.
    */
    template <typename Ret, typename... Args>
    class Delegate<Ret(Args...)>
    {
        template <auto Candidate, std::size_t... Index>
        ATTR_OPTIMIZE_HOT [[nodiscard]] static auto Wrap(std::index_sequence<Index...>) noexcept
        {
            using namespace detail;

            return +[](const void* const, Args... args) -> Ret {
                return static_cast<Ret>(std::invoke(Candidate,
                                                    std::forward<TypeListElementType<Index, TypeList<Args...>>>(
                                                        std::get<Index>(std::forward_as_tuple(
                                                            std::forward<Args>(args)...)))...));
            };
        }

        template <auto Candidate, typename Type, std::size_t... Index>
        ATTR_OPTIMIZE_HOT [[nodiscard]] static auto Wrap(Type*, std::index_sequence<Index...>) noexcept
        {
            using namespace detail;

            return +[](const void* const payload, Args... args) -> Ret {
                return static_cast<Ret>(
                    std::invoke(Candidate, static_cast<Type*>(const_cast<ConstnessAsType<void, Type>*>(payload)),
                                std::forward<TypeListElementType<Index, TypeList<Args...>>>(
                                    std::get<Index>(std::forward_as_tuple(std::forward<Args>(args)...)))...));
            };
        }

    public:
        /**
         * @brief Function type of the contained target.
        */
        using FunctionType = Ret(const void*, Args...);

        /**
         * @brief Function type of the delegate.
        */
        using Type = Ret(Args...);

        /**
         * @brief Return type of the delegate.
        */
        using ResultType = Ret;

        /**
         * @brief Default constructor.
        */
        Delegate() noexcept = default;

        /**
         * @brief Constructs a delegate and connects a free function or an unbound member.
         *
         * @tparam Candidate Function or member to connect to the delegate.
        */
        template <auto Candidate>
        Delegate(DelegateArgType<Candidate>) noexcept // cppcheck-suppress noExplicitConstructor
        {
            Connect<Candidate>();
        }

        /**
         * @brief Constructs a delegate and connects a free function with payload or a bound member.
         *
         * @tparam Candidate Function or member to connect to the delegate.
         * @tparam Type Type of class or type of payload.
         *
         * @param value_or_instance A valid object that fits the purpose.
        */
        template <auto Candidate, typename Type>
        Delegate(DelegateArgType<Candidate>, const Type* const value_or_instance) noexcept
        {
            Connect<Candidate>(value_or_instance);
        }

        /**
         * @brief Constructs a delegate and connects an user defined function with optional payload.
         *
         * @param function Function to connect to the delegate.
         * @param payload User defined arbitrary data.
        */
        Delegate(FunctionType* const function, const void* const payload = nullptr) noexcept // cppcheck-suppress noExplicitConstructor
        {
            Connect(function, payload);
        }

        /**
         * @brief Connects a free function or an unbound member to a delegate.
         *
         * @tparam Candidate Function or member to connect to the delegate.
        */
        template <auto Candidate>
        ATTR_OPTIMIZE void Connect() noexcept
        {
            using namespace detail;
            data_ = nullptr;

            if constexpr (std::is_invocable_r_v<Ret, decltype(Candidate), Args...>) {
                fn_ = +[](const void* const, Args... args) -> Ret {
                    return Ret(std::invoke(Candidate, std::forward<Args>(args)...));
                };
            }
            else if constexpr (std::is_member_pointer_v<decltype(Candidate)>) {
                fn_ = Wrap<Candidate>(IndexSequenceFor<TypeListElementType<0, TypeList<Args...>>>(
                    FunctionPointerType<decltype(Candidate)>{}));
            }
            else {
                fn_ = Wrap<Candidate>(IndexSequenceFor(FunctionPointerType<decltype(Candidate)>{}));
            }
        }

        /**
         * @brief Connects a free function with payload or a bound member to a delegate.
         *
         * The delegate isn't responsible for the connected object or the payload.
         * Users must always guarantee that the lifetime of the instance overcomes the one of the delegate.
         *
         * When used to connect a free function with payload, its signature must be such that the instance
         * is the first argument before the ones used to define the delegate itself.
         *
         * @tparam Candidate Function or member to connect to the delegate.
         * @tparam Type Type of class or type of payload.
         *
         * @param value_or_instance A valid object that fits the purpose.
        */
        template <auto Candidate, typename Type>
        ATTR_OPTIMIZE void Connect(const Type* const value_or_instance) noexcept
        {
            using namespace detail;
            data_ = value_or_instance;

            if constexpr (std::is_invocable_r_v<Ret, decltype(Candidate), Type*, Args...>) {
                fn_ = +[](const void* const payload, Args... args) -> Ret {
                    return Ret(std::invoke(Candidate,
                                           static_cast<Type*>(const_cast<ConstnessAsType<void, Type>*>(payload)),
                                           std::forward<Args>(args)...));
                };
            }
            else {
                fn_ = Wrap<Candidate>(value_or_instance,
                                      IndexSequenceFor(FunctionPointerType<decltype(Candidate), Type>{}));
            }
        }

        /**
         * @brief Connects an user defined function with optional payload to a delegate.
         *
         * The delegate isn't responsible for the connected object or the payload.
         * Users must always guarantee that the lifetime of an instance overcomes the one of the delegate.
         *
         * The payload is returned as the first argument to the target function in all cases.
         *
         * @param function Function to connect to the delegate.
         * @param payload User defined arbitrary data.
        */
        void Connect(FunctionType* const function, const void* const payload = nullptr) noexcept
        {
            fn_ = function;
            data_ = payload;
        }

        /**
         * @brief Resets a delegate.\n
         * After a reset, a delegate cannot be invoked anymore.
        */
        void Reset() noexcept
        {
            fn_ = nullptr;
            data_ = nullptr;
        }

        /**
         * @brief Returns the instance or the payload linked to a delegate, if any.
         *
         * @return An opaque pointer to the underlying data.
        */
        [[nodiscard]] const void* Instance() const noexcept
        {
            return data_;
        }

        /**
         * @brief Triggers a delegate.
         *
         * The delegate invokes the underlying function and returns the result.
         * Attempting to trigger an invalid delegate results in undefined behavior.
         *
         * @param args Arguments to use to invoke the underlying function.
         *
         * @return The value returned by the underlying function.
        */
        ATTR_OPTIMIZE_HOT FORCEINLINE Ret operator()(Args... args) const
        {
            assert(static_cast<bool>(*this) && "Delegate is uninitialized.");
            return fn_(data_, std::forward<Args>(args)...);
        }

        /**
         * @brief Checks whether a delegate actually stores a listener.
         *
         * @return \c false if the delegate is empty; \c true otherwise.
        */
        [[nodiscard]] explicit operator bool() const noexcept
        {
            return !(fn_ == nullptr);
        }

        /**
         * @brief Compares the contents of two delegates.
         *
         * @param rhs Delegate with which to compare.
         *
         * @return \c false if the two contents differ; \c true otherwise.
        */
        [[nodiscard]] bool operator==(const Delegate<Ret(Args...)>& rhs) const noexcept
        {
            return fn_ == rhs.fn_ && data_ == rhs.data_;
        }

    private:
        FunctionType* fn_{};
        const void* data_{};
    };

    /**
     * @brief Compares the contents of two delegates.
     *
     * @tparam Ret Return type of a function type.
     * @tparam Args Types of arguments of a function type.
     *
     * @param lhs A valid delegate object.
     * @param rhs A valid delegate object.
     *
     * @return \c true if the two contents differ; \c false otherwise.
    */
    template <typename Ret, typename... Args>
    [[nodiscard]] bool operator!=(const Delegate<Ret(Args...)>& lhs, const Delegate<Ret(Args...)>& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    /**
     * @brief Deduction guide.
     *
     * @tparam Candidate Function or member to connect to the delegate.
    */
    template <auto Candidate>
    Delegate(DelegateArgType<Candidate>) -> Delegate<std::remove_pointer_t<
        detail::FunctionPointerType<decltype(Candidate)>>>;

    /**
     * @brief Deduction guide.
     *
     * @tparam Candidate Function or member to connect to the delegate.
     * @tparam Type Type Type of class or type of payload.
    */
    template <auto Candidate, typename Type>
    Delegate(DelegateArgType<Candidate>, Type*) -> Delegate<std::remove_pointer_t<
        detail::FunctionPointerType<decltype(Candidate), Type>>>;

    /**
     * @brief Deduction guide.
     *
     * @tparam Ret Return type of a function type.
     * @tparam Args Types of arguments of a function type.
    */
    template <typename Ret, typename... Args>
    Delegate(Ret (*)(const void*, Args...), const void* = nullptr) -> Delegate<Ret(Args...)>;
}
