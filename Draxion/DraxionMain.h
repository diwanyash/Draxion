#pragma once

// For Client Use Only
#include "src/Draxion/Core/Application.h"
#include "src/Draxion/Events/Event.h"
#include "src/Draxion/Events/EventDispatcher.h"
#include "src/Draxion/Events/KeyEvent.h"
#include "src/Draxion/Core/Logger.h"
#include "src/Draxion/Core/Util/RandomGen.h"
#include "src/Draxion/Events/MouseEvents.h"

//-------------Input----------------------
#include "src/Draxion/Input/Input.h"
#include "src/Draxion/Input/KeyCodes.h"
//----------------------------------------

//----------------------------------------
#include "src/Draxion/Renderer/Texture.h"
//----------------------------------------

//-------------Layers---------------------
#include "src/Draxion/Core/Layer/ImGuiLayer.h"
//----------------------------------------

//-------------Debug---------------------
#include "src/Draxion/Debug/Profiler/ProfileTimer.h"
//----------------------------------------


//---------Rendering_Helpers---------
#include "src/Draxion/Renderer/Buffer/VertexArray.h"
#include "src/Draxion/Renderer/Buffer/Buffer.h"
#include "src/Draxion/Renderer/Shader/Shader.h"
#include "src/Draxion/Renderer/RendererCommand.h"
#include "src/Draxion/Renderer/Renderer.h"
#include "src/Draxion/Renderer/Renderer2D.h"
#include "src/Draxion/Core/ECS/System.h"
//-----------------------------------


//---------Camera---------
#include "src/Draxion/Renderer/OrthoGraphicCamera.h"
#include "src/Draxion/OrthoGraphicCameraController.h"
//------------------------


//-----ENTRY POINT--------------
//#include "src/Draxion/Core/EntryPoint.h" // OTHER FILES ON CLIENT SIDE WILL INCLUDE THIS AND IT'S PROBLEMATIC
//------------------------------