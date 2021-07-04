#include"list.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//void initialize_node(struct node*a, char * name, char * content)
//static int str_cpy(char **a, char * s)
//static void str_cpy(char **a, char * si, int i)
static void str_cpy(char **a, char * s, int i)
{
	if(s==NULL)
	{
		*a=NULL;
		return ;
	}
//	int i=strlen(s);
	*a=(char*)malloc(i+1);
	strncpy(*a,s,i+1);
	return;
//	return i;
}
//struct node* create_node(char *name, char *content,char mode)
struct node* create_node(void)
{
		struct node * r=(struct node*)malloc(sizeof(struct node));
		if(r==NULL)
		{
			printf("allocate mempry for node failed\n");
		}
		//r->pre=NULL;
		//r->nex=NULL;
		//r->mode=1;
		//assign_node(r,name,content,mode);
		return r;
}
void assign_node(struct node*r, char *name, char * content, char mode)
{
		r->space_sum=0;
		r->pre=NULL;
		r->nex=NULL;
		r->mode=mode;
		int l_name;
		if(name!=NULL)
		l_name=strlen(name);
		else
		l_name=0;
		//int l_content=strlen(content);
		int l_content;
		if(content!=NULL)
		l_content=strlen(content);
		else
		l_content=0;
		if(mode==0)
		{
			//r->name=(char*)malloc(l+1);
			//r->space_sum+=l;
			//strcpy(r->name, name);
			//r->space_sum+=str_cpy(&r->name,name,l_name);
			str_cpy(&r->name,name,l_name);
			//printf("%s : %d\n",name, l_name);
			//r->space_sum+=

			//l=strlen(content);
			//r->content=(char *)malloc(l+1);
			//r->space_sum+=l;
			//strcpy(r->content,content);
			//r->space_sum+=str_cpy(&r->content,content,l_content);
			str_cpy(&r->content,content,l_content);
		}
		else if(mode ==1)
		{
			r->name=name;
			r->content=content;
		}
			r->space_sum+=(l_name+l_content);
}

void print_node(const struct node*a)
{
	printf("%s: %s \n",a->name, a->content);
}


struct node* copy_node(const struct node*a)
{
	struct node*b=create_node();
	assign_node(b, a->name,a->content, 0);
	return b;
}

void empty_node(struct node* a)
{
	//memset(a, 0, sizeof(struct node));
	if(a==NULL)
	return;
	if(a->mode==0)
	{
		printf("Free a->name\n");
		if(a->name)
		free(a->name);
		printf("Free a->content\n");
		if(a->content)
		free(a->content);
		a->name=NULL;
		a->content=NULL;
	}
	/*
	a->name=NULL;
	a->content=NULL;
	a->mode=0;
	a->space_sum=0;
	a->pre=NULL;
	a->nex=NULL;
	*/
	memset(a,0,sizeof(struct node));
}

struct list * create_list(void)
{
	//return (struct list *)malloc(sizeof(struct list));
	struct list* r=(struct list*)malloc(sizeof(struct list));	
		if(r==NULL)
		{
			printf("allocate mempry for node failed\n");
		}
	return r;
}

void initialize_list(struct list * a)
{
	a->top=NULL;
	a->end=NULL;
	a->body=NULL;
	a->sum=0;
}

void append_list(struct node*b, struct list*a, char mode)//mode =1
{
	if(mode==0)
	b=copy_node(b);
	else if(mode==1)
	b=b;

	if(a->end==NULL)
	{
	a->end=b;
	a->top=b;
	}
	else {
	a->end->nex=b;
	b->pre=a->end;
	a->end=b;
	}
	a->sum+=1;
}

void push_list(struct node *b, struct list *a, char mode)// mode=1
{
	if(mode==0)
	b=copy_node(b);
	else if(mode==1)
	b=b;
	
	if(a->top==NULL)
	a->top=a->end=b;
	else
	{
	a->top->pre=b;
	b->nex=a->top;
	a->top=b;
	}
	a->sum+=1;
}

struct node* pop_back_list(struct list *l)
{
	if(l->end==NULL)
	return NULL;
	else{
	struct node * a=l->end;
	l->end=a->pre;
	if(l->end!=NULL)
		l->end->nex=NULL;
	else
		l->top=NULL;
	a->pre=NULL;
	l->sum-=1;
	//if(l->sum==0)
	//l->top=
	return a;
	}
}


struct node* pop_front_list(struct list* l)
{
	if(l->top==NULL)
	return NULL;
	struct node * a=l->top;
//	a->nex=NULL;
//	l->top=a->pre;
	l->top=a->nex;
	if (l->top!=NULL)
		l->top->pre=NULL;
	else
		l->end=NULL;
	a->nex=NULL;
	l->sum-=1;
	return a;
}

void do_list(void (*f)(const struct node*), struct list* l)
{
	//struct node*a=l->top, *b;
	struct node*a=l->top;
	while(a)
	{
		f(a);
		a=a->nex;
	}
}

char low(char a)
{
	if(a>='a'&&a<='z')
	return a;
	else 
	if(a>='A'&&a<='Z')
	return a-'A'+'a';
	else
	return -1;
}

char * lower_clear(const char *a)
{
	if(a==NULL)
	return NULL;
	int i=0;
	//char *s=a;
	const char *a1=a;
	a--;
	while(*++a)
	if(*a!=' ')
		i+=1;
	char *c=malloc(i+1);
	//a=s;
	a=a1;
	char *s=c;
	char d;
	while(*a)
	{
	d=low(*a++);
	if(d!=-1)
	*s++=d;
	}
	*s='\0';
	return c;
}
// return 0 equal
// not zero diff
char name_compare(const char *a, const char *b)
{
	char *a1=lower_clear(a),*a2;
	a2=a1;
	char *b1=lower_clear(b),*b2;
	b2=b1;
	if(a==NULL||b==NULL)
	if(a==NULL&&b==NULL)
	return 0;
	else
	return -1;
	int re=0;
	while(*a1||*b1)
	if(*a1++!=*b1++)
		{
			re=a1-a2;
			break;
		}
	free(a2);
	free(b2);
	return re;
}

/*
	a--;
	b--;
	char re=1;
	while(re)
	{
		re=0;
		while(*++a)
			if(*a==' ')
			continue;
		while(*++b)
			if(*b==' ')
			continue;
		if(*a!=
	}
	*/

//}
struct node* seek_node_list(const char * name, struct list * l)
{
	struct node*a=l->end;
	while(a)
	{
		if(name_compare(name, a->name)==0)
			//return a->content;
			return a;
		a=a->pre;
	}
	return NULL;
}

char* value_seek_node_list(const char * name, struct list * l)
{
	struct node* a=seek_node_list(name,l);
	if(a)
	return a->content;
	return NULL;
}
//// 1 mean you give all right to corresponding, includeing memory free
void set_body_list(struct node* b, struct list*l,char mode)
{
	if(l->body)
	{	
		empty_node(l->body);
		free(l->body);
	}
	if(mode==1)
		{
		l->body=create_node();
		assign_node(l->body, b->name, b->content,mode);
		}
	else	
	if(mode==0)
		l->body=copy_node(b);
}

void value_set_body_list(char *c,int len, struct list*l, char mode)
{	
	struct node*b=create_node();
	b->name=NULL;
	if(mode==1)
		b->content=c;
	else if(mode==0)
	{
		b->content=(char *)malloc(len);
		strncpy(b->content, c,len);
	}
	b->space_sum=len;
	b->mode=mode;
	set_body_list(b,l,1);
	free(b);
}

void set_node_list(char *name, char *new_value, struct list*l)
{
	struct node*a=seek_node_list(name,l);	
	if(a)
	{	
		//int i;
		if(a->mode==0)
		{
			int i=strlen(a->content);
			//i=strlen(a->content);
			//i=strlen(a->content);
			a->space_sum-=i;
			free(a->content);
			i=strlen(new_value);
			a->content=(char *)malloc(i+1);
			strcpy(a->content,new_value);
			a->space_sum+=i;
		}
		else
			assign_node(a,a->name,new_value,0);
	}
	else 
	add_key_value_in_list(name,new_value,l,1);
}

//direction ==0 top
// == 1 end
void add_key_value_in_list(char * key,char * value, struct list*l, char direction)
{
    struct node*a=create_node();
    assign_node(a,key,value,0);
    if(direction==0)
    push_list(a,l,1);
    else if(direction==1)
    append_list(a,l,1);
}
void empty_list(struct list*l)
{
#ifdef TEST
	int i=0;
#endif
	struct node*a=l->top,*b;
	while(a)
	{
		b=a->nex;
		//free(a);
		empty_node(a);
		free(a);
		//l->sum-=1;
		a=b;
#ifdef TEST
		i+=1;
#endif
	}
#ifdef TEST
	l->sum-=i;
	//if(i!=l->sum)
	if(l->sum)
	printf("The number of list error\n");
#endif
	l->top=l->end=NULL;
	l->sum=0;
	//printf("Hello, I finish free header memory\n");
	if(l->body)
	{
		//print_node(l->body);
		empty_node(l->body);
		free(l->body);
		l->body=NULL;
	}
}
struct node * list_to_string(const struct list * l)
{
	const struct node* a=l->top;
	const struct node**arr=(const struct node**)malloc(l->sum*sizeof(struct node*));
	int i=0;
	int s=0;
	while(a)
	{
		s+=a->space_sum;
		arr[i++]=a;
		a=a->nex;
	}
	if(l->body)
	s+=l->body->space_sum;
	s+=l->sum*4+2;
	//char * space=(char *)malloc(s+l->sum*4+2);
	char *space=(char *) malloc(s);
	char *save,*b/*,re*/;
	save=space;
	int c=s;
	for(s=0;s<i;s++)
		{
			//re=0;
			a=arr[s];
			//strcpy(space, a->
			b=a->name;
			if(b!=NULL)
			{
			while(*b)
			*space++=*b++;
			*space++=':';
			*space++=' ';
			}
			b=a->content;
			if(b!=NULL)
			{
			while(*b)
			*space++=*b++;
			*space++='\r';
			*space++='\n';
			}
		}	
	free(arr);
	*space++='\r';
	*space++='\n';
	if(l->body)
	strncpy(space, l->body->content,l->body->space_sum);
	struct node*d=create_node();
	//assign_node(d, NULL,save, 1);
	d->name=NULL;
	d->content=save;
	d->space_sum=c;
	d->pre=d->nex=NULL;
	d->mode=0;
	return d;	
}
struct node* header_body(char *c)
{
	struct node*b=create_node();
	char *s=strstr(c,"\r\n\r\n");
	if(s==NULL)
	{	
		printf("Not found \\r\\n\\r\\n\n");
		free(b);
		return NULL;
	}
	s[2]='\0';
	s[3]='\0';
	assign_node(b,c,s+4,1);
	b->mode=2;
	return b;
}
struct list* string_to_list(char *c)
{
	struct node*b=header_body(c);
	if(b==NULL)
	return NULL;
	struct list *l=create_list();
	initialize_list(l);
	//struct node *a=create_node();
	char *name,*content;
	content=strtok(b->name,"\r\n");
	//content=strstr(c,"\r\n");
	//assign(a,NULL, content,0);
	add_key_value_in_list(NULL, content,l,1);
	name=strtok(NULL," :\t\r\n");
	//while(content)
	while(name)
	{
		content=strtok(NULL,"\r\n");
		add_key_value_in_list(name, content,l,1);
		name=strtok(NULL," :\t\r\n");
	}
	//set_body_list(	
	append_list(b,l,1);
	return l;
}
void initialize_hlist(struct hlist*a)
{
	a->header=NULL;
	a->body=NULL;
}
