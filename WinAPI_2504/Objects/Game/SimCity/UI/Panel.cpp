#include "Framework.h"

Panel::Panel(PanelType type)
{
	buttons.reserve(MAX_BUTTON_SIZE);
}

Panel::~Panel()
{
	for (Button* button : buttons)
	{
		delete button;
	}
}

void Panel::Update()
{
	for (Button* button : buttons)
	{
		button->Update();
	}
}

void Panel::Render()
{
	for (Button* button : buttons)
	{
		button->Render();
	}
}

void Panel::Edit()
{
	for (Button* button : buttons)
	{
		button->Edit();
	}
}

void Panel::Init()
{
	CreateButtons();
	SetButtonEvents();
}
