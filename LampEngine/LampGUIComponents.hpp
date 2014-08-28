#pragma once

#include "LampGUI.hpp"
#include "LampComponent.hpp"

namespace LampProject
{

	class LampGUI_Window : public LampComponent
	{

	private:

	public:

		LampGUI_Window()
		{
			//Request resources from the asset manager
			Lamp::getAssetManager().loadTexture("gui_menu_left", "./data/ui/menu_bar_left.png");
			Lamp::getAssetManager().loadTexture("gui_menu_middle", "./data/ui/menu_bar_middle.png");
			Lamp::getAssetManager().loadTexture("gui_menu_right", "./data/ui/menu_bar_right.png");
		}

		~LampGUI_Window()
		{

		}


		void onDraw(LampGUIPainter& painter)
		{
			
			painter.drawImage("gui_menu_left", 10, 50);
			painter.drawImage("gui_menu_middle", 42, 50);
			painter.drawImage("gui_menu_middle", 74, 50);
			painter.drawImage("gui_menu_right", 106, 50);
			painter.drawString("Hello World", 28, 50);

		}

	};


}