class SinglyList;
void transpose_singly_list(SinglyList &l);

struct SinglyNode
{
  SinglyNode():val(0),next(NULL){}
  SinglyNode(double val_):val(val_),next(NULL){}
  double val;
  SinglyNode *next;
};


class SinglyList
{
public:
  friend void transpose_singly_list(SinglyList &l);
  SinglyList():head(NULL),tail(NULL){}
  ~SinglyList();
  void insert(double x);
  SinglyNode *search(double key) const;
  void del(double key);
  bool is_empty() const;
  void print() const;
  SinglyNode *get_head(){return head;}
  SinglyNode *get_tail();
private:
  SinglyNode *head;
  SinglyNode *tail;
};

inline bool SinglyList::is_empty() const
{
  if (head == NULL)
    return true;
  return false;
}

