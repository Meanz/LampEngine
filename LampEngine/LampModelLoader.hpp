#pragma once

namespace LampProject
{

	class LampModelLoader
	{

	private:

	public:

		LampModelLoader();
		~LampModelLoader();

		LampGameObject* loadModel(std::string modelPath);

	};

}

