#include <cstdio>
#include <fstream>
#include <dirent.h>
#include <cstring>

/* Initrd file makeup

1 dword  0xdeadbeef
1 dword  number of files

for every file:

512 bytes  name
1 dword    offset
2 dword    file size

file data

*/

class cInitRdFile
{
public:
    char szName[512];
    unsigned int nOffset;
    unsigned long lSize;
} __attribute__ ((__packed__));

class cInitRd
{
public:
    unsigned int nMagic;
    unsigned int nFiles;

    cInitRdFile* pFiles;
} __attribute__ ((__packed__));

unsigned long getFileSize( const char* szPath )
{
    FILE* pFile = fopen( szPath, "rb" );

    if (pFile == NULL)
	return 0;

    long lSize = 0;

    fseek( pFile, 0, SEEK_END );
    lSize = ftell( pFile );
    rewind( pFile );

    fclose( pFile );

    return lSize;
}

char* getFullPath( const char* szBase, const char* szFile )
{
    char* szReturn = new char[ strlen(szBase) + strlen(szFile) + 1];

    strcpy( szReturn, szBase );
    strcpy( szReturn + strlen(szReturn), "/" );
    strcpy( szReturn + strlen(szReturn), szFile );

    return szReturn;
}
       
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
	    char* szNewPath = getFullPath( szPath, pDirent->d_name );
	    nFiles += getFilesInDirectory( (const char*) szNewPath );
	    delete[] szNewPath;
	}
    }

    return nFiles;
}

int populateFileNames( cInitRdFile* pFiles, const char* szPath )
{
    DIR* pDir = opendir( szPath );

    if (pDir == NULL)
	return 0;

    int nIter = 0;
    dirent* pDirent = NULL;

    while ((pDirent = readdir( pDir )) != NULL)
    {
	if (pDirent->d_type == DT_REG)
	{	    
	    char* szFullPath = getFullPath( szPath, pDirent->d_name );
	    
	    strncpy( pFiles[nIter].szName, szFullPath, 511 );
	    pFiles[nIter].lSize = getFileSize( szFullPath );
	    
	    delete[] szFullPath;

	    nIter++;
     	}
	else if (pDirent->d_type == DT_DIR && pDirent->d_name[0] != '.')
	{
	    char* szNewPath = getFullPath( szPath, pDirent->d_name );

	    nIter += populateFileNames( &pFiles[ nIter ], szNewPath );
	    
	    delete[] szNewPath;
	}
    }

    return nIter;
}

int getFileData( cInitRdFile* pFiles, char* pDataBase, char* &pData, const char* szPath )
{
    DIR* pDir = opendir( szPath );

    if (pDir == NULL)
	return 0;

    int nIter = 0;
    dirent* pDirent = NULL;

    while ((pDirent = readdir( pDir )) != NULL)
    {
	if (pDirent->d_type == DT_REG)
	{
	    char* szFullPath = getFullPath( szPath, pDirent->d_name );
	    char* pBuffer = new char[ pFiles[nIter].lSize ];

	    FILE* pFile = fopen( szFullPath, "rb" );
	    fread( pBuffer, pFiles[nIter].lSize, 1, pFile );
	    fclose( pFile );

	    strcpy( pData, pBuffer );
	    
	    pFiles[nIter].nOffset = pData - pDataBase;
	    pData += pFiles[nIter].lSize + 1;

	    nIter++;
	}
	else if (pDirent->d_type == DT_DIR && pDirent->d_name[0] != '.')
	{
	    char* szNewPath = getFullPath( szPath, pDirent->d_name );

	    nIter += getFileData( &pFiles[ nIter ], pDataBase, pData, szNewPath );

	    delete[] szNewPath;
	}
    }

    return nIter;
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

    unsigned long lTotalBytes = 0;

    for (int i=0;i < nFiles;++i)
    {
	printf("%s, %lu bytes\n", pInitRd->pFiles[i].szName, pInitRd->pFiles[i].lSize );

	lTotalBytes += pInitRd->pFiles[i].lSize + 1;
    }

    printf("Total %lu bytes to pack.\n", lTotalBytes);

    char* pData = new char[lTotalBytes];
    char* pDataTemp = pData;
    unsigned int nDataOffset = sizeof(cInitRd) + sizeof(cInitRdFile) * nFiles;
    nDataOffset &= 0xFFFFFFF0;
    nDataOffset += 0x10;

    printf( "Data starting point is %i\n", nDataOffset );

    getFileData( pInitRd->pFiles, pData - nDataOffset, pDataTemp, szPath );

    fwrite( pData, lTotalBytes, 1, stdout );

    delete[] pData;
    delete[] pInitRd->pFiles;
    delete pInitRd;

    return 0;
}
