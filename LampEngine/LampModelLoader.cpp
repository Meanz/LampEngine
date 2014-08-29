#include "stdafx.h"
#include "LampModelLoader.hpp"
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

			//Now parse the child nodes of the model node!
			xml_node<>* workingNode = modelNode->first_node();
			while (workingNode != NULL)
			{
				//Get the name of this node!
				char* nodeName = workingNode->name();
				string nodeValue = basedir + workingNode->value();

				if (strcmp("mesh", nodeName) == 0)
				{
					//Let's do some checking, does this model have a skeleton node?
					bool hasSkeleton = false;
					if (workingNode->next_sibling("skeleton") != NULL) hasSkeleton = true;

					printf("MeshPath: %s\n", nodeValue.c_str());

					if (hasSkeleton)
					{
						//We want to create a skeletal mesh!
						//LampSkeletalMesh
					}
					else
					{

					}
				}
				else if (strcmp("texture", nodeName) == 0)
				{
					//We can also get texture by id!
					//<texture>id:engine_texture0</texture>
					
					//First test the length of the str
					if (nodeValue.length() >= 3)
					{
						if (strcmp("id:", nodeValue.substr(0, 3).c_str()) == 0)
						{
							//We have an id node!
						}
					}
					
					//Do full load!
					
				}
				else if (strcmp("skeleton", nodeName) == 0)
				{

				}
				else if (strcmp("animation", nodeName) == 0)
				{
				}
				else
				{
					printf("Uhandled node type in model. Type: %s\n", nodeName);
				}

				//Next
				workingNode = workingNode->next_sibling();
			}
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


