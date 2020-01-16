#include<iostream>
#include<cstdlib>
using namespace std;
class node1{
    private:
     node1 *left;
     node1 *right;
     node1 *parent;
     int reg_no;
     int d;
     float t;
     float x;
     int height;
     int left_count;
     int right_count;
    public:
        int get_r(){
            return reg_no;
        }
        void assign_r(int r){
            reg_no=r;
        } 
        node1 *get_left(){
            return left;
        }
        node1 *get_right(){
            return right;
        }
        node1 *get_parent(){
            return parent;

        }
        void assign_left(node1*p){
            left=p;
        }
        void assign_right(node1 *p){
            right=p;
        }
        void assign_parent(node1 *p){
            parent=p;
        }
        float get_t(){
            return t;
        }
        float get_x(){
            return x;
        }
        int get_d(){
            return d;
        }
        void assign_t(float time){
            t=time;
        }
        void assign_x(float position){
            x=position;
        }
        void assign_d(int direction){
            d=direction;
        }
        int get_height(){
            return height;
        }
        void assign_height(int h){
            height=h;
        }
        int get_left_count(){
            return left_count;
        }
        void assign_left_count(int k){
            left_count=k;
        }
        int get_right_count(){
            return right_count;
        }
        void assign_right_count(int k){
            right_count=k;
        }

};
class head{
    public:
        node1*root;
        float time;
    
};
int max1(int a,int b){
    if(a>b){
        return a;
    }
    else{
        return b;
    }
}
int height_node(node1 *p){
    if(p==NULL){
        return 0;
    }
    else{
        return p->get_height();;
    }
}
//search for car with registration number r
node1 *search(int r,node1 *t){
    if(t==NULL){
        return NULL;
    }
    else{
        node1 *p;
        p=t;
        while(p!=NULL){
            if(p->get_r()==r){
                return p;
            }
            else if(p->get_r()<r){
                p=p->get_right();
            }
            else{
                p=p->get_left();
            }
        }
        return NULL;
    }
}
node1* new_node(int r,float x,float t,int d,node1*n)  //new node is added at the leaf position
{  
    node1* node = new node1(); 
    node->assign_r(r); 
    node->assign_x(x);
    node->assign_t(t);
    node->assign_d(d);
    node->assign_left(NULL);  
    node->assign_right(NULL);  
    node->assign_height(1);
    node->assign_parent(n);
    node->assign_left_count(0);
    node->assign_right_count(0);
      
    return(node);  
}  
  
//rotates the subtree rooted at y to maintain balance
//rotates to the right  
node1 *right_Rotate(node1 *y)  
{  
    node1 *x = y->get_left();  
    node1 *T2 = x->get_right();  
  
    // Performing rotation   
    x->assign_right(y);  
    y->assign_left(T2);  
  
    // Updating the heights after rotation 
    y->assign_height(1 + max1(height_node(y->get_left()),height_node(y->get_right()))); 
                      
    x->assign_height(1 + max1(height_node(x->get_left()),height_node(x->get_right())));
    //updating the parents of rotated nodes
    x->assign_parent(y->get_parent());
    y->assign_parent(x);
    //updating the count of left node & count of right nodes
    y->assign_left_count(y->get_left_count()-(1+x->get_left_count()));
    x->assign_right_count(x->get_right_count()+1+y->get_right_count());
                  
  
    // Return new root after rotation  
    return x;  
}  
  
 
// rotate subtree rooted at x to maintain balance 
//rotates to the left  
node1 *left_Rotate(node1 *x)  
{  
    node1 *y = x->get_right();  
    node1 *T2 = y->get_left();  
  
    // Performing rotation  
    y->assign_left(x);  
    x->assign_right(T2);  
  
    // Updating heights after rotation  
    x->assign_height(1+max1(height_node(x->get_left()),height_node(x->get_right())));     
                     
    y->assign_height(1+max1(height_node(y->get_left()),height_node(y->get_right())));
    //updating the parents of rotated nodes  
    y->assign_parent(x->get_parent());
    x->assign_parent(y);
    //updating the count of left node & count of right nodes
    x->assign_right_count(x->get_right_count()-(1+y->get_right_count()));
    y->assign_left_count(y->get_left_count()+1+x->get_left_count());                
  
    // Returning new root after rotation 
    return y;  
}  
  
// Get Balance factor of node N  
int getBalance(node1 *N)  
{  
    if (N == NULL)  
        return 0;  
    return height_node(N->get_left()) - height_node(N->get_right());  
}  
  
// Recursive function to insert a key 
// key inserted into  subtree rooted with node 
// returns the new root of the subtree.
 node1* insert(node1* node, int r,float x,float t,int d)  
{  
    /* 1. Perform the normal BST insertion */
    if (node == NULL)  
        return(new_node(r,x,t,d,node));  
    //if r < r of node move left
    if (r < node->get_r()){  
        node->assign_left_count(node->get_left_count()+1);
        node->assign_left(insert(node->get_left(),r,x,t,d));
        node->get_left()->assign_parent(node);

        } 
      //  if r > r of node ,move right   
    else if (r > node->get_r()){  
        node->assign_right(insert(node->get_right(),r,x,t,d)); 
        node->assign_right_count(node->get_right_count()+1);
        node->get_right()->assign_parent(node);

    }
    else // Equal keys are not inserted again in BST  
        return node;  
  
    /* 2. Updating height of this ancestor node */
    node->assign_height(1+max1(height_node(node->get_left()),height_node(node->get_right())));  
                         
  
    /* 3. Get the balance factor of this ancestor  */
       
    int balance = getBalance(node);  
  
    // If this node becomes unbalanced, then  
    // there are 4 cases  
  
    // Left Left Case  
    if (balance > 1 && r < node->get_left()->get_r())  
        return right_Rotate(node);  
  
    // Right Right Case  
    if (balance < -1 && r > node->get_right()->get_r())  
        return left_Rotate(node);  
  
    // Left Right Case  
    if (balance > 1 && r > node->get_left()->get_r())  
    {  
        node->assign_left(left_Rotate(node->get_left()));  
        return right_Rotate(node);  
    }  
  
    // Right Left Case  
    if (balance < -1 && r < node->get_right()->get_r())  
    {  
        node->assign_right(right_Rotate(node->get_right()));  
        return left_Rotate(node);  
    }  
  
    /* return the (unchanged) node pointer */
    return node;  
}
// inserting into second avial tree with head h0
//inserts according to position of car
//inserts car moving from right to left
node1* insert_0(node1* node, int r,float x,float t,int d)  
{  
    /* 1. Perform the normal BST insertion */
    if (node == NULL)  
        return(new_node(r,x,t,d,node));  
  //Same as in BST 
    //inserted according to position
    if (x < (node->get_x()-(t-node->get_t()))){  
        node->assign_left_count(node->get_left_count()+1);
        node->assign_left(insert_0(node->get_left(),r,x,t,d));
        node->assign_x(node->get_x()-(t-node->get_t()));
        node->assign_t(t);
        node->get_left()->assign_parent(node);

        }  
    else if (x > node->get_x()-(t-node->get_t() )){  
        node->assign_right(insert_0(node->get_right(),r,x,t,d)); 
        node->assign_right_count(node->get_right_count()+1);
        node->assign_x(node->get_x()-(t-node->get_t()));
        node->assign_t(t);
        node->get_right()->assign_parent(node);

    }
    else // Equal X-coordinate in same direction are not allowed   
        return node;  
  
    /* 2. Update height of this ancestor node */
    node->assign_height(1+max1(height_node(node->get_left()),height_node(node->get_right())));  
                         
  
    /* 3. Get the balance factor of this ancestor*/  
        
    int balance = getBalance(node);  
  
    // If this node becomes unbalanced, then  
    // there are 4 cases  
    // basic avial tree operation
    // Left Left Case  
    if (balance > 1 && r < node->get_left()->get_r())  
        return right_Rotate(node);  
  
    // Right Right Case  
    if (balance < -1 && r > node->get_right()->get_r())  
        return left_Rotate(node);  
  
    // Left Right Case  
    if (balance > 1 && r > node->get_left()->get_r())  
    {  
        node->assign_left(left_Rotate(node->get_left()));  
        return right_Rotate(node);  
    }  
  
    // Right Left Case  
    if (balance < -1 && r < node->get_right()->get_r())  
    {  
        node->assign_right(right_Rotate(node->get_right()));  
        return left_Rotate(node);  
    }  
  
    /* return the (unchanged) node pointer */
    return node;  
}
// inserting into third avial tree with head h1
//inserts according to position of car
//inserts car moving from left to right
node1* insert_1(node1* node, int r,float x,float t,int d)  
{  
    /* 1. Perform the normal BST insertion */
    if (node == NULL)  
        return(new_node(r,x,t,d,node));  
  
    if (x < (node->get_x()+(t-node->get_t()))){  
        node->assign_left_count(node->get_left_count()+1);
        node->assign_left(insert_1(node->get_left(),r,x,t,d));
        node->assign_x(node->get_x()+(t-node->get_t()));
        node->assign_t(t);
        node->get_left()->assign_parent(node);

        }  
    else if (x > node->get_x()+(t-node->get_t()) ){  
        node->assign_right(insert_1(node->get_right(),r,x,t,d)); 
        node->assign_right_count(node->get_right_count()+1);
        node->assign_x(node->get_x()+(t-node->get_t()));
        node->assign_t(t);
        node->get_right()->assign_parent(node);

    }
    else // Equal keys are not allowed in BST  
        return node;  
  
    /* 2. Update height of this ancestor node */
    node->assign_height(1+max1(height_node(node->get_left()),height_node(node->get_right())));  
                         
  
    /* 3. Get the balance factor of this ancestor */ 
        
    int balance = getBalance(node);  
  
    // If this node becomes unbalanced, then  
    // there are 4 cases  
  
    // Left Left Case  
    if (balance > 1 && r < node->get_left()->get_r())  
        return right_Rotate(node);  
  
    // Right Right Case  
    if (balance < -1 && r > node->get_right()->get_r())  
        return left_Rotate(node);  
  
    // Left Right Case  
    if (balance > 1 && r > node->get_left()->get_r())  
    {  
        node->assign_left(left_Rotate(node->get_left()));  
        return right_Rotate(node);  
    }  
  
    // Right Left Case  
    if (balance < -1 && r < node->get_right()->get_r())  
    {  
        node->assign_right(right_Rotate(node->get_right()));  
        return left_Rotate(node);  
    }  
  
    /* return the (unchanged) node pointer */
    return node;  
}

  
  
  
// following function is used to get the successor of the node to be deleted
node1 * replacement(node1* node)  
{  
    node1* current = node;  
  
    /* loop down to find the leftmost leaf */
    while (current->get_left() != NULL)  
        current = current->get_left();  
  
    return current;  
}  
  
// Recursive function to delete a node  
// with given r from subtree with given root 
  
node1* deleteNode(node1* root, int r,float t)  
{  
      
    //   PERFORM STANDARD BST DELETE  
    if (root == NULL)  
        return root;  
  
    // If the r to be deleted is smaller than r of current node
    
    //  go in left subtree  
    if ( r < root->get_r() ){ 
        root->assign_left_count(root->get_left_count()-1);
        root->assign_left(deleteNode(root->get_left(), r,t));  
  
    // If the r to be deleted is greater than r of current node 
     
    //  go in right subtree  
       } 
    else if( r > root->get_r() ){
        root->assign_right_count(root->get_right_count()-1);
        root->assign_right(deleteNode(root->get_right(),r,t));  
    }
    // if r is same as root's r  
    // This is the node to be deleted  
    else
    {  
        // node with only one child or no child  
        if( (root->get_left() == NULL) ||  (root->get_right() == NULL) )
             
        {  
            
            node1 *temp;
            node1 *temp1;
            if(root->get_left()==NULL){
                temp=root->get_right();
            }
            else{
                temp=root->get_left();
            }
            // No child case  
            if (temp == NULL)  
            {  
                temp = root;  
                root = NULL;  
            }  
            else {
                temp1=root->get_parent();
            // One child case
             int c1,c2;
             c1=root->get_left_count();
             c2=root->get_right_count(); 
            *root = *temp; // Copy the contents of root and temp 
              root->assign_parent(temp1);
              root->assign_left_count(c1);
              root->assign_right_count(c2);
              if(temp->get_left()!=NULL){
                temp->get_left()->assign_parent(root);
              }
              if(temp->get_right()!=NULL){
                temp->get_right()->assign_parent(root);
                }             
             free(temp); 
            } 
        }  
        else
        {  
            // node with two children:  
            //get the  successor (smallest in the right subtree)  using replacement function
            node1* temp = replacement(root->get_right());  
  
            // Copy the inorder successor's  
            // data in this node  
            root->assign_r(temp->get_r());
            root->assign_x(temp->get_x());
            root->assign_t(temp->get_t());
            root->assign_d(temp->get_d());


  
            // Delete the inorder successor  
            root->assign_right(deleteNode(root->get_right(),  
                                     temp->get_r(),temp->get_t())); 
                                       
        }  
    }  
  
    // If the tree had only one node 
    // then return  
    if (root == NULL)  
    return root;  
  
    //  UPDATE HEIGHT OF THE CURRENT NODE  
    root->assign_height(1+max1(height_node(root->get_left()),height_node(root->get_right()))); 
                          
  
    //  GET THE BALANCE FACTOR OF  
    // on this node check the avial condition 
    int balance = getBalance(root);  
  
    // If this node becomes unbalanced,  
    // then there are 4 cases  
  
    // Left Left Case  
    if (balance > 1 &&  getBalance(root->get_left()) >= 0)
     { 
        return right_Rotate(root);  
    }
    // Left Right Case  
    if (balance > 1 &&  getBalance(root->get_left()) < 0)
          
    {  
        root->assign_left(left_Rotate(root->get_left()));  
        return right_Rotate(root);  
    }  
  
    // Right Right Case  
    if (balance < -1 &&  getBalance(root->get_right()) <= 0)
    {  
        return left_Rotate(root);  
    }
    // Right Left Case  
    if (balance < -1 &&  getBalance(root->get_right()) > 0)
         
    {  
        root->assign_right(right_Rotate(root->get_right()));  
        return left_Rotate(root);  
    }  
  
    return root;  
} 
// DELETING THE REQUIRED NODE FROM THE AVIAL TREE CONTAINING LEFT TO RIGHT GOING CARS(if the car with r has d=1)
node1* deleteNode_1(node1* root, int r,float t,float x)  
{  
      
    //  PERFORM STANDARD BST DELETE  
    if (root == NULL)  
        return root;  
  
    // If the r to be deleted is smaller than root's r  
    // move to left subtree 
    //adjust left count as node would be deleted from left subtree of root  
    if ( x < root->get_x()+(t-root->get_t()) ){ 
        root->assign_x(root->get_x()+(t-root->get_t()));
        root->assign_t(t);
        root->assign_left_count(root->get_left_count()-1);
        root->assign_left(deleteNode_1(root->get_left(), r,t,x));  
    }
    // If the key to be deleted is greater than root's r 
    // move to right subtree  
     //adjust the right count as the node to be deleted is in right subtree of the root
        
    else if( x > root->get_x()+(t-root->get_t()) ){
        root->assign_x(root->get_x()+(t-root->get_t()));
        root->assign_t(t);
        root->assign_right_count(root->get_right_count()-1);
        root->assign_right(deleteNode_1(root->get_right(),r,t,x));  
    }
    // if key is same as root's key, then  
    // This is the node to be deleted  
    else
    {  
        // node with only one child or no child  
        if( (root->get_left() == NULL) ||  (root->get_right() == NULL) )
             
        {  
           
            node1 *temp;
            node1 *temp1;
            if(root->get_left()==NULL){
                temp=root->get_right();
            }
            else{
                temp=root->get_left();
            }
            // No child case  
            if (temp == NULL)  
            {  
                temp = root;  
                root = NULL;  
            }  
            else {
            // One child case
             temp1= root->get_parent();
             int c1,c2;
             c1=root->get_left_count();
             c2=root->get_right_count(); 
             *root = *temp;                         // Copy the contents of root and temp 
              root->assign_parent(temp1);
              root->assign_left_count(c1);
              root->assign_right_count(c2);
              if(temp->get_left()!=NULL){
                temp->get_left()->assign_parent(root);
              }
              if(temp->get_right()!=NULL){
                temp->get_right()->assign_parent(root);
                }             
             free(temp); 
            } 
        }  
        else
        {  
            // node with two children 
            // get successor (smallest in the right subtree)  
            node1* temp = replacement(root->get_right());  
  
            // Copy the inorder successor's  
            // data to this node  
            root->assign_r(temp->get_r());
            root->assign_x(temp->get_x());
            root->assign_t(temp->get_t());
            root->assign_d(temp->get_d());


  
            // Delete the inorder successor  
            root->assign_right(deleteNode_1(root->get_right(),  
                                     temp->get_r(),temp->get_t(),temp->get_x())); 
                                       
        }  
    }  
  
    // If the tree had only one node 
    // then return  
    if (root == NULL)  
    return root;  
  
    //  UPDATE HEIGHT OF THE CURRENT NODE  
    root->assign_height(1+max1(height_node(root->get_left()),height_node(root->get_right()))); 
                          
  
    //  GET THE BALANCE FACTOR OF  THIS NODE
      
    int balance = getBalance(root);  
  
    // If this node becomes unbalanced,  
    // then there are 4 cases  
  
    // Left Left Case  
    if (balance > 1 &&  getBalance(root->get_left()) >= 0)
     { 
        return right_Rotate(root);  
    }
    // Left Right Case  
    if (balance > 1 &&  getBalance(root->get_left()) < 0)
          
    {  
        root->assign_left(left_Rotate(root->get_left()));  
        return right_Rotate(root);  
    }  
  
    // Right Right Case  
    if (balance < -1 &&  getBalance(root->get_right()) <= 0)
    {
        return left_Rotate(root);  
    }
    
    // Right Left Case  
    if (balance < -1 &&  getBalance(root->get_right()) > 0)
          
    {  
        root->assign_right(right_Rotate(root->get_right()));  
        return left_Rotate(root);  
    }  
  
    return root;  
}  
//deleting the car moving from right to left from the avial tree containing cars with d=0(moving right to left)
node1* deleteNode_0(node1* root, int r,float t,float x)  
{  
      
    //  PERFORM STANDARD BST DELETE  
    if (root == NULL)  
        return root;  
  
    // If the r to be deleted is smaller than root's r 
    
    // go in left subtree 
    //maintain left node  count 
    if ( x < root->get_x()-(t-root->get_t()) ){ 
        root->assign_x(root->get_x()-(t-root->get_t()));
        root->assign_t(t);
        root->assign_left_count(root->get_left_count()-1);
        root->assign_left(deleteNode_0(root->get_left(), r,t,x));  
    }  
    // If the r to be deleted is greater than root's r  
    //  go in right subtree  
    //maintain  node count   
    else if( x > root->get_x()-(t-root->get_t()) ){
        root->assign_x(root->get_x()-(t-root->get_t()));
        root->assign_t(t);
        root->assign_right_count(root->get_right_count()-1);
        root->assign_right(deleteNode_0(root->get_right(),r,t,x));  
    }
    // if key is same as root's key, then  
    // This is the node to be deleted  
    else
    {  
        // node with only one child or no child  
        if( (root->get_left() == NULL) ||  (root->get_right() == NULL) )
             
        {  
            
            node1 *temp;
            node1 *temp1;
            if(root->get_left()==NULL){
                temp=root->get_right();
            }
            else{
                temp=root->get_left();
            }
            // No child case  
            if (temp == NULL)  
            {  
                temp = root;  
                root = NULL;  
            }  
            else {
            // One child case
            temp1= root->get_parent();
            int c1,c2;
            c1=root->get_left_count();
            c2=root->get_right_count(); 
            *root = *temp;                 // Copy the contents of root and temp 
            root->assign_parent(temp1);
            root->assign_left_count(c1);
            root->assign_right_count(c2);
            if(temp->get_left()!=NULL){
                temp->get_left()->assign_parent(root);
              }
            if(temp->get_right()!=NULL){
                temp->get_right()->assign_parent(root);
            }                      
             free(temp); 
            } 
        }  
        else
        {  
            // node with two children  
            // Get the inorder successor (smallest in the right subtree)  
            node1* temp = replacement(root->get_right());  
  
            // Copy the inorder successor's  
            // data to this node  
            root->assign_r(temp->get_r());
            root->assign_x(temp->get_x());
            root->assign_t(temp->get_t());
            root->assign_d(temp->get_d());


  
            // Delete the inorder successor  
            root->assign_right(deleteNode_0(root->get_right(),  
                                     temp->get_r(),temp->get_t(),temp->get_x())); 
                                       
        }  
    }  
  
    // If the tree had only one node 
    // then return  
    if (root == NULL)  
    return root;  
  
    //  UPDATE HEIGHT OF THE CURRENT NODE  
    root->assign_height(1+max1(height_node(root->get_left()),height_node(root->get_right()))); 
                          
  
    //  GET THE BALANCE FACTOR : to  check the avial condition at this node 
      
    int balance = getBalance(root);  
  
    // If this node becomes unbalanced,  
    // then there are 4 cases  
  
    // Left Left Case  
    if (balance > 1 &&  getBalance(root->get_left()) >= 0)
     { 
        return right_Rotate(root);  
    }
    // Left Right Case  
    if (balance > 1 &&  getBalance(root->get_left()) < 0)
          
    {  
        root->assign_left(left_Rotate(root->get_left()));  
        return right_Rotate(root);  
    }  
  
    // Right Right Case  
    if (balance < -1 && getBalance(root->get_right()) <= 0) 
     { 
        return left_Rotate(root);  
    }
    // Right Left Case  
    if (balance < -1 &&  
        getBalance(root->get_right()) > 0)  
    {  
        root->assign_right(right_Rotate(root->get_right()));  
        return left_Rotate(root);  
    }  
  
    return root;  
}
int leftcar(int r,float t,node1 *root,node1 *root0,node1* root1){  //finding the immediate left car of the given car
    
    node1 *p;
    node1 *k;
    //search the given node in the primary avial tree to get the position ,time & direction of given car
    p=search(r,root);
    
    node1 *m;
    //if car goes from left to right
    if(p->get_d()==1){
        k=root1;
        while(k!=NULL){
            if(k->get_r()==r){
                                //finding the closest car in the same direction
                //left child exists(a car to the left exists travelling in same direction)
                if(k->get_left()!=NULL){
                    k=k->get_left();
                    while(k->get_right()!=NULL){
                        k=k->get_right();
                    }
                    //searching for immediate left car among cars travelling in opposite direction
                    m=root0;
                    while(m!=NULL){
                        //if a car  is found between the given car and its leftmost car(only in the direction d=1) travelling in d=0
                        //if mis between p and k
                        //move to right until it gets closer to p
                        if(k->get_d()==1){
                            if((m->get_x()-(t-m->get_t())) < (p->get_x()+t-p->get_t()) && (m->get_x()-(t-m->get_t()))>=(k->get_x()+t-k->get_t())){
                                k=m;
                                m=m->get_right();
                            }
                            //if the given car is behind the predecessor (from d=1) of the given car
                            //move to right until we get between them
                            else if((m->get_x()-(t-m->get_t())) < (p->get_x()+t-p->get_t()) && (m->get_x()-(t-m->get_t()))<(k->get_x()+t-k->get_t())){
                                m=m->get_right();
                            }
                            //if m is to the right of p
                            //move to left
                            else if((m->get_x()-(t-m->get_t())) >= (p->get_x()+t-p->get_t()) && (m->get_x()-(t-m->get_t()))>(k->get_x()+t-k->get_t())){
                                m=m->get_left();
                            }
                        }
                        else{
                            if((m->get_x()-(t-m->get_t())) < (p->get_x()+t-p->get_t()) && (m->get_x()-(t-m->get_t()))>=(k->get_x()-(t-k->get_t()))){
                                k=m;
                                m=m->get_right();
                            }
                            else if((m->get_x()-(t-m->get_t())) < (p->get_x()+t-p->get_t()) && (m->get_x()-(t-m->get_t()))<(k->get_x()-(t-k->get_t()))){
                                m=m->get_right();
                            }
                            else if((m->get_x()-(t-m->get_t())) >= (p->get_x()+t-p->get_t()) && (m->get_x()-(t-m->get_t()))>(k->get_x()-(t-k->get_t()))){
                                m=m->get_left();
                            }
                        }
                    }
                    /*k is the required node*/
                    //it is the car to immediate left of given car
                    if(k->get_r()==r){      //returns -1 if no car is to the left of given car
                        return -1;
                    }
                    else{
                        return k->get_r();
                   }


                }
                // if the given car has no car in the left which is travelling in same direction as the given car
                //then we search in the opposite direction
                else if(k->get_parent()==NULL || k->get_parent()->get_left()==k){
                    m=root0;
                    while(m!=NULL){
                        //we compare the current position of the m and p
                        //if we get a car to the left the given car
                        //we move to its right to see if a more closer car exists
                        if((m->get_x()-(t-m->get_t()))<(p->get_x()+t-p->get_t())){
                            k=m;
                            m=m->get_right();
                            while(m!=NULL){
                                if((m->get_x()-(t-m->get_t())) < (p->get_x()+t-p->get_t()) && (m->get_x()-(t-m->get_t()))>=(k->get_x()-(t-k->get_t()))){
                                    k=m;
                                    m=m->get_right();
                                }
                                else if((m->get_x()-(t-m->get_t())) < (p->get_x()+t-p->get_t()) && (m->get_x()-(t-m->get_t()))<(k->get_x()-(t-k->get_t()))){
                                    m=m->get_right();
                                }
                                else if((m->get_x()-(t-m->get_t())) >= (p->get_x()+t-p->get_t()) && (m->get_x()-(t-m->get_t()))>(k->get_x()-(t-k->get_t()))){
                                    m=m->get_left();
                                }   
                            }
                            /*k is required car*/
                            if(k->get_r()==r){
                                 return -1;
                            }
                            else{
                                 return k->get_r();
                            }

                            
                        }   
                        else {
                            m=m->get_left();
                        }

                    }
                
                    /*k is required car*/
                    if(k->get_r()==r){
                        return -1;
                    }
                    else{
                        return k->get_r();
                   }

                }
                //parent node is the car to the car on the left of given car which is travelling in same direction
                else{
                    k=k->get_parent();
                    m=root0;
                    while(m!=NULL){
                        if(k->get_d()==1){
                            if((m->get_x()-(t-m->get_t())) < (p->get_x()+t-p->get_t()) && (m->get_x()-(t-m->get_t()))>=(k->get_x()+t-k->get_t())){
                                k=m;
                                m=m->get_right();
                            }
                            else if((m->get_x()-(t-m->get_t())) < (p->get_x()+t-p->get_t()) && (m->get_x()-(t-m->get_t()))<(k->get_x()+t-k->get_t())){
                                m=m->get_right();
                            }
                            else if((m->get_x()-(t-m->get_t())) >= (p->get_x()+t-p->get_t()) && (m->get_x()-(t-m->get_t()))>(k->get_x()+t-k->get_t())){
                                m=m->get_left();
                            }
                        }
                        else{
                            if((m->get_x()-(t-m->get_t())) < (p->get_x()+t-p->get_t()) && (m->get_x()-(t-m->get_t()))>=(k->get_x()-(t-k->get_t()))){
                                k=m;
                                m=m->get_right();
                            }
                            else if((m->get_x()-(t-m->get_t())) < (p->get_x()+t-p->get_t()) && (m->get_x()-(t-m->get_t()))<(k->get_x()-(t-k->get_t()))){
                                m=m->get_right();
                            }
                            else if((m->get_x()-(t-m->get_t())) >= (p->get_x()+t-p->get_t()) && (m->get_x()-(t-m->get_t()))>(k->get_x()-(t-k->get_t()))){
                                m=m->get_left();
                            }
                        }
                    }
                    /*k is required*/
                    if(k->get_r()==r){
                        return -1;
                    }
                    else{
                        return k->get_r();
                   }

                }
            }
            else if((k->get_x() +(t-k->get_t()))>(p->get_x() + t-p->get_t())){
                k=k->get_left();
            }
            else{
                k=k->get_right();
            }
        }
    }
    // if given car is travelling in right to left direction
    //same as previous case
    //just the direction of travel is different
    else{
        k=root0;
        while(k!=NULL){
            if(k->get_r()==r){
                
                if(k->get_left()!=NULL){
                    k=k->get_left();
                    while(k->get_right()!=NULL){
                        k=k->get_right();
                    }
                    
                    m=root1;
                    while(m!=NULL){
                        if(k->get_d()==0){
                            if((m->get_x()+(t-m->get_t())) < (p->get_x()-(t-p->get_t())) && (m->get_x()+(t-m->get_t()))>=(k->get_x()-(t-k->get_t()))){
                                k=m;
                                m=m->get_right();
                            }
                            else if((m->get_x()+(t-m->get_t())) < (p->get_x()-(t-p->get_t())) && (m->get_x()+(t-m->get_t()))<(k->get_x()-(t-k->get_t()))){
                                m=m->get_right();
                            }
                            else if((m->get_x()+(t-m->get_t())) >= (p->get_x()-(t-p->get_t())) && (m->get_x()+(t-m->get_t()))>(k->get_x()-(t-k->get_t()))){
                                m=m->get_left();
                            }
                        }
                        else{
                            if((m->get_x()+(t-m->get_t())) < (p->get_x()-(t-p->get_t())) && (m->get_x()+(t-m->get_t()))>=(k->get_x()+(t-k->get_t()))){
                                k=m;
                                m=m->get_right();
                            }
                            else if((m->get_x()+(t-m->get_t())) < (p->get_x()-(t-p->get_t())) && (m->get_x()+(t-m->get_t()))<(k->get_x()+(t-k->get_t()))){
                                m=m->get_right();
                            }
                            else if((m->get_x()+(t-m->get_t())) >= (p->get_x()-(t-p->get_t())) && (m->get_x()+(t-m->get_t()))>(k->get_x()+(t-k->get_t()))){
                                m=m->get_left();
                            }
                        }
                    }
                    /*k is the required node*/
                    if(k->get_r()==r){
                        return -1;
                    }
                    else{
                        return k->get_r();
                   }


                }
                else if(k->get_parent()==NULL || k->get_parent()->get_left()==k){
                    m=root1;
                    while(m!=NULL){
                        if((m->get_x()+(t-m->get_t()))<(p->get_x()-(t-p->get_t()))){
                            k=m;
                            m=m->get_right();
                            while(m!=NULL){
                                if((m->get_x()+(t-m->get_t())) < (p->get_x()-(t-p->get_t())) && (m->get_x()+(t-m->get_t()))>=(k->get_x()+(t-k->get_t()))){
                                    k=m;
                                    m=m->get_right();
                                }
                                else if((m->get_x()+(t-m->get_t())) < (p->get_x()-(t-p->get_t())) && (m->get_x()+(t-m->get_t()))<(k->get_x()+(t-k->get_t()))){
                                    m=m->get_right();
                                }
                                else if((m->get_x()+(t-m->get_t())) >= (p->get_x()-(t-p->get_t())) && (m->get_x()+(t-m->get_t()))>(k->get_x()+(t-k->get_t()))){
                                    m=m->get_left();
                                }   
                            }
                            
                            /*k is required*/
                            if(k->get_r()==r){
                                return -1;
                             }
                             else{
                                  return k->get_r();
                              }
                            
                        }   
                        else {
                            m=m->get_left();
                        }

                    }
                    
                    /*k is required*/
                    if(k->get_r()==r){
                        return -1;
                    }
                    else{
                        return k->get_r();
                   }
                }
                else{
                    k=k->get_parent();
                    m=root1;
                    while(m!=NULL){
                        if(k->get_d()==0){
                            if((m->get_x()+(t-m->get_t())) < (p->get_x()-(t-p->get_t())) && (m->get_x()+(t-m->get_t()))>=(k->get_x()-(t-k->get_t()))){
                                k=m;
                                m=m->get_right();
                            }
                            else if((m->get_x()+(t-m->get_t())) < (p->get_x()-(t-p->get_t())) && (m->get_x()+(t-m->get_t()))<(k->get_x()-(t-k->get_t()))){
                                m=m->get_right();
                            }
                            else if((m->get_x()+(t-m->get_t())) >= (p->get_x()-(t-p->get_t())) && (m->get_x()+(t-m->get_t()))>(k->get_x()-(t-k->get_t()))){
                                m=m->get_left();
                            }
                        }
                        else{
                            if((m->get_x()+(t-m->get_t())) < (p->get_x()-(t-p->get_t())) && (m->get_x()+(t-m->get_t()))>=(k->get_x()+(t-k->get_t()))){
                                k=m;
                                m=m->get_right();
                            }
                            else if((m->get_x()+(t-m->get_t())) < (p->get_x()-(t-p->get_t())) && (m->get_x()+(t-m->get_t()))<(k->get_x()+(t-k->get_t()))){
                                m=m->get_right();
                            }
                            else if((m->get_x()+(t-m->get_t())) >= (p->get_x()-(t-p->get_t())) && (m->get_x()+(t-m->get_t()))>(k->get_x()+(t-k->get_t()))){
                                m=m->get_left();
                            }
                        }
                    }
                    /*k is required*/
                    
                    if(k->get_r()==r){
                        return -1;
                    }
                    else{
                        return k->get_r();
                   }
                }
            }
            else if((k->get_x()-(t-k->get_t()))>(p->get_x() -(t-p->get_t()))){
                k=k->get_left();
            }
            else{
                k=k->get_right();
            }
        }
    }

}
//finding the rightmost car to the given car
//procedure is similar 

int rightcar(int r,float t,node1 *root,node1 *root0,node1* root1){
    
    node1 *p;
    node1 *k;
    //search in the primary avial tree to get position,time,direction
    p=search(r,root);
    node1 *m;
    if(p->get_d()==1){
        k=root1;
        while(k!=NULL){
            if(k->get_r()==r){
                
                if(k->get_right()!=NULL){
                    k=k->get_right();
                    while(k->get_left()!=NULL){
                        k=k->get_left();
                    }
                    
                    m=root0;
                    while(m!=NULL){
                        if(k->get_d()==1){
                            if((m->get_x()-(t-m->get_t())) > (p->get_x()+t-p->get_t()) && (m->get_x()-(t-m->get_t()))<=(k->get_x()+t-k->get_t())){
                                k=m;
                                m=m->get_left();
                            }
                            else if((m->get_x()-(t-m->get_t())) > (p->get_x()+t-p->get_t()) && (m->get_x()-(t-m->get_t()))>(k->get_x()+t-k->get_t())){
                                m=m->get_left();
                            }
                            else if((m->get_x()-(t-m->get_t())) <= (p->get_x()+t-p->get_t()) && (m->get_x()-(t-m->get_t()))<(k->get_x()+t-k->get_t())){
                                m=m->get_right();
                            }
                        }
                        else{
                            if((m->get_x()-(t-m->get_t())) > (p->get_x()+t-p->get_t()) && (m->get_x()-(t-m->get_t()))<=(k->get_x()-(t-k->get_t()))){
                                k=m;
                                m=m->get_left();
                            }
                            else if((m->get_x()-(t-m->get_t())) > (p->get_x()+t-p->get_t()) && (m->get_x()-(t-m->get_t()))>(k->get_x()-(t-k->get_t()))){
                                m=m->get_left();
                            }
                            else if((m->get_x()-(t-m->get_t())) <= (p->get_x()+t-p->get_t()) && (m->get_x()-(t-m->get_t()))<(k->get_x()-(t-k->get_t()))){
                                m=m->get_right();
                            }
                        }
                    }
                    /*k is the required node*/
                    if(k->get_r()==r){
                        return -1;
                    }
                    else{
                        return k->get_r();
                   } 
                }
                else if(k->get_parent()==NULL || k->get_parent()->get_right()==k){
                    m=root0;
                    while(m!=NULL){
                        if((m->get_x()-(t-m->get_t()))>(p->get_x()+t-p->get_t())){
                            k=m;
                            m=m->get_left();
                            while(m!=NULL){
                                if((m->get_x()-(t-m->get_t())) > (p->get_x()+t-p->get_t()) && (m->get_x()-(t-m->get_t()))<=(k->get_x()-(t-k->get_t()))){
                                    k=m;
                                    m=m->get_left();
                                }
                                else if((m->get_x()-(t-m->get_t())) > (p->get_x()+t-p->get_t()) && (m->get_x()-(t-m->get_t()))>(k->get_x()-(t-k->get_t()))){
                                    m=m->get_left();
                                }
                                else if((m->get_x()-(t-m->get_t())) <= (p->get_x()+t-p->get_t()) && (m->get_x()-(t-m->get_t()))<(k->get_x()-(t-k->get_t()))){
                                    m=m->get_right();
                                }   
                            }
                            /*k is required*/
                            if(k->get_r()==r){
                                 return -1;
                             }
                             else{
                                return k->get_r();
                             }

                            
                        }   
                        else {
                            m=m->get_right();
                        }

                    }
                    
                    /*k is required*/
                    if(k->get_r()==r){
                        return -1;
                    }
                    else{
                        return k->get_r();
                   }

                }
                else{
                    k=k->get_parent();
                    m=root0;
                    while(m!=NULL){
                        if(k->get_d()==1){
                            if((m->get_x()-(t-m->get_t())) > (p->get_x()+t-p->get_t()) && (m->get_x()-(t-m->get_t()))<=(k->get_x()+t-k->get_t())){
                                k=m;
                                m=m->get_left();
                            }
                            else if((m->get_x()-(t-m->get_t())) > (p->get_x()+t-p->get_t()) && (m->get_x()-(t-m->get_t()))>(k->get_x()+t-k->get_t())){
                                m=m->get_left();
                            }
                            else if((m->get_x()-(t-m->get_t())) <= (p->get_x()+t-p->get_t()) && (m->get_x()-(t-m->get_t()))<(k->get_x()+t-k->get_t())){
                                m=m->get_right();
                            }
                        }
                        else{
                            if((m->get_x()-(t-m->get_t())) > (p->get_x()+t-p->get_t()) && (m->get_x()-(t-m->get_t()))<=(k->get_x()-(t-k->get_t()))){
                                k=m;
                                m=m->get_left();
                            }
                            else if((m->get_x()-(t-m->get_t())) > (p->get_x()+t-p->get_t()) && (m->get_x()-(t-m->get_t()))>(k->get_x()-(t-k->get_t()))){
                                m=m->get_left();
                            }
                            else if((m->get_x()-(t-m->get_t())) <= (p->get_x()+t-p->get_t()) && (m->get_x()-(t-m->get_t()))<(k->get_x()-(t-k->get_t()))){
                                m=m->get_right();
                            }
                        }
                    }
                    /*k is required*/
                    if(k->get_r()==r){
                        return -1;
                    }
                    else{
                        return k->get_r();
                   }


                }
            }
            else if((k->get_x() +(t-k->get_t()))>(p->get_x() + t-p->get_t())){
                k=k->get_left();
            }
            else{
                k=k->get_right();
            }
        }
    }
    else{
        k=root0;
        while(k!=NULL){
            if(k->get_r()==r){
                
                if(k->get_right()!=NULL){
                    k=k->get_right();
                    while(k->get_left()!=NULL){
                        k=k->get_left();
                    }
                    
                    m=root1;
                    while(m!=NULL){
                        if(k->get_d()==0){
                            if((m->get_x()+(t-m->get_t())) > (p->get_x()-(t-p->get_t())) && (m->get_x()+(t-m->get_t()))<=(k->get_x()-(t-k->get_t()))){
                                k=m;
                                m=m->get_left();
                            }
                            else if((m->get_x()+(t-m->get_t())) > (p->get_x()-(t-p->get_t())) && (m->get_x()+(t-m->get_t()))>(k->get_x()-(t-k->get_t()))){
                                m=m->get_left();
                            }
                            else if((m->get_x()+(t-m->get_t())) <= (p->get_x()-(t-p->get_t())) && (m->get_x()+(t-m->get_t()))<(k->get_x()-(t-k->get_t()))){
                                m=m->get_right();
                            }
                        }
                        else{
                            if((m->get_x()+(t-m->get_t())) > (p->get_x()-(t-p->get_t())) && (m->get_x()+(t-m->get_t()))<=(k->get_x()+(t-k->get_t()))){
                                k=m;
                                m=m->get_left();
                            }
                            else if((m->get_x()+(t-m->get_t())) > (p->get_x()-(t-p->get_t())) && (m->get_x()+(t-m->get_t()))>(k->get_x()+(t-k->get_t()))){
                                m=m->get_left();
                            }
                            else if((m->get_x()+(t-m->get_t())) <= (p->get_x()-(t-p->get_t())) && (m->get_x()+(t-m->get_t()))<(k->get_x()+(t-k->get_t()))){
                                m=m->get_right();
                            }
                        }
                    }
                    /*k is the required node*/
                    if(k->get_r()==r){
                        return -1;
                    }
                    else{
                        return k->get_r();
                    }

                }
                else if(k->get_parent()==NULL || k->get_parent()->get_right()==k){
                    m=root1;
                    while(m!=NULL){
                        if((m->get_x()+(t-m->get_t()))>(p->get_x()-(t-p->get_t()))){
                            k=m;
                            m=m->get_left();
                            while(m!=NULL){
                                if((m->get_x()+(t-m->get_t())) > (p->get_x()-(t-p->get_t())) && (m->get_x()+(t-m->get_t()))<=(k->get_x()+(t-k->get_t()))){
                                    k=m;
                                    m=m->get_left();
                                }
                                else if((m->get_x()+(t-m->get_t())) > (p->get_x()-(t-p->get_t())) && (m->get_x()+(t-m->get_t()))>(k->get_x()+(t-k->get_t()))){
                                    m=m->get_left();
                                }
                                else if((m->get_x()+(t-m->get_t())) <= (p->get_x()-(t-p->get_t())) && (m->get_x()+(t-m->get_t()))<(k->get_x()+(t-k->get_t()))){
                                    m=m->get_right();
                                }   
                            }
                        
                            /*k is required*/
                            if(k->get_r()==r){
                                return -1;
                             }
                            else{
                                 return k->get_r();
                             }
                            
                        }   
                        else {
                            m=m->get_right();
                        }

                    }
                    
                    /*k is required*/
                    if(k->get_r()==r){
                        return -1;
                    }
                    else{
                        return k->get_r();
                   }
                }
                else{
                    k=k->get_parent();
                    m=root1;
                    while(m!=NULL){
                        if(k->get_d()==0){
                            if((m->get_x()+(t-m->get_t())) > (p->get_x()-(t-p->get_t())) && (m->get_x()+(t-m->get_t()))<=(k->get_x()-(t-k->get_t()))){
                                k=m;
                                m=m->get_left();
                            }
                            else if((m->get_x()+(t-m->get_t())) > (p->get_x()-(t-p->get_t())) && (m->get_x()+(t-m->get_t()))>(k->get_x()-(t-k->get_t()))){
                                m=m->get_left();
                            }
                            else if((m->get_x()+(t-m->get_t())) <= (p->get_x()-(t-p->get_t())) && (m->get_x()+(t-m->get_t()))<(k->get_x()-(t-k->get_t()))){
                                m=m->get_right();
                            }
                        }
                        else{
                            if((m->get_x()+(t-m->get_t())) > (p->get_x()-(t-p->get_t())) && (m->get_x()+(t-m->get_t()))<=(k->get_x()+(t-k->get_t()))){
                                k=m;
                                m=m->get_left();
                            }
                            else if((m->get_x()+(t-m->get_t())) > (p->get_x()-(t-p->get_t())) && (m->get_x()+(t-m->get_t()))>(k->get_x()+(t-k->get_t()))){
                                m=m->get_left();
                            }
                            else if((m->get_x()+(t-m->get_t())) <= (p->get_x()-(t-p->get_t())) && (m->get_x()+(t-m->get_t()))<(k->get_x()+(t-k->get_t()))){
                                m=m->get_right();
                            }
                        }
                    }
                    /*k is required*/
                    if(k->get_r()==r){
                        return -1;
                    }
                    else{
                        return k->get_r();
                   }
                }
            }
            else if((k->get_x()-(t-k->get_t()))>(p->get_x() -(t-p->get_t()))){
                k=k->get_left();
            }
            else{
                k=k->get_right();
            }
        }
    }

}
//finding the total left cars with the help of augmentation (maintaing left count while insertion and deletion)
int totalleftcars(int r,float t,node1* root,node1* root0,node1* root1){
    
    node1 *p;
    node1*k;
    node1*m;
    int count=0;
    //search in primary avial tree
    p=search(r,root);
    //check the direction
    //proceed with the help of left count of nodes
    if(p->get_d()==1){
        m=root1;
        while(m->get_r()!=r){
            if(m->get_x()+(t-m->get_t())<(p->get_x()+(t-p->get_t()))){
                count=count+(1+m->get_left_count());
                m=m->get_right();

            }
            else{
                m=m->get_left();
            }
        }
        count=count+m->get_left_count();
        m=root0;
        while(m!=NULL){
            if(m->get_x()-(t-m->get_t())<(p->get_x()+t-p->get_t())){
                count=count+(1+m->get_left_count());
                m=m->get_right();

            }
            else if(m->get_x()-(t-m->get_t())>(p->get_x()+t-p->get_t())){
                m=m->get_left();
            }
            else{
                count=count+m->get_left_count();
                return count;
            }
        }
        return count;
    }
    else{
        m=root0;
        while(m->get_r()!=r){
            if(m->get_x()-(t-m->get_t())<p->get_x()-(t-p->get_t())){
                count=count+(1+m->get_left_count());
                m=m->get_right();
            }
            else{
                m=m->get_left();
            }
        }
        count=count+m->get_left_count();
        m=root1;
        while(m!=NULL){
            if(m->get_x()+(t-m->get_t())<(p->get_x()-(t-p->get_t()))){
                count=count+(1+m->get_left_count());
                m=m->get_right();
            }
            else if(m->get_x()+(t-m->get_t())>(p->get_x()-(t-p->get_t()))){
                m=m->get_left();
            }
            else{
                count=count+m->get_left_count();
                return count;
            }
        }
        return count;
    }
}
//finding total cars on right
//maintaing the right count during insertion and deletion
//similar to the total leftcars case
int totalrightcars(int r,float t,node1*root,node1*root0,node1*root1){
    
    node1 *p;
    node1 *k;
    node1 *m;
    int count=0;
    p=search(r,root);
    if(p->get_d()==1){
        m=root1;
        while(m->get_r()!=r){
            if(m->get_x()+(t-m->get_t())>(p->get_x()+(t-p->get_t()))){
                count=count+(1+m->get_right_count());
                m=m->get_left();

            }
            else{
                m=m->get_right();
            }
        }
        count=count+m->get_right_count();
        m=root0;
        while(m!=NULL){
            if(m->get_x()-(t-m->get_t())>(p->get_x()+t-p->get_t())){
                count=count+(1+m->get_right_count());
                m=m->get_left();

            }
            else if(m->get_x()-(t-m->get_t())<(p->get_x()+t-p->get_t())){
                m=m->get_right();
            }
            else{
                count=count+m->get_right_count();
                return count;
            }
        }
        return count;
    }
    else{
        m=root0;
        while(m->get_r()!=r){
            if(m->get_x()-(t-m->get_t())>p->get_x()-(t-p->get_t())){
                count=count+(1+m->get_right_count());
                m=m->get_left();
            }
            else{
                m=m->get_right();
            }
        }
        count=count+m->get_right_count();
        m=root1;
        while(m!=NULL){
            if(m->get_x()+(t-m->get_t())>(p->get_x()-(t-p->get_t()))){
                count=count+(1+m->get_right_count());
                m=m->get_left();
            }
            else if(m->get_x()+(t-m->get_t())<(p->get_x()-(t-p->get_t()))){
                m=m->get_right();
            }
            else{
                count=count+m->get_right_count();
                return count;
            }
        }
        return count;
    }
}
int finalinsert(head *h,head *h0,head *h1,int r,float x,float t,int d){
    
    h->time=t;
    
    h0->time=t;
    
    h1->time=t;
    if(d==0){
        h->root=insert(h->root,r,x,t,d);
        h0->root=insert_0(h0->root,r,x,t,d);
    }
    else if(d==1){
        h->root=insert(h->root,r,x,t,d);
        h1->root=insert_1(h1->root,r,x,t,d);
    }
    return 1;
}
int remove(head *h,head *h0,head *h1,int r,float t){
    h->time=t;
    h0->time=t;
    h1->time=t;
    node1 *p;
    p=search(r,h->root);
    float x;
    if(p->get_d()==0){
        x=p->get_x()-(t-p->get_t());
        
    
       h->root= deleteNode(h->root,r,t);
       
        h0->root=deleteNode_0(h0->root,r,t,x);
        return 1;
    }
    else if(p->get_d()==1){
        x=p->get_x()+(t-p->get_t());
    
       h->root= deleteNode(h->root,r,t);
       h1->root=deleteNode_1(h1->root,r,t,x);
       return 1;
    }
    //return 1;
}
int immediate_left(int r,float t,head *h,head *h0,head *h1){
    h->time=t;
    h0->time=t;
    h1->time=t;
    int a;
    a=leftcar(r,t,h->root,h0->root,h1->root);
    return a;
}
int immediate_right(int r,float t,head *h,head *h0,head *h1){
    h->time=t;
    h0->time=t;
    h1->time=t;
    int a;
    a=rightcar(r,t,h->root,h0->root,h1->root);
    return a;
}
int cars_on_left(int r,float t,head *h,head *h0,head *h1){
    h->time=t;
    h0->time=t;
    h1->time=t;
    int a;
    a=totalleftcars(r,t,h->root,h0->root,h1->root);
    return a;
}
int cars_on_right(int r,float t,head *h,head *h0,head *h1){
    h->time=t;
    h0->time=t;
    h1->time=t;
    int a;
    a=totalrightcars(r,t,h->root,h0->root,h1->root);
    return a;
}
int number_of_crossings(head *h,head *h0,head *h1,int r,float t){
    node1 *p;
    p=search(r,h->root);
    float prev_time;
    prev_time=h->time;
    int c1,c2;
    if(p->get_d()==1){
        c1=cars_on_left(r,prev_time,h,h0,h1);
        c2=cars_on_left(r,t,h,h0,h1);
        
    }
    else{
        c1=cars_on_right(r,prev_time,h,h0,h1);
        c2=cars_on_right(r,t,h,h0,h1);
        
    }
    h->time=t;
    h0->time=t;
    h1->time=t;
    return c2-c1;
}
//printing the tree
void inorder(node1 *root)  
{  
    if(root != NULL)  
    {  
          //cout << root->get_r() << " "; 
        inorder(root->get_left());
        cout << root->get_r() << " ";
        inorder(root->get_right());  
    }  
}  

  
 
int main()  
{  
    head *h;
    head *h0;
    head *h1;
    h=new head();
    h0=new head();
    h1=new head();
    h->root=NULL;
    h0->root=NULL;
    h1->root=NULL;
    int r;
    float x;
    float t;
    int d;
    int i=1;
    int testcases;
    cin >> testcases;
    
    int n;
    while(i<=testcases){
    
        cin >> n;
        if(n==1){
            cin >> r;
            cin >> x;
            cin >> t;
            cin >> d;
            finalinsert(h,h0,h1,r,x,t,d);
        }
        else if(n==2){
            cin >> r;
            cin >> t;
            remove(h,h0,h1,r,t);
        }
        else if(n==3){
            cin >> r;
            cin >> t;
            int a;
            a=immediate_left(r,t,h,h0,h1);
            cout << a <<endl ;
        }
        else if(n==4){
            cin >> r;
            cin >> t;
            int b;
            b=immediate_right(r,t,h,h0,h1);
            cout << b <<endl ;
        }
        else if(n==5){
            cin >> r;
            cin >> t;
            int c;
            c=cars_on_left(r,t,h,h0,h1);
            cout << c <<endl ;
        }
        else if(n==6){
            cin >> r;
            cin >> t;
            int d;
            d=cars_on_right(r,t,h,h0,h1);
            cout << d <<endl ;
        }
        else if(n==7){
            cin >>r;
            cin >>t;
            int e;
            e=number_of_crossings(h,h0,h1,r,t);
            cout << e <<endl;
        }
        else{
            break;
        }
        i=i+1;
    }
    
}
