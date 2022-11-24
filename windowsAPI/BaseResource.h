#pragma once
#include "Common.h"

namespace sw
{
	class BaseResource
	{
	public:
		BaseResource();
		virtual ~BaseResource();

		virtual HRESULT Load(const std::wstring& path) = 0;

		const std::wstring& GetKey() { return mKey; }
		const std::wstring& GetPath() { return mPath; }
		
		const void SetKey(const std::wstring key) { mKey = key; }
		const void SetPath(const std::wstring path) { mPath = path; }

	private:
		std::wstring mPath;
		std::wstring mKey;
	};
}

