#pragma once
#include <string>
#include <stdexcept>
#include <cstdio>
using namespace std;

#define STRING(...) sw::UtilString::Format(__VA_ARGS__)

namespace sw
{
	template<class char_t>
	struct _FormatFunction {};

	template<>
	struct _FormatFunction<char>
	{
		template<class... Args>
		int operator()(Args&&... InArgs)
		{
			return std::snprintf(std::forward<Args>(InArgs)...);
		}
	};

	template<>
	struct _FormatFunction<wchar_t>
	{
		template<class... Args>
		int operator()(Args&&... InArgs)
		{
			return std::swprintf(std::forward<Args>(InArgs)...);
		}
	};

	namespace UtilString
	{
		template<typename... Args>
		basic_string<char> Format(const basic_string<char>& InFormat, Args&&... InArgs)
		{
			if (InFormat.size() == 0 || sizeof...(Args) == 0)
				return InFormat;

			_FormatFunction<char> func{};

			int size_s = func(nullptr, 0, InFormat.c_str(), InArgs...);
			if (size_s <= 0)
				throw std::runtime_error("Error during formatting");

			auto size = static_cast<size_t>(size_s);

			std::basic_string<char> ret(size, 0);

			func(&ret[0], (size + 1) * sizeof(char), InFormat.c_str(), InArgs...);
			return ret;
		}

		template<typename... Args>
		basic_string<wchar_t> Format(const basic_string<wchar_t>& InFormat, Args&&... InArgs)
		{
			if (InFormat.size() == 0 || sizeof...(Args) == 0)
				return InFormat;

			_FormatFunction<wchar_t> func{};

			int size_s = func(nullptr, 0, InFormat.c_str(), InArgs...);
			if (size_s <= 0)
				throw std::runtime_error("Error during formatting");

			auto size = static_cast<size_t>(size_s);

			std::basic_string<wchar_t> ret(size, 0);

			func(&ret[0], (size + 1) * sizeof(wchar_t), InFormat.c_str(), InArgs...);
			return ret;
		}
	}
}