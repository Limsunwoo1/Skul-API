#include "Application.h"
#include "windowsAPI.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "EventManager.h"
#include "Time.h"
#include "Input.h"
#include "CollisionManager.h"
#include "Camera.h"
#include "UIManager.h"
#include "MemoryAllocator.h"
#include "MemoryTracer.h"
#include "CrashHandler.h"
#include "Loger.h"
#include "ObjectManager.h"

namespace sw
{
	//Application Application::mInstance;


	Application::Application()
	{
		mWindowData.clear();
	}

	Application::~Application()
	{

	}

	void Application::Initialize(WindowData data)
	{
		// 디버그용 클래스 초기화 구간
#ifdef USE_LOGER
		CLoger::GetInstance()->Init();
#endif
#ifdef USE_CRASH_HANDLER
		NotTraceAllocate([]() {
			CCrashHandler::GetInstance()->Init();
			});
#endif
		//

		Application::initialize(data);

		Time::GetInstance()->Initialize();
		Input::GetInstance()->Initialize();
		ObjectManager::GetInstance()->Initialize();
		SceneManager::GetInstance()->Initalize();
		UIManager::GetInstance()->Initialize();
		Camera::GetInstance()->Initialize();
	}

	void Application::initializeAtlasWindow(WindowData data)
	{
		mAtlasWindowData = data;
		mAtlasWindowData.hdc = GetDC(data.hWnd);
	}
		
	void Application::initialize(WindowData data)
	{
		mWindowData = data;
		mWindowData.hdc = GetDC(data.hWnd);

		// 1922
		// 비트맵 해상도를 설정하기 위한 실제 윈도우 크기 계산
		RECT rect = { 0,0, data.width, data.height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		// 윈도우 크기 변경
		SetWindowPos(data.hWnd,
			nullptr, 0, 0
			, rect.right - rect.left
			, rect.bottom - rect.top
			, 0);
		ShowWindow(data.hWnd, true);

		mWindowData.backTexture
			= CreateCompatibleBitmap(mWindowData.hdc, mWindowData.width, mWindowData.height);


		mWindowData.backbuffer = CreateCompatibleDC(mWindowData.hdc);
		HBITMAP dafaultBitmap
			= (HBITMAP)SelectObject(mWindowData.backbuffer, mWindowData.backTexture);
		
		DeleteObject(dafaultBitmap);

		// 메모리 해재 해주어야한다.
		mPens[(UINT)ePenColor::Red] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		mPens[(UINT)ePenColor::Green] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
		mPens[(UINT)ePenColor::Blue] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

		mBrushes[(UINT)eBrushColor::Transparent] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
		mBrushes[(UINT)eBrushColor::Black] = (HBRUSH)GetStockObject(BLACK_BRUSH);
		mBrushes[(UINT)eBrushColor::Gray] = CreateSolidBrush(RGB(71, 71, 71));
		mBrushes[(UINT)eBrushColor::White] = (HBRUSH)GetStockObject(WHITE_BRUSH);

		mMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_WINDOWSAPI));
	}

	void Application::SetMenuBar(bool power)
	{
		SetMenu(mWindowData.hWnd, mMenu);

		// 클라이언트 크기게 맞춤
		RECT rect = { 0, 0, mWindowData.width, mWindowData.height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, power);

		//윈도우 크기변경
		SetWindowPos(mWindowData.hWnd
			, nullptr, 0, 0
			, rect.right - rect.left
			, rect.bottom - rect.top
			, 0);

		ShowWindow(mWindowData.hWnd, true);
	}

	void Application::Tick()
	{
		Time::GetInstance()->Tick();
		Input::GetInstance()->Tick();
		UIManager::GetInstance()->Tick();

		SceneManager::GetInstance()->Tick();
		CollisionManager::GetInstance()->Tick();
		Camera::GetInstance()->Tick();
		

		Application::Render();

		// 모든 업데이트 렌더링 후 add, delete 
		EventManager::GetInstance()->Tick();
	}

	void Application::Render()
	{
		// Clear
		Rectangle(mWindowData.backbuffer,
			-1, -1, 
			mWindowData.width + 1, mWindowData.height + 1);

		// 더블 버퍼링
		// ===========================================
		SceneManager::GetInstance()->Render(mWindowData.backbuffer);

		UIManager::GetInstance()->Render(mWindowData.backbuffer);
		Camera::GetInstance()->Render(mWindowData.backbuffer);
		Time::GetInstance()->Render(mWindowData.backbuffer);
		Input::GetInstance()->Render(mWindowData.backbuffer);

		// BitBle 함수는 DC간에 이미지를 복사 해주는 함수
		BitBlt(mWindowData.hdc, 0, 0, mWindowData.width, mWindowData.height,
			mWindowData.backbuffer, 0, 0, SRCCOPY);
		// ===========================================
	}

	void Application::Clear()
	{
		Application::Distroyer();

		ReleaseDC(mWindowData.hWnd, mWindowData.hdc);
		ReleaseDC(mWindowData.hWnd, mWindowData.backbuffer);

		for (HPEN pen : mPens)
		{
			if (!pen)
				continue;

			DeleteObject(pen);
		}

		for (HBRUSH brush : mBrushes)
		{
			if (!brush)
				continue;

			DeleteObject(brush);
		}
	}

	void Application::Distroyer()
	{
		// 매니저 클래스 인스턴스 해제
		ObjectManager::GetInstance()->Release();
		SceneManager::GetInstance()->Release();
		ResourceManager::GetInstance()->Release();


		ObjectManager::GetInstance()->DestroyInstance();
		SceneManager::GetInstance()->DestroyInstance();
		UIManager::GetInstance()->DestroyInstance();
		ResourceManager::GetInstance()->DestroyInstance();
		Time::GetInstance()->DestroyInstance();
		Input::GetInstance()->DestroyInstance();
		EventManager::GetInstance()->DestroyInstance();
		CollisionManager::GetInstance()->DestroyInstance();
		Camera::GetInstance()->DestroyInstance();

		// 디버거 소멸
		CLoger::GetInstance()->DistroyInstance();
	}
}
