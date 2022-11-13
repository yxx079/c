#include <stdio.h>
#include <stdlib.h>
#include <string.h>


pthread_rwlock_t rwlock=PTHREAD_RWLOCK_INITIALIZER;


static int  countDT=0;
void *downtime() {
    if(countDT==3)
    exit(0); 
    else{
    sleep(2);
    balanceTree(root);
    countDT ++;}

}

//传入的是command文件名
void *ServeClient(char *client) {
    FILE *fp ; //缓冲区
    char buf [1024];//文件指针
    int len; //行字符指针
    char *functionName;;
    int nodeValue;
    char sep[] =" ";

    /*client解析*/
    char *clientID;
    clientID = strtok(client,"_");
    
    if ((fp = fopen(client,"r")) == NULL)
    {
        perror("Error! opening file");
        // 文件指针返回 NULL 则退出
        exit(1);         
    
    while (fgets(buf,1024,fp)!=NULL){
     len = strlen(buf);
     buf[len-1]='\0';
     functionName=strtok(buf,sep);
     
      if(strcmp(functionName,"removeNode")==0){
      nodeValue =atoi(strtok(NULL,sep));
      pthread_rwlock_rdlock(&rwlock);
     
      if( removeNode (root, nodeValue)!=NULL)
         printf("%s%s %d/n",clientID,functionName,nodeValue);
      pthread_rwlock_unlock(&rwlock);
      
      }
      if(strcmp(functionName,"addNode")==0){
      nodeValue =atoi(strtok(NULL,sep));
      pthread_rwlock_rdlock(&rwlock);
      if( addNode (root, nodeValue)!=NULL)
            printf("%s%s %d/n",clientID,functionName,nodeValue);
      pthread_rwlock_unlock(&rwlock);
      }

      if(strcmp(functionName,"countNodes")==0){
       pthread_rwlock_rdlock(&rwlock);
       
       printf("%s%s = %d",clientID,functionName,countNodes (root));
        pthread_rwlock_unlock(&rwlock);

      }

      if(strcmp(functionName,"avgSubtree")==0){
        pthread_rwlock_rdlock(&rwlock);
        printf("%s%s = %f",clientID,functionName,avgSubtree (root));
        pthread_rwlock_unlock(&rwlock);
      }
    }
     pthread_rwlock_destroy(&rwlock);
     fclose(fp);
    
    }}
