
#include <windows.h>
#include <windowsx.h>
#include <iostream>
#include <vector>
#include <time.h>
#include "battle.h"
using namespace std;
#define width 40
#define aa 10
#define bb 10


void DrawBlocks(HDC hdc, int n, int m);
void DrawBlocks(HDC hdc, int x, int y, int n, int m);
void FillBlocks(HDC hdc, int n, int m, HBRUSH b);
void FillBlocks(HDC hdc, int x, int y, int n, int m, HBRUSH b);
bool randflag = 1;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
        static TCHAR szAppName[] = TEXT("MyWindows");
        HWND hwnd;
        MSG msg;
        WNDCLASS wndclass;

        wndclass.style = CS_HREDRAW | CS_VREDRAW;
        wndclass.lpfnWndProc = WndProc;
        wndclass.cbClsExtra = 0;
        wndclass.cbWndExtra = 0;
        wndclass.hInstance = hInstance;
        wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
        wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
        wndclass.lpszMenuName = NULL;
        wndclass.lpszClassName = szAppName;

        if (!RegisterClass(&wndclass))
        {
                MessageBox(NULL, TEXT("这个程序需要在 Windows NT 才能执行！"), szAppName, MB_ICONERROR);
                return 0;
        }

        hwnd = CreateWindow(szAppName,
                TEXT("BATTLE"),
                WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                NULL,
                NULL,
                hInstance,
                NULL);

        ShowWindow(hwnd, iCmdShow);
        UpdateWindow(hwnd);

        while (GetMessage(&msg, NULL, 0, 0))
        {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
        }

        return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
        HDC hdc;
        PAINTSTRUCT ps;
        static BattleMap player(aa, bb), player2(aa,bb);
        HBRUSH hBrush0, hBrush1, hBrush2, hBrush3, hBrush4, hBrush6;
        static POINT point;
        static int x,y;
        static bool randflag;
        static int iCount;
        TCHAR PlayerTurns[128];

        if(!randflag){
            srand(time(NULL));
            player.randmap();
            player2.randmap();
            randflag = 1;
            iCount = 0;
        }
        TCHAR buffer[128];
        switch (message)
        {
        case WM_PAINT:
                hdc = BeginPaint(hwnd, &ps);
                hBrush0 = CreateHatchBrush(HS_DIAGCROSS, 0);
                hBrush1 = CreateSolidBrush(RGB(255,0,0));
                hBrush2 = CreateSolidBrush(RGB(255,0,255));
                hBrush3 = CreateSolidBrush(RGB(0,255,0));
                hBrush4 = CreateSolidBrush(RGB(0,0,255));
                hBrush6 = CreateSolidBrush(RGB(255,255,0));


                wsprintf(buffer, TEXT("%d, %d, %d"),x,y,iCount);
                TextOut(hdc, 11*width, 11*width, buffer, lstrlen(buffer));

                DrawBlocks(hdc, player.getcol(), player.getrow());
                DrawBlocks(hdc, 440, 0, aa, bb);
                for(int i = 0; i < player.getcol(); i++)
                    for(int j = 0; j < player.getrow(); j++)
                {
                    if(player.ischecked(i,j))
                    {
                        if(player.isempty(i,j))    FillBlocks(hdc, i, j, hBrush0);
                        if(player.getkind(i,j)==1) FillBlocks(hdc, i, j, hBrush1);
                        if(player.getkind(i,j)==2) FillBlocks(hdc, i, j, hBrush2);
                        if(player.getkind(i,j)==3) FillBlocks(hdc, i, j, hBrush3);
                        if(player.getkind(i,j)==4) FillBlocks(hdc, i, j, hBrush4);
                        if(player.getkind(i,j)==6) FillBlocks(hdc, i, j, hBrush6);
                    }
                }
                for(int i = 0; i < player2.getcol(); i++)
                    for(int j = 0; j < player2.getrow(); j++)
                {
                    if(player2.ischecked(i,j))
                    {
                        if(player2.isempty(i,j))    FillBlocks(hdc, 440, 0, i, j, hBrush0);
                        if(player2.getkind(i,j)==1) FillBlocks(hdc, 440, 0, i, j, hBrush1);
                        if(player2.getkind(i,j)==2) FillBlocks(hdc, 440, 0, i, j, hBrush2);
                        if(player2.getkind(i,j)==3) FillBlocks(hdc, 440, 0, i, j, hBrush3);
                        if(player2.getkind(i,j)==4) FillBlocks(hdc, 440, 0, i, j, hBrush4);
                        if(player2.getkind(i,j)==6) FillBlocks(hdc, 440, 0, i, j, hBrush6);
                    }
                }
                wsprintf(PlayerTurns, TEXT("Your turn!"));
                if(iCount%2 == 0)
                    TextOutA(hdc, 4 * width, 10.5 * width, PlayerTurns, lstrlen(PlayerTurns));
                if(iCount%2 == 1)
                    TextOutA(hdc, (11 + 4) * width, 10.5 * width, PlayerTurns, lstrlen(PlayerTurns));
                EndPaint(hwnd, &ps);
                return 0;

        case WM_LBUTTONDOWN:
            point.x = GET_X_LPARAM(lParam);
            point.y = GET_Y_LPARAM(lParam);
            x = point.x/width;
            y = point.y/width;
            if(x < player.getrow() && y < player.getcol()
               &&iCount%2 == 0){
            if(!player.ischecked(x,y))
            iCount ++;
            player.check(x,y);
            }
            if(11 <= x && x < player.getrow()+11 && y < player.getcol()
                    && iCount%2 == 1){
            x %= 11;
            if(!player2.ischecked(x,y))
            iCount ++;
            player2.check(x,y);
            }
            InvalidateRect(hwnd, NULL, true);
            SendMessage(hwnd, WM_PAINT, NULL, NULL);
            if(player.isfinished()){
                MessageBoxA(hwnd, TEXT("player2 Win!"), TEXT("BATTLE"), MB_OK);
            }
             if(player2.isfinished()){
                MessageBoxA(hwnd, TEXT("player1 Win!"), TEXT("BATTLE"), MB_OK);
            }
            return 0;
        case WM_RBUTTONDOWN:
            if(wParam & MK_CONTROL)
                for(int i = 0; i < aa; i ++)
                    for(int j = 0; j < bb; j++)
                        player.check(i,j);
            SendMessageA(hwnd, WM_PAINT, NULL, NULL);
            InvalidateRect(hwnd, NULL, FALSE);
            randflag = 0;
            return 0;
        case WM_KEYDOWN:
            switch(wParam)
            {
            case VK_F5:
                SendMessage(hwnd, WM_PAINT, NULL, NULL);
                InvalidateRect(hwnd, NULL, FALSE);
                randflag = 0;
                break;
            }
            return 0;
        case WM_DESTROY:
                randflag = 0;
                PostQuitMessage(0);
                return 0;
        }

        return DefWindowProc(hwnd, message, wParam, lParam);
}
void DrawBlocks(HDC hdc, int n, int m)
{
    HPEN hPen;
    hPen = CreatePen(PS_SOLID, 2, 0);
    SelectObject(hdc, hPen);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            Rectangle(hdc, i * width, j * width, (i+1)*width, (j+1)*width);
}
void DrawBlocks(HDC hdc, int x, int y, int n, int m)
{
    HPEN hPen;
    hPen = CreatePen(PS_SOLID, 2, 0);
    SelectObject(hdc, hPen);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            Rectangle(hdc, x + i * width, y + j * width, x + (i+1)*width, y + (j+1)*width);
}
void FillBlocks(HDC hdc, int n, int m, HBRUSH b)
{
    SelectObject(hdc, b);
    Rectangle(hdc, n*width, m*width, (n+1)*width, (m+1)*width);
}
void FillBlocks(HDC hdc, int x, int y, int n, int m, HBRUSH b)
{
    SelectObject(hdc, b);
    Rectangle(hdc, x + n*width, y + m*width, x + (n+1)*width, y + (m+1)*width);
}
