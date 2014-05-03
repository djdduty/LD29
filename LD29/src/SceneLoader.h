#ifndef SCENELOADER_H
#define SCENELOADER_H

#include <System/Environment.h>
#include <Resource/Mesh.h>
#include <Scene/Scene.h>
#include <string>
#include <map>

using namespace BearClaw;
namespace LD29 {
class PlaneEntry
{
public:
	f32 x;
	f32 y;
	f32 z;

	f32 u;
	f32 v;

	f32 n1;
	f32 n2;
	f32 n3;
	PlaneEntry() { x = 0; y = 0; z = 0; u = 0; v = 0; n1 = 0; n2 = 0; n3 = 0; };
};

class PlaneInstance
{
public:
	VertexList Vertices;
	string TexName;
	bool SkyBox;
	PlaneInstance() { Vertices = VertexList(); TexName = ""; SkyBox = false; }
};

typedef std::vector<PlaneInstance*> PlaneList;
typedef std::vector<string> LineList;

class SceneLoader
{
private:
	PlaneList m_Planes;
	LineList m_Lines;

	string m_Path;

	PlaneEntry ParseWord(string Word, PlaneEntry Entry);
protected:

public:
	SceneLoader(string path);
	Scene* Parse();
	
	LineList GetLines() { return m_Lines; }
	string GetPath() { return m_Path; }
};
}

#endif