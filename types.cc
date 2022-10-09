#include "smt-switch/smt.h"
#include "smt-switch/bitwuzla_factory.h"

#include "bv.h"

using namespace smt;
using namespace sym;

int main() {
    SmtSolver solver = BitwuzlaSolverFactory::create(false);

    solver->set_opt("produce-models", "true");

    bv<64> x(42);
    bv<64> y("y", solver);

    bv<64> z = y.op_neg(solver);
    bv<64> a = x.op_and(y, solver);
    x.s_ = x.sym(solver);
    bv<1> b = x.op_neqz(solver);
    solver->check_sat();
    std::cout << solver->get_value(b.s_) << "\n";

    return 0;
}

// using namespace smt;
//
// bool si32_concrete(si32_t i) {
//     return i.s == NULL;
// }
//
// static Sort bv1;
// static Sort bv32;
// static Term bv32_zero;
// static Term bv32_one;
//
// void symwrap_init(SmtSolver solver) {
//     bv1 = solver->make_sort(BV, 1);
//     bv32 = solver->make_sort(BV, 32);
//     bv32_zero = solver->make_term(0, bv32);
//     bv32_one = solver->make_term(1, bv32);
// }
//
// si32_t si32_any(SmtSolver solver, std::string name) {
//     return (si32_t){
//         .s = solver->make_symbol(name, bv32),
//     };
// }
//
// si32_t si32_conc(int32_t i) {
//     return (si32_t){
//         .c = i,
//     };
// }
//
// Term sym(SmtSolver solver, si32_t i) {
//     if (!si32_concrete(i)) {
//         return i.s;
//     } else if (i.c == 0) {
//         return bv32_zero;
//     } else if (i.c == 1) {
//         return bv32_one;
//     }
//     return solver->make_term(i.c, bv32);
// }
//
// // TODO: need to automatically call 'sym' before doing a symbolic op
//
// #define mk_binop(a, b, conc_op, sym_op)               \
//     do {                                              \
//         if (si32_concrete(a) && si32_concrete(b)) {   \
//             return (si32_t){                          \
//                 .c = (int32_t) (conc_op),             \
//             };                                        \
//         }                                             \
//         return (si32_t){                              \
//             .s = solver->make_term(sym_op, a.s, b.s), \
//         };                                            \
//     } while (0)
//
// si32_t si32_add(SmtSolver solver, si32_t a, si32_t b) {
//     mk_binop(a, b, a.c + b.c, Op(BVAdd));
// }
// si32_t si32_sub(SmtSolver solver, si32_t a, si32_t b) {
//     mk_binop(a, b, a.c - b.c, Op(BVSub));
// }
// si32_t si32_xor(SmtSolver solver, si32_t a, si32_t b) {
//     mk_binop(a, b, a.c ^ b.c, Op(BVXor));
// }
// si32_t si32_or(SmtSolver solver, si32_t a, si32_t b) {
//     mk_binop(a, b, a.c | b.c, Op(BVOr));
// }
// si32_t si32_and(SmtSolver solver, si32_t a, si32_t b) {
//     mk_binop(a, b, a.c & b.c, Op(BVAnd));
// }
// si32_t si32_sll(SmtSolver solver, si32_t a, si32_t b) {
//     mk_binop(a, b, a.c << b.c, Op(BVShl));
// }
// si32_t si32_srl(SmtSolver solver, si32_t a, si32_t b) {
//     mk_binop(a, b, (uint32_t) a.c >> (uint32_t) b.c, Op(BVLshr));
// }
// si32_t si32_sra(SmtSolver solver, si32_t a, si32_t b) {
//     mk_binop(a, b, a.c >> b.c, Op(BVAshr));
// }
// si32_t si32_mul(SmtSolver solver, si32_t a, si32_t b) {
//     mk_binop(a, b, a.c * b.c, Op(BVMul));
// }
// si32_t si32_sdiv(SmtSolver solver, si32_t a, si32_t b) {
//     mk_binop(a, b, a.c / b.c, Op(BVSdiv));
// }
// si32_t si32_udiv(SmtSolver solver, si32_t a, si32_t b) {
//     mk_binop(a, b, (uint32_t) a.c / (uint32_t) b.c, Op(BVUdiv));
// }
// si32_t si32_srem(SmtSolver solver, si32_t a, si32_t b) {
//     mk_binop(a, b, a.c % b.c, Op(BVSrem));
// }
// si32_t si32_urem(SmtSolver solver, si32_t a, si32_t b) {
//     mk_binop(a, b, (uint32_t) a.c % (uint32_t) b.c, Op(BVUrem));
// }
//
// #define mk_bool_binop(a, b, conc_op, sym_op)        \
//     do {                                            \
//         if (si32_concrete(a) && si32_concrete(b)) { \
//             return (sbool_t){                       \
//                 .c = conc_op,                       \
//             };                                      \
//         }                                           \
//         return (sbool_t){                           \
//             .s = solver->make_term(sym_op, a.s),    \
//         };                                          \
//     } while (0)
//
// sbool_t si32_slt(SmtSolver solver, si32_t a, si32_t b) {
//     mk_bool_binop(a, b, a.c < b.c, Op(BVSlt));
// }
// sbool_t si32_ult(SmtSolver solver, si32_t a, si32_t b) {
//     mk_bool_binop(a, b, (uint32_t) a.c < (uint32_t) b.c, Op(BVUlt));
// }
//
// #define mk_op(i, sym_t, conc_op, sym_op)         \
//     do {                                         \
//         if (si32_concrete(i)) {                  \
//             return (sym_t){                      \
//                 .c = conc_op,                    \
//             };                                   \
//         }                                        \
//         return (sym_t){                          \
//             .s = sym_op, \
//         };                                       \
//     } while (0)
//
// sbool_t si32_eqz(SmtSolver solver, si32_t i) {
//     mk_op(i, sbool_t, i.c == 0, solver->make_term(Op(BVComp), i.s, bv32_zero));
// }
// sbool_t si32_neqz(SmtSolver solver, si32_t i) {
//     mk_op(i, sbool_t, i.c != 0, solver->make_term(Op(BVNot), solver->make_term(Op(BVComp), i.s, bv32_zero)));
// }
//
// si64_t si32_to_si64_zext(SmtSolver solver, si32_t i) {
//     mk_op(i, si64_t, (uint32_t) i.c, solver->make_term(Op(Zero_Extend, 32), i.s));
// }
// si64_t si32_to_si64_sext(SmtSolver solver, si32_t i) {
//     mk_op(i, si64_t, i.c, solver->make_term(Op(Sign_Extend, 32), i.s));
// }
// si16_t si32_to_si16(SmtSolver solver, si32_t i) {
//     mk_op(i, si16_t, (int16_t) i.c, solver->make_term(Op(Extract, 15, 0), i.s));
// }
// si8_t si32_to_si8(SmtSolver solver, si32_t i) {
//     mk_op(i, si8_t, (int8_t) i.c, solver->make_term(Op(Extract, 7, 0), i.s));
// }
