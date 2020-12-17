typedef struct values {
    int row;
    int col;
    int num;
} values;

typedef struct node {
    values val;
    struct node *next;
} node;

typedef node* stack;

void init(stack *s);

void push(stack *s, values val);

values pop(stack *s);

int isempty(stack *s);

int isfull(stack *s);