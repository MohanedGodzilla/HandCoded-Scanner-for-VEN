#include<iostream>
#include<fstream>
#include<string>
using namespace std;
string s="";
enum Token{BEGIN_TOKEN,END_TOKEN,PROC_TOKEN,EQUAL_SY,LEFTPAR_SY,RIGHTPAR_SY,INTEGER_TOKEN,BOOLEAN_TOKEN,COMA_SY,
	SIMI_COLOUN,ASSIGN_SY,READ_TOKEN,WRITE_TOKEN,IF_TOKEN,THEN_TOKEN,ELSE_TOKEN,WHILE_TOKEN,DO_TOKEN,CALL_TOKEN,
	OR_TOKEN,AND_TOKEN,NOT_TOKEN,GE_SY,G_SY,SE_SY,S_SY,NOTEQUAL_SY,PLUS_SY,MINUS_SY,DIVISION_SY,MULTI_SY,
	NAME_TOKEN,NUMBERAL_TOKEN, END_OF_FILE_SY, ERROR_SY};

class Scanner{
public:
	Scanner(string filename);
	~Scanner(void);
	Token get_token(void);
	void display_tokens(void);
private:
	ifstream f;
	Token check_reserved(string s)
	{
		if (s=="begin")
			return BEGIN_TOKEN;
		else if (s=="end")
			return END_TOKEN;
		else if (s=="proc")
			return PROC_TOKEN;
		else if (s=="integer")
			return INTEGER_TOKEN;
		else if (s=="boolean")
			return BOOLEAN_TOKEN;
		else if (s=="read")
			return READ_TOKEN;
		else if (s=="write")
			return WRITE_TOKEN;
		else if (s== "if")
				return IF_TOKEN;
		else if (s== "then")
			return THEN_TOKEN;
		else if (s== "else")
			return ELSE_TOKEN;
		else if (s== "while")
			return WHILE_TOKEN;
		else if (s== "do")
			return DO_TOKEN;
		else if (s=="call")
			return CALL_TOKEN;
		else if (s== "or")
			return OR_TOKEN;
		else if (s== "and")
			return AND_TOKEN;
		else if (s== "not")
			return NOT_TOKEN;
		else return NAME_TOKEN;
	}
};

Scanner::Scanner(string filename){
	f.open(filename);
	if(!f)
	{
		cout<<"unable to open the file"<<endl;
		system("pause");
		exit(1);
	}
}

Scanner::~Scanner(){
	f.close();
}

Token Scanner::get_token(void){
	char ch;
	f.get(ch);
	while(!f.eof() && isspace(ch))
	{
		f.get(ch);
	}
	if(f.eof())
		return END_OF_FILE_SY;
	else if (ch == '(')
		return LEFTPAR_SY;
	else if (ch == ')')
		return RIGHTPAR_SY;
	else if (ch == '=')
		return EQUAL_SY;
	else if (ch == ',') 
		return COMA_SY;
	else if (ch == ';')
		return SIMI_COLOUN;
	else if (ch == ':') {
			   f.get(ch);
			   if (ch == '=') 
				   return ASSIGN_SY;
			   else {
				   f.putback(ch);
				   return ERROR_SY;
			   }
		   }
	else if (ch == '+')
		return PLUS_SY;
	else if (ch == '*')
		return MULTI_SY;
	else if (ch == '-')
		return MINUS_SY;
	else if (ch == '/')
		return DIVISION_SY;
	else if (ch == '<')
	{
		f.get(ch);
		if (ch == '>')
			return NOTEQUAL_SY;
		else if(ch == '=')
			return SE_SY;
		else {
			f.putback(ch);
			return S_SY;
		}
	}
	else if (ch == '<')
	{
		f.get(ch);
		if (ch == '>')
			return NOTEQUAL_SY;
		else if(ch == '=')
			return SE_SY;
		else {
			f.putback(ch);
			return S_SY;
		}
	}
	else if (ch == '>')
	{
		f.get(ch);
		if(ch == '=')
			return GE_SY;
		else {
			f.putback(ch);
			return G_SY;
		}
	}

	else if (isalpha(ch))
	{
		s = ch; 
		f.get(ch);
		while (!f.eof() && isalnum(ch))
		{ 
			s += ch;
			f.get(ch); 
		}
		f.putback(ch);
		check_reserved(s);
	}

	else if ( isdigit(ch)) // output is integer
	{ 
		s = ch; 
		f.get(ch);
		while (!f.eof() && isdigit(ch))
		{ 
			s += ch; 
			f.get(ch); 
		}

		f.putback(ch); 
		return NUMBERAL_TOKEN; 
	}
	else 
		return ERROR_SY;
}

void Scanner::display_tokens(void)
{
	Token t=get_token();
	while(t!= END_OF_FILE_SY)
	{
		switch (t)
		{
			case ERROR_SY: cout << "lexical error: illegal token"<<endl; break;
			case BEGIN_TOKEN: cout << "program token"<<endl ; break;
			case PROC_TOKEN: cout << "proc token"<<endl ; break;
			case EQUAL_SY: cout << "Equal symbol"<<endl ; break;
			case LEFTPAR_SY: cout << "lparn token"<<endl ; break;
			case RIGHTPAR_SY: cout << "rparn token"<<endl ; break;
			case INTEGER_TOKEN: cout << "integer token"<<endl ; break;
			case BOOLEAN_TOKEN: cout << "boolean token"<<endl ; break;
			case COMA_SY: cout << "coma token"<<endl; break;
			case SIMI_COLOUN: cout << "simiColon token"<<endl; break;
			case ASSIGN_SY: cout << "assign token"<<endl; break;
			case READ_TOKEN: cout << "read token"<<endl; break;
			case WRITE_TOKEN: cout << "write token"<<endl; break;
			case IF_TOKEN: cout << "if token"<<endl ; break;
			case THEN_TOKEN: cout << "then token"<<endl; break;
			case ELSE_TOKEN: cout << "else token"<<endl ; break;
			case WHILE_TOKEN: cout << "while token"<<endl; break;
			case END_TOKEN : cout<< "end token"<<endl; break;
			case DO_TOKEN: cout << "do token"<<endl; break;
			case CALL_TOKEN: cout << "call token"<<endl; break;
			case OR_TOKEN: cout << "or token"<<endl; break;
			case AND_TOKEN: cout << "and token"<<endl; break;
			case NOT_TOKEN: cout << "not token"<<endl; break;
			case SE_SY: cout << "LessThanOrEqual symbol"<<endl; break;
			case S_SY: cout << "LessThan symbol"<<endl; break;
			case G_SY: cout << "GreaterThan symbol"<<endl; break;
			case GE_SY: cout << "GreaterThanOrEqual symbol"<<endl; break;
			case NOTEQUAL_SY: cout << "NotEqual symbol"<<endl; break;
			case PLUS_SY: cout << "+ is token" <<endl; break;
			case MINUS_SY: cout << "- is token"<<endl; break;
			case MULTI_SY: cout << "* is token"<<endl; break;
			case DIVISION_SY: cout << "/ is token"<<endl; break;
			case NAME_TOKEN: cout << "name token"<<endl; break;
			case NUMBERAL_TOKEN: cout << "number token" <<endl; break;
		}
		t = get_token();
	}

	if (t== END_OF_FILE_SY) 
	{
		cout << "end_of_file " << endl;
	}
}

void main()
{
	string InName;
	cout << "Enter Name of input File : ";
	cin >> InName;
	Scanner in(InName);
	in.display_tokens();
	system("pause");
}