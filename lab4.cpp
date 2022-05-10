#include <iostream> 
#include <set> 
#include <string> 
#include <set>

using namespace std;

struct stack 
	   {
	char info;
	stack* next;
	   };
struct intStack
{
	double info;
	intStack* next;
};
struct list {
	char name;
	double value;
};
int Prior(char);
stack* InStack(stack*, char);
stack* OutStack(stack*, char*);
intStack* InIntStack(intStack*, double);
intStack* OutIntStack(intStack*, double*);

// функция перевода в опз
	// принимает инпут, возвращает оутпут
string turnToOPZ(string input)
{

		string output = "";
		char a, out;
		stack* chars = NULL;
		chars = InStack(chars, NULL);

for (int i = 0; i < input.length(); i++)
{
	if (input[i] != '(' && input[i] != ')' && input[i] != '*' && input[i] != '/' && input[i] != '+' && input[i] != '-')
	{
		output = output + input[i] + ' ';
	}
	else if (input[i] == '(')
		 {
		chars = InStack(chars, input[i]);
		 }
	else if (input[i] == ')')
		 {
		do
		{
			chars = OutStack(chars, &out);
			output = output + out + ' ';
		} while (chars->info != '(');
		chars = OutStack(chars, &out);
		chars = OutStack(chars, &out);
		output = output + out + ' ';
		out = NULL;
		 }
	else if (chars->info == NULL || Prior(input[i]) > Prior(chars->info))
		 {
		chars = InStack(chars, input[i]);
		 }
	else if (Prior(input[i]) <= Prior(chars->info))
		 {
		while (Prior(input[i]) <= Prior(chars->info))
		{
			chars = OutStack(chars, &a);
			output = output + a + ' ';
		}
		chars = InStack(chars, input[i]);
		 }
}
while (chars->info != NULL)
{
	chars = OutStack(chars, &a);
	output = output + a + ' ';
}
return output;
}


double calc_OPZ(string input,int Nn, list num[]) 
{

	intStack* numbers = NULL;
	double out = 0;
    double a = 0;
	double value_1 = 0, value_2 = 0, result = 0;
	for (int i = 0; i < input.length(); i++) {
		
        if (input[i] >=97 && input[i] <=123) {
            
            for (int j = 0; j < Nn ; j++){
            cout <<"i: " << i << endl << "num[i]: " << num[i].value << endl;
            if (input[i] == num[j].name) {
            numbers = InIntStack(numbers, num[j].value);
            }
        }} else
		if (input[i] != ' ') {
			numbers = OutIntStack(numbers, &a);
			value_1 = a;
			//cout << "v1: " << value_1 << endl;
			numbers = OutIntStack(numbers, &a);
			value_2 = a;
			//cout << "v2: " << value_2 << endl;
			switch (input[i]) {
			case '+': result = value_1 + value_2; break;
			case '-': result = value_2 - value_1; break;
			case '*': result = value_1 * value_2; break;
			case '/': try {if (value_1 == 0) throw value_1; result = value_2 / value_1; break;}
            catch (double value_1){
                    cerr << "Exception:: div by zero!" << endl;
            }
			}
            cout << "value 1: " << value_1 << endl;
            cout << "value 2: " << value_2 << endl;
             cout << "result: " << result << endl;
			numbers = InIntStack(numbers, result);
		}
	}
	OutIntStack(numbers, &out);
	return out;
}




int main() {
	
    string input = "", output = "";
	cout << "Input expression: ";
	cin >> input;
    set<char> bukvi;
	for (int i = 0; i < input.length(); i++) 
	{ 
        if (input[i] >= 97 && input[i] <=123)
		bukvi.insert(input[i]);
	}
    int N = bukvi.size();
    list numbers[N];
    set <char>:: iterator it;
    int i = 0;
    for(it = bukvi.begin(); it != bukvi.end(); it++){
        numbers[i].name = *it;
        cout << numbers[i].name << ": "; cin >> numbers[i].value;
        i++;
    }
	cout << endl;
	
	output = turnToOPZ(input);
    cout << "Opz turned::  " << output << endl;
	cout << "Opz calculated:: " calc_OPZ(output,N,numbers) << endl;
	return 0;
}

int Prior(char a) 
	{
		switch (a) 
		{
		case '^': return 4;
		case '*': return 3; 
		case '/': return 3;
		case '+': return 2;
		case '-': return 2;
		case '(': return 1;
		}
	return 0;
	}

stack* InStack(stack* p, char in) 
	   {
	stack* t = new stack;
	t->info = in;
	t->next = p;
	return t;
	   }

stack* OutStack(stack* p, char* out) 
	   {
	stack* t = p;
	*out = p->info;
	p = p->next;
	delete t;
	return p;
	   }

intStack* InIntStack(intStack* p, double in)
{
	intStack* t = new intStack;
	t->info = in;
	t->next = p;
	return t;
}

intStack* OutIntStack(intStack* p, double* out)
{
	intStack* t = p;
	*out = p->info;
	p = p->next;
	delete t;
	return p;
}


