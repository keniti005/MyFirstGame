// MyFirstGame.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "framework.h"
#include "MyFirstGame.h"

#define MAX_LOADSTRING 100

// グローバル変数:
HINSTANCE hInst;                                // 現在のインターフェイス
WCHAR szTitle[MAX_LOADSTRING];                  // タイトル バーのテキスト
WCHAR szWindowClass[MAX_LOADSTRING];            // メイン ウィンドウ クラス名

// このコード モジュールに含まれる関数の宣言を転送します:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//WinMainの引数
//hInstance：クラスのウィンドウプロシージャを含むインスタンスへのハンドル（実行可能ファイルまたはEXEの識別）
//hPrevInstance：16ビットWindowsで使用（インスタンスのバンドルを表している）されていたが、現在では0が入っている
//lpCmdLine：コマンドライン引数がUnicode文字列として含まれている
//nCmdShow：メインアプリケーションウィンドウが最小化、最大化、または正常に表示されるかのフラグ

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ここにコードを挿入してください。

    // グローバル文字列を初期化する
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MYFIRSTGAME, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // アプリケーション初期化の実行:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MYFIRSTGAME));

    MSG msg;

    // メイン メッセージ ループ:
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
//  関数: MyRegisterClass()
//
//  目的: ウィンドウ クラスを登録します。
//

//・cbSize：構造体のサイズ（バイト単位）。このメンバーをsizeof(WNDCLASSEX)に設定する。GetClassInfoEx関数を呼び出す前に必ず設定をする
//・style：クラススタイルの任意の組み合わせにすることができる
//・lpfnWndProc：ウィンドウプロシージャへのポインター。呼び出すには、CallWindowProc関数を使用する必要がある
//・cbClsExtra：ウィンドウクラス構造体の後に割り当てる余分なバイト数（バイト数はゼロに初期化する）
//・cbWndExtra：ウィンドウインスタンスの後に割り当てる余分なバイト数（バイト数はゼロに初期化する）
//・hInstance：クラスのウィンドウプロシージャを含むインスタンスへのバンドル
//・hIcon：アイコンへのバンドル。NULLの場合、システムは既定のアイコンを提供する
//・hCursor：カーソルへのバンドル。NULLの場合、マウスがアプリケーションは、ウィンドウが移動するたびにカーソルへの形状を明示的に設定が必要
//・hbrBackground：背景ブラシへのバンドル。背景の描画に使用するバンドルや、色の値にすることも可能。色の値が指定されてる場合はHBRUSH型の変換が必要（NULLの場合、独自の背景を描画する必要がある）
//・lpszMenuName：メニューのリソース名を指定するnullで終わる文字列へのポインター。NULLの場合、ウィンドウには既定のメニューはなくなる
//・lpszClassName：nullで終わる文字列へのポインター、またはアトム。(最大長は256まで)
//バラメータがアトムの場合：呼び出しによって作成されたクラスアトムである必要である。
//文字列の場合：クラス名にはRegisterClass(Ex)登録されている任意の名前、または定義済みのコントロールクラス名を指定することができる
//・hIconSm：小さなアイコンへのバンドル。NULLの場合、hIconメンバーによって指定されたアイコンを適切なサイズを検索する

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYFIRSTGAME));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   関数: InitInstance(HINSTANCE, int)
//
//   目的: インスタンス ハンドルを保存して、メイン ウィンドウを作成します
//
//   コメント:
//
//        この関数で、グローバル変数でインスタンス ハンドルを保存し、
//        メイン プログラム ウィンドウを作成および表示します。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // グローバル変数にインスタンス ハンドルを格納する

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  関数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: メイン ウィンドウのメッセージを処理します。
//
//  WM_COMMAND  - アプリケーション メニューの処理
//  WM_PAINT    - メイン ウィンドウを描画する
//  WM_DESTROY  - 中止メッセージを表示して戻る
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 選択されたメニューの解析:
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
            // TODO: HDC を使用する描画コードをここに追加してください...
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

// バージョン情報ボックスのメッセージ ハンドラーです。
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

//CreateWindowEx
//・引数
//dwExStyle：作成されるウィンドウの拡張ウィンドウスタイル
//lpClassName：null - terminated文字列またはクラスアトム
//lpWindowName：ウィンドウ名。静的コントロールを作成する場合は、lpWindowName使用してアイコンの名前または識別子を指定する
//dwStyle：作成するウィンドウのスタイル
//X：ウィンドウの最初の水平位置。xパラメーターは、ウィンドウの左上隅の最初のx座標(画面座標)。
//Y：ウィンドウの最初の垂直方向の位置。yパラメーターは、ウィンドウの左上隅の初期y座標(画面座標)。
//nWidth：ウィンドウの幅(デバイス単位)
//nHeight：ウィンドウの高さ(デバイス単位)
//hWndParent：作成されるウィンドウの親ウィンドウまたは所有者ウィンドウへのハンドル
//hMenu：メニューのハンドル
//hInstance：ウィンドウに関連付けるモジュールのインスタンスへのハンドル
//lpParam：WM_CREATEメッセージのlParamパラメーターが指す
//・戻り値
//作成したウィンドウへのバンドルを返す（失敗した場合NULLを返す）
