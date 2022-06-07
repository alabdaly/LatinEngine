#pragma once
#include "Base/Application.h"
#include "Base/TimeStep.h"
#include "Base/Input.h"

#include "OpenGL/Renderer.h"


#define StartLatinEngine(classname, width, height) LATIN::Application* app = new classname; app->Run(width, height); 