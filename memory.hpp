#if !defined(MEMORY_HPP)
#define MEMORY_HPP

#include <memory>
#include <type_traits>

template <auto fn>
using DeleteFromFn = std::integral_constant<decltype(fn), fn>;

template <typename T, auto fn>
using UniquePtr = std::unique_ptr<T, DeleteFromFn<fn>>;

#endif // !defined(MEMORY_HPP)

// vim:set sw=4 ts=4 noet:
