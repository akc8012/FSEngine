#include "../Header/Window.h"

Window::Window(FileSystem* fileSystem)
{
	this->fileSystem = fileSystem;
	CreateWindow(GetResolutionSetting(), fileSystem->GetSettingsValue<bool>("Fullscreen"));
}

void Window::CreateWindow(const tvec2<int>& resolution, bool fullscreen)
{
	if (sdlWindow != nullptr)
		SDL_DestroyWindow(sdlWindow);

	const int FullscreenFlag = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
	const int OnTopFlag = fileSystem->GetSettingsValue<bool>("ShowWindowOnTop") ? SDL_WINDOW_ALWAYS_ON_TOP : 0;
	const int WindowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | OnTopFlag | FullscreenFlag;

	const tvec2<int> WindowSize = fullscreen ? GetScreenResolution() : resolution;
	sdlWindow = SDL_CreateWindow("FSEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WindowSize.x, WindowSize.y, WindowFlags);

	if (sdlWindow == nullptr)
		throwFS((string)"Window could not be created: " + SDL_GetError());
}

void Window::ToggleFullscreen()
{
	SDL_GetWindowFlags(sdlWindow) & SDL_WINDOW_FULLSCREEN ? SetWindowed() : SetFullscreen();
}

void Window::SetWindowed()
{
	tvec2<int> resolutionSetting = GetResolutionSetting();

	SDL_SetWindowSize(sdlWindow, resolutionSetting.x, resolutionSetting.y);
	SDL_SetWindowFullscreen(sdlWindow, 0);
	SDL_SetWindowPosition(sdlWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

void Window::SetFullscreen()
{
	tvec2<int> screenResolution = GetScreenResolution();

	SDL_SetWindowSize(sdlWindow, screenResolution.x, screenResolution.y);
	SDL_SetWindowFullscreen(sdlWindow, SDL_WINDOW_FULLSCREEN);
}

void Window::SetResolutionToWindowResolution()
{
	tvec2<int> windowSize = GetWindowSize();
	SetResolution(windowSize.x, windowSize.y);
}

void Window::SetResolution(int width, int height)
{
	const int PositionX = 0, PositionY = PositionX;
	glViewport(PositionX, PositionY, width, height);
}

tvec2<int> Window::GetWindowSize() const
{
	int width, height;
	SDL_GetWindowSize(sdlWindow, &width, &height);
	return tvec2<int>(width, height);
}

tvec2<int> Window::GetScreenResolution() const
{
	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);
	return tvec2<int>(displayMode.w, displayMode.h);
}

tvec2<int> Window::GetResolutionSetting() const
{
	json resolution = fileSystem->GetSettingsValue("Resolution");
	return tvec2<int>(resolution[0], resolution[1]);
}

SDL_Window* Window::GetSDLWindow() const
{
	return sdlWindow;
}

void Window::SwapWindow()
{
	SDL_GL_SwapWindow(sdlWindow);
}

Window::~Window()
{
	SDL_DestroyWindow(sdlWindow);
}
