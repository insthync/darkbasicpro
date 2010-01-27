
#ifndef _CBSPTREE_H_
#define _CBSPTREE_H_

//////////////////////////////////////////////////////////////////////////////////////
// NOTES /////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
/*
	BSP functions
*/

//////////////////////////////////////////////////////////////////////////////////////
// COMMON INCLUDES ///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
#include ".\..\DBOFormat\DBOFormat.h"

//////////////////////////////////////////////////////////////////////////////////////
// DEFINES ///////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
#define SAFE_DELETE( p )       { if ( p ) { delete ( p );       ( p ) = NULL; } }
#define SAFE_RELEASE( p )      { if ( p ) { ( p )->Release ( ); ( p ) = NULL; } }
#define SAFE_DELETE_ARRAY( p ) { if ( p ) { delete [ ] ( p );   ( p ) = NULL; } }
#define SAFE_MEMORY( p )       { if ( p == NULL ) return false; }
#define MAX_STRING				256

//////////////////////////////////////////////////////////////////////////////////////
// CLASS DEFINITION //////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

class cBSPTree
{
	private:
		struct sVertex
		{
			float x, y, z;
			float nx, ny, nz;
			float tu, tv;
		};

		struct sPolygon
		{
			sVertex*	pVertices;
			WORD*		pIndices;
			WORD		dwVertexCount;
			WORD		dwIndexCount;
			D3DXVECTOR3	vecNormal;
			int			iTextureIndex;
			BYTE		bUsedAsSplitter;
			sPolygon*	pNext;
		};

	public:
		cBSPTree  ( );
		~cBSPTree ( );

		void Build ( int iCurrentNode, sPolygon* pPolyList );
		void Setup ( sMesh* pMesh );
};


#endif _CBSPTREE_H_
