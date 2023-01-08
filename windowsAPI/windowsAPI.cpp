// windowsAPI.cpp : 애플리케이션에 대한 진입점을 정의합니다.


// 1. 맵 툴 파일 입출력
//    타일과 충돌박스 생성하는 툴
// 2. 유한상태패턴
//    플레이어의 기본적인 공격, 점프, 이동, 스킬, 
//     스컬교체 구현 (스컬 교체는 스컬게임의 핵심인 플레이어의 속성을 바꾼다)
//     몬스터의 상태 Idle, Move, Attack, Hit 상태 구현
//     보스몬스터의 패턴 구현
// 3. 제네릭애니메이터
//    시작값과 최종값 사이를 시간의 흐름에 따라 보간해주는 기능에
//    함수 포인터를 통해 이벤트를 연결할수 있게 만들어서
//    다양한 상황에서 사용할수 있게 만듬 (사무라이 광역스킬)
// 4. 이펙트
//    오브젝트풀링을 이용한 최적화
// 5. AABB 충돌 로직 사용
// 6. 컴포넌트 패턴 사용 애니메이터, 콜리더, 리지드바디
// 7. 각 스테이트 혹은 스킬등에 필요한 키값이 wstring 이어서 
// 오타에 때문에 개발속도 지연 개선방안 enum 값을 사용해보자
// 8. 플레이어와 보스 - 오브젝트의 핸들러를 만들어 두개이상의 오브젝트를 하나로 컨트롤함
// 9. 방향벡터를 이용한 움직임 구현
// 10. 이벤트 매니저 - Scene Change, Add Object, Delete Object
// 이벤트 기능을만들어 런타임중이아닌 최종 렌더후에 
// 오브젝트의 추가 및 삭제 그리구 씬 교체를 위한 매니저
// 11. 가독성을 위해 애니메이션 파일경로 디파인값을 이용하여 가독성 개선
// 12. 

#include "windowsAPI.h"
#include "Application.h"

#include "SceneManager.h"
#include "ToolScene.h"
#include "TilePalette.h"
#include "Image.h"
//#include "MemoryAllocator.h"

//#ifdef UNICODE
//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
//#else
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
//#endif

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance, WNDPROC wndProc, LPCWSTR windowname);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    AtlasWndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // 메모리 누수를 체크해주는 함수
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(194775);

    // 1. wndclass 정의 윈도우의 기반(여러가지 속성)이되는 클래스를 정의해준다.
    // 
    // 2. 메모리상에우니도우를 할당해야한다. (CreatWindow)
    // 
    // 3. Showwindow 함수를 통해서 윈도우가 화면에 보여진다. (update window)
    // 
    // 4. winclass 정의할때 넣어준 함수포인터에 넣어준 loop (wndproc) 매 프레임마다 실핸한다. wndproc-(우리가 제어할 부분이다)

    // 5. 윈도우즈는 크게 3가지 라이브러리로 이루어져 있는데.
    // 메모리를 관리하고 실행시키는 KERNEL 커널
    // 유저 인터페이스와 관리하는 USER
    // 화면처리와 그래픽을 담당하는 GDI 로 이루어져있다.




    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSAPI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance, WndProc, szWindowClass);
    MyRegisterClass(hInstance, AtlasWndProc,L"AtlasWindow");

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSAPI));

    MSG msg;

    // GetMaessage : 프로세스에 발생한 메시지를 메세지 큐에서 꺼내서내옴
    // 메세지가 있을때만 메세지를 꺼내온다.
    // 메세지 case 함수를 호출해준다.
    
    
    // PeekMessage : 발생한 메세지를 가져 올때 메세지큐에서 따로 제거해줘야한다.
    // 메세지큐에 메세지가 들어있는 유/무에 관계없이 함수가 리턴된다.



    // 기본 메시지 루프입니다:
    while (1)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            // 게임 실행
            sw::Application::GetInstance().Tick();
            //DestoryMemoryAllocator();
        }
    }

    // 종료가 되었을때
    if (WM_QUIT == msg.message)
    {
        // 메모리 해제 작업
        sw::Application::GetInstance().Clear();
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance, WNDPROC wndProc, LPCWSTR windowName)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    // 생성할 윈도우의 속성
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = wndProc; //함수포인터
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSAPI)); // 아이콘모양
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW); // 마우스 커서모양
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1); // 배겨 색
    wcex.lpszMenuName   = nullptr;  /*MAKEINTRESOURCEW(IDC_WINDOWSAPI);*/ // 창이름  
    wcex.lpszClassName  = windowName; // 프로그램 클래스이름
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.
   
   WindowData windowData;
   windowData.width = 1600;
   windowData.height = 900;


   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, // - 창스타일
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   //  창시작 위지 // 창의 가로세로 크기  //-부모핸들 - 메뉴 //- 메인핸들 - 구조체번지수

   windowData.hWnd = hWnd;
   windowData.hdc = nullptr;

   if (!hWnd)
   {
      return FALSE;
   }

   SetWindowPos(hWnd, nullptr, 0, 0, windowData.width, windowData.height, 0);
   ShowWindow(hWnd, nCmdShow); // 생성한 윈도우를 그려주는 함수
   UpdateWindow(hWnd);         // 윈도우창 업데이트

   sw::Application::GetInstance().Initialize(windowData);

   if (sw::SceneManager::GetInstance()->CheckCurScen(eSceneType::Tool) == false)
       return TRUE;
   
   WindowData atlasWindowdata;
   hWnd = CreateWindowW(L"AtlasWindow", szTitle, WS_OVERLAPPEDWINDOW,
       CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   atlasWindowdata.hWnd = hWnd;

   sw::Application::GetInstance().initializeAtlasWindow(atlasWindowdata);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // 무효화 영역 발생시키기 ( WM_PAINT 메세지를 호출해주겠다)
    //InvalidateRect(hWnd, nullptr, false);

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;

            case ID_SAVE:
            {
                sw::Scene* scene = sw::SceneManager::GetInstance()->GetPlayScene();
                sw::ToolScene* toolScene = dynamic_cast<sw::ToolScene*>(scene);
                toolScene->SaveTilePalette();
            }
                break;

            case ID_LOAD:
            {
                sw::Scene* scene = sw::SceneManager::GetInstance()->GetPlayScene();
                sw::ToolScene* toolScene = dynamic_cast<sw::ToolScene*>(scene);
                toolScene->LoadTilePalette();
            }
                break;

            case IDM_EXIT:
                //DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            // 스톡오브젝트
            // 화면 지우기
            
            HBRUSH hClearBrush = (HBRUSH)GetStockObject(GRAY_BRUSH);
            HBRUSH oldClearBrush = (HBRUSH)SelectObject(hdc, hClearBrush);
            Rectangle(hdc, -1, -1, 1921, 1081);
            SelectObject(hdc, oldClearBrush);


            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);

            // DC 정리
            // 1. PEN BRUSH 핸들을 선언한다.
            // 2. GDI 오브젝트를 생성해준다.
            // 3. 생선된 오브젝트로 hdc 세팅해줘야한다. selectobject
            
            // 사용하고
            // 기존의 오브젝트로 되돌린다 (해제)
            // 핸들을 삭제한다.
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
