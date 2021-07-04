#ifndef LIST_HTTP
#define LIST_HTTP

struct node{
	char * name;
	char *content;
	int space_sum;
	struct node* pre;
	struct node* nex;
	char mode;
};

//void initialize_node(struct node*, char * name,char * content);// mode =1
//struct node * create_node(char * name,char * content, char mode);// mode =0
struct node * create_node(void);
void assign_node(struct node*, char *name, char * content, char mode);
void print_node(const struct node*);
//void set_name_node(struct node *, char * n, char mode)
struct node* copy_node( const struct node*);
void empty_node(struct node *);

struct list{
		struct node *top;
		struct node *end;
		struct node*body;
		int sum;
};
struct list* create_list(void);
void initialize_list(struct list*);
//void append_list(struct node *, struct list *);
// if mode ==0, then copy the content of node
//else if mode==1, then copy the address of node directly 
//void append_list(struct node *,struct list * ,char mode);
void append_list(struct node *,struct list *, char mpde);// mode =1
void push_list(struct node *,struct list * , char mode);// mode =1
struct node * pop_back_list(struct list *);
struct node* pop_front_list(struct list *);
void do_list(void (*) (const struct node*),struct list*);
char name_compare(const char * a, const char *b);
//char * seek_node_list(const char * name, struct list*); 
struct node* seek_node_list(const char * name, struct list*); 
char * value_seek_node_list(const char * name, struct list*);
void set_body_list(struct node*, struct list*, char mode);
void value_set_body_list(char *,int len, struct list*, char mode);
void set_node_list(char *name,char *new_value, struct list*);
//direction ==0 top
// == 1 end
void add_key_value_in_list(char * key,char * value, struct list*l, char direction);
void empty_list(struct list *);
//char * list_to_string(const struct list * l);
//struct node * list_to_string(const struct list * l, struct node*body);
struct node * list_to_string(const struct list * l);
struct list * string_to_list( char *);
struct hlist{
	struct list * header;
	struct list* body;
};
void initialize_hlist(struct hlist*);
#endif
