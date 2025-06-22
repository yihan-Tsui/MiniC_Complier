
#include <string>

std::string yacc_program = R"(

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int row, column;
int GoTo(int state, int c);
void error(char const *s);

//处理输入部分
//token 表，存储终结符和非终结符

char idx_token[10000][500];
char * return_token_name(int idx) {
    return idx_token[idx];
}

//产生式表，[0] —— 右部符号个数，[1] —— 左部符号的编号
int producers[2000][100];

int return_producer_len(int idx) {
    return producers[idx][0];
}
int return_producer_left(int idx) {
    return producers[idx][1];
}
//初始化token表&产生式表
void init_producers();


//处理c99.y 的词法分析Lex部分
typedef struct token {
	char * text;
	int line;
	int column;
	int id;
} token;


token * newToken(char * text, int line, int column, int id) {
	token * word = (token *)malloc(sizeof(token));
	int len = strlen(text);
	word->text = (char *)malloc(len * (sizeof(char) + 2));
	strcpy(word->text, text);
	word->line = line;
	word->column = column;
	word->id = id;
	return word;
}

token * read_next_token(int(*scan_)(const char *, ...)) {
	static char text[65536];
	static int line;
	static int column;
	static int id;
	if (scan_("%d < %d , %d > %[^\x06]\x06\n", &id, &line, &column, text) < 4) {
		return NULL;
	}
    return newToken(text, line, column, id);
}

//当前符号

token * curToken;
//读取下一个符号
token * nextToken() {
    curToken = read_next_token(scanf);
    if (curToken == NULL) {
        // 如果读不到新的 token，就手动生成一个“结束标记”token
        return newToken("$", -1, -1, '$');
    }
    // 否则，更新全局的行列号，用于后续错误报告
    row = curToken->line;
    column  = curToken->column;
    // 返回刚读到的有效 token
    return curToken;
}


//处理栈部分，画语法树
typedef struct CSTNode CSTNode;
//具体语法树节点
typedef struct CSTNode {
	int isTerminal; //终结符节点（isTer=1），叶子节点；非终结符节点（isTer=0），非叶子节点
    int idx; //如果是叶子，用 token id；如果是内部节点，用 producerId
	int line;
	int col;
	int childCnt;
	CSTNode ** childs;
	char * caption;//符号名称（从 item_name_table[idx] 获得）
	char * content;//拼接了所有子节点 content 后的字符串，用于打印
} CSTNode;

//创建具体语法树节点
CSTNode * newCSTNode(int isTer, int idx, int line, int col, int childCnt, CSTNode ** childs, char * caption, char * content) {
	CSTNode * node = (CSTNode *)malloc(sizeof(CSTNode));
	node->isTerminal = isTer;
	node->idx = idx;
	node->line = line;
	node->col = col;
	node->childCnt = childCnt;
	node->childs = (CSTNode **)malloc(childCnt * sizeof(CSTNode*));
	for (int i = 0; i < childCnt; ++i) {
		node->childs[i] = childs[i];
	}
	int len = strlen(caption);
	node->caption = (char *)malloc(len * (sizeof(char) + 2));
	strcpy(node->caption, caption);
	len = strlen(content);
	node->content = (char *)malloc(len * (sizeof(char) + 2));
	strcpy(node->content, content);
	return node;
}

//符号栈，语法树节点栈
CSTNode *NodeStack[100000];
//栈顶指针
int      NodeStackPtr = 0;

//返回栈顶节点
CSTNode * returnNodeTop() {
	if (NodeStackPtr == 0) return NULL;
	return NodeStack[NodeStackPtr - 1];
}
//入栈
void NodePush(int isTer, int idx, char * caption, char * content, int childCnt, int line, int col) {
	//空节点栈
	static CSTNode * emptyNodes[1024] = { NULL };
	CSTNode * newNode = newCSTNode(isTer, idx, line, col, childCnt, emptyNodes, caption, content);
	NodeStack[NodeStackPtr] = newNode;
	++NodeStackPtr;
}

//归约阶段所需操作
//在“归约”阶段把若干个子节点从节点栈上弹出，合并成一个新的父节点，再把父节点压回栈顶，并将这些子节点挂到父节点下
void NodeGenerate(int producerId) {
	static char content[100000];
	static CSTNode * childNodes[1024];
	//获取产生式右部符号个数
	int len = producers[producerId][0];
	//获取产生式左部符号编号
	int left = producers[producerId][1];
	int line;
	int col;
	for (int i = len - 1; i >= 0; --i) {
		//获取栈顶节点
		childNodes[i] = returnNodeTop();
		//获取栈顶节点行号
		line = returnNodeTop()->line;
		//获取栈顶节点列号
		col = returnNodeTop()->col;
		//弹出栈顶节点
		--NodeStackPtr;
	}
	//初始化content
	content[0] = '\0';
	//拼接子节点content
	for (int i = 0; i < len; ++i) {
		strcat(content, childNodes[i]->content);
	}
	//压入新节点：产生式左部父节点
	NodePush(0, producerId, idx_token[left], content, len, line, col);
	//为该父节点挂子节点
	for (int i = len - 1; i >= 0; --i) {
		returnNodeTop()->childs[i] = childNodes[i];
	}
}

//``打印语法树
void print_tree(CSTNode * root, int tabs) {
    int cnt = root->childCnt;

    // 打印缩进
    for (int i = 0; i < tabs; ++i) printf("  "); // 每层两个空格缩进，更清晰

    // 终结符节点（叶子）
    if (root->isTerminal) {
        printf("%s\n", root->caption);  // 只打印符号名
    } else {
        // 非终结符节点，打印产生式结构
        int idx = root->idx;
        int len = producers[idx][0];

        // 打印产生式结构：A -> B C D
        printf("%s ->", idx_token[producers[idx][1]]);
        for (int i = 2; i < len + 2; ++i) {
            printf(" %s", idx_token[producers[idx][i]]);
        }
        printf("\n");
    }

    // 递归打印子节点
    for (int i = 0; i < cnt; ++i) {
        print_tree(root->childs[i], tabs + 1);
    }
}


//状态栈
int stateStack[5000000];

//状态栈指针
int stateStackPtr = 0;
//入栈
void stateStackPush(int x) {
    stateStack[stateStackPtr++] = x;
}
//返回栈顶元素
int stateStackTop() {
    return stateStack[stateStackPtr - 1];
}
//出栈
void stateStackPop() {
    --stateStackPtr;
}

int GoTo(int state, int c);

void grammarParse(token *(*nextItem)()) {
    //当前符号
	static char curItemName[1024];
    //初始化状态栈
    stateStackPush(0);
    //读取下一个符号
    token *token = nextItem();
    //当前符号id
    int c = token->id;
    //状态栈不为空
    while (stateStackPtr > 0) {

		//获取当前状态，查GOTO表
	    int state = stateStackTop();

        int goTo  = GoTo(state, c);
        // 错误恢复
        if (goTo == 65536) {
            error("grammar parsing error!");
			//跳过错误 token，直到能继续移进或归约，或读到结束符 "$"
            do {
                if (strcmp(token->text, "$") == 0) goto BAD_STATE;
                token   = nextToken();
                c   = token->id;
                goTo = GoTo(state, c);
            } while (goTo < 0 || goTo == 65536);
        }
        // 移进（shift）
        if (goTo >= 0) {
			//入栈
            stateStackPush(goTo);
            //更新当前符号
            strcpy(curItemName, token->text);
            strcat(curItemName, " ");
            //构造一个叶子节点，把当前 token 压入节点栈
            NodePush(
              1,             // isTer = 1，终结符叶子节点
              token->id,         // token 类型码
              return_token_name(token->id),  // 叶子节点的名字
              curItemName,   // lexeme + 空格
              0,             // childCnt = 0
              token->line, token->column
            );
            token = nextToken();
            c = token->id;
        }
        // 归约（reduce）
        else {
			//计算出要归约的产生式编号
            int producerId = -1 - goTo;
			//获取产生式右部符号个数
            int h          = return_producer_len(producerId);
			//获取产生式左部符号编号
            int R          = return_producer_left(producerId);
			//归约
            NodeGenerate(producerId);
			//``状态栈弹出同样数量的状态
            while (h--) stateStackPop();
			//再次查表：在新的栈顶状态、以左部符号 R 做 GOTO
            state = stateStackTop();
            goTo  = GoTo(state, R);
            if (goTo == 65536) {
                goto BAD_STATE;
            }
			//``把 GOTO 的结果状态压回栈
            stateStackPush(goTo);
        }
    }
    return;
	//``恢复失败，若只有根节点则直接返回；否则报告错误
BAD_STATE:
    if (NodeStackPtr == 1) return;
    error("grammar parsing error!");
}



//错误处理

void error(char const *s) {
	fflush(stdout);
	//定位，报错
	printf("\nline<%d>, col<%d>: %s\n", row, column, s);
	for (int i = 0; i < 1000; ++i) {
		//输出当前状态可以接受的符号
		if (GoTo(stateStackTop(), i) != 65536) {
			printf("\tExpected - %s\n", return_token_name(i));
		}
	}
	//报错：当前读到的为
	if (curToken != NULL) printf("\tUnexpected : %s\n", return_token_name(curToken->id));
	else printf("\tUnexpected : program termination tag.\n");
}

void yyerror(char const *s)
{
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}


int main() {
    init_producers();

	FILE *input_file = freopen("./test.lo", "r", stdin);


	if (!input_file) {
		printf("Fail to open input file.\n");
		return -1;
		}
	
    grammarParse(nextToken);

	FILE *output_file = freopen("./tree.txt", "w", stdout);
	if (!output_file) {
		printf("Fail to create output file.\n");
		return -1;
	}

	// 打印节点栈中的内容
	for (int i = 0; i < NodeStackPtr; ++i) {
		printf("\n");
		print_tree(NodeStack[i], 0);
	}

	
	return 0;
}
)";
