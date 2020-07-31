#include "Application.h"
#include "Graphics/Renderer2D/Renderer2D.h"

Application App;
i32 LayersCount;

void
application_push_layer(Layer layer)
{
    array_push(App.Layers, layer);
    layer.OnAttach(App.Window);
}

void application_init(u32 width, u32 height, const char* name)
{
    i32 isWindowCreated;
    i32 openGLLoadStatus;

    App.IsMinimized = 0;
    App.IsRunning = 1;

    linux_set_current_stack_size(MB(500), MB(528));
    event_init_table(App.EventTypeToString, 32);

    isWindowCreated = window_create(&App.Window, width, height, "Demo", application_on_event);
    if (isWindowCreated == -1)
    {
        GERROR("Can't create window!\n");
        return;
    }

    //OpenGL
    openGLLoadStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (openGLLoadStatus == 0)
    {
        GERROR("Failed to init GLAD\n");
        return;
    }
    GLOG(MAGNETA("OpenGL version %s\n"), glGetString(GL_VERSION));
}

void application_start()
{
    f32 tempTime;
    f32 timeStep;
    f32 lastFrameTime;

    LayersCount = array_len(App.Layers);

    while (!window_should_close(&App.Window))
    {
        tempTime = (f32) glfwGetTime();
        timeStep = tempTime - lastFrameTime;
        lastFrameTime = tempTime;

        if (!App.IsMinimized)
        {
            for (i32 l = 0; l < LayersCount; l++)
            {
                App.Layers[l].OnUpdate(timeStep);
            }

            window_on_update(&App.Window);
        }

#if 0
        printf("timestep: %f ms\r", 1000 * timeStep);
#endif

    }

    for (i32 l = 0; l < LayersCount; l++)
    {
        App.Layers[l].OnDestoy();
    }

    //gui_terminate();
    window_terminate();
}

void
application_on_event(Event* event)
{
    Layer layer;

    if (event->Category == WindowCategory)
    {
        if (event->Type == WindowResized)
        {
            WindowResizedEvent* wevent = (WindowResizedEvent*) event;
            renderer_set_viewport(wevent->Width, wevent->Height);
        }
    }

    for (i32 l = 0; l < LayersCount; l++)
    {
        layer = App.Layers[l];
        layer.OnEvent(event);
    }
}
