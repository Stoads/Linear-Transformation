// MatrixTutorial.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//
#include "stdafx.h"
#include "MatrixTutorial.h"
#include <vector>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;
typedef struct Vector2 { int x, y; }Vector2;
typedef struct Matrix2 { double arr[2][2]; }Matrix2;
#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.
vector<Vector2> poly;
vector<Matrix2> matr;
vector<Matrix2> pMatr;
Matrix2 mat;
Matrix2 pMat;
int tog,draw;
// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void init() {
	srand((size_t)GetTickCount());
	poly.push_back({ 100,100 });
	poly.push_back({ 100,-100 });
	poly.push_back({ -100,-100});
	poly.push_back({ -100,100 });
	for (auto i : poly)
		matr.push_back({ {1,0,0,1} }), pMatr.push_back({ {1,0,0,1} });
	mat = { 1,0,0,1 },pMat = { 1,0,0,1 };
	draw=tog = 0;
}
int isEqual(Matrix2 *desc,Matrix2 *src) {
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			if (desc->arr[i][j] != src->arr[i][j])return 0;
	return 1;
}
Vector2 getMatMul(Matrix2 *mat,Vector2 *vec) {
	return { (int)(vec->x*mat->arr[0][0] + vec->y*mat->arr[0][1]),
			 (int)(vec->x*mat->arr[1][0] + vec->y*mat->arr[1][1]) };
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
	init();

    // TODO: ���⿡ �ڵ带 �Է��մϴ�.

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MATRIXTUTORIAL, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MATRIXTUTORIAL));

    MSG msg;

    // �⺻ �޽��� �����Դϴ�.
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MATRIXTUTORIAL));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MATRIXTUTORIAL);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      100, 100, 1100, 700, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����:  �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_KEYDOWN: {
		switch (wParam) {
		case 'T': {
			mat = { {1,0,0,1} };
			for (int i = 0, n = matr.size(); i < n; i++)
				matr[i] = { {1,0,0,1} };
			tog = tog ? 0 : 1;
			break;
		}
		case VK_UP: {
			int k = matr.size();
			if (k == 8)break;
			poly.push_back({100,100});
			matr.push_back({ {1,0,0,1} });
			pMatr.push_back({ {1,0,0,1} });
			k++;
			mat = { 1,0,0,1 };
			pMat = { 1,0,0,1 };
			for (int i = 0; i < k; i++) {
				pMatr[i] = { {1,0,0,1} };
				matr[i] = { { 1,0,0,1 } };
				poly[i] = { (int)(cos(2 * i*M_PI / k) * 100),(int)(sin(2 * i*M_PI / k) * 100) };
			}
			break;
		}
		case VK_DOWN: {
			int k = matr.size();
			if (k==3)break;
			poly.pop_back();
			matr.pop_back();
			pMatr.pop_back();
			k--;
			mat = { 1,0,0,1 };
			pMat = { 1,0,0,1 };
			for (int i = 0; i < k; i++) {
				pMatr[i] = { { 1,0,0,1 } };
				matr[i] = { { 1,0,0,1 } };
				poly[i] = { (int)(cos(2 * i*M_PI / k) * 100),(int)(sin(2 * i*M_PI / k) * 100) };
			}
			break;
		}
		case VK_SPACE: {
			if (tog) {
				for (int i = 0; i < 2; i++)
					for (int j = 0; j < 2; j++) {
						pMat.arr[i][j] = mat.arr[i][j];
						mat.arr[i][j] = (double)rand() / RAND_MAX * 2;
					}
			}
			else {
				for (int k = 0, n = matr.size(); k < n; k++)
					for (int i = 0; i < 2; i++)
						for (int j = 0; j < 2; j++) {
							pMatr[k].arr[i][j] = matr[k].arr[i][j];
							matr[k].arr[i][j] = (double)rand() / RAND_MAX * 2;
						}
			}
			break;
		}
		}
		InvalidateRect(hWnd, NULL, true);
		break;	
	}
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // �޴� ������ ���� �м��մϴ�.
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			HFONT hfont = CreateFont(18,0,0,0,400,0,0,0,ANSI_CHARSET,0,0,0,VARIABLE_PITCH | FF_ROMAN,TEXT("Consolas"));
            // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�.
			draw = 1;
			if (tog) {
				Vector2 vec;
				if(!isEqual(&mat,&pMat)){
					for (int i = 0; i < 30; i++) {
						Vector2 vec1 = getMatMul(&mat, &poly[poly.size() - 1]);
						Vector2 vec2 = getMatMul(&pMat, &poly[poly.size() - 1]);
						MoveToEx(hdc,(int)((double)(vec1.x-vec2.x)/30.0*i+vec2.x)+500,(int)((double)(vec1.y-vec2.y)/30.0*i+vec2.y)+300,NULL);
						for (int k = 0, n = poly.size(); k < n; k++) {
							vec1 = getMatMul(&mat, &poly[k]);
							vec2 = getMatMul(&pMat, &poly[k]);
							LineTo(hdc, (int)((double)(vec1.x - vec2.x) / 30.0*i + vec2.x) + 500, (int)((double)(vec1.y - vec2.y) / 30.0*i + vec2.y) + 300);
						}
						Sleep(20);
						Rectangle(hdc, -10, -10, 1100, 700);
					}
				}
				for (int k = 0; k < 2; k++) {
					char stri[2][256] = {};
					sprintf(stri[k], "%g %g", mat.arr[k][0], mat.arr[k][1]);
					TCHAR str[2][256] = {};
					for (int i = 0; stri[k][i]; i++)
						str[k][i] = stri[k][i];
					TextOut(hdc, 0, k * 18, str[k], strlen(stri[k]));
				}
				for (int i = 0, n = matr.size(); i < n; i++) {
					char stri[256];
					vec = getMatMul(&mat, &poly[i]);
					sprintf(stri, "%4d %4d", vec.x, vec.y); 
					TCHAR str[256] = {};
					for (int i = 0; stri[i]; i++)
						str[i] = stri[i];
					TextOut(hdc, 0, 40 + i * 18, str, strlen(stri));
				}
				vec = getMatMul(&mat, &poly[poly.size() - 1]);
				MoveToEx(hdc, vec.x + 500, vec.y + 300, NULL);
				for (int i = 0, n = poly.size(); i < n; i++) {
					vec = getMatMul(&mat, &poly[i]);
					LineTo(hdc, vec.x+500, vec.y + 300);
				}
			}
			else {
				Vector2 vec;
				{
					int t = 0;
					for (int k= matr.size(); t < k; t++) {
						if (!isEqual(&matr[t], &pMatr[t]))break;
					}
					if (t == matr.size())goto MatEqualUnTog;
				}
				for (int i = 0; i < 30; i++) {
					Vector2 vec1 = getMatMul(&matr[matr.size() - 1], &poly[poly.size() - 1]);
					Vector2 vec2 = getMatMul(&pMatr[pMatr.size() - 1], &poly[poly.size() - 1]);
					MoveToEx(hdc, (int)((double)(vec1.x - vec2.x) / 30.0*i + vec2.x)+500, (int)((double)(vec1.y - vec2.y) / 30.0*i + vec2.y)+300,NULL);
					for (int k = 0, n = poly.size(); k < n; k++) {
						vec1 = getMatMul(&matr[k], &poly[k]);
						vec2 = getMatMul(&pMatr[k], &poly[k]);
						LineTo(hdc, (int)((double)(vec1.x - vec2.x) / 30.0*i + vec2.x)+500, (int)((double)(vec1.y - vec2.y) / 30.0*i + vec2.y)+300);
					}
					Sleep(20);
					Rectangle(hdc, -10, -10, 1100, 700);
				}
			MatEqualUnTog:;
				for (int i = 0, n = matr.size(); i < n; i++) {
					for (int k = 0; k < 2; k++) {
						char stri[2][256] = {};
						vec = getMatMul(&matr[i], &poly[i]);
						sprintf(stri[k], "%10g %10g %4d %4d", matr[i].arr[k][0], matr[i].arr[k][1], vec.x, vec.y);
						TCHAR str[2][256] = {};
						for (int i = 0; stri[k][i]; i++)
							str[k][i] = stri[k][i];
						TextOut(hdc, 0, i * 40 + k * 18, str[k], strlen(stri[k]));
					}
				}
				vec = getMatMul(&matr[matr.size() - 1], &poly[poly.size() - 1]);
				MoveToEx(hdc, vec.x + 500, vec.y + 300, NULL);
				for (int i = 0, n = poly.size(); i < n; i++) {
					vec = getMatMul(&matr[i], &poly[i]);
					LineTo(hdc, vec.x + 500, vec.y + 300);
				}
			}
			draw = 0;
			EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
