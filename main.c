#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{

  char word[40];
  struct node *left;
  struct node *right;
  struct node *parent;
};
/* allocates a new node with the given data and NULL left,
   right and parent  pointers */
struct node *newNode(char data[])
{
    struct node *temp =  (struct node *)malloc(sizeof(struct node));
    strcpy(temp->word,data);
    temp->left = temp->right = temp->parent = NULL; ;
    return temp;
}

// to insert a new node with given word in BST
struct node* insert(struct node* node, char word[])
{
    //If the tree is empty, return a new node
    if (node == NULL) return newNode(word);
    // Otherwise, recur down the tree
    else
        {
            struct node *temp; // temp to save parent
    // insert left
    if ( 0 > strcmp(word, node->word))
        {
         temp = insert(node->left, word);
         node->left  = temp;
         temp->parent= node;
        }
    // insert right
    else if ( 0 < strcmp(word, node->word))
        {
        temp = insert(node->right, word);
        node->right = temp;
        temp->parent = node;
        }
        //return the (unchanged) node pointer
        return node;
       }

}
// print tree from a given node if needed
void inorder(struct node *root)
{
    if (root != NULL)
    {

        inorder(root->left);
        printf("%s\n", root->word);
        inorder(root->right);
    }
}
struct node *root = NULL, *temp, *succ, *min, *pred, *max;
 void load(FILE *f)
 {

    int i = 0;
    char w[40];

        while(!feof(f))
        {
             fscanf(f,"%s",w);
            // to insert the ROOT
            if(i==0)
                {
                root = insert(root,w);
                }
            insert(root,w);
            fscanf(f,"\n");
            i++;

        }

        fclose(f);

}
/* Computes the number of nodes in a tree. */
int size(struct node* node)
{
  if (node==NULL)
    return 0;
  else
    return(size(node->left) + 1 + size(node->right));
}
int maxDepth(struct node* node)
{
   if (node==NULL)
       return 0;
   else
   {
       /* compute the depth of each subtree */
       int lDepth = maxDepth(node->left);
       int rDepth = maxDepth(node->right);

       /* use the larger one */
       if (lDepth > rDepth)
           return(lDepth+1);
       else return(rDepth+1);
   }
}
int r = 0;
int l = 0;
// search a given word in a given BST
struct node* search(struct node* root, char word[])
{
    // Base Cases: root is null or key is present at root
    if (root == NULL ||  0 == strcmp(word, root->word))
       return root;


    // Key is greater than root's key
    else if ( 0 < strcmp(word, root->word))
        {
            // stop point in right subtree
            if(root->right == NULL)
            {
                return root;
            }
        r++;
        return search(root->right, word);

        }
    // Key is smaller than root's key
    else if ( 0 > strcmp(word, root->word))
        {
            // stop point in left subtree
            if(root->left == NULL)
            {
                return root;
            }
        l++;
        return search(root->left, word);
        }
}
struct node * minValue(struct node* node);

struct node * inOrdersuccessor(struct node *root, struct node *n)
{
  // the minimum value in the right subtree
  if( n->right != NULL )
    return minValue(n->right);

  // if node does not have right subtree..
  struct node *p = n->parent;
  // loop until n is left child of parent successor is parent
  while(p != NULL && n == p->right)
  {

     n = p;
     p = p->parent;
  }

  return p;
}
struct node *maxValue(struct node* node);

struct node * inOrderpredecessor(struct node *root, struct node *n)
{
   // the maximum value in the left subtree
  if( n->left != NULL )
    return maxValue(n->left);

  // if node does not have left subtree..
  struct node *p = n->parent;
  // loop until n is right child of parent predecessor is parent
  while(p != NULL && n == p->left)
  {

     n = p;
     p = p->parent;
  }

  return p;
}

// return the minimum data value found in that tree
struct node * minValue(struct node* node)
{
  struct node* current = node;

  /* loop down to find the leftmost leaf */
  while (current->left != NULL) {
    current = current->left;
  }
  return current;
}
// return the maximum data value found in that tree
struct node * maxValue(struct node* node)
{
  struct node* current = node;

  /* loop down to find the rightmost leaf */
  while (current->right != NULL) {
    current = current->right;
  }
  return current;
}
// split sentence and pass each word for spelling check;
void splitSentence (char word[])
{
 // space as delimiter
	char delim[] = " ";

	char *ptr = strtok(word, delim);

	while(ptr != NULL)
	{
	    //check current word
		checkWord(ptr);
		ptr = strtok(NULL, delim);
	}
}
// check word spelling and prints suggestions if wrong
void checkWord (char word[])
{
    // if word is correct
    if( 0 == strcmp(search(root,word)->word,word) )
        {
        printf(" + %s - ",search(root,word)->word);
        printf("CORRECT\n");
        }
    // if word is incorrect
    else
        {
        temp = search(root,word);
        succ = inOrdersuccessor(root, temp);
        pred = inOrderpredecessor(root, temp);
        printf(" + %s - %s,%s,%s\n",word,temp->word,succ->word,pred->word);
        }

}
int main()
{

    char wo[40];
    FILE *f;
    f = fopen("file.txt","r");
    load(f);

    printf("Size of the tree is %d\n", size(root));
    printf("Height of tree is %d\n", maxDepth(root));
    while(1)
    {
    // scan input sentence and send it to be split and checked
    printf("Enter Input:\n");
    gets(wo);
    splitSentence(wo);
    //r = 0;
    //l = 0;
    }
}
