#include <iostream>
#include <chrono>

#include "Teuchos_stacktrace.hpp"

#include "basic.h"
#include "add.h"
#include "symbol.h"
#include "dict.h"
#include "integer.h"
#include "mul.h"
#include "pow.h"

using SymEngine::Basic;
using SymEngine::Add;
using SymEngine::Mul;
using SymEngine::Pow;
using SymEngine::Symbol;
using SymEngine::umap_basic_num;
using SymEngine::map_vec_int;
using SymEngine::Integer;
using SymEngine::multinomial_coefficients;
using SymEngine::RCP;
using SymEngine::rcp;
using SymEngine::rcp_dynamic_cast;

int main(int argc, char* argv[])
{
    Teuchos::print_stack_on_segfault();

    RCP<const Basic> x = rcp(new Symbol("x"));
    RCP<const Basic> y = rcp(new Symbol("y"));
    RCP<const Basic> z = rcp(new Symbol("z"));
    RCP<const Basic> w = rcp(new Symbol("w"));
    RCP<const Basic> i15 = rcp(new Integer(15));

    RCP<const Basic> e, f, r;

    e = pow(add(add(add(x, y), z), w), i15);
    f = mul(e, add(e, w));

    std::cout << "Expanding: " << *f << std::endl;

    auto t1 = std::chrono::high_resolution_clock::now();
    r = expand(f);
    auto t2 = std::chrono::high_resolution_clock::now();
    //std::cout << *r << std::endl;
    std::cout
        << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count()
        << "ms" << std::endl;
    std::cout << "number of terms: "
        << rcp_dynamic_cast<const Add>(r)->dict_.size() << std::endl;

    return 0;
}
