class Stack
{
public:
  Stack();
  Stack(int max_size_);
  ~Stack(){delete[] a;}
  void push(double x);
  double pop();
  bool is_empty() const{if (top == -1) return true; else return false;}
  bool is_full() const{if (top == max_size -1) return true; else return false;}
  void print() const;
private:
  int max_size;
  int top;
  double *a; 
};

