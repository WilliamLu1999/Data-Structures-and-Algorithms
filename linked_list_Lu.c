#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
struct node1D {
    struct node1D *next;
    char *name;
};
struct node2D {
    struct node1D *first;
    struct node2D *down;
    char *name;
};
struct node2D *unseenHead;//external outside all functions unseen head pointer
void insertFront2D(char *value);
void insertBefore2D(char *value,char *before);
void insertFront1D(char *value,char *twoDname);
void insertBefore1D(char *value,char*oneDname);
void printAll();
void print1DList(char *value);
bool find1D(char *value);
bool find2D(char *value);

#define BUFSIZE 100
char buf[BUFSIZE];
int  bufp = 0;
int getword(char *word, int lim) {
    int c, getch(void);
    void ungetch(int);
    char *w = word;
    while (isspace(c = getch())) ;
    if (c != EOF)
      *w++ = c;
    if (!isalpha(c)) {
      *word= '\0';
      return c;
    }
    for ( ; --lim > 0; w++)
      
      if (!isalnum(*w = getch())) {
        ungetch(*w);
        break;
      }
    //printf("%d\n",lim);
    *w = '\0';
    return word[0];
}  
int getch(void) {
    return (bufp>0) ? buf[--bufp] : getchar();
}
void ungetch(int c) {
    if (bufp >= BUFSIZE)
      printf("ungetch: too many chars\n");
    else
      buf[bufp++] = c;
}
#define MAXWORDLENGTH 20
int main(){
    unseenHead=NULL;
    
    char wordbuf[MAXWORDLENGTH];
    
    while((getword(wordbuf, MAXWORDLENGTH) != EOF)){
        if(strcmp(wordbuf,"insertFront2D")==0){
        getword(wordbuf, MAXWORDLENGTH);
        insertFront2D(wordbuf);
        }
      
        else if(strcmp(wordbuf,"find2D")==0){
        //printf("%s\n",unseenHead->name);
        //if(unseenHead!=NULL){
          //  printf("%s testing\n",unseenHead->name);
            //unseenHead becomes find2D}
        getword(wordbuf,MAXWORDLENGTH);
        //printf("%s\n",wordbuf);
        find2D(wordbuf)? printf("Found") : printf("Not found");
        }
        else if(strcmp(wordbuf,"insertBefore2D")==0){
          char saveAlias[MAXWORDLENGTH];
          getword(wordbuf,MAXWORDLENGTH);
          strcpy(saveAlias,wordbuf);
          getword(wordbuf,MAXWORDLENGTH);
          insertBefore2D(saveAlias,wordbuf);
          
        }
        else if(strcmp(wordbuf,"insertFront1D")==0){
          char saveAlias2[MAXWORDLENGTH];
          getword(wordbuf,MAXWORDLENGTH);
          strcpy(saveAlias2,wordbuf);
          getword(wordbuf,MAXWORDLENGTH);
          insertFront1D(saveAlias2,wordbuf);
        }
        else if(strcmp(wordbuf,"find1D")==0){
          getword(wordbuf,MAXWORDLENGTH);
          find1D(wordbuf)? printf("Found") : printf("Not found");
        }
        else if(strcmp(wordbuf,"print1DList")==0){
          getword(wordbuf,MAXWORDLENGTH);
          print1DList(wordbuf);
        }
        else if(strcmp(wordbuf,"insertBefore1D")==0){
          char saveAlias3[MAXWORDLENGTH];
          getword(wordbuf,MAXWORDLENGTH);
          strcpy(saveAlias3,wordbuf);
          getword(wordbuf,MAXWORDLENGTH);
          insertBefore1D(saveAlias3,wordbuf);
        }
        else if(strcmp(wordbuf,"printAll")==0){
          printAll();
        }
    
    }
    return 0;

}
void insertFront2D(char *value){
    struct node2D *ptr;
    
    ptr = (struct node2D*)malloc(sizeof (struct node2D));
    ptr->name = malloc(strlen(value) + 1);  
    strcpy(ptr->name, value); 
    ptr->down=unseenHead;
    ptr->first=NULL;
    unseenHead=ptr;
    /*if (unseenHead==NULL){
      ptr->down=NULL;
      ptr->first=NULL;
      ptr->name=value;
      unseenHead=ptr;
    }
    else{
      ptr->name=value;
      ptr->first=NULL;
      ptr->down=unseenHead;
      unseenHead->first=NULL;//maybe wrong
      unseenHead=ptr;
    }*/
    //printf("\nNode inserted\n");
    //printf("\nNode inserted is %s",value);
    //printf("\nNode inserted is %s",ptr->name);
    printf("\nNode inserted is %s",unseenHead->name);
}
void insertBefore2D(char *value,char *before){
  struct node2D *ptr;
  ptr = (struct node2D*)malloc(sizeof (struct node2D));
  ptr->name = malloc(strlen(value) + 1);  
  strcpy(ptr->name, value); 
  ptr->first=NULL;
  
  if(ptr==NULL){
    printf("Invalid input value.");
    return;
  }
  struct node2D *temp=unseenHead;
  if(strcmp(unseenHead->name,before)==0){
    ptr->down=unseenHead;
    unseenHead= ptr; //switch back unseenHead. Give unseenHead the first position
    printf("Succeed.");
    return;
  }
  while(temp&& temp->down!=NULL){
    if (strcmp(temp->down->name,before)==0){//find the node before the name node
      ptr->down =temp->down;
      temp->down=ptr;
      printf("Succeed.");
      return;
  }else{
    temp=temp->down;
  }
  
}
  printf("No such before name.");
  free(ptr);
  return;
}
void insertFront1D(char *value,char *twodname){
  struct node1D *ptr;
  ptr =(struct node1D*)malloc(sizeof (struct node1D));
  ptr->name= malloc(strlen(value)+1);
  strcpy(ptr->name,value);
  if(ptr==NULL){
    printf("Invalid input value");
    return;
  }
  struct node2D *temp=unseenHead;//for the purpose of finding the start 2d node so that a one d node could be inserted.
  while(temp!=NULL){
    if(strcmp(temp->name,twodname)==0){
      ptr->next = temp->first;
      temp->first=ptr;
      printf("Succeed 1d node insertion");
      return;
    }
    else{
      temp= temp->down;
    }
  }
  printf("NO such 2D node to add the 1D node.");
  free(ptr);
  return;
}
void insertBefore1D(char *value, char *onedname){
  struct node2D *temp=unseenHead;
  if(temp==NULL){
    printf("Cannot insert the 1D node before the 1D node you specified since there's no 2D node yet.");
    return;
  }
  struct node1D *ptr;
  ptr=(struct node1D*)malloc(sizeof(struct node1D));// create space for the about to be inserted 1Dnode
  ptr->name =malloc(strlen(value)+1);
  strcpy(ptr->name,value);
  if(ptr==NULL){
    printf("Invalid input value.");
    return;
  }
 
  while(temp!=NULL){
    struct node1D * temp2 = temp->first;
    while(temp2!=NULL){
      
      if(strcmp(onedname,temp2->name)==0&&(temp->first==temp2)){
        //we find the 1d node. now insert it.
        ptr->next =temp->first;
        temp->first= ptr;
        printf("Insertion Succeed!");
        return;
      }
      if(temp2->next!=NULL){
        if(strcmp(onedname,temp2->next->name)==0){
          ptr->next =temp2->next;
          temp2->next=ptr;
          printf("Insertion Succeed!");
          return;
        }
        else{
          temp2=temp2->next;
        }
      }
      else{
          printf("Cannot add the 1d node. All have been searched.");
          return;
      }
      /*
      if(strcmp(onedname,temp2->name)!=0){
        if(temp2->next!=NULL){
          temp2=temp2->next;
        }
        else{
          if(temp->down!=NULL){
            temp = temp->down;
            temp2= temp->first;
          }
          else{
            printf("No such node to insert before. Ciao.");
            return;
          }
        }
      }

    }
    */
    }
   temp =temp->down;
  }
  printf("Cannot add the 1d node. All have been searched.");
  return;

}
bool find1D(char *value){
  struct node2D *temp=unseenHead;
  if(temp==NULL){
    return false;
  }
  struct node1D *temp2= temp->first;
  while(temp!=NULL){
    if(temp2!=NULL){
      if(strcmp(temp2->name,value)==0){
        return true;
      }
      else{
        temp2=temp2->next;
      }
    }
    else{
        temp=temp->down;
        if(temp!=NULL){
          temp2 =temp->first;
        }
        else
          {break;}
      }
    
  }
  return false;

}
bool find2D(char *value){
  struct node2D *temp=unseenHead;
  //temp->name = malloc(strlen(value) + 1);  
  //printf("%s unseenHEad name exist?\n",unseenHead->name);
  //strcpy(temp->name, unseenHead->name); 
    //temp->name = value;

  while (temp != NULL)
    {
        //printf("%s testing temp\n",temp->name);
        //printf("%s testing temp's val\n",value);
        if (strcmp(temp->name,value)==0){
            return true;
        }
        else{
          temp=temp->down;     
        }
      
    }
    return false;

}
void print1DList(char *value){
  struct node2D *temp = unseenHead;

  while (temp!=NULL)
  {
    if(strcmp(temp->name,value)!=0){
      temp=temp->down;
    }
    else{
      break;//now we have the correct temp with the value equal to the 2d node
    }
  }
  if(temp==NULL){
    printf("No way to print the 1D list since no such 2D node exists.");
    return;
  }
  
  struct node1D *temp2 = temp->first;
  printf("%s\t",temp->name);
  while(temp2!=NULL){
    printf("%s\t",temp2->name);
    temp2 =temp2->next;
    }
}
void printAll(){
  struct node2D *temp = unseenHead;
  if(temp==NULL){
    printf("No way to print anything as nothing are implemented.");
    return;
  }
  struct node1D *temp2 = temp->first;
  while(temp !=NULL){
   if(temp->first==NULL){
      printf("2d node name is %s\n",temp->name);}
      else{
        printf("2d node name is %s\n\t",temp->name);
      }
    while (temp2!=NULL){
      if(temp2->next!=NULL){
        printf("1d node name is %s\n\t",temp2->name);
        temp2 =temp2->next;
      }
      else{
        printf("1d node is %s\n",temp2->name);
        temp2 =temp2->next;
      }
    }
    
    temp=temp->down;
    if(temp!=NULL){
      temp2=temp->first;
    }
    else
      break;
}
return;
}



/* Lesson learned

1. Declaring external variable outside the main. Define it in the main.
2. getword takes one word at a time. Use char name[maxlength] to store the middle words.
3. malloc struct syntax.
4. The string inside the struct node also needs to be malloc.
5. Use strcpy to copy the string into the string of a struct.
6. Use strcmp to compare if two strings are equal or not. ==0 means they are equivalent.
7. Unseen pointer does not need malloc. It only points to the first node.
8. Be patient and you can solve them all.

*/