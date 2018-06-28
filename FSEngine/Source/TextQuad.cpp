#include "../Header/TextQuad.h"

TextQuad::TextQuad()
{
	const int FontSize = 18;
	font = TTF_OpenFont("Resource/Font/arial.ttf", FontSize);
	if (font == NULL)
		throw (string)"Failed to load font! SDL_ttf error: " + TTF_GetError();

	SDL_Surface* surface = TTF_RenderText_Blended(font, "hah crappy text", SDL_Color { 0, 0, 0, 255 });
	texture = new Texture(surface);
	SDL_FreeSurface(surface);

	vector<float> vertices =
	{
		 // positions         // texture coords
		-1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
		 1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
		-1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f,  0.0f, 0.0f
	};

	vector<Uint32> indices =
	{
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	const Uint32 Stride = 5;
	renderComponent = new RenderComponent(texture, vertices, indices, Stride);

	transformComponent = new TransformComponent();
	transformComponent->SetPosition(vec3(2, 0.2f, -3));
}

TextQuad::~TextQuad()
{
	delete texture;
	TTF_CloseFont(font);
}
