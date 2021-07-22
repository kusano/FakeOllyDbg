#define WIN32_LEAN_AND_MEAN
#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void Main()
{
    HINSTANCE hInstance = GetModuleHandleW(nullptr);

    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = L"OllyDbg";
    wcex.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
    if (RegisterClassExW(&wcex)==0)
    {
        MessageBoxW(nullptr, L"error (RegisterClassExW)", L"FakeOllyDbg", MB_ICONERROR | MB_OK);
        ExitProcess(1);
    }

    HWND hWnd = CreateWindowW(
        L"OllyDbg",
        L"OllyDbg",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        0,
        CW_USEDEFAULT,
        0,
        nullptr,
        nullptr,
        hInstance,
        nullptr);

    if (!hWnd)
    {
        MessageBoxW(nullptr, L"error (CreateWindowW)", L"FakeOllyDbg", MB_ICONERROR | MB_OK);
        ExitProcess(1);
    }

    ShowWindow(hWnd, SW_HIDE);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    MessageBoxW(nullptr, L"exit", L"FakeOllyDbg", MB_ICONINFORMATION | MB_OK);

    ExitProcess((UINT)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
