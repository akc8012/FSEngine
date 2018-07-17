#include "../Header/Window.h"

Window::Window(FileSystem* fileSystem)
{
	this->fileSystem = fileSystem;

	CreateWindow(GetResolutionSetting(), fileSystem->GetSettingsValue<bool>("Fullscreen"));
	CreateContext();
}

Window::Window(FileSystem* fileSystem, const tvec2<int>& size, bool fullscreen)
{
	this->fileSystem = fileSystem;

	CreateWindow(size, fullscreen);
	CreateContext();
}

void Window::CreateWindow(const tvec2<int>& resolution, bool fullscreen)
{
	if (window != nullptr)
		SDL_DestroyWindow(window);

	const tvec2<int> WindowSize = fullscreen ? GetScreenResolution() : resolution;
	const int FullscreenFlag = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
	const int OnTopFlag = fileSystem->GetSettingsValue<bool>("ShowWindowOnTop") ? SDL_WINDOW_ALWAYS_ON_TOP : 0;
	const int WindowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | OnTopFlag | FullscreenFlag;
	window = SDL_CreateWindow("FSEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WindowSize.x, WindowSize.y, WindowFlags);

	if (window == nullptr)
		throw (string)"Window could not be created: " + SDL_GetError();
}

void Window::CreateContext()
{
	SDL_GL_DeleteContext(context);
	context = SDL_GL_CreateContext(window);
	if (context == nullptr)
		throw (string)"OpenGL context could not be created! SDL Error: " + SDL_GetError();
}

void Window::ToggleFullscreen()
{
	SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN ? SetWindowed() : SetFullscreen();
}

void Window::SetWindowed()
{
	tvec2<int> resolutionSetting = GetResolutionSetting();

	SDL_SetWindowSize(window, resolutionSetting.x, resolutionSetting.y);
	SDL_SetWindowFullscreen(window, 0);
	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

void Window::SetFullscreen()
{
	tvec2<int> screenResolution = GetScreenResolution();

	SDL_SetWindowSize(window, screenResolution.x, screenResolution.y);
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
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
	SDL_GetWindowSize(window, &width, &height);
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

void Window::SwapWindow()
{
	SDL_GL_SwapWindow(window);
}

Window::~Window()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
}
