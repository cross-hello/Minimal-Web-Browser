//char * get( char * url, struct list * c);
//char * revokes(const char*, char *, struct list *, struct node*);
//char * revokes(const char*m, const char * url, struct list * c);
struct list* revokes(const char*m, const char * url, struct list * c);
void add_host(const char * m,struct node * a, struct list *l);
void default_host(struct list *l);



