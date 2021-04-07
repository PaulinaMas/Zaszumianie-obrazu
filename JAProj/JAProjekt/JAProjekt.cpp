// JAProjekt.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "JAProjekt.h"
#include <locale.h>
#include <commdlg.h>
#include <thread>
#include <vector>
#include <shobjidl.h> 
#include <stdlib.h>
#include <WinUser.h>
#include <commctrl.h>
#include <iostream>

#include <windows.h>
#include <random>
#include <chrono>
#include <string>

#include <fstream>

#include "CppLib.h"

#pragma comment(lib,"comctl32.lib")
#define MAX_LOADSTRING 100
typedef struct dataForSepia {
    int cpp = 0;
    int Asm = 0;
    int thread = 0;
    std::string ofile = "";
    int noise = 0;

}Data;
// Zmienne globalne:
long long programasmcpp();
Data data;                                      //struktura przechowuj¹ca szczegó³y odnoœnie formy uruchomienia programu
HWND hProgress;
DWORD IDC_TIMER;
DWORD nCounter;
HWND userThread;
HWND userNoise;


// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);





   

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_JAPROJEKT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_JAPROJEKT));

    MSG msg;

    // Main message loop:
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_JAPROJEKT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_JAPROJEKT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}



//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
       150, 50, 400, 350, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    ////////////////////////////////////////////////////////////////////////////////
    static HWND hButton1, hButton2;
    static HWND hEdit;

    HWND hLeftLabel;
    HWND hRightLabel;
    // HWND userThread;
    static OPENFILENAME ofn;

    static TCHAR FileName[MAX_PATH]; 
    static TCHAR TitleName[MAX_PATH]; 

    //Do obs³ugi okna otwarcia pliku
    TitleName[0] = 0; 
    FileName[0] = 0; 
    //do wyboru w¹tków
    ///////////////////////////////////////////////////////////////////////////////////
    switch (message)
    {
    case WM_CREATE:
        
       // hProgress = CreateWindowEx(0, PROGRESS_CLASS, (LPTSTR)NULL, WS_CHILD | WS_VISIBLE | PBS_SMOOTH, 20, 150, 300, 30, hWnd, (HMENU)0, hInst, NULL);


        //SetTimer(hWnd,ID_ROZPOCZNIJ,100,0);
        nCounter = 0;

        //wybór implementacji
        hButton1 = CreateWindowEx(LWS_TRANSPARENT, L"button", L"Cpp", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 150, 10, 70, 30, hWnd, (HMENU)IDC_CPP, NULL, NULL);
        hButton2 = CreateWindowEx(LWS_TRANSPARENT, L"button", L"ASM", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 250, 10, 70, 30, hWnd, (HMENU)IDC_ASM, NULL, NULL);
        //wybór illoœci watków
        userNoise = CreateWindowW(L"Edit", L"50", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 135, 20, 30, hWnd, (HMENU)IDC_SCROLL, NULL, NULL);
        userThread = CreateWindowW(L"Edit", L"1", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 55, 20, 30, hWnd, (HMENU)IDC_SCROLL, NULL, NULL);
        //przycisk do otwarcia pliku, na którym bêdzie zmiana
        RECT rcClient;
        GetClientRect(hWnd, &rcClient);
        MoveWindow(hEdit, 0, 0, rcClient.right, rcClient.bottom - 30, TRUE);
        CreateWindowEx(0, L"BUTTON", L"Otwórz", WS_CHILD | WS_VISIBLE | WS_BORDER,
            5, rcClient.bottom - 27, 50, 25, hWnd, (HMENU)ID_PLIK_OTWORZ, hInst, NULL);
        //Przycisk do rozpoczêcia dzia³ania programu
        CreateWindowEx(0, L"button", L"Rozpocznij", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 300, rcClient.bottom - 27, 80, 25, hWnd, (HMENU)ID_ROZPOCZNIJ, hInst, NULL);
        // CreateT(hWnd);
     
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDC_CPP:
            {
                CheckRadioButton(hWnd, IDC_CPP, IDC_ASM, IDC_CPP);
                data.cpp = 1;
                data.Asm = 0;
            }
            break;
            case IDC_ASM:
            {
                CheckRadioButton(hWnd, IDC_CPP, IDC_ASM, IDC_ASM);
                data.Asm = 1;
                data.cpp = 0;
            }
            break;
            case ID_PLIK_OTWORZ:
            {
                char* file1Path = new char[128];
                std::string file;
                HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
                    COINIT_DISABLE_OLE1DDE);
                if (SUCCEEDED(hr))
                {
                    IFileOpenDialog* pFileOpen;

                    // Create the FileOpenDialog object.
                    hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
                        IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

                    if (SUCCEEDED(hr))
                    {
                        // Show the Open dialog box.
                        hr = pFileOpen->Show(NULL);

                        // Get the file name from the dialog box.
                        if (SUCCEEDED(hr))
                        {
                            IShellItem* pItem;
                            hr = pFileOpen->GetResult(&pItem);
                            if (SUCCEEDED(hr))
                            {
                                PWSTR pszFilePath;
                                hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
                                size_t charsConverted = 0;
                                wcstombs_s(&charsConverted, file1Path, 128, pszFilePath, 128);
                                file = file1Path;
                                if (file.rfind(".bmp") != file.npos)
                                {   
                                    if (SUCCEEDED(hr))
                                    {
                                        MessageBoxW(NULL, pszFilePath, L"Wybrano plik", MB_OK);
                                        data.ofile = file;
                                        CoTaskMemFree(pszFilePath);
                                       
                                    }
                                }
                                else
                                    MessageBoxW(NULL, L"Proszê podaæ obraz .bmp", L"B³êdny plik!", MB_OK);
                                // Display the file name to the user.

                                pItem->Release();
                            }
                        }
                        pFileOpen->Release();
                    }
                    CoUninitialize();
                }

            }
            break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case ID_ROZPOCZNIJ:
            {

                wchar_t text[3];
                GetWindowTextW(userThread, text, 3);
                data.thread = _wtoi(text);
                wchar_t text1[4];
                GetWindowTextW(userNoise, text1, 4);
                data.noise = _wtoi(text1);
                if ((data.Asm == 0 && data.cpp == 0) || data.ofile == "" || data.thread == 0)
                    MessageBoxW(NULL, L"Proszê uzupe³niæ dane", L"Ups..", MB_OK);
                else if (data.thread < 1 || data.thread>64)
                    MessageBoxW(NULL, L"Z³a liczba w¹tków", L"Ups..", MB_OK);
                else
                {
                    long double czas = programasmcpp();
                    std::string grrr = std::to_string(czas);
                    std::wstring widestr = std::wstring(grrr.begin(), grrr.end());
                    const wchar_t* czasik = widestr.c_str();

                    CreateWindowW(L"Static", czasik, WS_VISIBLE | WS_CHILD, 220, 180, 60, 30, hWnd, NULL, NULL, NULL);
                }


            }
            break;
           
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            int max_threads = std::thread::hardware_concurrency();
            TCHAR buf[300]; // where you put result
            _stprintf(buf, TEXT("Sugerowana liczba w¹tków: %d"), max_threads);
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            TextOut(hdc, 5, 15, _T("Wybór realizacji:"), _tcslen(_T("Wybór implementacji:")));
            TextOut(hdc, 5, 60, _T("Iloœæ w¹tków:"), _tcslen(_T("Iloœæ w¹tków:")));
            TextOut(hdc, 5, 100, buf, _tcslen(buf));
            TextOut(hdc, 5, 140, _T("Wybór stopnia zaszumienia:"), _tcslen(_T("Wybór stopnia zaszumienia")));
            TextOut(hdc, 5, 180, _T("Czas trwania w milisekundach:"), _tcslen(_T("Czas trwania w milisekundach:")));


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

long long programasmcpp()
{


    std::uniform_int_distribution<int> unif(0, 100);
    std::default_random_engine re;
    std::uniform_int_distribution<int> uniff(0, 256);
    std::default_random_engine ree;



    // TODO: Place code here.

    setlocale(LC_CTYPE, "");
    BMP* bitmapa = new BMP;

    std::string str_obj(data.ofile);
    const char* file = &str_obj[0];
    bitmapa->ReadFromFile(file);
    RGBApixel now;
    BMP* bitmapanowa = new BMP;


    int liniena1 = bitmapa->TellWidth() / data.thread;
    if (bitmapa->TellWidth() % data.thread)
        liniena1 += 1;

    int z = 1;

    std::vector<std::thread> threads;
    bitmapanowa->SetSize(bitmapa->TellWidth(), bitmapa->TellHeight());
    for (int i = 0; i < bitmapa->TellWidth(); i++)
    {
        for (int j = 0; j < bitmapa->TellHeight(); j++)
        {

            now.Red = uniff(ree);
           now.Green = uniff(ree);
            now.Blue = uniff(ree);
            now.Alpha = bitmapa->GetPixel(i, j).Alpha;
            bitmapanowa->SetPixel(i, j, now);


        }
    }
   
    typedef void(_stdcall* MyProc1)(int a, int b, RGBApixel** c, RGBApixel** d, int stopien, int skok);
    HINSTANCE dllHandle = NULL;
    dllHandle = LoadLibrary(L"JAAsm.dll");
    MyProc1 procedura = (MyProc1)GetProcAddress(dllHandle, "MyProc1");

    std::chrono::steady_clock::time_point end;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    if (data.cpp)
    {
        for (int k = 0; k < bitmapa->TellWidth(); k += liniena1)
        {
            if (z * liniena1 >= bitmapa->TellWidth())
                threads.push_back(std::thread(zaszum, bitmapa->GetTable(), bitmapanowa->GetTable(), data.noise, liniena1, k, bitmapa->TellWidth(), bitmapa->TellHeight()));
            else
                threads.push_back(std::thread(zaszum, bitmapa->GetTable(), bitmapanowa->GetTable(), data.noise, liniena1, k, z * liniena1, bitmapa->TellHeight()));
            z++;
        }
        for (auto& t : threads)
        {
            t.join();
        }
       
    }
    else if (data.Asm)
    {

       
        for (int k = 0; k < bitmapa->TellWidth(); k += liniena1)
        {
            if (z * liniena1 >= bitmapa->TellWidth())  
                threads.push_back(std::thread(procedura, bitmapa->TellHeight(), k, bitmapa->GetTable(), bitmapanowa->GetTable(), data.noise, bitmapa->TellWidth()));
            else
                threads.push_back(std::thread(procedura, bitmapa->TellHeight(), k, bitmapa->GetTable(), bitmapanowa->GetTable(), data.noise, z * liniena1));
            z++;
        }
        for (auto& t : threads)
        {
            t.join();
        }
    }
    end = std::chrono::steady_clock::now();
    long long czaswyk = std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count();
   
    bitmapa->WriteToFile("zaszumieniewynik.bmp");
    return czaswyk;
}
// Message handler for about box.
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
