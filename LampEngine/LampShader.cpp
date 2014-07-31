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

std::string LampShader::getErrorString()
{
	return m_shaderSource;
}

void LampShader::setSource(std::string src)
{
	m_shaderSource = src;
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
	glGetShaderiv(m_glId, GL_COMPILE_STATUS, &isCompiled);

	if (!isCompiled)
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

void LampShaderProgram::addShader(LampShader* pShader)
{
	if (pShader == NULL) return; //Don't want to add a null shader do we

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

bool LampShaderProgram::compile()
{

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
			printf("Shader Compile Error\n%s", m_vShaders[i]->getErrorString().c_str());

			compileFailed = true;
			break;
		}
	}
	if (compileFailed)
	{
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

	}


	m_isCompiled = true;
	return true; //Compile okay! Wooohoo
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

}