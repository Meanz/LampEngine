#pragma once

#include "stdafx.h"
#include "LampGUIPainter.hpp"

namespace LampProject
{

	class LampComponent
	{

	private:
		//The area of this screen that this component occupies
		Area m_Area;
		//Only allow this component to draw things within it's Area
		//This should perhaps be configured in the shader?
		//Eg X > Area.X + Area.Width == discard ?
		bool m_Enclosed;

		//The parent of this component
		LampComponent* m_pParent;

		//The children of this component
		std::vector<LampComponent*> m_vChildren;
		
		//The add and remove queue for the components
		//This is done in order to avoid concurrent modification 
		std::vector<LampComponent*> m_vAddQueue;
		std::vector<LampComponent*> m_vRemoveQueue;


	public:

		LampComponent();
		~LampComponent();

		LampComponent* getParent();
		void setParent(LampComponent* pParent);

		//Add the given component to this component
		void add(LampComponent* pComponent);
		//Remove the given component from this component
		void remove(LampComponent* pComponent);
		//Remove this component from it's parent
		void remove();
		//Check if the given component is a child of this component
		bool has(LampComponent* pComponent);

		//Get the area of this component
		Area& getArea();
		//Set the area of this component
		void setArea(Area area);

		virtual void onTick() {};
		virtual void onDraw(LampGUIPainter& pPainter) {};

		void doTick();
		void doDraw(LampGUIPainter& pPainter);

	};

}