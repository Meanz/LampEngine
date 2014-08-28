#pragma once

#include "LampGUI.hpp"
#include "LampComponent.hpp"

namespace LampProject
{

	class LampGUI_Window : public LampComponent
	{

	private:
		bool hovering;

	public:

		LampGUI_Window()
		{
			//Request resources from the asset manager
			Lamp::getAssetManager().loadTexture("gui_menu_left", "./data/ui/menu_bar_left.png");
			Lamp::getAssetManager().loadTexture("gui_menu_middle", "./data/ui/menu_bar_middle.png");
			Lamp::getAssetManager().loadTexture("gui_menu_right", "./data/ui/menu_bar_right.png");

			hovering = false;
		}

		~LampGUI_Window()
		{

		}

		void onTick()
		{
			//Check if the mouse is inside here :D
			int mx = Lamp::getInput().getMouseX();
			int my = Lamp::getInput().getMouseY();

			if (mx >= 10 && mx <= 138 && my >= 50 && my <= 50 + 24)
			{
				hovering = true;
			}
			else
			{
				hovering = false;
			}
		}


		void onDraw(LampGUIPainter& painter)
		{
		

			if (hovering)
			{
				painter.setColor(RED);
			}
			else
			{
				painter.setColor(WHITE);
			}
			painter.drawImage("gui_menu_left", 10, 50);
			painter.drawImage("gui_menu_middle", 42, 50);
			painter.drawImage("gui_menu_middle", 74, 50);
			painter.drawImage("gui_menu_right", 106, 50);
			painter.drawString("Hello World", 28, 50);

		}

	};


}