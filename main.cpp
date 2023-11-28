#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "SDL.h"

#pragma comment(lib, "SDL2")      //전처리기 라이브러리에 추가
#pragma comment(lib, "SDL2main")  

const int NUM_IMAGE = 4; // 사진 갯수

int main(int argc, char* argv[])
{
	srand(static_cast<unsigned int>(time(nullptr)));
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* Mywindow = SDL_CreateWindow("Hello World", 100, 100, 800, 600, SDL_WINDOW_OPENGL);
	SDL_Renderer* MyRenderer = SDL_CreateRenderer(Mywindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);

	SDL_Event MyEvent;
	bool IsRunning = true;

	SDL_Surface* imageSurface = SDL_LoadBMP("SDL2/tr (2).bmp");
	if (!imageSurface)
	{
		std::cerr << "Failed to load BMP file: " << SDL_GetError() << std::endl;
		return -1;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(MyRenderer, imageSurface);
	SDL_FreeSurface(imageSurface);

	SDL_Rect destRect = { 100, 100, 200, 200 };

	while (IsRunning)
	{
		SDL_PollEvent(&MyEvent);
		switch (MyEvent.type)
		{
		case SDL_QUIT:
			IsRunning = false;
			break;
		case SDL_KEYDOWN:
			if (MyEvent.key.keysym.sym == SDLK_ESCAPE)
			{
				IsRunning = false;
			}
			break;
		}

		SDL_SetRenderDrawColor(MyRenderer, 0xff, 0xae, 0xc8, 0x00);
		SDL_RenderClear(MyRenderer);

		for (int i = 0; i < 1000; ++i)
		{
			int X = rand() % 800;
			int Y = rand() % 600;
			int W = rand() % 200 + 10;
			int H = rand() % 200 + 10;
			int R = rand() % 256;
			int G = rand() % 256;
			int B = rand() % 256;
			int A = rand() % 256;

			SDL_SetRenderDrawColor(MyRenderer, R, G, B, A);
			SDL_Rect MyRect = { X, Y, W, H };
			SDL_RenderFillRect(MyRenderer, &MyRect);
		}

		destRect.x = rand() % 600;  // 랜덤 X 좌표 갱신
		destRect.y = rand() % 400;  // 랜덤 Y 좌표 갱신

		SDL_RenderCopy(MyRenderer, texture, NULL, &destRect);
		SDL_RenderPresent(MyRenderer);
	}

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(MyRenderer);
	SDL_DestroyWindow(Mywindow);
	SDL_Quit();
	return 0;
}
