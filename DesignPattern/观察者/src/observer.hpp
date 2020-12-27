class Observer
{
public:
  Observer() {}
  virtual void update(int id) = 0;
  ~Observer() {}
};
