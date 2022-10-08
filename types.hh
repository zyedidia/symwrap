#pragma once

#include "smt-switch/smt.h"

typedef struct {
    bool c;
    smt::Term s;
} sbool_t;

typedef struct {
    int8_t c;
    smt::Term s;
} si8_t;

typedef struct {
    int16_t c;
    smt::Term s;
} si16_t;

typedef struct {
    int32_t c;
    smt::Term s;
} si32_t;

typedef struct {
    int64_t c;
    smt::Term s;
} si64_t;

void stypes_init(smt::SmtSolver solver);
si32_t si32_any(smt::SmtSolver solver, std::string name);
si32_t si32_conc(int32_t i);
smt::Term sym(smt::SmtSolver solver, si32_t i);

si32_t si32_add(smt::SmtSolver solver, si32_t a, si32_t b);
si32_t si32_sub(smt::SmtSolver solver, si32_t a, si32_t b);
si32_t si32_xor(smt::SmtSolver solver, si32_t a, si32_t b);
si32_t si32_or(smt::SmtSolver solver, si32_t a, si32_t b);
si32_t si32_and(smt::SmtSolver solver, si32_t a, si32_t b);
si32_t si32_sll(smt::SmtSolver solver, si32_t a, si32_t b);
si32_t si32_srl(smt::SmtSolver solver, si32_t a, si32_t b);
si32_t si32_sra(smt::SmtSolver solver, si32_t a, si32_t b);
si32_t si32_mul(smt::SmtSolver solver, si32_t a, si32_t b);
si32_t si32_sdiv(smt::SmtSolver solver, si32_t a, si32_t b);
si32_t si32_udiv(smt::SmtSolver solver, si32_t a, si32_t b);
si32_t si32_srem(smt::SmtSolver solver, si32_t a, si32_t b);
si32_t si32_urem(smt::SmtSolver solver, si32_t a, si32_t b);
sbool_t si32_slt(smt::SmtSolver solver, si32_t a, si32_t b);
sbool_t si32_ult(smt::SmtSolver solver, si32_t a, si32_t b);

sbool_t si32_eqz(smt::SmtSolver solver, si32_t i);
sbool_t si32_neqz(smt::SmtSolver solver, si32_t i);

si64_t si32_to_si64_zext(smt::SmtSolver solver, si32_t i);
si64_t si32_to_si64_sext(smt::SmtSolver solver, si32_t i);
si16_t si32_to_si16(smt::SmtSolver solver, si32_t i);
si8_t si32_to_si8(smt::SmtSolver solver, si32_t i);
