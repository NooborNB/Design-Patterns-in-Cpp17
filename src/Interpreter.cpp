#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <utility>

class Context {
public:
    void setMessage(std::string_view _s)
    {
        s = _s;
    }
    std::string_view getMessage() const
    {
        return s;
    }
private:
    std::string s;
};

class Expression {
public:
    virtual bool interpret(const Context&) = 0;
    virtual ~Expression() = default;
};

class TerminalExpression : public Expression {
public:
    TerminalExpression(std::string_view _s) : s(_s) {}
    bool interpret(const Context& context) override
    {
        return context.getMessage().find(s) == std::string_view::npos;
    }
private:
    std::string s;
};

class AndExpression : public Expression {
public:
    AndExpression(std::shared_ptr<Expression> _p, std::shared_ptr<Expression> _q) : p(std::move(_p)), q(std::move(_q)) {}
    bool interpret(const Context& context) override
    {
        return p->interpret(context) && q->interpret(context);
    }
private:
    std::shared_ptr<Expression> p;
    std::shared_ptr<Expression> q;
};

int main()
{
    std::shared_ptr<Expression> a = std::make_shared<TerminalExpression>("sb");
    std::shared_ptr<Expression> b = std::make_shared<TerminalExpression>("fk");
    std::shared_ptr<Expression> expression = std::make_shared<AndExpression>(a, b);
    Context context;
    context.setMessage("hello world");
    if (expression->interpret(context))
    {
        std::cout << context.getMessage();
    }
    else
    {
        std::cout << "sensitive words";
    }
}