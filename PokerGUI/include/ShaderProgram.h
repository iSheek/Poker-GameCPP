#pragma once
/**
 * @file ShaderProgram.h
 * @brief File containing declaration of ShaderProgram class
 */

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>

/**
* @brief Class representing shader's program
*/
class ShaderProgram
{
private:
	unsigned int id{};			///< id of the program

	/**
	* @brief Helper function that checks if the uniform was found
	* @param uniformLocation location of the uniform found by using glGetUniformLocation()
	* @param name name of the uniform
	* @details It doesn't throw anything since the app can still work without any crash, but instead there is an information to the console about uniform not found
	* @return true if found
	*/
	bool checkIfUniformFound(GLint uniformLocation, const std::string& name) const;

public:
	/**
	* @brief Main constructor of the class
	* @details It reads from shader files and creates shaders from them and attaches and links them to the program
	* @param vertexPath path to the vertex shader file
	* @param fragmentPath path to the fragment shader file
	* @throws std::runtime_error if there is an error during any part of creating the shaders' program
	*/
	ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath);

	/**
	* @brief Custom destructor
	* @details Deletes program using OpenGL call
	*/
	~ShaderProgram()
	{
		glDeleteProgram(id);
	}

	/**
	* @name Copying and moving
	* Class is the sole owner of the resources and copying would cause double remove
	*/
	///@{
	ShaderProgram(const ShaderProgram& other) = delete;
	ShaderProgram(ShaderProgram&& other) = delete;
	ShaderProgram& operator=(const ShaderProgram& other) = delete;
	ShaderProgram& operator=(ShaderProgram&& other) = delete;
	///@}

	/**
	* @brief Method that starts using this program
	* @details This method has to be called before rendering vertices that were made to use this program
	*/
	void use()
	{
		glUseProgram(id);
	}

	/**
	* @name Setting uniforms
	* Separate methods for setting different types of uniforms
	*/
	///@{
	// utility uniform functions
// ------------------------------------------------------------------------
	void setBool(const std::string& name, bool value) const
	{
		GLint uniformLocation{ glGetUniformLocation(id, name.c_str()) };

		if (checkIfUniformFound(uniformLocation, name))
		{
			glUniform1i(uniformLocation, static_cast<int>(value));
		}
	}
	// ------------------------------------------------------------------------
	void setInt(const std::string& name, int value) const
	{
		GLint uniformLocation{ glGetUniformLocation(id, name.c_str()) };
		if (checkIfUniformFound(uniformLocation, name))
		{
			glUniform1i(uniformLocation, value);
		}
	}
	// ------------------------------------------------------------------------
	void setFloat(const std::string& name, float value) const
	{
		GLint uniformLocation{ glGetUniformLocation(id, name.c_str()) };
		if (checkIfUniformFound(uniformLocation, name))
		{
			glUniform1f(uniformLocation, value);
		}
	}
	// ------------------------------------------------------------------------
	void setVec2(const std::string& name, const glm::vec2& value) const
	{
		GLint uniformLocation{ glGetUniformLocation(id, name.c_str()) };
		if (checkIfUniformFound(uniformLocation, name))
		{
			glUniform2fv(uniformLocation, 1, &value[0]);
		}
	}
	void setVec2(const std::string& name, float x, float y) const
	{
		GLint uniformLocation{ glGetUniformLocation(id, name.c_str()) };
		if (checkIfUniformFound(uniformLocation, name))
		{
			glUniform2f(uniformLocation, x, y);
		}
	}
	// ------------------------------------------------------------------------
	void setVec3(const std::string& name, const glm::vec3& value) const
	{
		GLint uniformLocation{ glGetUniformLocation(id, name.c_str()) };
		if (checkIfUniformFound(uniformLocation, name))
		{
			glUniform3fv(uniformLocation, 1, &value[0]);
		}
	}
	void setVec3(const std::string& name, float x, float y, float z) const
	{
		GLint uniformLocation{ glGetUniformLocation(id, name.c_str()) };
		if (checkIfUniformFound(uniformLocation, name))
		{
			glUniform3f(uniformLocation, x, y, z);
		}
	}
	// ------------------------------------------------------------------------
	void setVec4(const std::string& name, const glm::vec4& value) const
	{
		GLint uniformLocation{ glGetUniformLocation(id, name.c_str()) };
		if (checkIfUniformFound(uniformLocation, name))
		{
			glUniform4fv(uniformLocation, 1, &value[0]);
		}
	}
	void setVec4(const std::string& name, float x, float y, float z, float w) const
	{
		GLint uniformLocation{ glGetUniformLocation(id, name.c_str()) };
		if (checkIfUniformFound(uniformLocation, name))
		{
			glUniform4f(uniformLocation, x, y, z, w);
		}
	}
	// ------------------------------------------------------------------------
	void setMat2(const std::string& name, const glm::mat2& mat) const
	{
		GLint uniformLocation{ glGetUniformLocation(id, name.c_str()) };
		if (checkIfUniformFound(uniformLocation, name))
		{
			glUniformMatrix2fv(uniformLocation, 1, GL_FALSE, &mat[0][0]);
		}
	}
	// ------------------------------------------------------------------------
	void setMat3(const std::string& name, const glm::mat3& mat) const
	{
		GLint uniformLocation{ glGetUniformLocation(id, name.c_str()) };
		if (checkIfUniformFound(uniformLocation, name))
		{
			glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, &mat[0][0]);
		}
	}
	// ------------------------------------------------------------------------
	void setMat4(const std::string& name, const glm::mat4& mat) const
	{
		GLint uniformLocation{ glGetUniformLocation(id, name.c_str()) };
		if (checkIfUniformFound(uniformLocation, name))
		{
			glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &mat[0][0]);
		}
	}
	///@}

	/**
	* @brief Getter of the program's id
	* @return id of the program
	*/
	unsigned int getId() const
	{
		return id;
	}
};