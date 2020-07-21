#pragma once

#include <cglm/cglm.h>
#include "Graphics/Window.h"
#include "Graphics/KeyCodes.h"
#include "Utils/Types.h"

typedef struct OrthographicCamera {
    f32 Rotation; 
    f32 Speed;
    f32 AspectRatio;
    f32 ZoomLevel;
    vec3 Position;
    mat4 ViewMatrix;
    mat4 ViewProjectionMatrix;
    mat4 ProjectionMatrix;
} OrthographicCamera;

OrthographicCamera 
orthographic_camera_create(f32 left, f32 right, f32 bot, f32 top);

void
orthographic_camera_set_projection(OrthographicCamera* camera, f32 left, f32 right, f32 bot, f32 top);

void
orthographic_camera_recalculate_view_matrix(OrthographicCamera* camera);

static void
orthographic_camera_on_update(OrthographicCamera* camera, Window* window, f32 timestep)
{
    if (window_is_key_pressed(window, KEY_W))
    {
	camera->Position[1] += camera->Speed * timestep;
    }
    else if (window_is_key_pressed(window, KEY_S))
    {
	camera->Position[1] -= camera->Speed * timestep;
    }
    if (window_is_key_pressed(window, KEY_A))
    {
	camera->Position[0] -= camera->Speed * timestep;
    }
    else if (window_is_key_pressed(window, KEY_D))
    {
	camera->Position[0] += camera->Speed * timestep;
    }
	
    if (window_is_key_pressed(window, KEY_Q))
    {
	camera->Rotation += 0.1f * timestep;
    }
    else if (window_is_key_pressed(window, KEY_E))
    {
	camera->Rotation -= 0.1f * timestep;
    }

    orthographic_camera_set_projection(camera, -camera->AspectRatio * camera->ZoomLevel, camera->AspectRatio * camera->ZoomLevel, -camera->ZoomLevel, camera->ZoomLevel);
    orthographic_camera_recalculate_view_matrix(camera);
}

static void
orthographic_camera_on_event(OrthographicCamera* camera, Event* event)
{
    if (event->Category == MouseCategory)
    {
	if (event->Type == MouseScrolled)
	{
	    MouseScrolledEvent* mevent = (MouseScrolledEvent*)event;

	    if (camera->ZoomLevel > 0.1f)
	    {
		camera->ZoomLevel -= mevent->YOffset / 10;
	    }
	    else if (mevent->YOffset < 0.0f)
	    {
		camera->ZoomLevel -= mevent->YOffset / 10;
	    }
	}
    }
}

static void
orthographic_camera_resize(OrthographicCamera* camera, f32 width, f32 height)
{
    camera->AspectRatio = width / height;
    orthographic_camera_set_projection(camera, -camera->AspectRatio * camera->ZoomLevel, camera->AspectRatio * camera->ZoomLevel, -camera->ZoomLevel, camera->ZoomLevel);
}
