#include<stdio.h>
#include<stdlib.h>
struct node1
{
  int val;
  char colour;
  struct node1 *left;
  struct node1 *right;
  struct node1 *p;
};
typedef struct node1 node;
node *root;
node NIL={0,'b',NULL,NULL,NULL};
node * create_node(int );
void addnode(node **,node *);
void inorder(node *);
void fix(node *);
void left_rotate(node*);
void right_rotate(node*);
main()
{
  node *new;
  root=&NIL;
  int data;
  while(1){
    printf("Enter a number,-999 to stop\n");
    scanf("%d",&data);
    if(data==-999)
      break;
    else{
      new=create_node(data);
      if(root==&NIL)
	{
	  root=new;
	  root->colour='b';
	}
      else
	addnode(&root,new);
    }
  }
  
  inorder(root);
}
void inorder(node *root)
{
  if(root!=&NIL){
    inorder(root->left);
    printf("(%d,%c) ",root->val,root->colour);
    if(root->p!=&NIL)
      printf("%d\n",root->p->val);
    else
      printf("<--root\n");
    inorder(root->right);
  }
  
}
node * create_node(int data)
{
  node *temp;
  temp=(node*)malloc(sizeof(node));
  temp->val=data;
  temp->colour='r';
  temp->left=&NIL;
  temp->right=&NIL;
  temp->p=&NIL;
  return temp;
}

void addnode(node **y , node * new)
{
  if(*y==&NIL)
    {
      *y=new;
      fix(new);
    }
  else
    {
      if((*y)->val > new->val)
	{	new->p=*y;
	  addnode(&(*y)->left,new);
	  
	} 
      else
	{
	  new->p=*y;
	  addnode(&(*y)->right,new);
	  
	}
    }
}

void fix(node * new)
{
  node *uncle;
  while(new->p->colour=='r')
    {
      if(new->p==new->p->p->left)
	{
	  uncle=new->p->p->right;
	  if(uncle->colour=='r')
	    {
	      new->p->colour='b';
	      uncle->colour='b';
	      new->p->p->colour='r';
	      new=new->p->p;
	    }
	  else {
	    if(new == new->p->right)
	      {
		new=new->p;
		left_rotate(new);
	      }
	    new->p->colour='b';
	    new->p->p->colour='r';
	    right_rotate(new->p->p);
	  }
	}
      else
	{
	  uncle=new->p->p->left;
	if(uncle->colour=='r')
	    {
	      new->p->colour='b';
	      uncle->colour='b';
	      new->p->p->colour='r';
	      new=new->p->p;
	    }
	  else {
	    if(new == new->p->left)
	      {
		new=new->p;
		right_rotate(new);
	      }
	    new->p->colour='b';
	    new->p->p->colour='r';
	    left_rotate(new->p->p);
	  }
	}
    }
  root->colour='b';
}

void left_rotate(node *x)
{
  node *y;
  y=x->right;
  x->right=y->left;
  if(y->left!=&NIL)
    y->left->p=x;
  y->p=x->p;
  if (x->p==&NIL)
    root=y;
  else if(x==x->p->left)
    x->p->left=y;
  else
    x->p->right=y;
  y->left=x;
  x->p=y;
}

void right_rotate(node *x)
{
 node *y;
  y=x->left;
  x->left=y->right;
  if(y->right!=&NIL)
    y->right->p=x;
  y->p=x->p;
  if (x->p==&NIL)
    root=y;
  else if(x==x->p->right)
    x->p->right=y;
  else
    x->p->left=y;
  y->right=x;
  x->p=y;
}
