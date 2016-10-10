#include <iostream>
#include <string>
#include <random>

void true_foo( int x )
{
  std::cout << "true_foo( " << x << " )." << std::endl;
}

void false_foo( int x )
{
  std::cout << "false_foo( " << x << " )." << std::endl;
}

bool condition_foo( int x )
{
  return x % 2 == 0;
}

int main()
{
  auto condition_lambda = []( auto const & cond_f, auto const & true_f, auto const & false_f )
  {
    return [&]( auto &&... args )
    {
      return cond_f( args... ) ?
        true_f( std::forward<decltype(args)>(args)... ) :
        false_f( std::forward<decltype(args)>(args)... );
    };
  };

  std::random_device rd;
  std::uniform_int_distribution<> dist(1, 100);

  condition_lambda( condition_foo, true_foo, false_foo )( dist(rd) );

  return 0;
}

