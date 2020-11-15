# include <Windows.h>
# include <iostream>
# include <string>
# include <sstream>

// 自定义的窗口消息处理函数
LRESULT WINAPI CustomWindProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	std::ostringstream tStringStream;
	switch (uMsg)
	{
	case WM_CLOSE:
		PostQuitMessage(69);
		break;
	case WM_KEYDOWN: // Insensitive to upper and lower case, when you control a role, such as use w/s/a/d, use this.
		if (wParam == 'F')
			SetWindowText(hWnd, "New Title");
		break;
	case WM_KEYUP:
		if (wParam == 'F')
			SetWindowText(hWnd, "Next Title");
		break;
	case WM_CHAR: // when you input text, use this.
		break;
	case WM_LBUTTONDOWN:
		const POINTS tMousePoint = MAKEPOINTS(lParam);
		tStringStream << "[Log]: Left Mouse Point: " << tMousePoint.x << ", " << tMousePoint.y << "." << std::endl;
		SetWindowText(hWnd, tStringStream.str().c_str());

		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

// 主程序入口
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	const auto tClassName = "D3D11Graphics";
	//Register window class
	WNDCLASSEX tWindowClass = { 0 };
	tWindowClass.cbSize = sizeof(tWindowClass);
	tWindowClass.style = CS_OWNDC;
	tWindowClass.lpfnWndProc = CustomWindProc; // use custom window procedure
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
	HWND tWindow = CreateWindowEx(0, tClassName, "Sample-002-Message-Process", WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, 0, 0, 1280, 720, nullptr, nullptr, hInstance, nullptr);
	ShowWindow(tWindow, SW_SHOW);

	// Pump message
	MSG tMsg;
	BOOL tResult;
	while (tResult = GetMessage(&tMsg, nullptr, 0, 0))
	{
		TranslateMessage(&tMsg);
		DispatchMessage(&tMsg);
	}

	if (tResult < 0)
		return tResult;
	else
		return tMsg.wParam;

	//return 0;
}