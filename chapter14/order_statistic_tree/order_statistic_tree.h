struct Node
{
  Node():key(0),size(0),left(NULL),right(NULL),parent(NULL),color(0){}
  Node(int k):key(k),size(1),left(NULL),right(NULL),parent(NULL),color(1){}
  void init(Node *x);
  int key;
  int size;
  Node *left;
  Node *right;
  Node *parent;
  bool color; // block:0, red: 1
};

class Tree
{
public:
  Tree():nil(new Node()),root(nil){}
  void insert(Node *x);
  Node *search(int key);
  void del(Node *x);
  Node *select(int i);
  int key_rank(int key);
  int key_rank_recursive(int key);
  int rank(Node *p);
  void print();
  void init_node(Node *x);
  Node *minimum(Node *x);
  Node *nil;
private:
  Node *root;
  void insert_fixup(Node *x);
  void left_rotate(Node *x);
  void right_rotate(Node *x);
  void minus1_upto_root(Node *x);
  void transplant(Node *u, Node *v);
  void del_fixup(Node *x);
  int _key_rank_recursive(int key, Node *p);
};

