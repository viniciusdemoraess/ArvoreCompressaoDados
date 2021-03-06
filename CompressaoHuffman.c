#include "compressaoHuffman.h" 
// adiciona um novo n� na �rvore 
int add(TreeNode **root, void *element, TreeComparator f) {
    if ((*root) == NULL) {
        // alcan�ou o local da folha, atualiza o pai
        TreeNode *newnode = (TreeNode *) malloc(sizeof(TreeNode));
        if (newnode == NULL)
            return 0;
        newnode->element = element;
        newnode->left = newnode->right = NULL;
        *root = newnode;
        return 1;
    }
    
    int compvalue = f(element, (*root)->element);
    if (compvalue > 0) {
        return add(&(*root)->right, element, f);
    } else if (compvalue < 0) {
        return add(&(*root)->left, element, f);
    } else {
        return -1;
    }
    
}

// busca binaria na arvore 
int find(TreeNode *root, void *key, TreeComparator f, void **element) {
    int compvalue;
    
    // Passamos a folha
    if (root == NULL)
        return 0;
    
    compvalue = f(key, root->element);
    if (compvalue == 0) {
        // encontrado
        *element = root->element;
        return 1;
    }
    
    // desce no nivel da arvore
    if (compvalue > 0)
        return find(root->right, key, f, element);
    
    return find(root->left, key, f, element);
}

//impressão dos elementos por ordem crescente 
void in_order(TreeNode *root, printNode print) {
    if (root!=NULL) {
        in_order(root->left, print); //percorre pela esquerda até encontrar NULL 
        print(root->element); //imprime a raiz
        in_order(root->right, print); //percorre para direita até encontrar NULL
    }
}
//impressão dos elementos na forma posfixa  
void pre_order(TreeNode *root, printNode print) {
    if (root!=NULL) {
        print(root->element); //imprime raiz
        pre_order(root->left, print); //percorre até o elemento mais a esquerda
        pre_order(root->right, print); //percorre até o elemento mais a direita
    }
}
//Exibe os elementos da árvore na ordem Esquerda Direita Raiz 
void post_order(TreeNode *root, printNode print) {
    if(root!=NULL) {
        post_order(root->left, print);
        post_order(root->right, print);
        print(root->element);
    }
}

//greaterRight 
TreeNode *greaterRight(TreeNode **no) {
    if((*no)->right!=NULL){
        return greaterRight(&(*no)->right);
    }else{
        TreeNode *aux = *no;
        //se não houver essa verificação, esse nó vai perder todos os seus filhos da esquerda
        if((*no)->left!=NULL){
            *no = (*no)->left;
        }else{
            *no = NULL;
        }
        return aux;
    }
}
//funcao smallerLeft 
TreeNode *smallerLeft(TreeNode **no){
    if((*no)->left != NULL)
        return smallerLeft(&(*no)->left);
    else{
        TreeNode *aux = *no;
        if((*no)->right != NULL){ // se nao houver essa verificacao, esse nó vai perder todos os seus filhos da direita!
            *no = (*no)->right;
        }else
            *no = NULL;
        return aux;
    }
}

//remove um nó/elemento da arvore binaria
int removeTreeNode(TreeNode **root, void *key, TreeComparator f) {
    if(*root == NULL){   // caso a chave nao exista na arvore
        return 0;
    }
    int compvalue = f(key, (*root)->element);
    if(compvalue < 0){
        removeTreeNode(&(*root)->left, key, f);
    }else {
        if(compvalue > 0) {
            removeTreeNode(&(*root)->right, key, f);
        } else {    // se nao eh igual
            TreeNode *aux = *root;
            // Se nao tem filhos
            if (((*root)->left == NULL) && ((*root)->right == NULL)){
                free(aux);
                (*root) = NULL;
            }
            else{ // so tem o filho da direita
                if ((*root)->left == NULL){
                    (*root) = (*root)->right;
                    aux->right = NULL;
                    free(aux);
                    aux = NULL;
                }
                else{ //so tem filho da esquerda
                    if ((*root)->right == NULL){
                        (*root) = (*root)->left;
                        aux->left = NULL;
                        free(aux); 
                        aux = NULL;
                    }
                    else{ //Busco o maior filho à direita da subarvore esquerda.
                        aux = greaterRight(&(*root)->left);
                        aux->left = (*root)->left;
                        aux->right = (*root)->right;
                        (*root)->left = (*root)->right = NULL;
                        free((*root));  *root = aux;  aux = NULL;
                    }
                }
            }
        }
    }
    return 1;
}

// Calcula a altura da ávore/subárvore 
int height (TreeNode *root) {
    if (root == NULL)
        return -1; // a árvore está vazia
    else {
        int hl = height(root->left);// calcula a altura da esquerda
        int hr = height(root->right);// calcula a altura da direita
        if (hl < hr) return hr + 1; 
        else return hl + 1;
    }
}

// Destroi a arvore e navegar em pos-ordem 
void destroy (TreeNode **root) {
    if (*root==NULL) return;
    destroy(&(*root)->left);
    destroy(&(*root)->right);
    free(*root);
    *root=NULL;
}