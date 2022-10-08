#include "types.hh"
#include "smt-switch/smt.h"
#include "smt-switch/bitwuzla_factory.h"

using namespace smt;

int main() {
    SmtSolver s = BitwuzlaSolverFactory(false);

    s->set_opt("produce-models", "true");
    s->set_opt("incremental", "true");

    si32_t x = si32_conc(42);
    si32_t y = si32_any(s, "y");

    z = si32_add(s, x, y);

    return 0;
}
