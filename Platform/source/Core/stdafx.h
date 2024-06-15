#pragma once
// STL
#include <algorithm>
#include <atomic>
#include <cassert>
#include <cmath>
#include <condition_variable>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <execution>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
// Rendering
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
// Custom
#include "Component/InputComponent.h"
#include "Core/Vector2.h"
#include "Core/Job.h"
#include "Core/AABB.h"
#include "Core/Entity.h"
#include "Core/Game.h"
#include "DataComponent/DebugDataComponent.h"
#include "DataComponent/JumpDataComponent.h"
#include "DataComponent/MoveDataComponent.h"
#include "DataComponent/ScrollDataComponent.h"
#include "System/DebugSystem.h"
#include "System/EntitySystem.h"
#include "System/InputSystem.h"
#include "System/JumpDataSystem.h"
#include "System/PositionDataSystem.h"
#include "System/RenderSystem.h"
#include "System/ScrollSystem.h"

#ifdef _DEBUG
#include "vld.h"
#include "optick.h"
#endif // _DEBUG

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

#define JOB_SYSTEM
//#undef JOB_SYSTEM