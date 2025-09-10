// MyFirstGame.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "framework.h"
#include "MyFirstGame.h"
#include "Direct3D.h"
//#include "Quad.h"
#include "Camera.h"
//#include "Dice.h"
//#include "Sprite.h"
#include "Transform.h"
#include "Fbx.h"
#include "Input.h"

HWND hWnd = nullptr;

//今初期化しなくても後にWindows側で初期化する

#define MAX_LOADSTRING 100

//グローバル変数の宣言
const wchar_t* WIN_CLASS_NAME = L"SAMPLE GAME WINDOW";//ウィンドウクラス名
const int WINDOW_WIDTH = 800;  //ウィンドウの幅//SVGAサイズ
const int WINDOW_HEIGHT = 600; //ウィンドウの高さ

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

    //szWindowClass = WIN_CLASS_NAME;

    // グローバル文字列を初期化する
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MYFIRSTGAME, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);


    // アプリケーション初期化の実行:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    //Direct3D初期化
    HRESULT hr;
    hr = Direct3D::Initialize(WINDOW_WIDTH, WINDOW_HEIGHT, hWnd);
    if (FAILED(hr))
    {
        PostQuitMessage(0);
    }

    //DirectInputの初期化
    Input::Initialize(hWnd);

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MYFIRSTGAME));

    MSG msg = {};

    Camera::Initialize();
    
    //Sprite* s = new Sprite();
    //hr = s->Initialize();
    //if (FAILED(hr))
    //{
    //    PostQuitMessage(0);
    //}
    //Transform* transform = new Transform();

    Fbx* fbx = new Fbx();
    hr = fbx->Load("Oden.fbx");
    if (FAILED(hr))
    {
        PostQuitMessage(0);
    }


    //Quad* q = new Quad();
    //hr = q->Initialize();
    //if (FAILED(hr))
    //{
    //    PostQuitMessage(0);
    //}
    //Dice* dice = new Dice();
    //hr = dice->Initialize();
    //if (FAILED(hr))
    //{
    //    PostQuitMessage(0);
    //}


    // メイン メッセージ ループ:
    //while (GetMessage(&msg, nullptr, 0, 0))
    while (msg.message != WM_QUIT)
    {
        //if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        //{
        //    TranslateMessage(&msg);
        //    DispatchMessage(&msg);
        //}

        //メッセージあり
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
                TranslateMessage(&msg);
                DispatchMessage(&msg);            
        }

        Camera::Update();
        Input::Update();

        Direct3D::BeginDraw();

        static Transform transform;
        transform.rotate_.y += 0.1f;
        //描画処理
        //static float angle = 0.3f;
        //XMMATRIX mat = XMMatrixRotationY(XMConvertToRadians(angle));
        //angle += 0.1f;
        //dice->Draw(mat);
        //transform->Calculation();
        //XMMATRIX mat = XMMatrixIdentity();
        //XMMATRIX mat = transform->GetWorldMatrix();
        //q->Draw(mat);
        //s->Draw(mat);
        fbx->Draw(transform);
        
        if (Input::IsKey(DIK_ESCAPE))
        {
            PostQuitMessage(0);
        }

        Direct3D::EndDraw();
    }

    //解放処理
    //SAFE_RELEASE(q);
    //SAFE_RELEASE(dice);
    //SAFE_RELEASE(s);
    SAFE_RELEASE(fbx);
    Input::Release();
    Direct3D::Release();
    return 0;
}



//
//  関数: MyRegisterClass()
//
//  目的: ウィンドウ クラスを登録します。
//

//Windowクラスの仕組み
//WNDCLASSEXW構造体
//メンバ
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
    //wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYFIRSTGAME));
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    //wcex.hbrBackground  = (HBRUSH)(COLOR_BACKGROUND +1);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    //wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

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
//   hWnd - 実行されているウィンドウの種類と設定、実行されたウィンドウを識別するための変数
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // グローバル変数にインスタンス ハンドルを格納する

   //ウィンドウサイズの計算
   RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
   AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
   int winW = winRect.right - winRect.left;     //ウィンドウ幅
   int winH = winRect.bottom - winRect.top;     //ウィンドウ高さ

   hWnd = CreateWindowW(szWindowClass, WIN_CLASS_NAME, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, winW,winH, nullptr, nullptr, hInstance, nullptr);

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
//  wndProc     - ウィンドウが何かの動作した時、windowsに通知をしてディスプレイに実行結果を表示させる
//  nessage     - 何の動作をした時の識別番号
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

//メッセージループとコールバックの関係と仕組み
//仕組み
//・メッセージループ：アプリケーションがイベントを処理するためのループ。アプリケーションを常にイベントを監視し、それらに応答できるようにする
//・コールバック：特定のイベントが発生したときに実行される関数。イベントが発生した際、関連付けられたコールバック関数を呼び出す
//関係
//・メッセージループでイベントを検出し、コールバック関数を呼び出すための仕組みを提供。コールバック関数は、メッセージループによってディスパッチされたイベントに対する実際の処理を担当