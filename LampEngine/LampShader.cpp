#include "stdafx.h"
#include "LampShader.hpp"


LampShader::LampShader(LampShaderType shaderType) :
m_shaderType(shaderType),
m_glId(0)
{
}

LampShader::~LampShader()
{
	if (m_glId > 0)
		glDeleteShader(m_glId);
}

GLuint LampShader::getGLId()
{
	return m_glId;
}

std::string LampShader::getErrorString()
{
	return m_errorString;
}

std::string LampShader::getSource()
{
	return m_shaderSource;
}

void LampShader::setSource(std::string src)
{
	m_shaderSource = src;
}

LampShaderType LampShader::getType()
{
	return m_shaderType;
}

std::string LampShader::getTypeString()
{
	if (m_shaderType == LampShaderType::FRAGMENT) 
	{
		return "FRAGMENT_SHADER";
	}
	else if (m_shaderType == LampShaderType::VERTEX)
	{
		return "VERTEX_SHADER";
	}
	else if (m_shaderType == LampShaderType::GEOMETRY)
	{
		return "GEOMETRY_SHADER";
	} 
	else
	{
		return "UNKNOWN TYPE";
	}
}

bool LampShader::compile()
{
	if (m_glId > 0)
	{
		glDeleteShader(m_glId);
	}

	//Generate our shader
	GLint iShaderType = GL_FRAGMENT_SHADER;
	if (m_shaderType == LampShaderType::FRAGMENT)
	{
		//do nothing, but it's important that it is here
	}
	else if (m_shaderType == LampShaderType::VERTEX)
	{
		iShaderType = GL_VERTEX_SHADER;
	}
	else if (m_shaderType == LampShaderType::GEOMETRY)
	{
		iShaderType = GL_GEOMETRY_SHADER;
	}
	else
	{
		m_errorString = "Invalid Shader Type";
		return false;
	}

	m_glId = glCreateShader(iShaderType);

	if (!m_glId)
	{
		m_errorString = "Could not create shader, glCreateShader failed.";
		return false;
	}

	//Upload source
	const GLchar* source = (const GLchar*)m_shaderSource.c_str();
	glShaderSource(m_glId, 1, &source, 0);

	//Compile the shader
	glCompileShader(m_glId);
	//Is compiled?
	GLint isCompiled = 0;
	glGetShaderiv(m_glId, GL_COMPILE_STATUS, (int*)&isCompiled);

	if (isCompiled == GL_FALSE)
	{
		//Store error string!
		GLint maxLength = 0;
		glGetShaderiv(m_glId, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(m_glId, maxLength, &maxLength, &infoLog[0]);

		m_errorString = (char*)&infoLog[0];
	}
	return isCompiled <= 0 ? false : true;
}

LampShaderProgram::LampShaderProgram() :
m_glId(0), m_isCompiled(false)
{

}

LampShaderProgram::~LampShaderProgram()
{
	//Delete all associated shader objects ? :o
	for (unsigned int i = 0; i < m_vShaders.size(); i++)
	{
		delete m_vShaders[i]; //this will cause glDeleteShader on the shader
	}

	if (m_glId > 0)
	{
		glDeleteProgram(m_glId);
	}
}

GLuint LampShaderProgram::getGLId()
{
	return m_glId;
}

std::string LampShaderProgram::getErrorString()
{
	return m_errorString;
}

void LampShaderProgram::addShader(LampShader* pShader)
{
	if (pShader == NULL)
	{
		printf("Attempted to add null shader.\n");
		return; //Don't want to add a null shader do we
	}

	m_vShaders.push_back(pShader);
}

void LampShaderProgram::clearShaders()
{
	for (unsigned int i = 0; i < m_vShaders.size(); i++)
	{
		//Delete?
		delete m_vShaders[i];
	}

	m_vShaders.clear();
}

bool LampShaderProgram::compile(LampShaderMap shaderMap)
{
	//Set the shader map
	m_shaderMap = shaderMap;

	//Try to compile all shaders before we continue compiling!
	//Important for the recompile feature!
	std::vector<LampShader*> compiledShaders;

	//There was a reason for this complexity,
	//And well, it's ugly now,
	//But I am to lazy to change it back, it works :D
	//TODO: Find a reason for me writing all this text instead of actually just fixing the code
	bool compileFailed = false;
	for (unsigned int i = 0; i < m_vShaders.size(); i++)
	{
		bool didCompile = m_vShaders[i]->compile();
		if (!didCompile)
		{
			//Print log?
			printf("Shader[%s] Compile Error\n%s", m_vShaders[i]->getTypeString().c_str(), m_vShaders[i]->getErrorString().c_str());

			compileFailed = true;
			break;
		}
	}
	if (compileFailed)
	{
		printf("Unable to compile shaders.\n");
		return false;
	}

	//Create a new program!
	if (m_glId > 0)
	{
		glDeleteProgram(m_glId);
	}
	m_glId = glCreateProgram();

	//Attach all shaders!
	for (unsigned int i = 0; i < m_vShaders.size(); i++)
	{
		printf("Attached shader: %i\n", i);
		glAttachShader(m_glId, m_vShaders[i]->getGLId());
	}

	glLinkProgram(m_glId);

	GLint isLinked = 0;
	glGetProgramiv(m_glId, GL_LINK_STATUS, (int*)&isLinked);

	if (isLinked == GL_FALSE)
	{
		//Store error string!
		GLint maxLength = 0;
		glGetProgramiv(m_glId, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(m_glId, maxLength, &maxLength, &infoLog[0]);

		m_errorString = (char*)&infoLog[0];

		compileFailed = true;
	}

	//Delete the attached shaders!
	for (unsigned int i = 0; i < m_vShaders.size(); i++)
	{
		glDetachShader(m_glId, m_vShaders[i]->getGLId());
		delete m_vShaders[i]; //Delete the shader!
	}
	m_vShaders.clear();

	

	//Error checking
	printf("########## SHADER LOG ##########\n");
	if (compileFailed) 
	{
		m_isCompiled = false;
		printf("Unable to link program: \n%s\n", m_errorString.c_str());
		std::cin.get();
	}
	else
	{
		m_isCompiled = true;
		printf("Program linked okay!");

		//Find all uniform locations
		int samplerIndex = 0;
		for (unsigned int i = 0; i < m_shaderMap.uniformNames.size(); i++)
		{
			GLint loc = glGetUniformLocation(m_glId, m_shaderMap.uniformNames[i].c_str());
			if (loc == -1) 
			{
				printf("Could not find location for uniform %s\n", m_shaderMap.uniformNames[i].c_str());
			}
			else
			{
				m_shaderMap.uniformLocations[i] = loc;

				if (m_shaderMap.uniformTypes[i] == "sampler2D")
				{
					m_shaderMap.samplerSlots[m_shaderMap.uniformNames[i]] = samplerIndex++;
				}
			}
		}
	}

	return !compileFailed; //Compile okay! Wooohoo
}

void LampShaderProgram::use()
{
	if (!m_isCompiled)
	{
		//Error!
		printf("Tried to use uncompiled shader! (TODO: Remove this message and add an error reporting system )  :D");
	}
	else
	{
		glUseProgram(m_glId);
	}
}

void LampShaderProgram::updateUniforms(LampRenderer& renderer)
{
	for (unsigned int i = 0; i < m_shaderMap.uniformNames.size(); i++)
	{
		std::string& uniformName = m_shaderMap.uniformNames[i];
		std::string& uniformType = m_shaderMap.uniformTypes[i];
		const GLint uniformLocation = m_shaderMap.uniformLocations[i];

		if (uniformLocation == -1)
		{
			continue; //Ignore this mapping
		}

		//Do uniform name checkings
		//Should really pass these things into hashes later for easier lookups
		//Maybe some fancy lookup tables :D
		if (uniformName.substr(0, 2) == "R_")
		{
		}
		else if (uniformType == "sampler2D")
		{
			//Lookup sampler slots
			GLuint samplerSlot = m_shaderMap.getSamplerSlot(uniformName);
			if (samplerSlot == -1) continue; //sampler slot not found
			std::string map = uniformName.substr(2);

			//Find texture through material
			//tex = pMaterial->getTexture(map)
			//tex->bind();
		}
		else if (uniformName.substr(0, 2) == "T_")
		{
			//Transform related
			std::string unprefixedName = uniformName.substr(2);

			if (unprefixedName == "projectionView")
			{
				//Get the projection matrix from the camera
				glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(Lamp::getScene().getCamera()->getProjectionMatrix()));
			}
			else if (unprefixedName == "world")
			{
				//Get the projection matrix from the camera
				//Just for testing :D
				glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(Lamp::getScene().getCamera()->getViewMatrix()));
			}
		}
		else
		{
			printf("Unhandled uniform type: %s name: %s in shader.\n", uniformType.c_str(), uniformName.c_str());
		}
	}
}