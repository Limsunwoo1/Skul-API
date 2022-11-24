#include "ToolScene.h"
#include "Application.h"
#include "framework.h"
#include "WindowsAPI.h"

#include "Application.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ToolScene.h"
#include "Image.h"
#include "Input.h"


namespace sw
{

	ToolScene::ToolScene()
	{
		mTilePalette = new TilePalette();
	}

	ToolScene::~ToolScene()
	{
		delete mTilePalette;
	}

	void ToolScene::Initialize()
	{

	}

	void ToolScene::Tick()
	{
        if (mTilePalette)
            mTilePalette->Tick();
	}

	void ToolScene::Render(HDC hdc)
	{
		WindowData mainWindow = Application::GetInstance().GetWindowData();
        Rectangle(hdc, 0, 0, mainWindow.width, mainWindow.height);

		Scene::Render(hdc);

		HPEN GreenPen = CreatePen(PS_SOLID, 2, RGB(0, 130, 0));
		HPEN oldPen = (HPEN)SelectObject(hdc, GreenPen);

		int maxRow = mainWindow.height / TILE_SIZE * TILE_SCALE + 1;
		for (size_t i = 0; i < maxRow; i++)
		{
			MoveToEx(hdc, 0, TILE_SIZE * i * TILE_SCALE, nullptr);
			LineTo(hdc, mainWindow.width, TILE_SIZE * i * TILE_SCALE);
		}

		int maxColumn = mainWindow.width / TILE_SIZE * TILE_SCALE + 1;
		for (size_t i = 0; i < maxColumn; i++)
		{
			MoveToEx(hdc, TILE_SIZE * i * TILE_SCALE, 0, nullptr);
			LineTo(hdc, TILE_SIZE * i * TILE_SCALE, mainWindow.height);
		}

		(HPEN)SelectObject(hdc, oldPen);
		DeleteObject(GreenPen);
	}

	void ToolScene::Enter()
	{
		Application::GetInstance().SetMenuBar(true);
	}

	void ToolScene::Exit()
	{

	}

    void ToolScene::SaveTilePalette()
    {
        mTilePalette->Save();
    }
    void ToolScene::LoadTilePalette()
    {
        mTilePalette->Load();
    }
    void ToolScene::LoadTilePalette(const std::wstring& path)
    {
        mTilePalette->Load(path);
    }

}

LRESULT CALLBACK AtlasWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        WindowData windowData
            = sw::Application::GetInstance().GetWindowData();


        WindowData atlasWindowData
            = sw::Application::GetInstance().GetAtlasWindowData();

        sw::Scene* scene = sw::SceneManager::GetInstance()->GetPlayScene();
        sw::ToolScene* toolScene = dynamic_cast<sw::ToolScene*>(scene);

        sw::Image* atlas = toolScene->GetAtlasImage();

        RECT rect = { 0, 0, atlas->GetWidth() * TILE_SCALE, atlas->GetHeight() * TILE_SCALE };
        AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
        // 윈도우 크기 변경
        SetWindowPos(hWnd
            , nullptr, windowData.width, 0
            , rect.right - rect.left
            , rect.bottom - rect.top
            , 0);

        ShowWindow(hWnd, true);
        UpdateWindow(hWnd);

    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {
        case IDM_ABOUT:
            //DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;

    case WM_LBUTTONDOWN:
    {
        if (GetFocus())
        {
            sw::Vector2 mousePos =
                sw::Input::GetInstance()->GetMousePos(hWnd);

            int y = mousePos.y / (TILE_SIZE * TILE_SCALE);
            int x = mousePos.x / (TILE_SIZE * TILE_SCALE);

            int index = (y * TILE_LINE_X) + (x % TILE_LINE_X);
            sw::Scene* scene = sw::SceneManager::GetInstance()->GetPlayScene();
            sw::ToolScene* toolscene = dynamic_cast<sw::ToolScene*>(scene);
            toolscene -> SetTileIndex(index);
        }

    }
    break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        WindowData atlasWindowData
            = sw::Application::GetInstance().GetAtlasWindowData();

        sw::Scene* scene = sw::SceneManager::GetInstance()->GetPlayScene();
        sw::ToolScene* toolScene = dynamic_cast<sw::ToolScene*>(scene);

        sw::Image* atlas = toolScene->GetAtlasImage();
        sw::Vector2 pos(sw::Vector2::Zero);

        TransparentBlt(hdc, pos.x, pos.y
            , atlas->GetWidth() * TILE_SCALE, atlas->GetHeight() * TILE_SCALE
            , atlas->GetDC(), 0, 0, atlas->GetWidth(), atlas->GetHeight()
            , RGB(255, 0, 255));


        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        //KillTimer(hWnd, 0);
    }
    break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}