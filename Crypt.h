#pragma once

class CCrypt
{
public:
	CCrypt(void);
	~CCrypt(void);
	void GetFileNamesFromDialog(vector<CString>& vsFiles,CWnd* ownerCWnd);
	// in - filename and path out - encrupted file on the disk.........
	bool CEncryptFiles(vector<CString>& vsFiles,CString& CSKey,CProgressCtrl& m_Progress1,CProgressCtrl& m_Progress2,ALG_ID Algid);
   	bool CDecryptFiles(vector<CString>& vsFiles,CString& CSKey,CProgressCtrl& m_Progress1,CProgressCtrl& m_Progress2,ALG_ID Algid);
private:
	ALG_ID Algid;
	// function crypt one file
	bool CDecryptOneFile(CString& CSsourceFile, CString& CSdestinationFile, CString& CSPassword,CProgressCtrl& m_Progress2);
	bool CEncryptOneFile(CString& CSsourceFile, CString& CSdestinationFile, CString& CSPassword,CProgressCtrl& m_Progress2);
};



//bool EncryptFile(PCHAR szSource,PCHAR szDestination,PCHAR szPassword)
//{ 
//#define MY_ENCODING_TYPE  (PKCS_7_ASN_ENCODING | X509_ASN_ENCODING)
//#define KEYLENGTH  0x00800000
//#define ENCRYPT_ALGORITHM CALG_RC4 
//#define ENCRYPT_BLOCK_SIZE 8 
//
//FILE *hSource; 
//FILE *hDestination; 
//
//HCRYPTPROV hCryptProv; 
//HCRYPTKEY hKey; 
//HCRYPTKEY hXchgKey; 
//HCRYPTHASH hHash; 
//
//PBYTE pbKeyBlob; 
//DWORD dwKeyBlobLen; 
//
//PBYTE pbBuffer; 
//DWORD dwBlockLen; 
//DWORD dwBufferLen; 
//DWORD dwCount; 
// 
//// Open source file. 
//hSource = fopen(szSource,"rb");
//// Open destination file. 
//hDestination = fopen(szDestination,"wb");
//
//// Get the handle to the default provider. 
//CryptAcquireContext(&hCryptProv,NULL,MS_ENHANCED_PROV,PROV_RSA_FULL,0);
//
//// Create the session key.
//if(!szPassword ) 
//{ 
//   fprintf(stderr, "no password program will exit!");
//} 
//
//// Create a hash object. 
//CryptCreateHash(hCryptProv,CALG_MD5,0,0,&hHash);
//
//// Hash the password. 
//CryptHashData(hHash,(BYTE *)szPassword,strlen(szPassword),0);
//
//// Derive a session key from the hash object. 
//CryptDeriveKey(hCryptProv,ENCRYPT_ALGORITHM,hHash,KEYLENGTH,&hKey);
// 
//// Destroy hash object. 
//if(hHash) 
//{
//    if(!(CryptDestroyHash(hHash)))
//       MyHandleError("Error during CryptDestroyHash"); 
//    hHash = 0;
//}
//
//// Determine the number of bytes to encrypt at a time. 
//// This must be a multiple of ENCRYPT_BLOCK_SIZE.
//// ENCRYPT_BLOCK_SIZE is set by a #define statement.
//dwBlockLen = 1000 - 1000 % ENCRYPT_BLOCK_SIZE; 
//
//// Determine the block size. If a block cipher is used, 
//// it must have room for an extra block. 
//if(ENCRYPT_BLOCK_SIZE > 1)
//{
// dwBufferLen = dwBlockLen + ENCRYPT_BLOCK_SIZE; 
//}
//else
//{
// dwBufferLen = dwBlockLen; 
//}
//
//// Allocate memory. 
//pbBuffer = (BYTE *)malloc(dwBufferLen);
//
//// In a do loop, encrypt the source file, and write to the source file. 
//do
//{
// // Read up to dwBlockLen bytes from the source file. 
// dwCount = fread(pbBuffer, 1, dwBlockLen, hSource); 
// 
// // Encrypt data. 
// CryptEncrypt(hKey,0,feof(hSource),0,pbBuffer,&dwCount,dwBufferLen);
//
// // Write data to the destination file. 
// fwrite(pbBuffer, 1, dwCount, hDestination);
//
//}while(!feof(hSource)); 
//
//
//// Close files.
//fclose(hSource);
//fclose(hDestination);
//
//// Free memory. 
//if(pbBuffer)
//   free(pbBuffer); 
// 
//if(hKey)
//{
//    if(!(CryptDestroyKey(hKey)))
//        MyHandleError("Error during CryptDestroyKey");
//}
//
//// Release the provider handle. 
//if(hCryptProv)
//{
//    if(!(CryptReleaseContext(hCryptProv, 0)))
//        MyHandleError("Error during CryptReleaseContext");
//}
//
//
//return(TRUE); 
//} // end Encryptfile






