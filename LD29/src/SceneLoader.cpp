#include <SceneLoader.h>
#include <Components/PlaneComponent.h>
#include <fstream>

using namespace BearClaw;
namespace LD29 {
SceneLoader::SceneLoader(string path) {
	m_Path = path;
}

Scene* SceneLoader::Parse()
{
	Scene* s = new Scene("World");

	ifstream Stream(m_Path);
	for (string line; getline(Stream, line);) {
		m_Lines.push_back(line);
	}

	std::vector<PlaneEntry> PlaneEntries = std::vector<PlaneEntry>();

	for (int i = 0; i < m_Lines.size(); i++) {
		string Line = m_Lines[i];
		PlaneEntry Entry;
		string Word;
		if (Line == "plane") {
			PlaneEntries = std::vector<PlaneEntry>();
			Word = "";
			//BC_LOG("new plane on line %d\n", i);
		} else if (Line == "end") {
			PlaneInstance Plane;
			for (int x = 0; x < PlaneEntries.size(); x++) {
				PlaneEntry tmp = PlaneEntries[x];
				Plane.Vertices.push_back(Vertex(Vec3(tmp.x, tmp.y, tmp.z), Vec3(tmp.n1, tmp.n2, tmp.n3), Vec2(tmp.u, tmp.v)));
				//BC_LOG("x:%f y:%f z:%f\n\n", tmp.x, tmp.y, tmp.z);
			}
			Word = "";
			//BC_LOG("end of plane on line %d\n", i);
			PlaneEntries = std::vector<PlaneEntry>();
			m_Planes.push_back(Plane);
		} else {
			for (int n = 0; n < Line.size(); n++) {
				Byte c = Line[n];
				if (c != ' ') {
					Word += c;
					//std::cout << c;
				} else {
					Entry = ParseWord(Word, Entry);
					Word = "";
				}
			}
			PlaneEntries.push_back(Entry);
		}
	}

	for (int y = 0; y < m_Planes.size(); y++) {
		PlaneInstance p = m_Planes[y];
		SceneNode* n = new SceneNode("planeNode" + y);
		s->AddChild(n);
		PlaneComponent* pl = new PlaneComponent("planeComponent" + y, p.Vertices);
		n->AddComponent(pl);
		//BC_LOG("Adding plane to scene\n");
	}

	return s;
}

PlaneEntry SceneLoader::ParseWord(string Word, PlaneEntry Entry)
{
	PlaneEntry Ret = Entry;
	string Property;
	string Value;
	bool OnValue = false;
	for (int i = 0; i < Word.size(); i++) {
		if (Word[i] != '=') {
			if (!OnValue) Property += Word[i];
			else Value += Word[i];
		} else {
			OnValue = true;
		}
	}
	//std::cout << Property << " = " << Value << std::endl;

	if (Property == "x") Ret.x		= atof(Value.c_str());
	if (Property == "y") Ret.y		= atof(Value.c_str());
	if (Property == "z") Ret.z		= atof(Value.c_str());

	if (Property == "u") Ret.u		= atof(Value.c_str());
	if (Property == "v") Ret.v		= atof(Value.c_str());

	if (Property == "n1") Ret.n1	= atof(Value.c_str());
	if (Property == "n2") Ret.n2	= atof(Value.c_str());
	if (Property == "n3") Ret.n3	= atof(Value.c_str());

	return Ret;
}
}