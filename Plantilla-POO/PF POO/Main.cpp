#include <Windows.h>
#include <windowsx.h>
#include "glew.h"
#include <gl\GLU.h>
#include <gl\GL.h>
#include "Scene.h"
#include <time.h>
#include "GamePadRR.h"
#include "resource.h"
#pragma comment (lib, "glew32.lib") 
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib") 

#define Timer1 100

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
WPARAM wParamL;
void DefPixelFormat(HDC hDC);
int x, y, Lx, Ly,counter;
HWND hInfo = 0;
HWND hText = 0;
bool ableToCheck = false;
HDC hContextoVentana;
Scene *scene;
GamePadRR *gamPad;
bool renderiza = false;
unsigned int dayTimer = 0;
RECT wr = { 100, 100, 1080, 720 };
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hwndVentana;
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX); //Tama�o en bytes de la estructura.
	wc.style = CS_HREDRAW | CS_VREDRAW; //Entero de 16 bits que codifica el estilo de la clase de ventana.
	wc.lpfnWndProc = WindowProc;//Apunta al procedimiento de ventana.
	wc.hInstance = hInstance;//Identifica la instancia de la ventana a la que esta clase pertenece.
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);//Identificador del curso de la clase. Debe ser un manipulador de un recurso de tipo icono. Si es Null, la aplicaci�n mostrar� un icono cuando el usuario minice la ventana de la aplicaci�n.
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW; //Identificador del pincel para la clase.
	wc.lpszClassName = "IvanWindow"; //Especifica el nombre de la clase ventana.
	RegisterClassEx(&wc);//Registra una clase de ventana para su uso subsecuente en llamadas a las funciones CreateWindow o CreateWindowEx
	
	
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);//Calcula el tama�o necesario del rect�ngulo de la ventana.

	//Se crea la ventana definida previamente.
	hwndVentana = CreateWindowEx(NULL,//estilo extendido de ventana
		"IvanWindow",//puntero al nombre de la clase registrada *visto arriba*
		"Ventana Proyecto de POO",//puntero al nombre de la ventana
		WS_OVERLAPPEDWINDOW,//estilo de ventana
		wr.left,//posici�n horizontal de la ventana
	wr.top,//posici�n vertical de la ventana
		wr.right,//ancho de la ventana
		wr.bottom ,//alto de la ventana
		NULL,//manejador de la ventana padre o propietaria
		NULL,//manejador del menu o identificador de ventana hija
		hInstance,//manejador de la instancia de la aplicaci�n
		NULL);//puntero a los datos de creaci�n de la ventana

	ShowWindow(hwndVentana, nCmdShow);//Muestra la ventana creada
	ShowWindow(hInfo, SW_SHOW);
	//ShowCursor(false);
	
	
	glewInit();//Inicializa glew

	//Instancia de la escena
	scene = new Scene(hwndVentana);

	gamPad = new GamePadRR(1);
	ableToCheck = true;

	//Crear un timer con el valor especificado de time-out
	SetTimer(hwndVentana,//Manejador de ventana que recibir� los mensajes del timer
		Timer1,//identificador del timer
		30,//valor de time-out
		NULL);//direcci�n del procedimiento de timer

	MSG msg = { 0 };
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				break;
		}
		else
		{
			if (renderiza)
			{
				
				
				scene->render(hContextoVentana);
				renderiza = false;
				if (gamPad->IsConnected())
				{
					//PISTA: Algo puedes lograr aqui con ayuda del autocompletador
				}


			}
		}
	}

	return msg.wParam;

}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	static HGLRC hContextoGL;
	static HDC hContextoAux;
	int ancho, alto;
	char epx[6] = "";
	char epz[6] = "";
	char epy[6] = "";
	char edx[6] = "";
	char edz[6] = "";
	char edy[6] = "";
	char ec[80] = "";

	switch (message)
	{
	case WM_CREATE:
		hContextoAux = GetDC(hWnd);
		hContextoVentana = hContextoAux;
		DefPixelFormat(hContextoVentana);
		hContextoGL = wglCreateContext(hContextoVentana);
		wglMakeCurrent(hContextoVentana, hContextoGL);
		srand(time(NULL));
		break;
	


	case WM_MOUSEMOVE:
		Lx = x;
		Ly = y;
		x = GET_X_LPARAM(lParam);
		y = GET_Y_LPARAM(lParam);
		
 if (x >= ((wr.right ) / 2) + 200 || x <= ((wr.right ) / 2) - 200 || y <=((wr.bottom+wr.top)/2)-200 || y >= ((wr.bottom + wr.top) / 2) + 200)
		
		{
			SetCursorPos((wr.right + wr.left) /2, (wr.bottom + wr.top) / 2);
		}
	

			 if (Lx/10 < x/10) {
				 scene->turnRight();
		       	renderiza = true;
			  }
			 else {
				 if (Lx/10 > x/10 ) {
					
					 scene->turnLeft();
					 renderiza = true;
				 }
				
			 }
			 if (Ly/4 < y/4)
			 {
				 scene->turnDown();
				 renderiza = true;
			 }
			 else
			 {
				 if (Ly/4  > y/4 )
				 {
					 scene->turnUp();
					 renderiza = true;
				 }
				
			 }
			
		 
			 
		

	
				 break;
	

	case WM_KEYDOWN:
		switch (wParam)
		{


		case VK_F1:
		{
			string info = "X: " + to_string(scene->px) + " Y: " + to_string(scene->py)+ " Z: " +to_string(scene->pz);
			MessageBox(hWnd,info.c_str(),"INFO",MB_OK);
		}
			break;
		case VK_F2:
		{
			scene->Drawtru = true;
			
			
		}break;
		

		case VK_F3:
		{
			scene->GunH = new EDXFramework::Model("Modelos//Gun//Shotgun2.obj", "Modelos//Gun//Shotgun.bmp", 1);

		}break;
		case VK_F4:
		{
			scene->GunH = new EDXFramework::Model("Modelos//Gun//Rifle2.obj", "Modelos//Gun//Rifle.bmp", 1);

		}break;
		case VK_F5:
		{
			scene->GunH = new EDXFramework::Model("Modelos//Gun//Gun2.obj", "Modelos//Gun//Gun.bmp", 1);

		}break;
		case VK_F6:
		{
			if (scene->Tm)
			{
				scene->Tm = false;

			}
			else
			{
				scene->Tm = true;

			}
		
		}break;

		case VK_F7:
		{
			if (scene->Disco)
			{
				scene->Disco = false;

			}
			else
			{
				scene->Disco = true;

			}

		}break;

		case VK_SPACE:
		{
			scene->JA = true;
			scene->loop = 0;
			scene->CB = 0;
			


		}break;

		case VK_UP:
			scene->turnUp();
			renderiza = true;
			return 0;
		case VK_DOWN:
			scene->turnDown();
			renderiza = true;
			return 0;
		case VK_LEFT:
			scene->turnLeft();
			renderiza = true;
			return 0;
		case VK_RIGHT:
			scene->turnRight();
			renderiza = true;
			return 0;
		case 0x44: //D
			scene->move('r');
			renderiza = true;
			wParamL = wParam;
			return 0;
		case 0x45: //D
			scene->Enemi.Shoot();
			return 0;


		case 0x41: //A
			scene->move('l');
			renderiza = true;
			wParamL = wParam;
			return 0;
		case 0x57: //W
			scene->move('f');
			renderiza = true;
			wParamL = wParam;
			return 0;
		case 0x53: //S
			scene->move('b');
			renderiza = true;
			wParamL = wParam;
			return 0;
		}
		break;
	case WM_TIMER:
	{
		renderiza = true;

		scene->Animate++;
	}
		break;
	case WM_DESTROY:
	{
		KillTimer(hWnd, Timer1);
		delete scene;
		PostQuitMessage(0);
		wglMakeCurrent(hContextoVentana, NULL);
		wglDeleteContext(hContextoGL);
	
		return 0;
	} break;

	case WM_SIZE:
	{
		alto = HIWORD(lParam);
		ancho = LOWORD(lParam);
		if (alto == 0)
			alto = 1;
		glViewport(0, 0, ancho, alto);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, (GLfloat)ancho / (GLfloat)alto, 1.0f, 10000.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	break;
	}

	
	return DefWindowProc(hWnd, message, wParam, lParam);
}

void DefPixelFormat(HDC hDC)
{
	int bestmatch;

	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR), //tama�o de la estructura
		1, //numero de version
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, //soporta la ventana, el opengl y manejara doble buffer
		PFD_TYPE_RGBA, //formato de 32 bits rgba
		32, //tama�o del color en 32 bits
		0, 0, 0, 0, 0, 0, //bits de color, no se usan
		0, //no hay buffer para el alfa
		0, //ignore el bit de corrimiento
		0, //no hay buffer de acumulacion
		0, 0, 0, 0, //no hay bits de acumulacion
		16, //tama�o del flotante para el buffer z
		0, //no hay buffers de stencil
		0, //no hay buffers auxiliares
		PFD_MAIN_PLANE, //plano principal para dibujo
		0, //reservado
		0, 0, 0 //mascaras de capas ignoradas
	};

	bestmatch = ChoosePixelFormat(hDC, &pfd);
	SetPixelFormat(hDC, bestmatch, &pfd);
}
