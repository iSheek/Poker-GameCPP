/**
 * @file ShaderProgram.cpp
 * @brief File containing definition of ShaderProgram class' methods
 */

#include "ShaderProgram.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cassert>


namespace {

	/**
	* @brief Helper function that checks whether there was any error while compiling
	* @param shader id of the shader
	* @return true if there was an error
	*/
	bool checkIfCompileErrors(GLuint shader)
	{
		constexpr int infoLogSize{ 1024 };
		GLint success{};
		GLchar infoLog[infoLogSize];

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, infoLogSize, NULL, infoLog);
			std::cerr << "ERROR::SHADER_COMPILATION_ERROR " << "\n" << infoLog << "\n -- --------------------------------------------------- -- \n";
			return true;
		}


		return false;
	}

	/**
	* @brief Helper function that checks whether there was any error while linking the program
	* @param program id of the program
	* @return true if there was an error
	*/
	bool checkIfLinkingErrors(GLuint program)
	{
		constexpr int infoLogSize{ 1024 };
		GLint success{};
		GLchar infoLog[infoLogSize];

		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(program, infoLogSize, NULL, infoLog);
			std::cerr << "ERROR::PROGRAM_LINKING_ERROR " << "\n" << infoLog << "\n -- --------------------------------------------------- -- \n";
			return true;
		}
		
		return false;
	}


	/**
	* @brief Helper class that was made to utilize RAII if there is any error during compiling shaders
	*/
	class ScopedShader
	{
	private:
		unsigned int id{};							///< id of the shader
		std::string shaderPath{};					///< path to the shader file
	public:
		/**
		* @brief Main constructor of the helper class
		* @param shaderPath path to the file containing shader's source code
		* @param shaderType either: GL_VERTEX_SHADER, GL_FRAGMENT_SHADER or GL_GEOMETRY_SHADER
		* @details It first reads shader's source file, after that it creates shader, compilation is in separate method since destructor is only called after object is fully created
		* @throws std::runtime_error if there is any error during reading file or creating shader
		*/
		ScopedShader(const std::string& shaderPath, GLenum shaderType) : shaderPath(shaderPath)
		{
			assert(shaderType == GL_VERTEX_SHADER || shaderType == GL_FRAGMENT_SHADER || shaderType == GL_GEOMETRY_SHADER);

			std::ifstream shaderFile{};
			shaderFile.open(shaderPath);
			if (!shaderFile)
			{
				throw std::runtime_error("ERROR SHADER FILE NOT READ: " + shaderPath);
			}

			std::stringstream shaderStream{};
			shaderStream << shaderFile.rdbuf();

			std::string shaderCode{ shaderStream.str() };
			const char* inputCode{ shaderCode.c_str() };

			// create shader
			id = glCreateShader(shaderType);
			if (id == 0)
			{
				throw std::runtime_error("ERROR SOMETHING WRONG OCCURED DURING CREATING SHADER: " + shaderPath);
			}
			glShaderSource(id, 1, &inputCode, NULL);

		}

		/**
		* @name Copying and moving
		* Class is the sole owner of the resources and copying would cause double remove
		*/
		///@{
		ScopedShader(const ScopedShader& other) = delete;
		ScopedShader(ScopedShader&& other) = delete;
		ScopedShader& operator=(const ScopedShader& other) = delete;
		ScopedShader& operator=(ScopedShader&& other) = delete;
		///@}

		/**
		* @brief Custom destructor of the helper class
		* @details It calls OpenGL function to delete the shader
		*/
		~ScopedShader()
		{
			glDeleteShader(id);
		}

		/**
		* @brief Separate method for compiling the shader
		* @details If something goes wrong then we utilize RAII and destroy the object properly if there is any stack unwinding
		* @throws std::runtime_error if there is an error during compiling the shader
		*/
		void compile()
		{
			glCompileShader(id);
			if (checkIfCompileErrors(id))
			{
				throw std::runtime_error("ERROR SOMETHING WRONG OCCURED DURING COMPILING SHADER: " + shaderPath);
			}
		}

		/**
		* @brief Getter of the shader's id
		* @return shader's id
		*/
		unsigned int getId() const
		{
			return id;
		}
	};
}

bool ShaderProgram::checkIfUniformFound(GLint uniformLocation, const std::string& name) const
{
	if (uniformLocation == -1)
	{
		std::cerr << "WARNING UNIFORM NOT FOUND: " << name << '\n';
		return false;
	}
	return true;
}

ShaderProgram::ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath)
{
	ScopedShader vertex{ vertexPath, GL_VERTEX_SHADER };
	vertex.compile();

	ScopedShader fragment{ fragmentPath, GL_FRAGMENT_SHADER };
	fragment.compile();

	// shader Program
	id = glCreateProgram();
	if (id == 0)
	{
		throw std::runtime_error("ERROR SOMETHING WRONG OCCURED DURING CREATING PROGRAM");
	}

	glAttachShader(id, vertex.getId());
	glAttachShader(id, fragment.getId());
	glLinkProgram(id);

	if (checkIfLinkingErrors(id))
	{
		glDeleteProgram(id);
		throw std::runtime_error("ERROR SOMETHING WRONG OCCURED DURING PROGRAM LINKING");
	}


}
