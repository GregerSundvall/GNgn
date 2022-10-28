// SDL_Playground.cpp : Defines the entry point for the application.
//


#include <complex>

#include "SDL.h"

int main( int argc, char* argv[] )
{
    const int WIDTH = 800;
    const int HEIGHT = 600;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("SDL2 Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);


    SDL_Texture* texture;
    int width = 800;
    int height = 600;
    SDL_PixelFormatEnum format = SDL_PIXELFORMAT_RGBA8888;
    SDL_TextureAccess access = SDL_TEXTUREACCESS_STREAMING;
    texture = SDL_CreateTexture(renderer, format, access, width, height);


    Uint8 image[width][height][4];
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            for (int k = 0; k < 4; ++k)
            {
                image[i][j][k] = 0;
            }
        }
    }
    // SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 8, SDL_PIXELFORMAT_RGBA8888);
    

    
    bool running = true;
    while (running)
    {
        if (image[0][0][0] == 255)
        {
            running = false;
            continue;
        }
        void* pixels;
        int pitch;

        if( SDL_LockTexture( texture, NULL, &pixels, &pitch ) != 0 )
        {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't lock texture: %s\n", SDL_GetError());
        }

        for (int i = 0; i < width; ++i)
        {
            for (int j = 0; j < height; ++j)
            {
                for (int k = 0; k < 4; ++k)
                {
                    image[i][j][k] += 1;
                }
            }
        }
        
        memcpy(pixels, image, width * height);

        
        // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        
        // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        // SDL_Rect rect = { (int)x, (int)100, 100, 100 };
        // SDL_RenderFillRect(renderer, &rect);

        SDL_RenderPresent(renderer);
        // SDL_Delay(16);
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
