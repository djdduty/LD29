#include <System/Environment.h>
#include <Renderer/Renderer.h>

namespace BearClaw {
Environment::Environment() :    m_FileSystem(new BcFileSystem()),
                                m_InputManager(new InputManager())
{
    RendererInitializer RenInit = RendererInitializer();
    m_Renderer = new Renderer(RenInit);
    m_ElapsedTime = 0.0;
}

Environment::~Environment()
{
    delete m_FileSystem;
}

void Environment::Init(WindowInitializer WinInit)
{
    m_Log = fopen("DebugOutput.txt", "w");

    BC_LOG("Initializing Environment...");

    m_Window = new BcWindow(WinInit);
    m_Window->Create();
    m_WindowWidth = m_Window->GetWidth();
    m_WindowHeight = m_Window->GetHeight();

    m_ShaderManager = new ShaderManager();
    m_TextureManager = new TextureManager();

    m_Renderer->Init();
    m_InputManager->Init(m_Window);
    m_ShaderManager->Init();

    BC_LOG("Done.\n");
    BC_LOG("Window size: %u x %u\n", WinInit.Width, WinInit.Height);
    BC_LOG("Desired GL Context version: %u.%u\n\n", WinInit.MajorVersion, WinInit.MinorVersion);
}

void Environment::Update(f64 DeltaTime)
{
    m_DeltaTime = DeltaTime;
    m_ElapsedTime += DeltaTime;
    if(m_WindowWidth != m_Window->GetWidth() || m_WindowHeight != m_Window->GetHeight())
    {
        m_WindowWidth = m_Window->GetWidth();
        m_WindowHeight = m_Window->GetHeight();
        glViewport(0,0,m_WindowWidth, m_WindowHeight);
    }
    m_Window->PollEvents();
    m_InputManager->PollEvents();

    m_Renderer->Render();
}

uid Environment::GetUuid(BC_OBJECT_TYPE Type)
{
    uid Random = rand() % 65535;
    if(CheckUuid(Random, Type))
    {
        if(Type == BC_SCENE_NODE)
            UsedNodeIds.push_back(Random);

        if(Type == BC_COMPONENT)
            UsedComponentIds.push_back(Random);

        return Random;
    }

    return GetUuid(Type);
}

bool Environment::CheckUuid(uid Candidate, BC_OBJECT_TYPE Type)
{
    if(Type == BC_SCENE_NODE)
    {
        for(i32 i = 0; i < UsedNodeIds.size(); i++)
        {
            if(UsedNodeIds[i] == Candidate)
                return false;
        }
    }
    if(Type == BC_COMPONENT)
    {
        for(i32 i = 0; i < UsedComponentIds.size(); i++)
        {
            if(UsedComponentIds[i] == Candidate)
                return false;
        }
    }

    return true;
}

i32 Environment::Log(const char* Text, ...)
{
    va_list List;
    va_start(List, Text);
    int Size = strlen(Text) + 512;
    char *Formatted = AllocStr(Size);

    vsnprintf(Formatted, Size, Text, List);
    va_end(List);

    i32 Ret = fprintf(m_Log, "%s", Formatted);
    printf("%s", Formatted);

    return Ret;
}

//TODO: Environment::LoadConfigFile(const BcString &ConfFile)
}
