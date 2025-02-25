/***************************************************************
 *
 * file: pss.h
 *
 * @Author  Nikolaos Vasilikopoulos (nvasilik@csd.uoc.gr), John Petropoulos (johnpetr@csd.uoc.gr)
 * @Version 30-11-2022
 *
 * @e-mail       hy240-list@csd.uoc.gr
 *
 * @brief   Implementation of the "pss.h" header file for the Public Subscribe System,
 * function definitions
 *
 *
 ***************************************************************
 */

#include <stdio.h>
#include <stdlib.h>

#include "pss.h"
struct Group *G[MG]; 
struct SubInfo *T[MG]; 

void inorder_traversal(struct Info* root) {
   if(root != NULL) {
      inorder_traversal(root->ilc);
      printf("Info Id: %d  ",root->iId);          
      inorder_traversal(root->irc);  
   }
}
struct Info *newnode(int id,int tm){
    struct Info *new= (struct Info*)malloc(sizeof(struct Info));
    new->iId=id;
    new->itm=tm;
    new->ip=new->ilc=new->irc=NULL;
    int i;
    for(i=0;i<MG;i++){
        new->igp[i]=0;
    }
    return new;
}
struct Info *BST_Insert2(struct Info *node,int id,int tm){
    if(node==NULL)return newnode(id,tm);
    if(id<node->itm)
        node->ilc=BST_Insert2(node->ilc,id,tm);
    else
        node->irc=BST_Insert2(node->irc,id,tm);
    return node;
}
struct TreeInfo* LO_BST_Insert(struct TreeInfo *root,int id,int tm){
    struct TreeInfo* newnode=(struct TreeInfo*)malloc(sizeof(struct TreeInfo));
    newnode->tId=id;
    newnode->ttm=tm;
    int count;
    if(root==NULL){ 
        newnode->next=NULL;
        newnode->tlc=NULL;
        newnode->trc=NULL;
        newnode->tp=NULL;
    }else{
        struct TreeInfo* new=(struct TreeInfo*)malloc(sizeof(struct TreeInfo));
        struct TreeInfo* prev;
        while (root!=NULL){
            prev=root;
            if(newnode->tId < root->tId){
                root=root->tlc;
            }else{
                root=root->trc;
            }
        }
        if(prev->tId > newnode->tId){
            new->tId=newnode->tId;
            newnode->next=prev;
            new->tlc=newnode;
            new->trc=prev;
            if(prev->tp!=NULL){
                if(prev->tp->tId > new->tId){
                    prev->tp->tlc=new;
                }else{
                    prev->tp->trc=new;
                }
                new->tp=prev->tp;
            }
            newnode->tp=new;
            prev->tp=new;
        }else{
            new->tId=prev->tId;
            prev->next=newnode;
            new->tlc=prev;
            new->trc=newnode;
            if(prev->tp!=NULL){
                if(prev->tp->tId > new->tId){
                    prev->tp->tlc=new;
                }else{
                    prev->tp->trc=new;
                }
                new->tp=prev->tp;
            }
            newnode->tp=new;
            prev->tp=new;
        }   
    }
    return newnode;
}

int size,hashFuctions;
void Subscription_Insert(int sId,int i){
    struct Subscription *newnode=(struct Subscription*)malloc(sizeof(struct Subscription));
    struct Group *current=G[i];
    if(!newnode){
        printf("cannot malloc");
        return;
    }
    newnode->sId=sId;
    if(current->gsub==NULL){
        current->gsub=newnode;
        newnode->snext=NULL;
    }else{
        newnode->snext=current->gsub->snext;
        current->gsub->snext=newnode;
    }

}
void SubInfo_Insert(int sId,int stm,int i){
    struct SubInfo *newnode=(struct SubInfo*)malloc(sizeof(struct SubInfo));
    struct SubInfo *current=T[i];
    if(!newnode){
        printf("cannot malloc");
        return;
    }
    newnode->sId=sId;
    newnode->stm=stm;
    int j;
    for(j=0;j<MG;j++){
        newnode->tgp[j]=(struct TreeInfo *)1;
        newnode->sgp[j]=(struct TreeInfo *)1;
    }
    newnode->tgp[i]=NULL;
    newnode->sgp[i]=NULL;

    if(current->snext==NULL){
        current->snext=newnode;
        newnode->snext=NULL;
    }else{
        while(current!=NULL){
            if(newnode->sId >= current->sId && current->snext==NULL){/*if the info goes last*/
                newnode->snext=NULL;
                current->snext=newnode;
                break;
            }
            else if(newnode->sId>=current->sId && newnode->sId <=current->snext->sId){/*if it goes in the middle*/
                newnode->snext=current->snext;
                current->snext=newnode;
                break;
            }
            else if(newnode->sId < current->sId){
                newnode->snext=current;
                T[i]=newnode;
                break;
            }
            current=current->snext;
        }
    }

}
struct Info* minNode(struct Info* node)
{
    struct Info* current = node;

    while (current && current->ilc != NULL)
        current = current->ilc;
 
    return current;
}
struct Info* array[MG][MG];
int count=0;
struct Info* deleteNode(struct Info* root, int tm,int i){
    if (root == NULL)
        return root;
    if (tm < root->itm)
        root->ilc = deleteNode(root->ilc, tm,i);
    else if (tm > root->itm)
        root->irc = deleteNode(root->irc, tm,i);
    else {
        if (root->ilc == NULL && root->irc == NULL)
            return NULL;
 
        else if (root->ilc == NULL) {
            struct Info* temp = root->irc;
            array[i][count]=root;
            count++;
            return temp;
        }
        else if (root->irc == NULL) {
            struct Info* temp = root->ilc;
            array[i][count]=root;
            count++;
            return temp;
        } 
        struct Info* temp = minNode(root->irc);
        root->itm = temp->itm;
        root->irc = deleteNode(root->irc, temp->itm,i);
    }
    return root;
}

/**
 * @brief Optional function to initialize data structures that
 *        need initialization
 *
 * @param m Size of the hash table.
 * @param p Prime number for the universal hash functions.
 *
 * @return 0 on success
 *         1 on failure
 */
int initialize(int m, int p){
    struct Group *pointer;
    struct SubInfo *sub;
    int i;
    int j;
    /*initialize groups*/
    for(i=0;i<MG;i++){
        pointer = (struct Group *) malloc(sizeof(struct Group));
        if(!pointer)return 1;
        pointer->gId=i;
        G[i]=pointer;
        pointer->gr=NULL;
        pointer->gsub=NULL;
        sub=(struct SubInfo*)malloc(sizeof(struct SubInfo));
        if(!sub)return 1;
        sub->sId=i;
        T[i]=sub;
        sub->snext=NULL;
        for(j=0;j<MG;j++){
            array[i][j]=NULL;
        }
    }
    /*initialize hash table*/
    size=m;
    hashFuctions=p;

    return 0;
}

/**
 * @brief Free resources
 *
 * @return 0 on success
 *         1 on failure
 */
int free_all(void){
    return EXIT_SUCCESS;
}

/**
 * @brief Insert info
 *
 * @param iTM Timestamp of arrival
 * @param iId Identifier of information
 * @param gids_arr Pointer to array containing the gids of the Event.
 * @param size_of_gids_arr Size of gids_arr including -1
 * @return 0 on success
 *          1 on failure
 */
int Insert_Info(int iTM,int iId,int* gids_arr,int size_of_gids_arr){
   int i;
   for(i=0;i<size_of_gids_arr;i++){
        if(gids_arr[i]>=64 || gids_arr[i]<0 ){
            printf("invalid\n");
            continue;
        }
        G[gids_arr[i]]->gr=BST_Insert2(G[gids_arr[i]]->gr,iId,iTM);
        G[gids_arr[i]]->gr->igp[i]=1;
   }
    return EXIT_SUCCESS;
}
/**
 * @brief Subsriber Registration
 *
 * @param sTM Timestamp of arrival
 * @param sId Identifier of subscriber
 * @param gids_arr Pointer to array containing the gids of the Event.
 * @param size_of_gids_arr Size of gids_arr including -1
 * @return 0 on success
 *          1 on failure
 */
int Subscriber_Registration(int sTM,int sId,int* gids_arr,int size_of_gids_arr){
    int i;
    for(i=0;i<size_of_gids_arr;i++){
        if(gids_arr[i]>=64 || gids_arr[i]<0 ){
            printf("invalid\n");
            continue;
        }
        Subscription_Insert(sId,gids_arr[i]);
        SubInfo_Insert(sId,sTM,gids_arr[i]);
    }
    return EXIT_SUCCESS;
}
/**
 * @brief Prune Information from server and forward it to client
 *
 * @param tm Information timestamp of arrival
 * @return 0 on success
 *          1 on failure
 */
int Prune(int tm){
    struct Info* currentinfo;
    int i;
    int j;
    struct SubInfo *curr;
    for(i=0;i<MG;i++){
        currentinfo=G[i]->gr;
        while (currentinfo!=NULL){
            if(tm>=currentinfo->itm){
                G[i]->gr=deleteNode(G[i]->gr,currentinfo->itm,i);
            }
            currentinfo=currentinfo->ilc;
        }
        count=0;
    }
    for(i=0;i<MG;i++){
        for(j=0;j<MG;j++){
            if(array[i][j]!=NULL)
                printf("array[%d][%d] %d->",i,j,array[i][j]->itm);
        }
        if(array[i][j]!=NULL)
        printf("\n\n");
    }
    for(i=0;i<MG;i++){
        curr=T[i]->snext;
        while (curr!=NULL){
            if(curr->tgp[i]!=(struct TreeInfo*)1){
                for(j=0;j<MG;j++){
                    if(array[i][j]!=NULL)
                    curr->tgp[i]=LO_BST_Insert(curr->tgp[i],array[i][j]->iId,array[i][j]->itm);
                }
            }
            curr=curr->snext;
        }
    }
    return EXIT_SUCCESS;
}
/**
 * @brief Consume Information for subscriber
 *
 * @param sId Subscriber identifier
 * @return 0 on success
 *          1 on failure
 */
int Consume(int sId){
    struct SubInfo* curr;
    int i;
    int j;
    for(i=0;i<MG;i++){
        curr=T[i]->snext;
        while (curr!=NULL){
            if(curr->sId==sId){/*briskw ton sub*/
                for(j=0;j<MG;j++){
                    if(curr->sgp[j]!=(struct TreeInfo*)1){/*briskw to group pou ekane sub*/
                        while(curr->tgp[j]->tlc!=NULL){/*briskw to lefmost*/
                            curr->tgp[j]=curr->tgp[j]->tlc;
                        }
                        while (curr->tgp[j]->next!=NULL){/*diatrexw ola ta info kai afhnw to deikth sto righmost*/
                            curr->tgp[j]=curr->tgp[j]->next;
                        }
                        
                    }
                }
            }
            curr=curr->snext;
        }
        
    }
    return EXIT_SUCCESS; 
}
/**
 * @brief Delete subscriber
 *
 * @param sId Subscriber identifier
 * @return 0 on success
 *          1 on failure
 */
int Delete_Subscriber(int sId){
    int i;
    struct Subscription *curr;
    struct Subscription *prev;
    for(i=0;i<MG;i++){
        
        curr=G[i]->gsub;
        if(curr==NULL)continue;

        if(curr->sId==sId){
            G[i]->gsub=curr->snext;
            free(curr);
        }else{
            while(curr!=NULL){
                prev=curr;
                curr=curr->snext;
                if(curr==NULL)break;
                if(curr->sId==sId){
                    prev->snext=curr->snext;
                    free(curr);
                    break;
                }
            }
        }
    }
    struct SubInfo* sub;
    struct SubInfo* prevsub;
    for(i=0;i<MG;i++){
        
        sub=T[i];
        if(sub==NULL)continue;

        if(sub->sId==sId){
            T[i]=sub->snext;
            free(sub);
        }else{
            while(sub!=NULL){
                prevsub=sub;
                sub=sub->snext;
                if(sub==NULL)break;
                if(sub->sId==sId){
                    prevsub->snext=sub->snext;
                    free(sub);
                    break;
                }
            }
        }
    }
    return EXIT_SUCCESS;
}
/**
 * @brief Print Data Structures of the system
 *
 * @return 0 on success
 *          1 on failure
 */
int Print_all(void){
    struct Group *currentgroup;
    struct Info *currentinfo;
    struct Subscription *currentsub;
    struct SubInfo* sub;
    int i;
    /*TODO den kanei ta print*/
    for( i=0;i<MG;i++){
        currentgroup=G[i];
        currentinfo=currentgroup->gr;
        if(currentinfo!=NULL){
            printf("GroupId: %d -> ",i);
            inorder_traversal(currentinfo);
            printf("\n");
        }
        currentsub=G[i]->gsub;
        while(currentsub!=NULL){
            printf("SubId: %d ",currentsub->sId);
            printf("\n");
            currentsub=currentsub->snext;
        }
    }
    for(i=0;i<MG;i++){
        sub=T[i]->snext;
        if(sub!=NULL)printf("\nT[%d] =",i);
        while (sub!=NULL){
            printf(" SubInfo Id: %d -> ",sub->sId); 
            sub=sub->snext;
        }
        
    }
    printf("\n");
    return EXIT_SUCCESS;
}
