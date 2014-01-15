/*#ifndef UNRDLL_H
#define UNRDLL_H


#define STRICT
#include <windows.h>
#include <stdio.h>
#include <ctype.h>
#include <locale.h>
#include <unrar.h>


class UnRDLL
{



    void ExtractArchive(char *ArcName,int Mode);
    void ListArchive(char *ArcName);
    void ShowComment(char *CmtBuf);
    void OutHelp(void);

    enum ERR_TYPE {ERR_OPEN, ERR_READ, ERR_PROCESS};
    void OutError(int Error,char *ArcName,int ErrType);

    void ShowArcInfo(unsigned int Flags,char *ArcName);
    void OutProcessFileError(int Error);
    int CALLBACK CallbackProc(UINT msg,LPARAM UserData,LPARAM P1,LPARAM P2);
};
#endif // UNRDLL_H*/
