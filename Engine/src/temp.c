#include "temp.h"
#include <stdlib.h>
#include "Utils/Logger.h"

#include <stdio.h>
#include <assert.h>
#include <glad/glad.h>
#include "cimgui.h"
#include "GUI/cimgui_impl_glfw.h"
#include "GUI/cimgui_impl_opengl3.h"


void bies_allocator_init()
{
    MemoryPool = malloc(KB(1) * sizeof(i8));
    Offset = 0;
    AllocationSize = 0;
    AllocationsCount = 0;
}

void* bies_allocate(i32 size)
{
    i32 padding = sizeof(AllocationHeader);
    AllocationHeader* header = (AllocationHeader*) ((i64)MemoryPool + Offset);
    header->IsFree = 0;
    header->BytesAllocated = size + padding;
    header->Allocated = (void*) ((i64)header + OffsetOf(AllocationHeader, Allocated));

    if (AllocationsCount > 0)
    {
        header->Prev = LastHeader;
        header->Prev->Next = header;
    }
    else
    {
        header->Prev = NULL;
        FirstHeader = header;
    }

    header->Next = NULL;
    LastHeader = header;

    Offset += size;
    AllocationSize += size;
    ++AllocationsCount;

    return header->Allocated;
}

void bies_allocator_show()
{
    AllocationHeader* ptr = NULL;
    for (ptr = FirstHeader; ptr->Next != NULL; ptr = ptr->Next)
    {
        if ((i64)ptr->Next == 0x100)
        {
            GERROR("next: %lld\n", (i64)ptr->Next);
            return;
        }

        printf("IsFree: %d, BytesAllocated: %d, PrevAddr: %lld, NextAddr: %lld, AllocatedAddr: %lld\n", ptr->IsFree, ptr->BytesAllocated, (i64) ptr->Prev, (i64) ptr->Next, (i64) ptr->Allocated);
    }
}

void bies_allocator_test()
{
    printf("Sizeof AllocationHeader: %d Sizeof(Size_t): %d, OffsetOf(Allocated): %d\n", sizeof(AllocationHeader), sizeof(size_t), OffsetOf(AllocationHeader, Allocated));

#if 1

    bies_allocator_init();

    Anon* object1 = bies_allocate(sizeof(Anon));
    Anon* object2 = bies_allocate(sizeof(Anon));

#else

    Anon* object1 = malloc(sizeof(Anon));
    Anon* object2 = malloc(sizeof(Anon));

#endif

    object1->Flag = 1;
    object1->BigFlag |= (1 << 8);
    CSTRING_FILL(object1->Name, "Name1");

    object2->Flag = 2;
    object2->BigFlag |= (1 << 7);
    CSTRING_FILL(object2->Name, "Name2");

    printf("object1 .Flag = %d .BigFlag = %d .Name = %s\n", object1->Flag, object1->BigFlag, object1->Name);
    printf("object2 .Flag = %d .BigFlag = %d .Name = %s\n", object2->Flag, object2->BigFlag, object2->Name);

    Anon* object3 = (Anon*) ((i8*)object2 - sizeof(Anon));
    printf("object3 .Flag = %d .BigFlag = %d .Name = %s\n", object3->Flag, object3->BigFlag, object3->Name);

    bies_allocator_show();

    GLOG("All is work!\n");
}

void imgui_test(void)
{
    assert(igDebugCheckVersionAndDataLayout(igGetVersion(), sizeof(ImGuiIO), sizeof(ImGuiStyle), sizeof(ImVec2), sizeof(ImVec4), sizeof(ImDrawVert), sizeof(ImDrawIdx)));
    printf("CreateContext() - v%s\n", igGetVersion());

    if (!glfwInit())
    {
        GERROR("GLFW is not initialized!\n");
        return;
    }

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", NULL, NULL);
    if (window == NULL)
    {
        GERROR("Can't create window!\n");
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    i32 openGLLoadStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (openGLLoadStatus == 0)
    {
        GERROR("Failed to init GLAD\n");
        return;
    }
    GLOG(MAGNETA("OpenGL version %s\n"), glGetString(GL_VERSION));

    igCreateContext(NULL);
    ImGuiIO *io = igGetIO();

    ImGuiStyle guiStyle;
    igStyleColorsDark(&guiStyle);

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    bool show_another_window = false, show_demo_window;
    f32 clearColor[4] = { 0.113f, 0.316f, 0.642f, 1.0f };
    ImVec2 buttonSize = {50.0f, 50.0f};
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        igNewFrame();

        {
            static int counter = 0;
            static bool isWindowOpen;
            igBegin("Hello, world!", &isWindowOpen, NULL);
            igText("This is some useful text.");
            igColorEdit3("clear color", clearColor, ImGuiColorEditFlags_InputRGB);

            igText("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / igGetIO()->Framerate, igGetIO()->Framerate);
            igEnd();
        }

        // Rendering
        igRender();
        i32 display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(igGetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    glfwDestroyWindow(window);
    glfwTerminate();
    igDestroyContext(NULL);
}

