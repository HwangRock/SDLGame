#include "func.h"
#include <windows.h>
#include<string>
#include<vector>
#include "SDL_image.h"

int g_input;
double g_elapsed_time_ms;

std::string g_output;

int g_X;
int g_Y;

int sizeH;
int sizeW;

SDL_Rect catPos;
SDL_Rect dogPos;
SDL_Texture* catTexture;
SDL_Texture* dogTexture;





/////////////////////////////////////////////////////////////
void InitGame() {
	g_input = 0;
	g_output = "*";
	g_flag_running = true;

	g_X = 0;
	g_Y = 10;

	sizeH = 20;
	sizeW = 30;

	g_elapsed_time_ms = 0;


	


	// std::cout ��¿� ���۸� ����Ͽ�, ��� �ӵ��� �������� ������ ���Ѵ�.
	setvbuf(stdout, NULL, _IOLBF, 4096);

	// Clear the console screen.
	system("cls");
}



/////////////////////////////////////////////////////////////


void Update()
{

	//left
	if (g_input == 1) { g_X--; }
	//right
	else if (g_input == 2) { g_X++; }
	//up
	else if (g_input == 3) { g_Y--; }
	//down
	else if (g_input == 4) { g_Y++; }


	//shot space
	if (g_input == 5)
	{

		

		g_input = 0;
	}

	
	g_elapsed_time_ms += 33;



}



/////////////////////////////////////////////////////////////
// �׸��� �׸��� �Լ�.

void Render() {
	//// 1. ��� �׸���.
	// 1.1. Ŀ���� �ܼ� ȭ���� ���� �� �𼭸� �κ����� �ű��. ��ǥ(0, 0)
	COORD cur;
	cur.X = 0;
	cur.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);

	//// 1.2. ��� �κ�
	for (int i = 0; i < sizeH; i++) {
		for (int j = 0; j < sizeW; j++) {
			if (i == g_Y && j == g_X) { std::cout << "*"; }
			else { std::cout << "_"; }
		}
		std::cout << std::endl;
	}

	//// 1.3. ��� �Ʒ��� �ð�
	std::cout << "Elapsed Time: " << g_elapsed_time_ms / 1000.0f << std::endl;



	//// 3. ������ �ϼ�.
	// std::cout���� ����� ���� ��, ���� ȭ�鿡 ǥ�õ� �ʰ� ���ۿ� ���� �ִ� ���� �ִٸ�, ��� ȭ�鿡 ��µǵ��� �Ѵ�.
	std::cout.flush();

}



/////////////////////////////////////////////////////////////
// HandleEvents() 
// �̺�Ʈ�� ó���ϴ� �Լ�.
// main �Լ��� while loop�� ���ؼ� ������ �ݺ� ȣ��ȴٴ� ���� ����.
void HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {

		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_LEFT) {
				g_input = 1;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT) {
				g_input = 2;
			}
			else if (event.key.keysym.sym == SDLK_UP) {
				g_input = 3;
			}
			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				g_input = 4;
			}
			else if (event.key.keysym.sym == SDLK_SPACE)
			{
				g_input = 5;
			}
			break;

		case SDL_KEYUP:
			g_input = 0;
			break;

		case SDL_MOUSEBUTTONDOWN:
			// ���콺 ���� ��ư�� ���� ���� ��.
			break;

		default:
			break;
		}
	}

}




/////////////////////////////////////////////////////////////
// ClearGame() 
// ���α׷��� ���� �� �� �� ȣ��Ǵ� �Լ�.
// �� �Լ����� ���� �ڿ�(�̹���, ���� ��)�� �޸� ���� �����ؾ��Ѵ�.
void ClearGame()
{
}