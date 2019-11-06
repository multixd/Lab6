#include "arithmeticExpression.h"
#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <fstream>

int arithmeticExpression::priority(char op){
    int priority = 0;
    if(op == '('){
        priority =  3;
    }
    else if(op == '*' || op == '/'){
        priority = 2;
    }
    else if(op == '+' || op == '-'){
        priority = 1;
    }
    return priority;
}

bool arithmeticExpression::isLeaf(TreeNode* curr) {
	if(curr-> left == NULL && curr-> right == NULL) {
		return true;
	}
	return false;
}

string arithmeticExpression::infix_to_postfix(){
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

/*void arithmeticExpression::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error opening "<< outputFilename<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;void buildTree();
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}*/

arithmeticExpression::arithmeticExpression(const string &exp) {
	infixExpression = exp;
	root = NULL;
}

void arithmeticExpression::buildTree() {
	string postfixExpression = infix_to_postfix();
	std::cout << postfixExpression << std::endl;
	stack<TreeNode*> s;
	char c;

	for(unsigned i = 0; i< postfixExpression.size();++i){
		c = postfixExpression.at(i);
		
		if(c != '+' && c != '-' && c != '*' && c != '/' ) {
			//std::cout << "?" << std::endl;
			s.push((new TreeNode(c,'a')));
		}
		else if( c == '+' || c == '-' || c == '*' || c == '/') {
			//std::cout << "!" << std::endl;
			TreeNode *one = s.top();
			s.pop();
			TreeNode *two = s.top();
			s.pop();
			TreeNode *three = new TreeNode(c,'a');
			three->left = two;
			three->right = one;
			s.push(three);
			//std::cout << "@" << std::endl;
		}
	}
	TreeNode* top = s.top();
	root = top;
	s.pop();
	
	if(!s.empty()) {
		std::cout << "Error!" << std::endl;
	}
}
	
void arithmeticExpression::infix(TreeNode *curr) {
	if(curr == NULL) {
		return;
	}
	
	if(isLeaf(curr)) {
		std::cout << curr-> data;
	}
	else {
		std::cout <<"(";
		infix(curr->left);
		std::cout << curr -> data;
		infix(curr -> right);
		std::cout << ")";
	}

}	

void arithmeticExpression::infix() {
	infix(root);
}

void arithmeticExpression::prefix(TreeNode *curr) {
	if(curr == NULL) {
		return;
	}
	
	std::cout << curr->data;
	prefix(curr->left);
	prefix(curr-> right);
}

void arithmeticExpression::postfix(TreeNode *curr) {
	if(curr == NULL) {
		return;
	}
	postfix(curr->left);
	postfix(curr-> right);
	std::cout << curr->data;
}

void arithmeticExpression::prefix() {
	prefix(root);
}

void arithmeticExpression::postfix() {
	postfix(root);
}
