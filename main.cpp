#include <SDL.h>
#undef main
class Application {
public:
	Application() {
		m_Window = SDL_CreateWindow(
			"SimpleStuff",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			680, 480, NULL);
		m_WindowSurface = SDL_GetWindowSurface(m_Window);
		m_PlayerSurface = SDL_LoadBMP("player.bmp");
		m_PlayerPosition.x = 0;
		m_PlayerPosition.y = 0;
		m_PlayerPosition.w = 16;
		m_PlayerPosition.h = 16;
		m_RealPositionX = 0;
		m_RealPositionY = 0;
	}
	~Application() {
		SDL_FreeSurface(m_WindowSurface);
		SDL_DestroyWindow(m_Window);
	}
	void loop() {
		bool windowOpen = true;
		while (windowOpen) {
			while (SDL_PollEvent(&m_WindowEvent) > 0) {
				switch (m_WindowEvent.type) {
				case SDL_QUIT:
					windowOpen = false;
					break;
				case SDL_MOUSEMOTION:
					m_RealPositionX = m_WindowEvent.motion.x;
					m_RealPositionY = m_WindowEvent.motion.y;
				}
			}
			update(1.0/60.0);
			draw();
		}
	}
	void update(double delta_time) {
		m_PlayerPosition.x = m_RealPositionX - 16;
		m_PlayerPosition.y = m_RealPositionY - 16;
	}
	void draw() {
		SDL_UpdateWindowSurface(m_Window);
		SDL_FillRect(m_WindowSurface, NULL, SDL_MapRGB(m_WindowSurface->format, 0, 0, 0));
		SDL_BlitSurface(m_PlayerSurface, NULL, m_WindowSurface, &m_PlayerPosition);
	}
private:
	SDL_Window* m_Window;
	SDL_Surface* m_WindowSurface;
	SDL_Event m_WindowEvent;
	SDL_Surface* m_PlayerSurface;
	SDL_Rect m_PlayerPosition;
	double m_RealPositionX;
	double m_RealPositionY;
};

int main() {
	Application app;
	app.loop();
}