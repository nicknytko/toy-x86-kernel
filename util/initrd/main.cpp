#include <cstdio>
#include <fstream>
#include <dirent.h>
#include <cstring>

/* Initrd file makeup

1 dword  0xdeadbeef
1 dword  number of files

for every file:

255 bytes  name
1 dword    offset

padding until dword-aligned

file data

*/

class cInitRdFile
{
public:
    char szName[255];
    unsigned int nOffset;
} __attribute__ ((__packed__));

class cInitRd
{
public:
    unsigned int nMagic;
    unsigned int nFiles;

    cInitRdFile* pFiles;
} __attribute__ ((__packed__));

int getFilesInDirectory( const char* szPath )
{
    DIR* pDir = opendir( szPath );
    
    if (pDir == NULL)
	return 0;

    int nFiles = 0;
    dirent* pDirent = NULL;

    while ((pDirent = readdir( pDir )) != NULL)
    {
	if (pDirent->d_type == DT_REG)
	    nFiles++;
	else if (pDirent->d_type == DT_DIR && pDirent->d_name[0] != '.')
	{
	    char* szNewPath = new char[ strlen(szPath) + strlen(pDirent->d_name) + 1 ];

	    strcpy( szNewPath, szPath );
	    strcpy( szNewPath + strlen(szNewPath), "/" );
	    strcpy( szNewPath + strlen(szNewPath), pDirent->d_name );

	    nFiles += getFilesInDirectory( (const char*) szNewPath );

	    delete[] szNewPath;
	}
    }

    return nFiles;
}

void populateFileNames( cInitRdFile* pFiles, const char* szPath )
{
    DIR* pDir = opendir( szPath );

    if (pDir == NULL)
	return;

    int nIter = 0;
    dirent* pDirent = NULL;

    while ((pDirent = readdir( pDir )) != NULL)
    {
	if (pDirent->d_type == DT_REG)
	    strncpy( pFiles[nIter].szName, pDirent->d_name, 254 );
     	else if (pDirent->d_type == DT_DIR && pDirent->d_name[0] != '.')
	{
	    char* szNewPath = new char[ strlen(szPath) + strlen(pDirent->d_name) + 1 ];

	    strcpy( szNewPath, szPath );
	    strcpy( szNewPath + strlen(szNewPath), "/" );
	    strcpy( szNewPath + strlen(szNewPath), pDirent->d_name );

	    populateFileNames( &pFiles[ nIter ], szNewPath );

	    delete[] szNewPath;
	}
    }
}

int main( )
{
    const char* szPath = "root";

    int nFiles = getFilesInDirectory( szPath );

    cInitRd* pInitRd = new cInitRd;
    pInitRd->nMagic = 0xDEADBEEF;
    pInitRd->nFiles = nFiles;
    pInitRd->pFiles = new cInitRdFile[ nFiles ];

    populateFileNames( pInitRd->pFiles, szPath );

    delete[] pInitRd->pFiles;
    delete pInitRd;

    return 0;
}
