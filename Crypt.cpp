

#include "StdAfx.h"
#include "crypt.h"



CCrypt::CCrypt(void)
{
}



CCrypt::~CCrypt(void)
{
}



void CCrypt::GetFileNamesFromDialog(vector<CString>& vsFiles,CWnd* ownerCWnd)
{
   //Create an Open dialog; the default file name extension is ".my".
   CFileDialog fileDlg (TRUE, "", "*.*", OFN_FILEMUSTEXIST| OFN_ALLOWMULTISELECT, "All Files (*.*)|*.*|All Files (*.*)|*.*||",ownerCWnd);
   
   #define MAX_BUFF 1024000//1MB

   //Customize OFN....   structure for multiple files
   char *fdata = new char[MAX_BUFF];
   if(!fdata) return;//No memory
   ZeroMemory(fdata,sizeof(MAX_BUFF));
   OPENFILENAME &m_ofn = fileDlg.GetOFN();
   m_ofn.nMaxFile = MAX_BUFF;  
   m_ofn.lpstrFile = fdata;
      
   //Run dialog...
   if( fileDlg.DoModal () == IDOK )
   {
    //fill vector...
    CString tempbuff;
    register unsigned int loop;
    for(loop = 0;loop <= MAX_BUFF;loop++)
    {
      if(fdata[loop] != '\0')
 	  { 
	   tempbuff.Append((CString)fdata[loop]);
	  }
	  if(fdata[loop] == '\0')
	  {
       vsFiles.push_back(tempbuff);
	   tempbuff = "";
	   if(fdata[(loop+1)] == '\0') break;//end job  		 
	  }
    }//...
   }else
   {
	   return;
	   delete []fdata; 
   }

  //select one file...
  if(vsFiles.size() == 1)
  {
   CString temp = vsFiles[0];
   vsFiles.clear();
   temp.MakeReverse();
   unsigned int inamelen = temp.Find('\\');
   temp.MakeReverse();
   CString CSPath = temp.Left(temp.GetLength() - inamelen);
   CString CSFileName = temp.Right(inamelen);
   vsFiles.push_back(CSPath);
   vsFiles.push_back(CSFileName);
  }//...

  //check path...
  CString temp = vsFiles[0];
  if(temp.Right(1) != '\\')
  {
	  temp.Append((CString)'\\');
	  vsFiles.erase(vsFiles.begin());
      vsFiles.insert(vsFiles.begin(),temp);
  }
  //...

  //For testing this 
  //for(unsigned int muk = 0;muk < vsFiles.size();muk++)
  //{
  // MessageBox(NULL,vsFiles[muk],"",MB_OK);
  //}

   delete []fdata; 
}



// in - filename and path out - encrypted file on the disk.........
bool CCrypt::CDecryptFiles(vector<CString>& vsFiles,CString& CSKey,CProgressCtrl& m_Progress1,CProgressCtrl& m_Progress2,ALG_ID algid)
{ 
	Algid = algid;
    CString CSFilePath = vsFiles[0];
	CString CSSourceFile;
	CString CSDestinationFile;
    bool ret;
	//main loop...
	m_Progress1.SetRange(0,(int)vsFiles.size() - 1);//Progress bar property
    m_Progress1.SetStep(1);
	unsigned int mloop = 1;//vsFiles[0] - path
	for(mloop = 1; mloop < (int)vsFiles.size();mloop++)
	{
	 CSSourceFile = CSFilePath + vsFiles[mloop];
     CSDestinationFile = CSFilePath + vsFiles[mloop];
     CSDestinationFile = CSDestinationFile.Left(CSDestinationFile.GetLength() - 3);
	 CSDestinationFile.Append("eef");
	 ret = CEncryptOneFile(CSSourceFile,CSDestinationFile,CSKey,m_Progress2);
     if(!ret) return false;
     m_Progress1.StepIt();
	 CSDestinationFile.Empty();
	 CSSourceFile.Empty();
	}//end of main loop...
    m_Progress1.SetPos(0);
	return true;
}



// in - filename and path out - encrypted file on the disk.........
bool CCrypt::CEncryptFiles(vector<CString>& vsFiles,CString& CSKey,CProgressCtrl& m_Progress1,CProgressCtrl& m_Progress2,ALG_ID algid)
{ 
	Algid = algid;
    CString CSFilePath = vsFiles[0];
	CString CSSourceFile;
	CString CSDestinationFile;
    bool ret;
	//main loop...
	m_Progress1.SetRange(0,(int)vsFiles.size() - 1);//Progress bar property
    m_Progress1.SetStep(1);
	unsigned int mloop = 1;//vsFiles[0] - path
	for(mloop = 1; mloop < (int)vsFiles.size();mloop++)
	{
	 CSSourceFile = CSFilePath + vsFiles[mloop];
     CSDestinationFile = CSFilePath + vsFiles[mloop];
     CSDestinationFile = CSDestinationFile.Left(CSDestinationFile.GetLength() - 3);
	 CSDestinationFile.Append("eef");
	 ret = CEncryptOneFile(CSSourceFile,CSDestinationFile,CSKey,m_Progress2);
     if(!ret) return false;
     m_Progress1.StepIt();
	 CSDestinationFile.Empty();
	 CSSourceFile.Empty();
	}//end of main loop...
    m_Progress1.SetPos(0);
	return true;
}



// function crypt one file
bool CCrypt::CEncryptOneFile(CString& CSsourceFile, CString& CSdestinationFile, CString& CSPassword,CProgressCtrl& m_Progress2)
{
 #define MY_ENCODING_TYPE  (PKCS_7_ASN_ENCODING | X509_ASN_ENCODING)
 #define KEYLENGTH  0x00800000
 #define ENCRYPT_BLOCK_SIZE 32 //Original 8 

 FILE *hSource; 
 FILE *hDestination; 
 HCRYPTPROV hCryptProv; 
 HCRYPTKEY hKey; 
 HCRYPTHASH hHash; 
 PBYTE pbBuffer; 
 DWORD dwBlockLen; 
 DWORD dwBufferLen; 
 DWORD dwCount; 
 
 // Open source file. 
 hSource = fopen(CSsourceFile,"rb");
 if(!hSource) return false;

 // Open destination file. 
 hDestination = fopen(CSdestinationFile,"wb");
 if(!hDestination) return false;

 // Get the handle to the default provider. 
 BOOL ret = CryptAcquireContext(&hCryptProv,NULL,MS_ENHANCED_PROV,PROV_RSA_FULL,0);
 if(!ret) return false;

 // Create a hash object. 
 ret = CryptCreateHash(hCryptProv,CALG_MD5,0,0,&hHash);
 if(!ret) return false;
 
 // Hash the password. 
 ret = CryptHashData(hHash,(BYTE*)CSPassword.GetBuffer(0),CSPassword.GetLength(),0);
 CSPassword.ReleaseBuffer();
 if(!ret) return false;

 // Derive a session key from the hash object. 
 ret = CryptDeriveKey(hCryptProv,Algid,hHash,KEYLENGTH,&hKey);
 if(!ret) return false;

 // Destroy hash object. 
 if(hHash) 
 {
   CryptDestroyHash(hHash);
   hHash = 0;
 }

 // Determine the number of bytes to encrypt at a time. 
 // This must be a multiple of ENCRYPT_BLOCK_SIZE.
 // ENCRYPT_BLOCK_SIZE is set by a #define statement.
 dwBlockLen = 1000 - 1000 % ENCRYPT_BLOCK_SIZE; 

 // Determine the block size. If a block cipher is used, 
 // it must have room for an extra block. 
 if(ENCRYPT_BLOCK_SIZE > 1)
 {
  dwBufferLen = dwBlockLen + ENCRYPT_BLOCK_SIZE; 
 }
 else
 {
  dwBufferLen = dwBlockLen; 
 }

 // Allocate memory. 
 pbBuffer = (BYTE *)malloc(dwBufferLen);

 //write extension of file on the top...
 fwrite(CSsourceFile.Right(3), 1, 3, hDestination);

 // In a do loop, encrypt the source file, and write to the source file. 
 do
 {
  // Read up to dwBlockLen bytes from the source file. 
  dwCount = (DWORD)fread(pbBuffer, 1, dwBlockLen, hSource); 
  // Encrypt data. 
  ret = CryptEncrypt(hKey,0,feof(hSource),0,pbBuffer,&dwCount,dwBufferLen);
  if(!ret)
  {
	  if(pbBuffer)
    free(pbBuffer); 
  return false;
  }
  // Write data to the destination file. 
  fwrite(pbBuffer, 1, dwCount, hDestination);

  m_Progress2.StepIt();//Progress bar

 }while(!feof(hSource)); 

 m_Progress2.SetPos(0);

 // Close files.
 fclose(hSource);
 fclose(hDestination);

 // Free memory.  
 if(pbBuffer)
    free(pbBuffer); 
 
 if(hKey)
 {
     CryptDestroyKey(hKey);
 }

 // Release the provider handle. 
 if(hCryptProv)
 {
  CryptReleaseContext(hCryptProv, 0);
 }


return(TRUE); 
}



// function decrypt one file
bool CCrypt::CDecryptOneFile(CString& CSsourceFile, CString& CSdestinationFile, CString& CSPassword,CProgressCtrl& m_Progress2)
{
 #define MY_ENCODING_TYPE  (PKCS_7_ASN_ENCODING | X509_ASN_ENCODING)
 #define KEYLENGTH  0x00800000
 #define ENCRYPT_BLOCK_SIZE 32 //Original 8 

 FILE *hSource; 
 FILE *hDestination; 
 HCRYPTPROV hCryptProv; 
 HCRYPTKEY hKey; 
 HCRYPTHASH hHash; 
 PBYTE pbBuffer; 
 DWORD dwBlockLen; 
 DWORD dwBufferLen; 
 DWORD dwCount; 
 
 // Open source file. 
 hSource = fopen(CSsourceFile,"rb");
 if(!hSource) return false;

 // Open destination file. 
 hDestination = fopen(CSdestinationFile,"wb");
 if(!hDestination) return false;

 // Get the handle to the default provider. 
 BOOL ret = CryptAcquireContext(&hCryptProv,NULL,MS_ENHANCED_PROV,PROV_RSA_FULL,0);
 if(!ret) return false;

 // Create a hash object. 
 ret = CryptCreateHash(hCryptProv,CALG_MD5,0,0,&hHash);
 if(!ret) return false;
 
 // Hash the password. 
 ret = CryptHashData(hHash,(BYTE *)CSPassword.GetBuffer(0),CSPassword.GetLength(),0);
 CSPassword.ReleaseBuffer();
 if(!ret) return false;

 // Derive a session key from the hash object. 
 ret = CryptDeriveKey(hCryptProv,Algid,hHash,KEYLENGTH,&hKey);
 if(!ret) return false;

 // Destroy hash object. 
 if(hHash) 
 {
   CryptDestroyHash(hHash);
   hHash = 0;
 }

 // Determine the number of bytes to encrypt at a time. 
 // This must be a multiple of ENCRYPT_BLOCK_SIZE.
 // ENCRYPT_BLOCK_SIZE is set by a #define statement.
 dwBlockLen = 1000 - 1000 % ENCRYPT_BLOCK_SIZE; 

 // Determine the block size. If a block cipher is used, 
 // it must have room for an extra block. 
 if(ENCRYPT_BLOCK_SIZE > 1)
 {
  dwBufferLen = dwBlockLen + ENCRYPT_BLOCK_SIZE; 
 }
 else
 {
  dwBufferLen = dwBlockLen; 
 }

 // Allocate memory. 
 pbBuffer = (BYTE *)malloc(dwBufferLen);

 // In a do loop, encrypt the source file, and write to the source file. 
 do
 {
  // Read up to dwBlockLen bytes from the source file. 
  dwCount = (DWORD)fread(pbBuffer, 1, dwBlockLen, hSource); 
  // Encrypt data. 
  ret = CryptEncrypt(hKey,0,feof(hSource),0,pbBuffer,&dwCount,dwBufferLen);
  if(!ret)
  {
	  if(pbBuffer)
    free(pbBuffer); 
  return false;
  }
  // Write data to the destination file. 
  fwrite(pbBuffer, 1, dwCount, hDestination);

  m_Progress2.StepIt();//Progress bar

 }while(!feof(hSource)); 

 m_Progress2.SetPos(0);

 // Close files.
 fclose(hSource);
 fclose(hDestination);

 // Free memory.  
 if(pbBuffer)
    free(pbBuffer); 
 
 if(hKey)
 {
     CryptDestroyKey(hKey);
 }

 // Release the provider handle. 
 if(hCryptProv)
 {
  CryptReleaseContext(hCryptProv, 0);
 }


return(TRUE); 
}



////get in file...
//	 CString CSFilePath = vsFiles[0];
//     CFile InFile;
//     CFileException fileException;
//	 if(!InFile.Open(CSFilePath + vsFiles[mloop], CFile::modeRead, &fileException ) )
//	 {
//		TRACE( "Can't open file for reading %s, error = %u\n",
//		vsFiles[mloop], fileException.m_cause );
//	 return false;
//	 }
//	 ULONGLONG  inFlen = InFile.GetLength();
//     if(!inFlen) return false;//...
//     
//	 //get out file...
//	 CString OutFileNameAndPath;
//     for(int lop = 0;lop < vsFiles[mloop].GetLength();lop++)
//	 {
//      if(vsFiles[mloop] != '.') OutFileNameAndPath.Append((CString)vsFiles[mloop]);	
//	 }
//     OutFileNameAndPath.Append(".enf");
//     CFile OutFile;
//	 if(!OutFile.Open(OutFileNameAndPath, CFile::modeWrite|CFile::modeCreate , &fileException ) )
//	 {
//		TRACE( "Can't open file for writing %s, error = %u\n",
//		OutFileNameAndPath, fileException.m_cause );
//	 return false;
//	 }//...
//
//     DWORD outLen;
//     OutFile.SetLength(outLen);
//	 OutFile.SeekToBegin();
//
//     #define MAX_BUFF 1024000//1MB
//     char *fbuff = new char[MAX_BUFF];
//     if(!fbuff) return false;//No memory
//     ZeroMemory(fbuff,sizeof(MAX_BUFF));
//	 OutFile.Close();
//     InFile.Close();
//	 delete []fbuff;
//








