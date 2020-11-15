# include <Windows.h>

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	const auto tClassName = L"D3D11Graphics";
	//Register window class
	WNDCLASSEX tWindowClass = { 0 };
	tWindowClass.cbSize = sizeof(tWindowClass);
	tWindowClass.style = CS_OWNDC;
	tWindowClass.lpfnWndProc = DefWindowProc; // use default window procedure
	tWindowClass.cbClsExtra = 0;
	tWindowClass.cbWndExtra = 0;
	tWindowClass.hInstance = hInstance;
	tWindowClass.hIcon = nullptr;
	tWindowClass.hCursor = nullptr;
	tWindowClass.hbrBackground = nullptr;
	tWindowClass.lpszMenuName = nullptr;
	tWindowClass.lpszClassName = tClassName;
	tWindowClass.hIconSm = nullptr;

	RegisterClassEx(&tWindowClass);

	//Create window instance
	HWND tWindow = CreateWindowEx(0, tClassName, L"Sample-001-Create-Window", WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, 0, 0, 1280, 720, nullptr, nullptr, hInstance, nullptr);
	ShowWindow(tWindow, SW_SHOW);

	// Pump message
	MSG tMsg;
	while (GetMessage(&tMsg, nullptr, 0, 0))
	{
		TranslateMessage(&tMsg);
		DispatchMessage(&tMsg);
	}
	return 0;
}