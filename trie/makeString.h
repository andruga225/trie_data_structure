#pragma once
#include <string>
#include <type_traits>

namespace Impl
{
    template <typename MaybeString>
    inline constexpr bool isString = std::is_convertible_v<MaybeString, std::string>;

    template <>
    inline constexpr bool isString<std::string_view> = true;  // 'cause is not implicitly convertible to std::string
}

template <typename Object>
auto makeString(const Object& object) -> decltype(object.to_string())
{
    return object.to_string();
}

template <typename Numeric>
auto makeString(Numeric value) -> decltype(std::to_string(value))
{
    return std::to_string(value);
}

template <typename Iterable>
auto makeString(const Iterable& iterable)
-> std::enable_if_t<!Impl::isString<Iterable>,
    decltype(makeString(*std::begin(iterable)))>
{
    std::string result;
    for (const auto& i : iterable)
    {
        if (!result.empty())
            result += ';';
        result += makeString(i);
    }

    return result;
}

template <typename String>
auto makeString(String&& s)
-> std::enable_if_t<Impl::isString<String>, std::string>
{
    return std::string(std::forward<String>(s));
}