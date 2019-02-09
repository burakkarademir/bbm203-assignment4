#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0]) 
#define ALPHABET_SIZE (26) 
#define CHAR_TO_INDEX(c) ((int)c - (int)'a') 

struct TrieNode 
{ 
    struct TrieNode *children[ALPHABET_SIZE]; 
    char password[25];
    bool isEndOfWord; 
}; 

struct lines{
	char line[100];
	char word[30];
};






struct TrieNode *getNode(void) 
{ 
    struct TrieNode *pNode = NULL; 
  
    pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode)); 
  
    if (pNode) 
    { 
        int i; 
  
        pNode->isEndOfWord = false; 
  
        for (i = 0; i < ALPHABET_SIZE; i++) 
            pNode->children[i] = NULL; 
    } 
  
    return pNode; 
} 
  
// If not present, inserts key into trie 
// If the key is prefix of trie node, just marks leaf node 
void insert(struct TrieNode *root, const char *key, const char *password) 
{ 
    int level; 
    int length = strlen(key); 
    int index; 
  
    struct TrieNode *pCrawl = root; 
  
    for (level = 0; level < length; level++) 
    { 
        index = CHAR_TO_INDEX(key[level]); 
        if (!pCrawl->children[index]) 
            pCrawl->children[index] = getNode(); 
  
        pCrawl = pCrawl->children[index]; 
    } 
  
    // mark last node as leaf 
    pCrawl->isEndOfWord = true; 
    strcpy(pCrawl->password,password);
} 
  
// Returns true if key presents in trie, else false 
bool search(struct TrieNode *root, const char *key) 
{ 
    int level; 
    int length = strlen(key); 
    int index; 
    struct TrieNode *pCrawl = root; 
  
    for (level = 0; level < length; level++) 
    { 
        index = CHAR_TO_INDEX(key[level]); 
  
        if (!pCrawl->children[index]) 
            return false; 
  
        pCrawl = pCrawl->children[index]; 
    } 
    return (pCrawl != NULL && pCrawl->isEndOfWord); 
} 
bool search_withoutendofword(struct TrieNode *root, const char *key) 
{ 
    int level; 
    int length = strlen(key); 
    int index; 
    struct TrieNode *pCrawl = root; 
  
    for (level = 0; level < length; level++) 
    { 
        index = CHAR_TO_INDEX(key[level]); 
  
        if (!pCrawl->children[index]) 
            return false; 
  
        pCrawl = pCrawl->children[index]; 
    } 
    return (pCrawl != NULL); 
}

bool search_firstchar(struct TrieNode *root, const char *key) 
{ 
    int level; 
    int length = 1; 
    int index; 
    struct TrieNode *pCrawl = root; 
  
    for (level = 0; level < length; level++) 
    { 
        index = CHAR_TO_INDEX(key[level]); 
  
        if (!pCrawl->children[index]) 
            return false; 
  
        pCrawl = pCrawl->children[index]; 
    } 
    return (pCrawl != NULL); 
}
bool searchpass(struct TrieNode *root, const char *key) 
{ 
    int level; 
    int length = strlen(key); 
    int index; 
    struct TrieNode *pCrawl = root; 
  
    for (level = 0; level < length; level++) 
    { 
        index = CHAR_TO_INDEX(key[level]); 
  
        if (!pCrawl->children[index]) 
            return false; 
  
        pCrawl = pCrawl->children[index]; 
    } 
    return (pCrawl != NULL && pCrawl->isEndOfWord && pCrawl->password!=NULL); 
} 
bool printpass(struct TrieNode *root, const char *key, FILE *fptr) 
{ 
    int level; 
    int length = strlen(key); 
    int index; 
    struct TrieNode *pCrawl = root; 
  
    for (level = 0; level < length; level++) 
    { 
        index = CHAR_TO_INDEX(key[level]); 
  
        if (!pCrawl->children[index]) 
            return false; 
  
        pCrawl = pCrawl->children[index]; 
    } 
    fprintf(fptr,"\"%s\" password \"%s\"\n",key,pCrawl->password);
} 
bool searchand_comparepass(struct TrieNode *root, const char *key, const char *password) 
{ 
    int level; 
    int length = strlen(key); 
    int index; 
    struct TrieNode *pCrawl = root; 
  
    for (level = 0; level < length; level++) 
    { 
        index = CHAR_TO_INDEX(key[level]); 
  
        if (!pCrawl->children[index]) 
            return false; 
  
        pCrawl = pCrawl->children[index]; 
    } 
    return (pCrawl != NULL && pCrawl->isEndOfWord && pCrawl->password!=NULL && strcmp(pCrawl->password,password)==0); 
} 
bool compare_password(struct TrieNode *root, const char *key, const char *password) 
{ 
    int level; 
    int length = strlen(key); 
    int index; 
    struct TrieNode *pCrawl = root; 
  
    for (level = 0; level < length; level++) 
    { 
        index = CHAR_TO_INDEX(key[level]); 
  
        if (!pCrawl->children[index]) 
            return false; 
  
        pCrawl = pCrawl->children[index]; 
    } 
    return (strcmp(pCrawl->password,password)==0); 
} 




int deletion(struct TrieNode* *curr, char* str)
{
	// return if Trie is empty
	if (*curr == NULL)
		return 0;

	// if we have not reached the end of the string
	if (*str)
	{
		// recurse for the node corresponding to next character in
		// the string and if it returns 1, delete current node
		// (if it is non-leaf)
		if (*curr != NULL && (*curr)->children[*str - 'a'] != NULL &&
			deletion(&((*curr)->children[*str - 'a']), str + 1) &&
			(*curr)->isEndOfWord == 0)
		{
			if (!haveChildren(*curr))
			{
				free(*curr);
				(*curr) = NULL;
				return 1;
			}
			else {
				return 0;
			}
		}
	}

	// if we have reached the end of the string
	if (*str == '\0' && (*curr)->isEndOfWord)
	{
		// if current node is a leaf node and don't have any children
		if (!haveChildren(*curr))
		{
			free(*curr); // delete current node
			(*curr) = NULL;
			return 1; // delete non-leaf parent nodes
		}

		// if current node is a leaf node and have children
		else
		{
			// mark current node as non-leaf node (DON'T DELETE IT)
			(*curr)->isEndOfWord = 0;
			return 0;	   // don't delete its parent nodes
		}
	}

	return 0;
}
// returns 1 if given node has any children
int haveChildren(struct TrieNode* curr)
{
    int i;
	for (i = 0; i < ALPHABET_SIZE; i++)
		if (curr->children[i])
			return 1;	// child found

	return 0;
}



bool isLeafNode(struct TrieNode* root) 
{ 
    return root->isEndOfWord != false; 
}
void display(struct TrieNode* root, char str[], int level, int flag, int branching,FILE *fptr ) 
{ 
    // If node is leaf node, it indiicates end 
    // of string, so a null charcter is added 
    // and string is displayed 
   if (isLeafNode(root))  
    { 
        if(branching==0 && haveChildren(root)==0 && flag==0){
            str[level] = '\0'; 
            fprintf(fptr,"-%s \n",str);
        }
        else if(branching==0 && haveChildren(root)==1 && root->isEndOfWord==true && flag==0){
            flag=1;
            str[level] = '\0'; 
            fprintf(fptr,"-%s \n",str);
        }
        else{
            str[level] = '\0'; 
            fprintf(fptr,"      -%s \n",str);
        }
    }
  
    int i,k; 
    for (i = 0; i < 26; i++)  
    { 
  
        // if NON NULL child is found 
        // add parent key to str and 
        // call the display function recursively 
        // for child node 
        if (root->children[i])  
        { 
          for(k=0;k< 26;k++){
            if(flag==0  && level!=0 && root->children[k] && i!=k){
                flag=1;
                branching++;
                str[level] = '\0'; 
                fprintf(fptr,"-%s \n",str);
            }
        }
            str[level] = i + 'a'; 
            display(root->children[i], str, level + 1,flag,branching,fptr); 
        } 
    }
    
   
} 




int find_line_number(char *argv[]){
	
    FILE *fptr;
    int lineNumber=0;
	
    if((fptr=fopen(argv[1],"r"))==NULL){
        exit(1);
    }
    else{
    	char line[100];
        /*This loop count number of all lines*/
        while(fgets(line, sizeof(line), fptr)) {
        	lineNumber++;
	} 
		
        fclose(fptr);
    }
    return lineNumber;
}

void read_file(char *argv[], struct lines *lines){
    FILE *fptr;
    char line[100];
    
	if((fptr=fopen(argv[1],"r"))==NULL){
        exit(1);
    }
    
    else{
    	char *word=(char*)malloc(90);
    	int i=0;
        /*read file line by line and get lines*/
        while(fgets(line, sizeof(line), fptr)) {
            if(strcmp(line,"\r\n")!=0||strcmp(line,"\n")!=0){
                strcpy(lines[i].line,line);
                word= strtok (line," ");
                strcpy(lines[i].word,word);
                i++;
            }
	} 
        fclose(fptr);
    }	
}

int main(int argc, char** argv) {
    FILE *fptr;
    fptr=fopen("output.txt", "w");
    int line_number=find_line_number(argv);
    struct lines *lines=(struct lines *)malloc(line_number*sizeof( struct lines));
    read_file(argv, lines);
    int i;
    struct TrieNode *root = getNode(); 

    for(i=0;i<line_number;i++){
        strtok(lines[i].line," ");
        char *name = strtok(NULL, " ,\n");
       
        if(strcmp(lines[i].word,"-a")==0){
            char *password = strtok(NULL," ,\n");
            if(search(root,name)){
                fprintf(fptr,"\"%s\" reserved username\n", name);
            }
            else{
                insert(root,name,password);
                fprintf(fptr,"\"%s\" was added\n", name);
            }
        }
        else if(strcmp(lines[i].word,"-s")==0){
            char name2[1];
            strncpy(name2,name,1);
            if(searchpass(root,name)){
                printpass(root,name,fptr);
            }
            else if(search_withoutendofword(root,name) && !searchpass(root,name)){
                fprintf(fptr,"\"%s\" not enough username\n", name);
            }
            else if(search_firstchar(root,name2)){
                fprintf(fptr,"\"%s\" incorrect username\n", name);
            }
            else if(!search_firstchar(root,name2)){
                fprintf(fptr,"\"%s\" no record\n", name);
            }
        }
        else if(strcmp(lines[i].word,"-q")==0){
            char *password = strtok(NULL," ,\n");
            char name2[1];
            strncpy(name2,name,1);
            if(searchand_comparepass(root,name,password)){
                fprintf(fptr,"\"%s\" succesfull login\n", name);
            }
            else if(search(root,name)){
                if(!compare_password(root,name,password)){
                    fprintf(fptr,"\"%s\" incorrect password\n", name);
                }
            }
            else if(search_withoutendofword(root,name) && !searchpass(root,name)){
                fprintf(fptr,"\"%s\"  not enough username\n", name);
            }
            else if(search_firstchar(root,name2)){
                fprintf(fptr,"\"%s\" incorrect username\n", name);
            }
            else if(!search_firstchar(root,name2)){
                fprintf(fptr,"\"%s\" no record\n", name);
            }
        }
        else if(strcmp(lines[i].word,"-d")==0){
            char name2[1];
            strncpy(name2,name,1);
            if(searchpass(root,name)){
                deletion(&root,name);
                fprintf(fptr,"\"%s\" deletion is successfull\n", name);
            }
            else if(search_withoutendofword(root,name) && !searchpass(root,name)){
                fprintf(fptr,"\"%s\" not enough username\n", name);
            }
            else if(search_firstchar(root,name2)){
                fprintf(fptr,"\"%s\" incorrect username\n", name);
            }
            else if(!search_firstchar(root,name2)){
                fprintf(fptr,"\"%s\" no record\n", name);
            }
        }
        else if(strcmp(lines[i].word,"-l")==0){
            int level = 0; 
            char str[20]; 
            display(root, str, level,0,0,fptr);
        }


    }
    fclose(fptr);
    return (EXIT_SUCCESS);
}

