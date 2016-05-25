// forward_list::splice_after
#include <iostream>
#include <forward_list>

int main ()
{
  std::forward_list<int> first = { 1, 2, 3, 4, 5, 6, 7, 8 };

  auto it = first.begin();  // points to the 1
   it++;
   it++;
  first.splice_after ( first.begin(), first, it);
  std::cout << "first contains:";
  for (int& x: first) std::cout << " " << x;
  std::cout << std::endl;

  return 0;
}
