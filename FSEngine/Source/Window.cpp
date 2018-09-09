#include "../Header/Window.h"

Window::Window(FileSystem* fileSystem)
{
	this->fileSystem = fileSystem;
	CreateWindow(GetWindowSizeSettingsValue(), fileSystem->GetSettingsValue<bool>("Fullscreen"));
}

tvec2<int> Window::GetWindowSizeSettingsValue() const
{
	json windowSize = fileSystem->GetSettingsValue("WindowSize");
	return tvec2<int>(windowSize[0], windowSize[1]);
}

void Window::CreateWindow(const tvec2<int>& windowSize, bool fullscreen)
{
	if (sdlWindow != nullptr)
		SDL_DestroyWindow(sdlWindow);

	const int FullscreenFlag = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
	const int OnTopFlag = fileSystem->GetSettingsValue<bool>("ShowWindowOnTop") ? SDL_WINDOW_ALWAYS_ON_TOP : 0;
	const int WindowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | OnTopFlag | FullscreenFlag;

	const tvec2<int> WindowSize = fullscreen ? GetScreenResolution() : windowSize;
	sdlWindow = SDL_CreateWindow("FSEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WindowSize.x, WindowSize.y, WindowFlags);

	if (sdlWindow == nullptr)
		throwFS((string)"Window could not be created: " + SDL_GetError());
}

tvec2<int> Window::GetScreenResolution() const
{
	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);
	return tvec2<int>(displayMode.w, displayMode.h);
}

void Window::ToggleFullscreen()
{
	IsFullscreen() ? SetWindowed() : SetFullscreen();
}

void Window::SetWindowed()
{
	tvec2<int> windowSizeSetting = GetWindowSizeSettingsValue();

	SDL_SetWindowSize(sdlWindow, windowSizeSetting.x, windowSizeSetting.y);
	SDL_SetWindowFullscreen(sdlWindow, 0);
	SDL_SetWindowPosition(sdlWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

void Window::SetFullscreen()
{
	tvec2<int> screenResolution = GetScreenResolution();

	SDL_SetWindowSize(sdlWindow, screenResolution.x, screenResolution.y);
	SDL_SetWindowFullscreen(sdlWindow, SDL_WINDOW_FULLSCREEN);
}

void Window::SetResolutionToWindowSize()
{
	tvec2<int> windowSize = GetWindowSize();

	tvec2<int> position = tvec2<int>(0, 0);
	glViewport(position.x, position.y, windowSize.x, windowSize.y);
}

tvec2<int> Window::GetWindowSize() const
{
	tvec2<int> windowSize = tvec2<int>(0, 0);
	SDL_GetWindowSize(sdlWindow, &windowSize.x, &windowSize.y);
	return windowSize;
}

void Window::SetWindowSizeFromSettingsValue()
{
	SetWindowSize(GetWindowSizeSettingsValue());
}

void Window::SetWindowSize(const tvec2<int>& windowSize)
{
	if (windowSize == GetWindowSize())
		return;

	SDL_SetWindowSize(sdlWindow, windowSize.x, windowSize.y);
}

bool Window::ContinuallyReloadWindowSizeSetting() const
{
	return !IsFullscreen();
}

bool Window::IsFullscreen() const
{
	return SDL_GetWindowFlags(sdlWindow) & SDL_WINDOW_FULLSCREEN;
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
