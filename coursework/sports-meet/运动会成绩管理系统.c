#include <stdio.h>
#include <stdlib.h>
#define NAME 17 //字符数
#define NUMU 20
#define NUMP 20
#define H 5 //每一行输出的学校或项目数
  
//运行本程序须知：
//代码百分之百完整，肯定能运行成功! 如果不能运行，肯定是你的软件下载或者配置有问题！！! 切记~~~
//运行前要解压我发给你的压缩包，然后打开文件夹下的源程序运行。 
//切不可自己复制粘贴一份，复制粘贴肯定会报错！！！因为除了源代码还有其他存储文件都在我发你的压缩包下。
// Dev 和 VS 都能成功运行。用 VS 时除了打开源代码，还要打开文件夹里面的 .exe 可执行文件进行运行!! 
 
FILE *fp;
const char wenjian[] = "system.txt"; //文件命名
typedef struct link
{
    int gram[3][NUMP];//gram[0]存男生项目，gram[1]存女生项目,gram[2]存这个学校中男女在此项目上的总分
    int sum[3];//sum[0]存男生总得分，sum[1]存女生总得分，sum[2]存学校总得分
}link; 
typedef struct MESSAGE
{
    int b[4]; // b[0-3]依次为(学校个数，项目个数，男生项目个数，女生项目个数
    char xuexiao[NUMU][NAME];//学校名称
    int sex[NUMU];//性别（区分男女子项目）
    struct link spot[NUMU];//添加积分情况
    int junction[NUMP];//决定取前三或前五
    int count[NUMP][5];//项目的学校编号
    char xiangmu[NUMP][NAME];//项目名称
} MESSAGE;
 
int junction[][5] = {{5, 3, 2, 0, 0}, {7, 5, 3, 2, 1}};
char sex[][3] = {"男", "女"};
char fenlei[][5] = {"男子", "女子", "学校"};
int gainint(int *p, int a, int b);//输入数据p，输入数据下限a，输入数据上限b
int gainchar(char A[], int min, int max);//输入字符A，输入字符数量下限min，输入字符数量上限max
int bijiao(char a[], char b[]);//等待进行匹配查找的字符串a，进行匹配查找的关键字b
void record(char school[][NAME], char game[][NAME], int b[], MESSAGE *temp);
int xianshi();
int jianyan(char b[], int T);//检验字符是否符合要求,T=0检验当前字符串是否全为汉字 T=1检验学校,T=2检验比赛
int jianyan2(char b[], int T);
void paixu(MESSAGE *temp, int select,FILE *fp);
 
char key[][3] = {"！", "。", "？", "《", "》", "，", "｛", "｝", "（", "）", "￥", "‘", "’", "：", "；", "—", "”", "“", "、", "·", "~", "\0"};
char school[][5] = {"大学", "学院", "华侨", "校区", "政法", "管理", "经济", "科学", "理工", "科技", "医科", "医药", "财经", "技术", "职业", "师范", "中国", "海洋", "石油", "民族", "外贸", "分校", "建筑", "工业", "外语", "\0"};
char program[][3] = {"跳", "滑", "冰", "射", "骑", "击", "跑", "拉", "道", "球", "举", "米", "水", "摔", "爬", "泳", "拔", "车", "踩", "接", "划", "体", "田", "人", "赛", "\0"};
 
int read(MESSAGE *message,FILE *fp)
{
    if ((fp = fopen(wenjian, "r")) == NULL)
    {
        if ((fp = fopen(wenjian, "w+")) != NULL)
        {
            fclose(fp);
            if ((fp = fopen(wenjian, "r")) == NULL)
                return printf("文件读取失败!\n");
        }
    }
    fread(message, sizeof(MESSAGE), 1, fp);
    fclose(fp);
    return 0;
}
 
 
int main()
{
	system("color f0"); 
    MESSAGE SG = {0}, *message = &SG;
    int i, j, k, select, choice, now, next;
 
    if (read(message,fp))
    {
        printf("请按任意键进行下一步\n");
        getch();
    }
 
    do
    {
        system("cls");
        select = xianshi();
        if (select == 1)
            record(message->xuexiao, message->xiangmu, message->b, message);
        else if (message->b[0])
        {
            if (select >= 2 && select <= 4)
            {
                fp = fopen(wenjian, "a+");
                paixu(message, select - 2,fp);
                fclose(fp);
            }
                
            else if (select == 5)
            {
                fp = fopen(wenjian, "a+");
                for (k = 0; k < message->b[0]; k++) //输出学校名称选项 每五个一行
                    printf("%d:%-13s%c", k + 1, message->xuexiao[k], (k + 1) % H ? ' ' : '\n');
                printf("\n输入学校前的编号[1,%d]:", message->b[0]);
                choice = gainint(&choice, 1, message->b[0]) - 1;
                next = 0;
                while (next < message->b[1])
                {
                    now = next;
                    if ((next + H) < (message->b[1]))
                        next = next + H;
                    else
                        next = message->b[1];
 
                    for (i = now; i < next; i++)
                    {
                        fprintf(fp,"(%s-%d)%-8s ", sex[message->sex[i]], message->junction[i], message->xiangmu[i]);
                        printf("(%s-%d)%-8s ", sex[message->sex[i]], message->junction[i], message->xiangmu[i]);
                    } //输出项目信息
 
                    fprintf(fp,"\n");
                    printf("\n");
                    for (j = 0; j < 3; j++)
                    {
                        fprintf(fp,"%-s:  ", fenlei[j]);
                        printf("%-s:  ", fenlei[j]);
                        for (k = now; k < next; k++)
                        {
                            if (j == message->sex[k] || j == 2)
                            {
                                fprintf(fp,"%02d分    \t", (message->spot + choice)->gram[j][k]);
                                printf("%02d分    \t", (message->spot + choice)->gram[j][k]);
                            }
                            else
                            {
                                fprintf(fp,"******  \t");
                                printf("******  \t");
                            }
 
                        }
                        fprintf(fp,"\n");
                        printf("\n");
                    }
                    fprintf(fp,"\n");
                    printf("\n");
                }
                fclose(fp);
            }
            else if (select == 6)
            {
                fp = fopen(wenjian, "a+");
                for (i = 0; i < message->b[1]; i++)
                {
                    printf("\t\t第%d个比赛项目: %-13s<%s子> 只录入前%d名\n", i + 1, message->xiangmu[i], sex[message->sex[i]], message->junction[i]);
                    fprintf(fp,"\t\t第%d个比赛项目: %-13s<%s子> 只录入前%d名\n", i + 1, message->xiangmu[i], sex[message->sex[i]], message->junction[i]);
                    for (j = 0; j < message->junction[i]; j++)
                    {
                        fprintf(fp,"\t第%d名:%-13s%02d分", j + 1, message->xuexiao[message->count[i][j]], junction[(message->junction[i]) / 4][j]);
                        printf("\t第%d名:%-13s%02d分", j + 1, message->xuexiao[message->count[i][j]], junction[(message->junction[i]) / 4][j]);
                    }
                    printf("\n\n");
                    fprintf(fp,"\n\n");
                }
                fclose(fp);
            }
            else if (select == 9)
            {
                printf("确认清空请按1 否则请按0:");
                if (gainint(&choice, 0, 1))
                    for (k = 0; k < NUMP; k++) //对申请出来的结构体中的所有项目初始化
                        for (i = 0; i < 3; i++)
                        {
                            (message->spot + k)->sum[i] = 0; // sum[]初始化
                            for (j = 0; j < NUMP; j++)
                                (message->spot + k)->gram[i][j] = 0; //项目初始化
                            message->b[i] = 0;
                        }
                /*if (write(message,fp))
                    return 0;*/
                read(message,fp);
            }
            else if(select==7)
            {
                system(wenjian);
            }
        }
        printf("\n请按任意键继续…\n");
        getch();
    } while (select != 8);
    
    return 0;
}
 
int bijiao(char a[], char b[])
{
    int i = 0, j = 0;
    while (a[i] && b[j])
        if (a[i++] == b[j])
        {
            j++;
        }
        else
        {
            i = i - j;
            j = 0;
        }
    if (b[j] == '\0')
        return i - j + 1;//若匹配成功则返回第一次匹配成功的下标
    else
        return 0;
}
 
int gainint(int *p, int a, int b)
{
    do
    {
        *p = 0;
        scanf("%d", p);
        while (getchar() != '\n')
            ;
        if (*p > b || *p < a)
            printf("输入有误,请重新输入[%d--%d]:", a, b);
    } while (*p > b || *p < a);
    return *p;//返回输入数据
}
 
int gainchar(char A[], int min, int max)
{
    int B, C;
    do
    {
        A[max] = B = C = 0;
        while ((A[B++] = getchar()) != '\n' && B < max)
            ;
 
        if (A[B - 1] != '\n')
            while (getchar() != '\n' && ++C)
                ;//如果输入的最后一个字符不是回车，那么将剩余长度计到C
 
        else
            A[--B] = 0;//否则把录进数组的回车删掉，即为成功输入字符。
 
        if (C || B && B < min)
            printf("录入的字符串长度为%d字节\n只录入(%d--%d)个字符!\n", B + C, min, max);
    } while (C || B < min);
    return B;//返回录入成功字符数量
}
 
int jianyan(char b[], int T) //检验b[]是否符合实际
{
    int d = 0, i, LEN = -1, F;
    while (b[++LEN])
        ;
    for (i = 0; i < LEN; i++)
        if (b[i] > 0) //汉字ascll编码每一个字节为负数
            return printf("输入中含有非中文字符!");
    for (i = 0; key[i][0]; i++)
    {
        F = bijiao(b, key[i]); //匹配中文标点符号
        if (F && F % 2)
            return printf("输入中含有非汉字中文字符!");
    }
    if (T == 1) //检验学校的名称
    {
        for (i = 0; school[i][0]; i++)
        {
            F = bijiao(b, school[i]);
            if (F && F % 2)
                d++;
        }
        if (!d)
            return printf("查无此校~学校名称输入可能存在错误!");
    }
    if (T == 2) //检验比赛的名称
    {
        for (i = 0; program[i][0]; i++)
        {
            F = bijiao(b, program[i]);
            if (F && F % 2)
                d++;
        }
        if (!d)
            return printf("没有发现相关比赛~项目名称输入可能存在错误!");
    }
    return 0;
}
 
int jianyan2(char b[], int T) //检验b[]是否符合实际
{
    int d = 0, i, LEN = -1, F;
    if (T == 2) //检验比赛的名称
    {
        for (i = 0; program[i][0]; i++)
        {
            F = bijiao(b, program[i]);
            if (F )
                d++;
        }
        if (!d)
            return printf("没有发现相关比赛~项目名称输入可能存在错误!");
    }
    return 0;
}
 
void record(char school[][NAME], char game[][NAME], int b[], MESSAGE *temp) //记录数据；school为学校名，game为项目名，b（参考结构体中定义），temp信息结构体
{
    char choose[][13] = {"录入学校数目", "总计项目数目", "男子项目数目"}; //提示用户输入内容
    int scope[][3] = {{5, 1, 0}, {NUMU, NUMP, NUMU}};                     //输入的各个内容的范围
    int i, j, k, pan, count, choice, man;
    scope[1][0] = NUMU - b[0]; //剩余录入的学校的数量（主要为后续加入数据设计）
    scope[1][1] = NUMP - b[1]; //剩余录入的项目的数量（主要为后续加入数据设计）
 
    if (b[0])
    {
        scope[0][0] = scope[0][1] = 0;
    }//当用户已经进入此函数输入过一次后,改变条件将学校个数项目个数下限改为0
 
    for (i = 0; i < 3; i++)
    {
        printf("\t%s(%d--%d)\n\t:", choose[i], scope[0][i], scope[1][i]);
        gainint(&b[i], scope[0][i], scope[1][i]);
 
        if (i == 1)
        {
            scope[1][2] = b[1]; //输入项目完毕后，改变男生项目的长度
            if (!b[0] && !b[1])//输入为零时进行下一步
            {
                b[2] = b[1];
                i++;
            }
        }
        if (i == 2)
        {
            if (!b[0] || !b[1])
            {
                return;
            }
            b[3] = b[1] - b[2]; //男生输入完毕时，女生的项目=总项目-男生项目
        }
    }
    for (i = NUMU - scope[1][0]; i < b[0] + NUMU - scope[1][0]; i++)
        do
        {
            k = 0;
            printf("请输入第%d个学校的名称(只录入%d-%d字符):\n", i + 1, 8, NAME);
            gainchar(school[i], 8, NAME);
            for (j = 0; j < i; j++)                                               //对输入的学校名称进行查重
                if (bijiao(school[j], school[i]) && bijiao(school[i], school[j])) //之前的学校和当前录入的学校重复
                    k++;
            if (k)
                printf("该学校已经录入!");
 
        } while (jianyan(school[i], 1) || k);
 
    b[0] += NUMU - scope[1][0]; //计算出目前的学校总数（主要为后续加入数据设计）
 
    for (i = NUMP - scope[1][1]; i < b[1] + NUMP - scope[1][1]; i++) //录入项目
    {
        temp->sex[i] = (b[1] + NUMP - scope[1][1] - i) <= b[3]; //判断性别,0为男,1为女，先输入男
        do
        {
            k = 0;
            printf("请输入第%d个项目(%s)名称(只录入%d-%d字符):\n", i + 1, sex[temp->sex[i]], 4, NAME); //输入项目名称
            gainchar(game[i], 4, NAME);
            for (j = 0; j < i; j++)
                if (bijiao(game[j], game[i]))
                    k++;
            if (k)
                printf("项目已录入成功!");
            pan = (k || jianyan2(game[i], 2)); //区分分录入前三名还是前五名
            if (!pan)                         //当输入满足要求时 继续询问项目的录入名次
                do
                {
                    printf("该项目录入成绩: 3:取前三  5:取前五:"); //询问录入的时前几名
                    gainint(&(temp->junction[i]), 3, 5);           //将第i+1个项目的分数情况放在头节点的junction[i]数组里
                } while ((temp->junction[i]) == 4);                //只录入3和5
        } while (pan);                                             //当输入不满足要求时重新输入
        system("cls");
 
        for (k = 0; k < b[0]; k++) //输出学校名称选项 每五个一行
            printf("%d:%-13s%c", k + 1, school[k], (k + 1) % H ? ' ' : '\n');
 
        printf("\n\n获得 %s:(%s子)的前%d名(填学校前的编号):\n", game[i], sex[temp->sex[i]], temp->junction[i]);
        for (j = 0; j < temp->junction[i]; j++) //每次录入的项目个数=temp->junction[i]
        {
            do
            {
                pan = 0;
                printf("第%d名(%d-%d):", j + 1, 1, b[0]);
                count = gainint(&count, 1, b[0]) - 1; //范围1-b[0]
                (temp->count[i][j]) = count;          // temp->count[i][j]中的数值就是第i个学校,名次为j
                for (k = 0; k < j; k++)               //检验名次是否录入重复
                    if (temp->count[i][k] == count)
                        pan = printf("一个学校只能获得一个名次!\n");
            } while (pan);
            choice = junction[(temp->junction[i]) / 4][j];
            man = temp->sex[i];
            (temp->spot + count)->gram[man][i] = choice; //把choice积分存入第count个学校的第i个项目的gram[man][i]里
            (temp->spot + count)->gram[2][i] += choice;  //修改第count个学校的该项目总分
            (temp->spot + count)->sum[man] += choice;    //修改第count个学校的男女团体总积分
            (temp->spot + count)->sum[2] += choice;      //修改学校的总积分
        }
    }
    b[1] += NUMP - scope[1][1]; //修改录入的项目的总数量（主要为后续加入数据设计）
}
 
void paixu(MESSAGE *temp, int select,FILE *fp) //选择排序
{
    int i, j, k, m, a, b, n, school[2][NUMU] = {0};
    n = temp->b[0];
    printf("升序请按0 降序请按1:");
    gainint(&b, 0, 1);
    for (i = 0; i < n; i++)
    {
        school[1][i] = i; //记录学校当前的位置编号
        school[0][i] = (temp->spot + i)->sum[select];
    }
    printf("%s排名如下\t（以第%d列分数为准）:\n\n", fenlei[select], select + 1);
    fprintf(fp,"%s排名如下\t（以第%d列分数为准）:\n\n", fenlei[select], select + 1);
    for (i = 0; i < n - 1; i++)
    {
        k = i;
        for (j = i + 1; j < n; j++)
        {
            if (b && school[0][j] > school[0][k])
                k = j;
 
            else if (!b && school[0][j] < school[0][k])
                k = j;
        }
 
        if (k != i)
            for (m = 0; m < 2; m++)
            {
                a = school[m][k];
                school[m][k] = school[m][i];
                school[m][i] = a;
            }
    }
    printf("名次: 学校名称   男子   女子   学校总分\n");
    fprintf(fp,"名次: 学校名称   男子   女子   学校总分\n");
    for (i = 0; i < n; i++)
    {
        k = (b ? i + 1 : n - i); //计算排名的名次显示方向
        j = school[1][i];        // 记录学校的编号
        printf("第%02d:%-13s%02d分\t%02d分\t%02d分\n", k, temp->xuexiao[j], (temp->spot + j)->sum[0], (temp->spot + j)->sum[1], (temp->spot + j)->sum[2]);
        fprintf(fp,"第%02d:%-13s%02d分\t%02d分\t%02d分\n", k, temp->xuexiao[j], (temp->spot + j)->sum[0], (temp->spot + j)->sum[1], (temp->spot + j)->sum[2]);
    }
}
 
int xianshi()
{
    int a;
    system("mode con cols=130 lines=30"); //控制台 宽度130 高度30
    printf("\t\t\t\t运动会分数统计\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("\t*    功     能    表                 积   分   规   则\n");
    printf("\t* 1.添加学校及项目                  *取前三名(1,2,3)\n");
    printf("\t* 2.按男子团体总分排序输出           *积分分别为--5,3,2\n");
    printf("\t* 3.按女子团体总分排序输出         \n");
    printf("\t* 4.按学校总分排序输出               *取前五名(1,2,3,4,5)\n");
    printf("\t* 5.按编号或名称查询学校情况         *积分分别为--7,5,3,2,1\n");
    printf("\t* 6.显示比赛项目各学校名次情况       \n");
    printf("\t* 7.读取文件                    \n");
    printf("\t* 8.保存信息并退出                   \n");
    printf("\t* 9.清空并恢复初始化界面             \n");
    printf("\n");
    printf("\t*注意：一个汉字占两个字符！！！\n");
    printf("\t*注意：功能1可分多次选择！！！\n");
    printf("\t*注意：录入项目时默认先男后女！！！\n");
    printf("\t*注意：初次使用请先使用功能1录入数据！！！\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\t");
    printf("请输入您的选择(1-9):");
    return gainint(&a, 1, 9);
}
