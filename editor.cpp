#include<bits/stdc++.h>
#include<iostream>
#include<fstream>
#include<stack>
using namespace std;

ofstream myfile;
  
class Linklist{
     
     public:
     string data;
     Linklist *next;
     
     Linklist(){
        next=NULL;
     }
};

class UndoC{
    public:
 int opcount=0;
 string backup;
 Linklist *opnode;
 };

stack <UndoC*> st;
stack <UndoC*> st2;

Linklist *head=new Linklist(); //head of linklist
int opcount=0;

void update(string source,string des){

Linklist *ptr=head;

while(ptr!=NULL)
{
    if(ptr->data==source)
    {   
         UndoC *obj=new UndoC();  //push
       obj->opcount=3;
       obj->opnode=ptr;
       obj->backup=source;
       st.push(obj);

        ptr->data=des;
        cout<<"Updation sucessfull !"<<endl;
        return;
    }
ptr=ptr->next;
}
cout<<"Source data not found . "<<endl;

}

 void del(string source)
{

Linklist *ptr=head;
Linklist *pre=head;

  UndoC *obj=new UndoC(); 
       obj->opcount=6;
       obj->backup=source;
if(ptr->data==source)
{
  
      obj->opnode=head; // need check
      st.push(obj);

    head=ptr->next;
    delete(ptr);

    cout<<"Deleted sucessfully !"<<endl;
    return;
}

while(ptr!=NULL)
{
    if(ptr->data==source)
    {  
        obj->opnode=pre; //pre node ..for delete
        st.push(obj);

        pre->next=ptr->next;
        delete(ptr);
        cout<<"Deleted sucessfully !"<<endl;
        return;
    }
    pre=ptr;
ptr=ptr->next;
}
cout<<"Source data not found ! "<<endl;

}


 
 void storedata()
  { 
       UndoC *obj=new UndoC();  
       obj->opcount=2;
       obj->opnode=head;
       st.push(obj);

      string data;
      cout<<"Enter data to insert: "<<endl;
      fflush(stdin);
      getline(cin,data);

      istringstream iss(data);
      string word;

      Linklist *ptr=head;
      while(iss>> word)
      {
              
              if(ptr==NULL)
              {  
                 Linklist *node=new Linklist();
                 node->data=word;
                 head=node;
                 ptr=node;

                  obj->opnode=ptr;
              }
              else{
                    Linklist *node=new Linklist();
                    node->data=word;
                    ptr->next=node;
                    ptr=node;

              }

      }
  }
    
      void display()
      {  cout<<"Current data------"<<endl;
        Linklist *ptr=head;

        while(ptr!=NULL)
        {
            cout<<ptr->data<<"-->";
            ptr=ptr->next;
        }
        cout<<endl;
      }



void append(string source)
{
    Linklist *ptr=head;

    UndoC *obj=new UndoC();
    obj->opcount=4;
    obj->backup=source;
    
    if(ptr==NULL)
    {      obj->opnode=head;
           st.push(obj);

         Linklist *node=new Linklist();
                 node->data=source;
                 head=ptr=node;
          cout<<"Appended sucessfully !"<<endl;
          return ;
    }
   else{
         while(ptr->next!=NULL){
          ptr=ptr->next;

         }
           Linklist *node=new Linklist();
            node->data=source;
            ptr->next=node;

             obj->opnode=ptr;
           st.push(obj);

            cout<<"Appended sucessfully !"<<endl;

            return ;
        }
        cout<<"Append failed !"<<endl;
}


void search(string source){
   
   Linklist *ptr=head;

   while(ptr->data!=source && ptr->next!=NULL && ptr!=NULL)
      {  ptr=ptr->next;  
      }
        if(ptr->data==source)
        cout<<source<<" is found !"<<endl;
        else
        cout<<source<<" not found !"<<endl;

}

//////////////////////  UNDO methods /////////////////////

void undo_store(UndoC *ptr)
{
   Linklist *head=ptr->opnode;
    UndoC *obj2=new UndoC();    //redo push
       obj2->opcount=ptr->opcount;
       obj2->opnode=head;
       st2.push(obj2);

    ptr->opnode=NULL;
    cout<<"Undo sucessfull !"<<endl;
}

void undo_update(UndoC *ptr)
{
     UndoC *obj2=new UndoC();    //redo push
       obj2->opcount=ptr->opcount;
       obj2->opnode=ptr->opnode;
       obj2->backup=ptr->opnode->data;
       st2.push(obj2);

   ptr->opnode->data=ptr->backup;   
   cout<<"Undo sucessfull !"<<endl;   
}

  void undo_append(UndoC *ptr)
  {
    UndoC *obj2=new UndoC();    //redo push
       obj2->opcount=ptr->opcount;
       obj2->opnode=ptr->opnode;
       obj2->backup=ptr->backup;
       st2.push(obj2);


    ptr->opnode->next=NULL;
    cout<<"Undo sucessfull !"<<endl;
  }

  void undo_delete(UndoC *ptr)
  {
     UndoC *obj2=new UndoC();    //redo push
       obj2->opcount=ptr->opcount;
       obj2->opnode=ptr->opnode;
       st2.push(obj2);

    Linklist *node=new Linklist();
    node->data=ptr->backup;
    node->next=ptr->opnode->next;
    ptr->opnode->next=node;
    cout<<"Undo sucessfull !"<<endl;
  }

     /////////////////////// Redo methods /////////////////

void redo_store(UndoC *ptr2)
{
     head=ptr2->opnode;
      cout<<"Redo sucessfull !"<<endl;
}
void redo_update(UndoC *ptr2)
{
  ptr2->opnode->data=ptr2->backup;
  cout<<"Redo sucessfull !"<<endl;
}
void redo_append(UndoC *ptr2)
{
   Linklist *node=new Linklist();
        node->data=ptr2->backup;
   ptr2->opnode->next=node;
   cout<<"Redo sucessfull !"<<endl;
}
 void redo_delete(UndoC *ptr2)
 {
    ptr2->opnode->next=ptr2->opnode->next->next;
    cout<<"Redo sucessfull !"<<endl;
 }


  ////////////  main  ////////////


int main(){
  int loop=1;
  string f="";

  while(loop)
  { int input;
    

       cout<<"1. Create storage for your data: "<<endl;
       cout<<"2. Insert data:"<<endl;
       cout<<"3. Update data:"<<endl;
       cout<<"4. Append data:"<<endl;
       cout<<"5. Search data:"<<endl;
       cout<<"6. Delete data:"<<endl;
       cout<<"7. Display data on console:"<<endl;
       cout<<"8. Undo operation:"<<endl;
       cout<<"9. Redo operation:"<<endl;
       cout<<"10. Save data in  permanent storage:"<<endl;
       cout<<"11. EXIT "<<endl;
         
       cout<<"Enter choice: ";  
       fflush(stdin);
       cin>>input;   
  system("cls");
  switch(input)
   {  
      case 1: 
      {  cout<<"Enter the file name: "<<endl;
       
         cin>>f;
            ofstream myfile(f+".txt",ios::app);

            cout<<"File created sucessfully: "<<endl;

      } break;
      case 2: 
      {       
          storedata();
       
          opcount=2;
      } break;
      case 3: 
      {     
          string source,des;   
            cout<<"Enter source data: ";
             cin>>source;
             
            cout<<"Enter destination data: "<<endl;
             cin>>des;
        update(source,des);
        opcount=3;
      } break;
      case 4: {
             string source;   
             cout<<"Enter data to append: "<<endl;
             cin>>source;
             append(source);
            opcount=4;
      } break;
      case 5: {
             string source;   
             cout<<"Enter data to search: "<<endl;
             cin>>source;
             search(source);

             
      } break;
      case 6: {
             string source;   
             cout<<"Enter data to delete: "<<endl;
             cin>>source;
             del(source);
            opcount=6;
      } break;
      case 7: {
            display();

      } break;
      case 8: { 
                  if(!st.empty())
                { UndoC *ptr=st.top();
                   st.pop();
                   switch(ptr->opcount)
                  {
                    case 2: undo_store(ptr); break;
                    case 3: undo_update(ptr); break;
                    case 4: undo_append(ptr); break;
                    case 6: undo_delete(ptr); break;

                  default: cout<<"default undo";

                  }
                }
                else
                cout<<"Nothing to undo !"<<endl;              

      } break;
      case 9: 
      {
              if(!st2.empty())
                { UndoC *ptr2=st2.top();
                   st2.pop();
                   switch(ptr2->opcount)
                  {
                    case 2: redo_store(ptr2); break;
                    case 3: redo_update(ptr2); break;
                    case 4: redo_append(ptr2); break;
                    case 6: redo_delete(ptr2); break;

                  default: cout<<"default redo";

                  }
                }
                else
                cout<<"Nothing to redo !"<<endl;
      } break;
      case 10: {  
        if (head == NULL) {
            cout << "No nodes  in the list ";
        }
        else {
            ofstream outfile;
            outfile.open(f+".txt", ios::app);
            Linklist *temp = head;
            while (temp != NULL) {
            outfile << temp->data << endl;
                temp = temp->next;
            }
            outfile.close();

            cout<<"All data saved sucessfully !"<<endl;
        }
    

      } break;
      case 11: loop=0; break;
      default: cout<<"wrong input...try again";
   }
  
  
  }
  
    return 0;

}