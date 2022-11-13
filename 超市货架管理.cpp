#include <iostream>
#include<vector>
#include<stack>
using namespace std;

 //商品类,商品信息
class Commodit     
{
public:
    string name;      //商品名称
    int num;        //数量
    int year;       //年份
    int month;      //月份
    int day;        //日期
};
//货架类
class Shelves       
{
private:
    Commodit* data;             //商品信息
public:
    void ComInit(stack<Commodit>&s, vector<stack<Commodit>>&v);//初始化
    void PutCom(stack<Commodit>&s, vector<stack<Commodit>>&v);//上货
    void OutCom(stack<Commodit>&s, vector<stack<Commodit>>&v);//出货
    void PrintCom(stack<Commodit>&s, vector<stack<Commodit>>&v);//显示货物的信息
};
                                                      //初始化商品
void Shelves::ComInit(stack<Commodit>&s, vector<stack<Commodit>>&v)    
{
    int ComNUM;                                              //商品种类数量
    cout << "请输入商品种类数量：" << endl;
    cin >> ComNUM;
    for (int i = 0; i <= ComNUM - 1; i++)
    {
        Commodit  C;                                        //商品类信息作为结点
        stack<Commodit> s;
        cout << "商品名称：" << endl;                       //商品名称
        cin >> C.name;                                      
        cout << "商品数量：" << endl;                       //商品数量
        cin >> C.num;
        if (C.num > 100)
        {
            C.num = 100;
        }
        cout << "商品的日期：（年--月--日）：" << endl;     //商品日期
        cin >> C.year >> C.month >> C.day;
        cout << endl;
        s.push(C);                                          //商品信息作为结点进栈
        v.push_back(s);                                     //栈作为数组元素进数组
    }
}
                        //营业时间售卖出货
void Shelves::OutCom(stack<Commodit>&s, vector<stack<Commodit>>&v)
{
    string BuyName;                                         //输入需要购买的商品名称
    int BuyNum,count=0;
    cout << "输入需要购买的商品的名称：" << endl;
    cin >> BuyName;                                         //要购买的数量
    cout << "输入需要购买的数量：" << endl;
    cin >> BuyNum;
    for (int i = 0; i <= v.size() - 1; i++)
    {
        if (!v[i].empty())
        {
            v[i].top();
            if (v[i].top().name == BuyName && BuyNum > 0)   //找到名称对应的商品，并且要购买的数量要保证大于0
            {
                stack<Commodit> temp;                       //临时的栈来储存
                while (!v[i].empty())                       //先统计栈里面此类商品的总数Num
                {
                    Commodit C;
                    count = v[i].top().num + count;         //计算栈里面商品总共的数量：count
                    C = v[i].top();
                    v[i].pop();
                    temp.push(C);                           //另一个栈保存至原本的栈为空
                }
                while (!temp.empty())                       //倒栈还回来至临时的栈为空
                {
                    Commodit Temp;
                    Temp = temp.top();
                    temp.pop();
                    v[i].push(Temp);
                }
                if (count < BuyNum)                             //需要购买的数量大于库存，提示需要上货
                {
                    cout << "商品数量不足，需要上货。" << endl;
                }
                if (count >= BuyNum)                            //库存大于购买量，够数量售卖
                {
                    if (v[i].top().num == BuyNum)               //比较栈顶元素结点的num和需要购买的数量大小
                    {
                        v[i].pop();                             //栈顶元素与购买量相等，则直接出栈。  
                        if (v[i].empty())
                        {
                            cout << "此商品售至数量为0，货架上不存在这个商品，需要重新初始化。" << endl;      //数量为0时，货架上不存在这个东西，要重新初始化
                            break;                              //为什么不加break时，当唯一结点num正好买完时候，栈空会报错？
                        }
                        break;
                    }
                    if (v[i].top().num > BuyNum)                //栈顶元素的num比需要购买的大，则数量直接相减
                    {
                        v[i].top().num = v[i].top().num - BuyNum;
                        break;
                    }
                    if (v[i].top().num < BuyNum)                //若栈顶元素的num比需要购买的小，则先出栈后再取新的栈顶元素进行判断
                    {
                        BuyNum = BuyNum - v[i].top().num;
                        v[i].pop();
                        while (!v[i].empty())                   //往下新的栈顶元素进行判断比较
                        {
                            if (v[i].top().num == BuyNum)       //栈顶元素num等于购买量时，出栈
                            {
                                v[i].pop();
                                break;
                            }
                            if (v[i].top().num > BuyNum)                //num比购买量大，数量相减
                            {
                                v[i].top().num = v[i].top().num - BuyNum;
                                break;
                            }
                            if (v[i].top().num < BuyNum)            //仍然不足时，出栈再取新的栈顶元素再判断
                            {
                                BuyNum = BuyNum - v[i].top().num;
                                v[i].pop();
                            }
                        }
                    }
                }
            }
        }
    }
}   
                         //营业后上货补货
void Shelves::PutCom(stack<Commodit>&s, vector<stack<Commodit>>&v)
{
    string InName;
    int count = 0;
    cout << "输入需要上货的商品的名称：" << endl;
    cin >> InName;
    for (int i = 0; i <= v.size() - 1; i++)
    {
        if (!v[i].empty())
        {
            v[i].top();
            if (v[i].top().name == InName)
            {
                stack<Commodit> temp;                   //临时的栈储存
                stack<Commodit> sort;                   //排序栈
                while (!v[i].empty())
                {
                    Commodit C;
                    count = v[i].top().num + count;         //统计原本的栈里面商品的总数
                    C = v[i].top();
                    v[i].pop();
                    temp.push(C);                       //倒栈，至原本的栈为空
                }
                if (count == 100)
                {
                    cout << "货架上容量已满，不需要上货。" << endl;
                    break;
                }   
                Commodit Add;                                   //上货，作为新结点
                Add.name = InName;
                cout << "输入需要新上货的商品数量：" << endl;        //输入新上货商品的数量
                cin >> Add.num;
                if (count + Add.num > 100)                      //保证货架容量为100，修正数值
                {
                    Add.num = 100 - count;
                }
                cout << "输入需要新上货的商品的日期：" << endl;       //输入新上货商品的日期
                cin >> Add.year >> Add.month >> Add.day;
                //进行排序，保证打印信息日期最近的在下面，年份的比较
                if (Add.year < temp.top().year)                    
                {
                    while (Add.year < temp.top().year)              
                    {
                        Commodit comsort;
                        comsort = temp.top();
                        temp.pop();                             //栈顶元素出栈
                        sort.push(comsort);                     //进行判断是否与新的栈顶元素日期相同
                        if (!temp.empty() && Add.year == temp.top().year && Add.month == temp.top().month && Add.day == temp.top().day)
                        {
                            Add.num = Add.num + temp.top().num;     //与新的栈顶元素日期相等，上货的数量修正加上原本在栈里的商品数量
                            temp.pop();                             //新的栈顶元素出栈
                            break;                                  //break 出while 让上货的结点进栈
                        }
                        if (temp.empty())
                        {
                            break;
                        }
                    }
                    temp.push(Add);                                 //排序完成进栈
                    while (!sort.empty())
                    {
                        Commodit backsort;
                        backsort = sort.top();
                        sort.pop();
                        temp.push(backsort);
                    }
                }
                //进行排序，保证打印信息日期最近的打印出来在下面，年份相等的情况下月份的比较
                if (Add.year == temp.top().year && Add.month < temp.top().month)
                {
                    while (Add.year == temp.top().year && Add.month < temp.top().month)
                    {
                        Commodit comsort;
                        comsort = temp.top();
                        temp.pop();                         //栈顶元素出栈
                        sort.push(comsort);                 //进行判断是否与新的栈顶元素日期相同
                        if (!temp.empty() && Add.year == temp.top().year && Add.month == temp.top().month && Add.day == temp.top().day)
                        {
                            Add.num = Add.num + temp.top().num;     //与新的栈顶元素日期相等，上货的数量修正加上原本在栈里的商品数量
                            temp.pop();                             //新的栈顶元素出栈
                            break;                                  //break 出while 让上货的结点进栈
                        }
                        if (temp.empty())
                        {
                            break;
                        }
                    }
                    temp.push(Add);                                     //排序完成进栈
                    while (!sort.empty())
                    {
                        Commodit backsort;
                        backsort = sort.top();
                        sort.pop();
                        temp.push(backsort);
                    }
                }
                //进行排序，保证打印信息日期最近的打印出来在下面，年份月份相等的情况下月份的比较
                if (Add.year == temp.top().year && Add.month == temp.top().month && Add.day < temp.top().day)
                {
                    while (Add.year == temp.top().year && Add.month == temp.top().month && Add.day < temp.top().day)
                    {
                        Commodit comsort;
                        comsort = temp.top();
                        temp.pop();                     //栈顶元素出栈
                        sort.push(comsort);             //进行判断是否与新的栈顶元素日期相同
                        if (!temp.empty()&& Add.year == temp.top().year && Add.month == temp.top().month && Add.day == temp.top().day)
                        {
                            Add.num = Add.num + temp.top().num;         //与新的栈顶元素日期相等，上货的数量修正加上原本在栈里的商品数量  
                            temp.pop();                                 //新的栈顶元素出栈       
                            break;                                      //break 出while 让上货的结点进栈
                        }
                        if (temp.empty())
                        {
                            break;
                        }
                    }
                    temp.push(Add);                                        //排序完成进栈
                    while (!sort.empty())
                    {
                        Commodit backsort;
                        backsort = sort.top();
                        sort.pop();
                        temp.push(backsort);
                    }
                }
                //日期相等的情况中，与栈顶元素日期相等的情况
                if (Add.year == temp.top().year && Add.month == temp.top().month && Add.day == temp.top().day)
                {
                    temp.top().num = Add.num + temp.top().num;
                }
                //新上货的日期为最近最新的，不需要排序，直接上货
                if (Add.year > temp.top().year || (Add.year == temp.top().year && Add.month > temp.top().month)
                    || (Add.year == temp.top().year && Add.month == temp.top().month && Add.day > temp.top().day))
                {
                    temp.push(Add);                                 //因为倒栈，商品在临时储存的栈里面
                }        
                while (!temp.empty() && count<100)             //倒栈回来，至临时的栈为空
                {
                    Commodit Temp;
                    Temp = temp.top();
                    temp.pop();
                    v[i].push(Temp);                    
                }
            }
        }
    }
}
                                                //打印商品所有信息
void Shelves::PrintCom(stack<Commodit>&s, vector<stack<Commodit>>&v)       
{
    string Secondname;                                                          
    cout << "输入需要打印的商品的名称：" << endl;
    cin >> Secondname;
    for (int i=0;i<=v.size()-1;i++)        //遍历动态数组vector
    {
        if(!v[i].empty())
        {
            v[i].top();
            if (v[i].top().name == Secondname)
            {
                stack<Commodit> temp;                       //临时的一个栈储存
                while (!v[i].empty())
                {
                    Commodit C;
                    C = v[i].top();                           
                    cout << "商品名称为：" << v[i].top().name << endl;                  //打印信息
                    cout << "商品数量为：" << v[i].top().num << endl;
                    cout << "商品的生产日期为：" << v[i].top().year << "-" << v[i].top().month << "-" << v[i].top().day << endl;
                    v[i].pop();
                    temp.push(C);                      
                }
                while (!temp.empty())                    //倒栈回来，至原本栈为空
                {
                     Commodit Temp;
                     Temp = temp.top();
                     temp.pop();
                     v[i].push(Temp);
                }
            }
        }
    }
}

int main()
{
    Shelves S;                              //货架
    Commodit *com;                          //商品信息
    com = new Commodit;
    stack<Commodit> s;                      //STL stack 
    vector<stack<Commodit>> v;               //动态数组vector
    while (1)                               //菜单
    {
        cout << "--------------" << endl;
        cout << "超市货架管理" << endl;
        cout << "--------------" << endl;
        cout << "1.商品初始化" << endl;
        cout << "2.商品营业时间期间售卖" << endl;
        cout << "3.商品营业时间结束上货" << endl;
        cout << "4.商品信息打印" << endl;
        cout << "5.退出" << endl;
        cout << "--------------" << endl;
        cout << endl;
        cout << "进行选择：" << endl;
        int select;
        cin >> select;                         //菜单选择
        switch (select)
        {
        case 1:                                 //1.初始化
            S.ComInit(s,v);
            break;
        case 2:                                 //2.营业时间售卖
            S.OutCom(s,v);
            break;
        case 3:                                 //3.营业结束上货
            S.PutCom(s,v);
            break;
        case 4:                                 //4.商品信息打印
            S.PrintCom(s,v);
            break;
        case 5:                                 //5.退出
            exit(0);
        default:
            break;
        }
    }return 0;
}
//最后一行