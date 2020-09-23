/******************************************************************
	CqOctree.CPP

  Performing Color Quantization using Octree algorithm

  The 2 functions for global use is
	  HPALETTE CreateOctreePalette (HBITMAP hImage, UINT nMaxColors, UINT nColorBits)
	  HPALETTE CreateOctreePalette (LPSTR lpDIB, UINT nMaxColors, UINT nColorBits)
  For using convenience, define it in DIBAPI.H
******************************************************************/

#include "stdafx.h"
#include "dibapi.h"

// structure use internally
// store the necessary info of a node in octree
typedef struct _NODE 
{
    BOOL bIsLeaf;               // TRUE if node has no children
    UINT nPixelCount;           // Number of pixels represented by this leaf
    UINT nRedSum;               // Sum of red components
    UINT nGreenSum;             // Sum of green components
    UINT nBlueSum;              // Sum of blue components
    struct _NODE* pChild[8];    // Pointers to child nodes
    struct _NODE* pNext;        // Pointer to next reducible node
} NODE;

// Function prototypes
	//Global use, define it in dibapi.h
	//HPALETTE CreateOctreePalette (HDIB hDIB, UINT nMaxColors, UINT nColorBits)
	//HPALETTE CreateOctreePalette (LPSTR lpDIB, UINT nMaxColors, UINT nColorBits)
//Local use only
HPALETTE BuildOctreePalette(HANDLE hImage, UINT nMaxColors, UINT nColorBits);
void AddColor (NODE**, BYTE, BYTE, BYTE, UINT, UINT, UINT*, NODE**);
NODE* CreateNode (UINT, UINT, UINT*, NODE**);
void ReduceTree (UINT, UINT*, NODE**);
void DeleteTree (NODE**);
void GetPaletteColors (NODE*, PALETTEENTRY*, UINT*);
int GetRightShiftCount (DWORD);
int GetLeftShiftCount (DWORD);

// Function body

/************************************************************************* 
 * 
 * CreateOctreePalette() 
 * 
 * Parameters: 
 * 
 * HDIB hDIB        - Handle to source DIB 
 * UINT nMaxColors  - destination color number
 * UINT nColorBits  - destination color bits
 * 
 * Return Value: 
 * 
 * HPALETTE         - Handle to the result palette
 * 
 * Description: 
 * 
 * This function use Octree color quantization algorithm to get
 * optimal m kinds of color to represent total n kinds of color 
 * in a DIB, and use the m kinds of color to build a palette.
 * With the palette, we can display the DIB on reasonable accuracy.
 * 
 ************************************************************************/ 
HPALETTE CreateOctreePalette(HDIB hDIB, UINT nMaxColors, UINT nColorBits)
{
	HANDLE hImage;

	hImage = DIBToDIBSection(hDIB);
	if (! hImage)
		return NULL;
	return BuildOctreePalette(hImage, nMaxColors, nColorBits);
}

/************************************************************************* 
 * 
 * CreateOctreePalette() 
 * 
 * Parameters: 
 * 
 * LPBYTE lpDIB     - Pointer to DIB data buffer
 * UINT nMaxColors  - destination color number
 * UINT nColorBits  - destination color bits
 * 
 * Return Value: 
 * 
 * HPALETTE         - Handle to the result palette
 * 
 * Description: 
 * 
 * This function use Octree color quantization algorithm to get
 * optimal m kinds of color to represent total n kinds of color 
 * in a DIB, and use the m kinds of color to build a palette.
 * With the palette, we can display the DIB on reasonable accuracy.
 * 
 ************************************************************************/ 
HPALETTE CreateOctreePalette(LPBYTE lpDIB, UINT nMaxColors, UINT nColorBits)
{
	HANDLE hImage;

	hImage = DIBToDIBSection(lpDIB);
	if (! hImage)
		return NULL;
	return BuildOctreePalette(hImage, nMaxColors, nColorBits);
}

// local function to build optimal palette from DIBSection
HPALETTE BuildOctreePalette(HANDLE hImage, UINT nMaxColors, UINT nColorBits)
{
    DIBSECTION ds;
    int i, j, nPad;
    BYTE* pbBits;
    WORD* pwBits;
    DWORD* pdwBits;
    DWORD rmask, gmask, bmask;
    int rright, gright, bright;
    int rleft, gleft, bleft;
    BYTE r, g, b;
    WORD wColor;
    DWORD dwColor, dwSize;
    LOGPALETTE* plp;
    HPALETTE hPalette;
    NODE* pTree;
    UINT nLeafCount, nIndex;
    NODE* pReducibleNodes[9];
    HDC hdc;    
	BYTE* pBuffer;    
	BITMAPINFO bmi;

    // Initialize octree variables
    pTree = NULL;
    nLeafCount = 0;
    if (nColorBits > 8) // Just in case
        return NULL;
    for (i=0; i<=(int) nColorBits; i++)
        pReducibleNodes[i] = NULL;

    // Scan the DIB and build the octree
    GetObject (hImage, sizeof (ds), &ds);
    nPad = ds.dsBm.bmWidthBytes - (((ds.dsBmih.biWidth *
        ds.dsBmih.biBitCount) + 7) / 8);

    switch (ds.dsBmih.biBitCount) {

    case 1: // 1-bit DIB    
	case 4: // 4-bit DIB    
	case 8: // 8-bit DIB
        //        
		// The strategy here is to use ::GetDIBits to convert the
        // image into a 24-bit DIB one scan line at a time. A pleasant
        // side effect of using ::GetDIBits in this manner is that RLE-
        // encoded 4-bit and 8-bit DIBs will be uncompressed.        //
        hdc = GetDC (NULL);        
		pBuffer = new BYTE[ds.dsBmih.biWidth * 3];
        ZeroMemory (&bmi, sizeof (bmi));
        bmi.bmiHeader.biSize = sizeof (BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = ds.dsBmih.biWidth;
        bmi.bmiHeader.biHeight = ds.dsBmih.biHeight;
        bmi.bmiHeader.biPlanes = 1;        
		bmi.bmiHeader.biBitCount = 24;
        bmi.bmiHeader.biCompression = BI_RGB;
        for (i=0; i<ds.dsBmih.biHeight; i++) 
		{
            GetDIBits (hdc, (HBITMAP) hImage, i, 1, pBuffer, &bmi,
                DIB_RGB_COLORS);            
			pbBits = pBuffer;
            for (j=0; j<ds.dsBmih.biWidth; j++) 
			{                
				b = *pbBits++;
                g = *pbBits++;                
				r = *pbBits++;
                AddColor (&pTree, r, g, b, nColorBits, 0, &nLeafCount,
                          pReducibleNodes);
                while (nLeafCount > nMaxColors)
                    ReduceTree (nColorBits, &nLeafCount, pReducibleNodes);            
			}        
		}
        delete pBuffer;        
		ReleaseDC (NULL, hdc);        
		break;    
	
	case 16: // One case for 16-bit DIBs
        if (ds.dsBmih.biCompression == BI_BITFIELDS) {
            rmask = ds.dsBitfields[0];
            gmask = ds.dsBitfields[1];
            bmask = ds.dsBitfields[2];
        }
        else {
            rmask = 0x7C00;
            gmask = 0x03E0;
            bmask = 0x001F;
        }

        rright = GetRightShiftCount (rmask);
        gright = GetRightShiftCount (gmask);
        bright = GetRightShiftCount (bmask);

        rleft = GetLeftShiftCount (rmask);
        gleft = GetLeftShiftCount (gmask);
        bleft = GetLeftShiftCount (bmask);

        pwBits = (WORD*) ds.dsBm.bmBits;
        for (i=0; i<ds.dsBmih.biHeight; i++) {
            for (j=0; j<ds.dsBmih.biWidth; j++) {
                wColor = *pwBits++;
                b = (BYTE) (((wColor & (WORD) bmask) >> bright) << bleft);
                g = (BYTE) (((wColor & (WORD) gmask) >> gright) << gleft);
                r = (BYTE) (((wColor & (WORD) rmask) >> rright) << rleft);
                AddColor (&pTree, r, g, b, nColorBits, 0, &nLeafCount,
                          pReducibleNodes);
                while (nLeafCount > nMaxColors)
                    ReduceTree (nColorBits, &nLeafCount, pReducibleNodes);
            }
            pwBits = (WORD*) (((BYTE*) pwBits) + nPad);
        }
        break;

    case 24: // Another for 24-bit DIBs
        pbBits = (BYTE*) ds.dsBm.bmBits;
        for (i=0; i<ds.dsBmih.biHeight; i++) {
            for (j=0; j<ds.dsBmih.biWidth; j++) {
                b = *pbBits++;
                g = *pbBits++;
                r = *pbBits++;
                AddColor (&pTree, r, g, b, nColorBits, 0, &nLeafCount,
                          pReducibleNodes);
                while (nLeafCount > nMaxColors)
                    ReduceTree (nColorBits, &nLeafCount, pReducibleNodes);
            }
            pbBits += nPad;
        }
        break;

    case 32: // And another for 32-bit DIBs
        if (ds.dsBmih.biCompression == BI_BITFIELDS) {
            rmask = ds.dsBitfields[0];
            gmask = ds.dsBitfields[1];
            bmask = ds.dsBitfields[2];
        }
        else {
            rmask = 0x00FF0000;
            gmask = 0x0000FF00;
            bmask = 0x000000FF;
        }

        rright = GetRightShiftCount (rmask);
        gright = GetRightShiftCount (gmask);
        bright = GetRightShiftCount (bmask);

        pdwBits = (DWORD*) ds.dsBm.bmBits;
        for (i=0; i<ds.dsBmih.biHeight; i++) {
            for (j=0; j<ds.dsBmih.biWidth; j++) {
                dwColor = *pdwBits++;
                b = (BYTE) ((dwColor & bmask) >> bright);
                g = (BYTE) ((dwColor & gmask) >> gright);
                r = (BYTE) ((dwColor & rmask) >> rright);
                AddColor (&pTree, r, g, b, nColorBits, 0, &nLeafCount,
                          pReducibleNodes);
                while (nLeafCount > nMaxColors)
                    ReduceTree (nColorBits, &nLeafCount, pReducibleNodes);
            }
            pdwBits = (DWORD*) (((BYTE*) pdwBits) + nPad);
        }
        break;

    default: // DIB must be 16, 24, or 32-bit!
        return NULL;
    }

    if (nLeafCount > nMaxColors) { // Sanity check
        DeleteTree (&pTree);
        return NULL;
    }

    // Create a logical palette from the colors in the octree
    dwSize = sizeof (LOGPALETTE) + ((nLeafCount - 1) * sizeof (PALETTEENTRY));
    if ((plp = (LOGPALETTE*) HeapAlloc (GetProcessHeap (), 0,
        dwSize)) == NULL) {
        DeleteTree (&pTree);
        return NULL;
    }

    plp->palVersion = 0x300;
    plp->palNumEntries = (WORD) nLeafCount;
    nIndex = 0;
    GetPaletteColors (pTree, plp->palPalEntry, &nIndex);
    hPalette = CreatePalette (plp);

    HeapFree (GetProcessHeap (), 0, plp);
    DeleteTree (&pTree);
    return hPalette;
}

// local function to add a color to octree
void AddColor (NODE** ppNode, BYTE r, BYTE g, BYTE b, UINT nColorBits,
    UINT nLevel, UINT* pLeafCount, NODE** pReducibleNodes)
{
    int nIndex, shift;
    static BYTE mask[8] = { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 };

    // If the node doesn't exist, create it
    if (*ppNode == NULL)
        *ppNode = CreateNode (nLevel, nColorBits, pLeafCount,
                              pReducibleNodes);

    // Update color information if it's a leaf node
    if ((*ppNode)->bIsLeaf) {
        (*ppNode)->nPixelCount++;
        (*ppNode)->nRedSum += r;
        (*ppNode)->nGreenSum += g;
        (*ppNode)->nBlueSum += b;
    }

    // Recurse a level deeper if the node is not a leaf
    else {
        shift = 7 - nLevel;
        nIndex = (((r & mask[nLevel]) >> shift) << 2) |
            (((g & mask[nLevel]) >> shift) << 1) |
            ((b & mask[nLevel]) >> shift);
        AddColor (&((*ppNode)->pChild[nIndex]), r, g, b, nColorBits,
                  nLevel + 1, pLeafCount, pReducibleNodes);
    }
}

// local function to create a new node in octree
NODE* CreateNode (UINT nLevel, UINT nColorBits, UINT* pLeafCount,
                  NODE** pReducibleNodes)
{
    NODE* pNode;

    if ((pNode = (NODE*) HeapAlloc (GetProcessHeap (), HEAP_ZERO_MEMORY,
        sizeof (NODE))) == NULL)
        return NULL;

    pNode->bIsLeaf = (nLevel == nColorBits) ? TRUE : FALSE;
    if (pNode->bIsLeaf)
        (*pLeafCount)++;
    else { // Add the node to the reducible list for this level
        pNode->pNext = pReducibleNodes[nLevel];
        pReducibleNodes[nLevel] = pNode;
    }
    return pNode;
}

// local function to reduce the nodes of octree
void ReduceTree (UINT nColorBits, UINT* pLeafCount, NODE** pReducibleNodes)
{
    int i;
    NODE* pNode;
    UINT nRedSum, nGreenSum, nBlueSum, nChildren;

    // Find the deepest level containing at least one reducible node
    for (i=nColorBits - 1; (i>0) && (pReducibleNodes[i] == NULL); i--);

    // Reduce the node most recently added to the list at level i
    pNode = pReducibleNodes[i];
    pReducibleNodes[i] = pNode->pNext;

    nRedSum = nGreenSum = nBlueSum = nChildren = 0;
    for (i=0; i<8; i++) {
        if (pNode->pChild[i] != NULL) {
            nRedSum += pNode->pChild[i]->nRedSum;
            nGreenSum += pNode->pChild[i]->nGreenSum;
            nBlueSum += pNode->pChild[i]->nBlueSum;
            pNode->nPixelCount += pNode->pChild[i]->nPixelCount;
            HeapFree (GetProcessHeap (), 0, pNode->pChild[i]);
            pNode->pChild[i] = NULL;
            nChildren++;
        }
    }

    pNode->bIsLeaf = TRUE;
    pNode->nRedSum = nRedSum;
    pNode->nGreenSum = nGreenSum;
    pNode->nBlueSum = nBlueSum;
    *pLeafCount -= (nChildren - 1);
}

// local function to delete a node of octree
void DeleteTree (NODE** ppNode)
{
    int i;

    for (i=0; i<8; i++) {
        if ((*ppNode)->pChild[i] != NULL)
            DeleteTree (&((*ppNode)->pChild[i]));
    }
    HeapFree (GetProcessHeap (), 0, *ppNode);
    *ppNode = NULL;
}

// local function to get color entry from a palette
void GetPaletteColors (NODE* pTree, PALETTEENTRY* pPalEntries, UINT* pIndex)
{
    int i;

    if (pTree->bIsLeaf) {
        pPalEntries[*pIndex].peRed =
            (BYTE) ((pTree->nRedSum) / (pTree->nPixelCount));
        pPalEntries[*pIndex].peGreen =
            (BYTE) ((pTree->nGreenSum) / (pTree->nPixelCount));
        pPalEntries[*pIndex].peBlue =
            (BYTE) ((pTree->nBlueSum) / (pTree->nPixelCount));
        (*pIndex)++;
    }
    else {
        for (i=0; i<8; i++) {
            if (pTree->pChild[i] != NULL)
                GetPaletteColors (pTree->pChild[i], pPalEntries, pIndex);
        }
    }
}

// local function to get pixel count
int GetRightShiftCount (DWORD dwVal)
{
    int i;

    for (i=0; i<sizeof (DWORD) * 8; i++) {
        if (dwVal & 1)
            return i;
        dwVal >>= 1;
    }
    return -1;
}

// local function to get pixel count
int GetLeftShiftCount (DWORD dwVal)
{
    int nCount, i;

    nCount = 0;
    for (i=0; i<sizeof (DWORD) * 8; i++) {
        if (dwVal & 1)
            nCount++;
        dwVal >>= 1;
    }
    return (8 - nCount);
}
