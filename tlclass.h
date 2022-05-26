#ifndef __TLCLASS_H
#define __TLCLASS_H

typedef struct tagLOGPALETTE256 {
    WORD            palVersion;
    WORD            palNumEntries;
    PALETTEENTRY    palPalEntry[256];
    } LOGPALETTE256;

enum TTileFormat { tf1BPP, tfNES, tfGameBoy, tfVirtualBoy, tfSNES, tfSMS, tfGenesis, tfSNES3BPP, tfNGPC, tfRAW };

class TTLImage
	{
	private:
    unsigned __int64 BitPatterns[8][256];
    unsigned __int64 *ScanPtr;
    BYTE RowPixels[8];
    DWORD BitIndex;
    DWORD TempOffset;
	void *FileHandle;
	unsigned long NumBytes;
	public:
        TTLImage();        // constructor
        ~TTLImage();       // destructor
	void LoadFromFile(AnsiString fname);
	void SaveToFile(AnsiString fname);
    void Paint(void);
	Graphics::TBitmap *Bitmap;
    LOGPALETTE256 Palette;
	TTileFormat TileFormat;
	BYTE *FilePtr;
	AnsiString FileName;
	DWORD FileSize;
	int FileOffset;
    DWORD TileSize;
    DWORD TileOffset;
    DWORD Zoom;
    DWORD TileWidth;
    DWORD TileHeight;
    DWORD BytesPerLine;
    DWORD TilesX;
    DWORD TilesY;
	bool Modified;
	};

//-------------------------------------------------------

TTLImage::TTLImage()  // Constructor
{
// Set default tile display variables
TileWidth = 8;
TileHeight = 8;
TilesX = 16;
TilesY = 16;

// Create & initialize bitmap
Bitmap = new Graphics::TBitmap();
Bitmap->HandleType = bmDIB;
Bitmap->PixelFormat = pf8bit;
Bitmap->Width = TileWidth * TilesX;
Bitmap->Height = -((signed int)TileHeight * (signed int)TilesY);

BYTE DefaultPalette[] = { 0, 0, 0, 0,
                                   0, 85, 85, 0,
                                   0, 170, 170, 0,
                                   0, 255, 255, 0,
                                   64, 0, 0, 0,
                                   128, 0, 0, 0,
                                   192, 0, 0, 0,
                                   255, 0, 0, 0,
                                   0, 64, 0, 0,
                                   0, 128, 0, 0,
                                   0, 192, 0, 0,
                                   0, 255, 0, 0,
                                   0, 0, 64, 0,
                                   0, 0, 128, 0,
                                   0, 0, 192, 0,
                                   0, 0, 255, 0 };

memcpy(&Palette.palPalEntry[0], DefaultPalette, 16*4);

// Initialize palette
Palette.palVersion = 0x300;
Palette.palNumEntries = 256;
Bitmap->Palette = CreatePalette((LOGPALETTE *)&Palette);
SetPaletteEntries(Bitmap->Palette, 0, 256, (PALETTEENTRY *)&Palette.palPalEntry[0]);

// Create bit patterns
for (int z=0; z<8; z++)
    for (int y=0; y<256; y++)
        for (int x=0; x<8; x++)
            ((BYTE *)BitPatterns[z])[(y << 3) + x] = (BYTE)(((y >> (x ^ 7)) & 1) << z);
}

//-------------------------------------------------------

TTLImage::~TTLImage()     // Destructor
{
GlobalFree(FilePtr);
DeleteObject(Bitmap->Palette);
delete Bitmap;
}

//-------------------------------------------------------

void TTLImage::LoadFromFile(AnsiString fname)
{
FileName = fname;
// Open file for reading
FileHandle = CreateFile(FileName.c_str(),
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
// Get file size
FileSize = GetFileSize(FileHandle, NULL);
// Allocate memory for file
FilePtr = (BYTE *)GlobalAlloc(GMEM_FIXED,
					FileSize);
// Read file
ReadFile(FileHandle,
    	FilePtr,
    	FileSize,
    	&NumBytes,
    	NULL);
CloseHandle(FileHandle);


AnsiString FileExt = UpperCase(ExtractFileExt(FileName));
if (FileExt == ".NES")
    {
    TileFormat = tfNES;
    TileSize = 16;
    }
else if (FileExt == ".SMC")
    {
    TileFormat = tfSNES;
    TileSize = 32;
    }
else if (FileExt == ".GB")
    {
    TileFormat = tfGameBoy;
    TileSize = 16;
    }
else if (FileExt == ".VB")
    {
    TileFormat = tfVirtualBoy;
    TileSize = 16;
    }
else if (FileExt == ".NGP")
    {
    TileFormat = tfNGPC;
    TileSize = 16;
    }
else if (FileExt == ".SMS")
    {
    TileFormat = tfSMS;
    TileSize = 32;
    }
else if (FileExt == ".SMD")
    {
    TileFormat = tfGenesis;
    TileSize = 32;
    }
else
    {
    TileFormat = tf1BPP;
    TileSize = 8;
    }

FileOffset = 0;
Zoom = 2;
Modified = false;
}

//-------------------------------------------------------

void TTLImage::SaveToFile(AnsiString fname)
{
FileHandle = CreateFile(fname.c_str(),
			GENERIC_WRITE,
			NULL,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
WriteFile(FileHandle,
	FilePtr,
	FileSize,
	&NumBytes,
	NULL);
CloseHandle(FileHandle);

Modified = false;
}

//-------------------------------------------------------

void TTLImage::Paint(void)
{
TempOffset = FileOffset;
for (DWORD z=0; z<(TileHeight*TilesY); z+=TileHeight)
    {   // do Y tiles vertically
    for (DWORD y=0; y<TileHeight; y++)
	    {   // do one scanline
	    ScanPtr = (unsigned __int64 *)Bitmap->ScanLine[z+y];
	    for (DWORD x=0; x<TilesX; x++)
	        {   // do X tiles horizontally
            switch(TileFormat)
                {
                case tf1BPP:
                BitIndex = FilePtr[TempOffset + (x << 3) + y];
                ScanPtr[x] = BitPatterns[0][BitIndex];
                break;

                case tfNES:
                TileOffset = TempOffset + (x << 4) + y;
                ScanPtr[x] = BitPatterns[0][FilePtr[TileOffset]]
                            | BitPatterns[1][FilePtr[TileOffset+8]];
                break;

                case tfGameBoy:
                TileOffset = TempOffset + (x << 4) + (y << 1);
                ScanPtr[x] = BitPatterns[0][FilePtr[TileOffset]]
                            | BitPatterns[1][FilePtr[TileOffset+1]];
                break;

                case tfVirtualBoy:
                TileOffset = TempOffset + (x << 4) + (y << 1);
                RowPixels[0] = (BYTE)(FilePtr[TileOffset] & 0x03);
                RowPixels[1] = (BYTE)((FilePtr[TileOffset] & 0x0C) >> 2);
                RowPixels[2] = (BYTE)((FilePtr[TileOffset] & 0x30) >> 4);
                RowPixels[3] = (BYTE)(FilePtr[TileOffset++] >> 6);
                RowPixels[4] = (BYTE)(FilePtr[TileOffset] & 0x03);
                RowPixels[5] = (BYTE)((FilePtr[TileOffset] & 0x0C) >> 2);
                RowPixels[6] = (BYTE)((FilePtr[TileOffset] & 0x30) >> 4);
                RowPixels[7] = (BYTE)(FilePtr[TileOffset] >> 6);
                ScanPtr[x] = *(unsigned __int64 *)&RowPixels;
                break;

                case tfNGPC:
                TileOffset = TempOffset + (x << 4) + (y << 1);
                RowPixels[4] = (BYTE)(FilePtr[TileOffset] >> 6);
                RowPixels[5] = (BYTE)((FilePtr[TileOffset] & 0x30) >> 4);
                RowPixels[6] = (BYTE)((FilePtr[TileOffset] & 0x0C) >> 2);
                RowPixels[7] = (BYTE)(FilePtr[TileOffset++] & 0x03);
                RowPixels[0] = (BYTE)(FilePtr[TileOffset] >> 6);
                RowPixels[1] = (BYTE)((FilePtr[TileOffset] & 0x30) >> 4);
                RowPixels[2] = (BYTE)((FilePtr[TileOffset] & 0x0C) >> 2);
                RowPixels[3] = (BYTE)(FilePtr[TileOffset] & 0x03);
                ScanPtr[x] = *(unsigned __int64 *)&RowPixels;
                break;

                case tfSNES:
                TileOffset = TempOffset + (x << 5) + (y << 1);
                ScanPtr[x] = BitPatterns[0][FilePtr[TileOffset]]
                            | BitPatterns[1][FilePtr[TileOffset+1]]
                            | BitPatterns[2][FilePtr[TileOffset+16]]
                            | BitPatterns[3][FilePtr[TileOffset+17]];
                break;

                case tfSNES3BPP:
                TileOffset = TempOffset + (x << 5) + (y << 1);
                ScanPtr[x] = BitPatterns[0][FilePtr[TileOffset]]
                            | BitPatterns[1][FilePtr[TileOffset+1]]
                            | BitPatterns[2][FilePtr[TileOffset+16]];
                break;

                case tfSMS:
                TileOffset = TempOffset + (x << 5) + (y << 2);
                ScanPtr[x] = BitPatterns[0][FilePtr[TileOffset]]
                            | BitPatterns[1][FilePtr[TileOffset+1]]
                            | BitPatterns[2][FilePtr[TileOffset+2]]
                            | BitPatterns[3][FilePtr[TileOffset+3]];
                break;

                case tfGenesis:
                TileOffset = TempOffset + (x << 5) + (y << 2);
                RowPixels[0] = (BYTE)(FilePtr[TileOffset] >> 4);
                RowPixels[1] = (BYTE)(FilePtr[TileOffset++] & 0x0F);
                RowPixels[2] = (BYTE)(FilePtr[TileOffset] >> 4);
                RowPixels[3] = (BYTE)(FilePtr[TileOffset++] & 0x0F);
                RowPixels[4] = (BYTE)(FilePtr[TileOffset] >> 4);
                RowPixels[5] = (BYTE)(FilePtr[TileOffset++] & 0x0F);
                RowPixels[6] = (BYTE)(FilePtr[TileOffset] >> 4);
                RowPixels[7] = (BYTE)(FilePtr[TileOffset++] & 0x0F);
                ScanPtr[x] = *(unsigned __int64 *)&RowPixels;
                break;

                case tfRAW:
                BYTE *PixPtr = &FilePtr[TempOffset + (x << 3) + (y << 7)];
                ScanPtr[x] = *(unsigned __int64 *)PixPtr;
                }
            }
        }
    TempOffset += TileSize * TilesX;
    }
}

#endif
