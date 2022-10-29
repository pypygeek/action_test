#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char word[128];        // 구조체 : 데이터 형식
    char meaning[256];
} element;
typedef struct TreeNode
{
    element key;       // 구조체 : 노드의 구조
    struct TreeNode *left, *right;
} TreeNode;
 
int compare(element b, element a);
void display(TreeNode *p);
TreeNode * search(TreeNode * r, element k);
TreeNode * new_node(element i);
TreeNode *insert_node(TreeNode *n, element k);
TreeNode * min_value_node(TreeNode * n);
TreeNode * delete_node(TreeNode * r, element k);
void help();
void menu();
int fileShow();
int fileStore(char word[128], char mean[256]);
 
void main()
{
    menu();
    fileShow();
}
int fileStore(char word[128], char mean[256])
{
    FILE  *fp;
    fopen_s(&fp, "c:\\data\\a.txt", "a");
    fprintf(fp, "%s\n", word);
    fprintf(fp, "%s\n", mean);
    fclose(fp);
    return 0;
}
int fileShow()
{
    char test[256];
    char c;
    int line=0;
    FILE *fp = 0;    
    fopen_s(&fp, "c:\\data\\a.txt", "r");
    if (fp == 0)
    {
        printf("파일 열기 실패\n");
        return 0;
    }    
    while ((c = getc(fp)) != EOF)
    {
        if (c == '\n')
        {
            line++;
        }
    }
    fclose(fp);
    fopen_s(&fp, "c:\\data\\a.txt", "r");
    printf("%d", line);
    for (int i = 0; i < line; i++)
    {
        fgets(test, 128, fp);        
        printf("파일 내용[%d] : %s\n", i, test);
    }    
    fclose(fp);
    return 0;
}
int compare(element e1, element e2)
{
    // strcmp(1, 2) : 1 > 2 = 양수, 1 < 2 = 0 음수,  1 == 2 = 0
    return strcmp(e1.word, e2.word);
}
void display(TreeNode *p)
{
    if (p != NULL)  //트리 구조 출력
    {
        printf("(");
        display(p->left);
        printf("%s", p->key.word);
        display(p->right);
        printf(")");
    }
}
TreeNode * search(TreeNode * root, element key)
{
    TreeNode * p = root;   //// 이진 탐색 트리 탐색 함수
    while (p != NULL)
    {
        if (compare(key, p->key) == 0)
        {
            return p;
        }
        else if (compare(key, p->key) < 0)
        {
            p = p->left;
        }
        else if (compare(key, p->key) > 0)
        {
            p = p->right;
        }
    }
    return p;     // 탐색에 실패했을 경우 NULL 반환
}
TreeNode * new_node(element item)
{
    TreeNode * temp = (TreeNode *)malloc(sizeof(TreeNode));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}
TreeNode *insert_node(TreeNode *node, element key)
{    // 트리가 공백이면 새로운 노드를 반환한다. 
    char word[128];
    char mean[256];
    if (node == NULL)
    {
        strcpy_s(word, sizeof(key.word), key.word);
        strcpy_s(mean, sizeof(key.meaning), key.meaning);
        fileStore(word, mean);
        return new_node(key);
    }
    // 그렇지 않으면 순환적으로 트리를 내려간다. 
    if (compare(key, node->key) < 0)
    {
        node->left = insert_node(node->left, key);
    }
    else if (compare(key, node->key) > 0)
    {
        node->right = insert_node(node->right, key);
    }
    // 루트 포인터를 반환한다. 
 
    strcpy_s(word, sizeof(key.word), key.word);
    strcpy_s(mean, sizeof(key.meaning), key.meaning);
    fileStore(word, mean);
    return node;
}
TreeNode * min_value_node(TreeNode * node)
{
    TreeNode * current = node;
    // 맨 왼쪽 단말 노드를 찾으러 내려감
    while (current->left != NULL)
    {
        current = current->left;
    }
    return current;
}
// 이진 탐색 트리와 키가 주어지면 키가 저장된 노드를 삭제하고 
// 새로운 루트 노드를 반환한다. 
TreeNode * delete_node(TreeNode * root, element key)
{
    if (root == NULL)
    {
        return root;
    }
    // 만약 키가 루트보다 작으면 왼쪽 서브 트리에 있는 것임
    if (compare(key, root->key) < 0)
    {
        root->left = delete_node(root->left, key);
    }
    // 만약 키가 루트보다 크면 오른쪽 서브 트리에 있는 것임
    if (compare(key, root->key) > 0)
    {
        root->right = delete_node(root->right, key);
    }
    // 키가 루트와 같으면 이 노드를 삭제하면 됨
    else
    {
        // 첫 번째나 두 번째 경우
        if (root->left == NULL)
        {
            TreeNode * temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            TreeNode * temp = root->left;
            free(root);
            return temp;
        }
        // 세 번째 경우
        TreeNode * temp = min_value_node(root->right);
        // 중외 순회시 후계 노드를 복사한다. 
        root->key = temp->key;
        // 중외 순회시 후계 노드를 삭제한다. 
        root->right = delete_node(root->right, temp->key);
    }
    return root;
}
void help()
{
    printf("\n**** i: 입력, d: 삭제, s: 탐색, p: 출력, q: 종료 ****: ");
}
void menu()
{
    char command;
    element e;
    TreeNode * root = NULL;
    TreeNode * tmp;
 
    do
    {
        help();
        command = getchar();
        getchar();        // 엔터키 제거
        switch (command) {
        case 'i':
            printf("단어:");
            gets_s(e.word, sizeof(e.word));
            printf("의미:");
            gets_s(e.meaning, sizeof(e.meaning));
            root = insert_node(root, e);
            break;
 
        case 'd':
            printf("단어:");
            gets_s(e.word, sizeof(e.word));
            root = delete_node(root, e);
            break;
 
        case 'p':
            display(root);
            printf("\n");
            break;
 
        case 's':
            printf("단어:");
            gets_s(e.word, sizeof(e.word));
            tmp = search(root, e);
            if (tmp != NULL)
            {
                printf("의미:%s\n", tmp->key.meaning);
            }
            break;
        }
    } while (command != 'q');
