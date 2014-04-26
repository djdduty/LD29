#include <Gui/FontFile.h>
#include <fstream>

namespace BearClaw {
FontFile::FontFile(string FontName)
{
    m_Path = "Data/Font/"+FontName+".txt";
    m_ImagePath = "Data/Font/"+FontName+".png";
}

void FontFile::Parse()
{
    ifstream Stream(m_Path);
    for(string line; getline(Stream, line);)
    {
        m_Lines.push_back(line);
    }

    for(int i = 0; i < m_Lines.size(); i++)
    {
        string Line = m_Lines[i];
        FontEntry Entry;
        string Word;
        for(int n = 0; n < Line.size(); n++)
        {
            Byte c = Line[n];
            if(c != ' ')
            {
                Word += c;
            } else {
                Entry = ParseWord(Word, Entry);
                Word = "";
            }
        }
        if(Entry.Code != 0);
        m_Entries.push_back(Entry);
    }

    /*for(int i = 0; i < m_Entries.size(); i++)
    {
        BC_LOG("%c pos:%f,%f size:%f,%f\n", m_Entries[i].Code, m_Entries[i].x, m_Entries[i].y, m_Entries[i].width, m_Entries[i].height);
    }*/
}

FontEntry FontFile::ParseWord(string Word, FontEntry Entry)
{
    FontEntry Ret = Entry;
    string Property;
    string Value;
    bool OnValue = false;
    for(int i = 0; i < Word.size(); i++)
    {
        if(Word[i] != '=')
        {
            if(!OnValue)
                Property += Word[i];
            else
                Value += Word[i];
        } else {
            OnValue = true;
        }
    }

    if(Property == "id")
        Ret.Code = atof(Value.c_str());
    if(Property == "x")
        Ret.x = atof(Value.c_str());
    if(Property == "y")
        Ret.y = atof(Value.c_str());
    if(Property == "width")
        Ret.width = atof(Value.c_str());
    if(Property == "height")
        Ret.height = atof(Value.c_str());
    if(Property == "xoffset")
        Ret.xoffset = atof(Value.c_str());
    if(Property == "yoffset")
        Ret.yoffset = atof(Value.c_str());

    return Ret;
}

FontEntry FontFile::GetEntry(Byte code)
{
    for(int i = 0; i < m_Entries.size(); i++)
    {
        if(m_Entries[i].Code == code)
            return m_Entries[i];
    }
    FontEntry* Zero = new FontEntry();
    return *Zero;
    BC_LOG("Could not find the character %c in the font", code);
}
}