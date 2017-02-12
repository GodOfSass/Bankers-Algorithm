#include<iostream>
#include<conio.h>
using namespace std;
enum resource_type{A=0,B,C,D,E,F,G,H,I,J};
int resource; 
int i; int safe=-1;int pno; 
int remain[50];int remi=0; int avail[10];
int *res; int safe_state[50];int count_remain;
struct process
{      
    int max[10];    
    int need[10];
    int allocation[10];
    int done;
    void calc_need()
    {  for(i=A;i<resource;i++)
       {
         need[i]=(max[i]-allocation[i]);
       }
    }
    process()
    { done=0;
      for(int i=0;i<10;i++){
      max[i]=0;
      allocation[i]=0;
      need[i]=0;
      }
    }
    int check()
    { int flag=0;
      for(int v=0;v<resource;v++)
      {
        if(need[v]>avail[v]) { ++flag;}
        
      }
      if(flag==0) return 1;
      else return 2;
    }
    friend void safe_update(int x)
    {  safe_state[++safe]=x;
    
    }
    void update()
    {  
      for(i=A;i<resource;i++)
      {
        avail[i]+=allocation[i];
      }
      done=1;
    }   
};
int end_check()
{
  for(i=A;i<resource;i++)
  {
    if(avail[i]!=res[i]) return 2;
  }
  return 1;
}
void Bank_Algo(struct process *s,int remain[])
{ 
  
      count_remain=0;
      for(int p=0;p<pno;p++)
      { 
        if(!s[p].done)
          {
             if(s[p].check()==1)
              {
                printf("\nP%d:req(",p);
                for(int z=0;z<resource;z++)
                printf("%d ",s[p].need[z]);
                printf(")<=Available(");
                for(int z=0;z<resource;z++)
                printf("%d ",avail[z]);
                printf(") Hence P%d is completed!",p);
                safe_update(p);
                printf("\nSafe State is Now->{");
                for(int h=0;h<=safe;h++)
                {
                  printf(" P%d ",safe_state[h]);
                }
                printf("}");
                s[p].update();
                printf("\nAvailable is now (");
                for(int z=0;z<resource;z++)
                printf("%d ",avail[z]);
                printf(")");
              }
             else {
                    printf("\n P%d:req > Available => Skipped\n",p);
                    ++count_remain;
                  }
          }
        
      }
      remain[++remi]=count_remain;
    
if(remain[remi]==remain[remi-1])
{
   printf("\nDEADLOCK PRESENT\n");
   return;
} 
else if(end_check()==2){ Bank_Algo(s,remain);}
else
  {
    printf("\nSafe State Reached ->{");
    for(i=0;i<=safe;i++)
    {
      printf(" P%d ",safe_state[i]);
    }
    printf("}");
  }
  return;
}

int main()
{   char c='A'; int k;int q;
    printf("\tBANKERS ALGORITHM ---- CODED BY ADEEB \n\n");
    printf("Enter The No:of Processes->");
    scanf("%d",&pno);
    remain[0]=pno;
    printf("\nEnter The No:of Resources->");
    scanf("%d",&resource);
    res = new int[resource];
    for(i=A;i<resource;i++)
    { 
      printf("\nEnter Total No:Of Resource instances of Type %c->",c++);
      scanf("%d",&res[i]);
    }  
    struct process *s= new process[pno];
    int z=0;
    do{
      printf("\nEnter Allocation(ABC...), Max(ABC...) for Process P%d->",z);
      for(q=A;q<resource;q++)
      { 
        scanf("%d",&s[z].allocation[q]);
      }
      for(q=A;q<resource;q++)
      { 
        scanf("%d",&s[z].max[q]);
      }
      s[z].calc_need();
      ++z;
    }while(z<pno);
    printf("\nEnter Available(ABC...)->");
    for(int k=A;k<resource;k++)
    {      
      scanf("%d",&avail[k]);
    }
    printf("\nTotal Resource\n");
    c='A';
    for(q=A;q<resource;q++)
    {
      printf("%c->%d\n",c++,res[q]);
    }
    printf("\n  MAX         ALLOCATION         NEED\n");
    char f,g,h;f=g=h='A';
     
      for(q=A;q<resource;q++)
      printf("%c  ",f++);
      printf("       ");
      for(q=A;q<resource;q++)
      printf("%c  ",g++);
       printf("       ");
      for(q=A;q<resource;q++)
      printf("%c  ",h++);
      printf("\n");
    
    for(i=0;i<pno;i++)
    {
       for(q=A;q<resource;q++)
       printf("%d  ",s[i].max[q]);
       printf("\t");
       for(q=A;q<resource;q++)
       printf("%d  ",s[i].allocation[q]);
       printf("\t");
       for(q=A;q<resource;q++)
       printf("%d  ",s[i].need[q]);
       printf("\n\n");
    }
    Bank_Algo(s,remain);    
    getch();
}

