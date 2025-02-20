#include <windows.h>
#include <stdio.h>

double num1;
double num2;
char character[100];
char textnum1[100];
char textnum2[100];

HWND TEXT, Plus, Minus, Multiply, Divide, num_1, num_2;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		case WM_CREATE:
			TEXT = CreateWindow("STATIC","Please input two numbers", WS_VISIBLE | WS_CHILD | SS_CENTER, 20, 20, 200, 20, hwnd, NULL, NULL, NULL);
			Plus = CreateWindow("Button", "+", WS_VISIBLE | WS_CHILD  , 50, 110, 25, 25, hwnd, (HMENU) 1, NULL, NULL);
			Minus= CreateWindow("Button", "-", WS_VISIBLE | WS_CHILD  , 85, 110, 25, 25, hwnd, (HMENU) 2, NULL, NULL);
			Multiply = CreateWindow("Button", "*", WS_VISIBLE | WS_CHILD , 120, 110, 25, 25, hwnd, (HMENU) 3, NULL, NULL);
			Divide = CreateWindow("Button", "/", WS_VISIBLE | WS_CHILD , 155, 110, 25, 25, hwnd, (HMENU) 4, NULL, NULL);
			num_1 = CreateWindow("EDIT", "",   WS_CHILD | WS_VISIBLE, 40, 50, 160, 20, hwnd, NULL, NULL, NULL);
			num_2 = CreateWindow("EDIT", "",   WS_CHILD | WS_VISIBLE, 40, 80, 160, 20, hwnd, NULL, NULL, NULL);
			break;

		case WM_COMMAND:
			GetWindowText(num_1, &textnum1[0], 100);
			GetWindowText(num_2, &textnum2[0], 100);
			num1 = atof(textnum1);
			num2 = atof(textnum2);
			switch (LOWORD(wParam))
			{
				case 1:
					sprintf(character, "%f", num1 + num2);
					::MessageBox(hwnd, character, "Result", MB_OK);
					break;
				case 2:
					sprintf(character, "%f", num1 - num2);
					::MessageBox(hwnd, character, "Result", MB_OK);
					break;
				case 3:
					sprintf(character, "%f", num1 * num2);
					::MessageBox(hwnd, character, "Result", MB_OK);
					break;
				case 4:
					sprintf(character, "%f", num1 / num2);
					::MessageBox(hwnd, character, "Result", MB_OK);
					break;
			}
			break;

		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; 
	HWND hwnd; 
	MSG msg; 

	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; 
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	wc.hbrBackground = CreateSolidBrush(RGB(142,100,227));;
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); 
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); 

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_SYSMENU,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	while(GetMessage(&msg, NULL, 0, 0) > 0) { 
		TranslateMessage(&msg);
		DispatchMessage(&msg); 
	}
	return msg.wParam;
}