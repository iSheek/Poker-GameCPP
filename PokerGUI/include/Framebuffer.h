#pragma once

/**
 * @file Framebuffer.h
 * @brief File containing declaration of Framebuffer class
 */


/**
* @brief Class responsible for creating, allowing framebuffer to be drawn into virtual resolution and drawing it into window's resolution
*/
class Framebuffer {
private:
	unsigned int FBO{};					///< id of the framebuffer object
	unsigned int textureId{};			///< id of the texture that saves pixels of the original scene

public:
	/**
	* @brief Main constructor of the class
	* @throws std::runtime_error when framebuffer's status isn't complete when it should
	* @pre There has to be existing OpenGL context
	* @details It generates framebuffer object, texture, and sets up the parameters
	*/
	Framebuffer();


	/**
	* @name Copying and moving
	* Class is the sole owner of the resources and copying would cause double remove
	*/
	///@{
	Framebuffer(const Framebuffer& other) = delete;
	Framebuffer(Framebuffer&& other) = delete;
	Framebuffer& operator=(const Framebuffer& other) = delete;
	Framebuffer& operator=(Framebuffer&& other) = delete;
	///@}

	/**
	* @brief Custom destructor
	* @details It deletes framebuffer object and texture
	*/
	~Framebuffer();

	/**
	* @brief Binds the framebuffer from this class and clears color buffer bit using poker table color
	* @details It sets up viewport to virtual resolution and from now on every draw call is made into this framebuffer
	*/
	void drawToFramebuffer();

	/**
	* @brief Shows rendered objects from virtual resolution scaled to window's resolution
	* @details The image is centered and the image is scaled to the biggest integer multiple that fits in the window, 
	* if the window size isn't proper multiple then there will be black bars, this method has to be called after drawing the scene but before rendering ImGui
	* @param windowWidth width of the glfw window (using glfwGetFramebufferSize())
	* @param windowHeight height of the glfw window (using glfwGetFramebufferSize())
	*/
	void showInWindow(int windowWidth, int windowHeight);


};