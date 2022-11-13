#include <stdio.h>
#include <stdlib.h>
#include <string.h>


pthread_rwlock_t rwlock=PTHREAD_RWLOCK_INITIALIZER;



void *downtime() {
    for(int i=0;i<3;i++){
          sleep(2);
   
       pthread_rwlock_rdlock(&rwlock);
       Node *temp=root;
       root = balanceTree(temp);
       freeSubtree(temp);
       pthread_rwlock_unlock(&rwlock);
      

    }
return NULL;
}

//传入的是command文件名
void *ServeClient(char *client) {
    FILE *fp ; //缓冲区
    char buff [1024];//文件指针
    int len; //行字符指针
    char functionName[30];
    int nodeValue;

    /*client解析*/
    char clientID[20];
    sscanf(client,"%[^_]",clientID);
    
    
    if ((fp = fopen(client,"r")) == NULL)
    {
        perror("Error! opening file");
        // 文件指针返回 NULL 则退出
        exit(1);       }  
    
    while (fgets(buff,1024,fp)!=NULL){
     len = strlen(buff);
     buff[len-1]='\0';
     sscanf(buff,"%s %d",functionName,&nodeValue);
     
      if(strcmp(functionName,"removeNode")==0){
      pthread_rwlock_wrlock(&rwlock);
      root=removeNode (root, nodeValue);
         printf("%sdeleteNode %d\n",clientID,nodeValue);
      pthread_rwlock_unlock(&rwlock);
      
      }
      if(strcmp(functionName,"addNode")==0){
      pthread_rwlock_wrlock(&rwlock);
      root=addNode (root, nodeValue);
            printf("%s%s %d\n",clientID,functionName,nodeValue);
      pthread_rwlock_unlock(&rwlock);
      }

      if(strcmp(functionName,"countNodes")==0){
       pthread_rwlock_rdlock(&rwlock);
       printf("%s%s = %d\n",clientID,functionName,countNodes (root));
        pthread_rwlock_unlock(&rwlock);

      }

      if(strcmp(functionName,"avgSubtree")==0){
        pthread_rwlock_rdlock(&rwlock);
        printf("%s%s = %f\n",clientID,functionName,avgSubtree (root));
        pthread_rwlock_unlock(&rwlock);
      }
    }
     pthread_rwlock_destroy(&rwlock);
     fclose(fp);
     return NULL;
    
    }
