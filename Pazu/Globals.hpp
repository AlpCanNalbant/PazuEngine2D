// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#pragma once
#include <memory>
#include <numbers>
#include "Shader.hpp"

namespace Pazu
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-qualifiers"
#pragma GCC diagnostic ignored "-Wliteral-suffix"

	inline const unsigned char *const operator"" UC(const char *const str, size_t) noexcept
	{
		return reinterpret_cast<const unsigned char *const>(str);
	}
	inline const unsigned char *const operator"" uc(const char *const str, size_t) noexcept
	{
		return reinterpret_cast<const unsigned char *const>(str);
	}
	inline const unsigned char *const operator"" Uc(const char *const str, size_t) noexcept
	{
		return reinterpret_cast<const unsigned char *const>(str);
	}
	inline const unsigned char *const operator"" uC(const char *const str, size_t) noexcept
	{
		return reinterpret_cast<const unsigned char *const>(str);
	}

	inline constexpr float operator"" RD(const long double deg) noexcept
	{
		return static_cast<const float>(deg) * std::numbers::pi_v<float> / 180.0f;
	}
	inline constexpr float operator"" rd(const long double deg) noexcept
	{
		return static_cast<const float>(deg) * std::numbers::pi_v<float> / 180.0f;
	}
	inline constexpr float operator"" Rd(const long double deg) noexcept
	{
		return static_cast<const float>(deg) * std::numbers::pi_v<float> / 180.0f;
	}
	inline constexpr float operator"" rD(const long double deg) noexcept
	{
		return static_cast<const float>(deg) * std::numbers::pi_v<float> / 180.0f;
	}

	inline constexpr float operator"" DG(const long double rad) noexcept
	{
		return static_cast<const float>(rad) * 180.0f / std::numbers::pi_v<float>;
	}
	inline constexpr float operator"" dg(const long double rad) noexcept
	{
		return static_cast<const float>(rad) * 180.0f / std::numbers::pi_v<float>;
	}
	inline constexpr float operator"" Dg(const long double rad) noexcept
	{
		return static_cast<const float>(rad) * 180.0f / std::numbers::pi_v<float>;
	}
	inline constexpr float operator"" dG(const long double rad) noexcept
	{
		return static_cast<const float>(rad) * 180.0f / std::numbers::pi_v<float>;
	}

#pragma GCC diagnostic pop

	template <typename T>
	void SafeDelete(T *value)
	{
		delete value;
		value = NULL;
	}

	template <typename T>
	void SafeDeleteArray(T *value)
	{
		delete[] value;
		value = NULL;
	}

	template <typename T>
	void SafeDeleteList(T value)
	{
		while (!value.empty())
			SafeDelete(value.back()), value.pop_back();
	}

	template <typename T>
	void SafeDeleteElement(T value, int index)
	{
		SafeDelete(value[index]);
		value.erase(std::remove(value.begin(), value.end(), value[index]), value.end());
	}

	extern std::shared_ptr<Shader> DefaultShader;
}
