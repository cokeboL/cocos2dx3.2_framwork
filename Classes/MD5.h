#ifndef MD5_H
#define MD5_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef unsigned char TYBYTE;
typedef unsigned int  TYUINT;

class CMD5
{
public:
	
	CMD5(void);

	char* GetFileMD5Values(const char* pFileName);
	char* GetStringMD5Values(const char* pStr);
private:
	void  Init(void);
	void  UpDate(const TYBYTE* input, TYUINT length);
	void  Transform(const TYBYTE* block);
	void  DeCode(const TYBYTE* input, TYUINT* output, TYUINT length);
	void  EnCode(const TYUINT* input, TYBYTE* output, TYUINT length);
	void  SetMD5Code(const TYBYTE* input, TYUINT length);

	const TYBYTE* Digest();

private:
	TYUINT	m_state[4];		// state (ABCD)
	TYUINT	m_count[2];		// number of bits, modulo 2^64 (low-order word first)
	TYBYTE	m_buffer[64];	// input buffer
	TYBYTE	m_digest[16];	// message digest
	char	m_MD5Val[33];	// ±£´æ MD5 Öµ
};

#endif	//	MD5_H