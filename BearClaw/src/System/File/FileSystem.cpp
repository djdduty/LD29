#include <System/File/FileSystem.h>
#include <System/Environment.h>

namespace BearClaw {

/*
 * BcFile
 */

BcFile::BcFile(const BcString &FileName)
{
    m_Fp        = 0;
    m_FileName  = FileName;
}

BcFile::~BcFile()
{
    FileSys->CloseFile(this);
    m_Fp = 0;
}

BcString BcFile::GetFileName()  const
{
    return m_FileName;
}

size_t  BcFile::GetFileSize()   const
{
    fpos_t fpos = GetPosition();
    fseek(m_Fp, 0L, SEEK_END);
    size_t Size = ftell(m_Fp);
    fsetpos(m_Fp, &fpos);
    return Size;
}

bool BcFile::EndOfFile()        const
{
    return feof(m_Fp);
}

void BcFile::SetPosition(size_t Position)
{
    fseek(m_Fp, Position, SEEK_SET);
}

fpos_t BcFile::GetPosition()      const
{
    fpos_t Pos;
    fgetpos(m_Fp, &Pos);
    return Pos;
}

void BcFile::Write(const char* Text, ...)
{
    va_list Args;
    va_start(Args,Text);
    if(vfprintf(m_Fp,Text,Args) < 0)
    {
        BC_ERROR("Attempt to write string (%s) failed. (%s)\n",Text,m_FileName.Ptr());
    }
    va_end(Args);
}

void BcFile::Write(const BcString &Text,...)
{
    va_list Args;
    va_start(Args,Text);
    if(vfprintf(m_Fp,Text.Ptr(),Args) < 0)
    {
        BC_ERROR("Attempt to write string (%s) failed. (%s)\n",Text.Ptr(),m_FileName.Ptr());
    }
    va_end(Args);
}
void BcFile::Write(char *Text)
{
    if(fprintf(m_Fp,"%s",Text) < 0)
    {
        BC_ERROR("Attempt to write string (%s) failed. (%s)\n",Text,m_FileName.Ptr());
    }
}
void BcFile::Write(void *Data,size_t Size)
{
    if(fwrite(Data,Size,1,m_Fp) != 1)
    {
        BC_ERROR("Attempt to write %lu bytes failed. (%s)\n",Size,m_FileName.Ptr());
    }
}

void *BcFile::Read(size_t Size,i32 Blocks) const
{
    Byte *Data = new Byte[Size * Blocks];
    memset(Data,0,Size);
    if(fread(Data,Size,Blocks,m_Fp) != Blocks)
    {
        delete [] Data;
        BC_ERROR("Attempt to read %lu bytes failed. (%s)\n",Size,m_FileName.Ptr());
        return 0;
    }
    return Data;
}
BcString BcFile::ReadLine() const
{
    BcString Str;
    char c = fgetc(m_Fp);
    while(c != '\n' && c != '\0' && c != '\r' && !EndOfFile())
    {
        Str += c;
        c = fgetc(m_Fp);
    }
    return Str;
}
BcString BcFile::ReadAll()  const
{
    size_t Sz = GetFileSize();
    char *C = new char[Sz + 2];
    if(fread(C,Sz,1,m_Fp) != 1)
    {
        BC_ERROR("Attempt to read %u bytes failed. (%s)\n",Sz,m_FileName.Ptr());
    }
    C[Sz + 1] = 0;
    BcString Str = C;

    delete [] C;
    return Str;
}

/*
 * BcFileSystem
 */

BcFileSystem::BcFileSystem()
{}

BcFileSystem::~BcFileSystem()
{
    for(i16 i = 0; i < m_Files.Size(); i++)
        delete m_Files[i];
}

BcFile* BcFileSystem::OpenFile(const BcString &FileName, OPEN_MODE Mode)
{
    BcFile* File = new BcFile(FileName);
    switch(Mode)
    {
        case OM_READ_TEXT:
        {
            File->m_Fp = fopen(FileName.Ptr(),"r");
        }
        case OM_READ_BINARY:
        {
            File->m_Fp = fopen(FileName.Ptr(),"rb");
        }
        case OM_WRITE_TEXT:
        {
            File->m_Fp = fopen(FileName.Ptr(),"w");
        }
        case OM_WRITE_BINARY:
        {
            File->m_Fp = fopen(FileName.Ptr(),"wb");
        }
        case OM_APPEND_TEXT:
        {
            File->m_Fp = fopen(FileName.Ptr(),"a");
        }
        case OM_APPEND_BINARY:
        {
            File->m_Fp = fopen(FileName.Ptr(),"ab");
        }
        case OM_READ_WRITE_TEXT:
        {
            File->m_Fp = fopen(FileName.Ptr(),"w+");
        }
        case OM_READ_WRITE_BINARY:
        {
            File->m_Fp = fopen(FileName.Ptr(),"wb+");
        }
        default:
        {
            BC_ERROR("Invalid open mode for file (Must be in the enum BearClaw::BcFileSystem::OPEN_MODE). (%s)\n", FileName.Ptr());
            break;
        }
    }
    if(!File->m_Fp)
    {
        BC_ERROR("Attempt to open file failed. (%s)\n", FileName.Ptr());
        delete File;
        File = 0;
    }
    return File;
}

void BcFileSystem::CloseFile(BcFile *File)
{
    if(!File->m_Fp)
    {
        BC_ERROR("The file cannot be closed because it isn't open. (%s)\n", File->GetFileName().Ptr());
        return;
    }
    fclose(File->m_Fp);
    m_Files.Remove(File);
}

i16 BcFileSystem::GetOpenFileCount()    const
{
    return m_Files.Size();
}

bool BcFileSystem::FileExists(const BcString &FileName)     const
{
    struct stat Stat;
    return (stat(FileName.Ptr(), &Stat)==0);
}

bool BcFileSystem::DirectoryExists(const BcString &Directory) const
{
    struct stat Stat;
    return (stat(Directory.Ptr(), &Stat)==0);
}

BcString BcFileSystem::GetFileExtension(const BcString &FileName) const
{
    BcVector <Index>Indices;
    if(FileName.FindAllOf(".",Indices) == 0); BC_ERROR("Filename (%s) has no extension.\n",FileName.Ptr());
    BcString Ext = FileName.Substr(Indices[Indices.Size() - 1] + 1,FileName.Length());
    return Ext;
}
}
