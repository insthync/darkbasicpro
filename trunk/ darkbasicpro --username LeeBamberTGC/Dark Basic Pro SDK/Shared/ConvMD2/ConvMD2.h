//
// ConvMDL Functions Header
//

//////////////////////////////////////////////////////////////////////////////////
// INCLUDE COMMON FILES //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
#include <windows.h>

//////////////////////////////////////////////////////////////////////////////////////
// DBOFORMAT INCLUDE /////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
#include "..\\DBOFormat\\DBOBlock.h"
#include ".\..\DBOFormat\DBOFormat.h"
#include ".\..\DBOFormat\DBOFrame.h"
#include ".\..\DBOFormat\DBOMesh.h"
#include ".\..\DBOFormat\DBORawMesh.h"
#include ".\..\DBOFormat\DBOEffects.h"
#include ".\..\DBOFormat\DBOFile.h"
#include ".\..\core\globstruct.h"

//////////////////////////////////////////////////////////////////////////////////
// DEFINES ///////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

#ifdef DARKSDK_COMPILE
    #undef DARKSDK
	#undef DBPRO_GLOBAL
	#define DARKSDK static
	#define DBPRO_GLOBAL static
#else
	#define DARKSDK __declspec ( dllexport )
	#define DBPRO_GLOBAL 
	#define DARKSDK_DLL 
#endif

//#define DARKSDK __declspec ( dllexport )
//#define SAFE_DELETE( p )       { if ( p ) { delete ( p );       ( p ) = NULL; } }
//#define SAFE_RELEASE( p )      { if ( p ) { ( p )->Release ( ); ( p ) = NULL; } }
//#define SAFE_DELETE_ARRAY( p ) { if ( p ) { delete [ ] ( p );   ( p ) = NULL; } }

//////////////////////////////////////////////////////////////////////////////////////
// EXPORTED FUNCTIONS ////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

#ifndef DARKSDK_COMPILE
extern "C"
{
	DARKSDK	bool	Convert		( LPSTR pFilename, DWORD *pBlock, DWORD* pdwSize );
	DARKSDK void	Free		( LPSTR );
}
#else
	bool	ConvertMD2		( LPSTR pFilename, DWORD *pBlock, DWORD* pdwSize );
	void	FreeMD2			( LPSTR );
#endif

//////////////////////////////////////////////////////////////////////////////////
// MD2 STRUCTURES ////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
struct sMD2Header
{
   int iMagicNum;
   int iVersion;
   int iSkinWidthPx;
   int iSkinHeightPx;
   int iFrameSize;
   int iNumSkins;
   int iNumVertices;
   int iNumTexCoords;
   int iNumTriangles;
   int iNumGLCommands;
   int iNumFrames;
   int iOffsetSkins;
   int iOffsetTexCoords;
   int iOffsetTriangles;
   int iOffsetFrames;
   int iOffsetGlCommands;
   int iFileSize;
};

struct sMD2Vertex
{
	float fVert [ 3 ];
	UCHAR ucReserved;
};

struct sMD2Frame
{
	float		fScale [  3 ];
	float		fTrans [  3 ];
	char		szName [ 16 ];
	sMD2Vertex* pVerts;

	~sMD2Frame ( );
};

struct sMD2Triangle
{
	USHORT usVertexIndices  [ 3 ];
	USHORT usTextureIndices [ 3 ];
};

struct sMD2TexCoord
{
	float fTex [ 2 ];
};

struct sMD2Skin
{
	char caSkin [ 64 ];
};
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
