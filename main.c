#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include<string.h>
//Definition de la structure
   typedef struct node
    {
      int val;
      struct node *link;
    }node;
//Def de fonction de creation
node *creation(int n ,char t[]){

//La fonction de creation de "Nodes"

node * HEAD=NULL;
node * TEMP=NULL;
node * P=NULL;

for(int i=0;i<n;i++){

    TEMP=(node*)malloc(sizeof(node));
    TEMP->val=t[i];
    TEMP->link=NULL;

    if(HEAD==NULL){
        HEAD=TEMP;
    }else{

    P=HEAD;
    while(P->link != NULL){
        P = P->link;
    }//Loop
    P->link=TEMP;

    }//else


}
   return HEAD;
}

void display(node *HEAD){

node * P=HEAD;

    while(P!=NULL)
    {
       printf("%d->",P->val);
       P=P->link;
    }



}
//fonction de inverse
node *inv(node *head){
node *Queue,*p;

    Queue=head->link;
    head->link=NULL;
    while(Queue != NULL){
    p=Queue;
    Queue=Queue->link;
    p->link=head;
    head=p;
    }

return head;
}
//Fonction d'ajout node pour la list de resault
node *push(node* head,int val){
node * newp = (node*)malloc(sizeof(node));
newp->val=val;
newp->link=head;
head=newp;
return head;

}

//La fonction d'addition
node *addition(node *head1,node *head2){

if(head1->val==0)
    return head2;
if(head2->val==0)
    return head1;


    node *ptr1 =head1;
    node *ptr2 =head2;
    node *head3 =NULL;
    int carry=0,sum;

    while(ptr1||ptr2){
    sum=0;
    if(ptr1)
         sum += ptr1->val;
    if(ptr2)
         sum += ptr2->val;

    sum +=carry;
    carry=sum/10;
    sum=sum%10;

    head3=push(head3,sum);

    if(ptr1)
         ptr1=ptr1->link;
    if(ptr2)
         ptr2=ptr2->link;
        }
    if(carry)
       head3=push(head3,carry);

    return head3;



}

node* newNode(int val)
{
	node* temp = (node*)malloc(sizeof(node));
	temp->val = val;
	temp->link = NULL;
	return temp;
}


/* A utility function to get length
of linked list */
int getLength(node* Node)
{
	int size = 0;
	while (Node != NULL) {
		Node = Node->link;
		size++;
	}
	return size;
}

/* A Utility that padds zeros in front of the
Node, with the given diff */
node* paddZeros(node* sNode, int diff)
{
	if (sNode == NULL)
		return NULL;

	node* zHead = newNode(0);
	diff--;
	node* temp = zHead;
	while (diff--) {
		temp->link = newNode(0);
		temp = temp->link;
	}
	temp->link = sNode;
	return zHead;
}

/* Subtract LinkedList Helper is a recursive function,
move till the last Node, and subtract the digits and
create the Node and return the Node. If d1 < d2, we
borrow the number from previous digit. */
static bool borrow;
node* subtractLinkedListHelper(node* l1, node* l2)
{

	if (l1 == NULL && l2 == NULL && borrow == 0)
		return NULL;

	node* previous = subtractLinkedListHelper(l1 ? l1->link : NULL, l2 ? l2->link : NULL);

	int d1 = l1->val;
	int d2 = l2->val;
	int sub = 0;

	/* if you have given the value to next digit then
	reduce the d1 by 1 */
	if (borrow) {
		d1--;
		borrow = false;
	}

	/* If d1 < d2, then borrow the number from previous
	digit. Add 10 to d1 and set borrow = true; */
	if (d1 < d2) {
		borrow = true;
		d1 = d1 + 10;
	}

	/* subtract the digits */
	sub = d1 - d2;

	/* Create a Node with sub value */
	node* current = newNode(sub);

	/* Set the Next pointer as Previous */
	current->link = previous;

	return current;
}

/* This API subtracts two linked lists and returns the
linked list which shall have the subtracted result. */
node* subtract(node* l1, node* l2)
{
	// Base Case.
	if (l1 == NULL && l2 == NULL)
		return NULL;

	// In either of the case, get the lengths of both
	// Linked list.
	int len1 = getLength(l1);
	int len2 = getLength(l2);

	node *lNode = NULL, *sNode = NULL;

	node* temp1 = l1;
	node* temp2 = l2;

	// If lengths differ, calculate the smaller Node
	// and padd zeros for smaller Node and ensure both
	// larger Node and smaller Node has equal length.
	if (len1 != len2) {
		lNode = len1 > len2 ? l1 : l2;
		sNode = len1 > len2 ? l2 : l1;
		sNode = paddZeros(sNode, abs(len1 - len2));
	}

	else {
		// If both list lengths are equal, then calculate
		// the larger and smaller list. If 5-6-7 & 5-6-8
		// are linked list, then walk through linked list
		// at last Node as 7 < 8, larger Node is 5-6-8
		// and smaller Node is 5-6-7.
		while (l1 && l2) {
			if (l1->val != l2->val) {
				lNode = l1->val > l2->val ? temp1 : temp2;
				sNode = l1->val > l2->val ? temp2 : temp1;
				break;
			}
			l1 = l1->link;
			l2 = l2->link;
		}
	}
	// If both lNode and sNode still have NULL value,
	// then this means that the value of both of the given
	// linked lists is the same and hence we can directly
	// return a node with value 0.
	if (lNode == NULL && sNode == NULL) {
		return newNode(0);
	}
	// After calculating larger and smaller Node, call
	// subtractLinkedListHelper which returns the subtracted
	// linked list.
	borrow = false;
	return subtractLinkedListHelper(lNode, sNode);
}


//Multiplier deux listes
long long multiplier(node* premier, node* deux)
{
    long long N = 1000000007;
    long long num1 = 0, num2 = 0;
    while (premier || deux) {

        if (premier) {
            num1 = ((num1)*10) % N + premier->val;
            premier = premier->link;
        }

        if (deux) {
            num2 = ((num2)*10) % N + deux->val;
            deux = deux->link;
        }
    }
    return ((num1 % N) * (num2 % N)) % N;
}

//The main programm
int main()
{
     node *Tete,*Tete1,*resault, *Queue, *p,*sub1=NULL,*sub2=NULL;




    int n=0,x,i=1,x2,n2,n3,n4,tt;
    Tete=NULL;
    Queue=NULL;
    //printf("Donner la Taille de nombre 1  : ");
    printf("Donner le nombre 1 : ");
    scanf("%d",&n);
    printf("Donner le nombre 2 : ");
    scanf("%d",&n2);
    tt=n;
    n3=tt;
    n4=n2;
    i=0;
    while(n3!=0){
    n3=n3/10;
    i=i+1;
    }
    x=i;
    i=0;
    while(n4!=0){
    n4=n4/10;
    i=i+1;
    }
    x2=i;

    //printf("Donner la Taille de nombre 2  : ");
    //scanf("%d",&x2);
    char T1[x];
    char T2[x2];
    n4=n2;
    //scanf("%d",&x);


   // n=atoi(T1);
    //n2=atoi(T2);
    //printf("%d",n);
    i=1;
    while(n!=0){
    T1[x-i]=n%10;
    n=n/10;
    i=i+1;
    }
    i=1;
    while(n2!=0){
    T2[x2-i]=n2%10;
    n2=n2/10;
    i=i+1;
    }
    Tete=creation(x,T1);
    Tete1=creation(x2,T2);
    printf("La liste represente avec :\n");
    display(Tete);
    printf("\nLa liste represente avec :\n");
    display(Tete1);
    //inverser la liste
    Tete=inv(Tete);
    Tete1=inv(Tete1);
    printf("\napres la inverse :\n");
    display(Tete);
    printf("\napres la inverse :\n");
    display(Tete1);
    resault=addition(Tete,Tete1);
    printf("\napres l'addition :\n");
    display(resault);
    //resault=NULL;
    /*resault=creation(x,T1);
    bool done;
    while(Tete1!=NULL&&Tete!=NULL){
    int v1,v2;

    v1=Tete->val;
    if(done==true)
    v2=Tete1->val+1;
    else
    v2=Tete1->val;
    if((v1)>(v2) ){
    resault->val=v1-v2;
    done=false;
    }else{
    resault->val=(v1+10)-v2;
    done=true;
    }
    Tete=Tete->link;

    Tete1=Tete1->link;
    resault=resault->link;

    }*/
int tem;
i=0;
 while(i<x)
    {
        tem=T1[i];
        p=newNode(tem);
        if (sub1==NULL)
        {
            sub1=p;
        }
        else
        {
            Queue->link=p;
        }
        Queue=p;
        i=i+1;
    }
i=0;
    while(i<x)
    {
        tem=T2[i];
        p=newNode(tem);
        if (sub2==NULL)
        {
            sub2=p;
        }
        else
        {
            Queue->link=p;
        }
        Queue=p;
        i=i+1;
    }
    p=sub1;

resault = subtract(sub1, sub2);
if(resault!=NULL){
        printf("\napres la soustraction :\n");
    display(resault);
}else
printf("\nNULL");
//Multiplier deux nombres

tem=multiplier(sub1,sub2);
printf("\nApres la multiplication :\n");

int tem1=tem;
    i=1;
    while(tem1!=0){
    tem1=tem1/10;
    i=i+1;
    }
    n3=i;
    char T3[n3];

    i=1;
    while(tem!=0){
    T3[n3-i]=tem%10;
    tem=tem/10;
    i=i+1;
    }



node *resautat_multi=creation(n3-1,T3);
display(resautat_multi);
//division
n3=tt;

int div=n3/n4;
tem1=div;
    i=0;
    while(tem1!=0){
    tem1=tem1/10;
    i=i+1;
    }
    tem1=i;
    char T4[tem];

    i=1;
    while(div!=0){
    T4[tem1-i]=div%10;
    div=div/10;
    i=i+1;
    }
    node *division=creation(tem1,T4);
    printf("\n");
    printf("Apres la division :\n");

    display(division);
    return 0;
}

// By Moh allali 
//GG_s
