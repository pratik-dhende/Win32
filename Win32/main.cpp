#ifndef UNICODE
#define UNICODE
#endif 

#include<Windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{	
	// Register the window class.
	const wchar_t CLASS_NAME[] = L"Sample Window Class";

	WNDCLASS wc = { };

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME; // local to current process (shouldn't conflict with window control class names)

	// This function registers the window class with the operating system
	RegisterClass(&wc);

	HWND hwnd = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		L"Application",    // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		nullptr        // Additional application data
	);

	if (hwnd == NULL)
	{
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);

	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		// The DispatchMessage function tells the operating system to call the window procedure of the window that is the target of the message
		DispatchMessage(&msg);
	}
	
	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				// This function fills in the PAINTSTRUCT structure with information on the repaint request
				HDC hdc = BeginPaint(hwnd, &ps);

				// All painting occurs here, between BeginPaint and EndPaint.
			
				// In this case, we pass in the entire update region (the rcPaint member of PAINTSTRUCT). On the first WM_PAINT message, the entire client area needs to be painted, so rcPaint will contain the entire client area. On subsequent WM_PAINT messages, rcPaint might contain a smaller rectangle
				FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

				// This function clears the update region, which signals to Windows that the window has completed painting itself
				EndPaint(hwnd, &ps);
			}
			return 0;

		case WM_DESTROY:
			{	
				// WM_CLOSE -> Prompt user / send to DefWindowProc -> Destory -> WM_DESTROY -> PostQuitMessage(0) adds 0 which adds WM_QUIT to queue 
				PostQuitMessage(0);
				return 0;
			}
			return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}