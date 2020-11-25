class DoublyListNode
{
public:
  DoublyListNode():val(0),prev(NULL),next(NULL){}
  DoublyListNode(double val_):val(val_),prev(NULL),next(NULL){}
  double val;
  DoublyListNode * prev;
  DoublyListNode * next;
};

class NormalDoublyList
{
public:
  NormalDoublyList():head(NULL){}
  ~NormalDoublyList();
  void insert(double x);
  DoublyListNode *search(double key);
  void del(DoublyListNode *node);
  void print();
  bool is_empty(){return (head == NULL);}
private:
  DoublyListNode *head;
};

class SentineledDoublyList
{
public:
  SentineledDoublyList();
  ~SentineledDoublyList();
  void insert(double x);
  DoublyListNode *search(double key);
  void del(DoublyListNode *node);
  void print();
  bool is_empty(){return (nil->next == nil);}
private:
  DoublyListNode *nil;
};

