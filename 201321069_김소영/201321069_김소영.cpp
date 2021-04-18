// 201321069_��ҿ�.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "201321069_��ҿ�.h"

#include "egl\egl.h"
#include "vg\openvg.h"

#include "vgLoadImage.h"
#include <time.h>
#include "DXUTsound.h"

#define MAX_LOADSTRING 100

#define GAME_START 1
#define GAME_PLAYING 2
#define GAME_PLAYING2 3
#define GAME_USE 4
#define GAME_OVER 5
#define GAME_FINISH 6



// ���� ����:
HINSTANCE hInst;								// ���� �ν��Ͻ��Դϴ�.
TCHAR szTitle[MAX_LOADSTRING];					// ���� ǥ���� �ؽ�Ʈ�Դϴ�.
TCHAR szWindowClass[MAX_LOADSTRING];			// �⺻ â Ŭ���� �̸��Դϴ�.

EGLDisplay display;
EGLSurface surface;
EGLContext context;


void timerProc();
void draw();


int gameState;
int gameCount;
int a;

struct Fighter {  
	int  x, y;
	int count;
	bool animating;
} fighter;
struct FinRabbit {  
	int  x, y;
	int count;
} finr;
struct Carrot {  
	int  x, y;
} carrot;
struct Carrot2 {  
	int  x, y;
} carrot2;
struct FallCar {
	int shot, x, y;
} fallc[100];
struct Missile {  
	int shot, x, y;
} missiles[100];
struct Enemy {
	int shot, x, y;
} enemy[100];
struct Enemy2 {
	int shot, x, y;
} enemy2[100];
struct Enemy3 {
	int shot, x, y;
} enemy3[100];
struct Enemy4 {
	int shot, x, y;
} enemy4[100];
struct Enemy5 {
	int shot, x, y;
} enemy5[100];
struct Enemy6 {
	int shot, x, y;
} enemy6[100];
struct Enemy7 {
	int shot, x, y;
} enemy7[100];
struct Enemy8 {
	int shot, x, y;
} enemy8[100];
struct Amb{
	int shot, x, y;
} amb[100];//������
struct Amb2 {
	int shot, x, y;
} amb2[100];//������
struct Pol {
	int shot, x, y;
} pol[100];//������
struct Pol2 {
	int shot, x, y;
} pol2[100];//������
int cx=0;

CSoundManager* sm =NULL;
CSound* crashSound1=NULL;
CSound* crashSound2=NULL;
CSound* crashSound3=NULL;
CSound* crashSound4=NULL;
CSound* crashSound5=NULL;
CSound* crashSound6=NULL;

VGImage missileImg, enemyImg, bkImg, enemyImg2, enemyImg3, enemyImg4;
VGImage fighterImg[12],finrImg[2], carrotImg, carrotImg2, finImg,fin,fin2 ;
VGImage intro, text, press, menu, use, usek, useh, over, overImg;
VGImage enemyImg5, enemyImg6, enemyImg7, enemyImg8; 
VGImage ambImg,ambImg2,polImg,polImg2;
VGImage fallcImg, fallcImg2 , startR, finishR, overR ,stage1,stage2;

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: ���⿡ �ڵ带 �Է��մϴ�.
	MSG msg;
	HACCEL hAccelTable;

	// ���� ���ڿ��� �ʱ�ȭ�մϴ�.
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY201321069_, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY201321069_));

	// �⺻ �޽��� �����Դϴ�.
	DWORD lastTime = GetTickCount();
	while (1)
	{if( PeekMessage(&msg, NULL, 0, 0, 1) )
	{if(!TranslateAccelerator(msg.hwnd, NULL, &msg))
	{ TranslateMessage(&msg);
	DispatchMessage(&msg); }
	if( msg.message == WM_QUIT ) break;
	}DWORD curTime = GetTickCount();
	if( curTime-lastTime>32 ) // 30 frame per second
	{lastTime = lastTime+33;
	timerProc();}
	}

	return (int) msg.wParam;
}



//
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
//
//  ����:
//
//    Windows 95���� �߰��� 'RegisterClassEx' �Լ����� ����
//    �ش� �ڵ尡 Win32 �ý��۰� ȣȯ�ǵ���
//    �Ϸ��� ��쿡�� �� �Լ��� ����մϴ�. �� �Լ��� ȣ���ؾ�
//    �ش� ���� ���α׷��� �����
//    '�ùٸ� ������' ���� �������� ������ �� �ֽ��ϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0; 
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY201321069_));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY201321069_);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
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
   HWND hWnd;

   hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 800, 600, NULL, NULL, hInstance, NULL);

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
//  ����: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND	- ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT	- �� â�� �׸��ϴ�.
//  WM_DESTROY	- ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
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
		break;
	case WM_CREATE:{
		display = eglGetDisplay( GetDC(hWnd));
        eglInitialize( display, NULL, NULL );
        eglBindAPI( EGL_OPENVG_API );
		EGLint conf_list[] = { EGL_RED_SIZE, 8,
                        EGL_GREEN_SIZE, 8,
                        EGL_BLUE_SIZE, 8,
                        EGL_ALPHA_SIZE, 8,
                        EGL_NONE };
       EGLConfig config;
       EGLint    num_config;
       eglChooseConfig( display, conf_list, &config, 1, &num_config );
       surface = eglCreateWindowSurface( display, config, hWnd, NULL );
       context = eglCreateContext( display, 0, NULL, NULL );
	   
	 

	  missileImg = vgLoadImage(TEXT("MISSILE.png"));
      fighterImg[0] = vgLoadImage(TEXT("Rabbit1.png"));
	  fighterImg[1] = vgLoadImage(TEXT("Rabbit2.png"));
	  fighterImg[2] = vgLoadImage(TEXT("Rabbit3.png"));
	  fighterImg[3] = vgLoadImage(TEXT("Rabbit4.png"));
	  fighterImg[4] = vgLoadImage(TEXT("Rabbit5.png"));
	  fighterImg[5] = vgLoadImage(TEXT("Rabbit6.png"));
	  fighterImg[6] = vgLoadImage(TEXT("Rabbit7.png"));
	  fighterImg[7] = vgLoadImage(TEXT("Rabbit8.png"));
	  fighterImg[8] = vgLoadImage(TEXT("Rabbit9.png"));
	  fighterImg[9] = vgLoadImage(TEXT("Rabbit10.png"));
	  fighterImg[10] = vgLoadImage(TEXT("Rabbit11.png"));
	  fighterImg[11] = vgLoadImage(TEXT("Rabbit12.png"));

	  finrImg[0]=vgLoadImage(TEXT("Rabbitq.png"));
	  finrImg[1]=vgLoadImage(TEXT("Rabbitqq.png"));
	  finImg=vgLoadImage(TEXT("finish.png"));

	  enemyImg=vgLoadImage(TEXT("greenC.png"));
	  enemyImg2=vgLoadImage(TEXT("greenC2.png"));
	  enemyImg3=vgLoadImage(TEXT("redcar2.png"));
	  enemyImg4=vgLoadImage(TEXT("redcar22.png"));
	  enemyImg5=vgLoadImage(TEXT("greenC.png"));
	  enemyImg6=vgLoadImage(TEXT("greenC2.png"));
	  enemyImg7=vgLoadImage(TEXT("redcar2.png"));
	  enemyImg8=vgLoadImage(TEXT("redcar22.png")); //�ڵ���

	  ambImg=vgLoadImage(TEXT("119.png"));
	  ambImg2=vgLoadImage(TEXT("1192.png"));//������

	  polImg=vgLoadImage(TEXT("1122.png"));
	  polImg2=vgLoadImage(TEXT("112.png"));//������

	  carrotImg=vgLoadImage(TEXT("c.png"));
	  carrotImg2=vgLoadImage(TEXT("c.png"));
	  fallcImg=vgLoadImage(TEXT("c2.png"));
	  fallcImg2=vgLoadImage(TEXT("intro3444.png"));

	  over=vgLoadImage(TEXT("over.png"));
	  overImg=vgLoadImage(TEXT("introg.png"));
	  
	  use=vgLoadImage(TEXT("use.png"));
	  usek=vgLoadImage(TEXT("use-2.png"));
	  useh=vgLoadImage(TEXT("use-1.png"));

	  
	  
	  bkImg=vgLoadImage(TEXT("back.png"));
	  text = vgLoadImage(TEXT("START.png"));
	  intro = vgLoadImage(TEXT("introo.png"));
	  press = vgLoadImage(TEXT("press.png"));
	  menu = vgLoadImage(TEXT("jumping.png"));

	  startR=vgLoadImage(TEXT("Rabbitqq.png"));
	  finishR=vgLoadImage(TEXT("Rabbitqq.png"));
	  overR=vgLoadImage(TEXT("overR.png"));
	  
	  stage1=vgLoadImage(TEXT("stage1.png"));
	  stage2=vgLoadImage(TEXT("stage2.png"));

	  
	  gameState=GAME_START;
	  gameCount=0;
	  a=1;

	  fighter.y = 10;
	  fighter.x = 400;
	  fighter.animating = false;
	  fighter.count = 0;
	  finr.x= 250;
	  finr.y=250;
	  finr.count=0;

	  carrot.x= 400;
	  carrot.y= 510;
	  carrot2.x= 400;
	  carrot2.y= 510;

	   for( int i=0; i<100; i++ )
		  fallc[i].shot = false;

	  for( int i=0; i<100; i++ )
		  enemy[i].shot = false;
	  for( int i=0; i<100; i++ )
		  enemy2[i].shot = false;
	  for( int i=0; i<100; i++ )
		  enemy3[i].shot = false;
	  for( int i=0; i<100; i++ )
		  enemy4[i].shot = false;
	  for( int i=0; i<100; i++ )
		  enemy5[i].shot = false;
	  for( int i=0; i<100; i++ )
		  enemy6[i].shot = false;
	  for( int i=0; i<100; i++ )
		  enemy7[i].shot = false;
	  for( int i=0; i<100; i++ )
		  enemy8[i].shot = false;//�ڵ��� �ʱ�ȭ

	  for( int i=0; i<100; i++ )
		  amb[i].shot = false;
	  for( int i=0; i<50; i++ )
		  amb2[i].shot = false;//������ �ʱ�ȭ

	  for( int i=0; i<100; i++ )
		  pol[i].shot = false;
	  for( int i=0; i<100; i++ )
		  pol2[i].shot = false;//������ �ʱ�ȭ


	  sm= new CSoundManager();
	  sm->Initialize(hWnd,DSSCL_NORMAL);
	

	  sm->Create(&crashSound1,TEXT("SHK - ģ���� �Բ�.wav"),0,GUID_NULL);
	  sm->Create(&crashSound2,TEXT("���ϸ��̼�_����02��.wav"),0,GUID_NULL);
	  sm->Create(&crashSound3,TEXT("���ϸ��̼�_����01.wav"),0,GUID_NULL);
	  sm->Create(&crashSound4,TEXT("����_���̷�2.wav"),0,GUID_NULL);
	  sm->Create(&crashSound5,TEXT("����_���̷�1.wav"),0,GUID_NULL);
	  sm->Create(&crashSound6,TEXT("��ε�_����08.wav"),0,GUID_NULL);
	 
	  crashSound1->Play(0,DSBPLAY_LOOPING); //���� �ʱ�ȭ
	  
	  //�ʱ�ȭ 

				   }
				   break;


	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		if( wParam == VK_UP && fighter.y<500) 
		{
			if(gameState==GAME_PLAYING || gameState==GAME_PLAYING2 ){
				crashSound2->Play(0);
				fighter.y+=40;
				a=1;
				fighter.animating= true;}
		}
		if( wParam == VK_LEFT)
		{
			fighter.animating= true;
			fighter.count=6;
			a=3;
		}

		if( wParam == VK_RIGHT)
		{
			fighter.animating= true;
			fighter.count=9;
			a=4;
		}
		if( wParam == VK_DOWN && fighter.y>10) 
		{
			if(gameState==GAME_PLAYING || gameState==GAME_PLAYING2 ){
			crashSound2->Play(0);
			fighter.y-=40;
			fighter.count=3;
			a=2;
			fighter.animating= true;}
		}
		if( wParam == VK_SPACE)
		{
			if(gameState==GAME_START)
				gameState=GAME_USE;
			if(gameState==GAME_OVER)
				gameState=GAME_START;
			if(gameState==GAME_FINISH)
				gameState=GAME_START;
		}
		if( wParam == VK_SHIFT)
		{
			if(gameState==GAME_PLAYING)
				gameState=GAME_PLAYING2;
			if(gameState==GAME_USE)
				gameState=GAME_PLAYING;
			
		}
		if( wParam == VK_DELETE)
		{
			if(gameState==GAME_PLAYING2)
				gameState=GAME_FINISH;
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

void draw()
{
	int i;
	
	eglMakeCurrent(display,surface,surface,context);
	vgSeti(VG_MATRIX_MODE,VG_MATRIX_IMAGE_USER_TO_SURFACE);
	float clearColor[4]={1,0.5,0.2,1};
	vgSetfv(VG_CLEAR_COLOR,4,clearColor);
	vgClear(0,0,1000,1000);


	if( gameState == GAME_START ) //ó��ȭ��
	{
		int k=cx/800;
	
		vgLoadIdentity(); 
		vgTranslate(-cx,0);
		vgTranslate(k*800,0);
		vgDrawImage(intro);
		vgLoadIdentity(); 
		vgTranslate(-cx,0);
		vgTranslate((k+1)*800,0);
		vgDrawImage(intro);//���
		
		vgLoadIdentity();
		vgTranslate( 240,260 );
		vgDrawImage( press );
		vgLoadIdentity();
		vgTranslate( 200, 350);
		vgDrawImage( menu );
	
		
		if( gameCount<15 )
		{
			vgLoadIdentity();
			vgTranslate( 250, 300);
			vgDrawImage( text );
			vgLoadIdentity();
			vgTranslate( 100, 300);
			vgDrawImage( startR );
		}
		
		/*for( i=0; i<50; i++ ) 
		{
			if( enemy3[i].shot == true ) 
			{
				vgLoadIdentity();
				vgTranslate( enemy3[i].x, enemy3[i].y);
				vgDrawImage( enemyImg3 );
			}
		}
		for( i=0; i<50; i++ ) 
		{
			if( enemy2[i].shot == true ) 
			{
				vgLoadIdentity();
				vgTranslate( enemy2[i].x, enemy2[i].y);
				vgDrawImage( enemyImg2 );
			}
		}*/
	}


	if( gameState == GAME_FINISH ) 
	{
		//int k=cx/600;
	
		vgLoadIdentity(); 
		//vgTranslate(0,-cx);
		//vgTranslate(0,k*600);
		vgDrawImage(fallcImg2);
		//vgLoadIdentity(); 
		//vgTranslate(0,-cx);
		//vgTranslate(0,(k+1)*600);
		//vgDrawImage(finImg);
		crashSound6->Play(0);

			if( gameCount<15 )
		{
			vgLoadIdentity();
			vgTranslate( 280, 280);
			vgDrawImage( over );
			vgLoadIdentity();
			vgTranslate( 100, 300);
			vgDrawImage( finishR );
		}

		
		for( i=0; i<100; i++ ) {
		if( fallc[i].shot == true ) {
			vgLoadIdentity();
				vgTranslate( fallc[i].x, fallc[i].y);
				vgDrawImage( fallcImg );
		}
	}
		
		
			


		/*while(finr.count<2){
		vgLoadIdentity(); 
		vgTranslate( finr.x, finr.y );
		vgDrawImage( finrImg[finr.count] );}*/
		
	}

	if(gameState==GAME_USE )
	{
		vgLoadIdentity(); 
		vgDrawImage(use);
		
		if( gameCount<15 )
		{
			vgLoadIdentity();
			vgTranslate( 500, 50);
			vgDrawImage( usek );
	
		}
		vgLoadIdentity();
			vgTranslate( 100, 400);
			vgDrawImage( useh );
	
	
	}
	if(gameState==GAME_OVER )
	{
		vgLoadIdentity(); 
		vgDrawImage(overImg);
		
		crashSound5->Play(0);
		if( gameCount<15 )
		{
			vgLoadIdentity();
			vgTranslate( 280, 280);
			vgDrawImage( over );
			vgLoadIdentity();
			vgTranslate( 100, 300);
			vgDrawImage( overR );
		}
	
	
	}



	if(gameState==GAME_PLAYING )
	{	
		vgLoadIdentity(); 
		vgDrawImage(bkImg);
		
		vgLoadIdentity();
		vgTranslate(30,250);
		vgDrawImage( stage1);
		
		vgLoadIdentity(); 
		vgTranslate( fighter.x, fighter.y );
		vgDrawImage( fighterImg[fighter.count] );

		/*if(a=2){
		vgLoadIdentity(); 
		vgTranslate( fighter.x, fighter.y );
		vgDrawImage( fighterImg2[fighter.count] );}

		if(a=3){
		vgLoadIdentity(); 
		vgTranslate( fighter.x, fighter.y );
		vgDrawImage( fighterImg3[fighter.count] );}

		if(a=4){
		vgLoadIdentity(); 
		vgTranslate( fighter.x, fighter.y );
		vgDrawImage( fighterImg4[fighter.count] );}*/
		
		vgLoadIdentity();
		vgTranslate( carrot.x, carrot.y);
		vgDrawImage( carrotImg );
	
	//enemy1

	for( i=0; i<100; i++ ) {
		if( enemy[i].shot == true ) {
			vgLoadIdentity();
			vgTranslate( enemy[i].x, enemy[i].y);
			vgDrawImage( enemyImg );
		}
	}

	//enemy2

	for( i=0; i<100; i++ ) {
		if( enemy2[i].shot == true ) {
			vgLoadIdentity();
			vgTranslate( enemy2[i].x, enemy2[i].y);
			vgDrawImage( enemyImg2 );
		}
	}

	//enemy3

	for( i=0; i<100; i++ ) {
		if( enemy3[i].shot == true ) {
			vgLoadIdentity();
			vgTranslate( enemy3[i].x, enemy3[i].y);
			vgDrawImage( enemyImg3 );
		}
	}

	//enemy4

	for( i=0; i<100; i++ ) {
		if( enemy4[i].shot == true ) {
			vgLoadIdentity();
			vgTranslate( enemy4[i].x, enemy4[i].y);
			vgDrawImage( enemyImg4 );
		}
	}
	//
	//enemy5

	for( i=0; i<100; i++ ) {
		if( enemy5[i].shot == true ) {
			vgLoadIdentity();
			vgTranslate( enemy5[i].x, enemy5[i].y);
			vgDrawImage( enemyImg5 );
		}
	}
	//enemy6

	for( i=0; i<100; i++ ) {
		if( enemy6[i].shot == true ) {
			vgLoadIdentity();
			vgTranslate( enemy6[i].x, enemy6[i].y);
			vgDrawImage( enemyImg6 );
		}
	}
	//enemy7

	for( i=0; i<100; i++ ) {
		if( enemy7[i].shot == true ) {
			vgLoadIdentity();
			vgTranslate( enemy7[i].x, enemy7[i].y);
			vgDrawImage( enemyImg7 );
		}
	}
	//enemy8

	for( i=0; i<100; i++ ) {
		if( enemy8[i].shot == true ) {
			vgLoadIdentity();
			vgTranslate( enemy8[i].x, enemy8[i].y);
			vgDrawImage( enemyImg8 );
		}
	}
	}
	
	if(gameState == GAME_PLAYING2 )
	{	
		vgLoadIdentity(); 
		vgDrawImage(bkImg);
		
		vgLoadIdentity();
		vgTranslate( 30, 250);
		vgDrawImage( stage2);
		
		vgLoadIdentity(); 
		vgTranslate( fighter.x, fighter.y );
		vgDrawImage( fighterImg[fighter.count] );

		/*vgLoadIdentity(); 
		vgTranslate( fighter.x, fighter.y );
		vgDrawImage( fighterImg2[fighter.count] );

		vgLoadIdentity(); 
		vgTranslate( fighter.x, fighter.y );
		vgDrawImage( fighterImg3[fighter.count] );

		vgLoadIdentity(); 
		vgTranslate( fighter.x, fighter.y );
		vgDrawImage( fighterImg4[fighter.count] );*/
		
		vgLoadIdentity();
		vgTranslate( carrot2.x, carrot2.y);
		vgDrawImage( carrotImg2 );
	
	//enemy1

	for( i=0; i<100; i++ ) {
		if( enemy[i].shot == true ) {
			vgLoadIdentity();
			vgTranslate( enemy[i].x, enemy[i].y);
			vgDrawImage( enemyImg );
		}
	}

	//enemy2

	for( i=0; i<100; i++ ) {
		if( enemy2[i].shot == true ) {
			vgLoadIdentity();
			vgTranslate( enemy2[i].x, enemy2[i].y);
			vgDrawImage( enemyImg2 );
		}
	}

	//enemy3

	for( i=0; i<100; i++ ) {
		if( enemy3[i].shot == true ) {
			vgLoadIdentity();
			vgTranslate( enemy3[i].x, enemy3[i].y);
			vgDrawImage( enemyImg3 );
		}
	}

	//enemy4

	for( i=0; i<100; i++ ) {
		if( enemy4[i].shot == true ) {
			vgLoadIdentity();
			vgTranslate( enemy4[i].x, enemy4[i].y);
			vgDrawImage( enemyImg4 );
		}
	}
	//
	//enemy5

	for( i=0; i<100; i++ ) {
		if( enemy5[i].shot == true ) {
			vgLoadIdentity();
			vgTranslate( enemy5[i].x, enemy5[i].y);
			vgDrawImage( enemyImg5 );
		}
	}
	//enemy6

	for( i=0; i<100; i++ ) {
		if( enemy6[i].shot == true ) {
			vgLoadIdentity();
			vgTranslate( enemy6[i].x, enemy6[i].y);
			vgDrawImage( enemyImg6 );
		}
	}
	//enemy7

	for( i=0; i<100; i++ ) {
		if( enemy7[i].shot == true ) {
			vgLoadIdentity();
			vgTranslate( enemy7[i].x, enemy7[i].y);
			vgDrawImage( enemyImg7 );
		}
	}
	//enemy8

	for( i=0; i<100; i++ ) {
		if( enemy8[i].shot == true ) {
			vgLoadIdentity();
			vgTranslate( enemy8[i].x, enemy8[i].y);
			vgDrawImage( enemyImg8 );
		}
	}

	//
	for( i=0; i<100; i++ ) {
		if( amb[i].shot == true ) {
			vgLoadIdentity();
			vgTranslate( amb[i].x, amb[i].y);
			vgDrawImage( ambImg );
		}
	}
	
	for( i=0; i<100; i++ ) {
		if( amb2[i].shot == true ) {
			vgLoadIdentity();
			vgTranslate( amb2[i].x, amb2[i].y);
			vgDrawImage( ambImg2 );
		}
	}//������

	for( i=0; i<100; i++ ) {
		if( pol[i].shot == true ) {
			vgLoadIdentity();
			vgTranslate( pol[i].x, pol[i].y);
			vgDrawImage( polImg );
		}
	}

	for( i=0; i<100; i++ ) {
		if( pol2[i].shot == true ) {
			vgLoadIdentity();
			vgTranslate( pol2[i].x, pol2[i].y);
			vgDrawImage( polImg2 );
		}
	}//������



	}

	eglSwapBuffers(display,surface);
}
#define KEY_DOWN(code) ((GetAsyncKeyState(code)&0x8000))
void timerProc()
{
	int item;
	int item2;
	int item3;
	

	item = rand()% (100-0+1);
	item2 =rand()% (200-0+1);
	item3 =rand()% (50-0+1);

	gameCount = (gameCount+1)%30;

	if( KEY_DOWN(VK_RIGHT) && fighter.x<700 )  
	{  fighter.x+=10; }
    if( KEY_DOWN(VK_LEFT) && fighter.x>10 ) 
	{  fighter.x-=10; }
	//if( KEY_DOWN(VK_SPACE) && fighter.y<500 )  fighter.y+=20;
    //if( KEY_DOWN(VK_DOWN) && fighter.y>10 ) fighter.y-=20;
	
	/*finr.count++;
	if(finr.count>2)
		finr.count=0;*/
			

	
	if(fighter.animating){
		fighter.count++;
		if(fighter.count>2 ){
			fighter.count=0;
			fighter.animating= false;
		}
		if(fighter.count>5){
			fighter.count=0;
			fighter.animating= false;
		}
	}

	if(gameState==GAME_FINISH)
	{
		if(item3==0)
	{
		
		for( int i=0; i<100; i++ ) {
			if( fallc[i].shot == 0 ) 
			{
				fallc[i].shot = 1;
				fallc[i].x = rand()%(800-10+1)+10;
				fallc[i].y = 600;
				break;
			}


		}
	}
	for( int i=0; i<100; i++ ) {
		if( fallc[i].shot )
		{
			fallc[i].y-=10;
			if( fallc[i].y<-20) fallc[i].shot=0;
		}
	}
	
	}
	
	
	
	
	if( gameState==GAME_PLAYING || gameState==GAME_PLAYING2 ){
	///
	//��1
	if(item==0)
	{
		
		for( int i=0; i<100; i++ ) {
			if( enemy[i].shot == 0 ) 
			{
				enemy[i].shot = 1;
				enemy[i].x = 800;
				enemy[i].y = 80;
				break;
			}


		}
	}
	for( int i=0; i<100; i++ ) {
		if( enemy[i].shot )
		{
			enemy[i].x-=5;
			if( enemy[i].x<-100) enemy[i].shot=0;
		}
	}

	//��2

	if(item==1)
	{
		
			for( int i=0; i<100; i++ ) {
			if( enemy2[i].shot == 0 ) 
			{
				enemy2[i].shot = 1;
				enemy2[i].x = -100;
				enemy2[i].y = 120;
				break;
			}
		}
	}
	for( int i=0; i<100; i++ ) {
		if( enemy2[i].shot )
		{
			enemy2[i].x+=5;
			if( enemy2[i].x>850) enemy2[i].shot=0;
		}
	}
	
	//��3

	if(item==2)
	{
	
			for( int i=0; i<100; i++ ) {
			if( enemy3[i].shot == 0 ) 
			{
				enemy3[i].shot = 1;
				enemy3[i].x = 800;
				enemy3[i].y = 160;
				break;
			}
		}

	
	}
	for( int i=0; i<100; i++ ) {
		if( enemy3[i].shot )
		{
			enemy3[i].x-=6;
			if( enemy3[i].x<-100) enemy3[i].shot=0;
		}
	}

	//��4

	if(item==3)
	{
		
		for( int i=0; i<100; i++ ) {
			if( enemy4[i].shot == 0 ) 
			{
				enemy4[i].shot = 1;
				enemy4[i].x = -100;
				enemy4[i].y = 200;
				break;
			}
		}
		



	}
	for( int i=0; i<100; i++ ) {
		if( enemy4[i].shot )
		{
			enemy4[i].x+=6;
			if( enemy4[i].x>850) enemy4[i].shot=0;
		}
	}

	
	
	//

	//��5
	
	if(item==4)
	{
		
		for( int i=0; i<100; i++ ) {
			if( enemy5[i].shot == 0 ) 
			{
				enemy5[i].shot = 1;
				enemy5[i].x = 800;
				enemy5[i].y = 320;
				break;
			}


		}
	}
	for( int i=0; i<100; i++ ) {
		if( enemy5[i].shot )
		{
			enemy5[i].x-=5;
			if( enemy5[i].x<-100) enemy5[i].shot=0;
		}
	}

	//��6

	if(item==5)
	{
		
		for( int i=0; i<100; i++ ) {
			if( enemy6[i].shot == 0 ) 
			{
				enemy6[i].shot = 1;
				enemy6[i].x = -100;
				enemy6[i].y = 360;
				break;
			}


		}
	}
	for( int i=0; i<100; i++ ) {
		if( enemy6[i].shot )
		{
			enemy6[i].x+=5;
			if( enemy6[i].x>850) enemy6[i].shot=0;
		}
	}
	
	//��7

	if(item==6)
	{
		
		for( int i=0; i<100; i++ ) {
			if( enemy7[i].shot == 0 ) 
			{
				enemy7[i].shot = 1;
				enemy7[i].x = 800;
				enemy7[i].y = 440;
				break;
			}


		}
	}
	for( int i=0; i<100; i++ ) {
		if( enemy7[i].shot )
		{
			enemy7[i].x-=6;
			if( enemy7[i].x<-100) enemy7[i].shot=0;
		}
	}

	
	//��8
	if(item==7)
	{
		
		for( int i=0; i<100; i++ ) {
			if( enemy8[i].shot == 0 ) 
			{
				enemy8[i].shot = 1;
				enemy8[i].x = -100;
				enemy8[i].y = 480;
				break;
			}


		}
	}
	for( int i=0; i<100; i++ ) {
		if( enemy8[i].shot )
		{
			enemy8[i].x+=6;
			if( enemy8[i].x>850) enemy8[i].shot=0;
		}
	}

	
	if(gameState==GAME_PLAYING2)
	{
	if(item2==7){
		for( int i=0; i<100; i++ ) {
			if( amb[i].shot == 0 ) 
			{
				amb[i].shot = 1;
				crashSound4->Play(0);
				amb[i].x = -100;
				amb[i].y = 360;
				break;
			}}
		}
		for( int i=0; i<100; i++ ) {
		if( amb[i].shot )
		{
			amb[i].x+=20;
			if( amb[i].x>850) amb[i].shot=0;
		}
		}

		if(item2==9){
		for( int i=0; i<100; i++ ) {
			if( amb2[i].shot == 0 ) 
			{
				amb2[i].shot = 1;
				crashSound4->Play(0);
				amb2[i].x = 800;
				amb2[i].y = 80;
				break;
			}}
		}
		for( int i=0; i<100; i++ ) {
		if( amb2[i].shot )
		{
			amb2[i].x-=20;
			if( amb2[i].x<-100) amb2[i].shot=0;
		}
		}

		if(item2==10){
		for( int i=0; i<100; i++ ) {
			if( pol[i].shot == 0 ) 
			{
				pol[i].shot = 1;
				crashSound4->Play(0);
				pol[i].x = -100;
				pol[i].y = 200;
				break;
			}}
		}
		for( int i=0; i<100; i++ ) {
		if( pol[i].shot )
		{
			pol[i].x+=20;
			if( pol[i].x>850) pol[i].shot=0;
		}
		}

		if(item2==11){
		for( int i=0; i<100; i++ ) {
			if( pol2[i].shot == 0 ) 
			{
				pol2[i].shot = 1;
				crashSound4->Play(0);
				pol2[i].x = 800;
				pol2[i].y = 440;
				break;
			}}
		}
		for( int i=0; i<100; i++ ) {
		if( pol2[i].shot )
		{
			pol2[i].x-=20;
			if( pol2[i].x<-100) pol2[i].shot=0;
		}
		}
		}
		}
		
		//���� ����ȭ�� �ڵ��� �޸��� 
		
		/*if(gameState==GAME_START)
		{
			
			if(enemy2[2].shot= 0 ){
				enemy2[2].shot = 1;
				enemy2[2].x = -100;
				enemy2[2].y = 60;
			}
			if( enemy2[2].shot )
		{
			enemy2[2].x+=5;
			if( enemy2[2].x>850) enemy2[2].shot=0;
		}

			
			
			
			
			/*if(item==1)
			{
			for( int i=0; i<100; i++ ) {
			if( enemy2[i].shot == 0 ) 
			{
				enemy2[i].shot = 1;
				enemy2[i].x = -100;
				enemy2[i].y = 60;
				break;
			}
		}}
			
		for( int i=0; i<30; i++ ) {
		if( enemy2[i].shot )
		{
			enemy2[i].x+=5;
			if( enemy2[i].x>850) enemy2[i].shot=0;
		}
	}
	
	//��3

	if(item==2)
	{
		
		for( int i=0; i<100; i++ ) {
			if( enemy3[i].shot == 0 ) 
			{
				enemy3[i].shot = 1;
				enemy3[i].x = 800;
				enemy3[i].y = 20;
				break;
			}
		}
		
	}
	for( int i=0; i<100; i++ ) {
		if( enemy3[i].shot )
		{
			enemy3[i].x-=6;
			if( enemy3[i].x<-100) enemy3[i].shot=0;
		}
	}
	
	}*/


	
	
	//







	/*for(int i=0;i<100;i++) for(int j=0;j<100;j++){
		if(enemy[i].shot&&missiles[j].shot){
			int x11=enemy[i].x;
			int x12=enemy[i].x+76;
			int y11=enemy[i].y;
			int y12=enemy[i].y+40;
			int x21=missiles[j].x;
			int x22=missiles[j].x+24;
			int y21=missiles[j].y;
			int y22=missiles[j].y+12;
			if(x11<x22 && x21<x12 && y11<y22 && y21<y12)
			{
				enemy[i].shot=0;
				missiles[j].shot=0;}
		}
	}*/




	//�浹�˻�

		//
		if(gameState == GAME_PLAYING || gameState == GAME_PLAYING2){
	for(int i=0;i<100;i++){
		if(enemy[i].shot){
			int x11=enemy[i].x;
			int x12=enemy[i].x+30;
			int y11=enemy[i].y;
			int y12=enemy[i].y+30;
			int x21=fighter.x;
			int x22=fighter.x+30;
			int y21=fighter.y;
			int y22=fighter.y+30;
			if(x11<x22 && x21<x12 && y11<y22 && y21<y12)
			{
				crashSound3->Play(0);
				fighter.y = 10;
				fighter.x = 400;
				 for( int i=0; i<100; i++ )
					 enemy[i].shot = false;
				gameState=GAME_OVER;
			}
		}}
	for(int i=0;i<100;i++){
		if(enemy2[i].shot){
			int x11=enemy2[i].x;
			int x12=enemy2[i].x+30;
			int y11=enemy2[i].y;
			int y12=enemy2[i].y+30;
			int x21=fighter.x;
			int x22=fighter.x+30;
			int y21=fighter.y;
			int y22=fighter.y+30;
			if(x11<x22 && x21<x12 && y11<y22 && y21<y12)
			{
				crashSound3->Play(0);
				fighter.y = 10;
				fighter.x = 400;
				 for( int i=0; i<100; i++ )
					 enemy2[i].shot = false;
				gameState=GAME_OVER;
			}
		}}

	//
	for(int i=0;i<100;i++){
		if(enemy3[i].shot){
			int x11=enemy3[i].x;
			int x12=enemy3[i].x+30;
			int y11=enemy3[i].y;
			int y12=enemy3[i].y+30;
			int x21=fighter.x;
			int x22=fighter.x+30;
			int y21=fighter.y;
			int y22=fighter.y+30;
			if(x11<x22 && x21<x12 && y11<y22 && y21<y12)
			{
				crashSound3->Play(0);
				fighter.y = 10;
				fighter.x = 400;
				 for( int i=0; i<100; i++ )
					 enemy3[i].shot = false;
				gameState=GAME_OVER;
			}
		}}
	//
	for(int i=0;i<100;i++){
		if(enemy4[i].shot){
			int x11=enemy4[i].x;
			int x12=enemy4[i].x+30;
			int y11=enemy4[i].y;
			int y12=enemy4[i].y+30;
			int x21=fighter.x;
			int x22=fighter.x+30;
			int y21=fighter.y;
			int y22=fighter.y+30;
			if(x11<x22 && x21<x12 && y11<y22 && y21<y12)
			{
				crashSound3->Play(0);
				fighter.y = 10;
				fighter.x = 400;
				 for( int i=0; i<100; i++ )
					 enemy4[i].shot = false;
				gameState=GAME_OVER;
			}
		}}
	//
	for(int i=0;i<100;i++){
		if(enemy5[i].shot){
			int x11=enemy5[i].x;
			int x12=enemy5[i].x+30;
			int y11=enemy5[i].y;
			int y12=enemy5[i].y+30;
			int x21=fighter.x;
			int x22=fighter.x+30;
			int y21=fighter.y;
			int y22=fighter.y+30;
			if(x11<x22 && x21<x12 && y11<y22 && y21<y12)
			{
				crashSound3->Play(0);
				fighter.y = 10;
				fighter.x = 400;
				 for( int i=0; i<100; i++ )
					 enemy5[i].shot = false;
				gameState=GAME_OVER;
			}
		}}
	//
	for(int i=0;i<100;i++){
		if(enemy6[i].shot){
			int x11=enemy6[i].x;
			int x12=enemy6[i].x+30;
			int y11=enemy6[i].y;
			int y12=enemy6[i].y+30;
			int x21=fighter.x;
			int x22=fighter.x+30;
			int y21=fighter.y;
			int y22=fighter.y+30;
			if(x11<x22 && x21<x12 && y11<y22 && y21<y12)
			{
				crashSound3->Play(0);
				fighter.y = 10;
				fighter.x = 400;
				gameState=GAME_OVER;
			}
		}}
	//
	for(int i=0;i<100;i++){
		if(enemy7[i].shot){
			int x11=enemy7[i].x;
			int x12=enemy7[i].x+30;
			int y11=enemy7[i].y;
			int y12=enemy7[i].y+30;
			int x21=fighter.x;
			int x22=fighter.x+30;
			int y21=fighter.y;
			int y22=fighter.y+30;
			if(x11<x22 && x21<x12 && y11<y22 && y21<y12)
			{
				crashSound3->Play(0);
				fighter.y = 10;
				fighter.x = 400;
				gameState=GAME_OVER;
			}
		}}
	//
	for(int i=0;i<100;i++){
		if(enemy8[i].shot){
			int x11=enemy8[i].x;
			int x12=enemy8[i].x+30;
			int y11=enemy8[i].y;
			int y12=enemy8[i].y+30;
			int x21=fighter.x;
			int x22=fighter.x+30;
			int y21=fighter.y;
			int y22=fighter.y+30;
			if(x11<x22 && x21<x12 && y11<y22 && y21<y12)
			{
				crashSound3->Play(0);
				fighter.y = 10;
				fighter.x = 400;
				gameState=GAME_OVER;
			}
		}}

	if(gameState==GAME_PLAYING2)
	{
		for(int i=0;i<100;i++){
		if(amb[i].shot){
			int x11=amb[i].x;
			int x12=amb[i].x+30;
			int y11=amb[i].y;
			int y12=amb[i].y+30;
			int x21=fighter.x;
			int x22=fighter.x+30;
			int y21=fighter.y;
			int y22=fighter.y+30;
			if(x11<x22 && x21<x12 && y11<y22 && y21<y12)
			{
				crashSound3->Play(0);
				fighter.y = 10;
				fighter.x = 400;
				gameState=GAME_OVER;
			}
		}}

		for(int i=0;i<100;i++){
		if(amb2[i].shot){
			int x11=amb2[i].x;
			int x12=amb2[i].x+30;
			int y11=amb2[i].y;
			int y12=amb2[i].y+30;
			int x21=fighter.x;
			int x22=fighter.x+30;
			int y21=fighter.y;
			int y22=fighter.y+30;
			if(x11<x22 && x21<x12 && y11<y22 && y21<y12)
			{
				crashSound3->Play(0);
				fighter.y = 10;
				fighter.x = 400;
				gameState=GAME_OVER;
			}
		}}

		for(int i=0;i<100;i++){
		if(pol[i].shot){
			int x11=pol[i].x;
			int x12=pol[i].x+30;
			int y11=pol[i].y;
			int y12=pol[i].y+30;
			int x21=fighter.x;
			int x22=fighter.x+30;
			int y21=fighter.y;
			int y22=fighter.y+30;
			if(x11<x22 && x21<x12 && y11<y22 && y21<y12)
			{
				crashSound3->Play(0);
				fighter.y = 10;
				fighter.x = 400;
				gameState=GAME_OVER;
			}
		}}

		for(int i=0;i<100;i++){
		if(pol2[i].shot){
			int x11=pol2[i].x;
			int x12=pol2[i].x+30;
			int y11=pol2[i].y;
			int y12=pol2[i].y+30;
			int x21=fighter.x;
			int x22=fighter.x+30;
			int y21=fighter.y;
			int y22=fighter.y+30;
			if(x11<x22 && x21<x12 && y11<y22 && y21<y12)
			{
				crashSound3->Play(0);
				fighter.y = 10;
				fighter.x = 400;
				gameState=GAME_OVER;
			}
		}}
	
	}


	}

	if(gameState==GAME_PLAYING){

	        int x11=carrot.x;
	        int x12=carrot.x+30;
	        int y11=carrot.y;
			int y12=carrot.y+30;
			int x21=fighter.x;
			int x22=fighter.x+30;
			int y21=fighter.y;
			int y22=fighter.y+30;
			if(x11<x22 && x21<x12 && y11<y22 && y21<y12)
			{
				fighter.y = 10;
				fighter.x = 400;
				gameState=GAME_PLAYING2;
				
			}
	}
	
			if(gameState==GAME_PLAYING2)
			{

			int x11=carrot2.x;
	        int x12=carrot2.x+30;
	        int y11=carrot2.y;
			int y12=carrot2.y+30;
			int x21=fighter.x;
			int x22=fighter.x+30;
			int y21=fighter.y;
			int y22=fighter.y+30;
			if(x11<x22 && x21<x12 && y11<y22 && y21<y12)
			{
				gameState=GAME_FINISH;
				fighter.y = 10;
				fighter.x = 400;
				
			}
			}



		cx+=5;
		
		draw();
	}