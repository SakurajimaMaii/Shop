#include <cstdio>
#include <cstdlib>
#include <cstring>

typedef struct item     //建立一个结构体储存超市商品
{
    char category[20];
    char name[20];
    float price;
    int stock;
    char manufacturer[20];
    char brand[20];
    struct item *next;
} ITEM;

ITEM *Build();      //超市商品初始化
int Choice();        //第一个选择菜单
void Purchase(ITEM *items);     //实现“客户”功能
void Contents(ITEM *items, char cc[20]);     //实现“客户”菜单功能
ITEM *Find(char ca[20], char name[], ITEM *head);        //按照用户输入的“商品名称”查询并返回对应查询结果，否则返回nullptr
int Menu();     //实现“管理员”功能
void Add(ITEM *items);      //实现“添加”功能
void Inquire(ITEM *items);      //实现“查询”的框架功能
ITEM *Seek(ITEM *items);      //实现“查询”的核心功能，类似于上Find函数
void Modify(ITEM *items);       //实现“修改”功能
ITEM *Delete(ITEM *items);       //实现“删除”功能
ITEM *Statistics(ITEM *items);       //实现“统计”的框架功能
ITEM *GetMid(ITEM *items);

ITEM *LinkBy(ITEM *x, ITEM *y, float a, int b);

ITEM *StatisticsBy(ITEM *items, float a, int b);

void Print(ITEM *items);        //实现“输出”功能
void Storage(ITEM *items);      //实现“文件存盘”功能
ITEM *Open();        //实现“文件读取”功能
int main() {
    ITEM *items;
    int c, n;
    items = Build();
    while (true) {
        c = Choice();
        switch (c) {
            case 1:
                Purchase(items);
                break;
            case 2:
                n = Menu();
                switch (n) {
                    case 1:
                        Add(items);
                        break;
                    case 2:
                        Inquire(items);
                        break;
                    case 3:
                        Modify(items);
                        break;
                    case 4:
                        items = Delete(items);
                        break;
                    case 5:
                        items = Statistics(items);
                        break;
                    case 6:
                        Storage(items);
                        break;
                    case 7:
                        items = Open();
                        break;
                    case 0:
                        printf("\n已退出！\n\n");
                        break;
                    default:
                        printf("\n输入错误！\n\n");
                        break;
                }
                break;
            case 0:
                printf("\n已退出！\n");
                exit(0);
            default:
                printf("\n输入错误！\n\n");
                break;
        }
    }
}

ITEM *Build()           //超市商品初始化
{
    ITEM *head, *it1, *it2, *it3, *it4;
    it1 = (ITEM *) malloc(sizeof(ITEM));
    if (it1 != nullptr) {
        strcpy_s(it1->category, "食品");
        strcpy_s(it1->name, "红烧牛肉面");
        it1->price = 3.5;
        it1->stock = 48;
        strcpy_s(it1->manufacturer, "河南斯美特");
        strcpy_s(it1->brand, "思源");
    }
    it2 = (ITEM *) malloc(sizeof(ITEM));
    if (it2 != nullptr) {
        strcpy_s(it2->category, "化妆品");
        strcpy_s(it2->name, "男士润肤霜");
        it2->price = 69.9;
        it2->stock = 23;
        strcpy_s(it2->manufacturer, "德国进口");
        strcpy_s(it2->brand, "妮维雅");
    }
    it3 = (ITEM *) malloc(sizeof(ITEM));
    if (it3 != nullptr) {
        strcpy_s(it3->category, "日用品");
        strcpy_s(it3->name, "洗发露");
        it3->price = 23.5;
        it3->stock = 13;
        strcpy_s(it3->manufacturer, "广州宝洁");
        strcpy_s(it3->brand, "海飞丝");
    }
    it4 = (ITEM *) malloc(sizeof(ITEM));
    if (it4 != nullptr) {
        strcpy_s(it4->category, "饮料");
        strcpy_s(it4->name, "脉动");
        it4->price = 4.0;
        it4->stock = 35;
        strcpy_s(it4->manufacturer, "湖北达能");
        strcpy_s(it4->brand, "脉动");
    }
    head = it1;
    it1->next = it2;
    it2->next = it3;
    it3->next = it4;
    it4->next = nullptr;
    return head;
}

int Choice()        //第一个选择菜单
{
    int c;
    printf("请选择功能：\n\
    1:销售功能（客户）\n\
    2:商品简单管理功能（管理员）\n\
    0:退出\n");
    scanf_s("%d", &c);
    return c;
}

void Purchase(ITEM *items)     //实现“客户”功能
{
    int c, m;
    ITEM *j;
    char name[20], ca[20];
    printf("\n当前商品有:\n");
    Contents(items, (char *) "食品");
    Contents(items, (char *) "化妆品");
    Contents(items, (char *) "日用品");
    Contents(items, (char *) "饮料");
    printf("\n请输入商品类别:\n\
    1:食品\n\
    2:化妆品\n\
    3:日用品\n\
    4:饮料\n\
    0:退出\n");
    scanf_s("%d", &c);
    if (c == 0)
        goto E;
    if (c == 1)
        strcpy_s(ca, "食品");
    else if (c == 2)
        strcpy_s(ca, "化妆品");
    else if (c == 3)
        strcpy_s(ca, "日用品");
    else
        strcpy_s(ca, "饮料");       //通过数字选择简化用户输入
    printf("\n请输入商品名称:\n");
    scanf_s("%s", name);
    j = Find(ca, name, items);
    if (j == nullptr)
        printf("\n对不起，无此商品！\n");
    else {
        printf("\n请输入您要购买的数量：\n");
        scanf_s("%d", &m);
        if (m > j->stock)
            printf("\n对不起，库存不足！\n\n");
        else {
            j->stock -= m;
            printf("\n您共需付款%.2f元！\n谢谢购买，祝您购物愉快！\n\n", j->price * m);
        }
    }
    E:
    printf("\n已退出\n\n");
}

void Contents(ITEM *items, char cc[20])     //实现“客户”菜单功能
{
    ITEM *it = items;
    printf("%s:\n\t", cc);
    while (it != nullptr) {
        if (strcmp(it->category, cc) == 0) {
            printf("%s\t", it->name);
        }
        it = it->next;
    }
    printf("\n");
}

ITEM *Find(char ca[20], char name[], ITEM *head)        //按照用户输入的“商品名称”查询并返回对应链表节点，否则返回nullptr
{
    ITEM *p = head;
    while (p != nullptr) {
        if (strcmp(p->category, ca) == 0 && strcmp(p->name, name) == 0) {
            printf("\n该商品的信息:\n\
                价格:%.2f\n\
                生产厂家:%s\n\
                品牌:%s\n", p->price, p->manufacturer, p->brand);
            return p;
        }
        p = p->next;
    }
    return nullptr;
}

int Menu()     //实现“管理员”功能
{
    int n;
    printf("\n请选择您需要的功能：\n\
    1:添加功能\n\
    2:查询功能\n\
    3:修改功能\n\
    4:删除功能\n\
    5:统计功能\n\
    6:商品信息存盘\n\
    7:读出商品信息\n\
    0:退出\n");
    scanf_s("%d", &n);
    return n;
}

void Add(ITEM *items)      //实现“添加”功能
{
    ITEM *p, *pr;
    p = (ITEM *) malloc(sizeof(ITEM));
    if (p != nullptr) {
        printf("\n请输入待添加商品的类别、名称、价格、库存量、生产厂家、品牌:\n");
        scanf_s("%s %s %f %d %s %s", p->category, p->name, &p->price, &p->stock, p->manufacturer, p->brand);
    } else {
        printf("\n申请内存失败！\n");
        exit(0);
    }
    pr = items;
    while (pr->next != nullptr)     //寻找链表尾节点
    {
        pr = pr->next;
    }
    pr->next = p;
    p->next = nullptr;
    printf("\n已添加！\n\n");
}

void Inquire(ITEM *items)      //实现“查询”的框架功能
{
    ITEM *p = Seek(items);
    if (p != nullptr)
        printf("\n该商品的详细信息为:\n\
               类别:%s\n\
               名称:%s\n\
               价格:%.2f\n\
               库存量:%d\n\
               生产厂家:%s\n\
               品牌:%s\n\n", p->category, p->name, p->price, p->stock, p->manufacturer, p->brand);
    else
        printf("\n该记录不存在！\n\n");
}

ITEM *Seek(ITEM *items)      //实现“查询”的核心功能，类似于上Find函数
{
    ITEM *p = items, *ca;
    ca = (ITEM *) malloc(sizeof(ITEM));
    if (ca != nullptr) {
        printf("\n请输入待查商品的类别、名称、生产厂家:\n");
        scanf_s("%s %s %s", ca->category, ca->name, ca->manufacturer);
    } else {
        printf("\n申请内存失败！\n");
        exit(0);
    }
    while (p != nullptr)        //不断往链表尾节点靠近，寻找待查节点
    {
        if (strcmp(p->category, ca->category) == 0 && strcmp(p->name, ca->name) == 0 &&
            strcmp(p->manufacturer, ca->manufacturer) == 0) {
            return p;
        }
        p = p->next;
    }
    return nullptr;
}

void Modify(ITEM *items)       //实现“修改”功能
{
    ITEM *p = Seek(items);
    if (p != nullptr) {
        printf("\n请依次输入修改后的信息:类别、名称、价格、库存量、生产厂家、品牌:\n");
        scanf_s("%s %s %f %d %s %s", p->category, p->name, &p->price, &p->stock, p->manufacturer, p->brand);
        printf("\n已修改！\n\n");
    } else {
        printf("\n对不起，您输入有误！\n\n");
    }
}

ITEM *Delete(ITEM *items)       //实现“删除”功能
{
    ITEM *p = items, *d = items;
    char ca[20], na[20];
    printf("\n请输入待删除商品的类别:\n");
    scanf_s("%s", ca);
    printf("\n请输入待删除商品的名称:\n");
    scanf_s("%s", na);
    while (p != nullptr) {
        if (strcmp(p->category, ca) == 0 && strcmp(p->name, na) == 0)        //寻找待操作节点
            break;
        p = p->next;
    }
    /*这里分为待删除节点为头结点和非头结点两种，分别做处理，本质都为
      将待删除节点next域传给其上一节点（头结点除外），但是并不用考虑
      尾节点的问题，因为如果是尾节点其next域为nullptr传给其上一节点正对*/
    if (p == nullptr) {
        printf("\n对不起，您输入有误！\n\n");
        return items;
    } else if (p == items) {
        free(p);
        printf("\n已删除！\n\n");
        return items->next;
    } else {
        while (d != nullptr) {
            if (d->next == p) {
                free(p);
                printf("\n已删除！\n\n");
                d->next = p->next;
                return items;
            }
            d = d->next;
        }
    }
    return items;
}

ITEM *Statistics(ITEM *items)       //实现“统计”的框架功能
{
    int n;
    ITEM *Pt;
    printf("\n请选择统计方式:\n\
    1:按价格统计\n\
    2:按库存量统计\n\
    3:直接统计\n\
    0:退出\n");
    scanf_s("%d", &n);
    if (n == 0) {
        printf("\n已退出!\n\n");
        return items;
    } else if (n == 1) {
        Pt = StatisticsBy(items, items->price, 0);
        Print(Pt);
        return Pt;
    } else if (n == 2) {
        Pt = StatisticsBy(items, 0, items->stock);
        Print(Pt);
        return Pt;
    } else {
        Print(items);
        return items;
    }
}

/*下面三个函数为实现“统计”的核心功能，主要利用“归并排序”思想，为本
  码最大的闪光点（手动滑稽），此处不做详谈*/
ITEM *GetMid(ITEM *items) {
    if (items->next == nullptr)
        return items;
    ITEM *q = items, *s = items, *p;
    while (q->next != nullptr && q->next->next != nullptr) {
        q = q->next->next;
        s = s->next;
    }
    p = s->next;
    s->next = nullptr;
    return p;
}

/*下面两函数有一巧妙之处，即自定义函数参数中有float与int型可以用来
  区别是按何种方式统计，省的定义两个极其相似的函数统计，提高可读性*/
ITEM *LinkBy(ITEM *x, ITEM *y, float a, int b) {
    ITEM *ret = nullptr, *tail = nullptr;
    while (x != nullptr && y != nullptr) {
        if ((x->stock > y->stock && a == 0) || (x->price > y->price && b == 0)) {
            ITEM *temp = x->next;
            if (ret == nullptr) {
                ret = tail = x;
                ret->next = nullptr;
            } else {
                tail->next = x;
                tail = tail->next;
                tail->next = nullptr;
            }
            x = temp;
        } else {
            ITEM *temp = y->next;
            if (ret == nullptr) {
                ret = tail = y;
                ret->next = nullptr;
            } else {
                tail->next = y;
                tail = tail->next;
                tail->next = nullptr;
            }
            y = temp;
        }
    }
    if (x == nullptr)
        tail->next = y;
    else
        tail->next = x;
    return ret;
}

ITEM *StatisticsBy(ITEM *items, float a, int b) {
    if (items->next == nullptr)
        return items;
    ITEM *p1, *p2, *mid;
    mid = GetMid(items);
    p1 = StatisticsBy(items, a, b);
    p2 = StatisticsBy(mid, a, b);
    return LinkBy(p1, p2, a, b);
}

void Print(ITEM *items)        //实现“输出”功能
{
    int i = 1;
    ITEM *p = items;
    printf("\n统计商品为:\n");
    while (p != nullptr) {
        printf("\t%d:\n\
               类别:%s\n\
               名称:%s\n\
               价格:%.2f\n\
               库存量:%d\n\
               生产厂家:%s\n\
               品牌:%s\n", i, p->category, p->name, p->price, p->stock, p->manufacturer, p->brand);
        p = p->next;
        i++;
    }
    printf("\n");
}

void Storage(ITEM *items)      //实现“文件存盘”功能
{
    FILE *fp;
    errno_t err = fopen_s(&fp, "Shop.txt", "w");
    if (fp == nullptr) {
        printf("\n操作失败!\n");
        exit(0);
    } else {
        ITEM *p = items;
        while (p != nullptr) {
            fprintf(fp, "%s\t%s\t%.2f\t%d\t%s\t%s", p->category, p->name, p->price, p->stock, p->manufacturer,
                    p->brand);
            if (p->next != nullptr) {
                fprintf(fp, "\n");
            }
            p = p->next;
        }
        printf("\n储存成功! \n\n");
        fclose(fp);
    }
}

/*此处着实为难我很久，储存很简单，但是再按原样读取出来就非常难了，
  但是最后我还是找到方法了，利用\t就能完美的解决此问题，使储存的文
  件既有可读性又能使读取操作简单*/
ITEM *Open()        //实现“文件读取”功能
{
    FILE *fp;
    errno_t err = fopen_s(&fp, "Shop.txt", "r");
    if (fp == nullptr) {
        printf("\n打开失败,请检查该文件!\n");
        exit(0);
    } else {
        ITEM *p = nullptr, *pt = nullptr;
        while (!feof(fp)) {
            pt = (ITEM *) malloc(sizeof(ITEM));
            fscanf_s(fp, "%s%s%f%d%s%s", pt->category, pt->name, &pt->price, &pt->stock, pt->manufacturer, pt->brand);
            pt->next = p;
            p = pt;
        }
        pt = nullptr;
        printf("\n读取成功!\n\n");
        fclose(fp);
        return p;
    }
}