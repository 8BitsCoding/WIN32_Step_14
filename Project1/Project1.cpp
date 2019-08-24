// Project1.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Project1.h"

#define MAX_COUNT 5
int g_index[MAX_COUNT] = { 0, };

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_PAINT) {
		PAINTSTRUCT ps;
		HDC h_dc = BeginPaint(hWnd, &ps);

		for (int i = 0; i < MAX_COUNT; i++) {
			Rectangle(h_dc, i * 100, 0, 101 + i * 100, 101);
			Rectangle(h_dc, i * 100, 100, 101 + i * 100, 200);
		}

		// 설명을 위한 작은 네모 
		HGDIOBJ h_old_brush = SelectObject(h_dc, GetStockObject(NULL_BRUSH));

		for (int i = 0; i < MAX_COUNT; i++) {
			Rectangle(h_dc, i * 100 - 40, 5, 101 + i * 100 - 50, 95);
		}

		SelectObject(h_dc, GetStockObject(BLACK_BRUSH));

		for (int i = 0; i < MAX_COUNT; i++) {
			if (g_index[i] == 1)	Ellipse(h_dc, i * 100 + 50, 50, 101 + i * 100 + 50, 150);
		}
		
		SelectObject(h_dc, h_old_brush);

		EndPaint(hWnd, &ps);
		return 0;
	}
	else if (uMsg == WM_LBUTTONDOWN) {
		UINT x = LOWORD(lParam);
		UINT y = HIWORD(lParam);

		if (y >= 0 && y < 100) {
			//UINT index = x / 100;
			UINT index = (x + 50) / 100;
			if (index < MAX_COUNT) {
				/*
				int remain = x % 100;
				if (remain < 50) index++;
				*/
				g_index[index] = !g_index[index];
				InvalidateRect(hWnd, NULL, TRUE);
			}
		}
	}
	else if (uMsg == WM_DESTROY) PostQuitMessage(0);

	
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;

	wchar_t my_class_name[] = L"tipssoft";

	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = my_class_name;
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	HWND hWnd = CreateWindow(my_class_name, L"www.tipssoft.com",
		WS_OVERLAPPEDWINDOW, 100, 90, 400, 350, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}