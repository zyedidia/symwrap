#pragma once

#include "uint.h"
#include "sint.h"

#include "smt-switch/smt.h"

namespace sym {
    using namespace smt;

    template <int w_>
    class bv {
    public:
        bv(std::string name, SmtSolver solver) {
            Sort bvn = solver->make_sort(BV, w_);
            s_ = solver->make_symbol(name, bvn);
        }
        bv(int64_t val) {
            c_ = SInt<w_>(val);
        }
        bv(SInt<w_> sint) {
            c_ = sint;
        }
        bv(UInt<w_> uint) {
            c_ = uint.asSInt();
        }
        bv(Term term) {
            s_ = term;
        }

        bool concrete() const {
            return s_ == nullptr;
        }

        Term sym(SmtSolver s) const {
            if (!concrete()) {
                return s_;
            }
            // TODO: support larger bit-widths
            static_assert(w_ <= 64);
            return s->make_term(c_.as_single_word(), s->make_sort(BV, w_));
        }

        bv<w_> op_neg(SmtSolver s) const {
            if (concrete()) {
                return bv<w_>(~c_);
            }
            return s->make_term(Op(BVNeg), s_);
        }

#define mk_binop(other, solver, conc_op, sym_op)               \
    do {                                              \
        if (concrete() && other.concrete()) {   \
            return bv<w_>(conc_op); \
        }                                             \
        return solver->make_term(Op(sym_op), sym(solver), other.sym(solver)); \
    } while (0)


        bv<w_> op_add(const bv<w_> &other, SmtSolver s) const {
            mk_binop(other, s, c_.addw(other.c_), BVAdd);
        }
        bv<w_> op_sub(const bv<w_> &other, SmtSolver s) const {
            mk_binop(other, s, c_.subw(other.c_), BVSub);
        }
        bv<w_> op_xor(const bv<w_> &other, SmtSolver s) const {
            mk_binop(other, s, c_ ^ other.c_, BVXor);
        }
        bv<w_> op_or(const bv<w_> &other, SmtSolver s) const {
            mk_binop(other, s, c_ | other.c_, BVOr);
        }
        bv<w_> op_and(const bv<w_> &other, SmtSolver s) const {
            mk_binop(other, s, c_ & other.c_, BVAnd);
        }
        bv<w_> op_sll(const bv<w_> &other, SmtSolver s) const {
            mk_binop(other, s, c_ << other.c_, BVShl);
        }
        bv<w_> op_srl(const bv<w_> &other, SmtSolver s) const {
            mk_binop(other, s, c_.asUInt() >> other.c_.asUInt(), BVLshr);
        }
        bv<w_> op_sra(const bv<w_> &other, SmtSolver s) const {
            mk_binop(other, s, c_ >> other.c_, BVAshr);
        }
        bv<w_> op_mul(const bv<w_> &other, SmtSolver s) const {
            mk_binop(other, s, c_ * other.c_, BVMul);
        }
        bv<w_> op_sdiv(const bv<w_> &other, SmtSolver s) const {
            mk_binop(other, s, c_.divw(other.c_), BVSdiv);
        }
        bv<w_> op_udiv(const bv<w_> &other, SmtSolver s) const {
            mk_binop(other, s, c_.asUInt() / other.c_.asUInt(), BVUdiv);
        }
        bv<w_> op_srem(const bv<w_> &other, SmtSolver s) const {
            mk_binop(other, s, c_ % other.c_, BVSrem);
        }
        bv<w_> op_urem(const bv<w_> &other, SmtSolver s) const {
            mk_binop(other, s, c_.asUInt() % other.c_.asUInt(), BVUrem);
        }

#define mk_bool_binop(other, solver, conc_op, sym_op)        \
    do {                                            \
        if (concrete() && other.concrete()) { \
            return bv<1>(conc_op); \
        }                                           \
        return solver->make_term(Op(sym_op), sym(solver), other.sym(solver)); \
    } while (0)

        bv<1> op_slt(const bv<w_> &other, SmtSolver s) const {
            mk_bool_binop(other, s, c_ < other.c_, BVSlt);
        }
        bv<1> op_ult(const bv<w_> &other, SmtSolver s) const {
            mk_bool_binop(other, s, c_.asUInt() < other.c_.asUInt(), BVUlt);
        }

#define mk_op(solver, conc_op, sym_op)         \
    do {                                         \
        if (concrete()) {                  \
            return conc_op; \
        }                                        \
        return sym_op; \
    } while (0)

        bv<1> op_eqz(SmtSolver s) const {
            mk_op(s, c_ == 0, s->make_term(Op(BVComp), sym(s), bv<w_>(0).sym(s)));
        }
        bv<1> op_neqz(SmtSolver s) const {
            mk_op(s, c_ != 0, s->make_term(Op(BVNot), s->make_term(Op(BVComp), sym(s), bv<w_>(0).sym(s))));
        }

        SInt<w_> c_;
        Term s_;
    };
}
