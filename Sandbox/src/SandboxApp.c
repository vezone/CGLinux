//#include <Engine.h>
#include <EntryPoint.h>

#include "Sandbox.h"

void create_user_application()
{
    linux_set_current_stack_size(MB(500), MB(528));
    Layer layer;
    layer.OnAttach = sandbox_on_attach;
    layer.OnUpdate = sandbox_on_update;
    layer.OnEvent = sandbox_on_event;
    layer.OnDestoy = sandbox_on_destroy;
    application_push_layer(layer);
}
