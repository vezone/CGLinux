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