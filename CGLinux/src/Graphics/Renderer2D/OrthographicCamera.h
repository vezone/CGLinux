#pragma once

#include <cglm/cglm.h>
#include "Utils/Types.h"

typedef struct OrthographicCamera {
	mat4 ProjectionMatrix;
	mat4 ViewMatrix;
	mat4 ViewProjectionMatrix;
	vec3 Position;
	f32 Rotation; 
} OrthographicCamera;

OrthographicCamera 
orthographic_camera_create(f32 left, f32 right, f32 bot, f32 top);

void
orthographic_camera_set_projection(OrthographicCamera* camera, f32 left, f32 right, f32 bot, f32 top);

void
orthographic_camera_recalculate_view_matrix(OrthographicCamera* camera);

static void
orthographic_camera_on_update(OrthographicCamera* camera, f32 aspectRatio, f32 zoomLevel)
{
  orthographic_camera_set_projection(camera, 
      -aspectRatio * zoomLevel, 
       aspectRatio * zoomLevel, 
      -zoomLevel,
       zoomLevel);
  orthographic_camera_recalculate_view_matrix(camera);
}

static void
orthographic_camera_resize(OrthographicCamera* camera, f32 width, f32 height, f32 zoomLevel)
{
  f32 aspectRatio = width / height;
  orthographic_camera_set_projection(camera, 
		 aspectRatio * zoomLevel, 
		 aspectRatio * zoomLevel, 
		-zoomLevel,
		 zoomLevel);
}
