#include "game_layer.h"

#include <sys/stat.h>  

static HINSTANCE Instance;
static HWND Window;
static HDC DeviceContext;
static int32 CommandShow;
static int64 TimerFrequency;

int32 WINAPI
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int32 CmdShow)
{
	CommandShow = CmdShow;
	return Game_Main();
}

LRESULT CALLBACK
WndProc(HWND Window, UINT Message,
	WPARAM wParam, LPARAM lParam)
{
	LRESULT Result = 0;

	switch (Message) 
	{
	case WM_CREATE:
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
	{
	}	break;
	default:
		return DefWindowProc(Window, Message,
			wParam, lParam);
	}

	return Result;
}

void
Platform_Initialize(int32 WindowWidth, int32 WindowHeight)
{
	Instance = GetModuleHandle(0);
#if DEBUG_MODE
	if (Instance == 0)
	{
		MessageBox(0, "Obtaining Window's Instance Failed!",
			"Error!",
			MB_ICONEXCLAMATION | MB_OK);
	}
#endif

	WNDCLASSEX WindowsClassStructure = {};
	WindowsClassStructure.cbSize = sizeof(WNDCLASSEX);
	WindowsClassStructure.style = CS_OWNDC;
	WindowsClassStructure.lpfnWndProc = WndProc;
	WindowsClassStructure.cbClsExtra = 0;
	WindowsClassStructure.cbWndExtra = 0;
	WindowsClassStructure.hInstance = Instance;
	WindowsClassStructure.hIcon = LoadIcon(0, IDI_APPLICATION);
	WindowsClassStructure.hCursor = LoadCursor(0, IDC_ARROW);
	WindowsClassStructure.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WindowsClassStructure.lpszMenuName = 0;
	WindowsClassStructure.lpszClassName = "2DGame";
	WindowsClassStructure.hIconSm = LoadIcon(0, IDI_APPLICATION);

#if DEBUG_MODE
	if (!RegisterClassEx(&WindowsClassStructure))
	{
		MessageBox(0, "Window Registration Failed!",
			"Error!",
			MB_ICONEXCLAMATION | MB_OK);
	}
#else
	RegisterClassEx(&WindowsClassStructure);
#endif

	Window = CreateWindowEx(
		WS_EX_CLIENTEDGE, "2DGame",
		"2D Game Build 0.0",
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, WindowWidth,
		WindowHeight, 0, 0, Instance, 0);

#if DEBUG_MODE
	if (Window == 0)
	{
		MessageBox(0, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
	}
#endif

	DeviceContext = GetDC(Window);

#if DEBUG_MODE
	if (DeviceContext == 0)
	{
		MessageBox(0, "Obtaining Device Context Failed!",
			"Error!",
			MB_ICONEXCLAMATION | MB_OK);
	}
#endif

	UpdateWindow(Window);
}


// Accepted values for attribute names for the OpenGL Context(WGL)
#define WGL_CONTEXT_MAJOR_VERSION_ARB				0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB				0x2092
#define WGL_CONTEXT_LAYER_PLANE_ARB					0x2093
#define WGL_CONTEXT_FLAGS_ARB						0x2094
#define WGL_CONTEXT_PROFILE_MASK_ARB				0x9126

// Accepted values for flag bits for the OpenGL Context(WGL)
#define WGL_CONTEXT_DEBUG_BIT_ARB					0x0001
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB		0x0002

// Accepted values for attribute bits for the OpenGL Context(WLG)
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB			0X00000001
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB	0X00000002

//NOTE: Setting up a function pointer's return and parameter
//      types for creating an OpenGL Context.
typedef HGLRC __stdcall wgl_create_context_attribs_arb(HDC hDC,
	HGLRC hShareContext, const int32 *attribList);

void
Platform_InitRenderer()
{
	PIXELFORMATDESCRIPTOR DesiredPixelFormat = {};
	DesiredPixelFormat.nSize = sizeof(DesiredPixelFormat);
	DesiredPixelFormat.nVersion = 1;
	DesiredPixelFormat.dwFlags = PFD_SUPPORT_OPENGL |
		PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
	DesiredPixelFormat.iPixelType = PFD_TYPE_RGBA;
	DesiredPixelFormat.cColorBits = 32;
	DesiredPixelFormat.cAlphaBits = 8;
	DesiredPixelFormat.cDepthBits = 16;
	DesiredPixelFormat.iLayerType = PFD_MAIN_PLANE;

	int32 SuggestedPixelFormatIndex =
		ChoosePixelFormat(DeviceContext,
			&DesiredPixelFormat);
#if DEBUG_MODE
	if (SuggestedPixelFormatIndex == 0)
	{
		MessageBox(0,
			"Obtaining Suggested Pixel Format Index Failed!",
			"Error!",
			MB_ICONEXCLAMATION | MB_OK);
	}
#endif

	PIXELFORMATDESCRIPTOR SuggestedPixelFormat;

#if DEBUG_MODE
	if (!DescribePixelFormat(DeviceContext,
		SuggestedPixelFormatIndex, sizeof(SuggestedPixelFormat),
		&SuggestedPixelFormat))
	{
		MessageBox(0,
			"Obtaining Description of a Pixel Format Failed!",
			"Error!",
			MB_ICONEXCLAMATION | MB_OK);
	}

	if (!SetPixelFormat(DeviceContext,
		SuggestedPixelFormatIndex, &SuggestedPixelFormat))
	{
		MessageBox(0, "Setting Pixel Format Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
	}
#else
	DescribePixelFormat(DeviceContext,
		SuggestedPixelFormatIndex, sizeof(SuggestedPixelFormat),
		&SuggestedPixelFormat);
	SetPixelFormat(DeviceContext,
		SuggestedPixelFormatIndex, &SuggestedPixelFormat);
#endif

	HGLRC OpenGLContext =
		wglCreateContext(DeviceContext);
#if DEBUG_MODE
	if (OpenGLContext == 0)
	{
		MessageBox(0, "Obtaining OpenGL Render Context Failed!",
			"Error!",
			MB_ICONEXCLAMATION | MB_OK);
	}
#endif

	if (wglMakeCurrent(DeviceContext,
		OpenGLContext))
	{
		wgl_create_context_attribs_arb *wglCreateContextAttribsARB =
			(wgl_create_context_attribs_arb *)wglGetProcAddress(
				"wglCreateContextAttribsARB");

		if (wglCreateContextAttribsARB)
		{
			int32 Attribs[] =
			{
				WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
				WGL_CONTEXT_MINOR_VERSION_ARB, 5,
				WGL_CONTEXT_FLAGS_ARB,
				// TODO: Remove Debug for final
				WGL_CONTEXT_DEBUG_BIT_ARB,
				WGL_CONTEXT_PROFILE_MASK_ARB,
				WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
				0
			};
			HGLRC ShareContext = 0;
			HGLRC ModernContext =
				wglCreateContextAttribsARB(
					DeviceContext, ShareContext, Attribs);

			if (ModernContext)
			{
				if (wglMakeCurrent(DeviceContext,
					ModernContext))
				{
					wglDeleteContext(OpenGLContext);
					OpenGLContext = ModernContext;
				}
			}
		}
		else
		{
			MessageBox(0, "wglMakeCurrent Failed!", "Error!",
				MB_ICONEXCLAMATION | MB_OK);
		}
	}
	else
	{
		// TODO: Error
	}
}

void
Platform_ShowWindow()
{
	ShowWindow(Window, CommandShow);
}


int32
Platform_Loop()
{
	MSG Message = {};

	while (Message.message != WM_QUIT)
	{
		if (PeekMessage(&Message, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		Game_Loop();

#if DEBUG_MODE
		if (!SwapBuffers(DeviceContext))
		{
			MessageBox(0, "Swapping Buffers Failed!", "Error!",
				MB_ICONEXCLAMATION | MB_OK);
		}
#else
		SwapBuffers(DeviceContext);
#endif
	}

	return Message.message;
}

void
Platform_ConsoleOutput(char* Text)
{
	// NOTE: Beware of buffer overflow potential.
	OutputDebugStringA(Text);
}

int64
Platform_GetCPUTimerFrequency()
{
	if (TimerFrequency == 0)
	{
		LARGE_INTEGER Frequency;
#if DEBUG_MODE
		if (!QueryPerformanceFrequency(&Frequency))
		{
			// TODO: Error
			MessageBox(0, "Obtaining Timer Frequency Failed!",
				"Error!", MB_ICONEXCLAMATION | MB_OK);
		}
#else
		QueryPerformanceFrequency(&Frequency);
#endif
		TimerFrequency = Frequency.QuadPart;
		return TimerFrequency;
	}
	else
	{
		return TimerFrequency;
	}
}

int64
Platform_GetCPUTimer()
{
	LARGE_INTEGER Time;
#if DEBUG_MODE
	if (!QueryPerformanceCounter(&Time))
	{
		// TODO: Error
		MessageBox(0, "QueryPerformanceCounter Failed!",
			"Error!",
			MB_ICONEXCLAMATION | MB_OK);
	}
#else
	QueryPerformanceCounter(&Time);
#endif
	return Time.QuadPart;
}

int8
Platform_DoesFileExist(char* FileName)
{
	if (GetFileAttributes(FileName) == INVALID_FILE_ATTRIBUTES)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

unsigned char*
Platform_ReadFile(char* FileName)
{
	HANDLE ImageFile;
	ImageFile = CreateFile(FileName, GENERIC_READ, FILE_SHARE_READ, 0,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	DWORD FileSize = GetFileSize(ImageFile, 0);

	uint8* Buffer = new uint8[FileSize]{};

	LPDWORD BytesRead = 0;
	ReadFile(ImageFile, (LPVOID)Buffer, FileSize, BytesRead, 0);
	CloseHandle(ImageFile);
	return Buffer;
}

int8
Platform_GetStateOfKey(int key)
{
	int8 result = 0;

	if (GetAsyncKeyState(key) & 0x8000)
	{
		result = 1;
		return result;
	}
	else
	{
		return result;
	}
}

void
Platform_Cleanup()
{
	wglMakeCurrent(0, 0);
	ReleaseDC(Window, DeviceContext);
}
