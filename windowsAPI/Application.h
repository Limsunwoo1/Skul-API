#pragma once
#include "Common.h"

namespace sw
{
	class Application
	{
	public:
		static Application& GetInstance()
		{
			static Application mInstance;
			return mInstance;
		}


		void Initialize(WindowData data);
		void initializeAtlasWindow(WindowData data);
		void Tick();
		void Render();

		void Clear();

		WindowData GetWindowData() { return mWindowData; }
		WindowData GetAtlasWindowData() { return mAtlasWindowData; }
		HDC GetWindowDC() { return mWindowData.hdc; }

		void SetMenuBar(bool power);

		const HPEN &GetPen(ePenColor color)const { return mPens[(UINT)color]; }
		const HBRUSH &GetBrush(eBrushColor color)const { return mBrushes[(UINT)color]; }

	private:
		Application();
		~Application();

		void initialize(WindowData data);
		void Distroyer();

	private:
		//static Application mInstance;
		WindowData mWindowData;
		WindowData mAtlasWindowData;

		HMENU mMenu;


		HPEN mPens[(UINT)ePenColor::End];
		HBRUSH mBrushes[(UINT)eBrushColor::End];
	};
}

