#include "RunGameState.h"
#include <XEngine.h>

RunGameState::RunGameState()
	: GameState(State::RunGame)
{

}

RunGameState::~RunGameState()
{
}

void RunGameState::Load()
{
}

State RunGameState::Update(float deltaTime)
{
	if (X::IsKeyPressed(X::Keys::ENTER))
	{
		return State::End;
	}
	return State::RunGame;
}

void RunGameState::Render()
{
	const float textSize = 100.0f;
	const char* text = "RUNGAMESCREEN\nPress ENTER to Start";
	float textWidth = X::GetTextWidth(text, textSize);
	float screenX = (X::GetScreenWidth() - textWidth) * 0.5f;
	float screenY = X::GetScreenHeight() * 0.5f;
	X::DrawScreenText(text, screenX, screenY, textSize, X::Colors::White);
}
void RunGameState::Unload()
{
}

