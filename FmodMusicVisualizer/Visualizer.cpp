#include "Visualizer.h"
#include<iostream>


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


void Visualizer::run() {
	
	//Initialise glfw
	if (!glfwInit()) {
		cout<<"GLFW Initialization failed"<< endl;
		glfwTerminate();
		exit(-1);
	}
	//Setup glfw window properties
	//opengl version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "MusicVisualizer", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		exit(-1);
	}

	//set context for glew to use
	glfwMakeContextCurrent(window);
	//get buffersize information
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//Allow modern extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		cout << "GLEW initialization failed" << endl;
		glfwDestroyWindow(window);
		glfwTerminate();
		exit(-1);
	}

	//printf("OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));	

	Shader shader = Shader("Shaders/ShaderVertex.glsl", "Shaders/ShaderFragment.glsl");

	// create meshes
	GLint barNum = 10;
	Mesh* meshes = new Mesh[barNum];

	for (GLint idx = 0; idx < barNum; idx++) {
		meshes[idx].setVertices(idx, barNum); // set x coordinate
		meshes[idx].setupMesh();
		meshes[idx].loadTexture("Media/blue.jfif");
	}

	MusicManager player;
	player.loadMusic("Media/Swedish House Mafia - Don t You Worry Child.mp3");
	player.playMusic();

	// initialize spectrum
	int size = player.initSpectrum(12);
	float* frequencies = new float[size]();


	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		// get frequency
		player.getFrequency(frequencies);

		GLfloat red = 0.02f + (frequencies[1] * 0.9f);
		GLfloat green = 0.4f + (frequencies[1] * 0.2f);
		GLfloat blue = 0.639f + (frequencies[1] * 0.1f);


		// render
		glClearColor(red, green, blue, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.use();

		for (GLint i = 0; i < barNum; i++) {
			GLfloat yCoordinate = frequencies[i];
			GLfloat corr = yCoordinate * pow(2, i);
			meshes[i].draw(shader, corr);
		}

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();

}