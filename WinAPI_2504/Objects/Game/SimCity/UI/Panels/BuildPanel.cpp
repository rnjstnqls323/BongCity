#include "Framework.h"

BuildPanel::BuildPanel():Panel(PanelType::BuildPanel)
{
	Init();
	panel = new BuildButtonPanel();

}

BuildPanel::~BuildPanel()
{
}

void BuildPanel::Update()
{
	panel->Update();
}

void BuildPanel::Render()
{
	panel->Render();
}

void BuildPanel::Edit()
{
	panel->Edit();
}

void BuildPanel::CreateButtons()
{
	
}

void BuildPanel::SetButtonEvents()
{
}
