#ifndef FONT_FILE_H
#define FONT_FILE_H

#include <System/Environment.h>
#include <string>
#include <map>

namespace BearClaw {
class FontEntry
{
public:
    f32 x;
    f32 y;
    f32 width;
    f32 height;
    f32 xoffset;
    f32 yoffset;
    Byte Code;

    FontEntry(){x = 0, y = 0, width = 0, height = 0, Code = 0;}
};

typedef std::vector<FontEntry> EntryList;
//typedef std::vector<Byte> Line;
typedef std::vector<string> LineList;

class FontFile
{
private:
    EntryList m_Entries;

    string m_Path;
    string m_ImagePath;

    LineList m_Lines;
    FontEntry ParseWord(string word, FontEntry Entry);

public:
    FontFile(string FontName);
    
    void Parse();
    FontEntry GetEntry(Byte code);
    
    string GetImagePath() {return m_ImagePath;}
    EntryList GetEntries() {return m_Entries;}
    LineList GetLines() {return m_Lines;}
    string GetPath() {return m_Path;}
};
}

#endif