// Header file

// Structure to store state values of the jugs
struct state
{
	int jug8; 
	int jug5; 
	int jug3; 
	int fn_index;
};

typedef struct state state_t;
void init_state(state_t *ptr_state);
void disp_state(const state_t *ptr_state);
void set_state(state_t *ptr_state, int can, int mis, int pos);

// Move functions
void move_85(const state_t *src, state_t *dst);
void move_58(const state_t *src, state_t *dst);
void move_35(const state_t *src, state_t *dst);
void move_53(const state_t *src, state_t *dst);
void move_83(const state_t *src, state_t *dst);
void move_38(const state_t *src, state_t *dst);

int is_safe(const state_t* ptr_state);
int are_same(const state_t *lhs, const state_t *rhs);

// Structure to store node values
typedef struct node
{
	state_t st;
	struct node *next;
	struct node *prev;
}node_t;

// Structure to store list values
typedef struct list
{
	node_t* head;
	node_t* tail;
}list_t;

// list operations
void init_list(list_t *ptr_list);
void add_at_end(list_t *ptr_list, const state_t* ptr_state);

void remove_at_end(list_t *ptr_list);
void disp_list(const list_t *ptr_list);

int is_repeated(const list_t* ptr_list, const state_t* ptr_state);