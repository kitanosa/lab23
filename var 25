#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
смысл структуры вообще

Обычно все члены структуры связаны друг с другом. Например, информация об имени и адресе, находящаяся в списке рассылки, обычно представляется в виде структуры.
struct addr {
char name[30];
char street [40]; char city[20];
char state[3];
};

Имя структуры addr идентифицирует структуру данных и является спецификатором типа.
На данный момент на самом деле не создано никакой переменной. Определена только форма данных. Для объявления настоящей переменной, соответствующей данной структуре, следует написать:

struct addr addr_info;

В данной строке происходит объявление переменной addr_info типа addr. При объявлении структуры определяется переменная смешанного типа. До тех пор, пока не будет объявлена переменная данного типа, она не будет существовать.

Когда объявлена структурная переменная, компилятор автоматически выделяет необходимый участок памяти для размещения ВСЕХ ЕЕ ЧЛЕНОВ. Рис. показывает размещение addr_info в памяти.
name 30bytes   -|
street 40bytes  | - addr_info
city 20bytes    |
state 3bytes   -|
Важно понять, что каждая вновь создаваемая структурная переменная содержит свои собственный копии переменных, образующих структуру.
*/
// Обычно все члены структуры связаны друг с другом. Например, информация об имени и адресе, находящаяся в списке рассылки, обычно представляется в виде структуры.
typedef struct tree
// typedef struct tree node такой синтаксис этой команды
// typedef тип имя // он переименовывает тип struct tree на node чтобы не загромождать код
{
    int key;
    // указатель left на структуру. То есть мы создаем ссылку сруктурного типа на элемент который будет стоять слева от даного элемента с key
    struct tree *left;
    struct tree *right;
    struct tree *parent;
    // описав стурктуру мы не объявили кружочек. Мы объявили набор инструментов который мы потом будем использовать. То есть структура это не объект в данном лсучае. А набор инструментов характерных любому кружочку
}node;
// Цель функции create создать объект структуры. Поэтому мы выбираем node * (но все же странно. Другие не юазил это)
// node * в данном случае выходит в качестве типа данных. Это возвращаемый тип данных. То есть каким типом данных будет return root
// Чтобы менять root на протяжении всей программы мы пихаем его в аргументы (struct tree *root) функции в качестве адреса. Ведь по правилу (см в той же папке str.c) чтобы изменить root вне main (где он объявлен) нам надо пихать его в качестве адреса в другие функции
// также мы сделали возвращаемый тип адресным (node *) для того чтобы root вернулся к нам тоже в качестве адреса. Кастомная хуета. Можно былоб и без нее обойтись наверн
node *create(node *root, int key)
{
    node *tmp = malloc(sizeof(node));
    // выделение памяти под корень списка
    // MALLOC возвращает  указатель на адрес в памяти. Поэтому tmp есть адрес и мы его разыменовываем посредством -> (указатель на структуру)
    // (*tmp).parent = NULL
    // в чем смысл node* перед tmp? Описав node мы тем самым разрешили через tmp обратиться к структуре tree        (*tmp).parent = NULL
    // возвращаемый тип struct tree потому что с malloc мы создаем участок памяти для одного кружочка. А кружочек это структура. С ключом и указателями
    tmp -> key = key;
    tmp -> parent = NULL;
    // присвоили значению parent NULL
    tmp -> left = tmp -> right = NULL;
    // в итоге у нас tmp это адрес на структуру содержащую key и два указателя
    root = tmp;
    return root;
}


node *add(node *root, int key)
{
    // в create мы определили root (корень дерева) представляющий из себя кружочек с цифрой и двумя указателями
    // key в последующем будет сравниваться
    // дальше это используется в node *root2: мы приравниваем root2 = root заранее передав root2 свойства указателя
    node *root2 = root, *root3 = NULL;
    node *tmp = malloc(sizeof(node));
    tmp -> key = key;
    while (root2 != NULL)
    // мы сказали root2 = root. А root это корень дерева. Он ненулевой. Следовательно выполняем цикл где сравниваем root2 с корнем и в зависимости от сравнения идем направо или налево. И даем новое значение root2 пока не дойдем до нулевого!
    {
        root3 = root2;
        // мы сразу забиваем в root3=root2 чтобы оставить его как родителя. А после выполняем уже сравнение
        if (key < root2 -> key)
        // если (*root2).key > key то есть если корень больше ключа введенного с клавиатуры, то идем налево и выполняем цикл пока не дойдем до null
            root2 = root2 -> left;
        else
            root2 = root2 -> right;
    }
    // нашли нулевую ячейку. Забили в root3 родителя стоящего перед нулевой ячейкой. Теперь надо забить key в нулевую ячейку
    tmp -> parent = root3;
    tmp -> left = NULL;
    tmp -> right = NULL;
    // забиваем key в нулевую ячейку
    // если root3(родитель)>key то забиваем слева от root в ячейку tmp. Ведь в tmp у нас ключ key лежит
    if (key < root3 -> key) root3 -> left = tmp;
    else root3 -> right = tmp;
    return root;
}


node *search(node *root, int key)
{
    if ((root == NULL) || (root -> key == key))
        // если root == key то шик
        return root;
    // если корень > ключа то идем влево и запускаем снова search
    if (key < root -> key)
        return search(root -> left, key);
    else return search(root -> right, key);
}


node *tree_min(node *root)
        {
                node *l = root;
        while (l -> left != NULL)
        l = l -> left;
        return l;
        }


node *tree_max(node *root)
        {
                node *r = root;
        while (r -> right != NULL)
        r = r -> right;
        return r;
        }


node *successor(node *root)
// root = l
{
    /*
    Допустим надо надо удалить 3. Если у нее есть правое поддерево и его левый потомок, то через successor мы ищем минимального его левого потомка и заменяем вместо удаляемого
    у нас 3 удалить надо
    право поддерево 6 ( по if в delete мы рассматриваем этот случай)
    минимальный левый потомок 4. Его и должна найти эта функций successor
    а потом в delete записываем 4 вместо 3
            7
        3       8
    1     6
         5
        4 
    */
    node *p = root, *l = NULL;
    if (p -> right != NULL)
        return tree_min(p -> right);
        // мы вернули l в которой минимальное значение (4)
        // Оператор return завершает выполнение функции и возвращает управление вызывающей функции. 
    l = p -> parent;
    // цикл для правого листа (по идее) (НА САМОМ ДЕЛЕ В ДУШЕ НЕ ЕБУ КАК РАБОТАЕТ ЭТОТ ЦИКЛ. Но пройдемся дальше)
    while ((l != NULL) && (p == l -> right))
    {
        p = l;
        l = l -> parent;
    }
    // return l без входа в while если p у нас это левый лист
    return l;
}


node *delete(node *root, int key)
{
    node *l = NULL, *m = NULL;
    // l - узел который надо удалить
    l = search(root, key);
    // мы нашли l и рассматриваем несколько случаев. Когда есть что либо справа и слева от l либо нет
    if ((l -> left == NULL) && (l -> right == NULL))
    {
        // если l это лист, то мы в m забиваем родителя для l и удаляем дальше указатель на right/left. А после высвобождаем память занимаемую l (то есть сначала удалили ребро а потом ноду)
        m = l -> parent;
        if (l == m -> right) m -> right = NULL;
        else m -> left = NULL;
        // free это синтаксис освобождения памяти. В него передается адрес
        free(l);
    }
    if ((l -> left == NULL) && (l -> right != NULL))
    {
        m = l -> parent;
        if (l == m -> right) m -> right = l -> right;
        else m -> left = l -> right;
        free(l);
    }
    if ((l -> left != NULL) && (l -> right == NULL))
    {
        m = l -> parent;
        if (l == m -> right) m -> right = l -> left;
        else m -> left = l -> left;
        free(l);
    }
    if ((l -> left != NULL) && (l -> right != NULL))
    {
        // найдем минимального левого потомка у правого поддерева для удаляемого числа (в successor это 4. В рисунке)
        m = successor(l);
        // вместо 3 записываем 4
        l -> key = m -> key;
        // а теперь удаляем саму ноду которая была в 4
        if (m -> right == NULL)
            // сначала перейдем в родителя а потом из родителя удалим левого потомка
            m -> parent -> left = NULL;
        // в ином случае если есть справа от 4 допустим 4,5 то удаляем 4 и ставим на ее место 4,5
        else m -> parent -> left = m -> right;
        free(m);
    }
    return root;
}


void showtree (node *root, int n) {
    if (root->left) showtree(root->left, n+1);
    for (int i = 0; i < n; i++) printf("  ");
    printf("%d\n", root->key);
    if (root->right) showtree(root->right, n+1);
}


int max(int a,int b){
    if(a>b)
        return a;
    if(a<b)
        return b;
}
int check(node *root)
{

    if (root == NULL)
        return 0;
    return max(check(root->left), check(root->right)) + 1;
}      



int main(int argc, char const *argv[])
{
    node *root;
    int key, result, a, b;

    for(;;)
    {
        char answer[20];
        printf("\n   Выберите действие, которое нужно выполнить с деревом:\n\n\t-Чтобы создать дерево, введите 'create'\n\t-Чтобы добавить узел дереву, введите 'add'\n\t-Чтобы удалить узел дерева, введите 'delete'\n\t-Чтобы вывести содержимое дерева, введите 'show'\n\t-Чтобы проверить, является ли введенное дерево B деревом - введите 'check'\n\t-Чтобы закончить работу программы, введите 'end'\n\n >> ");
        scanf("%s", answer);
        // key это корень дерева key это узел

        if (strcmp(answer, "end") == 0){
            printf("Конец работы программы");
            break;
        } else if(strcmp(answer, "create") == 0){
            printf("\n   Введите значение корня\n\n >> ");
            scanf("%d", &key);
            root = create(root, key);
            printf("\n   Дерево успешно создано\n");
        } else if(strcmp(answer, "show") == 0){
            printf("\n");
            showtree(root, 0);
            printf("\n");
        } else if(strcmp(answer, "add") == 0){
            printf("\n   Введите значение узла\n\n >> ");
            scanf("%d", &key);
            root = add(root, key);
            printf("\n   Узел успешно добавлен\n");
        } else if(strcmp(answer, "delete") == 0){
            printf("\n   Введите значение узла, который нужно удалить\n\n >> ");
            scanf("%d", &key);
            root = delete(root, key);
            printf("\n   Узел успешно удален\n");

        } else if(strcmp(answer, "check") == 0){
            printf("глубина дерева %d\n", check(root));
        }

    }

    return 0;
}
