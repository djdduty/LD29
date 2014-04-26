#ifndef INTERFACES_H
#define INTERFACES_H

#include <System/OS/PlatformIncludes.h>


using namespace std::tr1;                               //Shared pointers without c++11 for msvc support

namespace BearClaw {

//Typedefs for shared pointers
class SceneNode;
typedef shared_ptr<SceneNode> StrongNodePtr;
typedef weak_ptr<SceneNode> WeakNodePtr;

class Component;                                        //No need to include it
typedef shared_ptr<Component> StrongComponentPtr;
typedef weak_ptr<Component> WeakComponentPtr;

class RenderNode;
typedef shared_ptr<RenderNode> StrongRenderNodePtr;
typedef weak_ptr<RenderNode> WeakRenderNodePtr;
//

}
#endif
