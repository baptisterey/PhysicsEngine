#include "RendererSystem.h"

RendererSystem::RendererSystem() : ISystem()
{
    context = NULL;
    window = nullptr;
    programID = NULL;
    mainCamera = new Camera(.8f,                                                  // View Angle
                            0.1f,                                                 // Near Plane
                            5000,                                                 // Far Plane
                            SCREEN_WIDTH,                                         // View Width
                            SCREEN_HEIGHT,                                        // View Height
                            Vector3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1750.f), // Position
                            Quaternion::fromEulerAngles(-.1f, -.2f, 0.f)          // Rotation
    );
}

RendererSystem::~RendererSystem() { close(); }

void RendererSystem::Update()
{
    glUseProgram(programID);
    glClear(GL_COLOR_BUFFER_BIT);

    for (IRendererComponent* component : components)
    {
        if (component->IsActive())
            component->Render(programID, mainCamera->getViewProjectionMatrix());
    }

    SDL_GL_SwapWindow(window);
}

void RendererSystem::AddRendererComponent(IRendererComponent* component)
{
    if (component != nullptr) { components.push_back(component); }
}

void RendererSystem::RemoveRendererComponent(IRendererComponent* component)
{
    components.erase(std::remove(components.begin(), components.end(), component),
                     components.end());
}

bool RendererSystem::InitRenderer(const char* title, int xpos, int ypos, int width, int height,
                                  bool fullscreen)
{
    // Window creation
    int flags = SDL_WINDOW_OPENGL;
    if (fullscreen) { flags |= SDL_WINDOW_FULLSCREEN; }

    window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if (!window)
    {
        printf("Failed to init SDL Window !");
        return false;
    }

    // OpenGL initialization
    context = SDL_GL_CreateContext(window);

    // Set OpenGL version.
    // SDL_GL_CONTEXT_CORE gives only the newer version, deprecated functions are disabled
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // 3.2 is part of the modern versions of OpenGL, but most video cards are able to run it
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    // Turn on double buffering with a 24bit Z buffer. Might need to change this to 16 or 32 for the
    // system.
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // This makes the buffer swap syncronized with the monitor's vertical refresh
    SDL_GL_SetSwapInterval(1);

    // Init GLEW
    // Apparently, this is needed only for Apple.
#ifndef __APPLE__
    glewExperimental = GL_TRUE;
    glewInit();
#endif

    // OpenGL other settings
    glEnable(GL_TEXTURE_2D);
    // glCullFace(GL_FRONT_AND_BACK);

    // Define the background
    glClearColor(.1f, .1f, .1f, 1.0);
    // Clear the content of the screen
    glClear(GL_COLOR_BUFFER_BIT);
    // Actually draw things on screen
    SDL_GL_SwapWindow(window);

    // Add VERTEX shader
    GLuint v_shader = glCreateShader(GL_VERTEX_SHADER);
    const char* v_str = Utils::ReadFile("Engine/Renderer/Shaders/VertexShader.glsl");
    glShaderSource(v_shader, 1, &v_str, 0);
    glCompileShader(v_shader);
    // Add FRAGMENT shader
    GLuint f_shader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* f_str = Utils::ReadFile("Engine/Renderer/Shaders/FragmentShader.glsl");
    glShaderSource(f_shader, 1, &f_str, 0);
    glCompileShader(f_shader);
    // Create a program (ID of process shaders)
    programID = glCreateProgram();
    glAttachShader(programID, v_shader);
    glAttachShader(programID, f_shader);
    glLinkProgram(programID);
    glDetachShader(programID, v_shader);
    glDetachShader(programID, f_shader);

    return true;
}

void RendererSystem::close()
{
    glDeleteProgram(programID);

    SDL_GL_DeleteContext(context);

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
}