#include "../Header/Window.h"

Window::Window(FileSystem* fileSystem)
 : fileSystem(fileSystem)
{
	CreateWindow(GetSurfaceSizeSettingsValue(), fileSystem->GetSettingsValue<bool>("Fullscreen"));
}

tvec2<int> Window::GetSurfaceSizeSettingsValue() const
{
	json surfaceSize = fileSystem->GetSettingsValue("SurfaceSize");
	return tvec2<int>(surfaceSize[0], surfaceSize[1]);
}

void Window::CreateWindow(const tvec2<int>& surfaceSize, bool fullscreen)
{
	if (sdlWindow != nullptr)
		SDL_DestroyWindow(sdlWindow);

	const int FullscreenFlag = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
	const int OnTopFlag = fileSystem->GetSettingsValue<bool>("ShowWindowOnTop") ? SDL_WINDOW_ALWAYS_ON_TOP : 0;
	const int WindowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | OnTopFlag | FullscreenFlag;

	const tvec2<int> SurfaceSize = fullscreen ? GetScreenResolution() : surfaceSize;
	sdlWindow = SDL_CreateWindow("FSEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SurfaceSize.x, SurfaceSize.y, WindowFlags);

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
	tvec2<int> surfaceSizeSetting = GetSurfaceSizeSettingsValue();

	SDL_SetWindowSize(sdlWindow, surfaceSizeSetting.x, surfaceSizeSetting.y);
	SDL_SetWindowFullscreen(sdlWindow, 0);
	SDL_SetWindowPosition(sdlWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

void Window::SetFullscreen()
{
	tvec2<int> screenResolution = GetScreenResolution();

	SDL_SetWindowSize(sdlWindow, screenResolution.x, screenResolution.y);
	SDL_SetWindowFullscreen(sdlWindow, SDL_WINDOW_FULLSCREEN);
}

tvec2<int> Window::GetSurfaceSize() const
{
	tvec2<int> surfaceSize = tvec2<int>(0, 0);
	SDL_GetWindowSize(sdlWindow, &surfaceSize.x, &surfaceSize.y);
	return surfaceSize;
}

void Window::SetSurfaceSizeSizeFromSettingsValue()
{
	SetSurfaceSize(GetSurfaceSizeSettingsValue());
}

void Window::SetSurfaceSize(const tvec2<int>& surfaceSize)
{
	if (surfaceSize == GetSurfaceSize())
		return;

	SDL_SetWindowSize(sdlWindow, surfaceSize.x, surfaceSize.y);
}

bool Window::ContinuallyReloadSurfaceSizeSetting() const
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

void Window::ReceiveEvent(const string& key, const json& event)
{
	if (key == "SurfaceSizeChanged")
		SetViewportSize(tvec2<int> { event[0], event[1] });
}

void Window::SetViewportSize(const tvec2<int>& viewportSize)
{
	const tvec2<int> ZeroPosition = tvec2<int>(0, 0);
	glViewport(ZeroPosition.x, ZeroPosition.y, viewportSize.x, viewportSize.y);
}

Window::~Window()
{
	SDL_DestroyWindow(sdlWindow);
}
