#include "stdafx.h"
#include "LampModelLoader.hpp"
#include "LampMWMLoader.hpp"
#include "LampMeshRenderer.hpp"
#include "LampSkeletalMeshRenderer.hpp"
#include "LampOBJLoader.hpp"
#include <rapidxml.hpp>

using namespace rapidxml;
using namespace std;

//#############
//# CPP Class #
//#############

LampModelLoader::LampModelLoader()
{

}

LampModelLoader::~LampModelLoader()
{

}

LampGameObject* LampModelLoader::loadModel(string modelPath)
{
	//Read a file from lamp utils!
	LampFileReadResult lfrr = readFile(modelPath);

	if (!lfrr.readComplete)
	{
		return NULL;
	}

	//Init rapid xml!
	xml_document<> doc;
	doc.parse<0>((char*)lfrr.fileContents.c_str());

	//First one should always be model!

	//Test the first node
	if (doc.first_node() != 0)
	{

		//Do string matching!
		if (strcmp("model", doc.first_node()->name()) == 0)
		{
			//Initialize our game object!

			//Our current node!
			xml_node<>* modelNode = doc.first_node();

			//Check if the document has a basedir attrib
			xml_attribute<>* basedirAttrib = modelNode->first_attribute("basedir");

			std::string basedir = "./";
			if (basedirAttrib != NULL)
			{
				//Parse the attribute
				basedir = basedirAttrib->value();
			}

			//TODO: Instead of iterating over each object and then comparing it
			//Search for each object type and then process it
			//This way we can attach the skeleton and meshes and everything in the order we want to.
			//Make's life a whole lot easier you know.


			//Create our game object here and return it!
			LampGameObject* lgo = new LampGameObject();


			xml_node<>* meshNode = modelNode->first_node("mesh");
			while (meshNode != NULL)
			{
				xml_node<>* textureNode = meshNode->first_node("texture");
				xml_node<>* skeletonNode = meshNode->first_node("skeleton");

				LampMesh* pMesh = NULL;
				LampTexture* pTexture = NULL;
				LampSkeleton* pSkeleton = NULL;

				if (meshNode != NULL)
				{
					char* nodeName = meshNode->name();
					xml_attribute<>* pPathAttrib = meshNode->first_attribute("path");
					string nodeValue = basedir + (pPathAttrib == NULL ? "" : pPathAttrib->value());

					//Load the mesh!

					//Check if the type attribute is there!
					xml_attribute<>* pTypeAttrib = meshNode->first_attribute("type");

					if (pTypeAttrib == NULL || pTypeAttrib->value() == "lm")
					{
						LampMWMLoader loader(nodeValue);
						pMesh = loader.loadModel();
						
					}
					else if (strcmp(pTypeAttrib->value(), "obj") == 0)
					{
						LampOBJLoader loader(nodeValue);
						pMesh = loader.loadMesh();
					}
					else
					{
						throw new std::runtime_error("Invalid type flag in " + modelPath);
					}
					if (pMesh != NULL)
					{
						pMesh->setMaterial(Lamp::getAssetManager().createMaterial());
						//Do we have a skeleton?
						if (skeletonNode != NULL)
						{
							pMesh->getMaterial()->setShader(Lamp::getAssetManager().getShaderProgram("skinned"));
							pMesh->setCompileMode(LampMeshCompileMode::COMPILE_LEGACY);
						}
						else
						{
							pMesh->getMaterial()->setShader(Lamp::getAssetManager().getShaderProgram("default"));
						}
						
					}
				}

				if (textureNode != NULL)
				{
					char* nodeName = textureNode->name();
					string nodeValue = basedir + textureNode->value();

					//Load the texture!
					pTexture = Lamp::getAssetManager().loadTexture(nodeValue);

					if (pMesh != NULL)
					{
						pMesh->getMaterial()->setTexture("diffuse", pTexture);
					}
				}

				if (skeletonNode != NULL)
				{
					char* nodeName = skeletonNode->name();
					string nodeValue = basedir + skeletonNode->value();

					LampMWMLoader loader(nodeValue);
					pSkeleton = loader.loadSkeleton();
				}

				//Seing as we can have several animations associated with this model
				//Let's just iterate!
				xml_node<>* animation = meshNode->first_node("animation");
				if (animation != NULL)
				{
					if (skeletonNode == NULL)
					{
						throw new std::runtime_error("Can not animate a mesh without a skeleton.");
					}
					while (animation != NULL)
					{
						animation = animation->next_sibling("animation");
					}
				}

				//Do we have a skeletal mesh?
				if (meshNode != NULL)
				{
					if (skeletonNode != NULL)
					{
						lgo->addComponent(new LampSkeletalMeshRenderer(pMesh, pSkeleton));
					}
					else
					{
						//We don't have a skeletal mesh, so let's just give it an ordinary
						//Mesh renderer
						lgo->addComponent(new LampMeshRenderer(pMesh));
					}
				}

				meshNode = meshNode->next_sibling("mesh");
			}

			return lgo;
		}
		else
		{
			//Report invalid xml file?
			printf("First node does not match \"model\"\n");
			return NULL;
		}
	}
	else
	{
		//Report invalid xml file?
		printf("First node does not exist!\n");
		return NULL;
	}

	//Return null anyways :D
	return NULL;
}


