#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>
#include <thread>

#include "Vector2.h"
#include "AABB.h"

#ifdef _DEBUG
#include "vld.h"
#include "optick.h"
#endif // _DEBUG

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>


// static values for the game
static const size_t k_LEVEL_WIDTH = 25u;
static const size_t k_LEVEL_HEIGHT = 15u;
static const size_t k_SCREEN_WIDTH = 20u;
static const size_t k_SCREEN_HEIGHT = 15u;
static const size_t k_SPRITE_WIDTH = 32u;
static const size_t k_SPRITE_HEIGHT = 32u;

// direction of the input
enum Direction : int
{
	LEFT = -1,
	RIGHT = 1
};
