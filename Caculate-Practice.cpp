#include <iostream>
#include <time.h>
#include <cstdlib>
#include <string>
#include <stack>
#include <map> 
using namespace std;

// 随机符号
char creat_symbol()
{
    int n = rand()%4;
    char sym;
    switch(n)
    {
        case 0: sym='+';break;
        case 1: sym='-';break;
        case 2: sym='*';break;
        case 3: sym='/';break;
    }
return sym;
}

// 随机括号
string bracket(string n)
{
    int random=rand()%2;
    if (random==1)
    {
        n='('+n+')';
    }
return n; 
}

// 数字转字符串
string int_str(int number)
{
    char str[1];
    itoa(number,str,10);
    string i_s = str;
return i_s;
}

// 连接数字运算符
string connect(string str1,string str2,char a)
{
    string equ = str1+a+str2;
return equ;
}

// 将中缀表达式转换成后缀表达式
string InfixToPostfix(string infix)
{
    char current = 0;
    string postfix;//后缀表达式

    stack<char> mark;//符号栈

    map<char,int> priority;//符号优先级
    priority['+'] = 0;
    priority['-'] = 0;
    priority['*'] = 1;
    priority['/'] = 1;

    for(int i = 0;i < infix.size(); ++i)
    {
        current = infix[i];
        switch(current)
        {
            case '0':case '1':case '2':case '3':case '4':case '5':
            case '6':case '7':case '8':case '9':case '.':
                postfix.push_back(current);//数字直接写入
                break;
            case '+':case '-':case '*':case '/':
                //如果运算符的前一项不是右括号即说明前一个数字输入完毕，用#标识
                if(infix[i-1] != ')')
                    postfix.push_back('#');
                //如果符号栈非空，即比较目前符号与栈顶符号优先级，低于等于出栈(并写入输出字符串)，
                //直至符号全部出栈或者遇到了'('或者大于栈顶符号的优先级
                if(!mark.empty())
                {
                    char tempTop = mark.top();
                    while(tempTop != '(' && priority[current] <= priority[tempTop])
                    {
                        postfix.push_back(tempTop);
                        mark.pop();
                        if(mark.empty())
                            break;
                        tempTop = mark.top();
                    }
                }
                mark.push(current);//新符号入栈
                break;
            case '(':
                if(infix[i-1] >= '0' && infix[i-1] <= '9')// for expression 2-5*2(6/2)
                {
                    postfix.push_back('#');
                    mark.push('*');
                }
                mark.push(current);
                break;
            case ')':
                postfix.push_back('#');//右括号说明前方数字输入完成，标识一下
                while(mark.top() != '(')
                {
                    postfix.push_back(mark.top());
                    mark.pop();
                }
                mark.pop();//左括号出栈
                break;
            default:
                break;//忽略其他字符
        }
    }
    if(infix[infix.size()-1] != ')')
        postfix.push_back('#');//中缀表达式最后一个是数字需要加上#。
    while(!mark.empty())//如果栈非空，全部出栈并写入输出字符串
    {
        postfix.push_back(mark.top());
        mark.pop();
    }
    return postfix;
}

// 计算后缀表达式
float posfixCompute(string s)
{
    stack<float> tempResult;

    string strNum;
    float currNum = 0;

    float tempNum = 0;
    for(string::const_iterator i = s.begin(); i != s.end(); ++i)
    {
        switch(*i)
        {
            case '0':case '1':case '2':case '3':case '4':case '5':
            case '6':case '7':case '8':case '9':case '.':
                strNum.push_back(*i);
                break;
            case '+':
                tempNum = tempResult.top();
                tempResult.pop();
                tempNum += tempResult.top();
                tempResult.pop();
                tempResult.push(tempNum);
                break;
            case '-':
                tempNum = tempResult.top();
                tempResult.pop();
                tempNum = tempResult.top() - tempNum;
                tempResult.pop();
                tempResult.push(tempNum);
                break;
            case '*':
                tempNum = tempResult.top();
                tempResult.pop();
                tempNum *= tempResult.top();
                tempResult.pop();
                tempResult.push(tempNum);
                break;
            case '/':
                tempNum = tempResult.top();
                tempResult.pop();
                tempNum = tempResult.top() / tempNum;
                tempResult.pop();
                tempResult.push(tempNum);
                break;
            case '#':
                currNum = atof(strNum.c_str());
                strNum.clear();
                tempResult.push(currNum);
                break;
        }
    }
    return tempResult.top();
}


// 表达式计算
float expressionCalculate(string s)
{
    return posfixCompute(InfixToPostfix(s));
}

//记录正确题数
int record(float answer,float input,int language) 
{
	int t=0;
	if(answer==input)
	{
        t++;
        if (language==1)
        {
            cout<<"答案正确"<<endl;
        }
        else
        {
            cout<<"The answer is correct."<<endl;
        }
	}
    else
    {
        if (language==1)
        {
            cout<<"答案错误，正确答案为："<<answer<<endl;
        }
        else
        {
            cout<<"The answer is wrong,the correct answer is:"<<answer<<endl;
        }
    }
	return t;
}

//显示结果 
void result(int t,int f,int language)
{
	char end;
	if(language==1)//中文的显示结果 
	{
        cout<<"题已答完，输入'Q'(或'q')显示测试结果"<<endl;
		cin>>end;
        if(end=='Q'||end=='q')
		{
		    cout<<"恭喜你答对了："<<t<<"题!"<<endl;
			cout<<"很遗憾你打错了："<<f<<"题!"; 
	    }		
    }
	else if(language==2)//英文的结果显示 
	{
		cout<<"Questions have been answered, enter the 'Q'(or 'q') display test results"<<endl; 
		cin>>end;
		if(end=='Q'||end=='q')
		{
			if(t>1)//选择英文question是否加s
			{
				cout<<"Congratulations on "<<t<<" questions!"<<endl;
			}
			else if(t<2)
			{
				cout<<"Congratulations on "<<t<<" question!"<<endl;
			}
			if(f>1)
			{
				cout<<"It is a pity that you missed "<<f<<" questions!"<<endl; 
			}
			else if(f<2)
			{
				cout<<"It is a pity that you missed "<<f<<" question!"<<endl; 
			}
	    }
	}
	return ;
}

int main()
{
    srand(unsigned(time(0)));
    int count,i,j,n1,n2,exchange,t=0,f,language,temp2;
    string str_n1,str_n2,temp;
    char symbol,end;
    cout<<"如果结果为小数，请精确到小数点后2位。\nIf the result is a decimal, please be accurate to two decimal place."<<endl;
    cout<<"============================================================================"<<endl;
    cout<<"请输入编号选择语言：1.中文  2.英文"<<endl;
    cout<<"Please enter the serial number selection language: 1.Chinese  2.English" <<endl;
	cin>>language;
    if(language==1)cout<<"请输入即将生成题目的数量:";
    else cout<<"Please enter the number of topics to be generated:"; 
    cin>>count;
    string equation[count];
    float *answer = new float[count];
    float *input = new float[count];
    for (i = 0; i < count; i++)
    {
        n1=rand()%11;
        n2=rand()%11;
        symbol=creat_symbol();
        str_n1=int_str(n1);
        str_n2=int_str(n2);
        equation[i]=connect(str_n1,str_n2,symbol);
        for (j = 0; j < 2; j++)
        {           
            str_n1=equation[i];
            str_n1=bracket(equation[i]);
            n2=rand()%11;
            str_n2=int_str(n2);
            // 对字符串位置进行随机交换
            exchange=rand()%2;
            if (exchange==1)
            {
                temp=str_n1;
                str_n1=str_n2;
                str_n2=temp;
            }
            symbol=creat_symbol();
            equation[i]=connect(str_n1,str_n2,symbol);
        }
        cout<<'<'<<i+1<<">. "<<equation[i]<<'=';
        cin>>input[i];
        answer[i]=expressionCalculate(equation[i]);
        //四舍五入保留两位小数
        temp2=(float)(answer[i]*100+0.5f);
        answer[i]=(float)temp2/100;
        //正确题目数量和是否正确的提示
        t+=record(answer[i],input[i],language);
        //错误题目数量 
		f=count-t;
        //作答结束后调用函数显示结果 
		if(i==count-1)
		result(t,f,language);
    }
    delete [] answer;
    delete [] input;
return 0;
}
