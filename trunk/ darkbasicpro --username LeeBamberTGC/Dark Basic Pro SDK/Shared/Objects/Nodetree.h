
//
// Nodetree Functions Header
//

#ifndef _NODETREE_H_
#define _NODETREE_H_

//////////////////////////////////////////////////////////////////////////////////////
// NOTES /////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
/*
	using a nodetree will help us to partition space within a scene, we can then use
	the nodetree for collision and faster runtime drawing
*/

//////////////////////////////////////////////////////////////////////////////////////
// COMMON INCLUDES ///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
#include ".\..\DBOFormat\DBOFormat.h"

#include < vector >
using namespace std;

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
class cNodeTree
{
	private:
		//////////////////////////////////////////////////////////////////////////////////////
		// STRUCTURES ////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////
		struct sObjectList
		{
			// linked list for objects
			sObject*		pObjectRef;			// original object ref
			sMesh*			pTransformedMesh;	// for transformed meshdata
			sObjectList*	pNext;				// next node in list
	
			sObjectList ( );					// constructor
			~sObjectList ( );
		};

		struct sDataList
		{
			// object and vertex list
			sObject*		pObjectRef;			// which object the vertices belong to
			sMesh*			pMeshRef;			// which object the vertices belong to
			D3DXVECTOR3		vecVertex;			// vertex
		};
		//////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////
		// PRIVATE VARIABLES /////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////
		vector < sMesh* >	m_pMeshList;				// mesh list
		sDataList*			m_pVertexList;				// vertex list for all objects
		int					m_iVertexCount;				// vertex count
		cNodeTree*			m_pNodes [ 8 ];				// sub nodes within the tree
		sObjectList			m_ObjectList;				// list of objects attached to the node
		D3DXVECTOR3			m_vecMin;					// minimum bounding box
		D3DXVECTOR3			m_vecMax;					// maximum bounding box
		D3DXVECTOR3			m_vecCentre;				// central point
		D3DXVECTOR3			m_vecDimension;				// node dimensions
		sDataList*			m_pVertices;				// vertex list for individual node
		float				m_fWidth;					// width
		int					m_iTriangleCount;			// triangle count
		bool				m_bSubDivided;				// is the node sub divided
		vector < sMesh* >	m_pGlobalMeshList;
		sObject*			m_pGlobalObject;
		bool				m_bDebug;
		//////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////
		// PRIVATE FUNCTIONS /////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////
		bool		AddObjectToList		( sObject* pObject );
		bool		AddMeshToList		( sObject* pObject, sMesh* pMesh );
		bool		GetBoundingBox		( void );
		bool		GetCentrePoint       ( D3DXVECTOR3* pVecCentre, int* piVertexCount );
		bool		GetBounds            ( D3DXVECTOR3 vecCentre, float* pfWidth, float* pfHeight, float* pfDepth );
		int			GetVertexCount       ( void );
		bool		CreateVertexList     ( void );
		bool		CreateNode           ( sDataList* pData, int iVertexCount, D3DXVECTOR3 vecCentre, float fWidth );
		void		CreateNewNode        ( sDataList* pData, vector < bool > pList, int iVertexCount, D3DXVECTOR3 vecCentre, float fWidth, int iTriangleCount, int iID );
		void		AssignVerticesToNode ( sDataList* pData, int iVertexCount );
		void		DrawDebug            ( cNodeTree* pNode );
		void		RebuildMesh          ( cNodeTree* pNode );
		void		DrawNode             ( cNodeTree* pNode );
		void		TransformVertices    ( sObject* pObject, sMesh* pMesh );
		void		BuildGlobalMeshList  ( cNodeTree* pNode );
		void		BuildGlobalObject    ( void );
		void		DestroyNode          ( cNodeTree* pNode );
		void		ClearForNewNodeUpdate( void );
		D3DXVECTOR3 GetNewNodeCentre     ( D3DXVECTOR3 vecCentre, float fWidth, int iID );
		//////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////

	public:
		//////////////////////////////////////////////////////////////////////////////////////
		// CONSTRUCTOR / DESTRUCTOR //////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////
		 cNodeTree ( );
		~cNodeTree ( );
		//////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////
		// PUBLIC FUNCTIONS //////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////
		bool AddObject ( sObject* pObject );
		bool Update    ( void );
		bool Render    ( void );
		bool Destroy   ( void );

		void TurnDebugOn  ( void );
		void TurnDebugOff ( void );
		//////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////
};

#endif _NODETREE_H_