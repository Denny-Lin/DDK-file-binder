//http://52sye.com/NewsInfo/1347405.html
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include<iostream>

int main(){
	long flen1 = 0;//檔案1的長度
	long flen2 = 0;//檔案2的長度
    FILE *fp1;
    FILE *fp2;
    FILE *fp3;//txt用來存放兩個檔案的長度的檔案 
	char cBuffer[60]; 
    char two_flen[60];//30byte + 30byte//0~29 + 30~59
	
	memset(cBuffer, '\0', sizeof(cBuffer));
	
	for(int i=0;i<60;i++){
		two_flen[i]='0';
	}
	 
	fp1=fopen("helloworld.exe","rb");// file1   
	fp2=fopen("hacked.exe","rb");// file2   
	
    if( NULL == fp1 || NULL == fp2){
        printf( "fp1&fp2 open failure\n" );
        return 1;
    }
	else{
        printf("open fp1&fp2 successed\n");        
        
        fseek(fp1, 0, SEEK_END);/* SEEK_END 位移的起算位址 = 檔案結尾 */
        flen1 = ftell(fp1);/* 得到檔案1大小 */ 	
			                              
        printf("Total size of file1 = %030s bytes\n", ltoa(flen1,cBuffer,10));//char* ltoa(long int value, char* string, int radix);
        
        fseek(fp2, 0, SEEK_END);
        flen2 = ftell(fp2);/* 得到檔案2大小 */ 		                  
        printf("Total size of file2 = %030d bytes\n", flen2);//30個字原左邊補0 
        
        fclose(fp1);
	    fclose(fp2);
    }
     	
	fp3=fopen("two_file_length.txt","w");// file3  
	if( NULL == fp3){
        printf( "fp3 open failure\n" );
        return 1;
    }
	else{	
        printf("open fp3 successed\n"); 
		
		fprintf(fp3, "%030s", ltoa(flen1,cBuffer,10));	
		
		fseek(fp3, 30, SEEK_SET);//跳到第30字元 
		fprintf(fp3, "%030s", ltoa(flen2,cBuffer,10));	

        fclose(fp3);
    }
    system("copy /b helloworld.exe+hacked.exe+two_file_length.txt tmp.exe");
    //system("pause");
    return 0; 
}
