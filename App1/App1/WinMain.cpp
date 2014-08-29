# include <Windows.h>

// Name of our class and the title
const char *clsName = "WinAPI";
char *title = "Windows API";

// Global flag for our message loop
bool running = true;

// Handle to the window
HWND hWnd = NULL;

// A windows callback procedure
LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		// Message created when the user tries to close the window
		case WM_CLOSE:
			DestroyWindow(hWnd);
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			running = false;
			return 0;

		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}

// Entry point of our application
int WINAPI WinMain(HINSTANCE hInstance,		// A handle to the current instance of the application.
				   HINSTANCE hPrevInstance,	// A handle to the previous instance of the application.
				   LPSTR lpCmdLine,			// The command line for the application, excluding the program name.
				   int nCmdShow)			// Controls show the window is to be shown.
{
	// Call to the MessageBox function
	//MessageBox(NULL, "Hello, Windows API!", "Hello", MB_OK | MB_ICONINFORMATION);

	// WinMain returns 0 if we exit before we enter message loop, more on that to come
	//return 0;

	WNDCLASSEX WndEx;
	MSG msg;

	// The size, in bytes, of this structure.
	WndEx.cbSize = sizeof(WNDCLASSEX);

	// The class style(s)
	WndEx.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

	// A pointer to the window procedure
	WndEx.lpfnWndProc = (WNDPROC) WndProc;

	// The number of extra bytes to allocate following the window-class structure
	WndEx.cbClsExtra = 0;

	// The number of extra bytes to allocate following the window instance
	WndEx.cbWndExtra = 0;

	// A handle to the class icon
	WndEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	// A handle to the class cursor
	WndEx.hCursor = LoadCursor(NULL, IDC_ARROW);

	// A handle to the class background brush
	WndEx.hbrBackground = NULL;

	// We're not using a menu here
	WndEx.lpszMenuName = NULL;

	// A pointer to a string that contains the class name
	WndEx.lpszClassName = clsName;

	// A handle to the instance that contains the window procedure for the class
	WndEx.hInstance = hInstance;

	// A handle to a small icon that is associated with the window class
	WndEx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// Register the windows class
	if (!RegisterClassEx(&WndEx))
	{
		MessageBox(NULL, "Failed to register class", "ERROR", MB_OK | MB_ICONERROR);
		return 0;
	}

	// Create the window
	if (! (hWnd = CreateWindowEx(WS_EX_APPWINDOW | WS_EX_WINDOWEDGE, // The extended window style
								 clsName,							 // A pointer to a string that contains the class name
								 title,								 // A pointer to a string that contains the title of the window
								 WS_OVERLAPPEDWINDOW |				 // The style of the window being created
								 WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
								 CW_USEDEFAULT, CW_USEDEFAULT,		 // initial x, y position of the window
								 460, 340,							 // initial w, h size of the window
								 NULL,								 // A handle to the parent or owner window
								 NULL,								 // A handle to a menu
								 hInstance,							 // A handle to the instance of the window
								 NULL)))							 // lParam
	{
		MessageBox(NULL, "Failed to create the window", "ERROR", MB_OK | MB_ICONERROR);
		return 0;
	}

	// The window is initially hidden, we need to show it
	ShowWindow(hWnd, SW_SHOW);

	while(running)
	{
		// Are there any messages in the message queue?
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}