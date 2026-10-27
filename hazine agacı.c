#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    int hazine;              //1 ise o dugumde hazýne var 0 ise hazýne yok
    struct Node *left;
    struct Node *right;
} Node;

Node *newNode(int value, int hazineMi) {
    Node *n = (Node *)malloc(sizeof(Node));
    n->data = value;
    n->hazine = hazineMi;
    n->left = NULL;
    n->right = NULL;
    return n;
}

Node *insert(Node *root, int value, int hazineMi) {
    if (root == NULL)
        return newNode(value, hazineMi);
    if (value < root->data)
        root->left = insert(root->left, value, hazineMi);
    else if (value > root->data)
        root->right = insert(root->right, value, hazineMi);
    return root;
}

/* Rekursif arama. Sayi agacta bulunur ve o dugumde hazine varsa 1 dondurur.
   soru 1: Her adimda ziyaret edilen dugumu ekrana yazar. */
int hazineAra(Node *root, int deger, int adim) {
    if (root == NULL)
        return 0;

    printf("Adim %d: %d dugumu ziyaret edildi\n", adim, root->data);

    if (deger == root->data)
        return root->hazine;
    if (deger < root->data)
        return hazineAra(root->left, deger, adim + 1);
    return hazineAra(root->right, deger, adim + 1);
}

/* soru 2: Agac yuksekligi = en uzun yoldaki dugum sayisi.
   En kotu durumda hazineyi bulmak icin gereken adim sayisi budur. */
int yukseklik(Node *root) {
    if (root == NULL)
        return 0;
    int sol = yukseklik(root->left);
    int sag = yukseklik(root->right);
    return 1 + (sol > sag ? sol : sag);
}

void freeTree(Node *root) {
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void) {
    Node *root = NULL;
    int degerler[] = {50, 30, 70, 20, 40, 60, 80};
    int hazineMi[] = { 0,  1,  0,  0,  1,  1,  0};   //30, 40 ve 60 ta hazine var 
    int n = sizeof(degerler) / sizeof(degerler[0]);
    int i;
    int sayi;

    for (i = 0; i < n; i++)
        root = insert(root, degerler[i], hazineMi[i]);

    printf("Bir sayi giriniz: ");
    if (scanf("%d", &sayi) != 1) {
        printf("Gecersiz giris!\n");
        freeTree(root);
        return 1;
    }

    if (hazineAra(root, sayi, 1))
        printf("Hazine bulundu!\n");
    else
        printf("Bosuna kazdin!\n");

    printf("En kotu durumda gereken adim sayisi (agac yuksekligi): %d\n",
           yukseklik(root));

    freeTree(root);
    return 0;
}
