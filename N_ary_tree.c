#include <stdio.h>
#include <stdlib.h>

typedef struct tree{
    float data;
    struct tree *father;
    struct tree *child;
    struct tree *brother;
}Node;


Node *new_node(float key)
{
    Node *new_node = malloc(sizeof(Node));
    new_node -> data = key;
    new_node -> father = NULL;
    new_node -> child = new_node -> brother = NULL;
    return new_node;
}

void *add_child(struct tree *root, float key)// мы через find найдем root и ему присобачим новую ноду new_root в которую положим key
{
    Node *new_root = malloc(sizeof(Node));
    new_root = new_node(key);
    new_root->father = root; // отец Nroot это root

    if(!root->child) // root->child == NULL  Если ребенок у ноды нулевой
        root -> child = new_root;

    else // если ребенок у ноды ненулевой
    {
        root = root -> child; // перейдем к ребенку. root это теперь ребенок
        while(root->brother) // root->brother != NULL
            root = root -> brother;  // дошли до последней ненудевлой ноды
        root -> brother = new_root; // забили в нулевого брата ноду new_root
    }
}

Node* find_node(struct tree *root_1, int pos){
    // stop case
    if (root_1 == NULL) // если не нашли root_1
        return NULL;

    if (root_1->data == pos) // если нашли
        return root_1;
    // first we'll recurse on the siblings
    struct tree *found;
    found=find_node(root_1->brother,pos); // начинаем обход с брата. Зачем отдельная структура хз (на самом деле чтобы избежать множества terurn из за матрешки с child). У меня снизу без нее, но там некрасивый ретерн последней строчкой

    if ( found != NULL )
        return found;
    // if not found we recurse on the children
    return find_node(root_1->child, pos);
}

/* Ниже моя реализация. Может она будет понятнее. Я над ней чет долго тупил. Нафига. Тупой. Но может быть понятнее
Node *find_node(struct tree * root_1, float pos) // ищем root_1 это нода к которой нам нужно прицепить ребенка. У этой ноды ключ pos (position)
{
    if(root_1 == NULL) // stop case. Если не найдешь число то чтобы функция не крашнулась и не знала шо делать. Возвращаем ей нулик
        return NULL;

    if(root_1->data == pos)
        return root_1;

    if (root_1->brother != NULL) // ниже не ставим return чтобы в случае нуля для брата матрешка не закрывалась для ребенка
        find_node(root_1->brother, pos);
    if(root_1->child != NULL)
        return find_node(root_1->child, pos);
    return root_1; // второй раз root_1 возвращать приходится из за страной матрешки от child. Она иногда завершает работу программе на своем find. Потому после нее впихнул root еще
}
*/




void print(struct tree *root){
    static int l = 0; // без этого сраного static вся функция ломается к ебеням. Не знаю пока как работает этот тупой print но работает и бох с ним
    if(root != NULL){
        l++;
        for(int i = 1; i < l; i++) printf("\t");
        printf("\\__%.3f\n", root->data);
        print(root->child);
        l--;
        print(root->brother);
    }
}

float max_elem(struct tree* root)// можем найти максим цифру потом по цифре find найти ноду и от нее в parent
{
    static float key;

    if (root->data >= key) {
        key = root->data;
    }
    if (root->brother != NULL)
        max_elem(root->brother);
    if (root->child != NULL)
        max_elem(root->child);

    return key;

}

int maxDepth(struct tree* root) // сначала найдем ноду с наибольшим ключом. Потом будем прыгать от нее к родителю пока не получим NULL. Так и узнаем глубину. В функцию msxdepth будем передавать ноду корня и ключ корня
{
    int i = 0;
    while(root->father != NULL)
    {
        root = root->father;
        i++;
    }
    printf("Глубина %d\n", i);
}

void node_Unlink(Node *node) // отделяем ноду от дерева
{
    Node *tmp = node->father->child;// найдем первого ребенка на уровне
    if (! node)
        return;
    if (node->father->child == node) // меняем указатель с родителя на ребенка
    {
        node->father->child = node->brother;
        node->brother = NULL; // ломаем указатель на следующий элемент после node
    }
    else
    {
        while(tmp->brother != node) // двигаемся направо пока не найдем ноду что надо удалить
            tmp = tmp->brother;
        tmp->brother = tmp->brother->brother;// как только дошли до того что следующий узел - нода. Меня указатель с ноды что стоит перед node на ноду что стоит после node
    }
    node->father = NULL;
    node->brother = NULL;
}

void node_Free(Node *node) // чистим отделенную ноду
{
    if (! node)
        return;
    if (node->child)
        node_Free(node->child);
    if (node->brother)
        node_Free(node->brother);
    free(node);
}


int main(){
    float key, pos;
    int action;

    struct tree *root = NULL;
    struct tree *root_1;

    printf("Дерево общего вида. Доступные действия:\n");
    printf("1. Добавить корень\n");
    printf("2. Добавить узел\n");
    printf("3. Распечатать дерево\n");
    printf("4. Глубина макс вершины\n");
    printf("5. Удалить узел\n");
    printf("6. Выход\n");

    while(1)
    {
        printf("Действие [0-6]: ");
        scanf("%d", &action);
        switch(action)
        {
            case 1:
            {
                printf("Значение корня: ");
                scanf("%f", &key);
                root = new_node(key);
                break;
            }

            case 2:
            {

                printf("Значение узла, на позицию которого нужно добавить узел: ");
                scanf("%f", &pos);
                root_1 = find_node(root, pos);
                if(root_1 == NULL)
                {
                    printf("Нету узла с указанным значением.\n");
                    break;
                }
                printf("Значение нового узла: ");
                scanf("%f", &key);
                add_child(root_1, key);
                break;
            }

            case 3:
            {
                print(root);
                break;
            }

            case 4:
            {
                root_1 = find_node(root, max_elem(root));
                maxDepth(root_1);
                break;
            }

            case 5:
            {
                
                printf("Значение узла который надо удалить: ");
                scanf("%f", &pos);

                root_1 = find_node(root, pos);
                node_Unlink(root_1);
                node_Free(root_1);
                printf("Узел успешно удален ");
            }

            case 6: break;

        }

        if (action == 6)
            break;

    }
    return 0;
}
