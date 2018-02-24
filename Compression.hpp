/**
* Compression
*
* Description : Performs all compression tasks. This is only a placeholder for
*               an actual compression algorithm. Available choices for this class
*               are an LZ4 based compression (HARD) or a Huffman Encoding Tree
*              (NOT AS HARD BUT STILL QUITE TIME CONSUMING).
**/
#include <cstdlib>

// HACK: NOT AN ACTUAL ABSTRACT CLASS. DO NOT USE!!!!
class Compression {
  virtual ~Compression() = 0;

  virtual void* compressData (const void* tData, const size_t tLen) = 0;
  virtual void* decompressData (const void* tData, const size_t tLen) = 0;
};

// TODO: Implement actual compression algorithm!!
