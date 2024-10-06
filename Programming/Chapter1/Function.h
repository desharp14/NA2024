#ifndef FUNCTION_H
#define FUNCTION_H

class Function {
public:
    // Pure virtual function to evaluate f(x)
    virtual double operator()(double x) const = 0;

    // Virtual function for derivative (needed for Newton's method)
    virtual double derivative(double x) const { return 0; }

    virtual ~Function() = default;
};

#endif // FUNCTION_H
