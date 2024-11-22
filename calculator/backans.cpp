#include <backans.h>

int priority(char ope)  //返回运算符优先级
{
    switch (ope) {
    case '#':
    case '(':
        return 0;
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
    case '%':
        return 2;
    case ')':
        return 3;
    default:
        return 0;
    }
}
bool isOpe(char arr)    //判断是否是操作符
{
    switch (arr) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '(':
    case ')':
        return true;
    default:
        return false;
    }
}
long double turnnum(string str, int wz)   //将字符串转化为数字并且返回
{
    long double sum[100] = { 0 }, sum1[100] = { 0 }, result = 0;
    int i = 0, q = 0, flag = 1, isFs = 0;
    if(str[wz] == '-')
    {
        isFs = 1;
        wz++;
    }
    while ( !isOpe(str[wz]) && str[wz] != ' ' )
    {
        if(str[wz] != 46 && flag){
            sum[i] = str[wz]-48;
            i++;
        }
        else if(str[wz] == 46)
            flag = false;
        else{
            sum1[q] = str[wz]-48;
            q++;
        }
        wz++;
    }
    int k = i - 1;
    for (int j = 0; j < i; j++,k--)          //整数部分
        result += (sum[j] * pow(10, k));
    long double xiaoshu = 0;
    k = -1;
    for(int j = 0; j < q; j++,k--)             //小数部分
        xiaoshu += (sum1[j] * pow(10, k));
    return isFs?-(result + xiaoshu):(result+xiaoshu);
}
bool Number(char ch)//判断是否为数字，是则返回true
{
    if ( (ch >= 48 && ch <= 57) || ch == 46)
        return true;
    else
        return false;
}
string getback(string str)//获取后缀表达式的函数
{
    char* middle = new char[100];
    char* tmp = middle;
    char* isFirst = tmp;
    for (int i=0; i<str.length(); i++) {
        *tmp = str[i];                                    //将 middle 所指向的字符串内容赋值为传入的 str ，同时保持 middle 指向首地址不变
        tmp++;
    }
    char* back = new char[100];             //同上
    char* backend = back;
    stack<char> s;
    s.push('#');
    while (*middle)
    {
        if( ((middle == isFirst)&& *middle == '-' && Number(*(middle+1))) || ( *(middle-1) == '(' && *middle == '-' && Number(*(middle+1))) || Number(*middle))
        {
            *back = *middle;                                       //判断是否为负数
            back++, middle++;
        }
        else
        {
            if (Number(*(back - 1)))    *back++ = ' ';     //如果前一位是数字的话添加空格 用以区分

            if (*middle == ')')//如果右括号的话，输出所有操作符直到遇到左括号，并抛弃相对应的一堆括号
            {
                while (s.top() != '(' && s.top() != '#')
                {
                    *back = s.top();
                    s.pop();
                    back++;
                        *back++ = ' ';
                }
                middle++;
                s.pop();//抛弃左括号
            }
            else if (*middle == '(')//遇到左括号，则进入栈
            {
                s.push(*middle); middle++;
            }
            else if (priority(*middle) > priority(s.top()))//如果栈内的操作符优先级高于栈外的优先级，则入栈
            {
                s.push(*middle); middle++;
            }
            else if (priority(*middle) <= priority(s.top()))
                                                     //如果栈内的操作符优先级低于或等于栈外的优先级，输出栈内的符号，并入栈栈外的符号
            {
                while (priority(*middle) <= priority(s.top()) && s.top() != '#') {
                    *back = s.top();
                    back++;                                                                 //直到栈内的操作符为空 或者 低于栈外的优先级
                    s.pop();
                        *back++ = ' ';
                }
                s.push(*middle);
                middle++;
            }
        }
    }
    while (isOpe(s.top()))//中缀表达式遍历完成，但是=栈中还有符号存在，一一出栈输出
    {
        if (Number(*(back - 1)))    *back++ = ' ';
        *back = s.top();
        qDebug("%c",*back);
        s.pop();
        if(s.top() != '#'){
            back++;
            *back++ = ' ';
        }
    }
    string tmpresult = "";                      //后面这些由于某些蜜汁bug而做出的一些处理。。。。。充满了妥协
    string result = "";
    int address = 0;
    for (;backend<=back;backend++)
        tmpresult += *backend;
    while(Number(tmpresult[address]) || isOpe(tmpresult[address]) || tmpresult[address] == ' ')
        result += tmpresult[address++];

    return result;
}

long double Cauculate(char ch, long double left, long double right)//各个操作符对应的操作
{
    switch (ch)
    {
    case '+':
        return left + right;
    case '-':
        return left - right;
    case '*':
        return left * right;
    case '/':
        return left / right;
    case '%':
        return int(left)%int(right);
    default:
        return 9;
    }
}

long double backans::result(string str)
{
    string back = getback(str);
    stack<long double> s;
    for (int i=0; i<back.length(); ) {
        if(!isOpe(back[i]) || (back[i] == '-' && Number(back[i+1]) )){                              //将数字依次入栈
            s.push(turnnum(back, i));
            while (back[i] != ' ')
                i++;
            i++;
        }
        else {
            long double a = s.top();
            s.pop();
            long double b = s.top();
            s.pop();
            s.push(Cauculate(back[i], b, a));//遇到符号时，取栈顶的第二个数和第一个数求解，并入栈
            i+=2;
        }
    }
    while (s.size() >= 2)//最终栈内存在的数大于2时，继续计算，直到只剩下一个数
    {
        long double a = s.top();
        s.pop();
        long double b = s.top();
        s.pop();
        s.push(Cauculate(back[back.length()-1], b, a));
    }
    //返回这个数字，既是最终结果
    return s.top();
}

