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
	PlaneInstance* Plane = new PlaneInstance();

	for (i32 i = 0; i < m_Lines.size(); i++) {
		string Line = m_Lines[i];
		PlaneEntry Entry;
		string Word;
		if (Line == "plane") {
			PlaneEntries = std::vector<PlaneEntry>();
			Plane = new PlaneInstance();
			Word = "";
			//BC_LOG("new plane on line %d\n", i);
		} else if (Line == "end") {
			for (i32 x = 0; x < PlaneEntries.size(); x++) {
				PlaneEntry tmp = PlaneEntries[x];
				Plane->Vertices.push_back(Vertex(Vec3(tmp.x, tmp.y, tmp.z), Vec3(tmp.n1, tmp.n2, tmp.n3), Vec2(tmp.u, tmp.v)));
			}
			m_Planes.push_back(Plane);
			Word = "";
		} else if (Line == "sky") {
			Plane->SkyBox = true;
			Word = "";
		} else if (Line == "texture") {
			string Texture = m_Lines[i + 1];
			Plane->TexName = Texture;
			i++;
		} else {
			for (i32 n = 0; n < Line.size(); n++) {
				Byte c = Line[n];
				if (c != ' ') {
					Word += c;
				}
				else {
					if (Word != "") Entry = ParseWord(Word, Entry);
					Word = "";
				}
			}
			PlaneEntries.push_back(Entry);
		}
	}

	ShaderFlags* FlagsDefault = new ShaderFlags();
	FlagsDefault->DefaultShader = false;
	FlagsDefault->HasDiffuseColor = true;
	FlagsDefault->LightingShader = true;
	HLShaderWrapper* Shader = new HLShaderWrapper("Data/Shaders/SkyBox.vert", "Data/Shaders/SkyBox.frag", FlagsDefault);

	Shader->Enable();
	Shader->SetProgramOutput(0, "FragColor");
	Shader->SetVertexAttrib(ShaderProgram::TEXTURE_COORD_ATTRIB, "Texcoord");
	Shader->SetVertexAttrib(ShaderProgram::VERTEX_COORD_ATTRIB, "Position");
	Shader->SetVertexAttrib(ShaderProgram::TANGENT_ATTRIB, "Tangent");
	Shader->SetVertexAttrib(ShaderProgram::NORMAL_ATTRIB, "Normal");

	Shader->LinkProgram();

	Environ->GetShaderManager()->AddShader(Shader);

	for (i32 y = 0; y < m_Planes.size(); y++) {
		PlaneInstance* p = m_Planes[y];
		SceneNode* n = new SceneNode("planeNode" + y);
		s->AddChild(n);
		PlaneComponent* pl = new PlaneComponent("planeComponent" + y, p->Vertices);
		pl->SetTexture(p->TexName);
		//std::cout << "Texture " << p->TexName << std::endl;
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
	for (i32 i = 0; i < Word.size(); i++) {
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