#ifndef VISUALIZER_H
#define VISUALIZER_H

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

#include "MusicManager.h"
#include "Mesh.h"

#include<iostream>
#include <GLFW/glfw3.h>
#include<stdlib.h>

class Visualizer
{
public:
	Visualizer() {}
	void run();
};

#endif
