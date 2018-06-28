#include "../Header/TextQuad.h"

TextQuad::TextQuad()
{
	//font = TTF_OpenFont("Resource/Font/arial.ttf", 18);
	//if (font == NULL)
	//	throw (string)"Failed to load font! SDL_ttf error: " + TTF_GetError();

	//SDL_Surface* surface = TTF_RenderUTF8_Blended(font, "hah ur mom", SDL_Color { 0, 0, 0, 255 });
	//texture = new Texture(surface);
	//SDL_FreeSurface(surface);

	vector<float> vertices =
	{
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};

	vector<Uint32> indices =
	{
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	const Uint32 Stride = 3;

	texture = new Texture("wall.png");
	renderComponent = new RenderComponent(texture, vertices, Stride, indices);
	transformComponent = new TransformComponent();
}

TextQuad::~TextQuad()
{
	delete texture;
	TTF_CloseFont(font);
}
