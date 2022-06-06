#pragma once
#include "Base/Application.h"


#define StartLatinEngine(classname, width, height) LATIN::Application* app = new classname; app->Run(width, height); 