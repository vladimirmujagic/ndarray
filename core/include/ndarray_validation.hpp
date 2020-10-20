#pragma once

#include <exception>
#include <vector>

#ifndef NDEBUG
    #define ASSERT_CONDITION(Expr, Msg) \
        M_ASSERT(#Expr, Expr, __FILE__, __LINE__, Msg)
#else
    #define ASSERT_CONDITION(Expr, Msg) ;
#endif


struct StopIteration : public std::exception {
    const char * what () const throw () {
        return "IterationStopped.";
    }
};

void M_ASSERT(const char *expr_str, bool expr, const char *file, int line, const char *msg);
void ASSERT_INDICES_IN_RANGE(const std::vector<unsigned> &shape, const std::vector<unsigned> indices);
void ASSERT_SHAPES_MATCH(const std::vector<unsigned> &shape1, const std::vector<unsigned> shape2);