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
                cout<<"\nP"<<p<<":req(";
                for(int z=0;z<resource;z++)
                cout<<s[p].need[z]<<" ";
                cout<<")<=Available(";
                for(int z=0;z<resource;z++)
                cout<<avail[z]<<" ";
                cout<<") Hence P"<<p<<" is completed!";
                safe_update(p);
                cout<<"\nSafe State is Now->{";
                for(int h=0;h<=safe;h++)
                {
                  cout<<" P"<<safe_state[h]<<" ";
                }
                cout<<"}";
                s[p].update();
                cout<<"\nAvailable is now (";
                for(int z=0;z<resource;z++)
                cout<<avail[z]<<" ";
                cout<<")";
              }
             else {
                    cout<<"\n P"<<p<<":req > Available => Skipped\n";
                    ++count_remain;
                  }
          }
        
      }
      remain[++remi]=count_remain;
    
if(remain[remi]==remain[remi-1])
{
   cout<<"\nDEADLOCK PRESENT\n";
   return;
} 
else if(end_check()==2){ Bank_Algo(s,remain);}
else
  {
    cout<<"\nSafe State Reached ->{";
    for(i=0;i<=safe;i++)
    {
      cout<<" P"<<safe_state[i]<<" ";
    }
    cout<<"}";
  }
  return;
}

int main()
{   char c='A'; int k;int q;
    cout<<"\tBANKERS ALGORITHM ---- CODED BY ADEEB \n\n";
    cout<<"Enter The No:of Processes->";
    cin>>pno;
    remain[0]=pno;
    cout<<"\nEnter The No:of Resources->";
    cin>>resource;
    res = new int[resource];
    for(i=A;i<resource;i++)
    { 
      cout<<"\nEnter Total No:Of Resource instances of Type "<<c++<<"->";
      cin>>res[i];
    }  
    struct process *s= new process[pno];
    int z=0;
    do{
      cout<<"\nEnter Allocation(ABC...), Max(ABC...) for Process P"<<z<<"->";
      for(q=A;q<resource;q++)
      { 
        cin>>s[z].allocation[q];
      }
      for(q=A;q<resource;q++)
      { 
        cin>>s[z].max[q];
      }
      s[z].calc_need();
      ++z;
    }while(z<pno);
    cout<<"\nEnter Available(ABC...)->";
    for(int k=A;k<resource;k++)
    {      
      cin>>avail[k];
    }
    cout<<"\nTotal Resource\n";
    c='A';
    for(q=A;q<resource;q++)
    {
      cout<<c++<<"->"<<res[q]<<"\n";
    }
    cout<<"\n  MAX         ALLOCATION         NEED\n";
    char f,g,h;f=g=h='A';     
      for(q=A;q<resource;q++)
      cout<<f++<<"  ";
      cout<<"       ";
      for(q=A;q<resource;q++)
      cout<<g++<<"  ";
      cout<<"       ";
      for(q=A;q<resource;q++)
      cout<<h++<<"  ";
      printf("\n");
    
    for(i=0;i<pno;i++)
    {
       for(q=A;q<resource;q++)
       cout<<s[i].max[q]<<"  ";
       cout<<"\t";
       for(q=A;q<resource;q++)
       cout<<s[i].allocation[q]<<"  ";
       cout<<"\t";
       for(q=A;q<resource;q++)
       cout<<s[i].need[q]<<"  ";
       printf("\n\n");
    }
    Bank_Algo(s,remain);    
    getch();
}

