#include "Sandbox.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <cglm/cglm.h>

#include "stdlib.h"

#include "Utils/String.h"
#include "Utils/Logger.h"
#include "Utils/Array.h"
#include "Graphics/Window.h"
#include "Graphics/KeyCodes.h"
#include "Graphics/Buffer.h"
#include "Graphics/Renderer2D/Renderer2D.h"
#include "Graphics/Renderer2D/OrthographicCamera.h"

#include "Platform/Linux/Linux.h"

// GLOBAL
#define HD 1
#define FULLHD 0
#define DRAW_BASE_SCENE 1
#define KENNY_BASE_PACK "CGLinux/resource/assets/textures/full_packs/kenney_assets_forest/foliagePack_"
#define PACK_TEXTURES_COUNT 50

#define STOP() static i32 numberfordebugpurposes; scanf("%d", &numberfordebugpurposes)

Window g_Window;
char WindowTitle[32];
#if HD == 1
f32 Width = 1280.0f;
f32 Height = 720.0f;
#elif FULLHD == 1
f32 Width = 1920.0f;
f32 Height = 1080.0f;
#else
f32 Width = 960.0f;
f32 Height = 640.0f;
#endif

Renderer2DStatistics Statistics;
OrthographicCamera Camera;
Shader batchedTextureShader;

//Textures
const char* shader_batched_texture_path = "CGLinux/resource/batched_texture_shader.glsl";
const char* texture_anime_chibi = "CGLinux/resource/anime_chibi.png";
const char* texture_cherno_hazel_logo = "CGLinux/resource/hazel.png";
const char* texture_hotline_miami = "CGLinux/resource/assets/textures/other/hotline_miami.png";

Texture2D hazelLogoTexture;
Texture2D chibiTexture;
Texture2D hotlineMiamiTexture;
Texture2D packTextures[PACK_TEXTURES_COUNT];

vec4 RedColor    = { 0.8f, 0.1f, 0.1f, 1.0f };
vec4 YellowColor = { 1.0f, 1.0f, 0.0f, 1.0f };
vec4 BlueColor   = { 0.1f, 0.1f, 0.8f, 1.0f };
vec4 GreenColor   = { 0.2f, 0.7f, 0.2f, 0.3f };

void
sandbox_on_attach(Window window)
{
    f32 aspectRatio;
    f32 zoomLevel;
    i32 offset;
    char path[512];

    g_Window = window;
    aspectRatio = Width / Height;
    zoomLevel = 5.0f;
    Camera = orthographic_camera_create(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
    Camera.AspectRatio = aspectRatio;
    Camera.ZoomLevel = zoomLevel;
    Camera.Speed = 5.0f;
    Camera.Position[1] += 2.0f;

    window_set_vsync(0);
    GFORMAT(WindowTitle, "Demo %f", Camera.ZoomLevel);
    window_set_title(&g_Window, WindowTitle);

    batchedTextureShader = graphics_shader_compile(
        graphics_shader_load(shader_batched_texture_path));

    hazelLogoTexture = graphics_texture2d_create(texture_cherno_hazel_logo);
    chibiTexture = graphics_texture2d_create(texture_anime_chibi);
    hotlineMiamiTexture = graphics_texture2d_create(texture_hotline_miami);

    offset = vstring_length(KENNY_BASE_PACK);
    for (i32 i = 0; i < PACK_TEXTURES_COUNT; i++)
    {
        if (i < 9)
        {
            sprintf(path, "%s%s%d%s", KENNY_BASE_PACK, "00", i+1, ".png");
        }
        else if (i >= 9 && i < 100)
        {
            sprintf(path, "%s%s%d%s", KENNY_BASE_PACK, "0", i+1, ".png");
        }

        packTextures[i] = graphics_texture2d_create(path);
    }

    renderer_batch_init(&Statistics, &batchedTextureShader, &Camera);
}

void sandbox_on_update(f32 timestep)
{
    renderer_reset_statistics(&Statistics);

    orthographic_camera_on_update(&Camera, &g_Window, timestep);

    renderer_clear((vec4) { 0.2f, 0.245f, 0.356f, 1.0f });

    renderer_submit_rectangle((vec3) {-1.5f, -0.5f, 0.0f}, (vec2) {1.0f, 1.0f}, &hazelLogoTexture);
    renderer_submit_rectangle((vec3) {-1.5f, -2.5f, 0.0f}, (vec2) {2.0f, 2.0f}, &chibiTexture);
    renderer_submit_rectangle((vec3) {-3.0f, -2.5f, 0.0f}, (vec2) {1.5f, 1.5f}, &chibiTexture);
    renderer_submit_rectangle((vec3) {3.0f, -2.5f, 0.0f}, (vec2) {1.5f, 1.5f}, &hotlineMiamiTexture);
    renderer_submit_rectangle((vec3) {3.0f, -2.5f, 0.0f}, (vec2) {1.5f, 1.5f}, &hotlineMiamiTexture);

#if 1
    {
        i32 i = 0;
        f32 size_of_each_quad = 0.19;
        f32 distance_between_quads = size_of_each_quad + 0.01;
        f32 x_begin_pos = -6.0;
        f32 x_end_pos = PACK_TEXTURES_COUNT * distance_between_quads + x_begin_pos; 
        for (f64 x = x_begin_pos; x < x_end_pos; x+=distance_between_quads)
        {
            if (i >= PACK_TEXTURES_COUNT)
            {
                i = 0;
            }

            renderer_submit_rectangle((vec3) {x, 6.0f, 0.0f}, (vec2){size_of_each_quad, size_of_each_quad}, &packTextures[i]);
            i++;
        }
    }
#endif

    renderer_submit_colored_rectangle((vec3) {1.0f, 1.0f, 0.0f}, (vec2) { 1.5f, 1.5f }, YellowColor);
    renderer_submit_colored_rectangle((vec3) {-2.0f, 1.0f, 0.0f}, (vec2) { 1.0f, 1.0f }, BlueColor);

    renderer_submit_colored_rotated_rectangle((vec3) {-6.0f, 1.0f, 0.0f}, (vec2) { 1.5f, 1.5f }, RedColor, 45);
    renderer_submit_colored_rotated_rectangle((vec3) {-7.0f, 1.0f, 0.0f}, (vec2) { 1.f, 1.f }, GreenColor, 45);
    renderer_submit_colored_rotated_rectangle((vec3) {-8.0f, 1.0f, 0.0f}, (vec2) { .5f, .5f }, YellowColor, 45);

    {
        static f32 angle = 0.0f;
        angle += timestep * 115.0f;
        angle = FMOD(angle, 360);
        renderer_submit_rotated_rectangle((vec3) { -6.0f, 2.0f, 0.0f }, (vec2) { 0.5f, 0.5f }, angle, &chibiTexture);
    }

#if 1
    {
        static i32 counter = 0;
        f64 tileSize = 0.3f;
        f64 tileShift = tileSize + tileSize * 0.1f;
        f64 startX = 5.5;
        f64 startY = 5.5;
        f64 endX = 19.5;
        f64 endY = 19.5;
        for (f64 y = startY; y < endY; y += tileShift)
        {
            for (f64 x = startX; x < endX; x += tileShift)
            {
                ++counter;
                renderer_submit_rectangle((vec3) {x, y, 0.0f}, (vec2) { tileSize, tileSize }, &chibiTexture);
            }
        }

        PRINT_ONESF(GLOG, "Counter: %10.5d\n", counter);
    }
#endif

    renderer_flush();

#if 1
    PRINT("DrawCalls: %d, RectanglesCount: %d\r", Statistics.DrawCalls, Statistics.RectanglesCount); 
#endif
}

void
sandbox_on_event(Event* event)
{
    if (event->IsHandled == 1)
    {
        return;
    }

    orthographic_camera_on_event(&Camera, event);

    if (event->Category == KeyCategory)
    {
        KeyPressedEvent* keyEvent = (KeyPressedEvent*) event;
        if (window_is_key_pressed(&g_Window, KEY_ESCAPE))
        {
            window_set_should_close(&g_Window, 1);
        }

        event->IsHandled = 1;
    }
    else if (event->Category == MouseCategory)
    {
        if (event->Type == MouseButtonPressed)
        {
            MouseButtonEvent* mevent = (MouseButtonEvent*) event;
            if (mevent->MouseCode == MOUSE_BUTTON_1)
            {
                if (Camera.ZoomLevel > 1.0f)
                {
                    Camera.ZoomLevel -= 1.0f;
                }
                else if (Camera.ZoomLevel == 1.0f)
                {
                    Camera.ZoomLevel = 0.1f;
                }
            }
            else if (mevent->MouseCode == MOUSE_BUTTON_2)
            {
                if (Camera.ZoomLevel != 0.1f)
                {
                    Camera.ZoomLevel += 1.0f;
                }
                else
                {
                    Camera.ZoomLevel = 1.0f;
                }
            }
        }

        GFORMAT(WindowTitle, "Demo %f", Camera.ZoomLevel);
        window_set_title(&g_Window, WindowTitle);

        event->IsHandled = 1;
    }
}

