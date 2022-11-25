

#include <complex>

#include "SDL.h"



int main( int argc, char* argv[] )
{
    const int windowWidth = 1920;
    const int windowHeight = 1080;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(
        "SDL2 Test",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        windowWidth, windowHeight,
        SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);
    

    int playerX = windowWidth * 0.5;
    int playerY = windowHeight * 0.5;
    int playerMoveXInput = 0;
    int playerMoveYInput = 0;
    float playerVelocityX = 0.0;
    float playerVelocityY = 0.0;
    
    
    bool running = true;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                { running =  false; break; }

            case SDL_KEYDOWN:
                {
                    int scancode = event.key.keysym.scancode;
                    if (scancode == SDL_SCANCODE_ESCAPE)
                    {
                        running = false;
                        break;
                    }
                    if (scancode == SDL_SCANCODE_W)
                    {
                        playerMoveYInput = SDL_clamp(playerMoveYInput -1, -1, 0);
                    }
                    if (scancode == SDL_SCANCODE_A)
                    {
                        playerMoveXInput = SDL_clamp(playerMoveXInput - 1, -1, 0);
                    }
                    if (scancode == SDL_SCANCODE_S)
                    {
                        playerY += 1;
                    }
                    if (scancode == SDL_SCANCODE_D)
                    {
                        playerX += 1;
                    }
                }
                
            case SDL_KEYUP:
                {
                    int scancode = event.key.keysym.scancode;

                    if (scancode == SDL_SCANCODE_W)
                    {
                        // Move
                    }
                    if (scancode == SDL_SCANCODE_A)
                    {
                        // Move
                    }
                    if (scancode == SDL_SCANCODE_S)
                    {
                        // Move
                    }
                    if (scancode == SDL_SCANCODE_D)
                    {
                        // Move
                    }
                }
                
            default: continue;
            }
        }

        SDL_SetRenderDrawColor(renderer, 10, 100, 10, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        SDL_Rect player = {playerX, playerY, 32, 32};
        SDL_RenderFillRect(renderer, &player);



        
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}













//
// #include "framework.h"
// #include "SDL_Playground.h"
//
// #define MAX_LOADSTRING 100
//
// // Global Variables:
// HINSTANCE hInst;                                // current instance
// WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
// WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
//
// // Forward declarations of functions included in this code module:
// ATOM                MyRegisterClass(HINSTANCE hInstance);
// BOOL                InitInstance(HINSTANCE, int);
// LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
// INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
//
// int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
//                      _In_opt_ HINSTANCE hPrevInstance,
//                      _In_ LPWSTR    lpCmdLine,
//                      _In_ int       nCmdShow)
// {
//     UNREFERENCED_PARAMETER(hPrevInstance);
//     UNREFERENCED_PARAMETER(lpCmdLine);
//
//     // TODO: Place code here.
//
//     // Initialize global strings
//     LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
//     LoadStringW(hInstance, IDC_SDLPLAYGROUND, szWindowClass, MAX_LOADSTRING);
//     MyRegisterClass(hInstance);
//
//     // Perform application initialization:
//     if (!InitInstance (hInstance, nCmdShow))
//     {
//         return FALSE;
//     }
//
//     HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SDLPLAYGROUND));
//
//     MSG msg;
//
//     // Main message loop:
//     while (GetMessage(&msg, nullptr, 0, 0))
//     {
//         if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
//         {
//             TranslateMessage(&msg);
//             DispatchMessage(&msg);
//         }
//     }
//
//     return (int) msg.wParam;
// }
//
//
//
// //
// //  FUNCTION: MyRegisterClass()
// //
// //  PURPOSE: Registers the window class.
// //
// ATOM MyRegisterClass(HINSTANCE hInstance)
// {
//     WNDCLASSEXW wcex;
//
//     wcex.cbSize = sizeof(WNDCLASSEX);
//
//     wcex.style          = CS_HREDRAW | CS_VREDRAW;
//     wcex.lpfnWndProc    = WndProc;
//     wcex.cbClsExtra     = 0;
//     wcex.cbWndExtra     = 0;
//     wcex.hInstance      = hInstance;
//     wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SDLPLAYGROUND));
//     wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
//     wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
//     wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SDLPLAYGROUND);
//     wcex.lpszClassName  = szWindowClass;
//     wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
//
//     return RegisterClassExW(&wcex);
// }
//
// //
// //   FUNCTION: InitInstance(HINSTANCE, int)
// //
// //   PURPOSE: Saves instance handle and creates main window
// //
// //   COMMENTS:
// //
// //        In this function, we save the instance handle in a global variable and
// //        create and display the main program window.
// //
// BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
// {
//    hInst = hInstance; // Store instance handle in our global variable
//
//    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
//       CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
//
//    if (!hWnd)
//    {
//       return FALSE;
//    }
//
//    ShowWindow(hWnd, nCmdShow);
//    UpdateWindow(hWnd);
//
//    return TRUE;
// }
//
// //
// //  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
// //
// //  PURPOSE: Processes messages for the main window.
// //
// //  WM_COMMAND  - process the application menu
// //  WM_PAINT    - Paint the main window
// //  WM_DESTROY  - post a quit message and return
// //
// //
// LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
// {
//     switch (message)
//     {
//     case WM_COMMAND:
//         {
//             int wmId = LOWORD(wParam);
//             // Parse the menu selections:
//             switch (wmId)
//             {
//             case IDM_ABOUT:
//                 DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
//                 break;
//             case IDM_EXIT:
//                 DestroyWindow(hWnd);
//                 break;
//             default:
//                 return DefWindowProc(hWnd, message, wParam, lParam);
//             }
//         }
//         break;
//     case WM_PAINT:
//         {
//             PAINTSTRUCT ps;
//             HDC hdc = BeginPaint(hWnd, &ps);
//             // TODO: Add any drawing code that uses hdc here...
//             EndPaint(hWnd, &ps);
//         }
//         break;
//     case WM_DESTROY:
//         PostQuitMessage(0);
//         break;
//     default:
//         return DefWindowProc(hWnd, message, wParam, lParam);
//     }
//     return 0;
// }
//
// // Message handler for about box.
// INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
// {
//     UNREFERENCED_PARAMETER(lParam);
//     switch (message)
//     {
//     case WM_INITDIALOG:
//         return (INT_PTR)TRUE;
//
//     case WM_COMMAND:
//         if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
//         {
//             EndDialog(hDlg, LOWORD(wParam));
//             return (INT_PTR)TRUE;
//         }
//         break;
//     }
//     return (INT_PTR)FALSE;
// }