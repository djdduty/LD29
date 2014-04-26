#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <System/OS/PlatformIncludes.h>
#include <Resource/TextureManager.h>
#include <Resource/ShaderManager.h>
#include <System/File/FileSystem.h>
#include <System/InputManager.h>
#include <Utils/EngineMacros.h>
#include <System/OS/Window.h>

namespace BearClaw {
class Logger;
class Renderer;

enum BC_OBJECT_TYPE
{
    BC_SCENE_NODE,
    BC_COMPONENT
};

class Environment
{
private:
    Environment();

protected:
    TextureManager*         m_TextureManager;
    ShaderManager*          m_ShaderManager;
    InputManager*           m_InputManager;
    BcFileSystem*           m_FileSystem;
    BcWindow*               m_Window;
    Renderer*               m_Renderer;
    FILE*                   m_Log;

    f64                     m_DeltaTime;
    f64                     m_ElapsedTime;
    i32                     m_WindowWidth,
                            m_WindowHeight;

    std::vector<uid>        UsedComponentIds;
    std::vector<uid>        UsedNodeIds;

public:
    ~Environment();

    static Environment* GetEnvironment()
    {
        static Environment* Env = new Environment();
        return Env;
    }

    virtual void Init(WindowInitializer WinInit);
    virtual void Update(f64 DeltaTime);
    uid GetUuid(BC_OBJECT_TYPE Type);
    bool CheckUuid(uid Candidate, BC_OBJECT_TYPE Type);
    void InitGui();

    i32  Log(const char* Text, ...);
    
    TextureManager*     GetTextureManager() const {return m_TextureManager; }
    ShaderManager*      GetShaderManager()  const {return m_ShaderManager;  }
    BcFileSystem*       GetFileSystem()     const {return m_FileSystem;     }
    InputManager*       GetInputManager()   const {return m_InputManager;   }
    BcWindow*           GetWindow()         const {return m_Window;         }
    Renderer*           GetRenderer()       const {return m_Renderer;       }

    i32                 GetWindowWidth()    {return m_WindowWidth;          }
    i32                 GetWindowHeight()   {return m_WindowHeight;         }
    f64                 GetDeltaTime()      {return m_DeltaTime;            }
    f64                 GetElapsedTime()    {return m_ElapsedTime;          }
};
}

#endif
