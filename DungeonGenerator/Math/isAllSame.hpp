#pragma once

template <class T, class HEAD, class... TAIL>
struct is_all_same {
	static constexpr bool value = is_all_same<T, HEAD>::value && is_all_same<T, TAIL...>::value;
};


template <class T, class ONEBIT>
struct is_all_same<T, ONEBIT> {
	static constexpr bool value = std::is_same<T, ONEBIT>::value;
};