# include <Windows.h>

int WINAPI WinMain( HINSTANCE hInstance,		// A handle to the current instance of the application.
					HINSTANCE hPrevInstance,	// A handle to the previous instance of the application.
					LPSTR lpCmdLine,			// The command line for the application, excluding the program name.
					int nCmdShow)				// Controls show the window is to be shown.
{
	// Call to the MessageBox function
	//MessageBox(NULL, "Hello, Windows API!", "Hello", MB_OK | MB_ICONINFORMATION);

	// WinMain returns 0 if we exit before we enter message loop, more on that to come
	//return 0;

	WNDCLASSEX WndEx;
	MSG msg;


}