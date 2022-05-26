#ifndef __BITMAP256_H__
#define __BITMAP256_H__

enum TTileFormat { tf1BPP = 0, tfNES, tfGameBoy, tfVirtualBoy, tfNGPC, tfSNES3BPP, tfSNES, tfSMS, tfGenesis, tfGBA, tfRAW8, tfSNES8BPP };

typedef struct {
    BITMAPINFOHEADER bmiHeader;
    RGBQUAD          bmiColors[256];
    } BMINFO256;

typedef struct {
    TTileFormat tlfmt;
    int tlsize;
    int tlskip;
    int tlbpp;
    int left;
    int top;
    int cols;
    int rows;
    } DRAWINFO;

typedef struct {
    int bmTileWidth;
    int bmTileHeight;
    int bmTileCols;
    int bmTileRows;

    void *bmptr;
    void *bmHandle;
    int bmsize;

    DRAWINFO decinfo;
    DRAWINFO encinfo;
    BMINFO256 bminfo;
    } Bitmap256;

#endif
