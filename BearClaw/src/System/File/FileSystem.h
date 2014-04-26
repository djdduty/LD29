#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <Utils/EngineMacros.h>
#include <Utils/Singleton.h>
#include <Utils/BcString.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdarg.h>
#include <iostream>

namespace BearClaw {
class BcFile;

class BcFileSystem
{
public:
    enum OPEN_MODE
    {
        OM_READ_BINARY,
        OM_READ_TEXT,
        OM_WRITE_BINARY,
        OM_WRITE_TEXT,
        OM_READ_WRITE_BINARY,
        OM_READ_WRITE_TEXT,
        OM_APPEND_BINARY,
        OM_APPEND_TEXT
    };

private:

protected:
    BcVector<BcFile*>   m_Files;
public:
    BcFileSystem();
    ~BcFileSystem();

    BcFile*     OpenFile(const BcString &FileName, OPEN_MODE Mode);
    void        CloseFile(BcFile* File);

    i16         GetOpenFileCount()                          const;

    bool        FileExists(const BcString &FileName)        const;
    bool        DirectoryExists(const BcString &Directory)  const;

    BcString    GetFileExtension(const BcString &FileName)  const;
};

class BcFile
{
protected:
    BcFile(const BcString &FileName);

    friend class    BcFileSystem;
    BcString        m_FileName;

public:
    FILE*           m_Fp;

    ~BcFile();
    BcString    GetFileName()   const;
    size_t      GetFileSize()   const;
    bool        EndOfFile()     const;
    fpos_t      GetPosition()   const;
    void        SetPosition(size_t Position);
    //
    void Write(char* Text);
    void Write(const char *Text, ...);
    void Write(void* Data, size_t Size);
    void Write(const BcString &Text, ...);
    //
    BcString ReadLine() const;
    BcString ReadAll()  const;
    void* Read(size_t Size, i32 Blocks) const;
    //
    template <typename Type>
    u16 Write(Type &Data)
    {
        if(fwrite(&Data, sizeof(Data), 1, m_Fp) != 1)
        {
            std::cout << "Attempt to write " << sizeof(Data) << " bytes failed.\n";     //TODO: Swap to use engine logging
            abort();
        }
        return sizeof(Data);
    }
    //
    template<typename Type>
    u16 Read(Type &Data)
    {
        if(fread(&Data, sizeof(Data), 1, m_Fp) != 1)
        {
            std::cout << "Attempt to read " << sizeof(Data) << " bytes failes.\n";      //TODO: Swap to use engine logging
            abort();
        }
        return sizeof(Data);
    }
};

} //end namespace
#endif
