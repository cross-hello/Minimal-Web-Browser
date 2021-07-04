#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h> /*socket*/
#include<sys/types.h>
#include<netdb.h>
#include<stdio.h>
#include<errno.h> /*perror()*/
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<stdlib.h>// for atoi() and //strtol
#include<netinet/in.h>
#include<arpa/inet.h>//for inet_addr()
#include"list.h"
int string_to_hex(const char *a)
{
	int i=0;
	//printf("%s",a);
	while(*a==' ')
	a++;
	/*char s=0;
	if(*a=='+'||*a=='-')
	s=*a;
	a++;
	*/
	if(*a=='0'&&(*(a+1)=='x'||*(a+1)=='X'))
	a+=2;
	//while(*a&&((*a>='0'&&*a<='9')||(*a>='a'&&*a<='z')||(*a>='A')&&(*a<='Z')))
	while(*a)
	{
		if(*a>='0'&&*a<='9')
			i=i*16+*a-'0';
		else 
		if(*a>='a'&&*a<='z')
			i=i*16+*a-'a'+10;
		else 
		if(*a>='A'&&*a<='Z')
			i=i*16+*a-'A'+10;
		else
			break;
		a++;
	}
	//printf("=%d\n",i);
	return i;
}
// Using:
////       ./client_web ip:port 
//       ./client_web url
//char char_at_str(const char *d, const char f)
//char char_at_str(const char f,const char *d)
int char_at_str(const char f,const char *d)
{
	const char *c=d;
	while(*d)
		if(*d++==f)
			return d-c-1;
	return -1;
}
void char_sit_at_char_in_str(char *d, const char s, const char r)
{
	d--;
	while(*++d)
	if(*d==s)
		*d=r;
}
// 0 domain 
// 1 ip
//"http://" should be the seven element of http_des array
char is_ip(const char *http_des)
{
	char c=0;//count the times of symbol period
	while(1)
	{
		switch(*http_des)
		{
			case '/':
			case '\0':
			case ':':
				goto bye;
			case '.':
				c++;
				break;
			case ' ':
				printf("invalid url for space in \n");
				return -1;
				//break;
			default:
				//if(*http_des<48||*http_des>57)
				if(*http_des<'0'||*http_des>'9')
					return 0;
		}
		http_des+=1;	
	}
	//bye:return 1;
	bye: if(c==3)
			return 1;
		else
			return 0;
}

int count(const char *c, const char *p)
{
	const char *s=p;
	int i=0;
	while(*c)
	{	
		p=s;
		while(*p)
			if(*p==*c)
			{
				i+=1;
				break;
			}
			else p++;
		if(*p=='\0')
		break;
		c++;
	}
//	printf("i==%d\n",i);//desired answer without count of terminating character 
	return i;
}
void count_in(char * des, const char* src, const char *p)
{
	const char *save=p;
	while(*src)
	{
		p=save;
		while(*p)
		if(*p==*src)
		{
			*des++=*p;
			break;
		}
		else p++;
		if(*p=='\0')
		break;
		src++;
	}
	*des='\0';
}
char * extract_ip(char *c)
{
	int i=count(c, ".0123456789");
	char *d=malloc(i+1);
	count_in(d,c,".0123456789");
//	puts(d);
	return d;
}
char * extract_url(char *c)
{
	char *s=strstr(c,"://");
	if(s==NULL)
	s=c;
	else 
	s+=3;
	int i=char_at_str('/',s);
	if(i==-1)
	i=strlen(s);
	char *b=malloc(i+1),*d;
	d=b;
	while(*c&&*c!='/')
	*d++=*c++;
	*d='\0';
	return b;
}
//int connect_url(const char * url)
//struct node* connect_url(const char * url)
struct node* connect_url(char * url)
{

	if(url==NULL)
	{
		printf("Input argument of get function is NULL\n");
		//return NULL:
		//return -1;
		return NULL;
	}
	struct node* b=create_node();
	b->mode=1;
	//char * url=strstr(COMMAND[1],"://");
	char * u=strstr(url,"://");
	int s=0;
	if(u==NULL)
	//url=COMMAND[1];
	u=url;
	else
	u+=strlen("://");
	printf("get host name OK\n");
	printf("url:%s\n",u);
	b->name=u;
	int i=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in wheres;
	wheres.sin_family=AF_INET;
	//char c=char_at_str(':',u);
	int c=char_at_str(':',u);
	if(-1!=c)
	{
		wheres.sin_port=htons(atoi(u+c+1));
		//char_sit_at_char_in_str(u,':','\0');
		//u[c]='\0';
		char *e=u+c+1;;
		//u=u+c+1;
		//while(*u>='0'&&*u<='9')
		//u++;
		while(*e>='0'&&*e<='9')
			e++;
	//	b->content=u;
		b->content=e;
	}
	else
	{
		wheres.sin_port=htons(80);//default web server port
		c=char_at_str('/',u);
		if(-1==c)
			b->content=u+strlen(u);
		else
			b->content=u+c;
	}

	//printf("ip port determined\n");
	printf("port determined\n");
	//if(is_ip(url))
	//if(is_ip(u))
	if(is_ip(b->name))
	{
		//wheres.sin_addr.s_addr=inet_addr(url);
		//wheres.sin_addr.s_addr=inet_addr(u);
		char *ip=extract_ip(b->name);
		//printf("ip: %s\n",ip);
		//wheres.sin_addr.s_addr=inet_addr(b->name);
		wheres.sin_addr.s_addr=inet_addr(ip);
		free(ip);
		if (-1==connect(i,(struct sockaddr *)&wheres,sizeof(wheres)))
		{
			perror("connect ");
			printf("url: %s\n",b->name);
			//return -2;
			empty_node(b);
			free(b);
			return NULL;
		}
	}
	else

	{
	//struct hostent *add=gethostbyname(url);
	struct addrinfo hint;
	memset(&hint,0,sizeof(hint));
	//hint.ai_flags=AF_INET;
	hint.ai_family=AF_INET;
	hint.ai_socktype=SOCK_STREAM;
	struct addrinfo *res;
	//if(-1==getaddrinfo(url,"http",&hint,&res))
	//s=getaddrinfo(url,"http",&hint,&res);
	//s=getaddrinfo(url,"80",&hint,&res);
	char *dd=extract_url(u);
	printf("%d---url: %s\n",__LINE__,dd);
	printf("Could I allocate res resources here?\n");
	s=getaddrinfo(dd,"80",&hint,&res);
	printf("I can\n");
	free(dd);
	if(0!=s)
		{
			//perror("getaddrinfo:");
			if(EAI_SYSTEM==s)
			fprintf(stderr,"strerror: %s\n",strerror(s));
			else
			fprintf(stderr,"gai_strerror: %s\n",gai_strerror(s));
			//printf("%s\n",

			//return -1;
			empty_node(b);
			free(b);
			return NULL;
		}
	else
		{
			struct addrinfo*rp;
			for(rp=res;rp!=NULL;rp=rp->ai_next)
//			if(-1!=connect(i,rp->ai_addr,rp->addrlen))
			{
				wheres.sin_addr.s_addr=((struct sockaddr_in*)(rp->ai_addr))->sin_addr.s_addr;
				if(-1!=connect(i,(struct sockaddr *)&wheres,sizeof(wheres)))
				break;
			}	
			if(rp!=NULL)
			printf("line %d: connect success\n ",__LINE__);
			freeaddrinfo(res);
			
			if(rp==NULL)
			{
				perror("Connect:");
				//return -3;
				empty_node(b);
				free(b);
				return NULL;
			}
			
	
		}

	}
	b->space_sum=i;
	//system("pause 0.1");
	//system("sleep 1");
	//return i;
	printf("revoke function finish \n");
	return b;

}
/*
//direction ==0 top
// == 1 end 
void add_key_value_in_list(const char * key, const char * value, struct list*l, char direction)
{
	struct node*a=create_node();
	assign_node(a,key,value,0);
	if(direction==0)
	push_list(a,l,1);
	else if(direction==1)
	append_list(a,l,1);
}*/
void default_host(struct list *l)
{
	add_key_value_in_list("Connection","keep-alive",l,1);
	add_key_value_in_list("Upgrade-Insecure-Requests","1",l,1);
	add_key_value_in_list("User-Agent","Hello Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.77 Safari/537.36",l,1);
	add_key_value_in_list("Accept","text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9",l,1);
//	add_key_value_in_list("Accept-Encoding","gzip, deflate",l,1);
	add_key_value_in_list("Accept-Language","en-US,en;q=0.9",l,1);
}
//m    --->"GET", "POST", ...
//add  --->' ', '/a/b'
char * method(const char *m, const char * add)
{
	
	//if(add=MULL)
	//}

	//printf("function method ok\n");
	//puts(m);
	//puts(add);
	int i=0;
	//if(add)
	if(*add)
		i=strlen(m)+strlen(add)+11;// strlen(" HTTP/1.1")+'\0'+' '(which after m)
	else
		i=strlen(m)+12;
	//printf("i=%d\n",i);
	char *s=(char *) malloc(i),*save;
	
	const char *b;
	save=s;
	b=m;
	while(*b)
	*s++=*b++;
	*s++=' ';
	if(*add=='/')
	{
		b=add;
		while(*b)
		*s++=*b++;
	}
	else
		*s++='/';
	strcpy(s," HTTP/1.1");
	//printf("function method ok\n");
	return save;
}
const char * terminology[]={"http://"};
char space[1024*4];
//#include<stdio.h>
void add_host(const char * m,struct node * a, struct list *l)
{
	//puts(a->name);
	//puts(a->content);
	//printf("a->content: %p", a->content);
	//printf("a->name: %p", a->name);
	//puts("hi");
	//printf("I am OK 12312312");
	char *c=a->name,save;
	//puts("hello");
	//printf("I am OK %d",__LINE__);
	//  char *test_save=a->content;
	//  *test_save='\0';
	//  puts("hello");
	//printf("a->content: %p", a->content);
	save=*(a->content);
	*(a->content)='\0';
	//puts("hello");
	//exit(1);
	//printf("I am OK %d",__LINE__);
	struct node *b=create_node();
	assign_node(b,"Host",c,0);
	printf("Host:%s\n\n",c);
	//puts("hello");
	//printf("I am OK %d",__LINE__);
	*a->content=save;
	//push_list(b,l,0);
	push_list(b,l,1);
	//empty_node(b);
	b=create_node();
	c=method(m, a->content);
	assign_node(b,NULL,c,1);
	b->mode=0;
//	assign_node(b,NULL, "GET / HTTP/1.1\r\n",0);
/*
	if(save!='/')
	assign_node(b,NULL, "GET / HTTP/1.1",0);
	else
	{
		c=(char *)malloc(14+strlen(a->content));
		sprintf(c,"GET %s HTTP/1.1",a->content);
		assign_node(b,NULL,c,1);
		b->mode=0;
	}
*/

	push_list(b,l,1);
	printf("Add host\n");
}
void prinnt(const char * c, int s)
{
	for(int i=0;i<s;i++)
		putchar(c[i]);
}
//char * get( char * url, struct node * c)
//char * get( char * url, struct list * c)
//char * revokes(const char*m, const char * url, struct list * c, struct node* body)
//char * revokes(const char*m, const char * url, struct list * c)
struct list* revokes(const char*m, const char * url, struct list * c)
{
	int i=strlen(url);
	char *ss=malloc(i+1);
	strcpy(ss,url);
	//url=ss;
	//struct node *b=connect_url(url);	
	printf("start connect url:%s\n",ss);
	struct node *b=connect_url(ss);	
	if(b==NULL)
		//return (char *)b;
		return NULL;
	printf("Finish connect url:%s\n",ss);
	//free(ss);
	printf("name: %s\n",b->name);
	printf("content: %s\n",b->content);
	//free(ss); ss in needed via struct node *b
	//printf("name: %s\n",b->name);
	//printf("content: %s\n",b->content);
	printf("Socket connection establish\n");
	//puts(b->name);
	//puts(b->content);
	//add_host("GET",b, c);
	//printf("into add_host\n");
	add_host(m,b, c);
	printf("HTML header add host completely\n");
//	int i=b->space_sum;
	i=b->space_sum;
	//empty_node(b);
	free(b);
	free(ss);
	printf("Now here are the header sent\n");
	do_list(print_node,c);
	//putchar('\n');
	//b=list_to_string(c,body);
	b=list_to_string(c);
	//prinnt(b->content, b->space_sum);
	send(i, b->content,b->space_sum,0);
	empty_node(b);
	free(b);
	b=NULL;
	//if(body)
	//send(i, body->content,body->space_sum,0);
	//int dd=accept(i,space, sizeof space, 0);
	int dd=recv(i,space, sizeof space, 0);
	space[dd]='\0';
	printf("Now let us see original feedback\n");
	//puts(space);
	//char *d=(char *)malloc(dd);
	//ss=(char*)malloc(dd);
	char *ee;
	puts("allocate memory for ee");
	ee=(char*)malloc(dd+1);
	puts("allocate finish");
	//strcpy(d,space);
	strcpy(ee,space);
	//struct list *l=string_to_list(d);
	printf("String to list process start\n");
	struct list *l=string_to_list(ee);
	printf("\nString to List completely\n");
	b=pop_back_list(l);
	//printf("The name of b is %s\n",b->name);
	//printf("The content of b is %s \n",b->content);
	printf("pop back from list OK\n");
	printf("show list of response:\n");
	do_list(print_node,l);
	putchar('\n');
	//printf("Respondse[Content-Length]:%s\n",value_seek_node_list("Content-Length", l));
	int len;
	//char *dd;
	if(value_seek_node_list("Transfer-Encoding",l)!=NULL)
	{
	//printf("Waiting for incoming stream\n");
	dd=recv(i,space,sizeof space,0);
	printf("Finish acceving \n");
	space[dd]='\0';
	//puts(space);
	//printf("Into strtok:\n");
	//char *test=strtok(space, "\r\n");
	//puts(test);
	puts(space);
	//printf("test: %s\n",test);
	//url=s
	ee=strtok(space, "\r\n");
	len=string_to_hex(ee);
	//len=string_to_hex(test);
	//printf("len=%d\n",len);
	//empty_node(b);
	free(b->name);
	b->name=NULL;
	while(*++ee!='\n');
	ee++;
	//assign_node(b, NULL, strtok(NULL,"\n"), 0);
	assign_node(b, NULL, ee, 0);
	//printf("b assign success\n");
	//b->content=strtok(NULL,"\n");
	//b->mode=1;
	}
	else
	{
	ee=value_seek_node_list("Content-Length", l);
	if(ee)
	len=atoi(ee);
	//else len=0;
	else len=strlen(b->content);
	}
	//printf("Space required is %d bytes\n",len);
	//printf("Response Status: %s\n", value_seek_node_list(NULL,l));
	if(len<0)
	{
		printf("Content-Length:%d\n",len);
		return NULL;
	}
	char *e=malloc(len+1);
	int e_len=len;
	//int e_len=strlen(b->content);
	//printf("initialize space: %d bytes---->%s\n", e_len,b->content);
	//printf("initialize space: %d bytes---->\n", e_len);
	//strncpy(e, b->content,e_len);
	strncpy(e,b->content,len+1);
	//empty_list(l);
	//empty_node(b);
	printf("Start clean mempory\n");
	if(b->name)
	free(b->name);
	else
	free(b->content);
	free(b);
	//printf("Empty list OK\n");
	printf("Empty node OK\n");

//	free(l);
//	free(d);
	//dd=e_len;
	while(e_len<len)
	{
		//printf("Accept %d byes\n",e_len);
		dd=recv(i,e+e_len, len-e_len, 0);
		if(dd==0)
		break;
		e_len+=dd;
	}
	printf("I accept %d bytes\n",e_len);
	e[e_len]='\0';
	b=create_node();
	printf("I create empty node of b in %d\n",__LINE__);
	b->name=NULL;
	b->content=e;
	b->space_sum=e_len;
	b->mode=0;
	set_body_list(b,l,1);
	free(b);
	close(i);
	printf("Finish function of revoke\n");
//	return e;
	return l;
}
