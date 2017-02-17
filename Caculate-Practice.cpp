#include <iostream>
#include <time.h>
#include <cstdlib>
#include <string>
#include <stack>
#include <map> 
using namespace std;

// �������
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

// �������
string bracket(string n)
{
    int random=rand()%2;
    if (random==1)
    {
        n='('+n+')';
    }
return n; 
}

// ����ת�ַ���
string int_str(int number)
{
    char str[1];
    itoa(number,str,10);
    string i_s = str;
return i_s;
}

// �������������
string connect(string str1,string str2,char a)
{
    string equ = str1+a+str2;
return equ;
}

// ����׺���ʽת���ɺ�׺���ʽ
string InfixToPostfix(string infix)
{
    char current = 0;
    string postfix;//��׺���ʽ

    stack<char> mark;//����ջ

    map<char,int> priority;//�������ȼ�
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
                postfix.push_back(current);//����ֱ��д��
                break;
            case '+':case '-':case '*':case '/':
                //����������ǰһ��������ż�˵��ǰһ������������ϣ���#��ʶ
                if(infix[i-1] != ')')
                    postfix.push_back('#');
                //�������ջ�ǿգ����Ƚ�Ŀǰ������ջ���������ȼ������ڵ��ڳ�ջ(��д������ַ���)��
                //ֱ������ȫ����ջ����������'('���ߴ���ջ�����ŵ����ȼ�
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
                mark.push(current);//�·�����ջ
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
                postfix.push_back('#');//������˵��ǰ������������ɣ���ʶһ��
                while(mark.top() != '(')
                {
                    postfix.push_back(mark.top());
                    mark.pop();
                }
                mark.pop();//�����ų�ջ
                break;
            default:
                break;//���������ַ�
        }
    }
    if(infix[infix.size()-1] != ')')
        postfix.push_back('#');//��׺���ʽ���һ����������Ҫ����#��
    while(!mark.empty())//���ջ�ǿգ�ȫ����ջ��д������ַ���
    {
        postfix.push_back(mark.top());
        mark.pop();
    }
    return postfix;
}

// �����׺���ʽ
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


// ���ʽ����
float expressionCalculate(string s)
{
    return posfixCompute(InfixToPostfix(s));
}

//��¼��ȷ����
int record(float answer,float input,int language) 
{
	int t=0;
	if(answer==input)
	{
        t++;
        if (language==1)
        {
            cout<<"����ȷ"<<endl;
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
            cout<<"�𰸴�����ȷ��Ϊ��"<<answer<<endl;
        }
        else
        {
            cout<<"The answer is wrong,the correct answer is:"<<answer<<endl;
        }
    }
	return t;
}

//��ʾ��� 
void result(int t,int f,int language)
{
	char end;
	if(language==1)//���ĵ���ʾ��� 
	{
        cout<<"���Ѵ��꣬����'Q'(��'q')��ʾ���Խ��"<<endl;
		cin>>end;
        if(end=='Q'||end=='q')
		{
		    cout<<"��ϲ�����ˣ�"<<t<<"��!"<<endl;
			cout<<"���ź������ˣ�"<<f<<"��!"; 
	    }		
    }
	else if(language==2)//Ӣ�ĵĽ����ʾ 
	{
		cout<<"Questions have been answered, enter the 'Q'(or 'q') display test results"<<endl; 
		cin>>end;
		if(end=='Q'||end=='q')
		{
			if(t>1)//ѡ��Ӣ��question�Ƿ��s
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
    cout<<"������ΪС�����뾫ȷ��С�����2λ��\nIf the result is a decimal, please be accurate to two decimal place."<<endl;
    cout<<"============================================================================"<<endl;
    cout<<"��������ѡ�����ԣ�1.����  2.Ӣ��"<<endl;
    cout<<"Please enter the serial number selection language: 1.Chinese  2.English" <<endl;
	cin>>language;
    if(language==1)cout<<"�����뼴��������Ŀ������:";
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
            // ���ַ���λ�ý����������
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
        //�������뱣����λС��
        temp2=(float)(answer[i]*100+0.5f);
        answer[i]=(float)temp2/100;
        //��ȷ��Ŀ�������Ƿ���ȷ����ʾ
        t+=record(answer[i],input[i],language);
        //������Ŀ���� 
		f=count-t;
        //�����������ú�����ʾ��� 
		if(i==count-1)
		result(t,f,language);
    }
    delete [] answer;
    delete [] input;
return 0;
}
